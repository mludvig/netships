/*
 * mic.h
 *
 * Michal Ludvig <michal@logix.cz>
 * 2000-07-25
 * License: BSD like
 *
 */

#ifndef __MIC_H__
#define __MIC_H__

#include <stdio.h>
#include <errno.h>
#include "mic_t.h"

#define helparg(x) (((x[0]=='-')||(x[0]=='/'))&&\
                   ((x[1]=='H')||(x[1]=='h')||(x[1]=='?')))

#define PW2(x) ((x)*(x))
#define PW3(x) ((x)*(x)*(x))

#ifdef __cplusplus
extern "C"
{
#endif
	/* print 'exitmsg' to stderr (printf string format) */
	/* and exit program with 'exitcode' */
	void failprog(unsigned char exitcode, const char *exitmsg, ...);
#ifdef __cplusplus
}
#endif


#endif
