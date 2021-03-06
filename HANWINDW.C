/*
 *  �a���a��  : �e�i�a���a�១
 *  ���� ���q : HANWINDW.C
 *  �e�e ��   : �� �� �b
 *  �i�a      : 1992.  6. 24
 *  ���� ���w : �w��(WINDOW) �ŝe �q��
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

#define MAXSTACK   10   /* �e���A �i�� �� ���e �w�� �A�� �� */

struct user_win_t {
  int left, top, width, height;
};
static void far *buf[MAXSTACK];

/* �� �aȂ�A�e ��A�a 0���a �e left, top, width, height�a ��w */
struct user_win_t stack[MAXSTACK];
/* �q�e �e�� �啡���� ���a�i ��w�a�e ���e */

/*
 * �w�� �aȂ ͡����
 * sp == 0�e �a�w�� �啡���i �i�e�a.
 */
static int sp = 0;

/*
 * �e�� �啡���� ���a�i �q�� ����..
 */
bool _Cdecl pushwindow(void)
{
  if(sp == MAXSTACK) {
    disperror(" ���� �啡�� �aȂ�� ��ñ ");
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

/* �a���� �{�e ���a �a�ሁ�i �b */
void _Cdecl eputchs(int left, int top, int width, byte ch)
{
  byte buf[81];
  register i;

  /* ch�� �����ụ ���a�i �e�i�� */

  for(i = 0; i < width; i++)
    buf[i] = ch;
  buf[i] = NULL;

  /* �� �b */

  eputsxy(left, top, buf);
}

/*
 * �A�� �a����
 *
 * clrfalg�a ON���e �A�� �����i ����
 * left�� top�e ��A�a �锁 ���a���A ���� �i ��.
 * �a �t�e 0���a �e �����a 0���a �b�e �����a �{�e �w���i ���b.
 * width�� height�e �A���� �췡�� �����i �a�a���e �e����
 * ���� �b�� �a �t�� 0���a �a�e �b�e �w�Ŵ��a.
 */
void _Cdecl drawbox(int left, int top, int width, int height, int clrflag)
{
  register y, cnt;

  eputsxy(-(abs(left)), -(abs(top)), "�");
  eputsxy(-(abs(left)), -(abs(top)+abs(height)-1), "�");

  eputchs(-(abs(left)+1), -(abs(top)), abs(width)-2, '�');
  eputchs(-(abs(left)+1), -(abs(top)+abs(height)-1), abs(width)-2, '�');

  eputsxy(-(abs(left)+abs(width)-1), -abs(top), "�");
  eputsxy(-(abs(left)+abs(width)-1), -(abs(top)+abs(height)-1), "�");
  for(y = -(abs(top)+1), cnt = 0; cnt < (abs(height)-2); cnt++, (y > 0) ? y++ : y--) {
    eputsxy(-abs(left), y, "�");
    eputsxy(-(abs(left)+abs(width)-1), y, "�");
  }
  if(clrflag) hclrscrxy(-(abs(left)+1), -(abs(top)+1), -(abs(width)-2), -(abs(height)-2));
}

/*
 * �w�� �i��,
 * ���� --> 1, ��́ : �A���� ����. --> 0
 * ���a��� ��a�i �a�� �g�a�� ����Ё�� �q
 * left�� top�e ���� �锁 �B�a�a ���a.
 * �a�a�� left�� top�e ���� 0���a �a�a.
 * �w�i �i�� ��Ё��e left, top���� 1���a �a��(��A�a ����)
 * width, height�e ��A�a ���� �������ᴡ �e�a.
 */
int _Cdecl wopen(int left, int top, int width, int height)
{
  long bufsize;

  if(!pushwindow())
    return;
/*  hwindow(1, 1, hgetmaxax(), hgetmaxay()); */
  /* textsize�� �锁���a��... ���� ϩ�a�a�� �����e.. */
  bufsize = htextsize(-(left-1), -(top-1), -(width+2), -(height+2));
  buf[sp-1]  = farmalloc(bufsize);
  if(buf[sp-1] == NULL) {  /* �A���� ���� */
    popwindow();
/*    releasehwindow(); */
    return 0;
  }
  /* �锁���a�� �១�a����Ё �w�i ���A�� ��� */
  hgettext(-(left-1), -(top-1), -(width+2), -(height+2), buf[sp-1]);
  drawbox(left-1, top-1, width+2, height+2, ON);
  hwindow(left, top, -width, -height);
  hgotoxy(1, 1);
  return 1;
}

/* �w�� �h�� */

void _Cdecl wclose(void)
{
/*  hwindow(1, 1, hgetmaxax(), hgetmaxay()); */
  hputtext(-(_CW->left/8), -(_CW->top/16), -(_CW->width/8+2), -(_CW->height/16+2), buf[sp-1]);
  farfree(buf[sp-1]);
  popwindow();
}

/*
 *  �w���� �w�a �A�����A �A���i �����a.
 */

void _Cdecl wtitle(byte *str)
{
  bool onoff, onoff2;

  onoff = isreverse();
  onoff2 = isunder();
  hsetunder(ON);
  hsetreverse(ON);

  /* �锁���a�A �b */
/*  eputchs(-(stack[sp-1].left-1), -(stack[sp-1].top-1), stack[sp-1].width+2, ' ');
  hputsxy(-(stack[sp-1].left+(stack[sp-1].width+2)/2-strlen(str)/2-1), -(stack[sp-1].top-1), str); */
  eputchs(-(_CW->left/8), -(_CW->top/16), _CW->width/8+2, ' ');
  hputsxy(-( _CW->left/8+(_CW->width/8+2-strlen(str))/2), -(_CW->top/16), str);

  /* ���� �wȁ ���� */
  hsetreverse(onoff);
  hsetunder(onoff2);
}

/* �e�� �w�� �� �w�����a�A ���a�i�i �a���A ���i���a �b�e�a. */

void _Cdecl wcenter(int y, byte *str)
{
  hputsxy((_CW->width/8-strlen(str))/2+1, y, str);
}

void _Cdecl wputs(int y, byte *str)
{
  hputsxy(1, y, str);
}

/* HANWINDW.C �� ���� �{ */
