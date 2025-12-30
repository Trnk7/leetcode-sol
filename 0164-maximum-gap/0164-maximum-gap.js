/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumGap = function(nums) {
    if(nums.length<2)return 0;
    nums.sort((a,b)=>a-b);
    let m=0;
    for(let i =1;i<nums.length;i++){
        m = Math.max(m,nums[i]-nums[i-1]);
    }
    return m;
};