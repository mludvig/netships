//
// poolu class
// Michal Ludvig <michal@logix.cz>
// License: BSD-like
// 22.11.1996
//

#include <ncurses.h>

#include "ns.h"

poolu::poolu(WINDOW *parent, int px, int py, int sx, int sy, class comm *cc)
	:pool(sx,sy,cc)
{
	c->regu(this);
	
	s=new seau(this,parent,px,py,sx,sy);
	
	fill();
	
	s->prefresh();
}

poolu::~poolu()
{
	delete s;
}

void poolu::mvup(void)
{
	cy = (cy > 0) ? cy-1 : ys-1;
	c->mvxy(cx,cy);
	s->prefresh();
}

void poolu::mvdown(void)
{
	cy = (cy < ys-1) ? cy+1 : 0;
	c->mvxy(cx,cy);
	s->prefresh();
}

void poolu::mvleft(void)
{
	cx = (cx > 0) ? cx-1 : xs-1;
	c->mvxy(cx,cy);
	s->prefresh();
}

void poolu::mvright(void)
{
	cx = (cx < xs-1) ? cx+1 : 0;
	c->mvxy(cx,cy);
	s->prefresh();
}

void poolu::mvabs(int x, int y)
{
	cx = ((x>=0) && (x<xs)) ? x : cx;
	cy = ((y>=0) && (y<ys)) ? y : cy;
	c->mvxy(cx,cy);
	s->prefresh();
}

int poolu::fill(void)
{
	int	i,j;
	for(i=0;i<xs;i++)
		for(j=0;j<ys;j++)
			f(i,j)=0;
	return 0;
}

int poolu::fire(void)
{
	int	x,y,t;
	
	if(!(f(cx,cy)&P_FIRED))
	{	
		t=c->quer(NULL,cx,cy);
		
		if (t>=0)	//	pokud je odpoved platna
		{
			f(cx,cy)=t;
		
			if(f(cx,cy)&P_SHUNK)
			{
				x=cx;
				y=cy;
			
//				inf->writef("debug: start of P_SHUNK (%d,%d)\n",x,y);
				
				while(isship(x-1,y))
					x--;
				
				while(isship(x,y-1))
					y--;	
				
//				inf->writef("debug: moved to start P_SHUNK (%d,%d)\n",x,y);
				
				while(isship(x,y))
				{
					f(x,y)|=P_SHUNK;
//					inf->writef("debug: P_SHUNK set (%d,%d)\n",x,y);
					
					if(isship(x+1,y))
						x++;
					else
						y++;
				}
			}
		}
	}
	s->prefresh();
	return f(cx,cy);
}

int poolu::fire(int x, int y)
{
	mvabs(x,y);
	return fire();
}
