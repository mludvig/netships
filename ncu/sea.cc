//
// sea class
// Michal Ludvig <michal@logix.cz>
// License: BSD-like
// 22.11.1996
//

#include <ncurses.h>

#include "ns.h"

sea::sea(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy)
{
	p=pp;
	
	yw = sy + 3;
	xw = sx*2 + 3;	

	xs=sx;
	ys=sy;
	
	if(parent==NULL)
		ws=newwin(yw, xw, py, px);
	else
		ws=derwin(parent, yw, xw, py, px);
	
	setupwins(); 
}

sea::~sea(void)
{
	delwin(wp);
	delwin(wb);
	delwin(ws);
}

void sea::setupws(void)
{
	int	i,n;
	
	wattrset(ws,A_NORMAL);
	
	/* prepare cursor for number-line */
	wmove(ws,0,2);
	
	/* let cursor move after write */
	leaveok(ws,TRUE);

	/* write numbers */
	for(i=1;i<=xs;i++)
		if((n=(i/10))*10==i) 
		{
			wattron(ws,A_BOLD);
			wprintw(ws,"%2d",i);
			wattroff(ws,A_BOLD);
		}
		else wprintw(ws,"%2d",i-10*n);
	
	/* write letters */
	for(i=1;i<yw-2;i++)
	{
		if((i/5)*5==i)
		{
			wattron(ws,A_BOLD);
			mvwaddch(ws,i+1,0,'A'+i-1);
			wattroff(ws,A_BOLD);
		}
		else
			mvwaddch(ws,i+1,0,'A'+i-1);
	}	
	
	/* update virtual screen */
	wnoutrefresh(ws);
}

void sea::setupwb(void)
{
	/* create box around a pool */
	box(wb,0,0);
	wnoutrefresh(wb);
}

void sea::setupwp(void)
{
	int	i,n;
	
	leaveok(wp,TRUE);
	
	for(i=0;i<yw;i++)
	{
		wmove(wp,i,0);
		for(n=0;n<xw;n++)
			waddstr(wp,"  ");
	}
	
	wnoutrefresh(wp);
}

void sea::setupwins(void)
{
	wb=derwin(ws,yw-1,xw-1,1,1);
	wp=derwin(ws,yw-3,xw-3,2,2);

	setupws();
	setupwb();

	doupdate();
	refresh();
}


