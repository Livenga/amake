#ifndef _AMAKE_H
#define _AMAKE_H

#if defined(_USE_CODE_)
#include "makefile.h"
#include "source.h"
#endif


#define AMAKE_VERSION "0.0.1"
#define MAX_TARGET    (128)


/** 
 * @enum error_codes
 * エラー番号一覧
 */
enum {
  E_TARGET_NAME = 10,
  E_MKDIR
} error_codes;



/* src/make.c */
#if !defined(_MAKE_PROJECT)
extern int
make_c_project(const char *target,
               const int  f_verbose);
extern int
make_tex_project(const char *target,
                 const int  f_verbose);
#endif


/* src/utility.c */
extern int
eprintf(FILE *strm,
        const char *fname,
        const char *stts);


/* src/ctrl_char.c */
#if !defined(_CTRL_CHAR)
extern int
conf_char_len(char *dest,
              const char *src);
#endif
#endif
