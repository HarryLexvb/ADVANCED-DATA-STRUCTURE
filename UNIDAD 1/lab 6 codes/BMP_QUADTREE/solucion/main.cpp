#include <iostream>
#include "BMP.h"
#include <cmath>
#include "BMP.h"

bool operator== (const RGBA_pixel& a, const RGBA_pixel& b){ // returns true if the two pixels are equal
    return (a.Red == b.Red and a.Green == b.Green and a.Blue == b.Blue); // and a.Alpha == b.Alpha);
}
bool operator!= (const RGBA_pixel& a, const RGBA_pixel& b){
    return !(a==b); // returns true if the two pixels are not equal
}

class QuadTree { // a quadtree is a tree with four children
private:
    static const int maxDepth = 8; // the maximum depth of the tree
    static const int minCoverage = 0; // the minimum coverage of a node
    static const int maxCoverage = 80; // the maximum coverage of a node
    BMP* data; // the image data
    int sizeX, sizeY, offsetX, offsetY, depth; // the size of the image, the offset of the image, and the depth of the node
    RGBA_pixel emptySpace; // the color of empty space
    RGBA_pixel black; // the color of black
    int coverage; // the coverage of the node
public:
    QuadTree *nw, *ne, *sw, *se; //4 nodes (northwest, northeast, southwest, southeast)
    QuadTree(BMP* data, int sizeX, int sizeY); // constructor for the root node (the entire image)
    QuadTree (BMP* data, int sizeX, int sizeY, int offsetX, int offsetY, int depth); // constructor for a child node (a subimage)
    QuadTree* split(); //initializes 4 children in a node
    QuadTree* rSplit(); //recursively splits the tree
    bool checkCollidable(); // checks if the node is collidable
    void drawBoundary(); // draws the boundary of the node
    void drawBoundaries(); // recursively draws the boundaries of the tree
    int getCoverage(); // returns the coverage of the node
};

QuadTree::QuadTree (BMP* data, int sizeX, int sizeY){ // constructor for the root node (the entire image)
    this->sizeX = sizeX; // set the size of the image
    this->sizeY = sizeY; // set the size of the image
    this->data = data; // set the image data
    offsetX = offsetY = depth = 0; // set the offset of the image and the depth of the node
    black.Red = 0; black.Green = 0; black.Blue = 0; black.Alpha = 0; // set the color of black
    emptySpace.Red = 255; emptySpace.Blue = 255; emptySpace.Green=255; emptySpace.Alpha = 0; // set the color of empty space
    coverage = getCoverage(); // set the coverage of the node
    nw = sw = ne = se = nullptr; // set the children to NULL
//	printf ("%d %d\n", sizeX, sizeY);
}
QuadTree::QuadTree (BMP* data, int offsetX, int offsetY, int sizeX, int sizeY, int depth){ // constructor for a child node (a subimage)
    this->sizeX = sizeX; // set the size of the image
    this->sizeY = sizeY;
    this->data = data; // set the image data
    this->offsetX = offsetX; // set the offset of the image
    this->offsetY = offsetY;
    this->depth = depth; // set the depth of the node
    black.Red = 0; black.Green = 0; black.Blue = 0; black.Alpha = 0; // set the color of black
    emptySpace.Red = 255; emptySpace.Blue = 255; emptySpace.Green=255; emptySpace.Alpha = 0; // set the color of empty space
    coverage = getCoverage(); // set the coverage of the node
    nw = sw = ne = se = nullptr; // set the children to NULL
}
QuadTree* QuadTree::split(){ // initializes 4 children in a node
    // northwest child
    nw = new QuadTree (data, offsetX, offsetY, int (floor (sizeX/2.0)), int(floor (sizeY/2.0)), depth+1);
    // northeast child
    ne = new QuadTree (data, offsetX + int(floor(sizeX/2.0)), offsetY, int(ceil(sizeX/2.0)), int(floor(sizeY/2.0)),depth+1);
    // southwest child
    sw = new QuadTree (data, offsetX, offsetY + int(floor(sizeY/2.0)), int(floor(sizeX/2.0)), int(ceil(sizeY/2.0)), depth +1);
    // southeast child
    se = new QuadTree (data, offsetX + int(floor(sizeX/2.0)), offsetY + int(floor(sizeY/2.0)), int(ceil(sizeX/2.0)), int(ceil(sizeY/2.0)), depth+1);
    return this; // return the node
}
bool QuadTree::checkCollidable(){ // checks if the node is collidable
    if (coverage >= minCoverage) return 1; // if the coverage is greater than the minimum coverage, the node is collidable
    return 0; // otherwise, it is not
}
QuadTree* QuadTree::rSplit(){
    if (coverage > 0) std::cout << coverage << std::endl; // print the coverage of the node
    if (depth < maxDepth and maxCoverage >= coverage and coverage >= minCoverage) { // if the node is not at the maximum depth and the coverage is within the range
        split(); // split the node
        nw->rSplit(); // recursively split the northwest child
        ne->rSplit();
        sw->rSplit();
        se->rSplit();
    }
    return this; // return the node
}
void QuadTree::drawBoundary(){ // draws the boundary of the node
    //draw horizontal lines
    for (int x = 0; x < sizeX; ++x){ // for each pixel in the horizontal line
        data->SetPixel (x+offsetX, offsetY+sizeY, black); //bottom
        data->SetPixel (x+offsetX, offsetY, black); //top
    }
    //draw vertical lines
    for (int y = 0; y < sizeY; ++y){ // for each pixel in the vertical line
        data->SetPixel (offsetX+sizeX, y+offsetY, black); // right
        data->SetPixel (offsetX, y+offsetY, black); // left
    }
}
void QuadTree::drawBoundaries(){
    if (coverage > minCoverage) drawBoundary(); // if the coverage is greater than the minimum coverage, draw the boundary
    if (nw != nullptr) nw -> drawBoundaries(); // recursively draw the boundaries of the children
    if (sw != nullptr) sw -> drawBoundaries();
    if (ne != nullptr) ne -> drawBoundaries();
    if (se != nullptr) se -> drawBoundaries();
}
int QuadTree::getCoverage() { // returns the coverage of the node
    int total = 0; // the total number of pixels in the node
    for (int x = 0; x < sizeX; ++x){ // for each pixel in the node
        for (int y = 0; y < sizeY; ++y){ // for each pixel in the node
            //printf ("X: %d Y: %d\n", x, y);
            if (data->GetPixel(x+offsetX, y+offsetY) != emptySpace) ++total; // if the pixel is not empty space, increment the total
        }
    }
    return (int)(((float)total*100)/(sizeX*sizeY)); // return the coverage of the node

}

int main(){
    BMP image;
    image.ReadFromFile ((char*)R"(C:\Users\win 10\Documents\CLION\solucion\image.bmp)");
    //image.ReadFromFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\megaman.bmp)");
    //image.ReadFromFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\Nack Sprites.bmp)");
    //image.ReadFromFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\robot.bmp)");
    //image.ReadFromFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\sample.bmp)");
    QuadTree tree (&image, image.TellWidth()-1, image.TellHeight()-1);
    tree.rSplit();
    tree.drawBoundaries();
    image.WriteToFile ((char*)R"(C:\Users\win 10\Documents\CLION\solucion\image_output.bmp)");
    //image.WriteToFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\megaman_output.bmp)");
    //image.WriteToFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\Nack Sprites_output.bmp)");
    //image.WriteToFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\Robot_output.bmp)");
    //image.WriteToFile ((char*)R"(C:\Users\win 10\Documents\CLION\BMP_QUADTREE\sample_output.bmp)");
}
