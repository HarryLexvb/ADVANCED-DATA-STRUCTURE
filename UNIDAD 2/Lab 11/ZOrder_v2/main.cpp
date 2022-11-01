/*Author: Harold Alejandro Villanueva Borda
 * Date: 2022/11/01
 * Department: Computer Science
 * Curse: Advance Data Structures
 * Institution: San Pablo Catholic University of Arequipa
*/

#include <SFML/Graphics.hpp>

// 2D points with integer coordinates 0 ≤ x ≤ p1, 0 ≤ y ≤ p2
template <class T>
struct Point {
    T x, y;
    Point(T x, T y) : x(x), y(y) {}
};

int zOrder(Point<int> p) {
    int x = p.x;
    int y = p.y;
    int z = 0;
    for (int i = 0; i < 3; i++) { // 3 bits
        z |= (x & 1) << (2 * i + 1); // here we use 2*i+1 instead of 2*i
        z |= (y & 1) << (2 * i);   // here we use 2*i instead of 2*i+1
        x >>= 1; // x = x / 2
        y >>= 1; // y = y / 2
    }
    return z;
}

template <class T>
void printZOrder(T p1, T p2) {
    std::vector<Point<T>> points;
    for (int y = 0; y <= p1; ++y) { // 0 ≤ x ≤ p1
        for (int x = 0; x <= p2; ++x) { // 0 ≤ y ≤ p2
            Point p = {y, x};
            points.push_back(p);
        }
    }
    std::sort(points.begin(), points.end(), [](Point<T> p1, Point<T> p2) {  // this function is used to sort the points in the vector
        return zOrder(p1) < zOrder(p2); // sort by z order curve value
    });

    /*
    for (int y = 0; y <= p1; y++) { // 0 ≤ y ≤ p1
        //std::cout << " y = " << y << "    ";
        for (int x = 0; x <= p2; x++) { // 0 ≤ x ≤ p2
            Point p = {y, x};
            std::cout << zOrder(p) << "\t"; // print z order curve value
        }
        std::cout << std::endl;
    }
    */

    //draw the points and connect them with lines
    sf::RenderWindow window(sf::VideoMode(800, 800), "Z order curve");
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color::Red);
    sf::VertexArray lines(sf::LinesStrip, points.size());
    for (int i = 0; i < points.size(); i++) {
        shape.setPosition(points[i].y * 800 / p1, points[i].x * 800 / p2);
        window.draw(shape);
        lines[i].position = sf::Vector2f(points[i].y * 800 / p1, points[i].x * 800 / p2);
    }
    window.draw(lines);
    window.display();
    sf::sleep(sf::seconds(5));

}

template <class T>
void queryZOrder(T x1, T x2, T y1, T y2, int n) {
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
    /*
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            Point p = {y, x};
            std::cout << zOrder(p) << "\t";
        }
        std::cout << std::endl;
    }
    */

    //draw the points and connect them with lines
    sf::RenderWindow window(sf::VideoMode(800, 800), "Z order curve");
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color::Red);
    sf::VertexArray lines(sf::LinesStrip, (x2 - x1 + 1) * (y2 - y1 + 1));
    int i = 0;
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            Point p = {y, x};
            shape.setPosition(p.y * 800 / n, p.x * 800 / n);
            window.draw(shape);
            lines[i].position = sf::Vector2f(p.y * 800 / n, p.x * 800 / n);
            i++;
        }
    }
    window.draw(lines);
    window.display();
    sf::sleep(sf::seconds(5));
}

int main() {
    int n=7;
    //printZOrder(n, n);
    printZOrder(n, n);
    queryZOrder(2,3,2,6, n);
    //queryZOrder(0,2,0,1, n);
    return 0;
}