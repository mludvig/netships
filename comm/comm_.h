#ifndef __COMM_H__
#define __COMM_H__

#define	SRV_PORT		8421
#define	MAXLEN		500

#ifdef __cplusplus
extern "C"
{
#endif

	void prhostent(struct hostent he);
	unsigned long str2inaddr(const char *hname);
	int initsrv(void);
	int initcli(const char *hnam);


#ifdef __cplusplus
}
#endif

#endif
