
#define _I2C_DRV_C_
#include "..\\Includes.h"

#define SPEEDUP_I2C
#define TRY_COUNT		 3 	/* retry if no ack */
unsigned char  i2c_op_status;
/******************************************************************
 Local Function Declarations.
*******************************************************************/
static unsigned char 	_writebyte(unsigned char c);
static unsigned char  	_ack(  unsigned char mode);
static unsigned char	_readbyte();

/****************************************************
  Write a byte to the i2c device specified by
  its device id.
 
  arguments:
	dev_id 	device id 
	addr	address to be written ( ignore if < 0 )
	data	data to be written
 
  return:
	0	okay (got ack)
	-1	error (no ack)	
*****************************************************/
#define wait_timer(x)	{_nop_();}

static unsigned char  _writebyte( unsigned char c)
{
#ifdef SPEEDUP_I2C

	if(c&0x80){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;
	
	if(c&0x40){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;

	if(c&0x20){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;
	
	if(c&0x10){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;
	if(c&0x08){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;
	
	if(c&0x04){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;

	if(c&0x02){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;
	
	if(c&0x01){
		IIC_DEV_01_SDA=1;
	}
	else{
		IIC_DEV_01_SDA=0;
	}
	_nop_();

	     IIC_DEV_01_SCL=1;
	 //    wait_timer(2);
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
	     IIC_DEV_01_SCL=0;

		IIC_DEV_01_SDA=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();		

	   	c=80;  /* ack start time */
		
            while (c) {
	        //if (!(cptr->SDA_sense())) 
	        if(!IIC_DEV_01_SDA)
		{
			c=1;	
			break;
	        }
		  c--;			  
	    }	    
		IIC_DEV_01_SCL=0;
		_nop_();
		_nop_();
		_nop_();
		_nop_();		
		return c;	

#else
       for (i = 0; i < 8; i++) {
		
            if (c & 0x80) {			/* most significant bit */
			IIC_DEV_01_SDA=1;
	    }
	    else {
			IIC_DEV_01_SDA=0;	
            }
	     wait_timer(2);
	//	_nop_();
	//	_nop_();
	
	     IIC_DEV_01_SCL=1;
	     wait_timer(2);
	//	_nop_();
	//	_nop_();
		
	     IIC_DEV_01_SCL=0;
	
            c <<= 1;
        }
        return _ack(1);			/* get acknowledge */
		
#endif
}

void _nakout()
{
	IIC_DEV_01_SDA=1;   		
	wait_timer(2);
	IIC_DEV_01_SCL=1;	
	wait_timer(2);
	IIC_DEV_01_SCL=0;
	wait_timer(2);	
}

void _ackout()
{
	IIC_DEV_01_SDA=0;   		
	wait_timer(2);
	IIC_DEV_01_SCL=1;	
	wait_timer(2);
	IIC_DEV_01_SCL=0;
	wait_timer(2);	
	IIC_DEV_01_SDA=1;
	
}


/****************************************************
 i2c_readbyte:
        Read a byte from the I2C bus. 
 
        arguments:
		*cptr 	ptr to the current device
			parameters.
        return:    
		b		byte read
*****************************************************/
static unsigned char _readbyte()
{
    	unsigned char b;
	
#ifdef SPEEDUP_I2C
		b=0;

		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x80;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		

		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x40;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
	
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x20;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		
		
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x10;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		
		
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x08;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		
		
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x04;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		

		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x02;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();
		_nop_();		

		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		if(IIC_DEV_01_SDA)
            {
	        b |= 0x01;
            }	
		IIC_DEV_01_SCL=0;	
		_nop_();
		_nop_();

#else
    	unsigned char i;
    b = 0;
    for (i = 0; i < 8; i++) {
	    b <<= 1;
		IIC_DEV_01_SCL=1;
		_nop_();
		_nop_();
		_nop_();		
	//	wait_timer(2);
		if(IIC_DEV_01_SDA)
            {
	        b |= 1;
            }	
	//    else
	 //   {
	 //       b |= 0;
	 //   }		
		IIC_DEV_01_SCL=0;		
    }
#endif	
    return(b);
}

unsigned char I2C_bytewrite( unsigned char slv_addr, unsigned short addr, unsigned char datax)
{
     unsigned char 	i;
     i2c_op_status=0x00;
    for (i = 0; i < TRY_COUNT; i++) 
    {   /* try again if no ack */
	  IIC_DEV_01_SDA=1;
	  IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=0;
	 wait_timer(2);	 
        if(!_writebyte(slv_addr)) /* control byte */
		goto error_write_byte;  
	  if(!_writebyte(addr))          /* word address */
	  	goto error_write_byte;
        if(!_writebyte(datax))            /* data */
		goto error_write_byte;	

	 IIC_DEV_01_SCL=0;	
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 wait_timer(2);

	 IIC_DEV_01_SDA=1;
        return(1);
        
error_write_byte:
	 IIC_DEV_01_SCL=0;	
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 wait_timer(2);	 
	 IIC_DEV_01_SDA=1;
	
//	 putstr("x wr err\r\n");
    } 
stop_wrbyte:
	 IIC_DEV_01_SCL=0;	
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 IIC_DEV_01_SDA=1;
//	 putstr("x w2 err\r\n");

	i2c_op_status=0xaa;

       return(0); /* timeout without acknowledge after several attempts */
}    

/****************************************************
  Read a byte from the i2c device specified by
  its device id.

  arguments:
	dev_id	device id
	addr	address to be read (ignore if < 0 )

  return:
	>= 0	data read 
	-1	error (no ack)
*****************************************************/
unsigned char  I2C_byteread( unsigned char slv_addr, unsigned short addr)
{
    int 	i;
    unsigned char 	b;
      i2c_op_status=0x00;

    for (i = 0; i < TRY_COUNT; i++) {   /* try again if no ack */

	  IIC_DEV_01_SDA=1;
	  IIC_DEV_01_SCL=1;	
	 wait_timer(2);

	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=0;
	 wait_timer(2);	 

           if(!_writebyte(slv_addr)) /* control byte */
			goto error_read_byte;  
	    if(!_writebyte(addr&0xff))          /* word address */
	    		goto error_read_byte;

	// repeat start
    	 IIC_DEV_01_SCL=1;
	 wait_timer(2);
	 IIC_DEV_01_SDA=1;	

	 wait_timer(2);
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=0;
	 wait_timer(2);	 

        if(!_writebyte(slv_addr|0x01))
        	goto error_read_byte;	
                                        /* control byte: for read */
        b = _readbyte();             /* read one byte of data */
        /* ack clock cycle: no ack is needed for read */
	#ifdef SPEEDUP_I2C
	_nakout();
	#else
        _ack(0);
	#endif
	
	 IIC_DEV_01_SCL=0;	
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 IIC_DEV_01_SDA=1;
        
	return b;
error_read_byte:
	 IIC_DEV_01_SCL=0;	
	 IIC_DEV_01_SDA=0;
	 wait_timer(2);
	 IIC_DEV_01_SCL=1;	
	 wait_timer(2);
	 IIC_DEV_01_SDA=1;

//	putstr("x rd err\r\n");
	continue;
    }
     i2c_op_status=0xbb;
    
    return(0xff);          /* timeout without acknowledge after several attempts */
}

