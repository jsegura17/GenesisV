/**************************************
*   GenesisV-015: Advanced Textures  *
*   Example - Complex Texture Effects *
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
float		textureScale;										// Texture Scaling
GLuint		textureWood;
GLuint		textureSet;
int			blendMode;											// Blend Mode (0=Replace, 1=Modulate)

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angleX = angleY = 0.0f;
	textureScale = 1.0f;
	textureWood = textureSet = 0;
	blendMode = 0;

	glClearColor (0.1f, 0.1f, 0.2f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable (GL_TEXTURE_2D);

	// Enable Blending
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

	textureWood = LoadTexture ("wood.jpg");
	textureSet = LoadTexture ("set-001.jpg");
	if (textureWood == 0 || textureSet == 0)
	{
		MessageBox (NULL, "Could Not Load Textures", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void Deinitialize (void)
{
	DeleteTexture (textureWood);
	DeleteTexture (textureSet);
	ShutdownGDIPlus ();											// Shutdown GDI+
}

void Update (DWORD milliseconds)
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)
		TerminateApplication (g_window);
	if (g_keys->keyDown [VK_F1] == TRUE)
		ToggleFullscreen (g_window);
	if (g_keys->keyDown ['B'] == TRUE)
	{
		blendMode = 1 - blendMode;
		g_keys->keyDown ['B'] = FALSE;
	}
	if (g_keys->keyDown ['+'] == TRUE)
	{
		textureScale += 0.1f;
		if (textureScale > 5.0f) textureScale = 5.0f;
		g_keys->keyDown ['+'] = FALSE;
	}
	if (g_keys->keyDown ['-'] == TRUE)
	{
		textureScale -= 0.1f;
		if (textureScale < 0.1f) textureScale = 0.1f;
		g_keys->keyDown ['-'] = FALSE;
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

	// Set Texture Environment
	if (blendMode == 0)
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Draw Cube With Wood Texture
	glBindTexture (GL_TEXTURE_2D, textureWood);
	glBegin (GL_QUADS);
		// Front
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (textureScale, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (textureScale, textureScale); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, textureScale); glVertex3f (-1.0f,  1.0f,  1.0f);
		// Back
		glTexCoord2f (textureScale, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (textureScale, textureScale); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, textureScale); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		// Top
		glTexCoord2f (0.0f, textureScale); glVertex3f (-1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (textureScale, 0.0f); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (textureScale, textureScale); glVertex3f ( 1.0f,  1.0f, -1.0f);
		// Bottom
		glTexCoord2f (textureScale, textureScale); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, textureScale); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		glTexCoord2f (textureScale, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		// Right
		glTexCoord2f (textureScale, 0.0f); glVertex3f ( 1.0f, -1.0f, -1.0f);
		glTexCoord2f (textureScale, textureScale); glVertex3f ( 1.0f,  1.0f, -1.0f);
		glTexCoord2f (0.0f, textureScale); glVertex3f ( 1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, 0.0f); glVertex3f ( 1.0f, -1.0f,  1.0f);
		// Left
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-1.0f, -1.0f, -1.0f);
		glTexCoord2f (textureScale, 0.0f); glVertex3f (-1.0f, -1.0f,  1.0f);
		glTexCoord2f (textureScale, textureScale); glVertex3f (-1.0f,  1.0f,  1.0f);
		glTexCoord2f (0.0f, textureScale); glVertex3f (-1.0f,  1.0f, -1.0f);
	glEnd ();

	// Draw Tiles Around
	glBindTexture (GL_TEXTURE_2D, textureSet);
	glPushMatrix ();
	glTranslatef (2.5f, 0.0f, 0.0f);
	glRotatef (angleY * 2.0f, 0.0f, 1.0f, 0.0f);
	float u1 = 0.0f, u2 = 0.25f, v1 = 0.0f, v2 = 0.25f;
	glBegin (GL_QUADS);
		glTexCoord2f (u1, v1); glVertex3f (-0.3f, -0.3f, 0.0f);
		glTexCoord2f (u2, v1); glVertex3f ( 0.3f, -0.3f, 0.0f);
		glTexCoord2f (u2, v2); glVertex3f ( 0.3f,  0.3f, 0.0f);
		glTexCoord2f (u1, v2); glVertex3f (-0.3f,  0.3f, 0.0f);
	glEnd ();
	glPopMatrix ();

	glFlush ();
}
