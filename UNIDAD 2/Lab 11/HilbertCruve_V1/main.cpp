#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>

struct Point {
    int x, y;

    //rotate/flip a quadrant appropriately
    void rot(int n, bool rx, bool ry) {
        if (!ry) { //rotate 90 degrees
            if (rx) {   //flip x and y
                x = (n - 1) - x;    //flip x
                y = (n - 1) - y;    //flip y
            }
            std::swap(x, y);    //rotate 90 degrees
        }
    }
};

Point fromD(int n, int d) {
    Point p = { 0, 0 }; //start at origin
    bool rx, ry;    //flip x and y
    int t = d;  //temp variable
    for (int s = 1; s < n; s <<= 1) {   //iterate through each quadrant
        rx = ((t & 2) != 0);    //check if x needs to be flipped
        ry = (((t ^ (rx ? 1 : 0)) & 1) != 0);   //check if y needs to be flipped
        p.rot(s, rx, ry);   //rotate/flip quadrant
        p.x += (rx ? s : 0);    //add x offset
        p.y += (ry ? s : 0);    //add y offset
        t >>= 2;    //move to next quadrant
    }
    return p;
}

std::vector<Point> getPointsForCurve(int n) {   //get points for curve
    std::vector<Point> points;  //points for curve
    for (int d = 0; d < n * n; ++d) {   //iterate through each point
        points.push_back(fromD(n, d));  //add point to curve
    }
    return points;  //return points
}

std::vector<std::string> drawCurve(const std::vector<Point> &points, int n) {   //draw curve
    auto canvas = new char *[n];    //create canvas
    for (size_t i = 0; i < n; i++) {    //iterate through each row
        canvas[i] = new char[n * 3 - 2];    //create row
        std::memset(canvas[i], ' ', n * 3 - 2); //fill row with spaces
    }

    for (int i = 1; i < points.size(); i++) {   //iterate through each point
        auto lastPoint = points[i - 1]; //get last point
        auto curPoint = points[i];  //get current point
        int deltaX = curPoint.x - lastPoint.x;  //get x difference
        int deltaY = curPoint.y - lastPoint.y;  //get y difference
        if (deltaX == 0) {
            // vertical line
            int row = std::max(curPoint.y, lastPoint.y);    //get row
            int col = curPoint.x * 3;   //get column
            canvas[row][col] = '|'; //draw line
        } else {
            // horizontal line
            int row = curPoint.y;   //get row
            int col = std::min(curPoint.x, lastPoint.x) * 3 + 1;    //get column
            canvas[row][col] = '_'; //draw line
            canvas[row][col + 1] = '_'; //draw line
        }
    }

    std::vector<std::string> lines; //lines for curve
    for (size_t i = 0; i < n; i++) {    //iterate through each row
        std::string temp;   //temp string
        temp.assign(canvas[i], n * 3 - 2);  //assign row to temp string
        lines.push_back(temp);  //add temp string to lines
    }
    return lines;   //return lines
}

void test(){
    for (int order = 1; order < 6; order++) {
        int n = 1 << order;
        auto points = getPointsForCurve(n);
        std::cout << "Hilbert curve, order=" << order << '\n';
        auto lines = drawCurve(points, n);
        for (auto &line : lines) {
            std::cout << line << '\n';
        }
        std::cout << '\n';
    }
}

int main() {

    test();
    return 0;
}