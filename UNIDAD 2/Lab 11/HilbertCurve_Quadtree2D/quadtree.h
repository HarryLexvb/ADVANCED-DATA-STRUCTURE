//
// Created HarryLex on 4/11/2022.
//

#ifndef ZORDECURVE3D_QUADTREE_H
#define ZORDECURVE3D_QUADTREE_H


#include <iostream>
#include <vector>
#include "Point.h"

/*
Input: Points, K // where Points are the coordinates of points in the map, and K is the threshold that uses to divide the quadtree
Output: Quad Tree structure
Procedure:
    1- Initialize root that holds all points in one node
        Root = Node (Points)
    2- Call recursive_subdivide(root, K)
    3- Call Nodes = find_children(root)
    4- Representing quarters and nodes on the map.
*/

class Node {
public:
    std::vector<Point> points;
    Node *NW, *NE, *SW, *SE;
    Node(std::vector<Point> points) {
        this->points = points;
        NW = NE = SW = SE = nullptr;
    }
};

class QuadTree {
public:
    Node *root;
    QuadTree(std::vector<Point> points) {
        root = new Node(points);
    }
    void recursive_subdivide(Node *node, int K){
        if (node->points.size() <= K) return;
        std::vector<Point> NW_points, NE_points, SW_points, SE_points;
        for (Point p : node->points) {
            if (p.x < 0 && p.y > 0) NW_points.push_back(p);
            else if (p.x > 0 && p.y > 0) NE_points.push_back(p);
            else if (p.x < 0 && p.y < 0) SW_points.push_back(p);
            else if (p.x > 0 && p.y < 0) SE_points.push_back(p);
        }
        node->NW = new Node(NW_points);
        node->NE = new Node(NE_points);
        node->SW = new Node(SW_points);
        node->SE = new Node(SE_points);
        recursive_subdivide(node->NW, K);
        recursive_subdivide(node->NE, K);
        recursive_subdivide(node->SW, K);
        recursive_subdivide(node->SE, K);
    }
    std::vector<Node*> find_children(Node *node){
        std::vector<Node*> children;
        if (node->NW == nullptr) {
            children.push_back(node);
            return children;
        }
        std::vector<Node*> NW_children = find_children(node->NW);
        std::vector<Node*> NE_children = find_children(node->NE);
        std::vector<Node*> SW_children = find_children(node->SW);
        std::vector<Node*> SE_children = find_children(node->SE);
        children.insert(children.end(), NW_children.begin(), NW_children.end());
        children.insert(children.end(), NE_children.begin(), NE_children.end());
        children.insert(children.end(), SW_children.begin(), SW_children.end());
        children.insert(children.end(), SE_children.begin(), SE_children.end());
        return children;
    }
};

#endif //ZORDECURVE3D_QUADTREE_H
