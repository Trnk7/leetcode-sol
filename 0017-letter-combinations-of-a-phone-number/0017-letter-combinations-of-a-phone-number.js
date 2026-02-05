/**
 * @param {string} digits
 * @return {string[]}
 */
var letterCombinations = function(digits) {
    let dict={'2':'abc','3':'def','4':'ghi','5':'jkl','6':'mno','7':'pqrs','8':'tuv','9':'wxyz'}
    let sol=[];
    let recu=function(s,i){
        if(i==digits.length){
            sol.push(s);
            return;
        }
        let alp=dict[digits[i]];
        for(let j =0;j<alp.length;j++){
            recu(s+alp[j],i+1);
        }
    }
    recu('',0)
    return sol;
};