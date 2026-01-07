/**
 * @param {string} s
 * @return {string}
 */
var frequencySort = function(s) {
    let freq = {};
    for(let c of s){
        if(freq[c])freq[c]++;
        else freq[c]=1;
    }
    let sorted = Object.keys(freq).sort((a,b)=>freq[b]-freq[a]);
    let ans="";
    for(let c of sorted){
        ans+=c.repeat(freq[c]);
    }
    return ans;
};