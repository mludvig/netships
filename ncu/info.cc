//
// info box
// Michal Ludvig <michal@logix.cz>
// 08 Dec 1996
// License: BSD-like
//

#include <stdlib.h>
#include	<stdarg.h>
#include <string.h>
#include <ncurses.h>

#include "ns.h"

info::info(WINDOW *parent, int px, int py, int sx, int sy)
{
	char	*title=" Info box ";
	
	if(parent==NULL)
		wm=newwin(sy,sx,py,px);
	else
		wm=derwin(parent,sy,sx,py,px);
	
	if(wm==NULL)
	{
		printw("Unable to create info\n");
		return;
	}
	
	wattron(wm,A_BOLD);
	box(wm,0,0);
	leaveok(wm,TRUE);
	mvwaddstr(wm,0, (wm->_maxx-strlen(title))/2, title);
	wattroff(wm,A_BOLD);
	wrefresh(wm);

	w=derwin(wm,sy-2,sx-2,1,1);
	scrollok(w,TRUE);
	leaveok(w,TRUE);
	wmove(w,0,0);
	wrefresh(w);

	w2=derwin(wm,1,15,sy-1,sx-17);
	scrollok(w2,FALSE);
	leaveok(w2,TRUE);
	werase(w2);
	wmove(w,0,0);
	wrefresh(w2);
}

info::~info()
{
	delwin(w);
	delwin(wm);
}

int info::write(const char *str)
{
	return write(A_NORMAL,str);
}

int info::write(int attr, const char *str)
{
	wattron(w,attr);
	mvwaddstr(w,w->_maxy,w->_curx,str);
	wattroff(w,attr);
	wrefresh(w);
	return 0;
}
               
int info::writef(int attr,const char *str, ...)
{
   va_list	args;
   char		buf[1000];

   va_start(args, str);
   vsprintf(buf, str, args);
   return write(attr, buf);
}

int info::writef(const char *str, ...)
{
   va_list	args;
   char		buf[1000];

   va_start(args, str);
   vsprintf(buf, str, args);
   return write(buf);
}

void info::write2(const char *str)
{
	write2(A_NORMAL,str);
}

void info::write2(int attr, const char *str)
{
	wattron(w2,attr);
	werase(w2);
	wmove(w2,0,0);
	wprintw(w2,"%.14s",str);
	wattroff(w2,attr);
	wrefresh(w2);	
}
