/*
 * Formatted-message handler functions
 * Michal Ludvig <micha@logix.cz>
 * BSD-like license
 * 06 Dec 1996
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fmesg.h"
#include "rw.h"

#define	MAXLEN	1000

int fmdecode(const char *src, char *arg)
{
	char	cmd[5];
	int	i;
	
	strncpy(cmd,src,4);
	cmd[4]=0;

	if(arg!=NULL)
	{
		if(strlen(src)>4)
			strcpy(arg, &src[4]);
		else
			arg[0]=0;
	}
	
	sscanf(cmd,"C%3d",&i);
	return i;
}

int fmrecv(int fd, char *arg, int maxlen)
{
	char	buf[MAXLEN];
	int	n;
	
	n=maxlen+4;
	
	if(n>MAXLEN) n=MAXLEN;
	
	if(readf(fd, buf, n)<1)
		return -1;
	else
		return fmdecode(buf, arg);
}

char *fmencode(char *res, int cmdn, const char *arg)
{
	static char		buf[MAXLEN];

	sprintf(buf,"C%03d%s",cmdn,(arg==NULL?"\0":arg));
	
	if(res!=NULL)
		strcpy(res, buf);

	if(buf[0]==0)	/* res[0] == 0, because of prev if !!! */
		return NULL;
	else
		return buf;
}

int fmsend(int fd, int cmdn, const char *arg)
{
	char	*ptr;
	
	if((ptr=fmencode(NULL, cmdn, arg))==NULL)
		return 0;
	else
		return writef(fd, ptr, strlen(ptr));
}
