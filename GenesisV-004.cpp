/**************************************
*                                     *
*   GenesisV-004: Colored Solid Cube *
*   Example - Rotating Solid Cube     *
*   With Different Colors Per Face    *
*                                     *
**************************************/

#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "GenesisCORE.h"										// Header File For GenesisCORE
#include "GLExt.h"

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;											// Window Structure
Keys*		g_keys;												// Keyboard Structure

// User Defined Variables
float		angleX;												// Used To Rotate On The X-Axis
float		angleY;												// Used To Rotate On The Y-Axis
float		angleZ;												// Used To Rotate On The Z-Axis

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;										// Store Window Structure
	g_keys		= keys;											// Store Keyboard Structure

	// Start Of User Initialization
	angleX		= 0.0f;											// Set Starting X Angle To Zero
	angleY		= 0.0f;											// Set Starting Y Angle To Zero
	angleZ		= 0.0f;											// Set Starting Z Angle To Zero

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	// Nothing To Deinitialize
}

void Update (DWORD milliseconds)								// Perform Motion Updates Here
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}

	angleX += (float)(milliseconds) / 10.0f;						// Update X Angle Based On The Clock
	angleY += (float)(milliseconds) / 7.0f;						// Update Y Angle Based On The Clock
	angleZ += (float)(milliseconds) / 12.0f;						// Update Z Angle Based On The Clock
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	glTranslatef (0.0f, 0.0f, -6.0f);							// Translate 6 Units Into The Screen
	glRotatef (angleX, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angleX
	glRotatef (angleY, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angleY
	glRotatef (angleZ, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angleZ

	// Draw A Solid Cube With Different Colors Per Face
	glBegin (GL_QUADS);											// Begin Drawing Quads

		// Front Face (Red)
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Left Of The Front Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Right Of The Front Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Top Right Of The Front Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Top Left Of The Front Face

		// Back Face (Green)
		glColor3f (0.0f, 1.0f, 0.0f);							// Set Color To Green
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Bottom Left Of The Back Face
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Back Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Back Face
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Bottom Right Of The Back Face

		// Top Face (Blue)
		glColor3f (0.0f, 0.0f, 1.0f);							// Set Color To Blue
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Top Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Bottom Left Of The Top Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Bottom Right Of The Top Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Top Face

		// Bottom Face (Yellow)
		glColor3f (1.0f, 1.0f, 0.0f);							// Set Color To Yellow
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Top Left Of The Bottom Face
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Top Right Of The Bottom Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Right Of The Bottom Face
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Left Of The Bottom Face

		// Right Face (Magenta)
		glColor3f (1.0f, 0.0f, 1.0f);							// Set Color To Magenta
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Bottom Right Of The Right Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Right Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Top Left Of The Right Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Left Of The Right Face

		// Left Face (Cyan)
		glColor3f (0.0f, 1.0f, 1.0f);							// Set Color To Cyan
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Bottom Left Of The Left Face
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Right Of The Left Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Top Right Of The Left Face
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Left Face

	glEnd ();													// Done Drawing Quads

	glFlush ();													// Flush The GL Rendering Pipeline
}
