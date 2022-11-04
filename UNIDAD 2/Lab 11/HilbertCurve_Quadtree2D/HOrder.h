//
// Created by HarryLexon 4/11/2022.
//

#ifndef HILBERTCURVE_QUADTREE2D_HORDER_H
#define HILBERTCURVE_QUADTREE2D_HORDER_H

class HOrder {
public:
    std::vector<Point> points;
    int K;
    HOrder(std::vector<Point> points, int K) {
        this->points = points;
        this->K = K;
    }

    int HilbertDistanceFromCoordinates(int x, int y, int i) {
        int d = 0;
        for (int s = i / 2; s > 0; s /= 2) {
            bool rx = (x & s) > 0;
            bool ry = (y & s) > 0;
            d += s * s * ((3 * rx) ^ ry);
            if (!ry) {
                if (rx) {
                    x = s - 1 - x;
                    y = s - 1 - y;
                }
                // Swap x and y
                int t = x;
                x = y;
                y = t;
            }
        }
        return d;
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
                    for (Point point : node->points) {
                        int code = HilbertDistanceFromCoordinates(point.x, point.y, 32);
                        sequence.push_back(code);
                    }
                    if (node->NW != nullptr) {
                        new_children.push_back(node->NW);
                        new_children.push_back(node->NE);
                        new_children.push_back(node->SW);
                        new_children.push_back(node->SE);
                    }
                }
                children = new_children;
            } else {
                break;
            }
        }
        return sequence;
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

    //print matrix using sfml
    void print_matrix_sfml(std::vector<int> sequence, int n) {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Quadtree");
        sf::RectangleShape rectangle(sf::Vector2f(800 / n, 800 / n));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1);
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sequence[i * n + j];
            }
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    rectangle.setPosition(i * 800 / n, j * 800 / n);
                    rectangle.setFillColor(sf::Color(matrix[i][j], matrix[i][j], matrix[i][j]));
                    window.draw(rectangle);
                }
            }
            window.display();
        }
    }

    //print number of points in each node using sfml
    void print_points(std::vector<int> sequence, int n) {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Quadtree");
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\win 10\\Documents\\CLION\\ZOrdeCurve3D\\ALIEN5.TTF")) {
            std::cout << "Error loading font" << std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sequence[i * n + j];
            }
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    text.setString(std::to_string(matrix[i][j]));
                    text.setPosition(sf::Vector2f(50 + 50 * j, 50 + 50 * i));
                    window.draw(text);
                }
            }
            window.display();
        }
    }

    //print number of points and connect each node using sfml
    void print_points_and_connect(std::vector<int> sequence, int n) {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Quadtree");
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\win 10\\Documents\\CLION\\ZOrdeCurve3D\\ALIEN5.TTF")) {
            std::cout << "Error loading font" << std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sequence[i * n + j];
            }
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    text.setString(std::to_string(matrix[i][j]));
                    text.setPosition(sf::Vector2f(50 + 50 * j, 50 + 50 * i));
                    window.draw(text);
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i < n - 1) {
                        sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(50 + 50 * j, 50 + 50 * i)),
                                sf::Vertex(sf::Vector2f(50 + 50 * j, 50 + 50 * (i + 1)))
                        };
                        window.draw(line, 2, sf::Lines);
                    }
                    if (j < n - 1) {
                        sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(50 + 50 * j, 50 + 50 * i)),
                                sf::Vertex(sf::Vector2f(50 + 50 * (j + 1), 50 + 50 * i))};
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }
            window.display();
        }
    }

};


#endif //HILBERTCURVE_QUADTREE2D_HORDER_H
