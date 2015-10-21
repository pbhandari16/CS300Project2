/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * CSCI 300 Graphics Project 2
 *
 * Nan Jiang, Pratistha Bhandari, Xiangyu Li *
 *
 * main.cpp -
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>

static double rotate_x = -58.0;
static double rotate_y = 0;

float zoomFactor = 60;

// Initialize OpenGL graphics
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0); // clear the viewport to black
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0.0,0.0,0.0,0.0);
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    glEnable(GL_COLOR_MATERIAL);
    glClearStencil(0);
    glEnable(GL_STENCIL_TEST);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    glMatrixMode(GL_MODELVIEW);
}

void mydisplay(void)
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(zoomFactor, w / h, 0.1, 100);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glRotatef(rotate_x, 0.0, 0.0, 1.0 );
    glRotatef(rotate_y, 1.0, 0.0, 0.0);
    
    glFlush();
    glutSwapBuffers();
}

// reshape function
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-40.0, 40.0, -40.0 * (GLfloat) h / (GLfloat) w, 40.0 * (GLfloat) h / (GLfloat) w, -40.0, 40.0);
    else
        glOrtho(-40.0 * (GLfloat) w / (GLfloat) h, 40.0 * (GLfloat) w / (GLfloat) h, -40.0, 40.0, -40.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

// keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            mydisplay();
            break;
        case 'f':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            mydisplay();
            break;
        case 'i':
            zoomFactor-=3;
            glutPostRedisplay();
            break;
        case 'o':
            zoomFactor+=3;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

// arrow keys that are used to control the rotation of the object
void specialKeys( int key, int x, int y )
{
    if (key == GLUT_KEY_RIGHT)
        rotate_x -= 5.0;
    else if (key == GLUT_KEY_LEFT)
        rotate_x -= -5.0;
    else if (key == GLUT_KEY_UP)
        rotate_y += 5.0;
    else if (key == GLUT_KEY_DOWN)
        rotate_y -= 5.0;
    
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);           //set window properties
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 2");
    glutDisplayFunc(mydisplay);     //display callback
    glutSpecialFunc(specialKeys);
    init();                         //set OpenGL state
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();                 //enter event loop
}