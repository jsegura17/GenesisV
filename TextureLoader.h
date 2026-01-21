/**************************************
*                                     *
*   TextureLoader.h                   *
*   Simple Texture Loading Utility    *
*   For OpenGL                        *
*                                     *
**************************************/

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <windows.h>
#include <gl\gl.h>

// Load Texture From JPG File
// Returns Texture ID (0 if failed)
GLuint LoadTexture (const char* filename);

// Load Texture From JPG File With Specific Size
GLuint LoadTextureSize (const char* filename, int width, int height);

// Delete Texture
void DeleteTexture (GLuint textureID);

// Load Texture Tile From set-001.jpg (4x4 grid)
// tileX and tileY are 0-3 (4x4 grid)
GLuint LoadTextureTile (const char* filename, int tileX, int tileY);

// Initialize/Shutdown GDI+ (call these in Initialize/Deinitialize)
void InitGDIPlus (void);
void ShutdownGDIPlus (void);

#endif // TEXTURE_LOADER_H
