#include <stdio.h>
#include <stdarg.h>
#include <bios.h>
#include "hanlib.h"
#include "hanerro2.h"

int prn_port = 0;   /* 0 = lpt1, 1 = lpt2 ... */

bool isOKprn(void)
{
  int res, prn_OK;

  res = biosprint(2, '*', prn_port) & 0x29;
  prn_OK = (res) ? false : true;
  return prn_OK;
}

bool lputc(unsigned char c)
{
  int res;

  while( 1 ) {
    res = biosprint(2, c, prn_port) & 0x29;
    if(res) {
      if(yesno(" ÏaŸ¥ÈáµA ·¥­áÐi ®ˆa ´ôŠ…¶a ", 0) == 0)
         continue;
      else
        return false;
    }
    else {
      break;
    }
  }
  biosprint(0, c, prn_port);
  return true;
}

bool lputs(unsigned char *s)
{
  while(*s) {
    if(!lputc(*s++))
      return false;
  }
  return true;
}

void lprintf(va_list arg_list, ...)
{
  va_list arg_ptr;
  char *format;
  char prtbuf[300];

  va_start(arg_ptr, arg_list);
  format = arg_list;
  vsprintf(prtbuf, format, arg_ptr);
  lputs(prtbuf);
}
