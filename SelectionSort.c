#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
									   // #include <GL/gl.h>
									   // #include <GL/glu.h>
#include <GL/glut.h> // Above two are already included in glut.h

void display();
void reshape(int, int);
void timer(int);
void SelectionSort(int*, int, int);

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	 // RGB--set in glutInitDisplayMode--and alpha**
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); 				 							 // Initializing glut,
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // RGB is the color mode, and use double buffers
	
	glutInitWindowPosition(200, 100); // Before creating window,
	glutInitWindowSize(500, 500);     // set up window position and size
	
	glutCreateWindow("Window1"); // Create window and set title
	
	glutDisplayFunc(display); 	// Both take a callback function--pointer to function 
	glutReshapeFunc(reshape); 	// must be called after creating the window
	glutTimerFunc(0, timer, 0); // Recursiveley calls itself, to update the object on display
	init();
	glutMainLoop(); // Also to keep the window open, call the main loop
								  // otherwise since no task, window will terminate
}

int arr[40] = {1, 3, 5, 7, 9, 
							2, 4, 6, 8, 10, 
							11, 13, 15, 17, 19, 
							12, 14, 16, 18, 20, 
							21, 23, 25, 27, 29, 
							22, 24, 26, 28, 30, 
							31, 33, 35, 37, 39, 
							32, 34, 36, 38, 40};

// Clear, Reset, Draw, Display
int cursor, cursor2, cursor3;
void display()
{
	// Clear and Reset
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the BUFFER before drawing
	glLoadIdentity(); // Reset the current metrics** (Rotations, transformations, etc)
	
	// Draw
	int i;
	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (i == cursor)
		{
			glColor3f(1.0, 0.5, 0.5);
		}
		else if (i == cursor3)
		{
			glColor3f(0.5, 0.5, 1.0);
		}
		else if (i == cursor2)
		{
			glColor3f(0.5, 1.0, 0.5);
		}
		else 
		{
			glColor3f(1.0, 1.0, 1.0);
		}
		glBegin(GL_POLYGON);
		glVertex2f(-10 + (i / 2.0), (arr[i]/2.0) - 10);
		glVertex2f(-10 + (i / 2.0), -10);
		glVertex2f(-10 + (i / 2.0) + 0.5, -10);
		glVertex2f(-10 + (i / 2.0) + 0.5, (arr[i]/2.0) - 10);
		glEnd();
	}
	
	// Display
	// glFlush();	
	glutSwapBuffers(); // Swap back buffer with the front buffer, this will avoid distortion in display
										 // if the object is complex thus could not be drawn within the span of a frame
}

// Set viewport and projection to maintain resolution
void reshape(int w, int h)
{
	// Viewport
	glViewport(0, 0, (GLsizei) w,(GLsizei) h); // Type casting is not neccesary	
	
	// Projection
	glMatrixMode(GL_PROJECTION);  // Currently in GL_MODELVIEW matrix, arg is change target
	glLoadIdentity();             // Reset
	gluOrtho2D(-10, 10, -10, 10);	// 2D projection
	glMatrixMode(GL_MODELVIEW);   // Back in MODELTVIEW matrix, to be able to draw  
}

// Timer function to apply updates to display at given periods
int iteration = 0, iteration2 = 1, temp;
void timer(int t)
{
	glutPostRedisplay();              // Recalls the display function
	glutTimerFunc(1000/25, timer, 0); // Calls itself every sixtieth of a second (60FPS)
	if (iteration != 40)
	{
		SelectionSort(arr, iteration, iteration2);
		if (iteration2 == 39)
		{
			if (arr[cursor3] > arr[iteration])
			{
				printf("Swapping %i at index %i; and %i at index %i.\n", arr[iteration], iteration, arr[cursor3], cursor3);
				temp = arr[iteration];
				arr[iteration] = arr[cursor3];
				arr[cursor3] = temp;
			}
			iteration++;
			cursor3 = iteration;
			iteration2 = iteration;
			
		}	
	}
	iteration2++;
}

void SelectionSort(int *a, int iteration, int iterataion2)
{
	cursor = iteration;
	cursor2 = iteration2;
	if (a[iteration2] > a[cursor3])
	{
		cursor3 = iteration2;
	}
	return;
}
