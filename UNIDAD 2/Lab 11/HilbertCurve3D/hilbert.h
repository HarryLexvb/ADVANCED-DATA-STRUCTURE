//
// Created by HarryLex on 4/11/2022.
//

#ifndef HILBERTCURVE3D_HILBERT_H
#define HILBERTCURVE3D_HILBERT_H


#include <GL/glut.h>
#include <string>
using namespace std;

class Hilbert{ //class for drawing Hilbert curves
private:
    string consts; //constants
    bool debug; //debug mode

    //L-system data
    float angle; //angle to turn
    float sideLen; //length of each side of the cube (or other shape)
    int level; //level of the curve
    string startStr; //start string for L-system
    string varsStr; //variables
    string* rulesArr; //rules for each variable (A, B, C, D) in order of appearance

    //Display lists
    GLuint shapes[4]; //0=cube, 1=pyra, 2=cyl, 3=leaf (private)
    static const int LEAF = 3; //index of leaf display list (public)
    int userShape; //user-defined shape (private)

    //Color and drawing
    void drawPyra(float height); //draw a pyramid
    void drawCube(float height); //draw a cube
    void drawCyl(float height); //draw a cylinder
    void drawLeaf(float height); //draw a leaf
    void drawCoord(float len); //draw a coordinate axis
    void changeColor(); //change the color of the shape

    //Parse
    void parseStr(string str, int level); //parse the string

    //OpenGL functions
    void init(); //initialize OpenGL
    void display(); //display function
    void reshape(int w, int h); //reshape function
    void keyboard(unsigned char key, int x, int y); //keyboard function
    void gl_main(int argc, char **argv); //main function

    //Workaround for issue with pointer to member functions
    static Hilbert* curObj; //current object

    static void displayWrapper() {  //display function wrapper
        curObj->display();  //display function wrapper
    }

    static void reshapeWrapper(int w, int h) { //reshape function wrapper
        curObj->reshape(w, h); //reshape function wrapper
    }

    static void keyboardWrapper(unsigned char key, int x, int y) { //keyboard function wrapper    {
        curObj->keyboard(key, x, y); //keyboard function wrapper
    }

public:
    //Constants to choose the drawing shape
    static const int CUBE = 0; //cube
    static const int PYRAMID = 1; //pyramid
    static const int CYLINDER = 2; //cylinder

    Hilbert(string start, string vars, string* rules, float ang, float side); //constructor
    void enableDebug(bool enable); //enable debug mode
    void setShape(int shape); //set the shape to draw
    void draw(int argc, char** argv, int lvl); //draw the curve
};

#endif //HILBERTCURVE3D_HILBERT_H
