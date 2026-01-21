/**************************************
*                                     *
*   GenesisV-001: Simple Triangle    *
*   Basic Example - Rotating Triangle *
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
float		angle;												// Used To Rotate The Triangle

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;										// Store Window Structure
	g_keys		= keys;											// Store Keyboard Structure

	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero

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

	angle += (float)(milliseconds) / 10.0f;						// Update angle Based On The Clock (Slower Rotation)
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	glTranslatef (0.0f, 0.0f, -6.0f);							// Translate 6 Units Into The Screen
	glRotatef (angle, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle

	// Draw A Simple Triangle
	glBegin (GL_TRIANGLES);										// Begin Drawing Triangles
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f ( 0.0f,  1.0f, 0.0f);						// Top Vertex
		glColor3f (0.0f, 1.0f, 0.0f);							// Set Color To Green
		glVertex3f (-1.0f, -1.0f, 0.0f);						// Bottom Left Vertex
		glColor3f (0.0f, 0.0f, 1.0f);							// Set Color To Blue
		glVertex3f ( 1.0f, -1.0f, 0.0f);						// Bottom Right Vertex
	glEnd ();													// Done Drawing Triangles

	glFlush ();													// Flush The GL Rendering Pipeline
}
