/*Author: Harold Alejandro Villanueva Borda
 * Date: 2022/11/01
 * Department: Computer Science
 * Curse: Advance Data Structures
 * Institution: San Pablo Catholic University of Arequipa
*/

#include <iostream>
#include <vector>
#include <algorithm>

// from https://en.wikipedia.org/wiki/Z-order_curve

// implement Z order curve for 2D points with integer coordinates 0 ≤ x ≤ 7, 0 ≤ y ≤ 7

/*
input: x = 7, y = 7
 output:
       x = 0  1  2  3  4  5  6  7
 y = 0     0  1  4  5 16 17 20 21
 y = 1     2  3  6  7 18 19 22 23
 y = 2     8  9 12 13 24 25 28 29
 y = 3    10 11 14 15 26 27 30 31
 y = 4    32 33 36 37 48 49 52 53
 y = 5    34 35 38 39 50 51 54 55
 y = 6    40 41 44 45 56 57 60 61
 y = 7    42 43 46 47 58 59 62 63
 */

// 2D points with integer coordinates 0 ≤ x ≤ p1, 0 ≤ y ≤ p2
struct Point {
    int x;
    int y;
};

// Z order curve for 2D points with integer coordinates 0 ≤ x ≤ p1, 0 ≤ y ≤ p2
int zOrder(Point p) {
    int x = p.x;
    int y = p.y;
    int z = 0;
    for (int i = 0; i < 3; ++i) { // 3 bits
        z |= (x & 1) << (2 * i + 1); // here we use 2*i+1 instead of 2*i
        z |= (y & 1) << (2 * i);   // here we use 2*i instead of 2*i+1
        x >>= 1; // x = x / 2
        y >>= 1;  // y = y / 2
    }
    return z;
}

// print
void printZOrder(int p1, int p2) {
    std::vector<Point> points;
    for (int y = 0; y <= p1; ++y) { // 0 ≤ x ≤ p1
        for (int x = 0; x <= p2; ++x) { // 0 ≤ y ≤ p2
            Point p = {y, x};
            points.push_back(p);
        }
    }
    std::sort(points.begin(), points.end(), [](Point p1, Point p2) {  // this function is used to sort the points in the vector
        return zOrder(p1) < zOrder(p2); // sort by z order curve value
    });
    //std::cout << "       x = 0  1  2  3  4  5  6  7" << std::endl;
    for (int y = 0; y <= p1; y++) { // 0 ≤ y ≤ p1
        //std::cout << " y = " << y << "    ";
        for (int x = 0; x <= p2; x++) { // 0 ≤ x ≤ p2
            Point p = {y, x};
            std::cout << zOrder(p) << "\t"; // print z order curve value
        }
        std::cout << std::endl;
    }
}

/*
  the range being queried (x = [2,3], y = [2,6]) is
  output:
    12 13
    14 15
    36 37
    38 39
    44 45
    46 47
 */

void queryZOrder(int x1, int x2, int y1, int y2) {
    int z1 = zOrder({x1, y1});
    int z2 = zOrder({x2, y2});
    int z = z1;
    for (int i = 0; i < 3; i++) { // 3 bits
        int x = (z & 2) >> 1; // here we use 2 instead of 1
        int y = z & 1; // here we use 1 instead of 2
        if (x == 0 && y == 0) { // 00
            z |= 1; // here we use 1 instead of 2
        } else if (x == 1 && y == 0) { // 10
            z |= 2; // here we use 2 instead of 1
        } else if (x == 0 && y == 1) { // 01
            z |= 3; // here we use 3 instead of 1
        } else if (x == 1 && y == 1) { // 11
            z |= 3; // here we use 3 instead of 2
        }
        if (z >= z2) { // if z is greater than z2, then break
            break;
        }
        z <<= 2; // z = z * 4
    }
    //print query
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            Point p = {y, x};
            std::cout << zOrder(p) << "\t";
        }
        std::cout << std::endl;
    }
}


int main() {
    std::cout << "Z order curve:" << std::endl;
    printZOrder(7,7);
    std::cout << std::endl;
    std::cout << "Query z order curve:" << std::endl;
    queryZOrder(2,3,2,6);
    //queryZOrder(2,4,2,5);
    return 0;
}