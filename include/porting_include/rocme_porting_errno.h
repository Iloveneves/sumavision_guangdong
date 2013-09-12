#ifndef _ROCME_ERRNO_H
#define _ROCME_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#if 0
#if 1   /*for windows*/
#include "winerror.h"
#undef  ROC_EBADF            /* override definition in errno.h */
#define ROC_EBADF            WSAEBADF
#undef  ROC_EINTR            /* override definition in errno.h */
#define ROC_EINTR            WSAEINTR
#undef  ROC_EINVAL           /* override definition in errno.h */
#define ROC_EINVAL           WSAEINVAL
#undef  ROC_EWOULDBLOCK      /* override definition in errno.h */
#define ROC_EWOULDBLOCK      WSAEWOULDBLOCK
#undef  ROC_EINPROGRESS      /* override definition in errno.h */
#define ROC_EINPROGRESS      WSAEINPROGRESS
#undef  ROC_EALREADY         /* override definition in errno.h */
#define ROC_EALREADY         WSAEALREADY
#undef  ROC_ENOTSOCK         /* override definition in errno.h */
#define ROC_ENOTSOCK         WSAENOTSOCK
#undef  ROC_EDESTADDRREQ     /* override definition in errno.h */
#define ROC_EDESTADDRREQ     WSAEDESTADDRREQ
#undef  ROC_EMSGSIZE         /* override definition in errno.h */
#define ROC_EMSGSIZE         WSAEMSGSIZE
#undef  ROC_EPROTOTYPE       /* override definition in errno.h */
#define ROC_EPROTOTYPE       WSAEPROTOTYPE
#undef  ROC_ENOPROTOOPT      /* override definition in errno.h */
#define ROC_ENOPROTOOPT      WSAENOPROTOOPT
#undef  ROC_EPROTONOSUPPORT  /* override definition in errno.h */
#define ROC_EPROTONOSUPPORT  WSAEPROTONOSUPPORT
#define ROC_ESOCKTNOSUPPORT  WSAESOCKTNOSUPPORT
#undef  ROC_EOPNOTSUPP       /* override definition in errno.h */
#define ROC_EOPNOTSUPP       WSAEOPNOTSUPP
#define ROC_EPFNOSUPPORT     WSAEPFNOSUPPORT
#undef  ROC_EAFNOSUPPORT     /* override definition in errno.h */
#define ROC_EAFNOSUPPORT     WSAEAFNOSUPPORT
#undef  ROC_EADDRINUSE       /* override definition in errno.h */
#define ROC_EADDRINUSE       WSAEADDRINUSE
#undef  ROC_EADDRNOTAVAIL    /* override definition in errno.h */
#define ROC_EADDRNOTAVAIL    WSAEADDRNOTAVAIL
#undef  ROC_ENETDOWN         /* override definition in errno.h */
#define ROC_ENETDOWN         WSAENETDOWN
#undef  ROC_ENETUNREACH      /* override definition in errno.h */
#define ROC_ENETUNREACH      WSAENETUNREACH
#undef  ROC_ENETRESET        /* override definition in errno.h */
#define ROC_ENETRESET        WSAENETRESET
#undef  ROC_ECONNABORTED     /* override definition in errno.h */
#define ROC_ECONNABORTED     WSAECONNABORTED
#undef  ROC_ECONNRESET       /* override definition in errno.h */
#define ROC_ECONNRESET       WSAECONNRESET
#undef  ROC_ENOBUFS          /* override definition in errno.h */
#define ROC_ENOBUFS          WSAENOBUFS
#undef  ROC_EISCONN          /* override definition in errno.h */
#define ROC_EISCONN          WSAEISCONN
#undef  ROC_ENOTCONN         /* override definition in errno.h */
#define ROC_ENOTCONN         WSAENOTCONN
#define ROC_ESHUTDOWN        WSAESHUTDOWN
#define ROC_ETOOMANYREFS     WSAETOOMANYREFS
#undef  ROC_ETIMEDOUT        /* override definition in errno.h */
#define ROC_ETIMEDOUT        WSAETIMEDOUT
#undef  ROC_ECONNREFUSED     /* override definition in errno.h */
#define ROC_ECONNREFUSED     WSAECONNREFUSED
#undef  ROC_ELOOP            /* override definition in errno.h */
#define ROC_ELOOP            WSAELOOP
#ifndef ROC_ENAMETOOLONG     /* possible previous definition in errno.h */
#define ROC_ENAMETOOLONG     WSAENAMETOOLONG
#endif
#define ROC_EHOSTDOWN        WSAEHOSTDOWN
#undef  ROC_EHOSTUNREACH     /* override definition in errno.h */
#define ROC_EHOSTUNREACH     WSAEHOSTUNREACH
#ifndef ROC_ENOTEMPTY        /* possible previous definition in errno.h */
#define ROC_ENOTEMPTY        WSAENOTEMPTY
#endif
#define ROC_EPROCLIM         WSAEPROCLIM
#define ROC_EUSERS           WSAEUSERS
#define ROC_EDQUOT           WSAEDQUOT
#define ROC_ESTALE           WSAESTALE
#define ROC_EREMOTE          WSAEREMOTE
#else


#define ROC_EPERM		 1	/* Operation not permitted */
#define ROC_ENOENT		 2	/* No such file or directory */
#define ROC_ESRCH		 3	/* No such process */
#define ROC_EINTR		 4	/* Interrupted system call */
#define ROC_EIO			 5	/* I/O error */
#define ROC_ENXIO		 6	/* No such device or address */
#define ROC_E2BIG		 7	/* Argument list too long */
#define ROC_ENOEXEC		 8	/* Exec format error */
#define ROC_EBADF		 9	/* Bad file number */
#define ROC_ECHILD		10	/* No child processes */
#define ROC_EAGAIN		11	/* Try again */
#define ROC_ENOMEM		12	/* Out of memory */
#define ROC_EACCES		13	/* Permission denied */
#define ROC_EFAULT		14	/* Bad address */
#define ROC_ENOTBLK		15	/* Block device required */
#define ROC_EBUSY		16	/* Device or resource busy */
#define ROC_EEXIST		17	/* File exists */
#define ROC_EXDEV		18	/* Cross-device link */
#define ROC_ENODEV		19	/* No such device */
#define ROC_ENOTDIR		20	/* Not a directory */
#define ROC_EISDIR		21	/* Is a directory */
#define ROC_EINVAL		22	/* Invalid argument */
#define ROC_ENFILE		23	/* File table overflow */
#define ROC_EMFILE		24	/* Too many open files */
#define ROC_ENOTTY		25	/* Not a typewriter */
#define ROC_ETXTBSY		26	/* Text file busy */
#define ROC_EFBIG		27	/* File too large */
#define ROC_ENOSPC		28	/* No space left on device */
#define ROC_ESPIPE		29	/* Illegal seek */
#define ROC_EROFS		30	/* Read-only file system */
#define ROC_EMLINK		31	/* Too many links */
#define ROC_EPIPE		32	/* Broken pipe */
#define ROC_EDOM		33	/* Math argument out of domain of func */
#define ROC_ERANGE		34	/* Math result not representable */

#define ROC_EDEADLK		35	/* Resource deadlock would occur */
#define ROC_ENAMETOOLONG	36	/* File name too long */
#define ROC_ENOLCK		37	/* No record locks available */
#define ROC_ENOSYS		38	/* Function not implemented */
#define ROC_ENOTEMPTY	39	/* Directory not empty */
#define ROC_ELOOP		40	/* Too many symbolic links encountered */
#define ROC_EWOULDBLOCK ROC_EAGAIN	/* Operation would block */
#define ROC_ENOMSG		42	/* No message of desired type */
#define ROC_EIDRM		43	/* Identifier removed */
#define ROC_ECHRNG		44	/* Channel number out of range */
#define ROC_EL2NSYNC	45	/* Level 2 not synchronized */
#define ROC_EL3HLT		46	/* Level 3 halted */
#define ROC_EL3RST		47	/* Level 3 reset */
#define ROC_ELNRNG		48	/* Link number out of range */
#define ROC_EUNATCH		49	/* Protocol driver not attached */
#define ROC_ENOCSI		50	/* No CSI structure available */
#define ROC_EL2HLT		51	/* Level 2 halted */
#define ROC_EBADE		52	/* Invalid exchange */
#define ROC_EBADR		53	/* Invalid request descriptor */
#define ROC_EXFULL		54	/* Exchange full */
#define ROC_ENOANO		55	/* No anode */
#define ROC_EBADRQC		56	/* Invalid request code */
#define ROC_EBADSLT		57	/* Invalid slot */

#define ROC_EDEADLOCK ROC_EDEADLK

#define ROC_EBFONT		59	/* Bad font file format */
#define ROC_ENOSTR		60	/* Device not a stream */
#define ROC_ENODATA		61	/* No data available */
#define ROC_ETIME		62	/* Timer expired */
#define ROC_ENOSR		63	/* Out of streams resources */
#define ROC_ENONET		64	/* Machine is not on the network */
#define ROC_ENOPKG		65	/* Package not installed */
#define ROC_EREMOTE		66	/* Object is remote */
#define ROC_ENOLINK		67	/* Link has been severed */
#define ROC_EADV		68	/* Advertise error */
#define ROC_ESRMNT		69	/* Srmount error */
#define ROC_ECOMM		70	/* Communication error on send */
#define ROC_EPROTO		71	/* Protocol error */
#define ROC_EMULTIHOP	72	/* Multihop attempted */
#define ROC_EDOTDOT		73	/* RFS specific error */
#define ROC_EBADMSG		74	/* Not a data message */
#define ROC_EOVERFLOW	75	/* Value too large for defined data type */
#define ROC_ENOTUNIQ	76	/* Name not unique on network */
#define ROC_EBADFD		77	/* File descriptor in bad state */
#define ROC_EREMCHG		78	/* Remote address changed */
#define ROC_ELIBACC		79	/* Can not access a needed shared library */
#define ROC_ELIBBAD		80	/* Accessing a corrupted shared library */
#define ROC_ELIBSCN		81	/* .lib section in a.out corrupted */
#define ROC_ELIBMAX		82	/* Attempting to link in too many shared libraries */
#define ROC_ELIBEXEC	83	/* Cannot exec a shared library directly */
#define ROC_EILSEQ		84	/* Illegal byte sequence */
#define ROC_ERESTART	85	/* Interrupted system call should be restarted */
#define ROC_ESTRPIPE	86	/* Streams pipe error */
#define ROC_EUSERS		87	/* Too many users */
#define ROC_ENOTSOCK	88	/* Socket operation on non-socket */
#define ROC_EDESTADDRREQ	89	/* Destination address required */
#define ROC_EMSGSIZE	90	/* Message too long */
#define ROC_EPROTOTYPE	91	/* Protocol wrong type for socket */
#define ROC_ENOPROTOOPT	92	/* Protocol not available */
#define ROC_EPROTONOSUPPORT	93	/* Protocol not supported */
#define ROC_ESOCKTNOSUPPORT	94	/* Socket type not supported */
#define ROC_EOPNOTSUPP	95	/* Operation not supported on transport endpoint */
#define ROC_EPFNOSUPPORT	96	/* Protocol family not supported */
#define ROC_EAFNOSUPPORT	97	/* Address family not supported by protocol */
#define ROC_EADDRINUSE	98	/* Address already in use */
#define ROC_EADDRNOTAVAIL	99	/* Cannot assign requested address */
#define ROC_ENETDOWN	100	/* Network is down */
#define ROC_ENETUNREACH	101	/* Network is unreachable */
#define ROC_ENETRESET	102	/* Network dropped connection because of reset */
#define ROC_ECONNABORTED	103	/* Software caused connection abort */
#define ROC_ECONNRESET	104	/* Connection reset by peer */
#define ROC_ENOBUFS		105	/* No buffer space available */
#define ROC_EISCONN		106	/* Transport endpoint is already connected */
#define ROC_ENOTCONN	107	/* Transport endpoint is not connected */
#define ROC_ESHUTDOWN	108	/* Cannot send after transport endpoint shutdown */
#define ROC_ETOOMANYREFS	109	/* Too many references: cannot splice */
#define ROC_ETIMEDOUT	110	/* Connection timed out */
#define ROC_ECONNREFUSED	111	/* Connection refused */
#define ROC_EHOSTDOWN	112	/* Host is down */
#define ROC_EHOSTUNREACH	113	/* No route to host */
#define ROC_EALREADY	114	/* Operation already in progress */
#define ROC_EINPROGRESS	115	/* Operation now in progress */
#define ROC_ESTALE		116	/* Stale NFS file handle */
#define ROC_EUCLEAN		117	/* Structure needs cleaning */
#define ROC_ENOTNAM		118	/* Not a XENIX named type file */
#define ROC_ENAVAIL		119	/* No XENIX semaphores available */
#define ROC_EISNAM		120	/* Is a named type file */
#define ROC_EREMOTEIO	121	/* Remote I/O error */
#define ROC_EDQUOT		122	/* Quota exceeded */

#define ROC_ENOMEDIUM	123	/* No medium found */
#define ROC_EMEDIUMTYPE	124	/* Wrong medium type */
#define ROC_ECANCELED	125	/* Operation Canceled */
#define ROC_ENOKEY		126	/* Required key not available */
#define ROC_EKEYEXPIRED	127	/* Key has expired */
#define ROC_EKEYREVOKED	128	/* Key has been revoked */
#define ROC_EKEYREJECTED	129	/* Key was rejected by service */

/* for robust mutexes */
#define ROC_EOWNERDEAD	130	/* Owner died */
#define ROC_ENOTRECOVERABLE	131	/* State not recoverable */
#endif
#endif

int rocme_porting_errno(void);

void rocme_porting_set_errno(int nVal);
#ifdef __cplusplus
};
#endif


#endif  /*_ROCME_ERRNO_H */
