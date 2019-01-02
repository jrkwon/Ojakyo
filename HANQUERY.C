/* --------------------------- HANQUERY.C -------------------------------*/

/*
 *  ¸aa ·³b, ®¸÷, ¬b¹A....
 *
 *  ¶A¦µA¬á ·¡ ¸aa·³b(®¸÷)¦µA ˆå‘Aº´á´¡ Ğa“e ·¥¸a“e ”a·q‰Á ˆ{”a.
 *
 *  1. ÀáŸ¡Ği ¸aaÌa·©· ¤åÑ¡
 *  2. ÀáŸ¡Ğa‰¡¸a Ğa“e ¸aa· ÀáŸ¡¬wÈŸi  iĞº‰ ÑÁ¡e¹A¡¢
 *  3. ÀáŸ¡Ği ¸aa¶a­¡¤åÑ¡
 *  4. ‹a ¸aa¶a­¡µA ”·wĞa“e ·³b ¶áÃ¡
 *
 *  ÑÁ¡eÀáŸ¡µÁ ‹a ¶A· ¸aa ·³bµA ”Ğe ¡¡—e ˆõ·i ÀáŸ¡Ğº…”a.
 *  Ğe¤åµA Ğaa· Ìa·© e ÀáŸ¡ˆa“wĞa”a.
 */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <string.h>
#include <dir.h>
#include "hanout.h"
#include "ascii.h"
#include "extkey.h"
#include "hancoord.h"
#include "hanwindw.h"
#include "hanerro2.h"
#include "hanprint.h"
#include "hanpop.h"
#include "handbms.h"

/* static void query_help_func(void); */
/* ** static int control_pannel(void); ** */
static void save_func(int file_no);
static void undo_func(int file_no);
static bool delete_func(int file_no);
static bool quit_func(char *msg);
static bool prev_func(int file_no, int key_no);
static bool next_func(int file_no, int key_no);
static bool go_first_func(int file_no, int key_no);
static bool go_last_func(int file_no, int key_no);
static void query(char *pkey, int file_no, int mode);
static void clear_record(int file_no);
static void rcdin(int file_no);
static void rcdout(int file_no);
static int empty(char *b, int l);
static int same(int file_no);
static void set_trap(int file_no);
static int key_entry(char *s, int file_no);
static void init_coord(struct coord_t crd[]);
static int init_data_ele(int data_ele[]);
static int init_query(int file_no, char *title, int data_ele[], struct coord_t crd[]);
static void close_query(int file_no);
/* static void list_help_func(void); */
static void disp_list(int y, int *filelist, int *dlist, char *buf, int offset, int mode);
static void disp_header(int *dlist);
/* static void disp_foot(void); */
static void disp_page(int key_no, int file_no, int *dlist, char *buf, int offset);
static char *db_list(int file_no, char *title, int key_no, int *dlist, int mode);
static void disp_field(char *b, char *msk, int el);
static void init_browse(int file_no, int data_ele[]);
static void print_card(unsigned char *buf, int *dlist, int file_no, int mode);

/* static int file;     */            /* <¸aaËi ¸÷·¦>µA¬á ¸÷·Ğe Íe»³Ği Ìa·©· ¤åÑ¡ */
/* static int exitflag; */          /* Àq· ˆt·i ˆa»¡¡e »©·¦Ÿi  aÃ¥”a.  */
static int existing_record;       /* ÑÁ¡eµA ¸aaˆa ¹¥¸Ğa¡e Àq */
static char *rb;                      /* AÅ¡—a ¤áÌá; Ğe Ìa·©µA ¹¥¸Ğa“e ¸å Ï©—aµA ”Ğ  */
static char *hb;                      /* AÅ¡—aˆa ˆ—¯¥–A´ö“e»¡ ÑÂ·¥Ğa‹¡¶áĞe ¥¡·A ¤áÌá	  */
static bool newflag;              /* ¬¡¶… ¸aa·³b·¡¡e true : UNDOµA¬á Àq¹¡ */
static int fl[] = { 0, -1 };      /* db_open()µA¬á ¬a¶w */
char *sc;                             /* ¹¥¸Ğa“e ¸å Ï©—aµA ”Ğe ˆõ·¡ ´a“¡œa Íe»³Ğaa‰¡
                                                        ¸å”i–E ·¥¸aµA ”Ğ¬á e, »b ÑÁ¡e ¤áÌá         */
static int len;                       /* AÅ¡—a· ‹©·¡ */
int *els, *tmp_els;                      /* ¸aa¶a­¡ Ÿ¡¯aËa */
static int list[MAXELE+1];      /* ¸aa¶a­¡—i· Ÿ¡¯aËaŸi ¸á¸wĞi ¤µi */
struct coord_t coord[MAXELE+1]; /* ¸aaÍe»³ ÑÁ¡eËiµA¬á ¹ÁÎaˆa ¸á¸w–I Š¹¡ÁA */
int no_ele;                            /* ÀáŸ¡Ği ¸aa¶a­¡· ˆ•® */
static FILE *result;            /* Â‰b¤wĞ··i ·¥­á‹¡¡ Ğa»¡´g‰¡ Ìa·©¡ Ğa“e ‰w¶Ÿi ¶áĞ */
static byte write_name[80];     /* Â‰b ¤wĞ··¡ Ìa·©·¥ ‰w¶ ‹a Ìa·© ·¡Ÿq */
void (*browse2update[MAXUPDATEFUNC])(int, char*);

extern byte picture[];          /* in HANSCRN.C */
extern int screen_displayed;

/* ¸aa Â‰b ¤wĞ· */
enum output_dir_t { TO_PRINT, TO_FILE };

/*
 *  rb : record buffer  ¸aa· ·³Â‰b·¡ ·¶´á´¡ ‹a ¶w·¡ À¶¡»±.
 *  sc : screen buffer  ¸aa ·³b‰Á ®¸÷µA¬á ³a·¡“e ÑÁ¡e ¶w ¤áÌá.
 *       ˜aœa¬á, ·³b,®¸÷ ¸b´óº—·¡œa¡e, Ñe¸ ¸b´óº—·¥ ¶w·¡ —i´á·¶”a.
 */

/* *********************************************************************** *
 *                ·¡ Ìa·©µA¬á ‰·É··a¡ ³a·¡“e Ğq®—i                       *
 * *********************************************************************** */

/*
 *  ¤a·¡œá¯a, ¸÷¸å, ¯©®¡ ·¥Ğe ¸aa Ìa·© ¬b¹A —w—w·
 *  ·¡·A¡ Ğ¬á ¸aaÌa·©‰Á ¬‚·¥Ìa·©µA ·¡¬w·¡ ¬—‰v·i ˜
 *  (¸÷¸å—w·a¡ ·¥Ğe ‰w¶“e ¸a•·¸â·a¡ ¬‚·¥Ìa·©·i ¥¢Š)
 *   e—e·¡µÁ ¸óÁ¢Ğ ¥¡œa“e ¡A¯¡»¡Ÿi Â‰bĞe”a.
 */
static void contact_jaerock(void)
{
  char *msg[] = {
    "  —¡¯aÇa ¶wœ··¡ ¦¹¢Ğe ˆõ·¡ ´a“¡œa¡e..  ",
    "  ¿u¿u... ¸aaÌa·©µA ¢…¹Aˆa ¬—‰vŠ…¶a.   ",
    "  ”á ·¡¬w· ¸b´ó·e  º—»¡Ğa¯¡‰¡          ",
    "  »b¯¡ ”a·q· µeœbÀá¡ µeœbĞa­a¬á •¡¶‘  ",
    "  ·i ¶aÀ÷Ğ º­A¶a.                     ",
    "ÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄ",
    "  Ô Ğe´·” ¸å¸aÉ·¯¥‰·Ğb‰Á ”Ğb¶¥       ",
    "     ·¥‰·»¡“wµeŠ¯©  (02)-290-0363      ",
    "  Ô HiTEL ID         rock88            ",
    "ÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄÔÄ",
        "                           1993. Š¥¸œb"
  };
  int cnt;

  if(wopen(hgetmaxax()/2-strlen(msg[0])/2, 11, strlen(msg[0]), 11)) {
    for(cnt = 0; cnt < 11; cnt++)
      wputs(1, msg[cnt]);
  }
  while( 1) {
    if(getxch() == ESC)
      break;
  }
  wclose();
}


static bool quit_func(char *msg)
{
  if(yesno(msg, 0) == 0) {  /* µ 0, ´a“¡µ¡ 1, Âá­¡ 2 */
        return true;
  }
  return false;
}

static bool delete_func(int file_no)
{
  if (spaces(sc)== 0)  {
        if(yesno("·¡ ¸aaŸi »¡¶‰Œa¶a ?", 1) == 0) { /* µ 0, ´a“¡µ¡ 1, Âá­¡ 2 */
          del_rcd(file_no);
          clear_record(file_no);
      return true;
        }
    return false;
  }
  return false;
}

static unsigned char *get_filename_to_write(unsigned char *name)
{
  if(win_hgetdata(40, " ¸á¸wĞi  ÑÁ·©·¡Ÿq·e ?", "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE", name)) {
    strcuttail(name);
    strupr(name);
    return name;
  }
  return NULL;
}

/*
 *  ¸aa Â‰b ¤wĞ· ¬é¸÷
 *  0 : ÏaŸ¥Èá¡
 *  1 : Ìa·©¡
 */
int output_dir_menu(void)
{
  char *title =
    "Ô„  ¸aa Â‰b ¤wĞ·  Ô„";
  char *menu[] = {
	" 1. ÏaŸ¥Èá¡ Â‰b     ",
	" 2. Ìa·©¡ Â‰b       ",
  };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 10, 2, menu, title, "12", 0, 1);
  if(ans == -1)
     return -1;
  return ans;
}

/*
 *  ¸aa Â‰b Ğw¡¢ ¬é¸÷
 *  0 : ¡¡—e Ğw¡¢ Â‰b
 *  1 : »¡¸÷Ğe Ğw¡¢ e
 */
/*
static int ele_sel_menu(void)
{
  char *title =
    "Ô„   ¸aa Â‰b Ğw¡¢   Ô„";
  char *menu[] = {
	" 1. ¡¡—e Ğw¡¢ Â‰b       ",
	" 2. »¡¸÷Ğe Ğw¡¢ e Â‰b   ",
  };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 10, 2, menu, title, "12", 0, 1);
  if(ans == -1)
     return -1;
  return ans;
}
*/

/* *********************************************************************** *
 *         ¸aa ·³b‰Á ®¸÷ —wµA¬á ¦¸â·a¡ ³a·¡“e Ğq®—i                *
 * *********************************************************************** */

static int empty(char *b, int l)
{
  while (l--)
    if (*b && *b != ' ')
      return FALSE;
    else
       b++;
  return TRUE;
}

/* AÅ¡—a ¤áÌáµÁ ¥¡·A¤áÌáˆa ”aŸe»¡ ˆñ¬a. »b, AÅ¡—aˆa ˆ—¯¥–A´ö“e»¡ */
static int same(int file_no)
{
  int ln = rlen(file_no);

  while (--ln)
    if (*(rb + ln) != *(hb + ln))
      break;
  return (*(rb + ln) == *(hb + ln));
}

/* ‹¡¥¥Ç¡ˆa ·³b–A´ö·i ˜ ‹aˆõ·i ÀáŸ¡Ği Ğq®Ÿi ¬é¸÷ */
static void set_trap(int file_no)
{
  int i = 0;

  while (index_ele [file_no] [0] [i])
    i++;
  edit(index_ele [file_no] [0] [i-1], key_entry);
}

/* ºÇ¡ˆa ·³b–A‰¡ a¬á ¤a¡ ·¡ Ğq®ˆa Ñ¡Â‰–E”a */
static int key_entry(char *s, int file_no)
{
  char key [MAXKEYLEN];
  int i;

  if (spaces(s))   /* ·³b–E ¸aaˆa ´ô”a¡e */
    return DBOK;
  *key = '\0';
  i = 0;
  while (index_ele [file_no] [0] [i])  {
    protect(index_ele[file_no][0][i],TRUE);
    strcat(key, sc + epos(index_ele[file_no][0][i++], els));
  }
  if (find_rcd(file_no, 1, key, rb, DB_EXACT) == DBERROR)  {
    post_notice("  ¬¡¶… ¸aa·³“¡”a  ");
    existing_record = FALSE;
    newflag = true;
    return DBOK;
  }
  else {
    disp_cmsg("  ·¡£¡ ˆ{·e ¸aaˆa ·¶¯s“¡”a  ");
	if(yesno(" ·¡ ¸aaŸi ®¸÷Ğa¯¡‰V¯s“¡Œa ? ", 0) == 0) { /* µ */
      rcdin(file_no);
      tally();
      newflag = false;
      return DBOK;
    }
    else {
      post_notice("  ¸b´ó·¡ Âá­¡–S“¡”a  ");
      return DBERROR;
    }
  }
}

/*
 * ¸aa¶a­¡Ÿi Íe»³Ği ¹ÁÎa Á¡‹¡ÑÁ
 * Ç¡¸aa¶a­¡· ¥¡Ñ¡Ÿi Î‰‰¡ ÑÁ¡e ¤áÌáŸi ‰·¤‚¢…¸a¡ À¶…”a.
 * ‹aŸ¡‰¡ ˆa¸w –á· ¸aa ¶áÃ¡¡ ·¡•·Ğe”a.
 */
static void clear_record(int file_no)
{
  int i = 0;

  while (index_ele [file_no][0][i])
    protect(index_ele[file_no][0][i++], FALSE);
  clrrcd(sc, els);
  existing_record = FALSE;
}

/* AÅ¡—a ¤áÌá· ¶w·i ÑÁ¡e¤áÌáµÁ ¥¡·A¤áÌáµA ¥¢¬a */
static void rcdin(int file_no)
{
  int i = 0;

  if (empty(rb, rlen(file_no)) == 0)  {
    rcd_fill(rb, sc, file_ele [file_no], els);
    mov_mem(rb, hb, rlen(file_no));
    existing_record = TRUE;
    while (index_ele [file_no] [0] [i])
      protect(index_ele[file_no][0][i++],TRUE);
  }
}

/* ¬ AÅ¡—aŸi ÂˆaĞaˆáa ·¡£¡ ·¶“e ¸aaŸi ˆ—¯¥Ğa‰¡, ”a¯¡ ¸aaËiµA ¸á¸w */
static void rcdout(int file_no)
{
  if (empty(sc, len) == 0)  {
    rcd_fill(sc, rb, els, file_ele[file_no]);
    if (existing_record)  {
      if (same(file_no) == 0)	{
        post_notice("  ¸aaŸi ¸á¸wĞs“¡”a  ");
        if(rtn_rcd(file_no, rb) == DBERROR) {
          disp_cmsg("  —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa ¸aaÌa·©µA ·¡¬w·¡ ·¶¯s“¡”a  ");
          contact_jaerock();
        }
      }
    }
    else  {
      post_notice("  ¬¡¶… ¸aaŸi ¸á¸wĞs“¡”a  ");
      if (add_rcd(file_no, rb) == DBERROR)
	      dberror();
    }
    clear_record(file_no);
  }
}

/* ”eÂˆa ¬åÈ‚–A¡e ‹a ”eÂ¤åÑ¡Ÿi •©aº‰¡, Âá­¡–A¡e -1·i •©aº…”a. */
/* *******
static int control_pannel(void)
{
  int isquit = FALSE, key, ans = 0;
  static int buttn_ptr = 0;

  do {
    mark_pannel(buttn_ptr);
    key = getxch();
    mark_pannel(buttn_ptr);
    switch(key) {
      case LEFTARROW : case SHIFT_TAB :
	      if(buttn_ptr == 0) buttn_ptr = BUTTON_CTR -1;
	      else		   buttn_ptr--;
	      break;
      case RIGHTARROW : case '\t' : case ' ' :
	      if(buttn_ptr == (BUTTON_CTR-1)) buttn_ptr = 0;
	      else		   buttn_ptr++;
	      break;
      case ESC : case UPARROW : case DOWNARROW :
	      isquit = TRUE;
	      ans = -1;
        break;
      case '\r' :
	      isquit = TRUE;
	      break;
    }
  } while(!isquit);
  return (ans == -1) ? ans : buttn_ptr;
}
****** */

static void save_func(int file_no)
{
  rcdout(file_no);
}

static void undo_func(int file_no)
{
  int ans;

  if(spaces(sc/* rb*/)== 0)  {
    ans = yesno("®¸÷Ğe ˆé ¶¥œ”¡ ĞiŒa¶a ?", 1);
    if(ans == 0) { /* µ 0, ´a“¡µ¡ 1, Âá­¡ 2 */
      rcdin(file_no);
    }
    else if(ans != 2 && existing_record) { /* ´a“¡µ¡ Ğ–“e•A, ¸aaˆa ¹¥¸Ğe”a */
      if(same(file_no) == 0)  {
        post_notice("  ¸aaŸi ¸á¸wĞs“¡”a  ");
        if(rtn_rcd(file_no, rb) == DBERROR) {
                 disp_cmsg("  —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa ¸aaÌa·©µA ·¡¬w·¡ ·¶¯s“¡”a  ");
                 contact_jaerock();
               }
          }
        }
  }
}

/* AÅ¡—a ¤áÌáˆa §¡´á·¶a? »b ‰·¤‚¢…¸a¡ e –A´á ·¶a? §¡´á·¶·a¡e Àq */
/* ÀáŸ¡Ği ¸aa· ¹ÁÎaŸi Á¡‹¡ÑÁĞe”a. */
static void init_coord(struct coord_t crd[])
{
  register i;

  for(i = 0; i < no_ele ; i++)
    coord[i].x = crd[i].x, coord[i].y = crd[i].y;
}

/*
 * ÀáŸ¡Ği ¸aa¶a­¡· ¢…¸aµi ¡¢¢·i Í¡·¥Èá ¤µi listµA ”q“e”a.
 */
static int init_data_ele(int data_ele[])
{
  int i;

  if( ! data_ele[0])
    return 0;
  for(i = 0; data_ele[i]; i++)
    list[i] = data_ele[i];
  return i;
}

/*
 * query Ğq® ¬a¶w·i ¶áĞe Á¡‹¡ÑÁ!
 * ¬÷‰·Ğa¡e 1, ¯©ÌĞa¡e 0·i •©aº…”a
 */

static int init_query(int file_no, char *title, int data_ele[], struct coord_t crd[])
{
  int count, i;

  fl[0] = file_no;
  db_open("", fl);   /* ‰w¡ »¡¸÷Ği ® ·¶•¡¢ ‰¡Áa´¡ */
  count = init_data_ele(data_ele);
  if (count == 0)  {                 /* ¡¡—e ¸aa¶a­¡Ÿi ÀáŸ¡Ğa‰V”a. */
    len = rlen(file_no);
    els = file_ele [file_no];
    for(i = 0; els[i]; i++)       /*  *file_ele[]· ¶a­¡· ˆ•® */
      ;
    no_ele = i;
  }
  else {
    len = epos(0, data_ele);
    els = data_ele;
    no_ele = count;
  }
  sc = (char *)farmalloc(len);        /* screen buffer */
  rb = (char *)farmalloc(rlen(file_no));  /* record buffer */
  hb = (char *)farmalloc(rlen(file_no));  /* hold buffer        */
  if (sc == (char *) 0 || rb == (char *) 0 ||  hb == (char *) 0)  {
    memerror();
    return FALSE;
  }
  init_rcd(file_no, rb);           /* rbŸi 'file'· Š¹¡µA ˜aœa ‰·¤‚·a¡ À¶…”a. */
  init_rcd(file_no, hb);           /* hbŸi 'file'· Š¹¡µA ˜aœa ‰·¤‚·a¡ À¶…”a. */
  init_screen(title, els, sc);
  init_coord(crd);
  return TRUE;
}

static void close_query(int file_no)
{
  clear_record(file_no);
  clear_edit();
  farfree(hb);
  farfree(rb);
  farfree(sc);
  db_close(fl);
}

/*
 *      >>   ¬¡¶… ¸aaŸi ·³bĞa“e ‰w¶· Íe»³ Ç¡     <<
 *
 *  F2       : ¸aaŸi ¸á¸wĞa‰¡ ‰­¢·³b
 *
 *  ShiftSPC : Ğe/µw ¤a‘
 *  Ins      : ¬s·³/®¸÷ ¤a‘
 *
 *  Enter    : ”a·q Ï©—a¡ ·¡•·
 *  Down     : ”a·q Ï©—a¡ ·¡•·
 *  Tab      : ”a·q Ï©—a¡ ·¡•·
 *  Up       : ·¡¸å Ï©—a¡ ·¡•·
 *  ShiftTab : ·¡¸å Ï©—a¡ ·¡•·

 *  ESC      :  aÃ¡‹¡
 */

/*
 *  ¸aa ·³b¬wÈµA¬á ¥© ® ·¶“e Ìs´ó¡A“A
 */
static int input_record_menu(void)
{
  char *title = "Ô„   ¸aa ·³b ¸b´ó    Ô„";
  char *menu[] = {
	" 1. ¸á¸wĞa‰¡ ‰­¢ ·³b    F2 ",
	" 2. ·³b Âá­¡(”a¯¡ ·³b)  F5 ",
    " 3. ¸aa Â‰b             F7 ",
    " 4. ¸á¸wĞa‰¡  aÃ¡‹¡      ESC "
  };
  int ret_code[] = { SAVEKEY, UNDOKEY, F7, QUITKEY };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 10, 4, menu, title, "1234", 0, 1);
  if(ans == -1)
     return -1;
  return ret_code[ans];
}

/*
 *  ¸aa ®¸÷¬wÈµA¬á ¥© ® ·¶“e Ìs´ó¡A“A
 */
static int update_record_menu(void)
{
  char *title = "Ô„   ¸aa ®¸÷ ¸b´ó    Ô„";
  char *menu[] = {
	" 1. ¸á¸wĞa‰¡  aÃ¡‹¡       F2 ",
	" 2. ®¸÷ Âá­¡(¶¥œ”¡)   F5 ",
    " 3. ¸aa Â‰b             F7 ",
    " 4. ¸á¸wĞa‰¡  aÃ¡‹¡      ESC "
  };
  int ret_code[] = { SAVEKEY, UNDOKEY, F7, ESC };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 10, 4, menu, title, "1234", 0, 1);
  if(ans == -1)
     return -1;
  return ret_code[ans];
}

/*
 *  ·¡ Ğq®“e ¸aa· ·³b‰Á ®¸÷µA¬á ¡¡– ¬a¶w–A“e Ğq®·¡”a.
 *
 *  ¸aa ·³b‰Á ¸aa ®¸÷·i ÀáŸ¡. pkey“e ºµi®A(primary key)· ¢…¸aµi,
 *  mode“e ·³b/®¸÷ ¬wÈÎa¯¡, modeˆa ®¸÷·©˜ e pkeyˆa ·AÒa
 */
static void query(char *pkey, int file_no, int mode)
{
  char *quit_msg[] = {
    "·³b ¸b´ó·i  aÃ¡¯¡‰V¯s“¡Œa ?",
    "®¸÷ ¸b´ó·i  aÃ¡¯¡‰V¯s“¡Œa ?"
  };
  int (*menu_func[2]) = { input_record_menu, update_record_menu };
  int (*func_ptr)();
  char *msg_ptr;
  int term = 0, ans, *ele_ptr, exitflag;
  bool skip_flag;
/* *******
void (*control_func[8])() =
    { save_func, undo_func, prev_func, next_func,
      go_first_func, go_last_func, delete_func, quit_func };
******* */

  msg_ptr = (mode == DBINPUT) ? quit_msg[0] : quit_msg[1];
  func_ptr = (mode == DBINPUT) ? menu_func[0] : menu_func[1];
  screen_displayed = exitflag = FALSE;
  skip_flag = false;
  pushwindow();
  hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-1);
  disp_record_status(file_no, (mode == DBINPUT) ? -1L : 0L);

  if(mode == DBINPUT)
    clrrcd(sc, els);	     /* ÑÁ¡e¤áÌáµA ‰·¤‚·i À¶…”a */
  set_trap(file_no);		     /* Ç¡ ¸aa¶a­¡ˆa ·³b–E Ò Ñ¡Â‰Ği Ğq® »¡¸÷ */
  while (!exitflag)  {
    disp_record_number(file_no, (mode == DBINPUT) ? -1L : 0L);
    if(!skip_flag)
      term = data_entry(pkey, file_no); /* ÑÁ¡e ·³bËiµA¬á ¯©¹A ·³b·i ¤h“e ¦¦… */
    else
      skip_flag = false;
/* ********
    if(term == SWITCHKEY) {
      buttn_ptr = control_pannel();
      if(buttn_ptr != -1)
	      control_func[buttn_ptr]();
      if(exitflag)
        term = QUITKEY;
    }
    else {
****** */
      switch (term)  {
        case MENUKEY :
	        term = func_ptr();
            if(term != -1)
              skip_flag = true;
	        break;
        case SAVEKEY :
            if(mode == DBUPDATE) { /* ®¸÷¬wÈ */
              exitflag = quit_func(msg_ptr);
   	          if(exitflag)
                save_func(file_no);
            }
            else /* ¬¸aa ·³b ¬wÈ */
              save_func(file_no);
	        break;
        case OUTPUTKEY : /* Äa—a Ñw¯¢· Â‰b ‹¡“w */
            ans = output_dir_menu();
            if(ans == -1) /* Âá­¡  */
              break;
            if(ans == TO_FILE) { /* Ìa·©¡ Â‰b */
              if(get_filename_to_write(write_name)) {
                if(access(write_name, 0) == 0) { /* file exist */
                  if(yesno(" Ìa·©·¡ ·¡£¡ ·¶¯s“¡”a. ”ü´á ³iŒa¶a ? ", 1) == 0) { /* yes */
                    result = fopen(write_name, "wt");
                    if(result) {
                      print_card(sc, els, file_no, DATA2FILE);
                      post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
                      fclose(result);
                    }
                    else {
                      disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
                    }
                  }
                }
                else {
                  result = fopen(write_name, "wt");
                  if(result) {
                    print_card(sc, els, file_no, DATA2FILE);
                    post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
                    fclose(result);
                  }
                  else {
                    disperror("  —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
                  }
                }
              }
            }
            else {  /* ÏaŸ¥Èá¡ Â‰b */
              print_card(sc, els, file_no, DATA2PRN);
/*               post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a "); */
            }
            break;
/* ***** ·³b‰Á ®¸÷ ¦¦…µA¬á“e ¸aa ¬a·¡· ·¡•··i ĞáœbĞa»¡ ´g“e”a.
        case CTRL_PGUP :
	        go_first_func(file_no);
	        break;
        case CTRL_PGDN :
	        go_last_func(file_no);
	        break;
        case PGUPKEY :
	        prev_func(file_no);
	        break;
        case PGDNKEY :
	        next_func(file_no);
	        break;
        case DELETEKEY :
	        delete_func(file_no);
	        break;
 ***** */
        case QUITKEY :
          exitflag = quit_func(msg_ptr);
		  if(exitflag)
            rcdout(file_no);
	      break;
        case ABORTKEY :
          ans = yesno(" ·³b·i ‰­¢ Ğa¯¡‰V¯s“¡Œa ?", 0);
          exitflag = (ans == 0) ? 0 : 1;
          if(!exitflag)
            clear_record(file_no); /* buffer clear Ğa‰¡ ‰­¢ ¸b´ó */
          break;
        case UNDOKEY :
          undo_func(file_no);
          if(newflag)
            clear_record(file_no);
          else
            newflag = false;
          break;
      } /* switch */
/*    } */ /* else */
  } /* while */
  popwindow();
}

/* *********************************************************************** *
 *                     ¸aa Ò´á¥¡‹¡µA¬á ³a·¡“e Ğq®—i                     *
 * *********************************************************************** */

static bool prev_func(int file_no, int key_no)
{
  rcdout(file_no);
  if(prev_rcd(file_no, key_no, rb) == DBERROR) {
    if (first_rcd(file_no, key_no, rb) == DBERROR)  {
      post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
      return false;
    }
    post_notice("  ˆa¸w Àá·q ¸aa·³“¡”a  ");
  }
  rcdin(file_no);
  return true;
}

static bool next_func(int file_no, int key_no)
{
  rcdout(file_no);
  if (next_rcd(file_no, key_no, rb) == DBERROR)  {
    if (last_rcd(file_no, key_no, rb) == DBERROR)  {
	  post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
      return false;
    }
    post_notice("  ˆa¸w  a»¡ b ¸aa·³“¡”a  ");
  }
  rcdin(file_no);
  return true;
}

static bool go_first_func(int file_no, int key_no)
{
  rcdout(file_no);
  if (first_rcd(file_no, key_no, rb) == DBERROR) {
    post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
    return false;
  }
  else {
    rcdin(file_no);
    return true;
  }
}

static bool go_last_func(int file_no, int key_no)
{
  rcdout(file_no);
  if (last_rcd(file_no, key_no, rb) == DBERROR) {
    post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
    return false;
  }
  else {
    rcdin(file_no);
    return true;
  }
}

/*
 *  ¸aa Àx‹¡µA ¬÷‰·Ğe Ò Àx·e ¸aaŸi ¥¡µaº‰¡,
 *  ‹a ¸aa ˆñ¬‚µA ¬a¶wĞ–”å Ç¡Ÿi ‹¡º…·a¡ ¸aa—i·i ¥¡µaº‘
 */
static int view_record_menu(void)
{
  char *title = "Ô„   ¸aa µiœq ¸b´ó   Ô„";
  char *menu[] = {
    " 1. ´|·a¡ ·¡•·        PgUp ",
    " 2. –á¡ ·¡•·          PgDn ",
    " 3. ˆa¸w ´|·a¡ ·¡•·  ^PgUp ",
    " 4. ˆa¸w –á¡ ·¡•·    ^PgDn ",
    " 5. ¸aa ®¸÷            Ôú ",
    " 6. ¸aa Â‰b            F7 ",
    " 7. ¸aa »¡¶‹¡          F8 ",
    " 8.  aÃ¡‹¡              ESC "
  };
  int ret_code[] = { PGUPKEY, PGDNKEY, CTRL_PGUP, CTRL_PGDN, CR, OUTPUTKEY, DELETEKEY, QUITKEY };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 10, 8, menu, title, "12345678", 0, 1);
  if(ans == -1)
     return -1;
  return ret_code[ans];
}

/*
 *  ¸aaˆñ¬‚µA ¬÷‰·Ğ–·i ˜ ‹a ¸aaŸi ¥¡µaº‰¡, ˆá‹¡µA¬á
 *  ¶¥Ğe”a¡e, ”aŸe ¸aaŸi Ëb¸÷ Ç¡ ®…¬á¡ µiœqĞe”aˆáa,
 *  ¸aaŸi »¡¶ˆáa, Â‰bĞaˆáa ®¸÷Ğaˆáa Ğa“e ·©·¡
 *  ˆa“wĞa•¡¢ Ğe”a.
 */
static void record_tour(char *title, int file_no, int key_no, unsigned char *keyvalue)
{
  int tmp, ans;
  int term = 0, exitflag;
  bool skip_flag;

  screen_displayed = exitflag = FALSE;
  skip_flag = false;
  pushwindow();

/*  hclrscrxy(-1, -1, hgetmaxax(), hgetmaxay()); */
  hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-2);
  display_template(title, 0 /* ¶aˆá·¡ Ï©¶a ´ô·q */);
  msg_bar(hgetmaxay(), " PgUp-´|  PgDn-–á  ^PgUp-ˆa¸w ´|  ^PgDn-ˆa¸w –á   Ôú-®¸÷   ÙLF10-ÀaŸ±ÎaÙM");
  while (!exitflag)  {
    rcdin(file_no);
/*    display_template(title, 1); */
    tally();

    if(!skip_flag)
      term = getxch();
    else
      skip_flag = false;
    switch (term)  {
      case MENUKEY :
	    term = view_record_menu();
		if(term != -1)
          skip_flag = true;
	    break;
      case CTRL_PGUP :
	    go_first_func(file_no, key_no);
	    break;
      case CTRL_PGDN :
	    go_last_func(file_no, key_no);
	    break;
      case PGUPKEY :
	    prev_func(file_no, key_no);
	    break;
      case PGDNKEY :
	    next_func(file_no, key_no);
	    break;
      case DELETEKEY : /* ·¡ ¸aa ¬b¹A */
        if(delete_func(file_no)) {
          /* »¡¶”a ¥¡“¡Œa ”a »¡¶¶”a. */
          if(!next_func(file_no, key_no) && !prev_func(file_no, key_no)) {
            post_notice(" ¡¡—e ¸aaˆa »¡¶¡¹v¯s“¡”a. ");
            exitflag = TRUE;
          }
        }
        break;
      case OUTPUTKEY : /* Äa—a Ñw¯¢ ¸aa Â‰b */
        ans = output_dir_menu();
        if(ans == -1) /* Âá­¡  */
          break;
        if(ans == TO_FILE) { /* Ìa·©¡ Â‰b */
          if(get_filename_to_write(write_name)) {
            if(access(write_name, 0) == 0) { /* file exist */
              if(yesno(" Ìa·©·¡ ·¡£¡ ·¶¯s“¡”a. ”ü´á ³iŒa¶a ? ", 1) == 0) { /* yes */
                result = fopen(write_name, "wt");
                if(result) {
                  print_card(rb, els, file_no, DATA2FILE);
                  fclose(result);
                  post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
                }
                else {
                  disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
                }
              }
            }
            else {
              result = fopen(write_name, "at");
              if(result) {
                print_card(rb, els, file_no, DATA2FILE);
                fclose(result);
                post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
              }
              else {
                disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
              }
            }
          }
        }
        else {  /* ÏaŸ¥Èá¡ Â‰b */
          print_card(rb, els, file_no, DATA2PRN);
/*          post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");*/
        }
        break;
      case CR :        /* ¸aa ®¸÷ */
        query(keyvalue, file_no, DBUPDATE);
        break;
      case QUITKEY :
		exitflag = quit_func("¸aa ˆñ¬‚ ¸b´ó·i  aÃ¡¯¡‰V¯s“¡Œa ?");
	    break;
    } /* switch */
  } /* while */
  popwindow();
}

/* ************************************************************************ *
 *    ¸aa ·³b, ®¸÷, Àx‹¡, »¡¶‹¡—wµA ¬a¶w–A“e ‰¡®º…· ¸aa ¹¡¸bĞq®     *
 * ************************************************************************ *

/*
 *  ¸aa ·³b·i ¶áĞe Ğq®.
 *
 *  ·¡ »©·¦Ÿi ¦Ÿa‹¡¸åµA ·¡£¡ ¡¡—e ‰Åe Ìa·©·e µi´á–“e ˆõ·a¡ Ğa¸a
 *  ‰Ãw¸â ÀaŸ±Îa¤w¯¢µA¬á“e Ñe¸· ¤w¯¢·¡ ”á a·i»¡ ¡¡Ÿa»¡ e
 *  Î‰”a¶… ¤w¯¢·¡œa¡e  ¶ ‰¥œeĞe ¤w¯¢·¡ –E”a.
 *
 *  Ïa¡‹aœ‘ ¯©Ğ—· ¥¥ÁAµA¬á ¸b´ó Ìa·©·i ¡¡– µi‰¡
 *  Ïa¡‹aœ‘·i { aÃ©˜ ¸b´ó Ìa·©·i ”h“e ¤w¯¢·i ÂáĞa¸a.
 *
 *  Ìa·©¤åÑ¡· µ¡ŸA¢…¹A“e ·¡ Ğq® ¦Ÿa‹¡¸åµA ÀáŸ¡Ğ´¡ Ğe”a.
 *
 *  *title     : ÀáŸ¡Ği ¸aa ÑÁ¡e· ¹A¡¢
 *  data_ele[] : ÀáŸ¡Ği ¸aa¶a­¡· ¸÷® ¤µi
 *  crd[]      : ¶á· ¸aa¶a­¡µA ”·wĞa“e ¶a­¡—i· ·³b¶áÃ¡
 */

void db_input(int file_no, char *title, int data_ele[], struct coord_t crd[])
{
  if(init_query(file_no, title, data_ele, crd)) {
    query(NULL, file_no, DBINPUT);
    close_query(file_no);
  }
}

/*
 *  ¸aa Àx‹¡Ÿi ¶áĞe Ğq®
 *
 *  *title     : ÀáŸ¡Ği ¸aa ÑÁ¡e· ¹A¡¢
 *  data_ele[] : ÀáŸ¡Ği ¸aa¶a­¡· ¸÷® ¤µi
 *  crd[]      : ¶á· ¸aa¶a­¡µA ”·wĞa“e ¶a­¡—i· ·³b¶áÃ¡
 *  keyno      : µi®A ¤åÑ¡
 *  *keyvalue  : Àx·aa“e ¸aa· ¢…¸aµi
 *
 *  ‰¡Ã¥ ¸ñ    : ¸aaŸi Àx·e Ò ‰¨¤a¡ Íe»³ ¬wÈ¡ ˆa»¡ i‰¡,
 *               ¸aaŸi ¥¡µaº‰¡ ·¥­áĞi ˆõ·¥»¡, Íe»³Ği ˆõ·¥»¡
 *               ¬åÈ‚Ğa•¡¢ Ğe”a.
 */

void db_search(int file_no, char *title, int data_ele[], struct coord_t crd[], int keyno, char *keyvalue, int find_mode)
{
  byte msg[80];

  if(init_query(file_no, title, data_ele, crd)) {
/*    file = file_no; */
    if(spaces(keyvalue)) {
      post_notice(" ˆa¸w Àá·q·a¡ ·¡•·Ğs“¡”a ");
      if (first_rcd(file_no, keyno, rb) == DBERROR) {
        post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
        return;
      }
      record_tour(title, file_no, keyno, keyvalue);
    }
    else if(find_rcd(file_no, keyno, keyvalue, rb, find_mode) != DBERROR) {
      sprintf(msg, " [%s] ¸aaŸi Àx´v¯s“¡”a ", keyvalue);
      post_notice(msg);
/*      query(keyvalue, file_no, DBUPDATE); */
      /*
       *  ¸aa· µiœq e ˆa“wĞa•¡¢ Ğe”a.  Ï©¶aĞe ¡A“A“e Ìs´ó ÑwÈ
       */
      record_tour(title, file_no, keyno, keyvalue);
    }
    else {
      sprintf(msg, " [%s] ·¡ ¸aa“e ´ô¯s“¡”a ", keyvalue);
      disp_cmsg(msg);
    }
    close_query(file_no);
  }
}

/*
 *  ÍiÁa¥¡‹¡ -- > ¸aa ®¸÷·i ¶áĞe Ğq®
 *
 *  *title     : ÀáŸ¡Ği ¸aa ÑÁ¡e· ¹A¡¢
 *  data_ele[] : ÀáŸ¡Ği ¸aa¶a­¡· ¸÷® ¤µi
 *  crd[]      : ¶á· ¸aa¶a­¡µA ”·wĞa“e ¶a­¡—i· ·³b¶áÃ¡
 */

void db_update(int file_no, char *title, int data_ele[], struct coord_t crd[], int key, char *buf)
{
  char keyvalue[MAXKEYLEN];
  int tmp;

  if(init_query(file_no, title, data_ele, crd)) {
/*    file = file_no; */
    memcpy(rb, buf, rlen(file_no));
    rcdin(file_no);
    tmp = epos(index_ele[file_no][0][key-1], els);
    strcpy(keyvalue, sc+tmp);
    query(keyvalue, file_no, DBUPDATE);
    close_query(file_no);
  }
}

void db_delete(int file_no, char *title, int data_ele[], struct coord_t crd[], int keyno, char *keyvalue)
{
  char msg[80];

  if(init_query(file_no, title, data_ele, crd)) {
/*    file = file_no; */
    if(find_rcd(file_no, keyno, keyvalue, rb, DB_EXACT) != DBERROR) {
      rcdin(file_no);
      display_template(title, 1);
      tally();
      delete_func(file_no);
    }
    else {
      sprintf(msg, " [%s] : ·¡ ¸aa“e ´ô¯s“¡”a ", keyvalue);
      disp_cmsg(msg);
    }
    close_query(file_no);
  }
}

/*
 *     ¸aa Ò´á¥¡‹¡ - ÑÁ¡e Š¬÷·e ”a·q‰Á ˆ{”a.
 *
 *     +-----------------------------------------------------------+
 *   1 |   ÑÁ¡e ¹A¡¢                                               |
 *     +-----------------------------------------------------------+
 *   2 |   ˆb ¸aa¶a­¡ ·¡Ÿq                                        |
 *     +-----------------------------------------------------------+
 *     |                                                           |
 *     .                                                           .
 *     .                                                           .
 *     .                                                           .
 *     |                                                           |
 *     +-----------------------------------------------------------+
 *  25 |   ¸aa¬wÈŸi Îa¯¡Ğe”a.  Á· ¸aa®µÁ Ñe¸ ¸aa¤åÑ¡ ˜a¶á..  |
 *     +-----------------------------------------------------------+
 */

#define  LISTLINES   (22)            /* ÍiÁa¥¡‹¡· º‰ ® */
#define  PRNLINES    (50)            /* Ğe ¹··¡µA ·¥­á–I º‰ ® */
#ifndef  DISP_MODE
#define  DISP_MODE
enum {  REVERSE, NORMAL } disp_mode;  /* Ğeº‰ Îa¯¡ ˜ ¤e¸å¯¡Ç© ˆõ·¥ˆa */
#endif

/* Ò´á¥¡‹¡µA¬á ¡A“A */
static int list_menu(void)
{
  char *title = "Ô„  ¸aa Ò´á¥¡‹¡  ¡ww  Ô„";
  char *menu[] = {
    " 1. Ğe ÑÁ¡e ´|·a¡ ·¡•·     PgUp ",
    " 2. Ğe ÑÁ¡e –á¡ ·¡•·       PgDn ",
    " 3. ˆa¸w ´|·a¡ ·¡•·       ^PgUp ",
    " 4. ˆa¸w –á¡ ·¡•·         ^PgDn ",
    " 5. ÑÁ¡e ¹A·© ¶á¡ ·¡•·    ^Home ",
    " 6. ÑÁ¡e ¹A·© ´aœ¡ ·¡•·   ^End ",
    " 7. µ¡Ÿe½¢ a á»¡         ^Right ",
    " 8. ¶E½¢ a á»¡            ^Left ",
    " 9. ¸aa Â‰b                 F7 ",
    " 0. ¸aa ®¸÷                 Ôú ",
    " -. ¸aa »¡¶‹¡               F8 ",
    " =.  aÃ¡‹¡                   ESC "
  };
  int ret_code[] = {
    PGUPKEY, PGDNKEY, CTRL_PGUP, CTRL_PGDN, CTRL_HOME, CTRL_END,
    RIGHTARROW, LEFTARROW, OUTPUTKEY, CR, DELETEKEY, QUITKEY
  };
  int ans;

  ans = popup(hgetmaxax()/2-strlen(menu[0])/2, 8, 12, menu, title, "1234567890-=", 0, 1);
  if(ans == -1)
     return -1;
  return ret_code[ans];
}

static int prev_list(int file_no, int key_no, char *buf)
{
  int flag;

  flag = 1;
  if(prev_rcd(file_no, key_no, buf) == DBERROR) {
    flag = 0;
    if (first_rcd(file_no, key_no, buf) == DBERROR)  {
      post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
    }
/* **********
   else {
      post_notice("  ˆa¸w Àá·q ¸aa·³“¡”a  ");
    }
 ******** */
  }
  return flag;
}

static int next_list(int file_no, int key_no, char *buf)
{
  int flag;

  flag = 1;
  if (next_rcd(file_no, key_no, buf) == DBERROR)  {
    flag = 0;
    if (last_rcd(file_no, key_no, buf) == DBERROR)  {
      post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
    }
/* ********
    else {
      post_notice("  ˆa¸w  a»¡ b ¸aa·³“¡”a  ");
    }
********* */
  }
  return flag;
}

static int go_first_list(int file_no, int key_no, char *buf)
{
  int flag;

  flag = 0;
  if (first_rcd(file_no, key_no, buf) == DBERROR) {
    flag = 0;
    post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
  }
  return flag;
}

static int go_last_list(int file_no, int key_no, char *buf)
{
  int flag;

  flag = 1;
  if (last_rcd(file_no, key_no, buf) == DBERROR) {
    flag = 0;
    post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
  }
  return flag;
}

static void disp_header(int *dlist)
{
  int onoff, width, line_width;

  onoff = isshadow();
  hsetshadow(ON);
  eputchs(-1, -TITLE_Y-1, hgetmaxax(), ' ');
  line_width = 0;
  while(*dlist) {
    width = headlen(*dlist);  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
    if(line_width+width+1 > CARDWIDTH)         /* ÑÁ¡e Ça‹¡¥¡”a Äá»¡¡e ‹a e !!! */
      break;
    hputsxy(line_width + 1, -TITLE_Y-1, hdenames[*dlist-1]);
    line_width += width + 1;
    dlist++;
  }
  hsetshadow(onoff);
}

static bool delete_list(int file_no)
{
  if(yesno("·¡ ¸aaŸi »¡¶‰Œa¶a ?", 1) == 0) { /* µ 0, ´a“¡µ¡ 1, Âá­¡ 2 */
    del_rcd(file_no);
    return true;
  }
  return false;
}

static void disp_page(int key_no, int file_no, int *dlist, char *buf, int offset)
{
  int y;

  hclrscr();
  for(y = 1; errno != D_EOF && y <= LISTLINES; y++) {
    hgotoxy(1, y);
    if(key_no) {                      /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
      disp_list(y, file_ele[file_no], dlist, buf, offset, NORMAL);
      next_rcd(file_no, key_no, buf); /* ‹a ¬‚·¥ ®…¬á¡ */
    }               /* ¸aaˆa ¸á¸w–E ¢‰Ÿ¡¸â ®…¬áµA ˜aœa ¸aaŸi Îa¯¡Ğe”a. */
    else if(seqrcd(file_no, buf) != DBERROR)  {
      disp_list(y, file_ele[file_no], dlist, buf, offset, NORMAL);
    }
  }
  for(; y > (errno == D_EOF ? 2 : 1); y--)
    prev_rcd(file_no, key_no, buf);
}

/* **************
static void disp_foot(void)
{
  char *str = "  Ô-·¡¸å   ÔŸ-”a·q   ^Home- …´|   ^End- …–á   Ôú-Íe»³  Ô‘-Ô-ÑÁ¡e¹Á¶";
  bool onoff;

  onoff = isshadow();
  hsetshadow(ON);
  hputsxy(-1, -STATUS_Y, str);
  eputchs(-(strlen(str)+1), -STATUS_Y, hgetmaxax()-strlen(str), ' ');
  hsetshadow(onoff);
  onoff = isreverse();
  hsetreverse(ON);
  eputchs(-1, -hgetmaxay(), hgetmaxax(), ' ');
  hsetreverse(onoff);
}
************* */

static char *db_list(int file_no, char *title, int key_no, int *dlist, int mode)
{
  unsigned char *buf;
  int onoff, isquit, y, ch, offset, tmpy, ans;
  RPTR cur_rec;
  bool skip_flag; /* ¡A“AµA¬á ·³b–A“e ˆé ÀáŸ¡Ğa‹¡ ¶áĞ */
  bool last_flag, first_flag;

  last_flag = skip_flag = false;
  if(!browse2update[file_no])
    return NULL;
  buf = (unsigned char *)farmalloc(rlen(file_no));
  if(!buf) {
    memerror();
    return;
  }

  errno = 0;

  if(first_rcd(file_no, 1, buf) == DBERROR)  {
    post_notice("  ¸aaˆa Ğaa•¡ ´ô¯s“¡”a  ");
    return;
  }
  pushwindow();
/*  sethwindow(1, 1, hgetmaxax(), hgetmaxay()); */
/*  hclrscrxy(-1, -1, hgetmaxax(), hgetmaxay()); */
  drawbox(-1, -TITLE_Y, hgetmaxax(), hgetmaxay(), 1);

  msg_bar(1, title);
/*  onoff = isreverse();
  hsetreverse(ON);
  eputchs(-1, -TITLE_Y, hgetmaxax(), ' ');
  hputsxy(-(hgetmaxax()/2-strlen(title)/2), -TITLE_Y, title);
  hsetreverse(onoff);
*/
  /* ¦Ÿi Àw ¬é¸÷ */
  hwindow(2, TITLE_Y+2, hgetmaxax()-1, hgetmaxay()-1);

  if(key_no)                          /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
    first_rcd(file_no, key_no, buf);  /* ¸aa· ¹A·© Àá·qµA¬á ¯¡¸b */
  disp_header(dlist);                 /* ÍiÁa¥© ˆb ¸aa¶a­¡ ·¡Ÿq·i Îa¯¡ */
/*  disp_foot(); */
  isquit = offset = 0;
  disp_page(key_no, file_no, dlist, buf, offset);
  disp_record_status(file_no, cur_rec);
  y = 1, cur_rec = 1L;
  do {
    errno = 0;            /*  µ¡ŸA¤åÑ¡ Á¡‹¡ÑÁ */
    disp_record_number(file_no, cur_rec);
    disp_list(y, file_ele[file_no], dlist, buf, offset, REVERSE);
    if(!skip_flag)
      ch = getxch();
    else
      skip_flag = false;
    disp_list(y, file_ele[file_no], dlist, buf, offset, NORMAL);
    switch(ch) {
      case CR :
        if(mode == B2UPDATE) {
          (browse2update[file_no])(file_no, buf);
/*          pushwindow();
          hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-1);
 */
          drawbox(-1, -TITLE_Y, hgetmaxax(), hgetmaxay(), 1);
          disp_header(dlist+offset);
          msg_bar(1, title);
          disp_record_status(file_no, cur_rec);
/*          disp_foot(); */
          for(tmpy = y; y > 1; y--)
            prev_rcd(file_no, key_no, buf);
          if(errno)
            next_rcd(file_no, key_no, buf);
          errno = 0;
          disp_page(key_no, file_no, dlist, buf, offset);
          for(errno = 0; y < tmpy; y++)
            next_rcd(file_no, key_no, buf);
          if(errno && y > 1)
            y--;
 /*         popwindow(); */
        }
        else {
          return buf + epos(index_ele[file_no][0][0], file_ele[file_no]);
        }
        break;
      case CTRL_HOME :
        for(; y > 1; y--, cur_rec--)
          prev_rcd(file_no, key_no, buf);
        break;
      case CTRL_END :
        for(errno = 0; errno != D_EOF && y < LISTLINES; y++, cur_rec++)
          next_rcd(file_no, key_no, buf);
        if(errno == D_EOF && y)
          y--, cur_rec--;
        break;
      case UPARROW :
        first_flag = last_flag = false;
        if(y > 1) {
          if(prev_list(file_no, key_no, buf))
            y--, cur_rec--;
          else {
            post_notice(" ˆa¸w Àá·q ¸aa·³“¡”a ");
            first_flag = true;
          }
        }
        else {
          if(prev_list(file_no, key_no, buf)) {
            hbackscroll();
            cur_rec--;
          }
          else {
            post_notice(" ˆa¸w Àá·q ¸aa ·³“¡”a ");
            first_flag = true;
          }
        }
        break;
      case DOWNARROW :
        last_flag = first_flag = false;
        if(y < LISTLINES) {
          if(next_list(file_no, key_no, buf))
            y++, cur_rec++;
          else {
            post_notice(" ˆa¸w  a»¡ b ¸aa ·³“¡”a ");
            last_flag = true;
          }
        }
        else {
          if(next_list(file_no, key_no, buf)) {
            hscroll();
            cur_rec++;
          }
          else {
            post_notice(" ˆa¸w  a»¡ b ¸aa ·³“¡”a ");
            last_flag = true;
          }
        }
        break;
      case PGUPKEY :
        last_flag = false;
        if(first_flag) {
          post_notice(" ˆa¸w Àá·q ¸aa ·³“¡”a ");
          first_flag = false;
        }
        for(; y > 0; y--, cur_rec--) {
          if(prev_list(file_no, key_no, buf))
            ;
          else {
            first_flag = true;
            break;
          }
        }
        if(y == 0) {
          for(y = LISTLINES; y > 1; y--, cur_rec--) {
            if(prev_list(file_no, key_no, buf))
              ;
            else {
              first_flag = true;
              break;
            }
          }
          errno = 0, y = 1;
          disp_page(key_no, file_no, dlist, buf, offset);
        }
        break;
      case PGDNKEY :
        first_flag = false;
        if(last_flag) {
          post_notice(" ˆa¸w  a»¡ b ¸aa ·³“¡”a ");
          last_flag = false;
        }
        for(; y <= LISTLINES; y++, cur_rec++) {
          if(next_list(file_no, key_no, buf))
            ;
          else {
            last_flag = true;
            break;
          }
        }
        if(y == LISTLINES+1) {
          errno = 0, y = 1;
          disp_page(key_no, file_no, dlist, buf, offset);
        }
        break;
      case CTRL_PGUP :
        for(; y > 0; y--, cur_rec--) {
          if(!prev_list(file_no, key_no, buf))
            break;
        }
        if(y == 0) {
          go_first_list(file_no, key_no, buf);
          errno = 0, y = 1;
          cur_rec = 1;
          disp_page(key_no, file_no, dlist, buf, offset);
        }
        first_flag = true;
        break;
      case CTRL_PGDN :
        for(; y < LISTLINES; y++, cur_rec++) {
          if(!next_list(file_no, key_no, buf))
            break;
        }
        if(y == LISTLINES) {
          go_last_list(file_no, key_no, buf);
          y = 1, errno = 0;
          disp_page(key_no, file_no, dlist, buf, offset);
        }
        last_flag = true;
        break;
      case LEFTARROW :
        if(offset) {
          offset--;
          disp_header(dlist+offset);
          for(tmpy = y; y > 1; y--)
            prev_rcd(file_no, key_no, buf);
          disp_page(key_no, file_no, dlist, buf, offset);
          for(; y < tmpy; y++)
            next_rcd(file_no, key_no, buf);
        }
        else {
          post_notice(" ¶E½¢ {·³“¡”a ");
        }
        break;
      case RIGHTARROW :
        if(*(dlist+offset)) {
          offset++;
          disp_header(dlist+offset);
          for(tmpy = y; y > 1; y--)
            prev_rcd(file_no, key_no, buf);
          disp_page(key_no, file_no, dlist, buf, offset);
          for(; y < tmpy; y++)
            next_rcd(file_no, key_no, buf);
        }
        else {
          post_notice(" µ¡Ÿe½¢ {·³“¡”a ");
        }
        break;
      case DELETEKEY :
        if(delete_list(file_no)) {
          for(tmpy = y-1; y > 1; y--)
            prev_rcd(file_no, key_no, buf);
          next_rcd(file_no, key_no, buf);
          disp_page(key_no, file_no, dlist, buf, offset);
          for(errno = 0; errno != D_EOF && y <= tmpy; y++)
            next_rcd(file_no, key_no, buf);
          if(errno == D_EOF && y)
            y--;
          if(get_total_record(file_no) == 0) {
            post_notice(" ¡¡—e ¸aaˆa »¡¶¡¹v¯s“¡”a ");
            isquit = 1;
          }
        }
        break;
      case OUTPUTKEY :
        ans = output_dir_menu();
        if(ans == -1) /* Âá­¡  */
          break;
        if(ans == TO_FILE) { /* Ìa·©¡ Â‰b */
          if(get_filename_to_write(write_name)) {
            if(access(write_name, 0) == 0) { /* file exist */
              if(yesno(" Ìa·©·¡ ·¡£¡ ·¶¯s“¡”a. ”ü´á ³iŒa¶a ? ", 1) == 0) { /* yes */
                result = fopen(write_name, "wt");
                if(result) {
                  print_card(buf, els, file_no, DATA2FILE);
                  post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
                  fclose(result);
                }
                else {
                  disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a  ");
                }
              }
            }
            else {
              result = fopen(write_name, "wt");
              if(result) {
                print_card(buf, els, file_no, DATA2FILE);
                post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a ");
                fclose(result);
              }
              else {
                disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
              }
            }
          }
        }
        else {  /* ÏaŸ¥Èá¡ Â‰b */
          print_card(buf, els, file_no, DATA2PRN);
/*          post_notice(" ¸aaŸi Â‰bĞ–¯s“¡”a "); */
        }
        break;
      case MENUKEY :
        ch = list_menu();
        if(ch != -1)
          skip_flag = true;
        break;
      case QUITKEY :
        isquit = quit_func("¸aa Ò´á¥¡‹¡ ¸b´ó·i  aÃ¡¯¡‰V¯s“¡Œa ?");
        break;
    }
  } while(!isquit);
  popwindow();
  farfree(buf);
  return NULL;
}

int headlen(int el)
{
  return strlen(elmask[el-1]) < strlen(hdenames[el-1]) ? strlen(hdenames[el-1]) : strlen(elmask[el-1]);
}

/* b“e ÑÁ¡e ¤áÌáµA¬á Ñe¸ Ï©—a· ¶áÃ¡  Í¡·¥Èá, ¸aa ¶a­¡Ÿi ÑÁ¡eµA Â‰b */
static void disp_field(char *b, char *msk, int el)
{
   char merge[80];
   register i = 0, gap = 0;

   if(eltype[el-1] == 'G') { /* ‹aŸ± Ìa·©· ‰w¶ */
     hputs("*‹aŸ±*");
   }
   else if(eltype[el-1] == 'M') {  /* ¡A¡¡ Ìa·© */
     hputs("*¢…¬á*");
   }
   else { /* ‹a ·¡¶A· ‰w¶ */
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
     hputs(merge);   /* ÑÁ¡eÈi·i Í¡ĞqĞe ¸aa¶a­¡· ¢…¸aµi */
     gap = strlen(hdenames[el-1])-strlen(merge);
     gap = gap > 0 ? gap : 0;
     hgotoxy(hwherex()+gap+1, hwherey());
   }
}

/*
 *  ¸aaŸi Ğeº‰ Îa¯¡Ğe”a.
 */

static void disp_list(int y, int *filelist, int *dlist, char *buf, int offset, int mode)
{
  char *line, *cur_ptr, *mask_ptr;
  int width, line_width, onoff;

  line_width = 0;
  line = (char *)farmalloc(epos(0, dlist));
  if(!line) {
    memerror();
    return;
  }
  if(mode == REVERSE) {
    onoff = isreverse();
    hsetreverse(ON);
  }
  hgotoxy(1, y);
  rcd_fill(buf, line, filelist, dlist);
  cur_ptr = line;
  cur_ptr += epos(*(dlist+offset), dlist);
  while(*(dlist+offset)) {   /* ¸aa¡¢¢µA ·¶“e ¸aa ¶a­¡ ˆ•® eÇq */
    mask_ptr = elmask[(*(dlist+offset))-1];
    width = headlen(*(dlist+offset));  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
    line_width += width + 1;
    if(line_width > CARDWIDTH)         /* ÑÁ¡e Ça‹¡¥¡”a Äá»¡¡e ‹a e !!! */
      break;
    disp_field(cur_ptr, mask_ptr, (*(dlist+offset)));
    dlist++;
    cur_ptr += strlen(cur_ptr)+1;
  }
  if(mode == REVERSE) {
    hsetreverse(onoff);
  }
  farfree(line);
}

/*
 *  ÍiÁa¥¡‹¡ Á¡‹¡ÑÁ
 */

static void init_browse(int file_no, int data_ele[])
{
  int count, i;

  tmp_els = els;
  count = init_data_ele(data_ele);
  if (count == 0)  {                 /* ¡¡—e ¸aa¶a­¡Ÿi ÀáŸ¡Ğa‰V”a. */
    len = rlen(file_no);
    els = file_ele [file_no];
    for(i = 0; els[i]; i++)       /*  *file_ele[]· ¶a­¡· ˆ•® */
      ;
    no_ele = i;
  }
  else {
    len = epos(0, data_ele);
    els = data_ele;
    no_ele = count;
  }
  fl[0] = file_no;
  db_open("", fl);   /* ‰w¡ »¡¸÷Ği ® ·¶•¡¢ ‰¡Áa´¡ */
}

static void close_browse(void)
{
  els = tmp_els;
  db_close(fl);
}

/*
 *  ·³bĞq®µÁ ÑÁ¡e ¤áÌáˆa Â—•©Ğa»¡´g“eˆa ˆñ¬aĞa•¡¢...
 *
 *  key_no : 0 ·¡¡e ¸aaˆa ¸á¸w–E ®…¬á¡
 *           1 ·¡¬w· ®œa¡e ‹a ¬‚·¥¤åÑ¡µA ˜aœa ¬‚·¥ ®…·a¡ ..
 *
 *  »©·¢…· µŸi —i´á¥¡¡e
 *  1)  aˆq·©¸aˆa 93.12.XX ·¥ ¬aœq—i·i ·¡Ÿq ®…·a¡ ¥¡‰¡¯¼”a !
 *  2) ¬÷·¡ 'Š¥'·¥ ¬aœq—i·i º£¥—w¢¤åÑ¡ ®…·a¡ ¥¡‰¡¯¼”a !
 *  ‹aœı”a¡e Ï©¶aĞe ·¥¸a—i·e ”a·q‰Á ˆ{”a.
 *  . ¸b´ó ”¬w Ìa·©¤åÑ¡
 *  . ¸b´óÑÁ¡e· ¹A¡¢
 *  . ¸b´ó”¬w·¡ –A“e ¸aa ¶a­¡ ¡¢¢
 *  . ¸÷iĞa‰¡¸aĞa“e µi®A¤åÑ¡
 *  . §¡ŠaÅ¡¸aĞa“e ¶a­¡¤åÑ¡
 *  . §¡ŠaĞi ¢…¸aµi
 *  . ¢…¸aµiµA¬á ´á—¡µA¬á ´á—¡Œa»¡Ÿi §¡ŠaĞi ˆõ·¥ˆa..
 */

char *db_browse(int file_no, char *title, int data_ele[], int key_no, int mode)
{
  char *ptr;

  hallowautoscroll(false);   /* ¸a•·¯aÇa© ‹q»¡ */
  init_browse(file_no, data_ele);
  ptr = db_list(file_no, title, key_no, els, mode);
  close_browse();
  return ptr;
}

/*
 *   ·¥­á¦
 *
 *   ·¥­á ¤wĞ·µA Ìa·©‰Á ÏaŸ¥Èá·¡¶AµA ÑÁ¡e·i ÂˆaĞiŒa Ğ–·aa...
 *   ‹a·, »¡‹q‰Á ˆ{·¡ ––A, ÉB¯aËa Ìa·©·i ¥© ® ·¶“e
 *   Ìa·©¥¡‹¡, ™¡“e Ìa·©Íe»³ Ïa¡‹aœ‘·i ¹A‰·Ğa“e Íe·¡ u‰V”a.
 */

int (*prn_func[2])() = { lputs, fputs };

static bool get_width(int *dlist)
{
  int width, line_width;

  line_width = 0;
  while(*dlist) {
    width = headlen(*dlist++);
    if(line_width+width+1 >= PAPERWIDTH)
      return false;
    line_width += width + 1;
  }
  return true;
}

bool check_printer(void)
{
  char msg[80];

  if(!isOKprn()) {
    disperror("ÏaŸ¥Èáˆa Œá¹a ·¶ˆáa, µe‰i–A´á·¶»¡ ´g¯s“¡”a");
    return false;
  }
  return true;
}

/*
 *  ·¥­áĞi Ğw¡¢·i ¬åÈ‚Ğe”a.
 *  •©aº“e ˆt·e ¬åÈ‚–E Ğw¡¢· Ÿ¡¯aËa·¡”a.
 *  data_ele[] : ÀáŸ¡Å¡¸a Ğa“e Ğw¡¢· Ÿ¡¯aËa.
 *               { 0, -1 }·¡¡e ¡¡—e Ğw¡¢·i ÀáŸ¡Ğe”a“e ·£¡.
 *  crd[]      : ÑÁ¡e ¹ÁÎa
 *  prn_list[] : ¬åÈ‚–E Ğw¡¢· Ÿ¡¯aËa, Ÿ¡¯aËa·  a»¡ b Îa¯¢·e 0
 */
int *get_print_list(int file_no, char *title, int data_ele[], struct coord_t crd[], int prn_list[])
{
  int ele_list[MAXELE+1];
  int count, len, i, j;

  count = init_data_ele(data_ele);
  if (count == 0)  {                 /* ¡¡—e ¸aa¶a­¡Ÿi ÀáŸ¡Ğa‰V”a. */
    len = rlen(file_no);
    els = file_ele [file_no];
    for(i = 0; els[i]; i++)       /*  *file_ele[]· ¶a­¡· ˆ•® */
      ;
    no_ele = i;
  }
  else {
    len = epos(0, data_ele);
    els = data_ele;
    no_ele = count;
  }
  sc = (char *)farmalloc(len);        /* screen buffer */
  init_screen(title, els, sc);
  init_coord(crd);

  display_template(title, 0);
  pushwindow();
  hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-1);
  if(!get_ele_list(ele_list)) {
/*    sethwindow(1, 1, hgetmaxax(), hgetmaxay()); */
    prn_list[0] = 0;  /* cancel flag */
    farfree(sc);
    popwindow();
    return NULL;
  }
  for(i = 0, j = 0; ele_list[j] != -1 && j < MAXELE; j++) {
    if(ele_list[j])
      prn_list[i++] = ele_list[j];
  }
/*  if( !i )
    prn_list[0] = 0, prn_list[1] = -1;*/
  prn_list[i] = 0;
/*  sethwindow(1, 1, hgetmaxax(), hgetmaxay()); */
  farfree(sc);
  popwindow();
  return prn_list;
}

static void print_header(int *dlist, char *title, int mode)
{
  int width, line_width, gap;
  int *tmp;

  /* ·©”e Â‰b–I Í¢·i ŠĞ¥¡¸a */
  tmp = dlist;
  line_width = 0;
  while(*dlist) {
    width = headlen(*dlist++);
/*    if(line_width+width+1 >= PAPERWIDTH)
      break; */
    line_width += width + 1;
  }

  if(mode == DATA2PRN && !check_printer())
    return;
  /* ¸aa ¹A¡¢·i ³a¸a */
  gap = line_width/2-strlen(title)/2;
  while(gap-- > 0)
    prn_func[mode](" ", result);
  prn_func[mode](title, result);
  prn_func[mode](mode == DATA2FILE ? "\n\n" : "\n\r\n\r", result);

  /* ¶õº‰ ‹u‹¡ */
  dlist = tmp;
  line_width = 0; /* ·¡ˆå »¡‹q ´e³a»¡ e ¿¢Ó© ¸aa· ‹©·¡Ÿi £¡Ÿ¡ ´i‹¡¶áĞ Ï©¶a */
  while(*dlist) {
    width = headlen(*dlist);  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
/*    if(line_width+width+1 >= PAPERWIDTH)
      break; */
    while(width-- >= 0)
      prn_func[mode]("-", result);
    dlist++;
  }
  prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);

  /* ˆb ¸aa¶a­¡· ·¡Ÿq ³a‹¡ */
  dlist = tmp;
  line_width = 0;
  while(*dlist) {
    width = headlen(*dlist);  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
/*    if(line_width+width+1 >= PAPERWIDTH)
      break;  */
    prn_func[mode](hdenames[*dlist-1], result);
    gap = width - strlen(hdenames[*dlist-1]) + 1;
    while(gap-- > 0)
      prn_func[mode](" ", result);
    dlist++;
  }
  prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);

  /* ´aœ º‰ ‹u‹¡ */
  dlist = tmp;
  line_width = 0;
  while(*dlist) {
    width = headlen(*dlist);  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
/*    if(line_width+width+1 >= PAPERWIDTH)
      break; */
    while(width-- >= 0)
      prn_func[mode]("-", result);
    dlist++;
  }
  prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);
}

static void print_field(char *b, char *msk, int el, int mode)
{
   char merge[80];
   register i = 0, gap = 0;

   if(eltype[el-1] == 'G') { /* ‹aŸ± Ìa·©· ‰w¶ */
     prn_func[mode]("*‹aŸ±*", result);
   }
   else { /* ‹a ·¡¶A· ‰w¶ */
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
     if(mode == DATA2PRN && !check_printer())
       return;
     prn_func[mode](merge, result);
     gap = strlen(hdenames[el-1])-strlen(merge) + 1;
     gap = gap >= 0 ? gap : 1;
     while(gap-- > 0)
     prn_func[mode](" ", result);
   }
}

static void print_list(int *filelist, int *dlist, char *buf, int mode)
{
  char *line, *cur_ptr, *mask_ptr;
  int width, line_width;

  if(mode == DATA2PRN && !check_printer())
    return;

  line_width = 0;
  line = (char *)farmalloc(epos(0, dlist));
  if(!line) {
    memerror();
    return;
  }
  rcd_fill(buf, line, filelist, dlist);
  cur_ptr = line;
  cur_ptr += epos(*dlist, dlist);
  while(*dlist) {   /* ¸aa¡¢¢µA ·¶“e ¸aa ¶a­¡ ˆ•® eÇq */
    mask_ptr = elmask[(*dlist)-1];
    width = headlen(*dlist);  /* ¸aa Èi· ‹©·¡µÁ Ğe‹i¸aa¶a­¡ ·¡Ÿqº— ‹¥ ˆõ */
    line_width += width + 1;
/*    if(line_width >= PAPERWIDTH)
      break; */
    print_field(cur_ptr, mask_ptr, (*dlist), mode);
    dlist++;
    cur_ptr += strlen(cur_ptr)+1;
  }
  if(mode == DATA2PRN && !check_printer())
    return;
  prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);
  farfree(line);
}

static void print_all_list(int file_no, char *title, int key_no, int *dlist, int mode)
{
  int lines;
  char *buf;

  buf = (char *)farmalloc(rlen(file_no));
  if(!buf) {
    memerror();
    return;
  }
  errno = 0;
  if(key_no)                          /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
    first_rcd(file_no, key_no, buf);  /* ¸aa· ¹A·© Àá·qµA¬á ¯¡¸b */

  do {
    print_header(dlist, title, mode);   /* ÍiÁa¥© ˆb ¸aa¶a­¡ ·¡Ÿq·i Îa¯¡ */
    for(lines = 0; errno != D_EOF && lines <= PRNLINES; lines++) {
      if(mode == DATA2PRN && !check_printer()) {
        farfree(buf);
        return;
      }
      if(key_no) {                      /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
        print_list(file_ele[file_no], dlist, buf, mode);
        next_rcd(file_no, key_no, buf); /* ‹a ¬‚·¥ ®…¬á¡ */
      }               /* ¸aaˆa ¸á¸w–E ¢‰Ÿ¡¸â ®…¬áµA ˜aœa ¸aaŸi Îa¯¡Ğe”a. */
      else if(seqrcd(file_no, buf) != DBERROR)  {
        print_list(file_ele[file_no], dlist, buf, mode);
      }
    }
    prn_func[mode]((mode == DATA2PRN ) ? "\f" : "\n\n", result);
  } while(errno != D_EOF);
  farfree(buf);
}

/*
 *  ¸aaŸi Äa—a Ñw¯¢·a¡ Â‰bĞa“e Ğq®
 *  ‹aœá“¡Œa, Ğe¸w· ¹··¡µA Ğe ¸aa· Ğw¡¢—i e·¡ Â‰b–A•¡¢ Ğe”a.
 */
static void print_card(unsigned char *buf, int *dlist, int file_no, int mode)
{
  char *cur_ptr, *mask_ptr;

  if(mode == DATA2PRN && !check_printer())
    return;

  /* ¹A¡¢ */
/*  prn_func[mode](title, result);
  prn_func[mode](mode == DATA2FILE ? "\n\n" : "\n\r\n\r", result); */

  cur_ptr = buf;
  cur_ptr += epos(*dlist, dlist);
  while(*dlist) {   /* ¸aa¡¢¢µA ·¶“e ¸aa ¶a­¡ ˆ•® eÇq */
    prn_func[mode](hdenames[*dlist-1], result);
    prn_func[mode](" : ", result);
    mask_ptr = elmask[(*dlist)-1];
    print_field(cur_ptr, mask_ptr, (*dlist), mode);
    dlist++;
    cur_ptr += strlen(cur_ptr)+1;
    prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);
  }
  prn_func[mode](mode == DATA2FILE ? "\n" : "\n\r", result);
}

static void print_all_card(int file_no, char *title, int key_no, int *dlist, int mode)
{
  int lines;
  char *buf;

  buf = (char *)farmalloc(rlen(file_no));
  if(!buf) {
    memerror();
    return;
  }
  errno = 0;
  if(key_no)                          /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
    first_rcd(file_no, key_no, buf);  /* ¸aa· ¹A·© Àá·qµA¬á ¯¡¸b */

  do {
    for(lines = 0; errno != D_EOF; lines++) {
      if(mode == DATA2PRN && !check_printer()) {
        farfree(buf);
        return;
      }
      if(key_no) {                      /* ¬‚·¥¤åÑ¡Ÿi »¡¸÷Ğ–”a¡e */
        print_card(buf, dlist, file_no, mode);
        next_rcd(file_no, key_no, buf); /* ‹a ¬‚·¥ ®…¬á¡ */
      }               /* ¸aaˆa ¸á¸w–E ¢‰Ÿ¡¸â ®…¬áµA ˜aœa ¸aaŸi Îa¯¡Ğe”a. */
      else if(seqrcd(file_no, buf) != DBERROR)  {
        print_card(buf, dlist, file_no, mode);
      }
    }
    prn_func[mode]((mode == DATA2PRN) ? "\f" : "\n\n", result);
  } while(errno != D_EOF);
  farfree(buf);
}

/*
 *  ”aº— ¹¡ˆå·i º‰¡ Â‰b·i Ği ® ·¶•¡¢ Ğa‰¡
 *  ™¡Ğe Â‰b¤wĞ··i Ìa·©, ÏaŸ¥Èá, –ˆa»¡¡ Ğe”a.
 *  Ìa·©¡ Â‰bĞi ˜“e ¬a¶w¸aµA‰A Ìa·© ·¡Ÿq·i ¢ˆ‰¡
 *  ˆ{·e ·¡Ÿq· Ìa·©·¡ ·¶”a¡e, ÑÂ·¥ ‰Á¸÷Œa»¡....
 */
void db_print(int file_no, char *title, int data_ele[], int key_no, int mode)
{
  char outfile[MAXPATH], *ing_ptr, *end_ptr;
  char *ing_msg[] = {
    "  Ìa·©¡ Â‰bĞa‰¡ ·¶¯s“¡”a  ",
    "  ·¥­áĞa‰¡ ·¶¯s“¡”a  "
  };
  char *end_msg[] = {
    "  Ìa·©µA ¸á¸wĞ–¯s“¡”a  ",
    "  ·¥­áŸi  aÁv¯s“¡”a  "
  };
  int width;
  bool onoff;

  ing_ptr = end_ptr = result = NULL;

  if(mode == DATA2FILE) {
    if(get_filename_to_write(write_name)) {
      if(access(write_name, 0) == 0) { /* file exist */
        if(yesno(" Ìa·©·¡ ·¡£¡ ·¶¯s“¡”a. ”ü´á ³iŒa¶a ? ", 1) == 0) { /* yes */
          result = fopen(write_name, "wt");
          if(result == NULL) {
            disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
            return;
          }
        }
        else {
          post_notice(" ¸b´ó·¡ Âá­¡ –S“¡”a ");
          return;
        }
      }
      else {
        result = fopen(write_name, "wt");
        if(result == NULL) {
          disperror(" —¡¯aÇa ¶wœ··¡ ¦¹¢Ğaˆáa, ·¡¬w·¡ ·¶¯s“¡”a ");
          return;
        }
      }
    } /* if getfile.. */
    else {
      post_notice(" ¸b´ó·¡ Âá­¡ –S“¡”a ");
      return;
    }

/*    sprintf(outfile, "%s.TXT", dbfiles[file_no]);
    result = fopen(outfile, "wt");
    if(result == NULL) {
      disperror("  Ìa·©·i  e—i ® ´ô¯s“¡”a  ");
      return;
    } */
    ing_ptr = ing_msg[0];  /* Ìa·©¡ Â‰bĞe”a“e ¡A¯¡»¡ */
    end_ptr = end_msg[0];
  }
  else if(mode == DATA2PRN) {
    if(!check_printer())
      return;
    ing_ptr = ing_msg[1];  /* ÏaŸ¥Èá¡ Â‰bĞe”a“e ¡A¯¡»¡ */
    end_ptr = end_msg[1];
  }
  init_browse(file_no, data_ele);

  width = (strlen(ing_ptr)+4 > 10) ? strlen(ing_ptr)+4 : 10;
  if( !wopen(hgetmaxax()/2-strlen(ing_ptr)/2-1, hgetmaxay()/2-1, width, 3)) {
    if(mode == DATA2FILE)
      fclose(result);
    close_browse();
    return;
  }
  wtitle(ing_ptr);
  onoff = isreverse();
  hsetreverse(ON);
  wcenter(2, " ÑÂ·¥ ");
  hsetreverse(onoff);

/*  if(get_width(els)) */   /* ‹©·¡ ˆñ¬aŸi Ğa»¡  i¸a */
    print_all_list(file_no, title, key_no, els, mode);
/*  else {
    fclose(result);
    wclose();
    disperror("  Ğeº‰· ‹©·¡ˆa á¢ ‹©´á¶a  ");
    return;
  }
*/
  if(result)
    fclose(result);
  wclose();
  close_browse();
  disp_cmsg_sec(end_ptr, 1);
}
