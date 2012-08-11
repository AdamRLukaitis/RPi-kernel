/*
 * general.c
 *
 */
 
 #include <stdint.h>
 #include "headers/general.h"
 #include "headers/gpio.h"
 #include "headers/asmStart.h"
 #include "headers/framebuffer.h"
 
 #include "headers/console.h"
 
/*
 * Local prototypes
 *
 */

void createHeader(uint32_t *address, uint32_t size);
void createInitialHeader(uint32_t *address);

/*
 * Public methods
 *
 */
 
int string_length(const char* str) {
	const char* s = str;
	while(*s) ++s;
	return s-str;
}


// provides the error notification for the divide functions
void __div0(void) {
	Gpio_SetMorse(1, false);
	Gpio_FlashStatusLed(PAT_D, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_I, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_V, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_I, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_D, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_E, END_OF_WORD);
	Gpio_FlashStatusLed(PAT_0, END_OF_WORD);
	Gpio_FlashStatusLed(PAT_E, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_R, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_R, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_O, END_OF_LETTER);
	Gpio_FlashStatusLed(PAT_R, END_OF_WORD);
}

// Dynamic allocation of memory
bool isInitialised = false;
#define MAGICALLOCATED 0x44414D66								// Dynamically Allocated Memory flag - 'DAMf'
uint32_t* AllocateMemory(uint32_t size) {
	uint32_t* headerNextPointer = &__bss_end__ + 1;
	
	if (0 == size) return (uint32_t*) 0x80000000;	// deliberately cause exception if used
	if(!isInitialised) {
		createInitialHeader(headerNextPointer);
	}
	
	char decimalString[10];
	Fb_WriteString("*  headerNextPointer: ");
	Fb_WriteLine(Gpio_ConvertToHexString((uint32_t)(headerNextPointer), decimalString, 8));
	Fb_WriteString("* *headerNextPointer: ");
	Fb_WriteLine(Gpio_ConvertToHexString((uint32_t)(*headerNextPointer), decimalString, 8));

	Console_WriteMemoryBlockHex((uint32_t)&__bss_end__, (uint32_t)(&__bss_end__ + 0x60) );
 
	bool isFound = false;
	while ((0 != *headerNextPointer) && !isFound) {				// not at end of list or finished
		if (0 == *(headerNextPointer+1)) { 									// not allocated
			uint32_t sizeOfFreeSpace = (*headerNextPointer - (uint32_t)(headerNextPointer) - 2);
			if (size <= sizeOfFreeSpace) { 										// There is space here
				isFound = true;
				if ((size - sizeOfFreeSpace) >= 0x4) {					// Insert new header: we have more than is needed
					createHeader(headerNextPointer, size);
				} 
			}
			headerNextPointer = (uint32_t*)(*headerNextPointer);
		}
	}
	
	Fb_WriteString("*        __bss_end__: ");
	Fb_WriteLine(Gpio_ConvertToHexString((uint32_t)(&__bss_end__), decimalString, 8));

	if (!isFound) { 															// At the last header without finding space
		createHeader(headerNextPointer, size);
	}
	return (headerNextPointer + 2);
}

bool FreeAllocatedMemory(uint32_t* address) {
	if (MAGICALLOCATED == *(address - 1)) {
		*(address - 1) = 0;		
	}

	return true;
}

/*
 * Local methods
 *
 */

// Create a memory header
void createHeader(uint32_t *address, uint32_t size) {
	*(address + size + 2)	= (uint32_t)(address - 1);				// previous
	*(address + size + 3)	= (uint32_t)(*address);						// next
	*(address + size + 4) = 0;															// allocated
	*address = (uint32_t)(address + size + 2);							// prior header
	*(address + 1) = MAGICALLOCATED;												// prior allocation. 
}

// Create the first header
void createInitialHeader(uint32_t *address) {
	*(address - 1) = 0;
	*address = 0;
	*(address + 1) = 0;
}

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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
 
