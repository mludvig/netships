/*
 * ReadN/WriteN/ReadF/WriteF functions
 * Michal Ludvig <michal@logix.cz>
 * License: BSD-like
 * 31 Nov 1996
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readn(int fd, char *buf, int nbytes)
{
	int	nleft, nread;
	
	nleft=nbytes;
	while(nleft>0)
	{
		nread=read(fd, buf, nleft);
		if(nread<0)
			return nread;
		else 
		if (nread==0)
			break;
		nleft -= nread;
		buf += nread;
	}
	return nbytes-nleft;	
}

int writen(int fd, char *buf, int nbytes)
{
	int	nleft, nwritten;
	
	nleft=nbytes;
	while(nleft>0)
	{
		nwritten=write(fd, buf, nleft);
		if(nwritten<0)
			return nwritten;
		else 
		if (nwritten==0)
			break;
		nleft -= nwritten;
		buf += nwritten;
	}
	return nbytes-nleft;	
}

int readf(int sd, char *buf, int maxlen)
{
	int	n,t;
	char	xx[3];
	char	*buft;
	
	if((n=readn(sd,xx,3))!=3)
		return n;
		
	if(sscanf(xx,"%3d",&t)!=1)
		return -2;
		
	buft=(char*)calloc(t+1,1);
	if(buft==NULL)
		return -3;
	
	if((n=readn(sd,buft,t))<0)
	{
		free(buft);
		return -1;
	}
	
	if(n>maxlen)
		n=maxlen;
	
	bcopy(buft, buf, n);
	free(buft);
	
	return n;
}

int writef(int sd, char *buf, int len)
{
	int	n;
	char	*b2;
	
	b2=(char*)calloc(len+3,1);
	
	sprintf(b2,"%03d%s",len,buf);
	
	if((n=writen(sd, b2, len+3))<0)
	{
		free(b2);
		return -1;
	}
	
	free(b2);
	return n-3;
}
