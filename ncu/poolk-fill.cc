//
// methods for filling and checking poolk
// Michal Ludvig <mic@cybeteria.cz>
// 22.11.1996
//

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "ns.h"

//#define RND_FILL

int poolk::nextship(int &x, int &y)
{
	for(;;)
	{
		if(x < xs-1)
			x++;
		else
		{
			x=0;
			y++;
		}
	
		if(y>=ys)
			return 0;
		
		if(isship(x,y))
			return 1;
	}
}

int poolk::shiphere(void)
{
	if(f(cx,cy)&P_SHIP)
		f(cx,cy)&=~P_SHIP;
	else
		f(cx,cy)|=P_SHIP;

	s->prefresh();
	return 0;
}

int poolk::checkpool(void)
{
	int	l,x,y,xx,yy;
	int	shid[4];
	
	for(l=0;l<4;l++) shid[l]=0;
	
	l=0;
	
	xx=0; yy=0;
	x=xx; y=yy;
	
	if(!isship(x,y))	// position (A,0)
		if(!nextship(xx,yy))
		{
			inf->write(A_BOLD,"You must place ships!!!\n");
			return 1;
		}
		
	for(;;)
	{
		x=xx; y=yy;
		if((!isship(x,y-1)) && (!isship(x-1,y)))
		{	/* we are here first time */
			l=1;
			
			for(;;)
			{
				if(isship(x-1,y+1) || isship(x+1,y+1))
				{	/* bad ship position */
					inf->writef("Collision detected at (%d, %c)\n", x, 'A'+y);
					cx=x;
					cy=y;
					s->prefresh();
					return 1;
				}
				
				if(!isship(x+1,y) && !isship(x,y+1))
				{
					shid[l-1]++;
					break;
				}
				else if(isship(x+1,y))
				{
					l++;
					x++;
				}
				else if(isship(x,y+1))
				{
					l++;
					y++;
				}
				
				if(l>4)
				{
					inf->writef("Ship too long (max=4) at (%d, %c)\n", x, 'A'+y);
					cx=x;
					cy=y;
					s->prefresh();
					return 1;
				}
			}
		}

		if(!nextship(xx,yy))
		{
			if((shid[0]==4)&&(shid[1]==3)&&(shid[2]==2)&&(shid[3]==1))
				return 0;
			else
			{
				inf->writef("All numbers must be 0: "
					"[4]=%d, [3]=%d, [2]=%d, [1]=%d\n",\
					1-shid[3],2-shid[2],3-shid[1],4-shid[0]);
				return 1;
			}
		}
	}
	inf->write(A_BOLD|A_BLINK,"Internal error: poolk::checkpool() Reached forbidden code!!!\n");
	beep();
	return 1;
}

#ifndef RND_FILL

int poolk::fill(void)
{
	int c,n;
	
	n=0;
	
	for(;;)
	{
		c=getch();
		
		switch(c)
		{
			case KEY_LEFT:
			case 'h':
			case 'H':
				mvleft();
				break;
			
			case KEY_RIGHT:
			case 'l':
			case 'L':
				mvright();
				break;
			
			case KEY_UP:
			case 'k':
			case 'K':
				mvup();
				break;
			
			case KEY_DOWN:
			case 'j':
			case 'J':
				mvdown();
				break;
		
			case 0x0D:		// Enter
			case 0x0A:
			case ' ':
				shiphere();
				break;
		
			case 'C':
			case 'c':
				if(checkpool()==0)
				{
					n=1;
					inf->write("Pool seems to be OK\n");
					cx=0;
					cy=0;
					this->c->filled();
					s->prefresh();
				}
				break;
			
			case 'Q':
			case 'q':
				n=-1;
				break;
					
			default:
				beep();
				break;
		}
		s->prefresh();
		if(n)
			break;
	}
	if(n==1)
		return 0;
	else
		return 1;
}

#else

int poolk::fill(void)
{
	int	i,j,k;
	
	srand((int)time(NULL));
	
	for(i=0;i<xs;i++)
		for(j=0;j<ys;j++)
		{
			k=(int) (100.0*rand()/(RAND_MAX+1.0));
			f[xs*j+i]=(k>75) ? P_SHIP : 0;
		}
	return 0;
}

#endif
