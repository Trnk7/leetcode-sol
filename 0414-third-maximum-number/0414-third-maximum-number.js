/**
 * @param {number[]} nums
 * @return {number}
 */
var thirdMax = function(nums) {
    let f =-Infinity;
    let s =-Infinity;
    let t =-Infinity;

    for(let i=0;i<nums.length;i++){
        if(nums[i]==f||nums[i]==s||nums[i]==t)continue;
        if(nums[i]>f){
            t =s;
            s= f;
            f = nums[i];
        }else if(nums[i]>s){
            t =s;
            s = nums[i];
        }else if(nums[i]>t){
            t = nums[i];
        }
    }
    if(t==-Infinity){
        return f;
    }else{
        return t;
    }
};