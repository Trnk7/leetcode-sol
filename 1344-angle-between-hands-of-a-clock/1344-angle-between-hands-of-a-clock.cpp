class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hourAngle = 30*(hour%12)+(double)minutes/2.0;
        double minuteAngle = (double)minutes*6;

        double diff = abs(hourAngle-minuteAngle);
        return diff<180?diff:360-diff;
    }
};