//
// NetShips class header file
// Michal Ludvig <michal@logix.cz>
// License: BSD-like
// 22.11.1996
//

#include	<ncurses.h>
#include "../version.h"

#ifndef _NS_H_MIC_
#define _NS_H_MIC_

#define	EMAIL			"michal@logix.cz"
#define	URL			"http://netships.sourceforge.net/"
#define	COPY_YEAR	"1996-2001"
#define	TITLE			" NetShips " VERSION " "

#define	f(x,y)			f[xs*y+x]

#define	P_FIRED	1
#define	P_SHIP	2
#define	P_TOUCH	4
#define	P_SHUNK	8

#ifndef	MAXLEN
#define	MAXLEN	1000
#endif

class sea
{
protected:
	WINDOW	*ws,*wb,*wp;

	int		xw,yw;			/* total window size */
	int		xs,ys;			/* pool size */
	int		cx,cy;			/* current position */
	
	class pool	*p;
	
	void	setupwins(void);
	void	setupws(void);
	void	setupwb(void);
	void	setupwp(void);
	
public:
			sea(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy);
	virtual	~sea();
	
	virtual	void	prefresh(void)=0;
};

class seak: public sea
{
public:
			seak(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy);
	
	virtual	void	prefresh(void);
};

class seau: public sea
{
public:
			seau(class pool *pp, WINDOW *parent, int px, int py, int sx, int sy);
	
	virtual	void	prefresh(void);
};

class comm
{
	class poolu	*u;
	class	poolk	*k;
	class	info	*info;
	
	int			sd,connected,myturn,gameover,fillok;
	char			buf[MAXLEN];
	
public:
			comm(class info *inf);
			~comm();
	
	int	connsrv(int port);
	int	conncli(const char *name, int port);
	
	void	regu(class poolu *pu);
	void	regk(class poolk *pk);

	void	filled(void);
	
	int	handle(void);
	int	close(void);
	int	ccac(void);
	
	int	quer(int *ad);
	int	quer(int *ad, int x, int y);
	void	mvxy(int x, int y);
	int	gtxy(int *x, int *y);
	
	void	mvle(void);
	void	mvri(void);
	void	mvup(void);
	void	mvdn(void);
};

class pool
{
protected:
	int			*f;

	int			xs,ys;			/* pool size */
	int			cx,cy;			/* current position */

	friend		seak;
	friend		seau;

	class sea	*s;
	class comm	*c;
	
	int	isship(int x, int y);

	virtual int		fill(void)=0;
	
public:
						pool(int sx, int sy, class comm *cc);
	virtual			~pool(void);
		
	virtual	void	mvup(void)=0;
	virtual	void	mvdown(void)=0;
	virtual	void	mvleft(void)=0;
	virtual	void	mvright(void)=0;
	
	virtual	void	mvabs(int x, int y)=0;
	
	virtual	int	fire(void)=0;
	virtual	int	fire(int x, int y)=0;
};

class poolu: public pool	/* pool unknown */
{
	int	fill(void);
	
public:
			poolu(WINDOW *parent, int px, int py, int sx, int sy, class comm *cc);
			~poolu();

	void	mvup(void);
	void	mvdown(void);
	void	mvleft(void);
	void	mvright(void);
	
	void	mvabs(int x, int y);
	
	int	fire(void);
	int	fire(int x, int y);
};

class poolk: public pool	/* pool unknown */
{
	int			alldone, sunk;
	class info	*inf;
	
	int	fill(void);
	int	shiphere(void);
	int	checkpool(void);
	int	nextship(int &x, int &y);
		
public:
			poolk(WINDOW *parent, int px, int py, int sx, int sy, class comm *cc, class info *ii);
			~poolk();

	int	ad(void);
	int	sh(void);
	
	void	mvup(void);
	void	mvdown(void);
	void	mvleft(void);
	void	mvright(void);
	
	void	mvabs(int x, int y);
	
	int	touch(int x, int y);
	int	fire(void);
	int	fire(int x, int y);
};

class info
{
	WINDOW	*wm,*w,*w2;
	
public:
			info(WINDOW *parent, int px, int py, int sx, int sy);
			~info();
	
	int	write(const char *str);
	int	write(int attr, const char *str);
	int	writef(const char *str, ...);
	int	writef(int attr,const char *str, ...);
	
	void	write2(const char *str);
	void	write2(int attr, const char *str);
};

#endif
