/**
 * @param {number[]} nums
 * @return {number}
 */
var repeatedNTimes = function(nums) {
  let n = Math.floor(nums.length/2);
  let dict={};
  for(let i=0;i<n*2;i++){
    console.log(dict);
    if(dict[nums[i]]){
        return nums[i];
    }else{
        dict[nums[i]]=1;
    }
  }

};