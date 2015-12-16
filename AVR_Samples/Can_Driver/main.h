
// ----------------------------------------------------------------------------
/* Copyright (c) 2015 Elementz Engineers Guild Pvt Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------

#ifndef _MAIN_H___
#define _MAIN_H___

#define clock_frequency     8000000
#define microseconds        clock_frequency/1000000
#define milliseconds        clock_frequency/1000


#define    BIT7    0x80
#define    BIT6    0x40
#define    BIT5    0x20
#define    BIT4    0x10
#define    BIT3    0x08
#define    BIT2    0x04
#define    BIT1    0x02
#define    BIT0    0x01

#define BAUD_2400     207
#define BAUD_4800     103
#define BAUD_9600     51
#define BAUD_19200    25
#define BAUD_38400    12
#define BAUD_57600    8
#define BAUD_115200   3

#define SUCCESS     1
#define FAIL        0
//void _delay_ms(long no_milliseconds);
//void _delay_us(long no_microseconds);


#endif /* _MAIN_H___ */


