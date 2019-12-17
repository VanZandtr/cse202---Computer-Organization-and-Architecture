/*********************************************************
 * config.h - Configuration data for the driver.c program.
 *********************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* 
 * CPEs for the baseline (naive) version of the rotate function that
 * was handed out to the students. Rd is the measured CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define R64    2.8
#define R128   4.2
#define R256   6.7
#define R512   10.9
#define R1024  13.6

/* 
 * CPEs for the baseline (naive) version of the smooth function that
 * was handed out to the students. Sd is the measure CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define S32    57.8
#define S64    58.0
#define S128   58.0
#define S256   58.2
#define S512   58.1

#endif /* _CONFIG_H_ */
