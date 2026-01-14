/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var findMatrix = function(nums) {
    let dict=new Map();
    nums.forEach((n)=>{
        if(dict.has(n)){
            dict.set(n,dict.get(n)+1)
        }else dict.set(n,1)
    })
    let mat=[]
    for(const [k,v] of dict){
        for(let i=0;i<v;i++){
            if(mat[i]){
                mat[i].push(k)
            }else{
                mat.push([k])
            }
        }
    }
    return mat
};