/**************************************
*   GenesisV-011: Texture Tiles       *
*   Example - Using set-001.jpg      *
*   Grid 4x4 Tiles                    *
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
GLuint		textureSet;											// Texture Set (4x4 grid)

BOOL Initialize (GL_Window* window, Keys* keys)
{
	g_window	= window;
	g_keys		= keys;
	angleX		= 0.0f;
	angleY		= 0.0f;
	textureSet	= 0;

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable (GL_TEXTURE_2D);

	// Initialize GDI+ for texture loading
	InitGDIPlus ();												// Initialize GDI+ For Texture Loading

	textureSet = LoadTexture ("set-001.jpg");
	if (textureSet == 0)
	{
		MessageBox (NULL, "Could Not Load Texture: set-001.jpg", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void Deinitialize (void)
{
	DeleteTexture (textureSet);
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

void DrawTile (int tileX, int tileY)								// Draw A Tile From 4x4 Grid
{
	float u1 = tileX / 4.0f;										// Left U Coordinate
	float u2 = (tileX + 1) / 4.0f;									// Right U Coordinate
	float v1 = tileY / 4.0f;										// Bottom V Coordinate
	float v2 = (tileY + 1) / 4.0f;									// Top V Coordinate

	glTexCoord2f (u1, v1); glVertex3f (-0.5f, -0.5f, 0.0f);
	glTexCoord2f (u2, v1); glVertex3f ( 0.5f, -0.5f, 0.0f);
	glTexCoord2f (u2, v2); glVertex3f ( 0.5f,  0.5f, 0.0f);
	glTexCoord2f (u1, v2); glVertex3f (-0.5f,  0.5f, 0.0f);
}

void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, -6.0f);
	glRotatef (angleX, 1.0f, 0.0f, 0.0f);
	glRotatef (angleY, 0.0f, 1.0f, 0.0f);

	glBindTexture (GL_TEXTURE_2D, textureSet);

	// Draw 4 Different Tiles From The Set
	// Tile (0,0) - Top Left
	glPushMatrix ();
	glTranslatef (-1.0f, 1.0f, 0.0f);
	glBegin (GL_QUADS);
		DrawTile (0, 0);
	glEnd ();
	glPopMatrix ();

	// Tile (1,0) - Top Right
	glPushMatrix ();
	glTranslatef (1.0f, 1.0f, 0.0f);
	glBegin (GL_QUADS);
		DrawTile (1, 0);
	glEnd ();
	glPopMatrix ();

	// Tile (0,1) - Bottom Left
	glPushMatrix ();
	glTranslatef (-1.0f, -1.0f, 0.0f);
	glBegin (GL_QUADS);
		DrawTile (0, 1);
	glEnd ();
	glPopMatrix ();

	// Tile (1,1) - Bottom Right
	glPushMatrix ();
	glTranslatef (1.0f, -1.0f, 0.0f);
	glBegin (GL_QUADS);
		DrawTile (1, 1);
	glEnd ();
	glPopMatrix ();

	glFlush ();
}
