/*
 * #defines for fmesg functions
 * Michal Ludvig <mic@cybeteria.cz>
 * 06 Dec 1996
 */

#ifndef __FMESG_T_H_MIC_
#define __FMESG_T_H_MIC_

#define	FM_CORQ	1		/* Connection Open ReQuest */
#define	FM_COAC	2		/* Connection Open ACcepted */
#define	FM_CCRQ	3		/* Connection Close ReQuest */
#define	FM_CCAC	4		/* Connection Close ACcepted */
#define	FM_INFO	5		/* INFO message */
#define	FM_MESG	6		/* MESsaGe */
#define	FM_MVUP	7		/* MoVe UP */
#define	FM_MVDN	8		/* MoVe DowN */
#define	FM_MVLE	9		/* MoVe LEft */
#define	FM_MVRI	10		/* MoVe RIght */
#define	FM_MVXY	11		/* MoVe to X, Y coords. (ignored if invalid) */
#define	FM_GTXY	12		/* GeT current X, Y coords. */
#define	FM_GXYR	13		/* GeT X, Y Result */
#define	FM_QUER	14		/* QUERy status of actual field */
#define	FM_QRES	15		/* RESult of FM_QUER */
#define	FM_INYT	16		/* Info: Not Your Turn */
#define	FM_IGOV	17		/* Info: Game Is Over */

#define	FM_INVL	888	/* received INVaLid command */
#define	FM_		0		/* unused item */
#define	FM_0000	0		/* end of list */

#endif
