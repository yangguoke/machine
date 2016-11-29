#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#ifdef _I2C_DRV_C_
#define _I2C_DRV_DEF_
#else
#define _I2C_DRV_DEF_ extern 
#endif

_I2C_DRV_DEF_ unsigned char I2C_bytewrite( unsigned char slv, unsigned short addr, unsigned char datax);
_I2C_DRV_DEF_ unsigned char I2C_byteread( unsigned char slv, unsigned short addr);
_I2C_DRV_DEF_ unsigned char read_data;
#endif

