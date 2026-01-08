/**
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
var commonFactors = function(a, b)  {
    let lim = Math.min(a,b);
    let liM = Math.max(a,b);
    let fLim=[]
    for(let i=0;i*i<=lim;i++){
        if(lim%i==0)fLim.push(i,lim/i);
        if(lim==i*i)fLim.pop();
    }
    if(a==b){
        return fLim.length;
    }
    let ans=0;
    for(let i=0;i<fLim.length;i++){
        if(liM%fLim[i]==0)ans++
    }
    
    return ans;

};