/*
 * Header for fmesg.c functions
 * Michal Ludvig <michal@logix.cz>
 * License: BSD-like
 * 06 Dec 1996
 */

#ifndef __FMESG_H_MIC_
#define __FMESG_H_MIC_

#ifdef __cplusplus
extern "C"
{
#endif
	
/* create formatted string from cmdn and arg, 
   and store it into res, and return as result */
char *fmencode(char *res, int cmdn, const char *arg);

/* parse src and return FN_????. arg contains rest of recvd. string */
int fmdecode(const char *src, char *arg);

/* create and send formatted string to fd */
int fmsend(int fd, int cmdn, const char *arg);

/* receive and parse formatted string form fd */
int fmrecv(int fd, char *arg, int maxlen);

#ifdef __cplusplus
}
#endif

#endif
