/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var findMatrix = function(nums) {
    let dict={};
    nums.forEach((n)=>{
        dict[n]=dict[n]+1||1;
    })
    let mat=[]
    for(let k in dict){
        for(let i=0;i<dict[k];i++){
            if(mat[i]){
                mat[i].push(parseInt(k))
            }else{
                mat.push([parseInt(k)])
            }
        }
    }
    return mat
};