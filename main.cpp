//test

#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

int sum = 0;
int x;
ifstream inFile;
int sn;
int cx = 0, cy = 0, cz = 0;

int initial_time = time(NULL), final_time, frame_count = 0;
DWORD dwResult;    
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
}DWORD dwResult;    
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
}
struct Sign
{
	int x1, y1, z1; 
	int state;
	int total;
};  Sign S[100];

void addSign()
{
	S[0].state++; if(S[0].state>4) { S[0].state=1;}
	int st=S[0].state;
	
	if(st==1) { S[0].total++; sn =S[0].total;}
	if(st==1                     ){ S[sn] .x1=cx; S[sn].y1=cy; S[sn] .z1=cz;}
}

void drawSign()
{ int i;
  for (i=1;i<S[0].total+1;i++)
  {
  	glBegin(GL_TRIANGLES);
  	glColor3f(0.2, 0.5, 1);
  	glVertex3f(S[i] .x1,S[i] .y1,S[i] .z1);

  	glEnd();
  }
}
void theCube()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.5, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(0, 3, 0);
	glEnd();
	glColor3f(0.9, 0.1, 0.1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.5);
	glPopMatrix();
}

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

		glBegin(GL_LINES);
		glColor3f(0.3, 0.1, 1);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f(19, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13.5, 0, -45);
	glRotatef(29, 1, 1, 0);
	glBegin(GL_POLYGON);

	drawGrid();
	drawSign();
	theCube();
	glutSwapBuffers();
	glFlush();

	glEnd();

	glVertex2f(0.0, 5.0);
	glVertex2f(-4.0, -3.0);
	glVertex2f(4.0, -3.0);
	glVertex2f(5.0, -2.0);

	frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0)
	{
		cout << "Fps : " << frame_count / (final_time - initial_time) << endl;
		frame_count = 0;
		initial_time = final_time;
	}
}

void init()
{
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
	if(key=='h') {
		addSign();
	}
	if (key == 'w')
	{
		cz -= 1;
	}
	if (key == 's')
	{
		cz += 1;
	} //forward / back
	if (key == 'a')
	{
		cx -= 1;
	}
	if (key == 'd')
	{
		cx += 1;
	} //left /right
	if (key == 'W')
	{
		cz -= 1;
	}
	if (key == 'S')
	{
		cz += 1;
	} //forward / back
	if (key == 'A')
	{
		cx -= 1;
	}
	if (key == 'D')
	{
		cx += 1;
	} //left /right
	if (key == 'XINPUT_GAMEPAD_DPAD_UP')
	{
		cz -= 1;
	}
	

	glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv)
{
	cout << "Welcome To My App / Uygulamama Ho�geldiniz / Dobrodo�li U Moju Aplikaciju \n";
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("MasterLenxiOnDuty"); // Create a window with the given title
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
