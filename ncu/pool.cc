//
// pool class
// Michal Ludvig <michal@logix.cz>
// License: BSD-like
// 22.11.1996
//

#include <stdlib.h>
#include <ncurses.h>

#include "ns.h"

pool::pool(int sx, int sy, class comm *cc)
{
	xs=sx;
	ys=sy;
	
	cx=0;
	cy=0;
	
	c=cc;
	
	f=(int*)calloc(xs*ys,sizeof(int));
}

pool::~pool()
{
	free(f);
}

int pool::isship(int x, int y)
{
	int n;
	
	if((x>=0)&&(x<xs)&&(y>=0)&&(y<ys))
		n=f(x,y)&P_SHIP;
	else
		n=0;
	
	return n;
}

