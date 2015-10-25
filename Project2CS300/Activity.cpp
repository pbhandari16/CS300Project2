/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * CSCI 300 Graphics Project 2
 *
 * Nan Jiang, Pratistha Bhandari, Xiangyu Li *
 *
 * Activity.cpp -
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

GLUquadricObj *obj;         // Pointer for quadric objects.

// Parameters for gluPerspective()
GLint angle = 60, nearP = 1, farP = 1000;

// Translation of the whole object
static GLfloat xTrans = 0.0, yTrans = 0.0, zTrans = 0.0;

// Rotation of the whole object
static GLfloat rotate_x = 0.0, rotate_y = 0.0, rotate_z = 0.0;

// Mouse function related variables
static int moving = 0, startx, starty;

// Initialize OpenGL graphics
void init(void)
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1.0, nearP, farP);
    gluLookAt(0.0, 0.0, 350.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);            // turn on the depth buffer
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
    glColor3f(1.0,0.0,0.0);
    
    //middle part clothing
    glBegin(GL_POLYGON);
    glVertex3f(-1.2,-7.5,8.0);
    glVertex3f(-1.2,-12.0,8.0);
    glVertex3f(1.2,-12.0,8.0);
    glVertex3f(1.2,-7.5,8.0);
    glEnd();
    
    //left side clothing
    glBegin(GL_POLYGON);
    glVertex3f(-1.6,-7.5,7.9);
    glVertex3f(-1.6,-12.0,7.9);
    glVertex3f(-1.2,-12.0,7.9);
    glVertex3f(-1.2,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-2.0,-7.5,7.8);
    glVertex3f(-2.0,-12.0,7.8);
    glVertex3f(-1.6,-12.0,7.9);
    glVertex3f(-1.6,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-2.4,-7.5,7.7);
    glVertex3f(-2.4,-12.0,7.7);
    glVertex3f(-2.0,-12.0,7.8);
    glVertex3f(-2.0,-7.5,7.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-3.0,-7.5,7.6);
    glVertex3f(-3.0,-12.0,7.6);
    glVertex3f(-2.4,-12.0,7.7);
    glVertex3f(-2.4,-7.5,7.7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-4.0,-7.5,7.3);
    glVertex3f(-4.0,-12.0,7.3);
    glVertex3f(-3.0,-12.0,7.6);
    glVertex3f(-3.0,-7.5,7.6);
    glEnd();
    
    
    //right side clothing
    glBegin(GL_POLYGON);
    glVertex3f(1.6,-7.5,7.9);
    glVertex3f(1.6,-12.0,7.9);
    glVertex3f(1.2,-12.0,7.9);
    glVertex3f(1.2,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.0,-7.5,7.8);
    glVertex3f(2.0,-12.0,7.8);
    glVertex3f(1.6,-12.0,7.9);
    glVertex3f(1.6,-7.5,7.9);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.4,-7.5,7.7);
    glVertex3f(2.4,-12.0,7.7);
    glVertex3f(2.0,-12.0,7.8);
    glVertex3f(2.0,-7.5,7.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(3.0,-7.5,7.6);
    glVertex3f(3.0,-12.0,7.6);
    glVertex3f(2.4,-12.0,7.7);
    glVertex3f(2.4,-7.5,7.7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(4.0,-7.5,7.3);
    glVertex3f(4.0,-12.0,7.3);
    glVertex3f(3.0,-12.0,7.6);
    glVertex3f(3.0,-7.5,7.6);
    glEnd();
    
    
    glPopMatrix();
}

void drawArms(void)
{
    glColor3f(1.0, 1.0, 0.0);
    obj = gluNewQuadric();
    //cylinder: @para: base radius/top radius/height/slices/stacks
    // upper arm
    glPushMatrix();
    glRotatef(-25, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 8.0, 8.0, 26, 30, 5);
    gluSphere(obj, 8.0, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-8.0, -36.0, 0.0);
    glRotatef(-13, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 8.0, 8.0, 40, 30, 5);
    gluSphere(obj, 8.0, 30, 30);
    glPopMatrix();
    
    //fore arm
    glPushMatrix();
    glTranslatef(-7.0, -68.0, 0.0);
    glRotatef(2, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 8.0, 8.0, 32, 30, 5);
    gluSphere(obj, 8.0, 30, 30);
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-6.0, -74.0, 0.0);
    glRotatef(2, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 9.0, 9.5, 10, 30, 5);
    gluSphere(obj, 9.0, 30, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-6.0, -89.0, 0.0);
    glRotatef(2, 0.0, 0.0, 1.0);
    glRotatef(-85, 1.0, 0.0, 0.0);
    gluCylinder(obj, 4.0, 4.0, 7, 30, 5);
    glTranslatef(0.0, -4.0, 0.0);
    gluSphere(obj, 5.0, 30, 30);
    glPopMatrix();
    
    //
    glPushMatrix();
    glTranslatef(0.0, -84.0, 0.0);
    glRotatef(35, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 4.0, 4.0, 7, 30, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, -86.0, 0.0);
    gluSphere(obj, 5.0, 30, 30);
    glPopMatrix();
    
    //
    glPushMatrix();
    glTranslatef(-12.0, -84.0, 0.0);
    glRotatef(-35, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, 4.0, 4.0, 7, 30, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-12.0, -86.0, 0.0);
    gluSphere(obj, 5.0, 30, 30);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(xTrans, yTrans, zTrans);
    
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glRotatef(rotate_x, 0.0, 0.0, 1.0 );
    glRotatef(rotate_y, 1.0, 0.0, 0.0);
    
    glColor3f(0.9,0.5,0.0);
    //glScaled(5,5,5);
    //minionBody();
    
    drawArms();
    
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
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

// keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 's':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    
    init();
    
    glutMainLoop();
}