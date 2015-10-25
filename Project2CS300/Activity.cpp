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

static double rotate_x = 0.0;
static double rotate_y = 0.0;
static double rotate_z = 0.0;

float zoomFactor = 60;

GLUquadricObj *obj;

// Initialize OpenGL graphics
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0); // clear the viewport to black
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING); //Enables openGl lighting
    glEnable(GL_LIGHT0);
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

void minionBody()
{
    obj = gluNewQuadric(); //creates a new quadric object
    
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
   	gluCylinder(obj,8.0,8.0,12,50,50); //middle body
    glPopMatrix();
    
    glPushMatrix();
    glutSolidSphere(8.0,20,20); //head sphere
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,-12,0.0);
    glutSolidSphere(8.0,20,20); //bottom sphere
    glPopMatrix();
    
    //right goggles
    glPushMatrix();
    glColor3f(0.90,0.91,0.98);
    glTranslatef(3.0,0.0,6.0);
    for (float i = 2.0; i < 3; i = i + 0.05)
        gluCylinder(obj,i,i,2.5,50,50);
    glPopMatrix();
    
    //left goggles
    glPushMatrix();
    glColor3f(0.90,0.91,0.98);
    glTranslatef(-3.0,0.0,6.0);
    for (float i = 2.0; i < 3; i = i + 0.05)
        gluCylinder(obj,i,i,2.5,50,50);
    glPopMatrix();
    
    //right eye
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(2.6,0.0,6.0);
    glutSolidSphere(2.5,20,20); //white eyeball
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.35,0.16,0.14);
    glTranslatef(2.8,0.0,8.0);
    glutSolidSphere(0.9,20,20); //brown part
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(2.8,0.0,8.4);
    glutSolidSphere(0.6,20,20); //tiny black part
    glPopMatrix();
    
    //left eyeball
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-2.6,0.0,6.0);
    glutSolidSphere(2.5,20,20); //white eyeball
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.35,0.16,0.14);
    glTranslatef(-2.8,0.0,8.0);
    glutSolidSphere(0.9,20,20); //brown part
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-2.8,0.0,8.4);
    glutSolidSphere(0.6,20,20); //tiny black part
    glPopMatrix();
    
    //smile
    glPushMatrix();
    //for (float i = 0.0; i < 10; i = i + 0.1)
    glPointSize(2.0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(3.0,-5.0,7.5);
    glVertex3f(2.8,-5.1,7.5);
    
    glVertex3f(2.6,-5.2,7.6);
    
    glVertex3f(2.4,-5.3,7.7);
    glVertex3f(2.2,-5.4,7.7);
    
    glVertex3f(2.0,-5.5,7.8);
    glVertex3f(1.8,-5.5,7.8);
    
    glVertex3f(1.6,-5.5,7.9);
    glVertex3f(1.4,-5.5,7.9);
    
    glVertex3f(1.2,-5.5,8.0);
    glVertex3f(1.0,-5.5,8.0);
    glVertex3f(0.8,-5.5,8.0);
    glVertex3f(0.6,-5.5,8.0);
    glVertex3f(0.4,-5.5,8.0);
    glVertex3f(0.2,-5.5,8.0);
    glVertex3f(0.0,-5.5,8.0);
    glVertex3f(-0.2,-5.5,8.0);
    glVertex3f(-0.4,-5.5,8.0);
    glVertex3f(-0.6,-5.5,8.0);
    glVertex3f(-0.8,-5.5,8.0);
    glVertex3f(-1.0,-5.5,8.0);
    glVertex3f(-1.2,-5.5,8.0);
    
    glVertex3f(-1.4,-5.5,7.9);
    glVertex3f(-1.6,-5.5,7.9);
    
    glVertex3f(-1.8,-5.5,7.8);
    glVertex3f(-2.0,-5.5,7.8);
    
    glVertex3f(-2.2,-5.4,7.7);
    glVertex3f(-2.4,-5.3,7.7);
    
    glVertex3f(-2.6,-5.2,7.6);
    
    glVertex3f(-2.8,-5.1,7.5);
    glVertex3f(-3.0,-5.0,7.5);
    glEnd();
    glPopMatrix();
    
    //clothing
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-1.2,-6.5,8.0);
    
    glEnd();
    glPopMatrix();
}

void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(zoomFactor, w / h, 0.1, 100);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glRotatef(rotate_x, 0.0, 0.0, 1.0 );
    glRotatef(rotate_y, 1.0, 0.0, 0.0);
    
    glColor3f(0.9,0.5,0.0);
    minionBody();
    
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