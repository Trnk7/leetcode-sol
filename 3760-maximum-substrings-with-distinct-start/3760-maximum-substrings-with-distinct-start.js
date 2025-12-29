/**
 * @param {string} s
 * @return {number}
 */
var maxDistinct = function(s) {
    let chars=new Set(s);
    return [...chars].length;
};