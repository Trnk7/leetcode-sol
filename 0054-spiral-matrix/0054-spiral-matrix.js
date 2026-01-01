/**
 * @param {number[][]} matrix
 * @return {number[]}
 */
var spiralOrder = function(matrix) {
    let i=0;
    let j=0;
    let dx=1;
    let dy=0;
    let ans=[];
    let m=matrix.length;
    let n=matrix[0].length;

    while(ans.length<n*m){
     ans.push(matrix[j][i]);
        matrix[j][i]=null;
        if(matrix[(j+dy+m)%m][(i+dx+n)%n]===null){
            let temp=dx;
            dx=-dy;
            dy=temp;
        }
        i+=dx;
        j+=dy;  
    }
    return ans;
};