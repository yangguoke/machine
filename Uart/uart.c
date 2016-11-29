#define _UART_C_
#include "..\\Includes.h"

unsigned char ostart;                /* transmission buffer start index      */
unsigned char oend;                  /* transmission buffer end index        */

unsigned char  istart;                /* receiving buffer start index         */
unsigned char  iend;                  /* receiving buffer end index           */

unsigned char  outbuf[OLEN];          /* storage for transmission buffer      */
unsigned char  inbuf[ILEN];           /* storage for receiving buffer         */

unsigned char  receive_data;

bit   sendfull;                       /* flag: marks transmit buffer full     */
bit   sendactive;                     /* flag: marks transmitter active       */
bit   sendstop;                       /* flag: marks XOFF character           */
bit	start_trans;
bit	char_rx;
/******************************************************************************/
/*       putbuf:  write a character to SBUF or transmission buffer            */
/******************************************************************************/
void putbuf (char c)  
{
  	if (!sendfull)  
  	{                   
	  	/* transmit only if buffer not full     */
	    	if (!sendactive && !sendstop)  {  /* if transmitter not active:           */
		      sendactive = 1;                 /* transfer the first character direct  */
		      SBUF = c;                       /* to SBUF to start transmission        */
	    	}
	    	else  {                           /* otherwize:                           */

		// this cause a deadlock
		// consider that :
		//   if we just set SBUF above, and then
		//   quickly changed	oend, the TI interrupt will cause
		//	a send,<maybe the outbuf has not yet be fed , so send bad char out> and ++ostart, and then
		// here we consider that oend=ostart, so sendfull =1
		// but this is not the correct thing.
			ES=0;		// this is import
	      		outbuf[oend++ & (OLEN-1)] = c;  		/* transfer char to transmission buffer */
	      		if (((oend ^ ostart) & (OLEN-1)) == 0)
	      			sendfull = 1;
	     	ES=1;
	    	}                                 /* set flag if buffer is full           */
  	}
}

void IntToStr( unsigned int wVal, unsigned char ucBase, unsigned char* pBuf )
{
    bit bShowZero = 0;
    unsigned int wDivider;
    unsigned char ucDisp;

    if( 0 == wVal )
    {
        pBuf[0] = '0';
        pBuf[1] = '\0';
        return;
    }

    if( 16 == ucBase )
        wDivider = 0x1000;
    else
        wDivider = 10000;

    while( wDivider )
    {
        ucDisp = wVal/wDivider;
        wVal = wVal%wDivider;

        if( ucDisp )
            bShowZero = 1;

        if( ucDisp || bShowZero )
        {
            if( ucDisp < 10 )
                *pBuf = '0' + ucDisp;
            else
                *pBuf = 'A' + ucDisp - 10;
            pBuf ++;
        }

        if( 16 == ucBase )
            wDivider /= 0x10;
        else
            wDivider /= 10;
    }
    *pBuf = '\0';
}

void putstr(unsigned char *pFmt)
{
    unsigned char ucBff; // character buffer

    while (1)
    {
         ucBff = *pFmt; // get a character
         if (ucBff == 0x00) // check end of string
             break;

         putchar(ucBff); // put a character

         pFmt++; // next
    } // while
}

unsigned char s_Buf[6];
void printf(unsigned char code *pFmt, unsigned int wVal)
{
    unsigned int ucBff;

    while( ucBff = *(pFmt++) )
    {
        if(ucBff == '%') // check special case
        {
            switch( *(pFmt++) ) // check next character
            {
                case 'x': // hexadecimal number
                case 'X':
                    IntToStr( wVal, 16, s_Buf );
                    putstr( s_Buf );
                    break;
                case 'd': // decimal number
                case 'i':
                    IntToStr( wVal, 10, s_Buf );
                    putstr( s_Buf );
                    break;
            } // switch
        }
        else // general
            putchar(ucBff); // put a character
    } // while
}

/******************************************************************************/
/*       putchar:  interrupt controlled putchar function                      */
/******************************************************************************/
void putchar (unsigned char c)  
{
  while (sendfull)  {                 /* wait for transmission buffer empty   */
  	;
  }
  putbuf (c);                         /* send character                       */
}

unsigned char get_char()
{
	#if 1
	return receive_data;
	#else
	unsigned char c;
	c=inbuf[istart ++];
	istart&=(ILEN-1);
	return c;
	#endif
}

void flush_serial_in()
{
	ES=0;
	istart=iend=0;
	ES=1;
}

void init_uart()
{
   iend=0;
   istart=0;
   sendactive=0;
   sendstop=0;
   start_trans=0;
   sendfull=0;	

   SCON=0x50; //配置串口为模式1
   TMOD|=0x20;
   PCON =0x00;
   TH1=0xFD;
   TL1=0xFD;
   ES=0;
   TI=0;
   TR1=1;

   char_rx=0;
   flush_serial_in();
   putstr("dbg start\r\n");
}

void uart() interrupt 4
{
	unsigned char c;
  	if (RI)  {                         /* if receiver interrupt                */
	    c = SBUF;                 /* read character                        */
	    RI = 0;                      /* clear interrupt request flag     */
		#if 1
		receive_data=c;
		#else
		 if (((iend +1)&( ILEN-1)) != istart)  {
	          	inbuf[iend] = c;
	          	char_rx=1;
			iend++;
			iend&=(ILEN-1);
	        }
		#endif
  	}

	  if (TI)
	  {          /* if transmitter interrupt              */
	    	TI = 0;                          /* clear interrupt request flag          */
	    	if (sendfull||ostart != oend)  {           /* if characters in buffer and           */
		      if (!sendstop)  {              /* if not Control+S received             */
		        SBUF = outbuf[ostart++ & (OLEN-1)];      /* transmit character        */
		        sendfull = 0;                /* clear 'sendfull' flag                 */
		                                    	 /* if task waiting: signal ready         */
		      }
    		}
    		else sendactive = 0;             /* if all transmitted clear 'sendactive' */
	  }

}