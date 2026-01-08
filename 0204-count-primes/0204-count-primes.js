/**
 * @param {number} n
 * @return {number}
 */
var countPrimes = function(n) {
    let list = new Array(n).fill(1);
    let i=2;
    while(i*i<n){
        if(!list[i]){
            i++;
            continue;
        }else{
            for(let j=i*i;j<n;j+=i){
                list[j]=0;
            }
        }
        i++;
    }
    let ans=0;
    for(let i=2;i<n;i++){
        if(list[i])ans++;
    }
    return ans;
};