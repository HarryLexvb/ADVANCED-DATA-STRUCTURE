//
// Created by HarryLex on 4/11/2022.
//

#include "hilbert.h"
#include <iostream>
#include <cmath>

/***** CONTENTS *****\
   Public methods
   Color and drawing
   Parsing
   OpenGL functions
\*******************/


//Part of the member function workaround (see the .h file for details)
Hilbert* Hilbert::curObj = 0; //current object

//Vars for changing the color
float color; //current color
bool up; //whether the color is increasing or decreasing

//Var for scene rotation
int deg = 0; //current rotation

/***** Public methods *****/

//Constructor, describes L-system
Hilbert::Hilbert(string start, string vars, string* rules, float ang, float side){ //constructor
    consts = "F+-&^\\/|[]`~$"; //Characters that we recognize as constants
    debug = false; //debug mode off by default

    startStr = start; //start string
    varsStr = vars; //variables
    rulesArr = rules; //rules
    angle = ang; //angle
    sideLen = side; //side length

    level = 0; //level 0 by default
    userShape = CUBE; //Default shape
}

//Enable drawing a coordinate system and printing the rotation angle
void Hilbert::enableDebug(bool enable){ //enable debug mode
    debug = enable; //set debug mode
}

//Allow user to specify the shape used in constructing the L-system
void Hilbert::setShape(int shape) {
    if(shape < 0 or shape > 2){ //invalid shape
        userShape = CUBE; //Default to cube
        cout << "Shape must be Hilbert.CUBE, Hilbert.PYRAMID, or Hilbert.CYLINDER" << endl; //error message
        cout << "Defaulting to cube" << endl; //error message
    }
    else{
        userShape = shape; //set shape
    }
}

//Public-facing draw function, calls private gl_main function
void Hilbert::draw(int argc, char** argv, int lvl){ //draw the curve
    level = lvl; //set level
    gl_main(argc, argv); //call gl_main
}

/***** Color and drawing *****/

//Draw a pyramid of the given height (height is equal to base length)
//When centered at the origin, it points along the positive y-axis
void Hilbert::drawPyra(float height){ //draw a pyramid
    //Vertices
    GLfloat vertexA[] = {-height/2, -height/2, -height/2};  //A
    GLfloat vertexB[] = {height/2, -height/2, -height/2};  //B
    GLfloat vertexC[] = {height/2, -height/2, height/2}; //C
    GLfloat vertexD[] = {-height/2, -height/2, height/2}; //D
    GLfloat vertexE[] = {0, height/2, 0}; //E

    //Base
    glBegin(GL_QUADS); //start drawing quads
    glNormal3f(0, -1, 0); //normal vector
    glVertex3fv(vertexA); //A
    glVertex3fv(vertexB); //B
    glVertex3fv(vertexC); //C
    glVertex3fv(vertexD); //D
    glEnd(); //end drawing quads

    //Sides
    glBegin(GL_TRIANGLES); //start drawing triangles
    glNormal3f(-1.414214, 1, 0); //normal vector
    glVertex3fv(vertexA); //A
    glVertex3fv(vertexD); //D
    glVertex3fv(vertexE);   //E
    glEnd(); //end drawing triangles

    glBegin(GL_TRIANGLES); //start drawing triangles
    glNormal3f(0, 1, 1.414214); //normal vector
    glVertex3fv(vertexD); //D
    glVertex3fv(vertexC); //C
    glVertex3fv(vertexE);  //E
    glEnd(); //end drawing triangles

    glBegin(GL_TRIANGLES); //start drawing triangles
    glNormal3f(1.414214, 1, 0); //normal vector
    glVertex3fv(vertexC); //C
    glVertex3fv(vertexB); //B
    glVertex3fv(vertexE); //E
    glEnd(); //end drawing triangles

    glBegin(GL_TRIANGLES); //start drawing triangles
    glNormal3f(0, 1, -1.414214); //normal vector
    glVertex3fv(vertexB); //B
    glVertex3fv(vertexA); //A
    glVertex3fv(vertexE); //E
    glEnd(); //end drawing triangles
}

//Draw a cylinder with diameter and height equal to len
//Sides are constructed with 10 faces
//Centered at the origin with the z-axis passing through the circular faces
void Hilbert::drawCyl(float len){ //draw a cylinder
    GLfloat bottomFace[3*10]; //bottom face
    GLfloat topFace[3*10]; //top face

    //This can probably be made more efficient...

    float convert = 3.14159/180; //Convert from degrees to radians

    //Initialize vertices
    for(int i = 0; i < 10; ++i){ //for each vertex    {
        float angle = 36*i*convert; //angle of vertex
        bottomFace[3*i] = topFace[3*i] = (len/2)*sin(angle); //x-coordinate
        bottomFace[3*i+1] = topFace[3*i+1] = (len/2)*cos(angle); //y-coordinate
        bottomFace[3*i+2] = -len/2; //z-coordinate
        topFace[3*i+2] = len/2; //z-coordinate
    }

    //Construct bottom face
    glBegin(GL_POLYGON); //start drawing polygon
    glNormal3f(0, 0, -1); //normal vector
    for(int i = 0; i < 10; ++i) //CCW winding
    {
        glVertex3f(bottomFace[3*i], bottomFace[3*i+1], bottomFace[3*i+2]); //vertex
    }
    glEnd(); //end drawing polygon

    //Construct top face
    glBegin(GL_POLYGON); //start drawing polygon
    glNormal3f(0, 0, 1); //normal vector
    for(int i = 9; i >= 0; --i) //CCW winding
    {
        glVertex3f(topFace[3*i], topFace[3*i+1], topFace[3*i+2]); //vertex
    }
    glEnd();

    //Construct sides
    float offset = 18*convert; //offset for vertices
    float dtheta = 36*convert; //change in angle
    glBegin(GL_QUADS); //start drawing quads
    for(int i = 0; i <= 8; ++i) { //for each quad
        glNormal3f(sin(offset + i*dtheta), cos(offset + i*dtheta), 0); //normal vector
        glVertex3f(topFace[3*i], topFace[3*i+1], topFace[3*i+2]); //vertex
        glVertex3f(topFace[3*i+3], topFace[3*i+4], topFace[3*i+5]); //vertex
        glVertex3f(bottomFace[3*i+3], bottomFace[3*i+4], bottomFace[3*i+5]); //vertex
        glVertex3f(bottomFace[3*i], bottomFace[3*i+1], bottomFace[3*i+2]); //vertex
    }

    //Add the last rectangle
    glNormal3f(sin(offset + 9*dtheta), cos(offset + 9*dtheta), 0); //normal vector
    glVertex3f(topFace[3*9], topFace[3*9+1], topFace[3*9+2]); //vertex
    glVertex3f(topFace[0], topFace[1], topFace[2]); //vertex
    glVertex3f(bottomFace[0], bottomFace[1], bottomFace[2]); //vertex
    glVertex3f(topFace[3*9], topFace[3*9+1], topFace[3*9+2]); //vertex
    glEnd();
}

//Draw a cube of the given side length using GLUT's built-in function
void Hilbert::drawCube(float height){ //draw a cube
    glutSolidCube(height); //draw a cube
}

//Draw a 6-sided green leaf in the xz plane with one tip at the origin
void Hilbert::drawLeaf(float len){ //draw a leaf
    glColor3f(0, 1, 0); //Full green
    glNormal3f(0, 1, 0); //normal vector
    glBegin(GL_POLYGON); //start drawing polygon
    glVertex3f(0, 0, 0); //vertex
    glVertex3f(1.732*0.5*len, 0, 0.5*len);
    glVertex3f((1.732*0.5 + 1)*len, 0, 0.5*len);
    glVertex3f((1.732 + 1)*len, 0, 0);
    glVertex3f((1.732*0.5 + 1)*len, 0, -0.5*len);
    glVertex3f(1.732*0.5*len, 0, -0.5*len);
    glEnd(); //end drawing polygon
    glColor3f(0.675, 0.451, 0.224); //Light brown
    //Ideally we would specify colors for different sections
}

//Draw a coordinate system with axes of the given length
void Hilbert::drawCoord(float len){ //draw a coordinate system
    glLineWidth(3); //Make the axes a bit more visible

    glBegin(GL_LINES); //start drawing lines
    glColor3f(1,0,0); //red
    glVertex3f(0,0,0); //x-axis
    glVertex3f(len,0,0); //x-axis

    glColor3f(0,1,0); //green
    glVertex3f(0,0,0); //y-axis
    glVertex3f(0,len,0); //y-axis

    glColor3f(0,0,1); //blue
    glVertex3f(0,0,0); //z-axis
    glVertex3f(0,0,len); //z-axis
    glEnd(); //end drawing lines

    glLineWidth(1); //Reset line width
}

//Fun method for changing the drawing color
void Hilbert::changeColor(){ //change the color
    if(color > 0.9) { //if the color is too bright
        up = false; //start going down
    }
    else if(color < 0.5) { //if the color is too dark
        up = true; //start going up
    }

    if(up) color += 0.05; // if going up, increase the color
    else color -= 0.05; //if going down, decrease the color

    glColor3f(0, color, 0); //set the color
}

/***** Parse *****/

//Recursively parse and draw the given string based on the rules above

/*
Note: a character can be both a variable and a constant.  When level is
not equal to zero, the char will be treated as a variable.  When level
is equal to zero it will be treated as a constant (provided that it
represents a valid constant)
*/

void Hilbert::parseStr(string str, int level){ //parse the string
    for(int i = 0; i < str.length(); ++i){ //for each character
        char c = str[i]; //get the character
        int index = varsStr.find_first_of(c); //get the index of the character in the string of variables

        if(level != 0 && index != string::npos) //if c is a variable
        {
            parseStr(rulesArr[index], level-1); //parse the rule for that variable
        }
        else if(consts.find_first_of(c) != string::npos) //if c is a constant
        {
            switch(c)
            {
                case '[': //push the current matrix
                    glPushMatrix(); break; //push the matrix
                case ']': //pop the current matrix
                    glPopMatrix(); break; //pop the matrix
                case '+': //rotate around the y-axis
                    glRotatef(angle,0,1,0); break; //rotate around the y-axis
                case '-': //rotate around the y-axis
                    glRotatef(-angle,0,1,0); break; //rotate around the y-axis
                case '&': //rotate around the x-axis
                    glRotatef(angle,1,0,0); break; //rotate around the x-axis
                case '^': //rotate around the x-axis
                    glRotatef(-angle,1,0,0); break; //rotate around the x-axis
                case '\\': //rotate around the z-axis
                    glRotatef(angle,0,0,1); break; //rotate around the z-axis
                case '/': //rotate around the z-axis
                    glRotatef(-angle,0,0,1); break;
                case '|': //rotate around the y-axis
                    glRotatef(180,0,1,0); break; //rotate around the y-axis
                case 'F': //draw a line
                    //changeColor();
                    glCallList(shapes[userShape]); break; //draw a line
                    break; //draw a line
                case '`': //draw a leaf
                    glColor3f(1, 0, 0); //Full red
                    break; //draw a leaf
                case '~': //draw a leaf
                    glColor3f(0.5, 0.5, 0.5); //Full gray
                    break; //draw a leaf
                case '$': //draw a leaf
                    glCallList(shapes[LEAF]); break; //draw a leaf
                    break; //draw a leaf
            }
        }
    }
}


/***** OpenGL functions *****/

//Set up lighting, enable settings
void Hilbert::init(){
    //Basic setup
    //black color is the background color of the window
    glClearColor(0.0, 0.0, 0.0, 0.0); //set the background color
    //glClearColor(0.5, 0.5, 0.5, 0.0); //set the background color
    glShadeModel(GL_FLAT); //Set the shading model
    glEnable(GL_DEPTH_TEST); //Enable depth testing
    //To draw leaves, culling must be disabled
    glEnable(GL_CULL_FACE); //Enable culling
    glCullFace(GL_BACK); //Cull the back faces

    //Lighting and color
    GLfloat light_pos[] = {5, 5, 5, 1}; //light position
    GLfloat light_diffuse[] = {0.4, 0.4, 0.4, 1}; //diffuse light
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1}; //ambient light
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos); //set the light position
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse); //set the diffuse light
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient); //set the ambient light
    glEnable(GL_LIGHTING); //enable lighting
    glEnable(GL_LIGHT1); //enable light 1

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); //set the color material
    glEnable(GL_COLOR_MATERIAL); //enable color material

    //Create display lists to (hopefully) speed up processing
    shapes[CUBE] = glGenLists(1); //create a display list
    glNewList(shapes[CUBE], GL_COMPILE); //start the display list
    glTranslatef(0, 0, sideLen); //translate to the top of the cube
    drawCube(sideLen); //draw the cube
    glTranslatef(0, 0, sideLen); //translate to the top of the cube
    drawCube(sideLen); //draw the cube
    glEndList(); //end the display list

    shapes[PYRAMID] = glGenLists(1); //create a display list
    glNewList(shapes[PYRAMID], GL_COMPILE); //start the display list
    glTranslatef(0, 0, sideLen); //translate to the top of the pyramid
    drawPyra(sideLen); //draw the pyramid
    glTranslatef(0, 0, sideLen); //translate to the top of the pyramid
    drawPyra(sideLen); //draw the pyramid
    glEndList(); //end the display list

    shapes[CYLINDER] = glGenLists(1); //create a display list
    glNewList(shapes[CYLINDER], GL_COMPILE); //start the display list
    glTranslatef(0, 0, sideLen); //translate to the top of the cylinder
    drawCyl(sideLen); //draw the cylinder
    glTranslatef(0, 0, sideLen); //translate to the top of the cylinder
    drawCyl(sideLen); //draw the cylinder
    glEndList(); //end the display list

    shapes[LEAF] = glGenLists(1); //create a display list
    glNewList(shapes[LEAF], GL_COMPILE); //start the display list
    drawLeaf(sideLen); //draw the leaf
    glEndList(); //end the display list
}

void Hilbert::display(){ //display the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color and depth buffers

    glLoadIdentity(); //reset the modelview matrix

    glPushMatrix(); //push the matrix

    gluLookAt(20, 30, -20, 0, 10, 0, -1, 2, 1); //Corner perspective

    if(debug) { //if debug mode is on
        drawCoord(sideLen*10); //draw the coordinate system
        cout << "Rotated by " << deg << " degrees" << endl; //print the rotation
    }

    //Draw a green circle as our base
    glColor3f(0, 0.8, 0); //Full green
    float convert = 3.14159/180; //convert degrees to radians
    glBegin(GL_POLYGON); //start drawing a polygon
    for(int i = 0; i < 360; i += 15){ //for each degree
        glVertex3f(-10*cos(i*convert), 0, 10*sin(i*convert)); //draw a vertex
    }
    glEnd(); //end drawing a polygon

    glRotatef(deg, 0, 1, 0); //Rotate scene

    //Set up color variables
    color = 0.4; //set the color to 0.4
    up = true; //set the color to go up

    //glColor3f(0.675, 0.451, 0.224); //Light brown
    glColor3f(0.5, 0.5, 0.5); //Full gray

    glRotatef(-90, 1, 0, 0); //Set pen to point upwards
    parseStr(startStr, level); //parse the string

    glPopMatrix(); //pop the matrix
    glutSwapBuffers(); //swap the buffers
}

//Handle window resizing
void Hilbert::reshape(int w, int h){ //reshape the window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport

    glMatrixMode(GL_PROJECTION); //set the projection matrix
    glLoadIdentity(); //reset the projection matrix
    gluPerspective(60, (GLfloat)w/h, 1, 80); //set the perspective

    glMatrixMode(GL_MODELVIEW); //set the modelview matrix
}

//Rotate scene with keyboard controls
void Hilbert::keyboard(unsigned char key, int x, int y){ //handle keyboard input
    switch(key){ //switch on the key pressed
        case 'a': //if a is pressed
            deg = (deg+5)%360; //rotate 5 degrees clockwise
            glutPostRedisplay(); //redisplay the scene
            break;  //break out of the switch
        case 'l': //if l is pressed
            deg = (deg-5)%360; //rotate 5 degrees counter-clockwise
            glutPostRedisplay(); //redisplay the scene
            break; //break out of the switch
        case 'r': //if r is pressed
            deg = 0; //reset the rotation
            glutPostRedisplay(); //redisplay the scene
            break; //break out of the switch
    }
}

//Register functions and run main loop
void Hilbert::gl_main(int argc, char **argv){ //run the main loop
    glutInit(&argc, argv); //initialize glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //set the display mode
    glutInitWindowSize(800, 800); //1500x600
    glutInitWindowPosition(100, 100); //set the window position
    glutCreateWindow("3D L-systems!"); //create the window

    init(); //initialize the scene

    curObj = this; //set the current object to this
    glutDisplayFunc(displayWrapper); //set the display function
    glutReshapeFunc(reshapeWrapper); //set the reshape function
    glutKeyboardFunc(keyboardWrapper); //set the keyboard function

    glutMainLoop(); //run the main loop
}
