/*
 * asmStart.h
 *
 */
 
#ifndef _H_ASMSTART
#define _H_ASMSTART

#include <stdint.h>
#include "types.h"

extern void WriteToMemory32 (unsigned int, unsigned int);
extern unsigned int ReadFromMemory32 (unsigned int);
extern void MemoryBarrier (void);
extern void SynchronisationBarrier (void);
extern void DataCacheFlush (void);
extern void DataSynchronisationBarrier (void);
extern void SmallDelay (unsigned int);
extern void VoidCall (void);
extern uint32_t FramebufferMemory;
extern uint32_t LinuxMachineType;
extern uint32_t AtagsAddress;
extern uint32_t EndFrameBuffer;
extern uint32_t _freeMemoryStart;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

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
