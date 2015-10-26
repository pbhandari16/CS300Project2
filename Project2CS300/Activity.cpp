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

/***** Global variables *****/
GLint win_width = 800;      // window dimensions
GLint win_height = 800;

// Parameters for gluPerspective()
GLint angle = 60, nearP = 1, farP = 1000;

GLUquadricObj *obj;         // Pointer for quadric objects.

// Rotation of the whole object
static GLfloat rotate_x = 0.0, rotate_y = 0.0, rotate_z = 0.0;

// Rotation for arms
static GLfloat armVert = 0.0, strechX = 0.0, strechY = 0.0, armSpeed = 1.0;
bool maxWave = false, waveHand = false;
static GLint fastFlag = 0;

// Mouse function related variables
static int moving = 0, startx, starty;

// Settings for running
float runningAngle = 0;
bool running = false;
int flag = 1;
float speed = 2;
int dist = 0;
int face = 0;

float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

// Initialize OpenGL graphics
void init(void)
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // gray background
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

// draw shoe tip
void drawShoeTip()
{
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
}

// draw shoe body
void drawShoeBody(float l, float w)
{
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
}

// draw feet
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
    glTranslatef(0, -1, 1.5);
    drawShoeTip();
    drawShoeBody(3, 2);
    glPopMatrix();
    glPopMatrix();
    
}

// draw body
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
    
    //left side clothing
    glColor3f(0.0,0.0,1.0);
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
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0.0,-7.5,0.0);
    glRotatef(90,1.0,0.0,0.0);
    glutSolidTorus (1.0,7.3,30,120);
    glPopMatrix();
}

// draw arm
void minionArm(bool isLeft, bool handUp)
{
    glColor3f(0.9,0.5,0.0);
    //cylinder: @para: base radius/top radius/height/slices/stacks
    GLfloat radi = 1.5, fingerRadi = 0.7;
    
    int sign = isLeft ? 1 : -1; // left/right parameters offset
    
    // upper arm
    glPushMatrix();
    if (handUp && isLeft)
    {
        glRotatef(-180, 1.0, 0.0, 0.0);
        glTranslatef(strechX, strechY, 0.0);
        glRotatef(armVert, 0.0, 0.0, 1.0);
    }
    else if (handUp && !isLeft)
    {
        glRotatef(-180, 1.0, 0.0, 0.0);
        glTranslatef(-strechX, strechY, 0.0);
        glRotatef(-armVert, 0.0, 0.0, 1.0);
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

// display function
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // draw floor
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(200.0, -52.0, 200.0);
    glVertex3f(200.0, -52.0, -200.0);
    glVertex3f(-200.0, -52.0, -200.0);
    glVertex3f(-200.0, -52.0, 200.0);
    glEnd();
    
    obj = gluNewQuadric();
    glTranslatef(trans_x, trans_y, trans_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    
    glScalef(2, 2, 2);
    
    minionBody();
    minionFeet();
    
    // left arm
    glPushMatrix();
    if (waveHand)
    {
        glTranslatef(-8.0, -7.0, 0.0);
    }
    else
        glTranslatef(-7.8, -11.0, 0.0);
    minionArm(true, waveHand);
    glPopMatrix();
    
    // right arm
    glPushMatrix();
    if (waveHand && fastFlag)
    {
        glTranslatef(8.0, -7.0, 0.0);
        minionArm(false, waveHand);
    }
    else
    {
        glTranslatef(7.8, -11.0, 0.0);
        minionArm(false, false);
    }
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
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
}

// keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
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
        case 113:
            exit(0);
            break;
        default:
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

// idle function
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
        switch (face) {
            case 0:
                trans_z += speed;
                //cout << "Check";
                break;
            case 1:
                trans_x += speed;
                break;
            case 2:
                trans_z -= speed;
                break;
            case 3:
                trans_x -= speed;
                break;
            default:
                break;
        }
        
        if (dist >= 80)
        {
            rotate_y +=90;
            face = (face+1)%4;
            dist = 0;
        }
    }
    
    if (fastFlag)
        armSpeed = 4.0;
    else
        armSpeed = 1.0;
    
    if (waveHand)
    {
        if (!maxWave && armVert > -60)
        {
            strechX -= 0.1;
            strechY += 0.1;
            armVert -= 5.0 * armSpeed;
        }
        else if (!maxWave && armVert <= -60)
        {
            maxWave = !maxWave;
            strechX += 0.1;
            strechY -= 0.1;
            armVert += 5.0 * armSpeed;
        }
        else if (maxWave && armVert >= 0)
        {
            maxWave = !maxWave;
            strechX -= 0.1;
            strechY += 0.1;
            armVert -= 5.0 * armSpeed;
        }
        else
        {
            strechX += 0.1;
            strechY -= 0.1;
            armVert += 5.0 * armSpeed;
        }
    }
    glutPostRedisplay();
}

// menu function
void menuSelect(int value)
{
    
    switch (value)
    {
        case 1:
            running = GL_TRUE;
            speed = 2;//start the animation
            glutIdleFunc(Animate);
            break;
        case 2:
            running = GL_TRUE;
            speed = 5;
            glutIdleFunc(Animate);
            break;
        case 3:
            running = GL_FALSE;
            //stop the animation
            runningAngle = 0;
            waveHand = GL_FALSE;
            maxWave = GL_FALSE;
            fastFlag = 0;
            glutIdleFunc(NULL);
            break;
        case 4:
            waveHand = GL_TRUE;
            maxWave = GL_FALSE;
            fastFlag = 0;
            glutIdleFunc(Animate);
            break;
        case 5:
            waveHand = GL_TRUE;
            maxWave = GL_FALSE;
            fastFlag = 1;
            glutIdleFunc(Animate);
            break;
        case 7:
            running = GL_FALSE;
            dist = 0;
            runningAngle = 0;
            glutPostRedisplay();
            break;
        case 6:
            exit(0); //quit application
            break;
    }
}

// visibility function
void Visible(int state)
{
    
    if (state == GLUT_VISIBLE)
    {
        if (running) glutIdleFunc(Animate); //if visible and moving then animate it
    }
    
    else
    {
        if (running) glutIdleFunc(NULL);
    }
}

// main function
int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowSize(win_width, win_height);       // 800 x 800 pixel window
    glutInitWindowPosition(100, 100);   // place window upper at the left corner on display
    glutCreateWindow("Project 2 - Minions");  // window title
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
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
