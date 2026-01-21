/**************************************
*                                     *
*   GenesisV-005: Multiple Objects   *
*   Example - Cube and Pyramid        *
*   Rotating At Different Speeds     *
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
float		cubeAngleX;											// Used To Rotate Cube On The X-Axis
float		cubeAngleY;											// Used To Rotate Cube On The Y-Axis
float		pyramidAngleX;										// Used To Rotate Pyramid On The X-Axis
float		pyramidAngleY;										// Used To Rotate Pyramid On The Y-Axis

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;										// Store Window Structure
	g_keys		= keys;											// Store Keyboard Structure

	// Start Of User Initialization
	cubeAngleX		= 0.0f;										// Set Starting Cube X Angle To Zero
	cubeAngleY		= 0.0f;										// Set Starting Cube Y Angle To Zero
	pyramidAngleX	= 0.0f;										// Set Starting Pyramid X Angle To Zero
	pyramidAngleY	= 0.0f;										// Set Starting Pyramid Y Angle To Zero

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

	// Update Cube Rotation Angles
	cubeAngleX += (float)(milliseconds) / 10.0f;				// Update Cube X Angle Based On The Clock
	cubeAngleY += (float)(milliseconds) / 7.0f;				// Update Cube Y Angle Based On The Clock

	// Update Pyramid Rotation Angles (Different Speed)
	pyramidAngleX += (float)(milliseconds) / 8.0f;				// Update Pyramid X Angle Based On The Clock
	pyramidAngleY += (float)(milliseconds) / 12.0f;			// Update Pyramid Y Angle Based On The Clock
}

void DrawCube (void)											// Function To Draw A Colored Cube
{
	glBegin (GL_QUADS);											// Begin Drawing Quads

		// Front Face (Red)
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Bottom Left Of The Front Face
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Bottom Right Of The Front Face
		glVertex3f ( 0.5f,  0.5f,  0.5f);						// Top Right Of The Front Face
		glVertex3f (-0.5f,  0.5f,  0.5f);						// Top Left Of The Front Face

		// Back Face (Green)
		glColor3f (0.0f, 1.0f, 0.0f);							// Set Color To Green
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Bottom Left Of The Back Face
		glVertex3f (-0.5f,  0.5f, -0.5f);						// Top Left Of The Back Face
		glVertex3f ( 0.5f,  0.5f, -0.5f);						// Top Right Of The Back Face
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Bottom Right Of The Back Face

		// Top Face (Blue)
		glColor3f (0.0f, 0.0f, 1.0f);							// Set Color To Blue
		glVertex3f (-0.5f,  0.5f, -0.5f);						// Top Left Of The Top Face
		glVertex3f (-0.5f,  0.5f,  0.5f);						// Bottom Left Of The Top Face
		glVertex3f ( 0.5f,  0.5f,  0.5f);						// Bottom Right Of The Top Face
		glVertex3f ( 0.5f,  0.5f, -0.5f);						// Top Right Of The Top Face

		// Bottom Face (Yellow)
		glColor3f (1.0f, 1.0f, 0.0f);							// Set Color To Yellow
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Top Left Of The Bottom Face
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Top Right Of The Bottom Face
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Bottom Right Of The Bottom Face
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Bottom Left Of The Bottom Face

		// Right Face (Magenta)
		glColor3f (1.0f, 0.0f, 1.0f);							// Set Color To Magenta
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Bottom Right Of The Right Face
		glVertex3f ( 0.5f,  0.5f, -0.5f);						// Top Right Of The Right Face
		glVertex3f ( 0.5f,  0.5f,  0.5f);						// Top Left Of The Right Face
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Bottom Left Of The Right Face

		// Left Face (Cyan)
		glColor3f (0.0f, 1.0f, 1.0f);							// Set Color To Cyan
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Bottom Left Of The Left Face
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Bottom Right Of The Left Face
		glVertex3f (-0.5f,  0.5f,  0.5f);						// Top Right Of The Left Face
		glVertex3f (-0.5f,  0.5f, -0.5f);						// Top Left Of The Left Face

	glEnd ();													// Done Drawing Quads
}

void DrawPyramid (void)										// Function To Draw A Colored Pyramid
{
	glBegin (GL_TRIANGLES);									// Begin Drawing Triangles

		// Front Face
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f ( 0.0f,  0.5f, 0.0f);						// Top Vertex
		glColor3f (0.0f, 1.0f, 0.0f);							// Set Color To Green
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Bottom Left Vertex
		glColor3f (0.0f, 0.0f, 1.0f);							// Set Color To Blue
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Bottom Right Vertex

		// Back Face
		glColor3f (1.0f, 1.0f, 0.0f);							// Set Color To Yellow
		glVertex3f ( 0.0f,  0.5f, 0.0f);						// Top Vertex
		glColor3f (0.0f, 1.0f, 1.0f);							// Set Color To Cyan
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Bottom Right Vertex
		glColor3f (1.0f, 0.0f, 1.0f);							// Set Color To Magenta
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Bottom Left Vertex

		// Right Face
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f ( 0.0f,  0.5f, 0.0f);						// Top Vertex
		glColor3f (0.0f, 0.0f, 1.0f);							// Set Color To Blue
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Bottom Right Vertex
		glColor3f (1.0f, 0.0f, 1.0f);							// Set Color To Magenta
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Bottom Left Vertex

		// Left Face
		glColor3f (0.0f, 1.0f, 0.0f);							// Set Color To Green
		glVertex3f ( 0.0f,  0.5f, 0.0f);						// Top Vertex
		glColor3f (0.0f, 1.0f, 1.0f);							// Set Color To Cyan
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Bottom Left Vertex
		glColor3f (1.0f, 0.0f, 0.0f);							// Set Color To Red
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Bottom Right Vertex

	glEnd ();													// Done Drawing Triangles

	// Draw Base (Square)
	glBegin (GL_QUADS);											// Begin Drawing Quads
		glColor3f (1.0f, 1.0f, 1.0f);							// Set Color To White
		glVertex3f (-0.5f, -0.5f,  0.5f);						// Top Left
		glVertex3f ( 0.5f, -0.5f,  0.5f);						// Top Right
		glVertex3f ( 0.5f, -0.5f, -0.5f);						// Bottom Right
		glVertex3f (-0.5f, -0.5f, -0.5f);						// Bottom Left
	glEnd ();													// Done Drawing Quads
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	glTranslatef (0.0f, 0.0f, -6.0f);							// Translate 6 Units Into The Screen

	// Draw Cube On The Left
	glPushMatrix ();												// Save Current Matrix
	glTranslatef (-1.5f, 0.0f, 0.0f);							// Move Left
	glRotatef (cubeAngleX, 1.0f, 0.0f, 0.0f);					// Rotate Cube On The X-Axis
	glRotatef (cubeAngleY, 0.0f, 1.0f, 0.0f);					// Rotate Cube On The Y-Axis
	DrawCube ();												// Draw The Cube
	glPopMatrix ();												// Restore Matrix

	// Draw Pyramid On The Right
	glPushMatrix ();												// Save Current Matrix
	glTranslatef (1.5f, 0.0f, 0.0f);							// Move Right
	glRotatef (pyramidAngleX, 1.0f, 0.0f, 0.0f);				// Rotate Pyramid On The X-Axis
	glRotatef (pyramidAngleY, 0.0f, 1.0f, 0.0f);				// Rotate Pyramid On The Y-Axis
	DrawPyramid ();												// Draw The Pyramid
	glPopMatrix ();												// Restore Matrix

	glFlush ();													// Flush The GL Rendering Pipeline
}
