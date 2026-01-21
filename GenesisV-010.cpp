/**************************************
*   GenesisV-010: Texture Filtering  *
*   Example - Different Filter Modes  *
**************************************/

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GenesisCORE.h"
#include "GLExt.h"
#include "TextureLoader.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#ifndef CDS_FULLSCREEN
#define CDS_FULLSCREEN 4
#endif

GL_Window*	g_window;
Keys*		g_keys;

float		angle;
GLuint		texture;
int			filterMode;											// Current Filter Mode (0=Nearest, 1=Linear)

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angle		= 0.0f;
	texture		= 0;
	filterMode	= 1;												// Start With Linear

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable (GL_TEXTURE_2D);

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

	texture = LoadTexture ("wood.jpg");
	if (texture == 0)
	{
		MessageBox (NULL, "Could Not Load Texture", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void Deinitialize (void)
{
	DeleteTexture (texture);
	ShutdownGDIPlus ();											// Shutdown GDI+
}

void Update (DWORD milliseconds)
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)
		TerminateApplication (g_window);
	if (g_keys->keyDown [VK_F1] == TRUE)
		ToggleFullscreen (g_window);
	if (g_keys->keyDown ['F'] == TRUE)							// Press F To Toggle Filter
	{
		filterMode = 1 - filterMode;							// Toggle Between 0 And 1
		g_keys->keyDown ['F'] = FALSE;							// Reset Key
	}

	angle += (float)(milliseconds) / 8.0f;
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -6.0f);
	glRotatef (angle, 0.0f, 1.0f, 0.0f);

	glBindTexture (GL_TEXTURE_2D, texture);

	// Set Filter Mode
	if (filterMode == 0)
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f, 0.0f);
		glTexCoord2f (3.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, 0.0f);
		glTexCoord2f (3.0f, 3.0f); glVertex3f ( 1.0f,  1.0f, 0.0f);
		glTexCoord2f (0.0f, 3.0f); glVertex3f (-1.0f,  1.0f, 0.0f);
	glEnd ();

	glFlush ();
}
