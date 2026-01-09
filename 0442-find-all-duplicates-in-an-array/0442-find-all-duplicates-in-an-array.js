/**
 * @param {number[]} nums
 * @return {number[]}
 */
var findDuplicates = function(nums) {
    let freq = new Uint8Array(nums.length+1).fill(0);
    for(let n of nums){
        freq[n]++;
    }
    let ans=[];
    for(let i=1;i<freq.length;i++){
        if(freq[i]>1){
            ans.push(i);
        }
    }
    return ans;
};