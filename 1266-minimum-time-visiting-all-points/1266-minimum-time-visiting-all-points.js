/**
 * @param {number[][]} points
 * @return {number}
 */
var minTimeToVisitAllPoints = function(points) {
    let t=0;
    for(let i=1;i<points.length;i++){
        let difx = Math.abs(points[i-1][0]-points[i][0])
        let dify = Math.abs(points[i-1][1]-points[i][1])
        t+=Math.max(difx,dify)
    }
    return t;
};