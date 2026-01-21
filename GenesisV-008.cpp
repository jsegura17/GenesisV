/**************************************
*                                     *
*   GenesisV-008: Multiple Textures  *
*   Example - Cube With Different     *
*   Textures On Each Face             *
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

#ifndef CDS_FULLSCREEN
#define CDS_FULLSCREEN 4
#endif

GL_Window*	g_window;
Keys*		g_keys;

// User Defined Variables
float		angleX;
float		angleY;
GLuint		textureWood;										// Wood Texture
GLuint		textureGrass;										// Grass Texture

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;

	angleX		= 0.0f;
	angleY		= 0.0f;
	textureWood	= 0;
	textureGrass = 0;

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable (GL_TEXTURE_2D);

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

	// Load Textures
	textureWood = LoadTexture ("wood.jpg");
	textureGrass = LoadTexture ("grass.jpg");
	
	if (textureWood == 0 || textureGrass == 0)
	{
		MessageBox (NULL, "Could Not Load Textures", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void Deinitialize (void)
{
	DeleteTexture (textureWood);
	DeleteTexture (textureGrass);
	ShutdownGDIPlus ();											// Shutdown GDI+
}

void Update (DWORD milliseconds)
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)
	{
		TerminateApplication (g_window);
	}

	if (g_keys->keyDown [VK_F1] == TRUE)
	{
		ToggleFullscreen (g_window);
	}

	angleX += (float)(milliseconds) / 10.0f;
	angleY += (float)(milliseconds) / 7.0f;
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -6.0f);
	glRotatef (angleX, 1.0f, 0.0f, 0.0f);
	glRotatef (angleY, 0.0f, 1.0f, 0.0f);

	glBegin (GL_QUADS);
		// Front Face - Wood
		glBindTexture (GL_TEXTURE_2D, textureWood);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f,  1.0f);

		// Back Face - Wood
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);

		// Top Face - Grass
		glBindTexture (GL_TEXTURE_2D, textureGrass);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);

		// Bottom Face - Wood
		glBindTexture (GL_TEXTURE_2D, textureWood);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);

		// Right Face - Wood
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);

		// Left Face - Wood
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);

	glEnd ();

	glFlush ();
}
