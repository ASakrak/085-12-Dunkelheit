/*//////////////////////
first of all I'm aware that the code is too complicated but I'm too busy to fix it.
I'm using this app just to have fun with cpp and learn/try something.
By the way so many code not running i know.
*/

//(It has no commercial purpose.)
/////////////////////

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
// for compile test
#include "src/test.cpp"
//
#include "src/UnitTest.h"
#include "include/test.h"
#include <bitset>
#include <time.h>
#include <string.h>
#include <cstdio>
#include <windows.h>
/*if you want to change color, u need this scheme.
 0 = Black       8 = Gray
	1 = Blue        9 = Light Blue
	2 = Green       A = Light Green
	3 = Aqua        B = Light Aqua
	4 = Red         C = Light Red
	5 = Purple      D = Light Purple
	6 = Yellow      E = Light Yellow
	7 = White       F = Bright White
*/
#include <math.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iso646.h>
#include <algorithm>
//#include <chrono>
//#include <thread>
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE 7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD 30
#define Xbox_BtnA Btn(0)
#define Xbox_BtnB Btn(1)
#define Xbox_BtnX Btn(2)
#define Xbox_BtnY Btn(3)
#define Xbox_LB Btn(4)
#define Xbox_RB Btn(5)
#define Xbox_Back Btn(6)
#define Xbox_Start Btn(7)

#include <cmath>
#define PI 3.1415926535897;

#ifdef __APPLE__
#ifdef TARGET_OS_MAC

#include <osx.h>

#endif
#elif defined(_WIN32) || defined(_WIN64)

#endif
/**/
using namespace std;
// using namespace this_thread; // sleep_for, sleep_until
// using namespace chrono; // nanoseconds, system_clock, seconds
int sum = 0;
int x;
int w;
void timer(int);
// this code for open file in console but its not running idk
ifstream inFile;
//
GLfloat angle = 0.0f;
int sn;
int cx = 7, cy = 0, cz = 7;
GLuint texture;
// this code for frame counter
int initial_time = time(NULL), final_time, frame_count = 0;

// Set this to true to animate.
// static bool spinning = true;
// This is the number of frames per second to render.
// static const int FPS = 60;
// static GLfloat currentAngleOfRotation = 0.0;

// test

/*void yoda(){
int i;
GLint circle_points = 100;
glBegin(GL_LINE_LOOP);
for (i = 0; i < circle_points; i++) {
   angle = 2*PI*i/circle_points;
   glVertex2f(cos(angle), sin(angle));
}
}*/

// test
/*DWORD dwResult;
for (DWORD i=0; i< XUSER_MAX_COUNT; i++ )
{
	XINPUT_STATE state;
	ZeroMemory( &state, sizeof(XINPUT_STATE) );

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState( i, &state );

	if( dwResult == ERROR_SUCCESS )
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}
}*/
static int shoulderAngle = 0, elbowAngle = 0;
/*s
void drawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIXM, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIndetity();
	glRasterPos2i(x, y);
	for(int i=0; i<length, i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

	}
}

void DrawScreen(SDL_Surface* screen, int h)
{
	glClear(GL_COLOR_BUFFER)
}
*/
// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		(elbowAngle += 5) and_eq 360;
		break;
	case GLUT_KEY_RIGHT:
		(elbowAngle -= 5) and_eq 360;
		break;
	case GLUT_KEY_UP:
		(shoulderAngle += 5) and_eq 360;
		break;
	case GLUT_KEY_DOWN:
		(shoulderAngle -= 5) and_eq 360;
		break;
	default:
		return;
	}
	glutPostRedisplay();
}
void wireBox(GLdouble width, GLdouble height, GLdouble depth)
{
	glPushMatrix();
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix();
}

// this codes for add texture but its not running now
GLuint LoadTexture(const char *filename, int width, int height)
{

	//    GLuint texture;
	unsigned char *data;
	FILE *file;

	// The following code will read in our RAW file
	file = fopen(filename, "rb");
	if (file == NULL)
		return 0;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//    // the texture wraps over at the edges (repeat)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
					  GL_RGB, GL_UNSIGNED_BYTE, data);

	free(data);

	return texture;
}
/*void idle() {
   glutPostRedisplay();   // Post a re-paint request to activate display()
}*/
/*void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}*/

/*void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
	// width is smaller, go from -50 .. 50 in width
	glOrtho(-50.0, 50.0, -50.0/aspect, 50.0/aspect, -1.0, 1.0);
  } else {
	// height is smaller, go from -50 .. 50 in height
	glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -1.0, 1.0);
  }
}*/

struct Sign
{
	int x1, y1, z1;
	int state;
	int total;
};
/*void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;


   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
	 // aspect >= 1, set the height from -1 to 1, with larger width
	  gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
	  // aspect < 1, set the width to -1 to 1, with larger height
	 gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}*/
Sign S[100];
// this code adding sign to grid but now its not running.
/*void addSign()
{
	S[0].state++;
	if (S[0].state > 4)
	{
		S[0].state = 1;
	}
	int st = S[0].state;

	if (st == 1)
	{
		S[0].total++;
		sn = S[0].total;
	}
	if (st == 1)
	{
		S[sn].x1 = cx;
		S[sn].y1 = cy;
		S[sn].z1 = cz;
	}
}*/

// THIS CODES NOT RUNNING. I HAVENT ANY IDEA BUT I'LL FIX
void drawSign()
{
	int i;
	for (i = 1; i < S[0].total + 1; i++)
	{

		glColor3f(0.2, 0.5, 1);
		glVertex3f(S[i].x1, S[i].y1, S[i].z1);

		glEnd();
	}
}

void test()
{
	GLboolean glIsFramebuffer(GLuint framebuffer);
	//
	// glDrawBuffer(theCube);
	// glReadBuffer(theCube);
}

/*void glGetQueryObjectiv(	GLuint id,
GLenum pname,
GLint * params);*/

// this code for cube and sphere
void theCube()
{
	// i tried adding texture but its not running. i havent any idea for this codes idk LMAOOIO
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture); // bind the texture
	glPushMatrix();
	// glBegin(GL_TRIANGLES);
	// glBegin(GL_QUAD_STRIP);
	// glColor3f(2.0f, 0.5f, 1.0f);
	// glutSolidCube(0.4);
	glVertex3f(0, 0, 0);
	glVertex3f(8, 0, 0);
	glVertex3f(0, 8, 0);
	glEnd();
	glColor3f(0.6f, 0.1f, 0.9f);
	glTranslatef(cx, cy, cz);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	/*/teapot
	glutWireTeapot(1.0);
	glTranslatef(-1.75, 0.5, 0.0);
	//*/
	///////////////////////////////////////////
	//
	// I'm trying make christmas tree
	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.5, 1.5, 70, 12);
	// glutSolidTorus(1.175, 1.85, 100, 60);
	// glTranslatef(-0.10, 0.5, -0.8);
	// glRotatef(270.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.95);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.5, 1.5, 70, 12);
	//////////
	glPushMatrix();
	glTranslatef(0.0, 0.2, 1.15);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.5, 1.5, 70, 12);
	////
	glPushMatrix();
	glTranslatef(0.0, 0.2, -2.7);
	glRotatef(0.0, 1.0, 0.0, 0.0);
	glutSolidCube(1.2);
	/////
	glPushMatrix();
	glTranslatef(-0.6, -1.1, 1.9);
	glRotatef(-0.5, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);
	/////
	glPushMatrix();
	glTranslatef(0.9, -0.8, 0.5);
	glRotatef(-0.5, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);
	/////
	glPushMatrix();
	glTranslatef(0.9, 1.5, 0.5);
	glRotatef(-0.5, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);

	/////
	glPushMatrix();
	glTranslatef(0.2, 1.0, 0.5);
	glRotatef(-0.5, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);
	/////

	glPushMatrix();
	glTranslatef(-1.2, -1.0, 0.5);
	glRotatef(-0.5, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);

	/////
	//(x,y,z)
	glPushMatrix();
	glTranslatef(-1.5, -1.0, 0.5);
	glRotatef(-0.7, -2.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);

	/*glPushMatrix();
	glTranslatef(0.9, -0.8, 0.5);
	glRotatef(1.6, 1.0, 1.0, 0.0);
	glutSolidSphere(0.370, 30, 30);*/

	///////////////////////////////////////////

	// Add a sphere to the scene.
	// glTranslatef(-0.10, 0.5, 0.0);
	// glRotatef(270.0, 1.0, 0.0, 0.0);
	// glutSolidSphere(1.900, 30, 50);
	// glutSolidSphere(1.570, 30, 30);

	// x,y,z
	glPushMatrix();
	/////////////x      y    z
	// glTranslatef(-0.5, 0.5, 3.4);
	// glRotatef(270.0, 0.5, 0.0, 0.0);
	// glRotatef(270.0, 1.0, 0.0, 0.0);
	// glutSolidSphere(0.150, 30, 50);

	/////////////x      y    z
	// glTranslatef(-1.0, 0.1, 0.2);
	// glRotatef(270.0, 0.5, 0.0, 0.0);
	// glRotatef(270.0, 1.0, 0.0, 0.0);
	// glutSolidSphere(0.150, 30, 50);

	//////////////
	// glTranslatef(-0.7, -0.5, 0.2);
	// glRotatef(270.0, 0.5, 0.0, 0.0);
	// glRotatef(270.0, 1.0, 0.0, 0.0);

	// glutSolidSphere(0.150, 30, 50);
	glPopMatrix();
	Sleep(10);
	// same code but for unix
	// and this "#include <unistd.h>" lib for these codes
	/*unsigned int microsecond = 1000000;
	usleep(3 * microsecond);//sleeps for 3 second*/

	// sleep_for(nanoseconds(10));
	// sleep_until(system_clock::now() + seconds(1));v
	///////////////////////////////////////////
	// this code makeing circle/sphere
	glColor4f(0.5f, 0.2f, 0.2f, 1.0f);
	// glutSolidSphere(1.31f, 100, 100);s
	// this code making torus
	glColor4f(0.5f, 0.5f, 0.5f, 0.3f);
	// glutWireTorus(0.8, 3, 5, 90);
	// cube here//
	// glutSolidCube(5);
	/////////////////
	glPopMatrix();
	glEnd();
	glFlush();
}
//>><<<<<<<<<<<<<<<
void drawGrid()
{
	int i;
	for (i = 0; i < 40; i++)
	{
		glPushMatrix();
		if (i < 20)
		{
			glTranslatef(0, 0, i);
		}
		if (i >= 20)
		{
			glTranslatef(i - 20, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}

		glBegin(GL_LINE_LOOP);
		glColor4f(2.1f, 1.1f, 0.1f, 5.0f);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}
class Orbiter
{
	double radius;
	double u;

public:
	Orbiter(double radius) : radius(radius), u(0.0) {}
	void advance(double delta) { u += delta; }
	void getPosition(double &x, double &y, double &z)	
	{
		x = radius * cos(u);
		y = 0;
		z = radius * sin(u);
	}
};
static Orbiter orbiter(5.0);
float x_position = -10.0;

void timer(int v)
{
    
	orbiter.advance(0.01);
	glutTimerFunc(1000 / 60, timer, v);
}
/*class Camera {
  double theta;      // determines the x and z positions
  double y;          // the current y position
  double dTheta;     // increment in theta for swinging the camera around
  double dy;         // increment in y for moving the camera up/down
public:
  Camera(): theta(0), y(3), dTheta(0.04), dy(0.2) {}
  double getX() {return 10 * cos(theta);}
  double getY() {return y;}
  double getZ() {return 10 * sin(theta);}
  void moveRight() {theta += dTheta;}
  void moveLeft() {theta -= dTheta;}
  void moveUp() {y += dy;}
  void moveDown() {if (y > dy) y -= dy;}
};*/
void display()
{

	// just for animation*/
	/*glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glFlush();
	glutSwapBuffers();*/
	//

	glutTimerFunc(0, timer, 0);
	double x, y, z;
	orbiter.getPosition(x, y, z);
	gluLookAt(x, y, z, 0.1, 0.1, 0.0, 0.0, 1.0, 0.0);
	// make the color a deep blue hue
	glClearColor(0.0F, 0.0F, 0.0F, 0.1F);
	// make the shading smooth
	glShadeModel(GL_SMOOTH);
	// clear the color buffers
	/////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	wireBox(2.0, 0.4, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
	glPushMatrix();						// Save model-view matrix setting
	glTranslatef(-0.5f, 0.4f, 0.0f);	// Translate
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
	glTranslatef(1.0, 0.0, 0.0);
	wireBox(2.0, 0.4, 1.0);
	///
	// I'm trying make animation to sphere andd torus
	glVertex2f(x_position, 1.0);
	glVertex2f(x_position, -1.0);
	glVertex2f(x_position + 2.0, -1.0);
	glVertex2f(x_position + 2.0, 1.0);

	glLoadIdentity();
	glTranslatef(-13.5, 0, -45);
	glRotatef(24, 1, 1, 0);
	// glBegin(GL_POLYGON);
	// glBegin(GL_TRIANGLES);
	// glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(5, 0, 0);
	glVertex3f(0, 5, 0);
	// glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(0, 4, 0);
	// this code making cube//
	// glutSolidCube(0.5);
	// glutWireTetrahedron(0.5);

	// this code not running but i'll fix(this code for image rendering)
	// texture = LoadTexture("aaaaaaaaaaaaaaaaaaaa", 256, 256);
	///////////////////////////////////////////

	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/// glColor3f(0.5f, 0.0f, 1.0f); // (0.5, 0, 1) is half red and full blue, giving dark purple.
	// glBegin(GL_QUADS);
	glVertex2f(0.0, 5.0);
	glVertex2f(-1.0, -3.0);
	glVertex2f(4.0, -3.0);
	glVertex2f(5.0, -2.0);
	glEnd();
	drawGrid();
	drawSign();
	theCube();
	// FreeTexture(texture);
	glutSwapBuffers();
	glFlush();

	glEnd();
	// angle += 0.2f;
	glVertex2f(0.0, 5.0);
	glVertex2f(-10.0, -3.0);
	glVertex2f(4.0, -3.0);
	glVertex2f(5.0, -2.0);
    
	// this codes for frame counter on console
	frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0)
	{

		cout << "Frame : " << frame_count / (final_time - initial_time) << endl;
		//printf("Frame %d\n", frame_count);

		frame_count = 0;
		initial_time = final_time;
	}
}

/*void timer /*but for animation*/ /* (int v) {

	 if (spinning) {
	 currentAngleOfRotation += 1.0;
	 if (currentAngleOfRotation > 360.0) {
	   currentAngleOfRotation -= 360.0;
	 }
	 glutPostRedisplay();
   }
   glutTimerFunc(1000/FPS, timer, v);
 }


 void mouse(int button, int state, int x, int y) {
	 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		 spinning = true;
	 }
	 else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		 spinning = false;
	 }
 }*/

void init()
{
	// this codes for color
	GLfloat black[] = {0.0, 1.0, 1.0, 1.0};
	GLfloat yellow[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat cyan[] = {0.0, 1.0, 0.0, 0.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat direction[] = {1.0, 1.0, 1.0, 1.0};
	
	/*green
	GLfloat black[] = {0.0, 1.0, 1.0, 1.0};
	GLfloat yellow[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat cyan[] = {0.0, 1.0, 0.0, 0.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat direction[] = {1.0, 1.0, 1.0, 1.0};*/
	
	/*black
	GLfloat black[] = {0.0, 1.0, 1.0, 0.0};
	GLfloat yellow[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat cyan[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat direction[] = {1.0, 1.0, 1.0, 1.0};*/
	
	
	/*red
	GLfloat black[] = {0.0, 1.0, 0.0, 0.0};
	GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat cyan[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat direction[] = {1.0, 1.0, 1.0, 1.0};
	*/
	
	/*purple
	GLfloat black[] = {0.0, 1.0, 1.0, 0.0};
	GLfloat yellow[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat cyan[] = {1.0, 0.0, 1.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat direction[] = {1.0, 1.0, 1.0, 1.0};
	*/

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 25);

	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);

	glEnable(GL_LIGHTING); // so the renderer considers light
	glEnable(GL_LIGHT0);   // turn LIGHT0 on
	glEnable(GL_DEPTH_TEST);
	///
	// glBegin(GL_TRIANGLES);
	// glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
	///
	glVertex3f(0, 5, 0);
	glVertex3f(5, 0, 0);
	glVertex3f(0, 5, 0);
	glEnd();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GLUT_SINGLE);
	glMatrixMode(GLUT_RGB);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	/*if (key == 'h')
	{
		addSign();
	}*/
	if (key == '8')
	{
		cz -= 1;
	}
	if (key == '2')
	{
		cz += 1;
	} // forward / back
	if (key == '4')
	{
		cx -= 1;
	}
	if (key == '6')
	{
		cx += 1;
	}
	if (key == 'w')
	{
		cz -= 1;
	}
	if (key == 's')
	{
		cz += 1;
	} // forward / back
	if (key == 'a')
	{
		cx -= 1;
	}
	if (key == 'd')
	{
		cx += 1;
	} // left /right
	if (key == 'W')
	{
		cz -= 1;
	}
	if (key == 'S')
	{
		cz += 1;
	} // forward / back
	if (key == 'A')
	{
		cx -= 1;
	}
	if (key == 'D')
	{
		cx += 1;
	} // left /right
	/*if (key == 'Xbox_BtnA')
	{
		cz -= 1;
	}
	if (key == 'Btn(1)')
	{
		cz += 1;
	} //forward / back
	if (key == 'Btn(2)')
	{
		cx -= 1;
	}
	if (key == 'Btn(3)')
	{
		cx += 1;

	} //left /right
	  //*/
	glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
	system("color 08");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout<<"   WILLKOMMEN \n";
	/*
	cout << "Welcome to my app / Uygulamama Ho�geldiniz / Dobrodo�li U Moju Aplikaciju / Velkommen til appen min\n";*/
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Alpha 0.1.0.0"); // Create a window with the given title
									   // Set the window's initial width & height
									   // Position the window's initial top-left corner
									   // glutIdleFunc(idle);
									   // glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	// glutReshapeFunc(reshape);
	// glutMouseFunc(mouse);
	glutTimerFunc(0, timer, 0);
	init();
	// Register display callback handler for window re-paint
	glutMainLoop();
	// Enter the event-processing loop
	return 0;
}
