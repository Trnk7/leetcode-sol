/**
 * @param {number[]} nums
 */
var Solution = function(nums) {
    this.frq=new Map();
    for(let i=0;i<nums.length;i++){
        let n = nums[i]
        if(this.frq.has(n)){
            this.frq.get(n).push(i)
        }else{
            this.frq.set(n,[i])
        }
    }
};

/** 
 * @param {number} target
 * @return {number}
 */
Solution.prototype.pick = function(target) {
    let rnd = Math.floor(this.frq.get(target).length*Math.random())
    return this.frq.get(target)[rnd];
};

/** 
 * Your Solution object will be instantiated and called as such:
 * var obj = new Solution(nums)
 * var param_1 = obj.pick(target)
 */