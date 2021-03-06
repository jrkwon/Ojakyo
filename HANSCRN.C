/* -------------------------- HANSCRN.C ------------------------- */

/*
 *   ���b�� �����A�� �a���e ���e ����
 *
 *   +------------------------------------------------------+
 *  1|                      �����e �A��                     |  <- ��ɷ
 *   +------------------------------------------------------+
 *  2+------------------------------------------------------+
 *  3| �� �����e �w�i ���Ё�� ���a�����i ��A�e�a.         |
 *   |                                                      |
 *   |                 +---------------+                    |
 *   |                 |  �s�� �A�A    |                    |
 *   |                 +---------------+                    |
 *   |                 |               |                    |
 *   .                 .               .                    .
 *   .                 .               .                    .
 *   |                 |               |                    |
 *   |                 +---------------+                    |
 *   |                                                      |
 * 24+------------------------------------------------------+
 *   +------------------------------------------------------+
 * 25| ���b�wȁ �a�� - �e/�w, ����, �s��, �a���� ���e �a��  |  <- ��ɷ
 *   +------------------------------------------------------+
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "hanout.h"
#include "hanin.h"
#include "hancolor.h"
#include "hancoord.h"
#include "hanwindw.h"
#include "hanerro2.h"
#include "handbms.h"
#include "hanprint.h"
#include "extkey.h"
#include "ascii.h"

int cur_col = 0, cur_row = 0;    /* �e�� ��᷁ ��á */
int screen_displayed;            /* ���e�A �i�� �a�� �A���e�� */
extern struct coord_t coord[MAXELE];    /* �b �a�a �a���� ���b���a */

struct {
  int prot;           /* ϩ�a�� ��ѡ �a�� - ON/OFF  */
  int (*edits)();     /* �b �a��(ϩ�a)���b ҁ ��З �i �q�� */
} sb [MAXELE];

int *elist;           /* �a�� ���a�a */
char *bf;             /* ���e ���� ͡���� */
char *tname;          /* ���b ���e�� �A�� */
char *prim_key;       /* ��ǡ�i ���aЁ���a */

int current_file;     /* �e�� �b�󺗷� �a�� ��ѡ */

byte picture[] = "#CcAa9HhEeKkLlYy!xX*";  /* �a�a���b�A �a���e ���� */
/* ****
 char *but_str[] = {
  "  ��w  ", "  �᭡  ", "  �|  ", "  ��  ", "  �� �|  ", "  �� ��  ", "  ����  ", "  �añ  " };
char query_help_str[] = "  PgUp-�|   PgDn-��   ^PgUp-�a�w �|   ^PgDn-�a�w ��   F5-�᭡  ESC-�{���� ";
 **** */
 
void (*_disp_card)(void);  /* ���� ���e�A �a�w�a�a �e�e ���e �b�i ���e �q�� ͡���� */

static int elp(int el);
static int no_flds(void);
static void data_coord(int el);
static void hookhangulmodetoggle(bool hangulmode);
static void hookinsertmodetoggle(bool insertmode);
/* static void hookmistyping(void); */
static void init_input(void);
static void close_input(void);
static int read_element(char type, char *msk, char *bfr, int el);
static void left_justify(char *s);
static void right_justify(char *s);
static void right_justify_zero_fill(char *s);
static int validate_date(char *s);
static void disp_element(char *b, char *msk, int el);

/* �������i �a���e�a */
void post_notice(char *s)
{
  disp_cmsg_sec(s, 1);
}

void clear_scrn(void)
{
  screen_displayed = FALSE;
  hclrscr();
}

/* ���e �១�i ���e ������ */
void init_screen(char *name, int *els, char *bfr)
{
  tname = name;
  elist = els;
  bf = bfr;
}

/* �b ϩ�a�A ��ѡ �����a�i ������a �E�a */
void protect(int el, int tf)
{
  sb[elp(el)].prot = tf;
}

/* �b �a��(el)�a ���b�E ҁ �����e �q���i ����e�a */
void edit(int el, int (*func)())
{
  sb[elp(el)].edits = func;
}

void clear_edit(void)
{
  int i;

  for(i = 0; i < MAXELE; i++)
    sb[i].edits = NULL;
}

/* �aǡ�a�A�� �����e �a�a�a����ѡ�A ��Ё,
 * �a�����a�a�A ��i�E �a�a�a���� �w�� ��ѡ
 * ���A �a�a �a����ѡ�i ���e �a�� ���a�a�A�� �y�弁���� ���a���a.
 * �a�� �a�a�a���a ���e �w�� ���A�a���i �a���g�a�a�� ����!
 */
static int elp(int el)
{
   int i;

   for (i = 0; *(elist + i); i++)
     if (el == *(elist + i))
       break;
     return i;
}

/* *************
void mark_pannel(int butt_ctr)
{
  static int flag = FALSE;
  int sum = BUTTON_GAP, ctr = butt_ctr;
  char ch1[2], ch2[2];
  bool onoff, onoff2;

  onoff = isreverse();
  onoff2 = isshadow();
  if(flag)
    hsetshadow(ON);
  else
    hsetreverse(ON);
  while(ctr--)
    sum += strlen(but_str[ctr])+BUTTON_GAP;
  ch1[1] = ch2[1] = '\0';
  ch1[0] = 16, ch2[0] = 17;
  hputsxy(-sum, -STATUS_Y, but_str[butt_ctr]);
  eputsxy(-sum, -STATUS_Y, flag ? " " : ch1);
  eputsxy(-(sum+strlen(but_str[butt_ctr])-1), -STATUS_Y, flag ? " " : ch2);
  if(flag)
    hsetshadow(onoff2);
  else
    hsetreverse(onoff);
  flag = !flag;
}
***************** */

/*
 *  �����E y���a(�锁���a)�A
 *  �e���i �e�� ���a�� �A�����i �b�e�a.
 */
void msg_bar(int y, byte *title)
{
   bool onoff;

   onoff = isreverse();
   hsetreverse(ON);
   eputchs(-1, -abs(y), hgetmaxax(), ' ');
   hputsxy(-(hgetmaxax()/2-strlen(title)/2), -abs(y), title);
   hsetreverse(onoff);
}

/*
 *  ���b�� ���� �b��A�� �a���e ���e�i �a�a���a.
 *  �wȁ���e �b�A�� �g�a��, �� �q���� �ᦉ�� �wȁ�� �b�q���i ���ᴡ.
 */
void display_template(char *title, int menu_flag)
{
   int i, el, ct; /* sum; */
   char detag[80], *cp1, *cp2;
   bool onoff;

   pushwindow();  /* �e�� �啡�� �wȁ ���� */

/*   hclrscrxy(-1, -1, hgetmaxax(), hgetmaxay()); */

   ct = no_flds();
   /* ���b ���e �A���� �a���� */
   drawbox(1, TITLE_Y+1, hgetmaxax(), hgetmaxay()-2, 1);
   msg_bar(TITLE_Y, title); /* ���e ��A �b�� �A�� �b */

   /* �a �e���A �w ��� */
   hwindow(2, TITLE_Y+2, hgetmaxax()-1, hgetmaxay()-1);
   screen_displayed = false;

/* ******
  if(menu_flag) {
     onoff = isshadow();
     hsetshadow(ON);
     hputsxy(-1, -STATUS_Y, query_help_str);
     eputchs(-strlen(query_help_str)-1, -STATUS_Y, hgetmaxax()-strlen(query_help_str), ' ');
     hsetshadow(onoff);
  }
  ******** */
/* ************
   if(menu_flag) {
     onoff = isshadow();
     hsetshadow(ON);
     eputchs(-1, -STATUS_Y, hgetmaxax(), ' ');
     for(sum = BUTTON_GAP, i = 0; i < 8; i++) {
       hputsxy(-sum, -STATUS_Y, but_str[i]);
       sum += strlen(but_str[i]) + BUTTON_GAP;
     }
     hsetshadow(onoff);
   }
************* */

   if(_disp_card)
     (*_disp_card)();
   for(i = 0; i < ct; i++) {
     el = *(elist + i);
     cp1 = elmask[el-1];
     cp2 = detag;
     while(*cp1 && cp2 < detag + sizeof detag - 1) {
       if(*cp1 & 0x80)
         *cp2++ = *cp1++, *cp2++ = *cp1++;
       else {
         *cp2++ = strchr(picture, *cp1) ?  ' ' : *cp1;
         cp1++;
       }
     }
     *cp2 = '\0';
     data_coord(el);  /* �a�a�a�� el�� ���b���a �t�i cur_col�� cur_row�A ��� */
     hputsxy(cur_col, cur_row, detag); /* ���e �����i �b */
     cur_col -= (strlen(hdenames[el-1])+1);
     onoff = isbold();
     hsetbold(ON);
     hputsxy(cur_col, cur_row, hdenames[el-1]); /* �e�i �a�a�a�� �b */
     hsetbold(onoff);
   }
   screen_displayed = TRUE;
   popwindow();
}

/* ���e ���b�i�A�� �a�a�i ���b�h�e�a */
int data_entry(char *pkey, int file)
{
  int (*validfunct)();
  int field_ctr, exitcode, el, index_ctr = 0;
  int field_ptr = 0, done = FALSE, isvalid;
  char *bfptr;

  prim_key = pkey;
  current_file = file;
  if (screen_displayed == FALSE)
    display_template(tname, 1);
  tally();
  field_ctr = no_flds();
  while(index_ele[file][0][index_ctr])
    index_ctr++;

  while (done == FALSE) {
     bfptr = bf + epos(elist[field_ptr], elist);
     el = *(elist + field_ptr);
     validfunct = sb[field_ptr].edits;
     if (sb[field_ptr].prot == FALSE) {
       exitcode = read_element(eltype[el-1], elmask[el-1], bfptr, el);
       isvalid = (exitcode != CANCELKEY && validfunct) ? (*validfunct)(bfptr, file/* exitcode */) : DBOK;
     }
     else {
       exitcode = DOWNARROW;
       isvalid = DBOK;
     }
     if (isvalid == DBOK) {
       switch (exitcode)  {
         case '\r' :
           if(field_ptr < index_ctr && spaces(bfptr))
             break;
           if(field_ptr+1 == field_ctr)
             done = TRUE, exitcode = SAVEKEY;
           else
             field_ptr++;
           break;
         case DOWNARROW : case '\t' :
           if(field_ptr < index_ctr && spaces(bfptr))
             break;
           else if(field_ptr+1 == field_ctr)
             field_ptr = index_ctr;
           else
             field_ptr++;
           break;
         case UPARROW : case SHIFT_TAB :
           if(field_ptr == index_ctr)
             field_ptr = field_ctr-1;
           else if(field_ptr)
             field_ptr--;
           break;
         case QUITKEY :
           done = TRUE;
           break;
         default:
           done = hookhgetdata(&exitcode);
           exitcode = _lastkey;
       }    /* switch */
     }   /* if */
     else { /* �b���e ϩ�a�A �����E �q�� ͡����A�� DBERROR�i ���a���v�a */
       done = TRUE;
       exitcode = ABORTKEY;
     }
  }   /* while */
  return (exitcode);
}

/* ���e ���b�i�A�� ϩ�a�� �����i ���e */
static int no_flds(void)
{
  int ct = 0;

  while (*(elist + ct))
    ct++;
  return ct;
}

/* �a�a �a���� ���b ���a */
static void data_coord(int el)
{
  cur_col = coord[elp(el)].x;
  cur_row = coord[elp(el)].y;
  hgotoxy(cur_col, cur_row);
}

/* 3�a���a�a ���a�i ���e�a. */
char *ins_comma(char *str)
{
  char tmp[80], tmp2[80];
  int i, j, len, tlen, comma, cnt;

  if(strchr(str, ','))
    return str;

  tlen = strlen(str);  /* ���� ���� */
  /* ���e ���� �A�� */
  for(i = 0, j = 0; i < tlen; i++)
    if(str[i] != ' ')
      tmp[j++] = str[i];
  tmp[j] = '\0';

  len = strlen(tmp);
  /* ���a ���� */
  comma = len/3;
  if((!(len % 3)) && len)
    comma--;
  for(i = len-1, j = tlen-1, cnt = 1; j >= 0; j--, cnt++) {
    if((!(cnt % 4)) && cnt && (i >= 0))
      tmp2[j] = ',';
    else {
     if(i < 0) {
        while(j)
          tmp2[j--] = ' ';
        tmp2[j] = ' ';
        break;
      }
      else {
        tmp2[j] = tmp[i];
        i--;
      }
    }
  }
  tmp2[tlen] = '\0';
  strcpy(str, tmp2);
  return str;
}

/* ���a�i �A���e�a. */

char *del_comma(char *str)
{
  char temp[80], *tmp, *tmp2, temp2[80], cnt=0;

  if(!strchr(str, ','))
    return str;
  tmp = temp;
  tmp2 = str;
  while(*tmp2) {
    if(*tmp2 != ',')
      *tmp++ = *tmp2++;
    else
      tmp2++, cnt++;
  }
  *tmp = '\0';
  tmp2 = temp2;
  while(cnt--)
    *tmp2++ = ' ';
  cnt = 0;
  while(temp[cnt])
    *tmp2++ = temp[cnt++];
  *tmp2 = '\0';
  strcpy(str, temp2);
  return str;
}

static void hookhangulmodetoggle(bool hangulmode)
{
  char *kbd_type[2] = { "�e�i ?�鯢Գ", "�w��  ����Գ" };

  bool onoff;
  onoff = isreverse();
  hsetreverse(true);
  kbd_type[0][5 /* ?��á */] = ishan2board() ? '2' : '3';
  hputsxy(-2, -hgetmaxay(), hangulmode ? kbd_type[0] : kbd_type[1]);
  hsetreverse(onoff);
}

static void hookinsertmodetoggle(bool insertmode)
{
  bool onoff;

  onoff = isreverse();
  hsetreverse(true);
  hputsxy(-14, -hgetmaxay(), insertmode ? "�s��Գ" : "����Գ");
  hsetreverse(onoff);
}

/*
 *  �e�� �a�a ��ѡ / �a�a�� �� ����
 */
void disp_record_number(int file_no, RPTR cur_rec)
{
  char total[20], cur[20], rec_status[40];
  RPTR total_rec;
  bool onoff;

  onoff = isreverse();
  hsetreverse(true);
  /* ���a�a ���i ���e�a */
  total_rec = get_total_record(file_no);
  ltoa(total_rec, total, 10);
  ins_comma(total);
  /* �e�� �a�a ��ѡ */
  if(cur_rec == -1L) {
    strcpy(cur, "�a�a ���b ��");  /* 13�a�a �� �g�a�� */
  }
  else if(cur_rec == 0L) {
    strcpy(cur, "�a�a ���� ��");  /* 13�a�a �� �g���� */
  }
  else {
    ltoa(cur_rec, cur, 10);
    ins_comma(cur);
  }
  sprintf(rec_status, "%13s / %-13s", cur, total);
  hprintfxy(-21, -hgetmaxay(), "%29s", rec_status);
  hsetreverse(onoff);
}

/*
static void hookmistyping(void)
{
  sound(600);
  delay(100);
  nosound();
}
*/
static void init_input(void)
{
  _hookhangulmodetoggle = hookhangulmodetoggle;
  _hookinsertmodetoggle = hookinsertmodetoggle;
/*  _hookmistyping = hookmistyping; */
/*  _hookhgetdata = hookhgetdata; */
}

static void close_input(void)
{
  _hookhangulmodetoggle = NULL;
  _hookinsertmodetoggle = NULL;
/*  _hookmistyping = NULL; */
  _hookhgetdata = NULL;
}

/*
 *
         1         2         3         4         5         6         7
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 �e�i ?�鯢Գ�s��Գ 2,147,483,648 / 2,147,483,648 ԳSTUDENTS.DATԳ�LF10 �a���a�M
                    +---------------------------+    +----------+
                      �A�� ���e�q �a���e �s�a���a    �b�� �� �a��
 *
 *  file_no  :  �e�� �b���a�� ���e �a�� ��ѡ
 *  cur_rec  :  �e�� �b�� �a���A�� �e�� �Aš�a��ѡ( ǡ ����)
 *              -1L���e, ������ �a�a�i �a�a�e �w������
 *               0L���e, �a�a�i �����a�e �w�����a.
 */
void disp_record_status(int file_no, RPTR cur_rec)
{
/*  char *kbd_type[2] = { "�e�i ?�鯢Գ", "�w��  ����Գ" };
  char total[20], cur[20], rec_status[40];
  RPTR total_rec; */
  bool onoff;

  onoff = isreverse();
  hsetreverse(true);

  eputchs(-1, -hgetmaxay(), hgetmaxax(), ' ');
  hookhangulmodetoggle(_hangulmode);
  hookinsertmodetoggle(_insertmode);
  disp_record_number(file_no, cur_rec);
/*  kbd_type[0][5] = ishan2board() ? '2' : '3';
  hputsxy(-2, -hgetmaxay(), _hangulmode ? kbd_type[0] : kbd_type[1]);
  hputsxy(-14, -hgetmaxay(), _insertmode ? "�s��Գ" : "����Գ");

  total_rec = get_total_record(file_no);
  ltoa(total_rec, total, 10);
  ins_comma(total);
  if(total_rec != -1L) {
    ltoa(cur_rec, cur, 10);
    ins_comma(cur);
  }
  else
    strcpy(cur, "�a�a �{");
  sprintf(rec_status, "%13s / %-13s", cur, total);
  hprintfxy(-21, -hgetmaxay(), "%29s", rec_status);
*/
  hprintfxy(-51, -hgetmaxay(), "Գ%8s.DATԳ", strupr(dbfiles[file_no]));
  hputsxy(-67, -hgetmaxay(), "�LF10 �a���a�M");
  hsetreverse(onoff);
}

/*
 *  ���A ���b�i �h�e ����
 *
 *  �e�� �e�i �a���a�១�A �x���� �a�a�w�i �a�� �����a�e �a�q�� �{�a
 *
 *  H : ���b ҁ �a���� �១�i �g�e�a
 *  D : �i�a (���b ҁ �i�a�a �e.��.�� ���ᝡ �A�� ���e�� ��a
 *  N : ���a ���b ҁ ���e�� ���i, �E�� �����A�e �����i ����
 *  Z : ���a ���b ҁ ���e�� ���i, �E�� �����A 0�i ����
 *  M : ����i �e���i �� ���a.
 *  K : ���b�h�� �g�� �a�� ����a... (M --> K �� �a����a)
 *  C : ���a ���b ҁ ���e�� ���i, �E�������A ���� ������, 3�a�� �a�a ���a(,) �s��
 *      - �q�� �a���A ���� �e�a. �a�a �a���e ���a�a�� ���aЁ���e�a.
 *  G : �a�� �a�� ���b, �aā��a �a���A�� ���b�h�q. �a���e ! �a�� ���� �e�Q.
 */

bool hookhgetdata(int *keycodep)
{
  bool ans;
/*  , onoff;
  char kbd_type[] = "�e�i ?�鯢Գ"; */


/*  onoff = isreverse();
  hsetreverse(ON);*/
  if (keycodep == NULL) {  /* Initialization before key input */
/*    disp_record_status(current_file, 0L); */
    init_input();
/*    hsetreverse(onoff);*/
    return false;
  }
  switch (*keycodep) {
    case ESC : case DOWNARROW : case '\t' : case F1 : case UPARROW :
    case PGUPKEY :  case PGDNKEY : case CTRL_PGUP : case CTRL_PGDN :
    case F2  :  case F5 : case F7 : case F8  : case F10 :  case SHIFT_TAB :
      *keycodep = CR;  /* If *keycodep = CR or ESC, quit hgetline */
      close_input();
      ans = true;
      break;
    case ALT_K:
/*      kbd_type[5] = ishan2board() ? '3' : '2';
      hputsxy(-1, -hgetmaxay(), kbd_type);*/
      if (ishan2board()) {
        hsethan390board(issplitmode());
      } else {
        hsethan2board(issplitmode());
      }
      ans  = false;
      break;
    default :
      ans =  false;
      break;
  }
/*  hsetreverse(onoff); */
  return ans;
}

static int read_element(char type, char *msk, char *bfr, int el)
{
   char temp[80], tmpbuf[80] = "", tmpbuf2[80] = "";
   int c, len, i = 0, allowcanceldelline, restoreline, cuttail, allowfirstdelline;
   int tmpins;
   bool onoff;

   if(type == 'G') {
     /*
      *  �a�����b(�aā�� ���e �a��) ����
      *  �a���a���� ���q�e ���a �a���� ��ǡ�i ���w�e�a.
      *  �a�a�� �a���� �i��a�e �a���� �w�� ���sǡ�� �a�w�e ���a�w�a�a.
      */
   }
   else if(type == 'K') {
     /*
      *  �a�� ��� ��a.
      */
     return _lastkey;
   }
   else if(type == 'M') {
     /*
      *  �A�� ϩ�a
      *  �a�����q�� �a�e ���� ���i�� �A���a..
      *  �a�����q.HTL
      *  ���a�� �e�i�e, �A�V��. ���� �a�����q�e
      *  �| 8�a�� ������ �A���� Ё���V�a.

      sprintf(temp, "%8s.HTL", denames[el]);
      editor(....temp);
      */
   }
   else {  /* �a ���A�� �a�a���b */
/*     sethwindow(2, TITLE_Y+1, hgetmaxax()-1, STATUS_Y-1); */
/*     pushwindow();
     hwindow(2, TITLE_Y+2, hgetmaxax()-1, hgetmaxay()-1); */
     data_coord(el);
     len = strlen(bfr);
     strcpy(temp, bfr);
     strcpy(tmpbuf, bfr);
     _hookhgetdata = hookhgetdata;
     allowcanceldelline = _allowcanceldelline, restoreline = _restoreline;
     cuttail = _cuttail, allowfirstdelline = _allowfirstdelline;
     _allowcanceldelline = _restoreline = _cuttail = _allowfirstdelline = false;
     putindata(tmpbuf, msk, tmpbuf2);
     strcpy(tmpbuf, tmpbuf2);
     if(type == 'C') {
       del_comma(tmpbuf);
       left_justify(tmpbuf);
     }
     tmpins = _insertmode;
     /* ���a ���b�� �ŝe�E �w���e �����wȁ�� */
     if(type == 'C' || type == 'D' || type == 'Z' || type == 'N')
       _insertmode = false;
     onoff = /*isunder(); */ isreverse();
     /* hsetunder(ON);     */ hsetreverse(ON);
     hgetdata(tmpbuf, msk);
     /* hsetunder(onoff); */ hsetreverse(onoff);
     _insertmode = tmpins;
     c = _lastkey;

     /* buff�A�� ���w(picture)�A�� */
     pickoutdata(tmpbuf, msk, tmpbuf2);
     while(tmpbuf[0] && len > i) {
       temp[i] = tmpbuf2[i];
       i++;
     }
     _allowcanceldelline = allowcanceldelline, _restoreline = restoreline;
     _cuttail = cuttail, _allowfirstdelline = allowfirstdelline;
     if (c != ESC) { /* ���b �i���a �᭡�A�� �g�v�a�e */
        switch(type) { /* �a�a�a���� �w�A �a�a �i���i ��a */
          case 'D' :
            validate_date(temp);
            break;
          case 'Z' :
            right_justify_zero_fill(temp);
            break;
          case 'N' :
            right_justify(temp);
            break;
          case 'C' :
            ins_comma(temp);
            break;
        } /* switch */
     } /* if */
     strcpy(bfr, temp);
/*     popwindow(); */
/*     sethwindow(2, TITLE_Y+1, hgetmaxax()-1, STATUS_Y-1); */
     data_coord(el);
     disp_element(bfr,msk,el);
     if(hookhgetdata(&c))
       return _lastkey;
   }
   return (c);
}

/* ���e�A�� �a�a�a���i ��Ȃ�h����Ё */
static int onoff_element(int el)
{
  bool onoff;
  int ch;

  data_coord(el);
  cur_col -= (strlen(hdenames[el-1])+1);
  onoff = isreverse();
  hsetreverse(ON);
  hputsxy(cur_col, cur_row, hdenames[el-1]); /* �e�i �a�a�a�� �b */
  hsetreverse(onoff);
  ch = getxch();
  hputsxy(cur_col, cur_row, hdenames[el-1]); /* �e�i �a�a�a�� �b */
  return ch;
}

/* �w�� ��Ȃ �A�A */
static int sel_menu(void)
{
  char *title =
    " Ԅ      �w�� ��Ȃ�a�� �w�w      Ԅ ";
  char *menu[] = {
    " 1. �w�� ��Ȃ ����              SPC ",
    " 2. �w�� ��Ȃ �����e �a�q ����   �� ",
    " 3. �e �w�� �a�q�a�� ����       Tab ",
    " 4. �e �w�� ����a�� ����      #Tab ",
    " 5. �A�� �� �w���a�� ����      Home ",
    " 6. �A�� �a���b �w���a�� ����   End ",
    " 7. ���� ��Ȃ                     + ",
    " 8. ���� ��Ȃ �᭡                - ",
    " 9. �᭡�a�� �añ               ESC ",
    " 0. �a�a �b�a�� �añ           F7 "
  };
  int ret_code[] = {
    ' ', CR, TAB, SHIFT_TAB, HOMEKEY, ENDKEY, '+', '-', QUITKEY, OUTPUTKEY
  };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 8, 10, menu, title, "1234567890", 0, 1);
  if(ans == -1)
     return -1;
  return ret_code[ans];
}

/*
 *  �a�a �b �b��A��
 *  �b�i �a���i ��Ȃ�e�a��a �a�e �w���A �a���a.
 *  ���a���e �t�e ��Ȃ�E �a�a�a�� ���a�a���a,
 *  �� ���a�a�� �a���b�e -1���a.
 *  ����A�e ��Ȃ�a�w�e �A�� �e���i
 *  �a����(80�i�� ����)�A�� �e���� �b�i �� ���e ���a�� �A�e�i
 *  �����a�a, �a����e �e�� ��Ȃ�E �a�a�a���a �a���a�e �e���i
 *  ���a����, �a�ỡ�e �a�w�a�A�A �{���e ���a�� �e�a.
 */
int *get_ele_list(int *ele_list)
{
  int field_ctr, ans, el, width, coloum;
  int field_ptr = 0, done = FALSE, cnt, ret;
  char msg[80];
  bool onoff, skip_flag;

  coloum = 0;
  skip_flag = false;
  onoff = isreverse(); hsetreverse(true);
  /*                                 1          2        3         4         5         6         7         8  */
  /*                        12345678901234567890123456789012345678901234567890123456789012345678901234567890  */
  hputsxy(-1, -hgetmaxay(), " SPC-��Ȃ  ��-��Ȃ&����  Tab-����  ESC-�᭡  �LF7-�b�M �L��Ȃ�E �e ��   0�e�M");
  /*  hputsxy(-1, -hgetmaxay(),    " SPC-��Ȃ  ��-��Ȃ&����  Tab-����  ESC-�᭡  �LF7-�b�M                       "); */
  hsetreverse(onoff);
/* *************
  onoff = isreverse();
  hsetshadow(ON);
  eputchs(-1, -STATUS_Y, hgetmaxax(), ' ');
  hputsxy(-1, -STATUS_Y, "  [�a������]-��Ȃ����   ��-��Ȃ����   ԑ-Ԑ �a�q�w��    F2-�b    ESC-�᭡");
  hsetshadow(onoff);
*********** */
  field_ctr = no_flds();
  /* ��Ȃ ���a�a ������ */
  for(cnt = 0; cnt < field_ctr; cnt++)
    ele_list[cnt] = 0;
  ele_list[cnt] = -1;
  while (done == FALSE) {
     onoff = isreverse(); hsetreverse(true);
     hprintfxy(-73, -STATUS_Y, "%3d", coloum);
     hsetreverse(onoff);

     el = *(elist + field_ptr);
     if(!skip_flag)
       ans = onoff_element(el);
     else
       skip_flag = false;
     switch (ans)  {
       case MENUKEY :
         ret = sel_menu();
         if(ret != -1) {
           ans = ret;
           skip_flag = true;
         }
         break;
       case '+' :  /* all select */
         coloum = 0;
         for(cnt = 0; cnt < field_ctr; cnt++) {
           ele_list[cnt] = *(elist + cnt);
           width = headlen(ele_list[cnt]);
           coloum = coloum + width + 1;
           data_coord(ele_list[cnt]);
           hputsxy(cur_col-1, cur_row, "��");
         }
         ele_list[cnt] = -1;
         break;
       case '-' :  /* all unselect */
         for(cnt = 0; cnt < field_ctr; cnt++) {
           ele_list[cnt] = 0;
/*           width = headlen(*(elist + cnt));
           coloum = coloum - width - 1; */
           data_coord(*(elist + cnt));
           hputsxy(cur_col-1, cur_row, "  ");
         }
         ele_list[cnt] = -1;
         coloum = 0;
         break;
       case HOMEKEY :
         field_ptr = 0;
         break;
       case ENDKEY :
         field_ptr = field_ctr-1;
         break;
       case DOWNARROW : case '\t' : case RIGHTARROW :
         if(field_ptr+1 == field_ctr)
           field_ptr = 0;
         else
           field_ptr++;
         break;
       case UPARROW : case SHIFT_TAB : case LEFTARROW :
         if(field_ptr)
           field_ptr--;
         else
           field_ptr = field_ctr-1;
         break;
       case QUITKEY : /* �᭡ */
         if(yesno(" �w�� ��Ȃ �b��i ���e�a���V�s���a ? ", 0) == 0) {
           ele_list[0] = 0;
           return NULL;
         }
         break;
       case OUTPUTKEY : /* ��Ȃ�i �aá�� �a�a �b�a�� .. */
         if(yesno(" ��Ȃ�E �w���i �b�a���V�s���a ? ", 0) == 0) {
           done = TRUE;
           ele_list[field_ctr] = -1;
         }
         break;
       case ' ' :
         if(!ele_list[field_ptr]) {
           width = headlen(el);
/* *********
           if(line_width+width+1 >= PAPERWIDTH) {
             sprintf(msg, " %d�e �a�� ��w�S���a ", PAPERWIDTH);
             disperror(msg);
             break;
           }
************ */
           ele_list[field_ptr] = el;
           coloum = coloum + width + 1;
         }
         else {
           width = headlen(el);
           ele_list[field_ptr] = 0;
           coloum = coloum - width - 1;
         }
         data_coord(el);
         hputsxy(cur_col-1, cur_row, ele_list[field_ptr] ? "��" : "  ");
         break;
       case '\r' :
         if(!ele_list[field_ptr]) {
           width = headlen(el);
/* ************
           if(line_width+width+1 >= PAPERWIDTH) {
             sprintf(msg, " %d�e �a�� ��w�S���a ", PAPERWIDTH);
             disperror(msg);
             break;
           }
******** */
           ele_list[field_ptr] = el;
           coloum = coloum + width + 1;
         }
         else {
           width = headlen(el);
           ele_list[field_ptr] = 0;
           coloum = coloum - width - 1;
         }
         data_coord(el);
         hputsxy(cur_col-1, cur_row, ele_list[field_ptr] ? "��" : "  ");
         if(field_ptr+1 == field_ctr)
           field_ptr = 0;
         else
           field_ptr++;
         break;
     }    /* switch */
  }   /* while */
  return ele_list;
}

/* �E�� ���i�a�� ���e���� ���e�e �����a�� �����a */
static void left_justify(char *s)
{
  int len, cnt = 0, cnt2;
  char tmp[40], *str;

  len = strlen(s);
  str = s;
  while(*str) {
    if(*str == ' ')
      str++;
    else
      tmp[cnt++] = *str++;
  }
  cnt2 = len - cnt;
  while(cnt2--)
    tmp[cnt++] = ' ';
  tmp[cnt] = '\0';
  strcpy(s, tmp);
}

/* ���a�i s�i ���e�� ���i(���e�e �����a�� �����a */
static void right_justify(char *s)
{
  int len;

  len = strlen(s);
  while (*s == ' ' && len)   {
    len--;
  *s++ = ' ';
  }
  if (len)
    while (*(s+(len-1)) == ' ')     {
      mov_mem(s, s+1, len-1);
      *s = ' ';
    }
}

/* ���a�i s�i ���e�� ���i(���e�e 0�a�� �����a */
static void right_justify_zero_fill(char *s)
{
  int len;

  if (spaces(s))
    return;
  len = strlen(s);
    while (*(s + len - 1) == ' ')   {
  mov_mem(s, s + 1, len-1);
    *s = '0';
  }
}

/* ���a�i c�e�A �����e �i�᷶�a�e �q �t�i ���a���a */
int spaces(char *c)
{
   while (*c == ' ')
     c++;
   return !*c;
}

/* ���a�i s�a �e������ �A��� �b�b�� �t�� ��w�e�a  */
static int validate_date(char *s)
{
  static int days [] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
  char date [7];
  int mo, yr;

  strncpy(date, s, 6);
  date[6] = '\0';
  if (spaces(date))
    return DBOK;
  *(date + 4) = '\0';
  mo = atoi(date+2);
  *(date + 2) = '\0';
  yr = atoi(date);
  days[1] = (yr % 4)  ? 28 : 29;
  if (mo && mo < 13 && atoi(s+4) && atoi(s+4) <= days [mo - 1])
    return DBOK;
  post_notice("�i�a�a �i���A����a, �e.��.�� ���ᝡ �A�ᴡЁ�a");
  return DBERROR;
}

/* ���e�� ���e ϩ�a�A �a�a �a�� �t �b */
void tally(void)
{
   int *els = elist;

/*   pushwindow();
   hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-1); */
   while (*els)
     put_field(*els++);
/*   popwindow(); */
}

/* �a�a �a���i ���e �a�a�a�� �q�A ���e�A �b�e�a */
void put_field(int el)
{
   data_coord(el);
   disp_element(bf + epos(el, elist), elmask[el - 1], el);
}

/* b�e ���e ����A�� �e�� ϩ�a�� ��á  ͡����, �a�a �a���i ���e�A �b */
static void disp_element(char *b, char *msk, int el)
{
   char merge[80];
   register i = 0;

   if(eltype[el-1] == 'G') { /* �a�� �a���� �w�� */
     /*
      * prime_key�i �a�����q�a�� �a�e PCX�a���i �����
      * ��Ё�� ���a�� �a���� ���e�A �b�e�a.
      * �a�a�� �a�a�a�� ���A �a���� ���e �a�a�a���� �w���A�e
      * ��ǡ�i 8�a ������ �a�e�A ���V��?
      */
     /* put_pcx(prim_key); */ /* PCX�a�� ���� */
   }
   else if(eltype[el-1] == 'M') {
     hputs(">>����<<");
   }
   else { /* �a ���A�� �w�� */
     while (*msk)    {
       if(*msk & 0x80) {
         merge[i++] = *msk++;
         merge[i++] = *msk++;
       }
       else {
         merge[i] = strchr(picture, *msk) ? *b++ : *msk;
         msk++, i++;
       }
     }
     merge[i] = '\0';
     hputs(merge);   /* ���e�i�i ͡�q�e �a�a�a���� ���a�i */
   }
}


