/*
 * mic_t.h
 *
 * Michal Ludvig <michal@logix.cz>
 * 2000-07-25
 * License: BSD like
 *
 */

#ifndef _MIC_T_H_
#define _MIC_T_H_

#ifndef _MIC_Uxx
#define _MIC_Uxx

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#ifndef _s64
typedef __signed__ long long _s64;
#endif
#ifndef _u64
typedef unsigned long long _u64;
#endif
#endif

#ifndef _u32
#define _u32 unsigned long
#endif

#ifndef _u16
#define _u16 unsigned short
#endif

#ifndef _u8
#define _u8 unsigned char
#endif

#ifndef _s32
#define _s32 long
#endif

#ifndef _s16
#define _s16 short
#endif

#ifndef _u8
#define _u8 signed char
#endif

#endif

#ifndef _MIC__Uxx
#define _MIC__Uxx

/* kernel 2.0.21 defines this
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#ifndef __s64
typedef __signed__ long long __s64;
#endif __s64
#ifndef __u64
typedef unsigned long long __u64;
#endif __u64
#endif
*/

#ifndef __u32
#define __u32 _u32
#endif

#ifndef __u16
#define __u16 _u16
#endif

#ifndef __u8
#define __u8 _u8
#endif

#ifndef __s32
#define __s32 _s32
#endif

#ifndef __s16
#define __s16 _s16
#endif

#ifndef __s8
#define __s8 _s8
#endif

#endif

#endif
