/**
 * @param {number[]} nums
 * @return {number}
 */
var triangularSum = function(nums) {
    for(let i=1;i<=nums.length;i++){
        
        for(let j=0;j<nums.length-i;j++){
            nums[j]=(nums[j]+nums[j+1])%10;
        }
    }
    return nums[0];
};