class Solution:
    def removeDuplicates(self, nums: list[int]) -> int:
        f=0
        l=0
        i=1
        while(l<len(nums)):
            if(nums[l]==nums[f]):
                l+=1
                continue
            
            nums[i]=nums[l]
            f=l
            i+=1
        
        return i