/**
 * @param {number[]} nums
 * @return {number[]}
 */
var findDuplicates = function(nums) {
    
    let ans=[];
    for(const n of nums){
        let ind = Math.abs(n)-1;
        if(nums[ind]<0){
            ans.push(Math.abs(n));
        }else{
            nums[ind]=-nums[ind];
        }
    }
    return ans;
};