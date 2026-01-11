/**
 * @param {number} left
 * @param {number} right
 * @return {number}
 */
var rangeBitwiseAnd = function(left, right) {
    let c=0;
    while(left!=right){
        c++
        left=left>>1;
        right=right>>1;
    }
    return left<<c;
};