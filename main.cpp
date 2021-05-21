#include <windows.h>  
#include <GL/glut.h>
#include <time.h>
#include <iostream> 
#include <fstream>
using namespace std;


int sum = 0;
int x;
ifstream inFile;
int cx=0,cy=0,cz=0;

int initial_time = time(NULL) , final_time,frame_count=0;

void theCube()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.5, 0.1);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(0, 3, 0);
    glEnd();
	glColor3f(0.9,0.1,0.1);
	glTranslatef(cx,cy,cz);
	glutSolidCube(0.4);
	glPopMatrix();
	
}

void drawGrid()
{
	int i;
	for (i=0;i<40;i++)
	{
		glPushMatrix();
		if(i<20){ glTranslatef(0,0,i);}
		if(i>=20){ glTranslatef(i-20,0,0); glRotatef(-90,0,1,0);}
		
		glBegin(GL_LINES);
		glColor3f(0.3,0.1,1); glLineWidth(1);
		glVertex3f(0,-0.1,0); glVertex3f(19,-0.1,0);
		glEnd();
		glPopMatrix();
	}
}

void display() 
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glTranslatef(-13.5,0,-45);
   glRotatef(29,1,1,0);
   
   drawGrid();
   theCube();
   glutSwapBuffers();
   

	
   frame_count++;
   final_time = time(NULL);
   if(final_time - initial_time > 0)
   {
   	cout<<"Fps : "<<frame_count/ (final_time - initial_time) <<endl;
   	frame_count = 0;
   	initial_time = final_time;
   }
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
}


void keyboard(unsigned char key,int x,int y)
{
	if(key=='w'){cz-=1;} if(key=='s'){cz+=1;}   //forward / back
	if(key=='a'){cx-=1;} if(key=='d'){cx+=1;}  //left /right
	if(key=='W'){cz-=1;} if(key=='S'){cz+=1;}   //forward / back
	if(key=='A'){cx-=1;} if(key=='D'){cx+=1;}  //left /right
	
	glutPostRedisplay();
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   cout<<"Welcome To My App / Uygulamama Hoþgeldiniz / Dobrodošli U Moju Aplikaciju \n";
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(1200,800); 
   glutCreateWindow("MasterLnxyOnDuty"); // Create a window with the given title
     // Set the window's initial width & height
    // Position the window's initial top-left corner
 
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
    init();
	// Register display callback handler for window re-paint
   glutMainLoop();  
           // Enter the event-processing loop
   return 0;
}
