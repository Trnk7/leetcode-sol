/**
 * @param {number} n
 * @return {number[][]}
 */
var generateMatrix = function(n) {
    let matrix = new Array(n).fill(0).map(()=>new Array(n).fill(null));
    let c=1;
    let i=0;
    let j=0;
    let dx=1;
    let dy=0;
    while(c<=n*n){
        matrix[j][i]=c++;
        if(matrix[(j+dy+n)%n][(i+dx+n)%n]!=null){
            let t = dx;
            dx=-dy;
            dy=t;
        }
        i+=dx;
        j+=dy;
    }
    return matrix;
};