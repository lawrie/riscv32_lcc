#ifndef __TERMIOS_H__
#define __TERMIOS_H__

#define FIONBIO          0x5421

#define TCGETS           0x5401
#define TCSETS           0x5402

#define ECHO             0000010
#define ICANON           0000002
#define ISIG             0000001
#define IXON             0002000

#define VTIME            5
#define VMIN             6

typedef unsigned char    cc_t;
typedef unsigned int     speed_t;
typedef unsigned int     tcflag_t;

#define NCCS             32

struct termios {
    tcflag_t c_iflag;                /* input mode flags */
    tcflag_t c_oflag;                /* output mode flags */
    tcflag_t c_cflag;                /* control mode flags */
    tcflag_t c_lflag;                /* local mode flags */
    cc_t c_line;                     /* line discipline */
    cc_t c_cc[NCCS];                 /* control characters */
    speed_t c_ispeed;                /* input speed */
    speed_t c_ospeed;                /* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
  };

#endif  /* __TERMIOS_H__ */

