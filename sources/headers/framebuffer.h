/*
 * framebuffer.h
 *
 */
 
#ifndef _H_FRAMEBUFFER
#define _H_FRAMEBUFFER

#include <stdint.h>
#include "colourStructure.h"

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 10

int	InitFb(void);
void Fb_ClearScreen(void);
void Fb_SetForegroundColour(struct ColourStructure colour);
void Fb_SetBackgroundColour(struct ColourStructure colour);
void Fb_SetCursorPosition(int x_position, int y_position);
void Fb_WriteCharacter(unsigned char putCharacter);
void Fb_WriteString(const char * putString);
struct Cursor Fb_GetCursorPosition(struct Cursor cursor);

#endif

/*
 * Copyright (c) 2012 Ischus Limited www.ischus.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
