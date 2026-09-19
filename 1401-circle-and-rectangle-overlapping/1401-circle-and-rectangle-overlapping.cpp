class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int xClosest = x1;
        int yClosest = y1;

        if(xCenter < x1 ){
            xClosest = x1;
        }else if(xCenter < x2){
            xClosest = xCenter;
        }else{
            xClosest = x2;
        }

        if(yCenter < y1){
            yClosest = y1;
        }else if(yCenter < y2){
            yClosest = yCenter;
        }else{
            yClosest = y2;
        }

        int dist = (xCenter - xClosest)*(xCenter - xClosest) + (yCenter - yClosest)*(yCenter - yClosest);
        
        return sqrt(dist)<=radius;
        
    }
};