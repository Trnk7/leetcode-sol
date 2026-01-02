/**
 * @param {string} s
 * @param {string} t
 * @return {character}
 */
var findTheDifference = function(s, t) {
    let sd = new Array(26).fill(0)
    let td = new Array(26).fill(0)

    for(let c of s){
        sd[c.charCodeAt(0)-'a'.charCodeAt(0)]++;
    }
    for(let c of t){
        td[c.charCodeAt(0)-'a'.charCodeAt(0)]++;
    }
    for(let i=0;i<26;i++){
        if(td[i]>sd[i]){
            return String.fromCharCode(i+'a'.charCodeAt(0));
        }
    }
};