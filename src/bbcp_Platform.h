#ifndef __BBCP_PLATFORM_H
#define __BBCP_PLATFORM_H
/******************************************************************************/
/*                                                                            */
/*                       b b c p _ P l a t f o r m . h                        */
/*                                                                            */
/* (c) 2002 by the Board of Trustees of the Leland Stanford, Jr., University  */
/*      All Rights Reserved. See bbcp_Version.C for complete License Terms    *//*                            All Rights Reserved                             */
/*   Produced by Andrew Hanushevsky for Stanford University under contract    */
/*              DE-AC03-76-SFO0515 with the Department of Energy              */
/******************************************************************************/

#define PS_CMD "/bin/ps -o ppid -p %d"

#ifdef AIX
#define S_IAMB  0x1FF
#define GETHOSTBYNAME(hname, rbuff, cbuff, cblen,  rpnt, pretc) \
     (rpnt = gethostbyname(hname))

#define GETHOSTBYADDR(haddr,hlen,htype,rbuff,cbuff,cblen, rpnt,pretc) \
     (rpnt = gethostbyaddr(haddr,hlen,htype))

#define GETSERVBYNAME(name, stype, psrv, buff, blen,  rpnt) \
     (rpnt = getservbyname(name, stype))

#define EBADSLT EFAULT
#endif

#if defined(FREEBSD)
#define SYS_ERR_DEF const char *const
#define SYS_NER_DEF const int
#define IOV_MAX 16
#endif

#if defined(FREEBSD) || defined(MACOS)
#ifndef O_DSYNC
#define O_DSYNC 0
#endif
#endif

#if defined(FREEBSD) || defined(MACOS) || defined(AIX)

#define S_IAMB  0x1FF

#define GETHOSTBYNAME(hname, rbuff, cbuff, cblen,  rpnt, pretc) \
     (rpnt = gethostbyname(hname))

#define GETHOSTBYADDR(haddr,hlen,htype,rbuff,cbuff,cblen, rpnt,pretc) \
     (rpnt = gethostbyaddr(haddr,hlen,htype))

#define GETSERVBYNAME(name, stype, psrv, buff, blen,  rpnt) \
     (rpnt = getservbyname(name, stype))

#endif
  
#ifdef LINUX

// The value should be MAX_IOVEC but it's not defined in Linux, sigh
//
#ifndef IOV_MAX
#define IOV_MAX 16
#endif
#ifndef POLLRDNORM
#define POLLRDNORM 0
#endif
#ifndef POLLRDBAND
#define POLLRDBAND 0
#endif

#define SYS_ERR_DEF const char *const
#define SYS_NER_DEF       int

#define S_IAMB  0x1FF

#define FMTLL "L"

#ifdef CRAY_X1E
#define GETHOSTBYNAME(hname, rbuff, cbuff, cblen,  rpnt, pretc) \
     (rpnt = gethostbyname(hname))

#define GETHOSTBYADDR(haddr,hlen,htype,rbuff,cbuff,cblen, rpnt,pretc) \
     (rpnt = gethostbyaddr(haddr,hlen,htype))

#define GETSERVBYNAME(name, stype, psrv, buff, blen,  rpnt) \
     (rpnt = getservbyname(name, stype))
#else
#define GETHOSTBYNAME(hname, rbuff, cbuff, cblen,  rpnt, pretc) \
     (gethostbyname_r(hname, rbuff, cbuff, cblen, &rpnt, pretc) == 0 && rpnt)

#define GETHOSTBYADDR(haddr,hlen,htype,rbuff,cbuff,cblen, rpnt,pretc) \
     (gethostbyaddr_r(haddr,hlen,htype,rbuff,cbuff,cblen,&rpnt,pretc) == 0 && rpnt)

#define GETSERVBYNAME(name, stype, psrv, buff, blen,  rpnt) \
     (getservbyname_r(name, stype, psrv, buff, blen, &rpnt) == 0 && rpnt)
#endif

#else

#define FMTLL "ll"

#endif

#if !defined(LINUX) && !defined(FREEBSD) && !defined(AIX) && !defined(MACOS)

#define SYS_ERR_DEF char *
#define SYS_NER_DEF int

#define GETHOSTBYNAME(hname, rbuff, cbuff, cblen, rpnt, pretc) \
(rpnt=gethostbyname_r(hname, rbuff, cbuff, cblen,       pretc))

#define GETHOSTBYADDR(haddr, hlen, htype, rbuff, cbuff, cblen, rpnt, pretc) \
(rpnt=gethostbyaddr_r(haddr, hlen, htype, rbuff, cbuff, cblen,       pretc))


#define GETSERVBYNAME(name, stype, psrv, buff, blen, rpnt) \
(rpnt=getservbyname_r(name, stype, psrv, buff, blen))

#endif

typedef       void * gsval_t;
typedef       void * ssval_t;
typedef size_t Size_T;

#ifdef FREEBSD
#define EPROTO  EPROTOTYPE
#define ENOSR   EILSEQ
#endif

#if defined(FREEBSD) || defined(MACOS) || defined(AIX)
#define EBADSLT EFAULT
#endif

#endif
