#include<bits/stdc++.h>
using namespace std;
// A very good problem .here the method of picking one rectangle and picking all points from it wont work as According to the problem, "randomly and uniformily picks an integer point in the space covered by the rectangles"

// if both set of points are taken together :
// It is saying that, now I am providing you a new set S = S1 + S2, where S = {p11, p12, ............, p1n, p21, p22, ........., p2m} , within this new set of points that are merged together, randomly pick a point from it. What do you think of the probability of getting p1i and p2j right now ? They are exactly the same, which is 1 / (n + m).

//But on picking one rect first then picking points :
// // the chance of getting S1 and S2 are both 1 / 2, so far so good. How ever, within S1 and S2, the chance of getting point p1i and p2j are 1 / n and 1 / m. So the final chance of getting p1i and p2j are:
// probability_of_getting_p1i = 1 / (2 * n)
// probability_of_getting_p2j = 1 / (2 * m)
// The probability depends on the size of two rectangle

// We can overcome this by increasing the chances based on the no of integers points in the rectangle (using this and not area because we need to return integer points)
// bigger rect will have higher chances to be choosen randomly.
// we will use a map to assign a rect acc to its (points convered) area.
// area = (b-a)*(d-c)   . no of integer points = (b-a+1)*(d-c+1)
class Solution{
public:
    map<int,vector<int>>mp;
    int total_area=0;
    
    Solution(vector<vector<int>>&rects){
        for(auto rect:rects){
            int pointArea = (rect[3]-rect[1]+1)*(rect[2]-rect[0]+1);
            total_area+=pointArea;
            mp[total_area]=rect;
        }
    }

    vector<int> pick(){
        int r = rand()%total_area;  // picking up a random area between 0 and total_area
        auto temp = mp.upper_bound(r); //finds area just greater than this random area
        vector<int>z = temp->second;
        int x = z[0]+rand()%(z[2]-z[0]+1);
        int y = z[1]+rand()%(z[3]-z[1]+1);

        return {x,y};
    }
};

// TC - solution fn - O(nlogn) ( due to map )
// pick fn - O(logn) due to upper bound  . rand() is O(1)