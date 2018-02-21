// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_BME280_USER_H
#define	XC_BME280_USER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "./I2C_user.h"

void Bme280_UserInit(void);
int8_t BME280_Data(void);

#endif	/* XC_BME280_USER_H */

