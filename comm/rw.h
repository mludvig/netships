/*
 * Author: Michal Ludvig <michal@logix.cz>
 * License: BSD-like (see ../LICENSE for details)
 */

#ifndef __RW_H_
#define __RW_H_

#ifdef __cplusplus
extern "C"
{
#endif

	/* read/write nbytes from buf */
	int readn(int fd, char *buf, int nbytes);
	int writen(int fd, char *buf, int nbytes);
	
	/* read/write formated string */
	int readf(int sd, char *buf, int maxlen);
	int writef(int sd, char *buf, int len);

#ifdef __cplusplus
}
#endif


#endif
