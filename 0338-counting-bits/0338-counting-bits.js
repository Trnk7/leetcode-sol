/**
 * @param {number} n
 * @return {number[]}
 */
function isPowerOf2(n){
    return !(n&(n-1));
}
var countBits = function(n) {
    let ans=[0]
    for(let i=1;i<=n;i++){
        if(i%2==0){
            if(isPowerOf2(i)){
                ans.push(1)
            }else{
                ans.push(ans[i/2])
            }
        }else{
            ans.push(ans[ans.length-1]+1)
        }
    }
    return ans;
};