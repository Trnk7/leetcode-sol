/**
 * @param {number[]} nums
 */
var Solution = function(nums) {
    this.original = nums;
    this.suff=[...this.original];
};

/**
 * @return {number[]}
 */
Solution.prototype.reset = function() {
    return this.original;
};

/**
 * @return {number[]}
 */
Solution.prototype.shuffle = function() {
   
    this.suff.sort((a,b)=>{
        return Math.random()<0.5?1:-1;
    })
    return this.suff;
};

/** 
 * Your Solution object will be instantiated and called as such:
 * var obj = new Solution(nums)
 * var param_1 = obj.reset()
 * var param_2 = obj.shuffle()
 */