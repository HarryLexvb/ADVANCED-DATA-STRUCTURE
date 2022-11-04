/*Author: Harold Alejandro Villanueva Borda
 * Date: 2022/11/01
 * Department: Computer Science
 * Curse: Advance Data Structures
 * Institution: San Pablo Catholic University of Arequipa
*/

#include <iostream>
#include "ZOrder.h"

int main() {
    std::vector<Point> points;
    int n = 8;
    for (int i = 0; i < n*n; i++) {
        points.push_back(Point(i % n, i / n, i));
    }
    ZOrder zOrder(points, n*n); // n*n is the max number of points in a node
    std::vector<int> sequence = zOrder.build(); // build the Z-order sequence
    std::cout << "Z-order sequence: " << std::endl;
    zOrder.print_matrix(sequence, n); // print the sequence in a n*n matrix
    std::cout << "range: " << std::endl;
    zOrder.print_range(sequence, n, 2, 3, 2, 6);
    zOrder.printZOrder(sequence, n, 2, 3, 2, 6);
    return 0;
}
