/*
 * Failprog function
 * Michal Ludvig <michal@logix.cz> (c) 1997-2001
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "mic.h"

void failprog(unsigned char exitcode, const char *exitmsg, ...)
{
   va_list args;

   va_start(args,exitmsg);
   vfprintf(stderr,exitmsg,args); 

   exit(exitcode);
}
