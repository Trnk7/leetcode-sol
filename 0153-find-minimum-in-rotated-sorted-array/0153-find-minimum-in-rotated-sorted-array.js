/**
 * @param {number[]} nums
 * @return {number}
 */
var findMin = function(nums) {
    if(nums.length<3){
        return Math.min(...nums);
    }
    let l = 0;
    let r = nums.length-1;
    if(nums[l]<nums[r]){
        return nums[l];
    }
    while(l<r){
        const mid = l+Math.floor((r-l)/2);

        if(nums[mid]<nums[mid-1]&&nums[mid]<nums[mid+1]){
            return nums[mid];
        }
        if(nums[mid]>=nums[l]&&nums[mid]>nums[r]){
            l = mid+1;
        }
        else{
            r = mid-1;
        }
    }
    return nums[l];
};