//
// comm class
// Michal Ludvig <michal@logix.cz>
// 22.11.1996, 2000-07-25
// License: BSD like
//

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

#include "fmesg.h"
#include "comm_.h"
#include "mic.h"
#include "ns.h"
#include	"fmtypes.h"

char	sbuf[500];

comm::comm(class info *inf)
{
	k=NULL;		// known
	u=NULL;		// unknown

	connected=0;
	gameover=1;
	
	fillok=0;
	
	info=inf;
}

comm::~comm()
{
	close();
}

void comm::regu(class poolu *pu)
{
	u=pu;
}

void comm::regk(class poolk *pk)
{
	k=pk;
}

int comm::connsrv(int port)
{
	int						sd,nd;
	socklen_t				clilen;
	struct sockaddr_in	sa,ca;
	char						hname[100];
	
	if(!fillok)
		return -7;
	
	if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
		return	-1;
		
	hname[0]=0;
	
	gethostname(hname,100);
	
	bzero((char*)&sa,sizeof(sa));
	sa.sin_family		= AF_INET;
	sa.sin_addr.s_addr= htonl(INADDR_ANY);
	sa.sin_port			= htons(port);
	
	if(bind(sd,(struct sockaddr *) &sa,sizeof(sa))<0)
	{
		::close(sd);
		if(errno==EADDRINUSE)
		{
			sd=conncli("localhost",port);
			return	sd;
		}
		else
			return 	-2;
	}
					
	listen(sd,5);
	
	clilen=sizeof(ca);
	
	sprintf(sbuf,"Waiting for connection (%s/%d) ... ",hname,ntohs(sa.sin_port));
	info->write(sbuf);
	
	nd=accept(sd,(struct sockaddr *) &ca, &clilen);
	
	if(nd < 0)
	{
		::close(sd);
		return nd;
	}
		
	sprintf(sbuf,"connected: %s\n",inet_ntoa(ca.sin_addr));
	info->write(sbuf);
	
	::close(sd);
	
	if(fmrecv(nd,NULL,4)!=FM_CORQ)
		return -1;
	else
		fmsend(nd,FM_COAC,NULL);
	
	connected=1;
	
	myturn=1;
	info->write2(A_BLINK|A_BOLD," Play...");
	
	gameover=0;
	
	this->sd=nd;
	
	return nd;
}

int comm::conncli(const char *name, int port)
{
	int						sd,c;
	struct sockaddr_in	sa;
	unsigned long			s_addr;
	
	if(!fillok)
		return -7;
	
	if((s_addr=str2inaddr(name))==0)
		return -1;
	
	for(;;)
	{
		if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
			return sd;	/* negative */
		
		bzero((char*)&sa,sizeof(sa));
		sa.sin_family		= AF_INET;
		sa.sin_addr.s_addr= s_addr;
		sa.sin_port			= htons(port);
	
		info->writef("Connecting %s/%d ... ",inet_ntoa(sa.sin_addr),ntohs(sa.sin_port));
	
		if(connect(sd,(struct sockaddr *) &sa,sizeof(sa))<0)
		{
			::close(sd);
	
			info->writef(A_BOLD, "unable to connect (%s) !!!\n",strerror(errno));
			info->write("Try again? (press N if not)\n");
			c=getch();

			if((c!='n')&&(c!='N'))
				continue;
			else
				return -2;
		}
		else
			break;
	}
			
	info->write("connected.\n");
	
	fmsend(sd,FM_CORQ,NULL);
	
	if(fmrecv(sd,NULL,4)!=FM_COAC)
		return -1;
	else
	{
		connected=1;
	
		myturn=0;
		gameover=0;
		info->write2(A_BLINK|A_BOLD," Wait...");
		this->sd=sd;
		return sd;
	}
}

int comm::handle(void)
{
	int	n;
	int	x,y;
	
	if((n=fmrecv(sd,buf,MAXLEN))<0)
		return n;
	
	switch (n)
	{
		case	FM_CORQ	:	fmsend(sd,FM_INVL,NULL);	/* unexpected command */
								break;
								
		case	FM_COAC	:	fmsend(sd,FM_INVL,NULL);	/* ------- || ------- */
								break;
								
		case	FM_CCRQ	:	/* printf("Close Request\n"); */
								break;
								
		case	FM_CCAC	:	/* printf("Close Accepted\n"); */
								break;
								
		case	FM_MVUP	:	k->mvup();
								break;
								
		case	FM_MVDN	:	k->mvdown();
								break;
								
		case	FM_MVLE	:	k->mvleft();
								break;
								
		case	FM_MVRI	:	k->mvright();
								break;
								
		case	FM_MVXY	:	sscanf(buf,"X%3dY%3d",&x,&y);
								k->mvabs(x,y);
								break;
		
		case	FM_QUER	:	if(myturn)
									fmsend(sd,FM_INYT,NULL);

								else if(gameover)
									fmsend(sd,FM_IGOV,NULL);

								else
								{
									buf[0]=k->fire();
									buf[1]=k->ad()+'0';
									buf[2]=k->sh()+'0';
									buf[3]=0;
									
									if(buf[0]&P_SHIP)
									{
										myturn=0;
										info->write2(A_BOLD|A_BLINK," Wait... ");
									}
									else
									{
										myturn=1;
										info->write2(A_BOLD|A_BLINK," Play... ");
										beep(); refresh();
									}
									
									if(buf[2]=='1')
										info->write(A_REVERSE,"Ship sunk ;-((\n");
										
									
									fmsend(sd,FM_QRES,buf);
								}
								break;
		
		case	FM_IGOV	:	info->write(A_BOLD,"Game is over ! You lost ! ;-((\n");
								info->write("Wait for partner...\n");
								gameover=1;
								myturn=1;
								info->write2(A_BOLD|A_BLINK," Game Over ");
								beep(); refresh();
								break;
								
		case	FM_MESG	:	/* ignore */
								break;
								
		case	FM_INVL	:	info->write("Invalid command received by opposite\n");
								/* ignore */
								break;
								
		default		:		// ignore nonrecognized commands
								info->write("Received unknown command (ignored)\n");
								// fmsend(sd,FM_INVL,NULL);
								break;
	}
	return n;
}

int comm::close(void)
{
	if(!connected)
		return -1;
	
	fmsend(sd,FM_CCRQ,NULL);
	
	if(fmrecv(sd,NULL,4)!=FM_CCAC)
		return 1;
	else
		::close(sd);
	
	connected=0;
	
	return 0;
}

int comm::ccac(void)
{
	if(!connected)
		return -1;
	
	fmsend(sd,FM_CCAC,NULL);
	::close(sd);
	
	connected=0;
	
	return 0;
}

int comm::quer(int *alldone)
{
	int	n,fmvalid,attempts;
	
	if(!connected)
		return -1;
	
	if(gameover)
	{
		beep(); refresh();
		return 0;
	}
	
	if(!myturn)
	{
		beep(); refresh();
		info->write("It's not your turn !!\n");
		return 0;
	}
	
	fmsend(sd,FM_QUER,NULL);

	fmvalid=0;
	attempts=3;
	
	while(!fmvalid)
	{
		n=fmrecv(sd,buf,4);
		if(!--attempts)			// mnoho spatnych odpovedi
		{
			fmvalid=-3;	
			info->write(A_BOLD|A_BLINK,"!!! Out of sync !!! (exitting)...\n");
			close();					// zavre spojeni
			break;
		}
		
//		if((n!=FM_QRES)&&(n!=FM_INYT)&&(n!=FM_IGOV))
//			return -1;
		
		switch (n)
		{
			case	FM_INYT:
									info->write("It's not your turn !!!\n");
									myturn=0;
									beep(); refresh();
									fmvalid=-2;
			//						return -2;
									break;
									
			case	FM_IGOV:
									info->write2(A_BOLD|A_BLINK," Game Over ");
									beep(); refresh();
									gameover=1;
									fmvalid=-2;
			//						return -2;
									break;
									
			case	FM_QRES:
									if(buf[0]&P_SHIP)
									{
										myturn=1;
										info->write2(A_BOLD|A_BLINK," Play... ");
									}
									else
									{
										info->write2(A_BOLD|A_BLINK," Wait... ");
										myturn=0;
									}
									
									if(buf[2]=='1')
										info->write(A_REVERSE,"Ship sunk! ;-))\n");
									
									if(buf[1]=='1')
									{
										info->write(A_BOLD,"Game is over! You won !!! :-))\n");
										info->write("Press Q for quit...\n");
										gameover=1;
										myturn=1;
										info->write2(A_BOLD|A_BLINK," Game Over ");
										fmsend(sd,FM_IGOV,NULL);
									}
									fmvalid=1;
									break;
									
			default:				
								fmvalid=0;
		}	// of switch
	}		// of while
	
	if(alldone!=NULL)	
		*alldone=buf[1]-'0';
	
	return (fmvalid<0?fmvalid:buf[0]);
}

int comm::quer(int *alldone, int x, int y)
{
	if(!connected)
		return -1;
	
	mvxy(x,y);
	
	return quer(alldone);
}

void comm::mvxy(int x, int y)
{
	if(!connected)
		return;
	
	sprintf(buf,"X%03dY%03d",x,y);
	
	fmsend(sd,FM_MVXY,buf);
}

int comm::gtxy(int *x, int *y)
{
	if(!connected)
		return -1;
	
	fmsend(sd,FM_QUER,NULL);
	
	if(fmrecv(sd,buf,MAXLEN)!=FM_QRES)
		return -1;
	
	sscanf(buf,"X%3dY%3d",x,y);
	return 0;
}

void comm::mvle(void)
{
	if(!connected)
		return;
	
	fmsend(sd,FM_MVLE,NULL);
}

void comm::mvri(void)
{
	if(!connected)
		return;
	
	fmsend(sd,FM_MVRI,NULL);
}

void comm::mvup(void)
{
	if(!connected)
		return;
	
	fmsend(sd,FM_MVUP,NULL);
}

void comm::mvdn(void)
{
	if(!connected)
		return;
	
	fmsend(sd,FM_MVDN,NULL);
}

void comm::filled(void)
{
	fillok=1;
}
