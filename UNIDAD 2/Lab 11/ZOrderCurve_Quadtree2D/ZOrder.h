//
// Created by HarryLex on 4/11/2022.
//

#ifndef ZORDERCURVE_QUADTREE2D_ZORDER_H
#define ZORDERCURVE_QUADTREE2D_ZORDER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "quadtree.h"
#include "Point.h"
#include <bitset>

// references: https://www.iasj.net/iasj/download/0b544c2c38a03d5e

/*
Z-order & Quad tree building algorithm
Input: Points, K
Output: SequencePointsZOrder
Procedure:
    1. Tree = QuadTree(Points,K)
    2. Initialize Queue
    3. Add Children of Root of Tree to Queue
    4. While True
    5. If Queue is not empty Then
    6. Children = queue.pop()
    7. For each Node in children
    8. Add Node.Children to Queue
    9. For each Point in Node.Points
    10. Code = Morton(Z-order)Encoding(Point.x, Point.y)
    11. Add Code to SequencePointsZOrder
    12. next
    13. next
    14. Else
    15. End
    16. endif
    17. next
    18. End
*/

class ZOrder {
public:
    std::vector<Point> points;
    int K;
    ZOrder(std::vector<Point> points, int K) {
        this->points = points;
        this->K = K;
    }
    std::vector<int> build() {
        QuadTree tree(points);
        tree.recursive_subdivide(tree.root, K);
        std::vector<Node*> children = tree.find_children(tree.root);
        std::vector<int> sequence;
        while (true) {
            if (!children.empty()) {
                std::vector<Node*> new_children;
                for (Node *node : children) {
                    if (node->NW != nullptr) {
                        new_children.push_back(node->NW);
                        new_children.push_back(node->NE);
                        new_children.push_back(node->SW);
                        new_children.push_back(node->SE);
                    }
                    for (Point p : node->points) {
                        int code = morton(p.x, p.y);
                        sequence.push_back(code);
                    }
                }
                children = new_children;
            } else {
                break;
            }
        }
        return sequence;
    }
    int morton(int x, int y) {
        int code = 0;
        for (int i = 0; i < 32; i++) {
            code |= ((x & (1 << i)) << i) | ((y & (1 << i)) << (i + 1));
        }
        return code;
    }

    // print points in Z-order
    void print(std::vector<int> sequence) {
        for (int i = 0; i < sequence.size(); i++) {
            std::cout << sequence[i] << " ";
        }
    }

    // put the  sequence[i] into an n*n matrix
    void print_matrix(std::vector<int> sequence, int n) {
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sequence[i * n + j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << matrix[i][j] << "\t";
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
    void print_range(std::vector<int> sequence, int n, int x1, int x2, int y1, int y2) {
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sequence[i * n + j];
            }
        }
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    /*
     * draw the points and connect with lines
     * draw reactangle around the points in the range x1, x2, y1, y2
    */
    void printZOrder(std::vector<int> sequence, int n, int x1, int x2, int y1, int y2){
        int p1 = n;
        int p2 = n;
        std::vector<Point> points;
        for (int y = 0; y <= p1; y++) { // 0 ≤ x ≤ p1
            for (int x = 0; x <= p2; x++) { // 0 ≤ y ≤ p2
                int code = morton(y, x);
                points.push_back(Point(y, x, code));
            }
        }
        std::sort(points.begin(), points.end(), [](Point a, Point b) {
            return a.z < b.z;
        });

        //draw the points and connect them with lines and draw reactangle around the points in the range x1, x2, y1, y2
        //draw the points and connect them with lines and draw reactangle around the points in the range x1, x2, y1, y2
        sf::RenderWindow window(sf::VideoMode(800, 800), "Z order curve");
        sf::CircleShape shape(2); // radius = 2
        shape.setFillColor(sf::Color::White); // white color
        sf::RectangleShape rectangle(sf::Vector2f(800, 800)); // rectangle with size 800x800
        rectangle.setFillColor(sf::Color::Transparent); // transparent color
        rectangle.setOutlineColor(sf::Color::Green); // green color
        rectangle.setOutlineThickness(1); // thickness = 1
        sf::VertexArray lines(sf::LinesStrip, points.size()); // lines between points
        for (int i = 0; i < points.size(); i++) { // for each point
            Point p = points[i]; // get point
            shape.setPosition(p.x * 800 / p1, p.y * 800 / p2); // set position of the point
            window.draw(shape); // draw point
            lines[i].position = sf::Vector2f(p.x * 800 / p1, p.y * 800 / p2); // set position of the line
            lines[i].color = sf::Color::Red; // red color
        }
        window.draw(lines); // draw lines
        rectangle.setPosition(x1 * 800 / p1, y1 * 800 / p2); // set position of the rectangle
        rectangle.setSize(sf::Vector2f((x2 - x1) * 800 / p1, (y2 - y1) * 800 / p2)); // set size of the rectangle
        window.draw(rectangle); // draw rectangle
        window.display(); // display the window
        sf::sleep(sf::seconds(15)); // sleep for 5 seconds
    }
};

#endif //ZORDERCURVE_QUADTREE2D_ZORDER_H
