/*Author: Harold Alejandro Villanueva Borda
 * Date: 2022/11/01
 * Department: Computer Science
 * Curse: Advance Data Structures
 * Institution: San Pablo Catholic University of Arequipa
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "quadtree.h"
#include "Point.h"
#include "HOrder.h"

/*
Quad tree building & H-order algorithm
Input: Points, K
Output: SequencePointsHOrder
Procedure:
    1. Tree = QuadTree(Points,K)
    2. Initialize Queue
    3. Add Children of Root of Tree to Queue
    4. While True
    5. If Queue is not empty Then
    6. Children = queue.pop()
    7. For each Node in children
    8. For each Point in Node.Points
    9. Code = HilbertDistanceFromCoordinates(Point.x, Point.y, 32)
    10. Add Code to SequencePointsZOrder
    11. next
    12. next
    13. Else
    14. End
    15. endif
    16. next
    17. End
*/


int main() {
    int n = 128;
    int K = n*n;
    std::vector<Point> points;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            points.push_back(Point(i, j,i));
        }
    }

    HOrder hOrder(points, K);
    std::vector<int> sequence = hOrder.build();
    //hOrder.print_matrix(sequence, n);
    hOrder.print_matrix_sfml(sequence, n);
    //hOrder.print_points(sequence, n);
    //hOrder.print_points_and_connect(sequence, n);
}
