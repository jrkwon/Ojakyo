#include <stdarg.h>

#define PAPERWIDTH   116

extern int prn_port;

bool isOKprn(void);
bool lputc(unsigned char c);
bool lputs(unsigned char *s);
void lprintf(va_list arg_list, ...);
