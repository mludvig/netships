//
// poolk class
// Michal Ludvig <mic@cybeteria.cz>
// 22.11.1996
//

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "ns.h"

poolk::poolk(WINDOW *parent, int px, int py, int sx, int sy, class comm *cc, class info *ii)
	:pool(sx,sy,cc)
{
	c->regk(this);
	
	inf=ii;
	
	s=new seak(this,parent,px,py,sx,sy);
	
	s->prefresh();

	if(fill())
		inf->write(A_BOLD,"warning: pool filled incorrectly !!!\n");
	
	s->prefresh();
}

poolk::~poolk()
{
	delete s;
}

void poolk::mvup(void)
{
	cy = (cy > 0) ? cy-1 : ys-1;
	s->prefresh();
}

void poolk::mvdown(void)
{
	cy = (cy < ys-1) ? cy+1 : 0;
	s->prefresh();
}

void poolk::mvleft(void)
{
	cx = (cx > 0) ? cx-1 : xs-1;
	s->prefresh();
}

void poolk::mvright(void)
{
	cx = (cx < xs-1) ? cx+1 : 0;
	s->prefresh();
}

void poolk::mvabs(int x, int y)
{
	cx = ((x>=0) && (x<xs)) ? x : cx;
	cy = ((y>=0) && (y<ys)) ? y : cy;
	s->prefresh();
}

int poolk::fire(int x, int y)
{
	mvabs(x,y);
	return fire();	
}

int poolk::fire(void)
{
	int	i,j,x,y;
	
	f(cx,cy)|=P_FIRED;
	
	alldone=0;
	sunk=0;
					
	if(f(cx,cy)&P_SHIP)
	{
		alldone=1;
		for(i=0;i<xs;i++)
			for(j=0;j<ys;j++)
				if((f(i,j)&P_SHIP)&&(!(f(i,j)&P_FIRED)))
					alldone=0;
					
		x=cx;
		y=cy;
	
		while(isship(x-1,y))
			x--;
	
		while(isship(x,y-1))
			y--;	
	
		i=x; j=y;		// zacatek lode
		
		sunk=1;
	
		while(isship(x,y))
		{
			if(!(f(x,y)&P_FIRED))
				sunk=0;
		
			if(isship(x+1,y))
				x++;
			else
				y++;
		}
		
		if (sunk)			// set sunk flag
		{
//			inf->writef("debug: start of P_SHUNK (%d,%d)\n",x,y);
			
//			while(isship(x-1,y))
//				x--;
			
//			while(isship(x,y-1))
//				y--;	
			
			x=i;
			y=j;
			
//			inf->writef("debug: moved to start P_SHUNK (%d,%d)\n",x,y);
			
			while(isship(x,y))
			{
				f(x,y)|=P_SHUNK;
//				inf->writef("debug: P_SHUNK set (%d,%d)\n",x,y);
				
				if(isship(x+1,y))
					x++;
				else
					y++;
			}
		}
	}
	
	s->prefresh();
	
	return f(cx,cy);
}

int poolk::ad(void)
{
	return	alldone;
}

int poolk::sh(void)
{
	return	sunk;
}
