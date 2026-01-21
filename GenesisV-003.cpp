/**************************************
*                                     *
*   GenesisV-003: Simple Cube       *
*   Example - Rotating Wireframe Cube*
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

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;										// Store Window Structure
	g_keys		= keys;											// Store Keyboard Structure

	// Start Of User Initialization
	angleX		= 0.0f;											// Set Starting X Angle To Zero
	angleY		= 0.0f;											// Set Starting Y Angle To Zero

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
	angleY += (float)(milliseconds) / 7.0f;						// Update Y Angle Based On The Clock (Different Speed)
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	glTranslatef (0.0f, 0.0f, -6.0f);							// Translate 6 Units Into The Screen
	glRotatef (angleX, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angleX
	glRotatef (angleY, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angleY

	// Draw A Wireframe Cube
	glColor3f (1.0f, 1.0f, 1.0f);								// Set Color To White
	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Front Face
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Left Of The Front Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Right Of The Front Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Top Right Of The Front Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Top Left Of The Front Face
	glEnd ();													// Done Drawing Front Face

	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Back Face
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Bottom Left Of The Back Face
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Back Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Back Face
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Bottom Right Of The Back Face
	glEnd ();													// Done Drawing Back Face

	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Top Face
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Top Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Bottom Left Of The Top Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Bottom Right Of The Top Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Top Face
	glEnd ();													// Done Drawing Top Face

	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Bottom Face
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Top Left Of The Bottom Face
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Top Right Of The Bottom Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Right Of The Bottom Face
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Left Of The Bottom Face
	glEnd ();													// Done Drawing Bottom Face

	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Right Face
		glVertex3f ( 1.0f, -1.0f, -1.0f);						// Bottom Right Of The Right Face
		glVertex3f ( 1.0f,  1.0f, -1.0f);						// Top Right Of The Right Face
		glVertex3f ( 1.0f,  1.0f,  1.0f);						// Top Left Of The Right Face
		glVertex3f ( 1.0f, -1.0f,  1.0f);						// Bottom Left Of The Right Face
	glEnd ();													// Done Drawing Right Face

	glBegin (GL_LINE_LOOP);										// Begin Drawing Line Loop
		// Left Face
		glVertex3f (-1.0f, -1.0f, -1.0f);						// Bottom Left Of The Left Face
		glVertex3f (-1.0f, -1.0f,  1.0f);						// Bottom Right Of The Left Face
		glVertex3f (-1.0f,  1.0f,  1.0f);						// Top Right Of The Left Face
		glVertex3f (-1.0f,  1.0f, -1.0f);						// Top Left Of The Left Face
	glEnd ();													// Done Drawing Left Face

	glFlush ();													// Flush The GL Rendering Pipeline
}
