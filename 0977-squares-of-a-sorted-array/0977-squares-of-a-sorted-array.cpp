/*
 * Copyright (C) 2026 Omega493

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

// Is a (maybe) stripped down version of selena::arena_alloc.
// Get it at https://codeberg.org/Omega493/selena

#ifndef SELENA_ARENA_ALLOC
#define SELENA_ARENA_ALLOC

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# define NOMINMAX
# include <process.h>
# include <Windows.h>
// For VirtualAlloc2 and VirtualFreeEx
# pragma comment(lib, "mincore")
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
# include <sys/mman.h>
# include <unistd.h>
#endif // ^^^ _WIN32 ^^^

#include <atomic>
#include <bit>
#include <bitset>
#include <new>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#define SELENA_ARENA_OVERLOAD_NEW_DELETE
#define SELENA_ARENA_CLEANUP_ON_EXIT

namespace selena {

class arena_alloc {
public:
  static void* alloc(
    const std::size_t size_,
    const std::align_val_t alignment_ = static_cast<std::align_val_t>(alignof(std::max_align_t))
  ) noexcept {
    if (!size_) {
      return nullptr;
    }

    tl_teardown_.ping();

    const std::size_t align_val_{ static_cast<std::size_t>(alignment_) };

    const std::size_t req_size_{ size_ + align_val_ + sizeof(allocator_header) };

    if (req_size_ <= page_size) {
      const std::size_t class_idx_{ get_class_idx(req_size_) };

      if (tl_free_lists_[class_idx_]) {
        free_node* node_{ tl_free_lists_[class_idx_] };
        tl_free_lists_[class_idx_] = node_->next_;

        std::byte* base_ptr_{ reinterpret_cast<std::byte*>(node_) };
        std::byte* data_ptr_{
          reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
        };

        allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
        header_->size_ = get_chunk_size(class_idx_);
        header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

        return data_ptr_;
      }

      void* page_ptr_{ alloc_pages(1) };

      if (!page_ptr_) {
        return nullptr;
      }

      const std::size_t chunk_sz_{ get_chunk_size(class_idx_) };
      const std::size_t num_chunks_{ page_size / chunk_sz_ };

      std::byte* byte_ptr_{ static_cast<std::byte*>(page_ptr_) };

      for (std::size_t i_{}; i_ < num_chunks_; ++i_) {
        free_node* node_{ reinterpret_cast<free_node*>(byte_ptr_ + (i_ * chunk_sz_)) };

        node_->next_ = tl_free_lists_[class_idx_];
        tl_free_lists_[class_idx_] = node_;
      }

      free_node* node_{ tl_free_lists_[class_idx_] };
      tl_free_lists_[class_idx_] = node_->next_;

      std::byte* base_ptr_{ reinterpret_cast<std::byte*>(node_) };
      std::byte* data_ptr_{
        reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
      };

      allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
      header_->size_ = chunk_sz_;
      header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

      return data_ptr_;
    }

    if (req_size_ > (arena_size - page_size)) {
      const std::size_t new_req_size_{ req_size_ + sizeof(large_allocs) };
      void* os_ptr_{ reserve_os(new_req_size_) };

      if (!os_ptr_) {
        return nullptr;
      }

      if (!commit_os(os_ptr_, new_req_size_)) {
        if (!release_os(os_ptr_, new_req_size_)) {
          // Memory leak!
        }

        return nullptr;
      }

      large_allocs* node_{ new(os_ptr_) large_allocs() };
      node_->size_ = new_req_size_;
      node_->npx_ = xor_ptrs<large_allocs>(nullptr, large_allocs_head_);

      if (large_allocs_head_) {
        large_allocs_head_->npx_ = xor_ptrs<large_allocs>(node_, xor_ptrs<large_allocs>(nullptr, large_allocs_head_->npx_));
      }

      large_allocs_head_ = node_;

      std::byte* base_ptr_{ static_cast<std::byte*>(os_ptr_) + sizeof(large_allocs) };
      std::byte* data_ptr_{
        reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
      };

      allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
      header_->size_ = req_size_;
      header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

      return data_ptr_;
    }

    const std::size_t pages_req_{ (req_size_ + page_size - 1) >> std::countr_zero(page_size) };
    void* multi_page_ptr_{ alloc_pages(pages_req_) };

    if (!multi_page_ptr_) {
      return nullptr;
    }

    std::byte* base_ptr_{ static_cast<std::byte*>(multi_page_ptr_) };
    std::byte* data_ptr_{
      reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
    };

    allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
    header_->size_ = pages_req_ << std::countr_zero(page_size);
    header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

    return data_ptr_;
  }

  static void free(void* ptr_) noexcept {
    if (!ptr_) {
      return;
    }

    std::byte* data_ptr_{ reinterpret_cast<std::byte*>(ptr_) };
    allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
    std::byte* base_ptr_{ data_ptr_ - header_->padding_offs_ };

    if (header_->size_ <= page_size) {
      const std::size_t class_idx_{ get_class_idx(header_->size_) };

      free_node* node_{ reinterpret_cast<free_node*>(base_ptr_) };
      node_->next_ = tl_free_lists_[class_idx_];
      tl_free_lists_[class_idx_] = node_;

      return;
    }

    if (header_->size_ > (arena_size - page_size)) {
      std::byte* os_ptr_{ base_ptr_ - sizeof(large_allocs) };
      large_allocs* node_{ reinterpret_cast<large_allocs*>(os_ptr_) };

      large_allocs* curr_{ large_allocs_head_ }, * prev_{ nullptr };

      while (curr_) {
        large_allocs* next_{ xor_ptrs(prev_, curr_->npx_) };

        if (curr_ == node_) {
          if (prev_) {
            prev_->npx_ = xor_ptrs<large_allocs>(xor_ptrs<large_allocs>(prev_->npx_, curr_), next_);
          } else {
            large_allocs_head_ = next_;
          }

          if (next_) {
            next_->npx_ = xor_ptrs<large_allocs>(prev_, xor_ptrs<large_allocs>(curr_, next_->npx_));
          }

          break;
        }

        prev_ = curr_;
        curr_ = next_;
      }

      if (release_os(os_ptr_, node_->size_)) {
        // Update counter in actual code
      } else {
        // Memory leak!
      }
      return;
    }

    free_pages(base_ptr_, header_->size_ >> std::countr_zero(page_size));
  }

  static inline const std::size_t page_size{
#ifdef _WIN32
    static_cast<std::size_t>([]() -> SYSTEM_INFO {
      SYSTEM_INFO temp_;
      std::memset(&temp_, 0, sizeof(temp_));
      GetSystemInfo(&temp_);
      return temp_;
    }().dwPageSize)
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    static_cast<std::size_t>(sysconf(_SC_PAGESIZE))
#endif // ^^^ _WIN32 ^^^
  };

  static constexpr inline std::size_t arena_size{ 1u << 21 };

private:
  struct alignas(std::max_align_t) allocator_header {
    std::size_t size_;
    std::size_t padding_offs_;
  };

  struct free_node {
    free_node* next_;
  };

  struct arena {
    arena* npx_;
    std::uint64_t committed_pages_[8];
  };

  struct large_allocs {
    large_allocs* npx_;
    std::size_t size_;
  };

  struct thread_teardown {
    inline void ping() const noexcept {}

    ~thread_teardown() noexcept {
      arena* curr_{ arena_head_ }, * prev_{ nullptr };

      while (curr_) {
        arena* next_{ xor_ptrs(prev_, curr_->npx_) };

        std::size_t committed_bytes_{};

        for (std::size_t i_{}; i_ < 8; ++i_) {
          const std::uint64_t block_{ curr_->committed_pages_[i_] };
          committed_bytes_ += static_cast<std::size_t>(std::popcount(block_)) << std::countr_zero(page_size);
        }

        if (!release_os(curr_, arena_size)) {
          // Memory leak!
        }

        prev_ = curr_; curr_ = next_;
      }

      arena_head_ = nullptr;

      large_allocs* curr_large_{ large_allocs_head_ };
      large_allocs* prev_large_{ nullptr };

      while (curr_large_) {
        large_allocs* next_large_{ xor_ptrs<large_allocs>(prev_large_, curr_large_->npx_) };

        if (!release_os(curr_large_, curr_large_->size_)) {
          // Memory leak!
        }

        prev_large_ = curr_large_;
        curr_large_ = next_large_;
      }

      large_allocs_head_ = nullptr;

      std::memset(&tl_free_lists_, 0, sizeof(tl_free_lists_));
    }
  };

  static thread_local inline arena* arena_head_{ nullptr };
  static thread_local inline large_allocs* large_allocs_head_{ nullptr };
  static thread_local inline thread_teardown tl_teardown_{};

  static constexpr inline std::size_t num_free_lists_{ 56 };
  static thread_local inline free_node* tl_free_lists_[num_free_lists_]{};

  template <typename T_>
  static inline T_* xor_ptrs(const T_* const next_, const T_* const prev_) noexcept {
    return reinterpret_cast<T_*>(
      reinterpret_cast<std::uint64_t>(next_) ^ reinterpret_cast<std::uint64_t>(prev_)
      );
  }

  static inline const std::size_t get_class_idx(const std::size_t size_) noexcept {
    if (size_ <= 256) {
      return (size_ - 1) >> 3;
    }

    const std::size_t s_{ size_ - 1 };
    const std::size_t b_{ static_cast<std::size_t>(std::bit_width(s_)) - 1 };
    const std::size_t shift_{ b_ - 2 };
    const std::size_t base_idx_{ 32 + ((b_ - 8) << 2) };
    const std::size_t sub_idx_{ (s_ >> shift_) & 3 };

    return base_idx_ + sub_idx_;
  }

  static inline const std::size_t get_chunk_size(const std::size_t idx_) noexcept {
    if (idx_ < 32) {
      return (idx_ + 1) << 3;
    }

    const std::size_t b_{ ((idx_ - 32) >> 2) + 8 };
    const std::size_t sub_{ (idx_ - 32) & 3 };
    const std::size_t shift_{ b_ - 2 };
    const std::size_t base_{ std::size_t(1) << b_ };

    const std::size_t step_{ std::size_t(1) << shift_ };

    return base_ + ((sub_ + 1) * step_);
  }

  static inline void* reserve_os(const std::size_t size_) noexcept {
#ifdef _WIN32
    if (size_ == arena_size) {
      static MEM_ADDRESS_REQUIREMENTS req_{
        .LowestStartingAddress = nullptr,
        .HighestEndingAddress = nullptr,
        .Alignment = arena_size
      };

      static MEM_EXTENDED_PARAMETER param_{
        .Type = MemExtendedParameterAddressRequirements,
        .Pointer = &req_
      };

      return VirtualAlloc2(GetCurrentProcess(), nullptr, size_, MEM_RESERVE, PAGE_NOACCESS, &param_, 1);
    }

    return VirtualAlloc2(GetCurrentProcess(), nullptr, size_, MEM_RESERVE, PAGE_NOACCESS, nullptr, 0);
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    if (size_ == arena_size) {
      const std::size_t resv_size_{ arena_size * 2 }; // Equates to 4 MB
      void* ptr_{ mmap(nullptr, resv_size_, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0) };

      if (ptr_ == MAP_FAILED) {
        return nullptr;
      }

      const std::uintptr_t base_{ reinterpret_cast<std::uintptr_t>(ptr_) };
      const std::uintptr_t aligned_{ (base_ + arena_size - 1) & ~(arena_size - 1) };
      const std::size_t pre_padding_{ aligned_ - base_ };
      const std::size_t post_padding_{ resv_size_ - pre_padding_ - arena_size };

      if (pre_padding_) {
        munmap(reinterpret_cast<void*>(base_), pre_padding_);
      }

      if (post_padding_) {
        munmap(reinterpret_cast<void*>(aligned_ + arena_size), post_padding_);
      }

      return reinterpret_cast<void*>(aligned_);
    }

    void* ptr_{ mmap(nullptr, size_, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0) };

    if (ptr_ == MAP_FAILED) {
      return nullptr;
    }

    return ptr_;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool commit_os(void* start_ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
    return VirtualAlloc2(GetCurrentProcess(), start_ptr_, size_, MEM_COMMIT, PAGE_READWRITE, nullptr, 0) != nullptr;
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    return mprotect(start_ptr_, size_, PROT_READ | PROT_WRITE) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool decommit_os(void* start_ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
# pragma warning(push)
# pragma warning(disable : 6250 28160) // Suppress "results in address space leaks" false positive
    return VirtualFreeEx(GetCurrentProcess(), start_ptr_, size_, MEM_DECOMMIT) != 0;
# pragma warning(pop)
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    madvise(start_ptr_, size_, MADV_DONTNEED);
    return mprotect(start_ptr_, size_, PROT_NONE) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool release_os(void* ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
    return VirtualFreeEx(GetCurrentProcess(), ptr_, 0, MEM_RELEASE) != 0;
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    return munmap(ptr_, size_) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline void* alloc_pages(const std::size_t num_pages_) noexcept {
    arena* curr_{ arena_head_ }, * prev_{ nullptr };

    while (curr_) {
      std::size_t start_page_{}, consecutive_{};

      for (std::size_t i_{ 1 }; i_ < 512; ++i_) {
        const std::size_t block_idx_{ i_ / 64 };
        const std::size_t bit_idx_{ i_ % 64 };

        const std::uint64_t current_block_{ curr_->committed_pages_[block_idx_] };

        if (!(current_block_ & (std::uint64_t(1) << bit_idx_))) {
          if (!consecutive_) {
            start_page_ = i_;
          }

          ++consecutive_;

          if (consecutive_ == num_pages_) {
            void* commit_ptr_{ reinterpret_cast<std::byte*>(curr_) + (start_page_ << std::countr_zero(page_size)) };

            if (!commit_os(commit_ptr_, num_pages_ << std::countr_zero(page_size))) {
              return nullptr;
            }

            for (std::size_t j_{ start_page_ }; j_ < start_page_ + num_pages_; ++j_) {
              const std::size_t set_block_{ j_ / 64 };
              const std::size_t set_bit_{ j_ % 64 };
              curr_->committed_pages_[set_block_] |= (std::uint64_t(1) << set_bit_);
            }

            return commit_ptr_;
          }
        } else {
          consecutive_ = 0;
        }
      }

      arena* next_{ xor_ptrs(prev_, curr_->npx_) };
      prev_ = curr_;
      curr_ = next_;
    }

    arena* new_arena_{ reinterpret_cast<arena*>(reserve_os(arena_size)) };

    if (!new_arena_) {
      return nullptr;
    }

    if (!commit_os(new_arena_, page_size)) {
      if (!release_os(new_arena_, arena_size)) {
        // Memory leak!
      }

      return nullptr;
    }

    new(new_arena_) arena();

    for (std::size_t i_{}; i_ < 8; ++i_) {
      new_arena_->committed_pages_[i_] = 0;
    }

    new_arena_->committed_pages_[0] = 1;

    new_arena_->npx_ = xor_ptrs<arena>(nullptr, arena_head_);

    if (arena_head_) {
      arena_head_->npx_ = xor_ptrs<arena>(new_arena_, xor_ptrs<arena>(nullptr, arena_head_->npx_));
    }

    arena_head_ = new_arena_;

    void* commit_ptr_{ reinterpret_cast<std::byte*>(arena_head_) + page_size };

    if (!commit_os(commit_ptr_, num_pages_ << std::countr_zero(page_size))) {
      return nullptr;
    }

    for (std::size_t j_{ 1 }; j_ < 1 + num_pages_; ++j_) {
      const std::size_t set_block_{ j_ / 64 };
      const std::size_t set_bit_{ j_ % 64 };
      arena_head_->committed_pages_[set_block_] |= (std::uint64_t(1) << set_bit_);
    }

    return commit_ptr_;
  }

  static inline void free_pages(void* ptr_, const std::size_t num_pages_) noexcept {
    std::byte* byte_ptr_{ static_cast<std::byte*>(ptr_) };
    arena* curr_{ reinterpret_cast<arena*>(reinterpret_cast<std::uintptr_t>(ptr_) & ~(arena_size - 1)) };
    std::byte* arena_byte_ptr_{ reinterpret_cast<std::byte*>(curr_) };
    const std::size_t start_page_{ static_cast<std::size_t>(byte_ptr_ - arena_byte_ptr_) >> std::countr_zero(page_size) };

    if (decommit_os(ptr_, num_pages_ << std::countr_zero(page_size))) {
      for (std::size_t i_{ start_page_ }; i_ < start_page_ + num_pages_; ++i_) {
        const std::size_t block_idx_{ i_ / 64 };
        const std::size_t bit_idx_{ i_ % 64 };
        curr_->committed_pages_[block_idx_] &= ~(std::uint64_t(1) << bit_idx_);
      }

      bool is_empty_{ true };

      if (curr_->committed_pages_[0] != 1) {
        is_empty_ = false;
      } else {
        for (std::size_t i_{ 1 }; i_ < 8; ++i_) {
          if (curr_->committed_pages_[i_] != 0) {
            is_empty_ = false;
            break;
          }
        }
      }

      if (is_empty_) {
        arena* c_{ arena_head_ };
        arena* p_{ nullptr };

        while (c_) {
          arena* n_{ xor_ptrs(p_, c_->npx_) };

          if (c_ == curr_) {
            if (p_) {
              p_->npx_ = xor_ptrs<arena>(xor_ptrs<arena>(p_->npx_, c_), n_);
            } else {
              arena_head_ = n_;
            }

            if (n_) {
              n_->npx_ = xor_ptrs<arena>(p_, xor_ptrs<arena>(c_, n_->npx_));
            }

            break;
          }

          p_ = c_;
          c_ = n_;
        }

        if (release_os(curr_, arena_size)) {
          // Update counters in original code...
        } else {
          // Memory Leak!
        }
      }
    } else {
      // Memory leak!
    }
  }

#ifdef SELENA_ARENA_CLEANUP_ON_EXIT
  static inline void free_all() noexcept {
    arena* curr_{ arena_head_ }, * prev_{ nullptr };

    while (curr_) {
      arena* next_{ xor_ptrs<arena>(prev_, curr_->npx_) };

      if (!release_os(curr_, arena_size)) {
        // Memory leak!
      }

      prev_ = curr_;
      curr_ = next_;
    }

    arena_head_ = nullptr;

    large_allocs* curr_large_{ large_allocs_head_ };
    large_allocs* prev_large_{ nullptr };

    while (curr_large_) {
      large_allocs* next_large_{ xor_ptrs<large_allocs>(prev_large_, curr_large_->npx_) };

      if (!release_os(curr_large_, curr_large_->size_)) {
        // Memory leak!
      }

      prev_large_ = curr_large_;
      curr_large_ = next_large_;
    }

    large_allocs_head_ = nullptr;
  }

  static inline const int atexit_registry_{ std::atexit(free_all) };
#endif // SELENA_ARENA_CLEANUP_ON_EXIT
}; // class arena_alloc

} // namespace selena

#ifdef SELENA_ARENA_OVERLOAD_NEW_DELETE

#ifdef _WIN32
# pragma warning(push)
# pragma warning(disable : 28251)
#endif // _WIN32

void* operator new(const std::size_t size_) {
  void* ptr_{ selena::arena_alloc::alloc(size_) };

  if (!ptr_) {
    throw std::bad_alloc();
  }

  return ptr_;
}

void operator delete(void* ptr_) noexcept {
  selena::arena_alloc::free(ptr_);
}

void* operator new[](const std::size_t size_) {
  void* ptr_{ selena::arena_alloc::alloc(size_) };

  if (!ptr_) {
    throw std::bad_alloc();
  }

  return ptr_;
}

void operator delete[](void* ptr_) noexcept {
  selena::arena_alloc::free(ptr_);
}

void operator delete(void* ptr_, std::size_t) noexcept {
  selena::arena_alloc::free(ptr_);
}

void operator delete[](void* ptr_, std::size_t) noexcept {
  selena::arena_alloc::free(ptr_);
}

#ifdef _WIN32
# pragma warning(pop)
#endif // _WIN32

#endif // SELENA_ARENA_OVERLOAD_NEW_DELETE

#endif // SELENA_ARENA_ALLOC

int speed_{ [] {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}() };

using vec_of_int = std::vector<int>;
/*
Two pointers:

class Solution {
public:
  static inline vec_of_int sortedSquares(vec_of_int& vec_) {
    res_->clear(); res_->reserve(vec_.size());

    for (std::ptrdiff_t i_{}, j_{ (std::ptrdiff_t)(vec_.size()) - 1 }; i_ <= j_;) {
      if (std::abs(vec_[i_]) > std::abs(vec_[j_])) {
        res_->push_back(vec_[i_] * vec_[i_]);
        ++i_;
      } else {
        res_->push_back(vec_[j_] * vec_[j_]);
        --j_;
      }
    }

    std::reverse(res_->begin(), res_->end());

    return *res_;
  }

private:
  static inline vec_of_int* res_;
  static inline const bool _start{ []() -> bool {
    res_ = new vec_of_int;
    res_->reserve(10'000);
    return true;
  }() };
};
*/

// Encoding/Decoding. O(1) SC, O(n) TC
class Solution {
public:
  static inline vec_of_int sortedSquares(vec_of_int& vec_) {
    int max_val_{};
    for (std::size_t i_{}; i_ < vec_.size(); ++i_) {
      vec_[i_] = std::abs(vec_[i_]);
      if (vec_[i_] > max_val_) {
        max_val_ = vec_[i_];
      }
    }

    const int m_{ max_val_ + 1 };

    for (std::ptrdiff_t i_{}, j_{ (std::ptrdiff_t)(vec_.size()) - 1 }, k_{ j_ }; i_ <= j_; --k_) {
      const int val_i_{ vec_[i_] % m_ }, val_j_{ vec_[j_] % m_ };

      if (val_i_ > val_j_) {
        vec_[k_] += val_i_ * m_;
        ++i_;
      } else {
        vec_[k_] += val_j_ * m_;
        --j_;
      }
    }
    
    for (std::size_t i_{}; i_ < vec_.size(); ++i_) {
      const int decoded_{ vec_[i_] / m_ };
      vec_[i_] = decoded_ * decoded_;
    }
    return vec_;
  }
};