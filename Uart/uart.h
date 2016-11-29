#ifndef UART_H
	#define UART_H

#ifdef _UART_C_
#define _UART_DEF
#else
#define _UART_DEF extern
#endif

#define  OLEN  8                      /* size of serial transmission buffer   */
#define  ILEN  8                      /* size of serial receiving buffer      */

_UART_DEF void init_uart();
_UART_DEF void putstr(unsigned char *pFmt);
_UART_DEF void printf(unsigned char code *pFmt, unsigned int wVal);
_UART_DEF void putchar (unsigned char c); 
_UART_DEF unsigned char get_char();
#endif