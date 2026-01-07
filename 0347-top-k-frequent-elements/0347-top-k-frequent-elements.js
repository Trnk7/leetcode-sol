/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var topKFrequent = function(nums, k) {
    let frq={};
    nums.forEach(a=>{
        if(frq[a])frq[a]++;
        else frq[a]=1;
    })
    let ans= Object.keys(frq).sort((a,b)=>frq[b]-frq[a]).slice(0,k)
    return ans.map(a=>parseInt(a));

};