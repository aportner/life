#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <regex>

// opengl stuff, only tested on apple...
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "Game.h"

using namespace std;

Game *game;

// this parses input from stdin to load coordinates
void loadCoordinates() {
    cout << "Enter coordinates in the form of (x,y)." << endl;
    
    // regex matching (x, y)
    regex rgx("^\\s*\\(\\s*([-+]?\\d+)\\s*\\,\\s*([-+]?\\d+)\\s*\\)\\s*$");
    
    smatch match;
    string input;
    
    while (true) {
        // read input
        getline(cin, input);
        
        if (regex_search(input, match, rgx)) {
            // if we match the regex, get the coords and add the cell
            char **buffer;
            
            string sX = match[1];
            string sY = match[2];
            
            int64_t x = strtoll(sX.c_str(), buffer, 10);
            int64_t y = strtoll(sY.c_str(), buffer, 10);
            
            cout << "Adding " << x << ", " << y << endl;
            
            game->getWorld()->addCell(x, y);
        } else {
            // give up if no coords
            break;
        }
    }
}

// recursive code to draw the current tree
void draw(CellTree *tree) {
    if (tree == 0)
        return;
    
    if (tree->isAlive) {
        // if alive, draw the current point and return since alive
        // cells are at the bottom of the tree
        typedef GLfloat point2[2];
        point2 p;
        p[0] = tree->x;
        p[1] = tree->y;
        
        glBegin(GL_POINTS);
        glVertex2fv(p);
        glEnd();
        
        return;
    }
    
    // otherwise iterate over the tree
    if (tree->hasChildren()) {
        for (int i = 0; i < CellTree::TREE_SIZE; ++i) {
            CellTree *child = tree->getChild(i);
            
            if (child != 0)
                draw(child);
        }
    }
}

// callback to display current state of the game
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw(game->getWorld()->getTree());
    
    glFlush();
}

// update loop to advance the game. this isn't frame-capped
// and could easily be optimized but for the sake of time
// i draw whenever there is an update call
void idle(void) {
    game->next();
    display();
}

// admittedly gl is not my strong suit, this is a code snippet
// which clears the buffer and draws cells as bright red
void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    game = new Game();
    
    loadCoordinates();
    
    cout << "Staring OpenGL" << endl;
    
    // another snippet to initialize OpenGL. looks like these calls
    // are deprecated in OSX 10.9 but I didn't want to spend too
    // much time digging into OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Life");
    glutDisplayFunc (display);
    glutIdleFunc(idle);
    myInit();
    glutMainLoop();
    
    return 0;
}

