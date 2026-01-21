/**************************************
*   GenesisV-009: Animated Textures  *
*   Example - Textures With Animation *
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
float		textureOffset;											// Texture Animation Offset
GLuint		texture;

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angle		= 0.0f;
	textureOffset = 0.0f;
	texture		= 0;

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

	angle += (float)(milliseconds) / 8.0f;
	textureOffset += (float)(milliseconds) / 1000.0f;				// Animate Texture Offset
	if (textureOffset > 1.0f) textureOffset -= 1.0f;				// Wrap Around
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -6.0f);
	glRotatef (angle, 0.0f, 1.0f, 0.0f);

	glBindTexture (GL_TEXTURE_2D, texture);

	glBegin (GL_QUADS);
		// Animated Texture Coordinates
		glTexCoord2f (0.0f + textureOffset, 0.0f + textureOffset); glVertex3f (-1.0f, -1.0f, 0.0f);
		glTexCoord2f (2.0f + textureOffset, 0.0f + textureOffset); glVertex3f ( 1.0f, -1.0f, 0.0f);
		glTexCoord2f (2.0f + textureOffset, 2.0f + textureOffset); glVertex3f ( 1.0f,  1.0f, 0.0f);
		glTexCoord2f (0.0f + textureOffset, 2.0f + textureOffset); glVertex3f (-1.0f,  1.0f, 0.0f);
	glEnd ();

	glFlush ();
}
