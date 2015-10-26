/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * CSCI 300 Graphics Project 2
 *
 * Nan Jiang, Pratistha Bhandari, Xiangyu Li *
 *
 * Activity.cpp - An implementation file using OpenGL to model a Minion.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cmath>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>
/***** Global variables *****/
GLint win_width = 800;      // window dimensions
GLint win_height = 800;

GLint angle = 60, nearP = 1, farP = 1000;

GLUquadricObj *obj;         // Pointer for quadric objects.

// Rotation of the whole object
static GLfloat rotate_x = 0.0, rotate_y = 0.0, rotate_z = 0.0;

// Rotation for arms
static GLfloat armVert = 0.0, strechX = 0.0, strechY = 0.0;
bool maxWave = false, handUp = false;

// Mouse function related variables
static int moving = 0, startx, starty;

float runningAngle = 0;
bool running = false;
int flag = 1;
float speed = 2;
float dist = 0;

using namespace std;
// Initialize OpenGL graphics
void init(void)
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1.0, nearP, farP);
    gluLookAt(0.0, 0.0, 350.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat gray[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = {1.0, 1.0, 1.0, 0.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);            // turn on the depth buffer
}


void drawCuboid(float x, float y, float z)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.5*x, 0.5*y, 0.5*z);
    glVertex3f(-0.5*x, -0.5*y, 0.5*z);
    glVertex3f(0.5*x, -0.5*y, 0.5*z);
    glVertex3f(0.5*x, 0.5*y, 0.5*z);
    
    glVertex3f(-0.5*x, 0.5*y, -0.5*z);
    glVertex3f(-0.5*x, -0.5*y, -0.5*z);
    glVertex3f(0.5*x, -0.5*y, -0.5*z);
    glVertex3f(0.5*x, 0.5*y, -0.5*z);
    
    glVertex3f(0.5*x, -0.5*y, 0.5*z);
    glVertex3f(0.5*x, -0.5*y, -0.5*z);
    glVertex3f(0.5*x, 0.5*y, -0.5*z);
    glVertex3f(0.5*x, 0.5*y, 0.5*z);
    
    glVertex3f(-0.5*x, -0.5*y, 0.5*z);
    glVertex3f(-0.5*x, -0.5*y, -0.5*z);
    glVertex3f(-0.5*x, 0.5*y, -0.5*z);
    glVertex3f(-0.5*x, 0.5*y, 0.5*z);
    
    glVertex3f(-0.5*x, 0.5*y, 0.5*z);
    glVertex3f(-0.5*x, 0.5*y, -0.5*z);
    glVertex3f(0.5*x, 0.5*y, -0.5*z);
    glVertex3f(0.5*x, 0.5*y, 0.5*z);
    
    glVertex3f(-0.5*x, -0.5*y, 0.5*z);
    glVertex3f(-0.5*x, -0.5*y, -0.5*z);
    glVertex3f(0.5*x, -0.5*y, -0.5*z);
    glVertex3f(0.5*x, -0.5*y, 0.5*z);
    glEnd();
    glPopMatrix();
}

void drawShoeTip()
{
    //glPushMatrix();
    int density = 250;
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    for (int i = -density; i < density; i++)
    {
        double buf = i * (1.5/density);
        double z = -buf*buf + 2.25;
        for (int j = 0; j< density; j++)
        {
            double x = j * (buf/density);
            double y = sqrt(buf*buf - x*x);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
    //glPopMatrix();
}

void drawShoeBody(float l, float w)
{
    //glPushMatrix();
    glTranslatef(0, 0, -0.5*l);
    int density = 250;
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    for (int i = -density; i < density; i++)
    {
        for (int j = -density; j< density; j++)
        {
            double x = i * (w/density);
            double z = j * (0.5*l/density);
            double y = sqrt(2.25 - x*x);
            glVertex3f(x, y, z);
        }
    }
    glEnd();
    //glPopMatrix();
}
void minionHair()
{
    //first hair
    glPushMatrix();
    
    double x = 1;
    double y = sqrt(64 - 2);
    double z = 1;
    glTranslatef(x, y, z);
    int density = 100;
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= density; i++)
    {
        x = (30/density)*i;
        y = -(x-0.2)*(x-0.2) + 0.04;
        glVertex3f(x, y, 1);
    }
    glEnd();
    glPopMatrix();
}

void minionFeet()
{
    
    glPushMatrix();
    glRotatef(runningAngle, 1.0, 0.0, 0.0);
    //Right leg
    glPushMatrix();
    glTranslatef(3.0, -16.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 3, 2, 6, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9, 0.5, 0.0);
    glTranslatef(3, -20, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 1.5, 1.4, 3.2, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(3, -23.3, 0.0);
    //drawCuboid(3, 2, 3);
    glTranslatef(0, -1, 1.5);
    drawShoeTip();
    drawShoeBody(3, 2);
    glPopMatrix();
    glPopMatrix();
    //Left leg
    glPushMatrix();
    glRotatef(-runningAngle, 1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-3.0, -16.0, 0.0);
    glColor3f(0.0,0.0,0.61);
    
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 3, 2, 6, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9, 0.5, 0.0);
    glTranslatef(-3, -20, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 1.5, 1.4, 3.2, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3, -23.3, 0.0);
    //drawCuboid(3, 2, 3);
    glTranslatef(0, -1, 1.5);
    drawShoeTip();
    drawShoeBody(3, 2);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(3, -23.3, 0.0);
    //drawCuboid(3, 2, 3);
    glTranslatef(0, -1, 1.5);
    drawShoeTip();
    drawShoeBody(3, 2);
    glPopMatrix();
    
    
}
void minionBody()
{
    
    glPushMatrix();
    glColor3f(0.9,0.5,0.0);
    glRotatef(90.0,1.0,0.0,0.0);
    gluCylinder(obj,8.0,8.0,12,50,50); //middle body
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.9,0.5,0.0);
    glutSolidSphere(8.0,20,20); //head sphere
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0,0.0,0.61);
    glTranslatef(0.0,-12,0.0);
    glutSolidSphere(8.0,20,20); //bottom sphere
    glPopMatrix();
    
    //goggles strap
    glPushMatrix();
    glColor3f(0.36,0.25,0.20);
    glRotatef(90,1.0,0.0,0.0);
    glutSolidTorus (1.0,7.1,30,120);
    glPopMatrix();
    
    //right goggles
    glPushMatrix();
    glColor3f(0.90,0.91,0.98);
    glTranslatef(3.0,0.0,6.0);
    for (float i = 2.0; i < 3; i = i + 0.001)
        gluCylinder(obj,i,i,2.5,50,50);
    glPopMatrix();
    
    //left goggles
    glPushMatrix();
    glColor3f(0.90,0.91,0.98);
    glTranslatef(-3.0,0.0,6.0);
    for (float i = 2.0; i < 3; i = i + 0.001)
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
    
    /************************************************
     ADD SMILE HERE! :D :D :D
     ************************************************/
    //smile
    glPushMatrix();
    glTranslatef(0.0, -5.5, 0.0);
    glPointSize(2.0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; i++)
    {
        double x = i*0.003;
        double y = 0.1*x*x;
        double z = sqrt(64 - x*x);
        glVertex3f(x, y, z);
        glVertex3f(-x, y, z);
    }
    glEnd();
    glPopMatrix();
    //clothing
    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    
    //middle part clothing
    glBegin(GL_POLYGON);
    glVertex3f(-1.2,-7.5,8.0);
    glVertex3f(-1.2,-12.0,8.0);
    glVertex3f(1.2,-12.0,8.0);
    glVertex3f(1.2,-7.5,8.0);
    glEnd();
    
    //grey patch
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(1.2,-8.5,8.1);
    glVertex3f(-1.2,-8.5,8.1);
    glVertex3f(-1.2,-10.5,8.1);
    glVertex3f(1.2,-10.5,8.1);
    glEnd();
    
    //triangle
    glColor3f(0.0,0.0,1.0);
    
    glColor3f(0.0,0.0,1.0);
    //left side clothing
    glBegin(GL_POLYGON);
    glVertex3f(-1.6,-7.5,7.9);
    glVertex3f(-1.6,-12.1,7.9);
    glVertex3f(-1.2,-12.1,7.9);
    glVertex3f(-1.2,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-2.0,-7.5,7.8);
    glVertex3f(-2.0,-12.1,7.8);
    glVertex3f(-1.6,-12.1,7.9);
    glVertex3f(-1.6,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-2.4,-7.5,7.7);
    glVertex3f(-2.4,-12.1,7.7);
    glVertex3f(-2.0,-12.1,7.8);
    glVertex3f(-2.0,-7.5,7.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-3.0,-7.5,7.6);
    glVertex3f(-3.0,-12.1,7.6);
    glVertex3f(-2.4,-12.1,7.7);
    glVertex3f(-2.4,-7.5,7.7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-4.0,-7.5,7.2);
    glVertex3f(-4.0,-12.1,7.2);
    glVertex3f(-3.0,-12.1,7.5);
    glVertex3f(-3.0,-7.5,7.5);
    glEnd();
    
    //right side clothing
    glBegin(GL_POLYGON);
    glVertex3f(1.6,-7.5,7.9);
    glVertex3f(1.6,-12.1,7.9);
    glVertex3f(1.2,-12.1,7.9);
    glVertex3f(1.2,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.0,-7.5,7.8);
    glVertex3f(2.0,-12.1,7.8);
    glVertex3f(1.6,-12.1,7.9);
    glVertex3f(1.6,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.4,-7.5,7.7);
    glVertex3f(2.4,-12.1,7.7);
    glVertex3f(2.0,-12.1,7.8);
    glVertex3f(2.0,-7.5,7.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(3.0,-7.5,7.6);
    glVertex3f(3.0,-12.1,7.6);
    glVertex3f(2.4,-12.1,7.7);
    glVertex3f(2.4,-7.5,7.7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(4.0,-7.5,7.2);
    glVertex3f(4.0,-12.1,7.2);
    glVertex3f(3.0,-12.1,7.5);
    glVertex3f(3.0,-7.5,7.5);
    glEnd();
    glPopMatrix();
    
    //shoulder straps
    glPushMatrix();
    glColor3f(0.0,0.0,0.61);
    glTranslatef(0.0,-7.5,0.0);
    glRotatef(90,1.0,0.0,0.0);
    glutSolidTorus (1.0,7.3,30,120);
    glPopMatrix();
}

void minionArm(bool isLeft, bool handUp)
{
    glColor3f(0.9,0.5,0.0);
    //cylinder: @para: base radius/top radius/height/slices/stacks
    GLfloat radi = 1.5, fingerRadi = 0.7;
    
    int sign = isLeft ? 1 : -1; // left/right parameters offset
    
    // upper arm
    glPushMatrix();
    if (handUp)
    {
        glRotatef(-180, 1.0, 0.0, 0.0);
        glTranslatef(strechX, strechY, 0.0);
        glRotatef(armVert, 0.0, 0.0, 1.0);
    }
    
    glPushMatrix();
    glRotatef(sign * -25, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, radi, radi, 4, 30, 5);
    gluSphere(obj, radi, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(sign * -0.44, -1.8, 0.0);
    glRotatef(sign * -12, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, radi, radi, 2.0, 30, 5);
    gluSphere(obj, radi, 30, 30);
    glPopMatrix();
    
    //fore arm
    glPushMatrix();
    glTranslatef(sign * -0.4, -3.0, 0.0);
    glRotatef(sign * 1, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, radi, radi, 2.0, 30, 5);
    gluSphere(obj, radi, 30, 30);
    glPopMatrix();
    
    // glove (hand)
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(sign * -0.6, -5.2, 0.0);
    glRotatef(sign * 2, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, radi + 0.1, radi + 0.5, 1.6, 30, 5);
    gluSphere(obj, radi + 0.1, 30, 30);
    glPopMatrix();
    
    // fingers
    glPushMatrix();
    glTranslatef(sign * -0.6, -7.0, 1.0);
    glRotatef(sign * 2, 0.0, 0.0, 1.0);
    glRotatef(-80, 1.0, 0.0, 0.0);
    gluCylinder(obj, fingerRadi, fingerRadi, 1.4, 30, 5);
    gluSphere(obj, fingerRadi, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(sign * 0.7, -6.6, 0.8);
    glRotatef(sign * 20, 0.0, 0.0, 1.0);
    glRotatef(-80, 1.0, 0.0, 0.0);
    gluCylinder(obj, fingerRadi, fingerRadi, 1.4, 30, 5);
    gluSphere(obj, fingerRadi, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(sign * -1.8, -6.6, 0.8);
    glRotatef(sign * -20, 0.0, 0.0, 1.0);
    glRotatef(-80, 1.0, 0.0, 0.0);
    gluCylinder(obj, fingerRadi, fingerRadi, 1.4, 30, 5);
    gluSphere(obj, fingerRadi, 30, 30);
    glPopMatrix();
    
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.6, 0.6, 0.6, 0.6);
    obj = gluNewQuadric();
    //    glMatrixMode( GL_MODELVIEW );
    //    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    
    
    glTranslatef(0.0, 0.0, dist);
    glScalef(2, 2, 2);
    //glColor3f(0.9,0.5,0.0);
    minionBody();
    minionFeet();
    
    // left arm
    glPushMatrix();
    if (handUp)
    {
        glTranslatef(-8.0, -7.0, 0.0);
    }
    else
        glTranslatef(-7.8, -11.0, 0.0);
    minionArm(true, handUp);
    glPopMatrix();
    
    // right arm
    glPushMatrix();
    glTranslatef(7.8, -11.0, 0.0);
    minionArm(false, false);
    glPopMatrix();
    
    glutSwapBuffers();
}

// reshape function
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluPerspective(angle, 1.0, nearP, farP);
    else
        gluPerspective(angle, 1.0, nearP, farP);
    gluLookAt(0.0, 0.0, 350.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    int mod;
    switch (key)
    {
        case 'w':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            display();
            break;
        case 'f':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            display();
            break;
        case 97:    //'a'
            mod = glutGetModifiers();
            if (mod == GLUT_ACTIVE_ALT)
                rotate_x += 10.0;
            else
                rotate_x -= 10.0;
            break;
        case 115:   //'s'
            mod = glutGetModifiers();
            if (mod == GLUT_ACTIVE_ALT)
                rotate_y += 10.0;
            else
                rotate_y -= 10.0;
            break;
        case 'y':
            handUp = !handUp;
            break;
        case 'z':
            rotate_z += 5;
            break;
        case 'x':
            rotate_z += -5;
            break;
        case 'r':
            running = true;
            break;
        case 113:
            exit(0);
            break;
    }
    glutPostRedisplay();
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

// mouse function
static void mouse(int button, int state, int x, int y)
{
    /* Rotate the scene with the left mouse button. */
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

// motion function
static void motion(int x, int y)
{
    if (moving) {
        rotate_x = rotate_x + (x - startx);
        rotate_y = rotate_y + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

void Animate(void)
{
    if (running)
    {
        if (runningAngle > 5)
            flag = -1;
        if (runningAngle < -5)
            flag = 1;
        runningAngle += flag * speed;
        dist += speed;
    }

    glutPostRedisplay();
}

void menuSelect(int value)
{
    
    switch (value)
    {
        case 1: running = GL_TRUE;
            speed = 2;//start the animation
            glutIdleFunc(Animate);
            break;
        case 2:
            running = GL_TRUE;
            speed = 5;
            glutIdleFunc(Animate);
            break;
        case 3: running = GL_FALSE;
            //stop the animation
            runningAngle = 0;
            glutIdleFunc(NULL);
            
            break;
        case 7: running = GL_FALSE;
            dist = 0;
            runningAngle = 0;
            glutPostRedisplay();
            break;
        case 6:
            exit(0); //quit application
            break;
    }
}


void Visible(int state)
{
    
    if (state == GLUT_VISIBLE)
    {
        if (running) glutIdleFunc(Animate); //if visible and moving then animate it
    }
    
    else
    {
        if (running) glutIdleFunc(NULL);
        cout << "Minion Stopped!" << '\n';//if invisible and moving then stop animation
        
    }
}

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowSize(win_width, win_height);       // 400 x 400 pixel window
    glutInitWindowPosition(100, 100);   // place window upper at the left corner on display
    glutCreateWindow("Project 2 - Minions");  // window title
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    //glutIdleFunc(Animate);
    glutVisibilityFunc(Visible);
    glutCreateMenu(menuSelect);
    glutIdleFunc(Animate);
    glutAddMenuEntry("walk", 1); //start animation
    glutAddMenuEntry("run", 2); //stop animation
    glutAddMenuEntry("stop", 3);
    glutAddMenuEntry("slow wave", 4);
    glutAddMenuEntry("fast wave", 5);
    glutAddMenuEntry("Quit", 6); //quit
    glutAddMenuEntry("reset", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    
    glutMainLoop();
}