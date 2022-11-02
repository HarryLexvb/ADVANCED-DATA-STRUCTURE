#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include "SFML/Graphics.hpp"

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

//draw curve
void drawCurve(sf::RenderWindow& window, std::vector<Point> points, int n) {
    sf::VertexArray lines(sf::LinesStrip, points.size());  //lines for curve
    for (int i = 0; i < points.size(); ++i) {  //iterate through each point
        lines[i].position = sf::Vector2f(points[i].x * 800 / n, points[i].y * 800 / n);  //set position of line
        lines[i].color = sf::Color::White;  //set color of line
    }
    window.draw(lines); //draw lines
}

//range query for curve
std::vector<Point> rangeQuery(std::vector<Point> points, int n, int x1, int y1, int x2, int y2) {
    std::vector<Point> queryPoints; //points in range
    for (int i = 0; i < points.size(); ++i) {  //iterate through each point
        if (points[i].x >= x1 && points[i].x <= x2 && points[i].y >= y1 && points[i].y <= y2) { //check if point is in range
            queryPoints.push_back(points[i]);   //add point to range
        }
    }
    return queryPoints; //return points in range
}

//draw range query
void drawRangeQuery(sf::RenderWindow& window, std::vector<Point> points, int n, int x1, int y1, int x2, int y2) {
    sf::VertexArray lines(sf::LinesStrip, points.size());  //lines for range query
    for (int i = 0; i < points.size(); ++i) {  //iterate through each point
        lines[i].position = sf::Vector2f(points[i].x * 800 / n, points[i].y * 800 / n);  //set position of line
        lines[i].color = sf::Color::Red;    //set color of line
    }
    window.draw(lines); //draw lines
}

int main() {
    int n = 128;  //number of points
    std::vector<Point> points = getPointsForCurve(n); //get points for curve
    sf::RenderWindow window(sf::VideoMode(800, 800), "Z-Order Curve");    //create window
    while (window.isOpen()) {   //main loop
        sf::Event event;    //event
        while (window.pollEvent(event)) {   //handle events
            if (event.type == sf::Event::Closed) { //check if window is closed
                window.close(); //close window
            }
        }
        window.clear(); //clear window
        drawCurve(window, points, n);   //draw curve
        //parameter for range query (x1, y1, x2, y2) (x1, y1) is top left corner, (x2, y2) is bottom right corner (0, 0) is top left corner of window
        drawRangeQuery(window, rangeQuery(points, n, 10, 10, 30, 30), n, 10, 10, 30, 30); //draw range query
        window.display();   //display window
    }
    return 0;
}

