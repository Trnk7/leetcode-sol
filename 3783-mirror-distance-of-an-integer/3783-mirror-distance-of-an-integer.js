/**
 * @param {number} n
 * @return {number}
 */
var mirrorDistance = function(n) {
    let num = n.toString();
    let revnum = [...num].reverse().join('');
    let ans =Math.abs(parseInt(num)-parseInt(revnum))
    return ans;
};