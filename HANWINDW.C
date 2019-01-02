/*
 *  œaù°ãaúë  : –eãiúa∑°ßaú·ü°
 *  —¡∑© ∑°üq : HANWINDW.C
 *  †eóe ∑°   : ä• ∏Å úb
 *  êiºa      : 1992.  6. 24
 *  —¡∑© êÅ∂w : ¿w¢Ö(WINDOW) â≈ùe –qÆÅ
 */

#include <stdlib.h>
#include <alloc.h>
#include <stdarg.h>
#include <string.h>
#include "hanout.h"
#include "hancolor.h"
#include "hancoord.h"
#include "hanwindw.h"
#include "hanerro2.h"

#define MAXSTACK   10   /* –eå·§ÂµA µiü© ÆÅ ∑∂ìe ¿w∑Å ¬AîÅ ÆÅ */

struct user_win_t {
  int left, top, width, height;
};
static void far *buf[MAXSTACK];

/* ∑° Øa»ÇµAìe ¥ÂπAêa 0•°îa «e left, top, width, heightàa ∏·∏w */
struct user_win_t stack[MAXSTACK];
/* ∏qåe —e∏Å ∂Âï°∂Å∑Å π¡Œaüi ∏·∏w–aìe â∑àe */

/*
 * ¿w∑Å Øa»Ç Õ°∑•»·
 * sp == 0∑e §a»w∑Å ∂Âï°∂Åüi †i–eîa.
 */
static int sp = 0;

/*
 * —e∏Å ∂Âï°∂Å∑Å π¡Œaüi ∏qØ° •°â≈..
 */
bool _Cdecl pushwindow(void)
{
  if(sp == MAXSTACK) {
    disperror(" ∑±Ø° ∂Âï°∂Å Øa»Ç∑° êÒ√± ");
    return false;
  }
  stack[sp].left = _CW->left/8 + 1, stack[sp].top = _CW->top / 16 + 1;
  stack[sp].width = _CW->width/8, stack[sp].height = _CW->height / 16;
  sp++;
  return true;
}

bool _Cdecl popwindow(void)
{
  if(sp == 0)
    return false;
  sp--;
  hwindow(stack[sp].left, stack[sp].top, -stack[sp].width, -stack[sp].height);
  true;
}

/* àaù°ù° à{∑e ¢Ö∏a µaú·àÅüi ¬âùb */
void _Cdecl eputchs(int left, int top, int width, byte ch)
{
  byte buf[81];
  register i;

  /* chù° ∑°ûÅ¥·ª• ¢Ö∏aµi †eóiã° */

  for(i = 0; i < width; i++)
    buf[i] = ch;
  buf[i] = NULL;

  /* ¨Â ¬âùb */

  eputsxy(left, top, buf);
}

/*
 * ëA°° ãaü°ã°
 *
 * clrfalgàa ON∑°°e ëA°° êÅ¶Åüi ª°∂ë
 * leftµ¡ top∑e ¥ÂπAêa ∏ÈîÅ π¡Œa∑±µA ∫Å∑Å –i àı.
 * ãa àt∑e 0•°îa «e àı∑°êa 0•°îa ∏b∑e àı∑°êa à{∑e §wØ¢∑i ï∑∏b.
 * widthµ¡ heightìe ëA°°∑Å êÏ∑°µ¡ ëº∑°üi êa»aêÅìe •eÆÅù°
 * ∑°àı µbØ° ãa àt∑° 0•°îa «aóe ∏bóe ¨wâ≈¥Ùîa.
 */
void _Cdecl drawbox(int left, int top, int width, int height, int clrflag)
{
  register y, cnt;

  eputsxy(-(abs(left)), -(abs(top)), "⁄");
  eputsxy(-(abs(left)), -(abs(top)+abs(height)-1), "¿");

  eputchs(-(abs(left)+1), -(abs(top)), abs(width)-2, 'ƒ');
  eputchs(-(abs(left)+1), -(abs(top)+abs(height)-1), abs(width)-2, 'ƒ');

  eputsxy(-(abs(left)+abs(width)-1), -abs(top), "ø");
  eputsxy(-(abs(left)+abs(width)-1), -(abs(top)+abs(height)-1), "Ÿ");
  for(y = -(abs(top)+1), cnt = 0; cnt < (abs(height)-2); cnt++, (y > 0) ? y++ : y--) {
    eputsxy(-abs(left), y, "≥");
    eputsxy(-(abs(left)+abs(width)-1), y, "≥");
  }
  if(clrflag) hclrscrxy(-(abs(left)+1), -(abs(top)+1), -(abs(width)-2), -(abs(height)-2));
}

/*
 * ¿w¢Ö µiã°,
 * ¨˜â∑ --> 1, Ø©ÃÅ : °A°°ü° ¶Åπ¢. --> 0
 * π¡Œa§Ò∂· àÒ¨aüi –aª° ¥g∑aì° π°Ø±–Å¥° –q
 * leftµ¡ top∑e °°ñÅ ∏ÈîÅ …BØaÀa π¡Œa.
 * òaúa¨· leftµ¡ top∑e °°ñÅ 0•°îa «aîa.
 * ¿w∑i µiã° ∂·–Å¨·ìe left, top°°ñÅ 1•°îa «aâ°(¥ÂπAêa ¥∑ÆÅ)
 * width, heightìe ¥ÂπAêa ¥∑∑Å ∏˜ÆÅ∑°¥·¥° –eîa.
 */
int _Cdecl wopen(int left, int top, int width, int height)
{
  long bufsize;

  if(!pushwindow())
    return;
/*  hwindow(1, 1, hgetmaxax(), hgetmaxay()); */
  /* textsizeï° ∏ÈîÅπ¡Œaù°... ∑°úÈ œ©∂aåaª• ¥Ùª°†e.. */
  bufsize = htextsize(-(left-1), -(top-1), -(width+2), -(height+2));
  buf[sp-1]  = farmalloc(bufsize);
  if(buf[sp-1] == NULL) {  /* °A°°ü° ¶Åπ¢ */
    popwindow();
/*    releasehwindow(); */
    return 0;
  }
  /* ∏ÈîÅπ¡Œaù° ¿·ü°–aã°∂·–Å ¿w∑i ∏Â¡Aù° ¨È∏˜ */
  hgettext(-(left-1), -(top-1), -(width+2), -(height+2), buf[sp-1]);
  drawbox(left-1, top-1, width+2, height+2, ON);
  hwindow(left, top, -width, -height);
  hgotoxy(1, 1);
  return 1;
}

/* ¿w¢Ö îhã° */

void _Cdecl wclose(void)
{
/*  hwindow(1, 1, hgetmaxax(), hgetmaxay()); */
  hputtext(-(_CW->left/8), -(_CW->top/16), -(_CW->width/8+2), -(_CW->height/16+2), buf[sp-1]);
  farfree(buf[sp-1]);
  popwindow();
}

/*
 *  ¿w¢Ö∑Å ¨w∏a …AñÅü°µA πA°¢∑i ¶õ∑•îa.
 */

void _Cdecl wtitle(byte *str)
{
  bool onoff, onoff2;

  onoff = isreverse();
  onoff2 = isunder();
  hsetunder(ON);
  hsetreverse(ON);

  /* ∏ÈîÅπ¡ŒaµA ¬âùb */
/*  eputchs(-(stack[sp-1].left-1), -(stack[sp-1].top-1), stack[sp-1].width+2, ' ');
  hputsxy(-(stack[sp-1].left+(stack[sp-1].width+2)/2-strlen(str)/2-1), -(stack[sp-1].top-1), str); */
  eputchs(-(_CW->left/8), -(_CW->top/16), _CW->width/8+2, ' ');
  hputsxy(-( _CW->left/8+(_CW->width/8+2-strlen(str))/2), -(_CW->top/16), str);

  /* ∂•úÅ ¨w»Å •¢äÅ */
  hsetreverse(onoff);
  hsetunder(onoff2);
}

/* —e∏Å ¿w¢Ö êÅ ¨wîÅπ¡ŒaµA ¢Ö∏aµi∑i àa∂ÖïA ∏˜ùiØ°≈a ¬âùb–eîa. */

void _Cdecl wcenter(int y, byte *str)
{
  hputsxy((_CW->width/8-strlen(str))/2+1, y, str);
}

void _Cdecl wputs(int y, byte *str)
{
  hputsxy(1, y, str);
}

/* HANWINDW.C ∑Å —¡∑© è{ */
