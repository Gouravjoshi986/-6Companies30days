class Solution {
private: 
    int minDist(int side1,int side2,int center){
        if(center >= side1 && center <= side2)return 0;
        // if we are here then center is outside the rect
        if(center<side1)return side1-center; 
        else return center-side2; 
    }
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // one possible way - checking every point on circumference if it lies on rectangle or not --> impractical 
    // we know - smallest distance from a point - perpendicular
    // we can check from the center of the circle and draw perpendiculars to sides of the rectangle 

    int xDist = minDist(x1,x2,xCenter);
    int yDist = minDist(y1,y2,yCenter);
    // if the point lies in the circle 
    return xDist*xDist + yDist*yDist <= radius*radius;
    }
};

// time complexity - O(1) -- only Arithmetic calculations 
// space complexity - O(1) 