/**************************************
*                                     *
*   GenesisV-006: Textured Quad       *
*   Example - Simple Textured Square  *
*                                     *
**************************************/

#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "GenesisCORE.h"										// Header File For GenesisCORE
#include "GLExt.h"
#include "TextureLoader.h"										// Header File For Texture Loading

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

GL_Window*	g_window;											// Window Structure
Keys*		g_keys;												// Keyboard Structure

// User Defined Variables
float		angle;												// Used To Rotate The Quad
GLuint		texture;											// Storage For One Texture

BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;										// Store Window Structure
	g_keys		= keys;											// Store Keyboard Structure

	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero
	texture		= 0;											// Initialize Texture To Zero

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	// Enable Texturing
	glEnable (GL_TEXTURE_2D);									// Enable 2D Texturing

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

	// Load Texture
	texture = LoadTexture ("wood.jpg");							// Load Wood Texture
	if (texture == 0)											// If Texture Loading Failed
	{
		MessageBox (NULL, "Could Not Load Texture: wood.jpg", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return False
	}

	return TRUE;												// Return TRUE (Initialization Successful)
}

void Deinitialize (void)										// Any User DeInitialization Goes Here
{
	DeleteTexture (texture);									// Delete The Texture
	ShutdownGDIPlus ();											// Shutdown GDI+
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

	angle += (float)(milliseconds) / 8.0f;						// Update angle Based On The Clock
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	glTranslatef (0.0f, 0.0f, -6.0f);							// Translate 6 Units Into The Screen
	glRotatef (angle, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
	glRotatef (angle * 0.5f, 1.0f, 0.0f, 0.0f);				// Rotate On The X-Axis By Half The angle

	// Bind Texture
	glBindTexture (GL_TEXTURE_2D, texture);					// Select Our Texture

	// Draw A Textured Quad
	glBegin (GL_QUADS);											// Begin Drawing Quads
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  0.0f);	// Bottom Left
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  0.0f);	// Bottom Right
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f,  0.0f);	// Top Right
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f,  0.0f);	// Top Left
	glEnd ();													// Done Drawing Quads

	glFlush ();													// Flush The GL Rendering Pipeline
}
