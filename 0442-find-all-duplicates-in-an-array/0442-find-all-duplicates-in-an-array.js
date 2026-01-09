/**
 * @param {number[]} nums
 * @return {number[]}
 */
var findDuplicates = function(nums) {
    
    let ans=[];
    for(let i=0;i<nums.length;i++){
        let ind = Math.abs(nums[i])-1;
        if(nums[ind]<0){
            ans.push(Math.abs(nums[i]));
        }else{
            nums[ind]=-nums[ind];
        }
    }
    return ans;
};