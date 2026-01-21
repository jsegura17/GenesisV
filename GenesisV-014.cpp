/**************************************
*   GenesisV-014: Complex Scene      *
*   Example - Multiple Textured      *
*   Objects In Scene                  *
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
GLuint		textureWood;
GLuint		textureGrass;
GLuint		textureSet;

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angle		= 0.0f;
	textureWood = textureGrass = textureSet = 0;

	glClearColor (0.2f, 0.2f, 0.3f, 0.5f);
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
	textureSet = LoadTexture ("set-001.jpg");
	if (textureWood == 0 || textureGrass == 0 || textureSet == 0)
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
	DeleteTexture (textureSet);
	ShutdownGDIPlus ();											// Shutdown GDI+
}

void Update (DWORD milliseconds)
{
	if (g_keys->keyDown [VK_ESCAPE] == TRUE)
		TerminateApplication (g_window);
	if (g_keys->keyDown [VK_F1] == TRUE)
		ToggleFullscreen (g_window);

	angle += (float)(milliseconds) / 8.0f;
}

void DrawTileQuad (int tileX, int tileY, float size)
{
	float u1 = tileX / 4.0f;
	float u2 = (tileX + 1) / 4.0f;
	float v1 = tileY / 4.0f;
	float v2 = (tileY + 1) / 4.0f;

	glBegin (GL_QUADS);
		glTexCoord2f (u1, v1); glVertex3f (-size, -size, 0.0f);
		glTexCoord2f (u2, v1); glVertex3f ( size, -size, 0.0f);
		glTexCoord2f (u2, v2); glVertex3f ( size,  size, 0.0f);
		glTexCoord2f (u1, v2); glVertex3f (-size,  size, 0.0f);
	glEnd ();
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -8.0f);
	glRotatef (angle, 0.0f, 1.0f, 0.0f);

	// Draw Ground (Grass)
	glBindTexture (GL_TEXTURE_2D, textureGrass);
	glPushMatrix ();
	glTranslatef (0.0f, -2.0f, 0.0f);
	glRotatef (-90.0f, 1.0f, 0.0f, 0.0f);
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-3.0f, -3.0f, 0.0f);
		glTexCoord2f (4.0f, 0.0f); glVertex3f ( 3.0f, -3.0f, 0.0f);
		glTexCoord2f (4.0f, 4.0f); glVertex3f ( 3.0f,  3.0f, 0.0f);
		glTexCoord2f (0.0f, 4.0f); glVertex3f (-3.0f,  3.0f, 0.0f);
	glEnd ();
	glPopMatrix ();

	// Draw Cube (Wood)
	glBindTexture (GL_TEXTURE_2D, textureWood);
	glPushMatrix ();
	glTranslatef (-1.5f, 0.0f, 0.0f);
	glRotatef (angle * 2.0f, 0.0f, 1.0f, 0.0f);
	// Draw cube faces (simplified - just front face shown)
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
		glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
		glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
	glEnd ();
	glPopMatrix ();

	// Draw Tiles From Set
	glBindTexture (GL_TEXTURE_2D, textureSet);
	glPushMatrix ();
	glTranslatef (1.5f, 0.0f, 0.0f);
	glRotatef (-angle, 0.0f, 1.0f, 0.0f);
	DrawTileQuad (0, 0, 0.5f);
	glPopMatrix ();

	glPushMatrix ();
	glTranslatef (0.0f, 1.5f, 0.0f);
	glRotatef (angle * 1.5f, 0.0f, 1.0f, 0.0f);
	DrawTileQuad (1, 1, 0.4f);
	glPopMatrix ();

	glFlush ();
}
