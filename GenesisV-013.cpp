/**************************************
*   GenesisV-013: Textured Lighting  *
*   Example - Textures With Lighting  *
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

float		angleX, angleY;
GLuint		texture;
GLfloat		lightAmbient[4]  = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat		lightDiffuse[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat		lightPosition[4] = {0.0f, 0.0f, 2.0f, 1.0f};

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angleX = angleY = 0.0f;
	texture = 0;

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable (GL_TEXTURE_2D);

	// Enable Lighting
	glEnable (GL_LIGHTING);
	glLightfv (GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv (GL_LIGHT1, GL_POSITION, lightPosition);
	glEnable (GL_LIGHT1);

	// Enable Color Material
	glEnable (GL_COLOR_MATERIAL);
	glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

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

	glBindTexture (GL_TEXTURE_2D, texture);

	glBegin (GL_QUADS);
		// Front Face
		glNormal3f (0.0f, 0.0f, 1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f (0.0f, 0.0f, -1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f (0.0f, 1.0f, 0.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f (0.0f, -1.0f, 0.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		// Right Face
		glNormal3f (1.0f, 0.0f, 0.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f (-1.0f, 0.0f, 0.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-1.0f,  1.0f, -1.0f);
	glEnd ();

	glFlush ();
}
