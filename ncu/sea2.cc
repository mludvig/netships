//
// seak and seau classes
// Michal Ludvig <mic@cybeteria.cz>
// 22.11.1996
//

#include <ncurses.h>

#include "ns.h"

seak::seak(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy)
	:sea(pp, parent, px, py, sx, sy)
{}

void seak::prefresh(void)
{
	int	i,j;
	
	for(i=0;i<xs;i++)
		for(j=0;j<ys;j++)
		{
			if((i==p->cx)&&(j==p->cy))
				wattron(wp,A_REVERSE);
			
			if(p->f[j*xs+i]&P_FIRED)
				if(p->f(i,j)&P_SHIP)
					if(!(p->f(i,j)&P_SHUNK))
						mvwaddstr(wp,j,2*i,"[]");
					else
						mvwaddstr(wp,j,2*i,"XX");
				else
					mvwaddstr(wp,j,2*i,"::");
			else 
				if(p->f(i,j)&P_SHIP)
					mvwaddstr(wp,j,2*i,"##");
				else
					mvwaddstr(wp,j,2*i,"  ");
			
			wattroff(wp,A_REVERSE);
		}
	wrefresh(wp);
}

seau::seau(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy)
	:sea(pp, parent, px, py, sx, sy)
{}

void seau::prefresh(void)
{
	int	i,j;
	
	for(i=0;i<xs;i++)
		for(j=0;j<ys;j++)
		{
			if((i==p->cx)&&(j==p->cy))
				wattron(wp,A_REVERSE);
			
			if(p->f[j*xs+i]&P_FIRED)
				if(p->f(i,j)&P_SHIP)
					if(!(p->f(i,j)&P_SHUNK))
						mvwaddstr(wp,j,2*i,"[]");
					else
						mvwaddstr(wp,j,2*i,"XX");					
				else
					mvwaddstr(wp,j,2*i,"::");
			else 
				mvwaddstr(wp,j,2*i,"  ");
			
			wattroff(wp,A_REVERSE);
		}
	wrefresh(wp);
}

