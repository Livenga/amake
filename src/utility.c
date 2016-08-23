#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/**
 * @fn eprintf
 *
 * @param (strm)  {FILE *}
 * @param (fname) {const char *} 関数名
 * @param (stts)  {const char *} ファイル名などのステータス
 * @return        {int)
 */
int
eprintf(FILE *strm,
        const char *fname,
        const char *stts)
{
  extern int errno;

  if(stts)
    return fprintf(strm, "%s: %s %s\n", fname, stts, strerror(errno));
  else
    return fprintf(strm, "%s: %s\n", fname, strerror(errno));
  return 0;
}
