#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define _CTRL_CHAR
#include "../include/amake.h"


int
conf_char_len(char *dest,
              const char *src)
{
  if(strlen(src) >= (MAX_TARGET - 1)) {
    return E_TARGET_NAME;
  }

  strncpy(dest, src, strlen(src));
  return 0;
}
