/*
 *
 * Support functions for comm
 * Michal Ludvig <michal@logix.cz>
 * 04 Dec 1996, 2000-07-25
 * License: BSD like
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "mic.h"
#include "rw.h"
#include "comm_.h"

char	sbuf[1000];

void prhostent(struct hostent he)
{
	char				*p1;
	struct in_addr	*p2;
	
	printf("Name:\t\t%s\n",he.h_name);
	while((p1=*(he.h_aliases))!=NULL)
	{
		printf("\talias:\t%s\n",p1);
		he.h_aliases++;
	}
	
	printf("\taddrtype = %d, addrlength = %d\n",he.h_addrtype,he.h_length);
	
	if(he.h_addrtype!=AF_INET)
	{
		printf("Unknown address type !!!\n");
		return;
	}
	while((p2 = (struct in_addr*) *he.h_addr_list++) != NULL)
		printf("\tinet addr: %s\n",inet_ntoa(*p2));
}

unsigned long str2inaddr(const char *hname)
{
	struct hostent		*hp;
	struct in_addr		inetaddr;
	
	if((inetaddr.s_addr=inet_addr(hname))==INADDR_NONE)
	/* argument is not a dot-format adress */
	{	/* hope it is a FQDN */
		if((hp=gethostbyname(hname)) == NULL)
			return 0;
		else
			if(hp->h_addrtype!=AF_INET)
				return 0;
			else
				inetaddr.s_addr=((struct in_addr*)hp->h_addr_list[0])->s_addr;
	}
	return inetaddr.s_addr;
}

int initsrv(void)
{
	int						sd,nd,clilen;
	struct sockaddr_in	sa,ca;
	char						hname[100];

	if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
		failprog(1,"f-comm-initsrv-socket\n");
	
	hname[0]=0;
	
	gethostname(hname,100);
	
	bzero((char*)&sa,sizeof(sa));
	sa.sin_family		= AF_INET;
	sa.sin_addr.s_addr= htonl(INADDR_ANY);
	sa.sin_port			= htons(SRV_PORT);
	
	if(bind(sd,(struct sockaddr *) &sa,sizeof(sa))<0)
		failprog(1,"f-comm-initsrv-bind\n");
		
	listen(sd,5);
	
	clilen=sizeof(ca);
	
	sprintf(sbuf,"Waiting for connection (%s/%d) ... ",hname,ntohs(sa.sin_port));
	write(0,sbuf,strlen(sbuf));
	
	nd=accept(sd,(struct sockaddr *) &ca, &clilen);
	
	if(nd < 0)
		failprog(1,"f-comm-initsrv-accept\n");
	
	sprintf(sbuf,"connected: %s\n",inet_ntoa(ca.sin_addr));
	write(0,sbuf,strlen(sbuf));
	
	close(sd);
	
	return nd;
}

int initcli(const char *hnam)
{
	int						sd;
	struct sockaddr_in	sa;
	unsigned long			s_addr;
	
	if((s_addr=str2inaddr(hnam))==0)
		return -1;
	
	if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
		failprog(1,"f-comm-initcli-socket\n");
	
	bzero((char*)&sa,sizeof(sa));
	sa.sin_family		= AF_INET;
	sa.sin_addr.s_addr= s_addr;
	sa.sin_port			= htons(SRV_PORT);
	
	sprintf(sbuf,"Connecting %s/%d ... ",inet_ntoa(sa.sin_addr),ntohs(sa.sin_port));
	write(0,sbuf,strlen(sbuf));
	
	if(connect(sd,(struct sockaddr *) &sa,sizeof(sa))<0)
		failprog(1,"unable to connect (%s) !!!\n",strerror(errno));
		
	sprintf(sbuf,"connected.\n");
	write(0,sbuf,strlen(sbuf));
	
	return sd;
}

