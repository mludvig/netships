//
// NetShips
// Michal Ludvig <michal@logix.cz>
// 23.11.1996, 25.7.2000
// License: BSD like
// 

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#include "ns.h"
#include "mic.h"
#include "fmtypes.h"

#define	xs	10
#define	ys	10

void crframe(void)
{
	/* init main window */
	wattrset(stdscr,A_BOLD);
	box(stdscr,0,0);
	mvwaddstr(stdscr,0,COLS/2-strlen(TITLE)/2,TITLE);
	wrefresh(stdscr);
}
	
int main(int argc, char *argv[])
{
	class poolu	*pu;
	class poolk	*pk;
	class comm	*co;
	class	info	*inf;
	
	int			c, sd, n;
	fd_set		wts;


	initscr();
	keypad(stdscr, TRUE);	/* enable keyboard mapping */
	nonl();						/* tell curses not to do NL->CR/NL on output */
   cbreak();					/* take input chars one at a time, no wait for \n */
   noecho();					/* don't echo input */
	
	crframe();					/* draw frame around stdscr */
	
	inf=new info(NULL,3,LINES-9,COLS-6,8);
	
	inf->writef(A_BOLD,"%s (c) %s\nMichal Ludvig <%s>\n", COPY_YEAR, TITLE, EMAIL);
	
	if(inf==NULL)
		endwin();
	
	co=new comm(inf);
	
	inf->write("Place your ships please. Press C for Check/Continue or Q for Quit\n"
				"Required amount of ships: [4]=1, [3]=2, [2]=3, [1]=4\n");
	
	pk=new poolk(NULL,COLS-2*xs-6,2,xs,ys,co,inf);
	
	pu=new poolu(NULL,3,2,xs,ys,co);
	
	if(argc>1)
		sd=co->conncli(argv[1],8421);
	else
		sd=co->connsrv(8421);
	
	if(sd<0)
	{
		if(sd==-7)	// poolk filled incorrectly
			inf->write(A_BOLD,"Incomplete pool: Exitting...");
		else
			inf->writef(A_BOLD|A_BLINK,"Connection failed (%s)",strerror(errno));
			
		inf->writef(A_BOLD,"\n%s (c) %s\nMichal Ludvig <%s>\n", COPY_YEAR, TITLE, EMAIL);
	
		delete pk;
		delete pu;
		delete co;
		delete inf;
		endwin();
		exit(1);
	}
	
	for(;;)
	{
		FD_ZERO(&wts);
		FD_SET(1,&wts);
		FD_SET(sd,&wts);
	
		if(select(sd+1,&wts,(fd_set *)0,(fd_set *)0,(struct timeval*)0)<0)
			failprog(1,"f-comm-run-select\n");
		
		if(FD_ISSET(sd,&wts))
		{	// socket
			n=co->handle();
			if(n==FM_CCRQ)
			{
				co->ccac();
				break;
			}
		}
		else 
		if(FD_ISSET(1,&wts))
		{	// stdin
		c=getch();
		switch(c)
		{
			case KEY_LEFT:
			case 'h':
			case 'H':
				pu->mvleft();
				break;
			
			case KEY_RIGHT:
			case 'l':
			case 'L':
				pu->mvright();
				break;
			
			case KEY_UP:
			case 'k':
			case 'K':
				pu->mvup();
				break;
			
			case KEY_DOWN:
			case 'j':
			case 'J':
				pu->mvdown();
				break;
		
			case 0x0D:		// Enter
			case 0x0A:
			case ' ':
				pu->fire();
				break;
		
			case 'Q':
			case 'q':
				co->close();
				break;
					
			default:
				break;
		}
		}
		if((c=='q')||(c=='Q'))
			break;
	}
	
	inf->writef(A_BOLD,"\n%s (c) %s\nMichal Ludvig <%s>\n", COPY_YEAR, TITLE, EMAIL);

	delete pu;

	delete pk;
	
	delete co;
	
	delete inf;
	
	endwin();
}
