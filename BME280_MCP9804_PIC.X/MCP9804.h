
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_MCP9804_H
#define	XC_HEADER_MCP9804_H

#include <stdint.h>
#include <xc.h> // include processor files - each processor file is guarded.  

#include "./I2C_user.h"


#define MCP9804_DEVICE_ADDR          0x18

#define MCP9804_ADDR_T_CONFIG        0x01
#define MCP9804_ADDR_T_UPPER         0x02
#define MCP9804_ADDR_T_LOWER         0x03
#define MCP9804_ADDR_T_CRIT          0x04
#define MCP9804_ADDR_TEMPERATURE     0x05
#define MCP9804_ADDR_MANUFACTURE_ID  0x06
#define MCP9804_ADDR_DEVICE_ID       0x07

#define MCP9804_PARAM_T_UPPER_H       0x01
#define MCP9804_PARAM_T_UPPER_L       0x60  // 22c
#define MCP9804_PARAM_T_LOWER_H       0x01
#define MCP9804_PARAM_T_LOWER_L       0x00  // 16c
#define MCP9804_PARAM_T_CRIT_H       0x01
//#define MCP9804_PARAM_T_CRIT_L       0xe0  // 30c
#define MCP9804_PARAM_T_CRIT_L       0x70  // 23c


void MCP9804_IdRead(void);
void MCP9804_Temperature(void);
void MCP9804_SetTupper(void);
void MCP9804_SetTlower(void);
void MCP9804_SetTcrit(void);
void MCP9804_ConfigRead(void);

#endif	/* XC_HEADER_MCP9804_H */

