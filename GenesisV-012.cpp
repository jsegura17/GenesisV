/**************************************
*   GenesisV-012: Multiple Objects   *
*   With Different Textures          *
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

float		cubeAngleX, cubeAngleY;
float		pyramidAngleX, pyramidAngleY;
GLuint		textureWood;
GLuint		textureGrass;

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	cubeAngleX = cubeAngleY = 0.0f;
	pyramidAngleX = pyramidAngleY = 0.0f;
	textureWood = textureGrass = 0;

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable (GL_TEXTURE_2D);

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

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
		TerminateApplication (g_window);
	if (g_keys->keyDown [VK_F1] == TRUE)
		ToggleFullscreen (g_window);

	cubeAngleX += (float)(milliseconds) / 10.0f;
	cubeAngleY += (float)(milliseconds) / 7.0f;
	pyramidAngleX += (float)(milliseconds) / 8.0f;
	pyramidAngleY += (float)(milliseconds) / 12.0f;
}

void DrawCube (void)
{
	glBindTexture (GL_TEXTURE_2D, textureWood);
	glBegin (GL_QUADS);
		// Front
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
		// Back
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		// Top
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
		// Bottom
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		// Right
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		// Left
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
	glEnd ();
}

void DrawPyramid (void)
{
	glBindTexture (GL_TEXTURE_2D, textureGrass);
	glBegin (GL_TRIANGLES);
		// Front
		glTexCoord2f (0.5f, 1.0f); glVertex3f ( 0.0f,  0.5f, 0.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		// Back
		glTexCoord2f (0.5f, 1.0f); glVertex3f ( 0.0f,  0.5f, 0.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
		// Right
		glTexCoord2f (0.5f, 1.0f); glVertex3f ( 0.0f,  0.5f, 0.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		// Left
		glTexCoord2f (0.5f, 1.0f); glVertex3f ( 0.0f,  0.5f, 0.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
	glEnd ();
	// Base
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
	glEnd ();
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -6.0f);

	// Draw Cube
	glPushMatrix ();
	glTranslatef (-1.5f, 0.0f, 0.0f);
	glRotatef (cubeAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef (cubeAngleY, 0.0f, 1.0f, 0.0f);
	DrawCube ();
	glPopMatrix ();

	// Draw Pyramid
	glPushMatrix ();
	glTranslatef (1.5f, 0.0f, 0.0f);
	glRotatef (pyramidAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef (pyramidAngleY, 0.0f, 1.0f, 0.0f);
	DrawPyramid ();
	glPopMatrix ();

	glFlush ();
}
