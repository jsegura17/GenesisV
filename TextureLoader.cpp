/**************************************
*                                     *
*   TextureLoader.cpp                 *
*   Simple Texture Loading Utility    *
*   For OpenGL - Supports JPG/BMP     *
*   Using Windows GDI+                *
*                                     *
**************************************/

#include "TextureLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>												// Header File For Windows
#include <gl/glu.h>													// Header File For The GLu32 Library
#include <gdiplus.h>												// Header File For GDI+
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

// Global GDI+ token
static ULONG_PTR gdiplusToken = 0;
static int gdiplusRefCount = 0;

// Initialize GDI+ (call before first LoadTexture)
void InitGDIPlus (void)
{
	if (gdiplusRefCount == 0)
	{
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	gdiplusRefCount++;
}

// Shutdown GDI+ (call when done with textures)
void ShutdownGDIPlus (void)
{
	gdiplusRefCount--;
	if (gdiplusRefCount == 0)
	{
		GdiplusShutdown (gdiplusToken);
		gdiplusToken = 0;
	}
}

// Load Texture From JPG/BMP File Using Windows GDI+
GLuint LoadTexture (const char* filename)
{
	GLuint textureID = 0;											// Texture ID
	unsigned char* imageData = NULL;								// Image Data
	int width = 0, height = 0;										// Image Dimensions

	// Initialize GDI+
	InitGDIPlus ();

	// Build File Path
	char fullPath[512];
	char exePath[512];
	
	// Get Executable Directory
	GetModuleFileName (NULL, exePath, 512);						// Get Full Path To Executable
	char* lastSlash = strrchr (exePath, '\\');					// Find Last Backslash
	if (lastSlash != NULL)
	{
		*(lastSlash + 1) = '\0';									// Terminate String At Last Backslash
	}
	
	// Try multiple paths
	sprintf (fullPath, "%simages\\%s", exePath, filename);			// First: images folder next to executable
	
	// Convert to wide string for GDI+
	WCHAR wfilename[512];
	MultiByteToWideChar (CP_ACP, 0, fullPath, -1, wfilename, 512);

	// Load Image Using GDI+
	Image* image = new Image (wfilename);
	if (image->GetLastStatus () != Ok)
	{
		// Try relative path
		sprintf (fullPath, "images\\%s", filename);
		MultiByteToWideChar (CP_ACP, 0, fullPath, -1, wfilename, 512);
		delete image;
		image = new Image (wfilename);
		if (image->GetLastStatus () != Ok)
		{
			// Try direct path
			MultiByteToWideChar (CP_ACP, 0, filename, -1, wfilename, 512);
			delete image;
			image = new Image (wfilename);
			if (image->GetLastStatus () != Ok)
			{
				char errorMsg[1024];
				sprintf (errorMsg, "Could not load texture:\n\n%s\n\nTried:\n- %simages\\%s\n- images\\%s\n- %s", 
					filename, exePath, filename, filename, filename);
				MessageBox (NULL, errorMsg, "Texture Load Error", MB_OK | MB_ICONEXCLAMATION);
				delete image;
				return 0;											// Return 0 If File Not Found
			}
		}
	}

	// Get Image Dimensions
	width = image->GetWidth ();
	height = image->GetHeight ();

	if (width == 0 || height == 0)
	{
		MessageBox (NULL, "Invalid image dimensions", "Texture Load Error", MB_OK | MB_ICONEXCLAMATION);
		delete image;
		return 0;
	}

	// Allocate Memory For Image Data
	imageData = (unsigned char*)malloc (width * height * 3);		// RGB = 3 Bytes Per Pixel
	if (!imageData)
	{
		MessageBox (NULL, "Out of memory", "Texture Load Error", MB_OK | MB_ICONEXCLAMATION);
		delete image;
		return 0;
	}

	// Convert To Bitmap
	Bitmap* bitmap = new Bitmap (width, height, PixelFormat24bppRGB);
	if (!bitmap)
	{
		free (imageData);
		delete image;
		return 0;
	}

	Graphics* graphics = Graphics::FromImage (bitmap);
	if (!graphics)
	{
		delete bitmap;
		free (imageData);
		delete image;
		return 0;
	}

	graphics->DrawImage (image, 0, 0, width, height);
	delete graphics;

	// Get Bitmap Data
	BitmapData bitmapData;
	Rect rect (0, 0, width, height);
	if (bitmap->LockBits (&rect, ImageLockModeRead, PixelFormat24bppRGB, &bitmapData) != Ok)
	{
		delete bitmap;
		free (imageData);
		delete image;
		return 0;
	}

	// Copy Data (BGR to RGB conversion)
	unsigned char* src = (unsigned char*)bitmapData.Scan0;
	unsigned char* dst = imageData;
	int stride = bitmapData.Stride;
	
	for (int y = 0; y < height; y++)
	{
		unsigned char* rowSrc = src + (y * stride);
		unsigned char* rowDst = dst + (y * width * 3);
		for (int x = 0; x < width; x++)
		{
			rowDst[x * 3 + 0] = rowSrc[x * 3 + 2];					// R
			rowDst[x * 3 + 1] = rowSrc[x * 3 + 1];					// G
			rowDst[x * 3 + 2] = rowSrc[x * 3 + 0];					// B
		}
	}

	bitmap->UnlockBits (&bitmapData);

	// Generate OpenGL Texture
	glGenTextures (1, &textureID);									// Generate One Texture ID
	glBindTexture (GL_TEXTURE_2D, textureID);						// Bind The Texture

	// Give The Image To OpenGL
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

	// Set Texture Parameters
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Clean Up
	free (imageData);
	delete bitmap;
	delete image;

	return textureID;												// Return The Texture ID
}

GLuint LoadTextureSize (const char* filename, int width, int height)
{
	// For now, just call LoadTexture
	// This can be extended for specific size requirements
	return LoadTexture (filename);
}

void DeleteTexture (GLuint textureID)
{
	if (textureID != 0)
	{
		glDeleteTextures (1, &textureID);							// Delete The Texture
	}
}

// Load Texture Tile From set-001.jpg (4x4 grid)
GLuint LoadTextureTile (const char* filename, int tileX, int tileY)
{
	// For now, load full texture and use texture coordinates
	// This is a simplified version - full implementation would extract the tile
	GLuint textureID = LoadTexture (filename);
	
	// Note: Full implementation would extract the specific tile from the 4x4 grid
	// For now, we'll use texture coordinates to show the tile
	
	return textureID;
}
