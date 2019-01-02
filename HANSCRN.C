/* -------------------------- HANSCRN.C ------------------------- */

/*
 *   ∑≥ùbâ¡ ÆÅ∏˜µA¨· ≥a∑°ìe —¡°e äÅπ°
 *
 *   +------------------------------------------------------+
 *  1|                      †ı∑∂ìe πA°¢                     |  <- •°…∑
 *   +------------------------------------------------------+
 *  2+------------------------------------------------------+
 *  3| ∑° êÅ¶Åìe ¿w∑i ¨È∏˜–Å¨· π¡Œaª°∏˜∑i ÆÛâA–eîa.         |
 *   |                                                      |
 *   |                 +---------------+                    |
 *   |                 |  Ãs¥Û °AìA    |                    |
 *   |                 +---------------+                    |
 *   |                 |               |                    |
 *   .                 .               .                    .
 *   .                 .               .                    .
 *   |                 |               |                    |
 *   |                 +---------------+                    |
 *   |                                                      |
 * 24+------------------------------------------------------+
 *   +------------------------------------------------------+
 * 25| ∑≥ùb¨w»Å ŒaØ° - –e/µw, ÆÅ∏˜, ¨s∑≥, îaûÅâ° ∑∂ìe Ãa∑©  |  <- •°…∑
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

int cur_col = 0, cur_row = 0;    /* —e∏Å ƒ·¨·∑Å ∂·√° */
int screen_displayed;            /* —¡°eµA Ài∑° ŒaØ° ñA¥ˆìeª° */
extern struct coord_t coord[MAXELE];    /* àb ∏aûa ∂a≠°∑Å ∑≥ùbπ¡Œa */

struct {
  int prot;           /* œ©óa∑Å •°—° µa¶Å - ON/OFF  */
  int (*edits)();     /* àb ∂a≠°(œ©óa)∑≥ùb “Å Ø©–ó –i –qÆÅ */
} sb [MAXELE];

int *elist;           /* ∂a≠° ü°ØaÀa */
char *bf;             /* —¡°e §·Ã· Õ°∑•»· */
char *tname;          /* ∑≥ùb —¡°e∑Å πA°¢ */
char *prim_key;       /* ∫Å«°üi •¢¨a–ÅñÖîa */

int current_file;     /* —e∏Å ∏b¥Û∫ó∑• Ãa∑© §Â—° */

byte picture[] = "#CcAa9HhEeKkLlYy!xX*";  /* ∏aûa∑≥ùbµA ≥a∑°ìe ¥∑Ø¢ */
/* ****
 char *but_str[] = {
  "  ∏·∏w  ", "  ¬·≠°  ", "  ¥|  ", "  ñ·  ", "  †Ö ¥|  ", "  †Ö ñ·  ", "  ª°∂ë  ", "  †a√±  " };
char query_help_str[] = "  PgUp-¥|   PgDn-ñ·   ^PgUp-àa∏w ¥|   ^PgDn-àa∏w ñ·   F5-¬·≠°  ESC-è{êÅã° ";
 **** */
 
void (*_disp_card)(void);  /* ã°•• —¡°eµA ¨a∂w∏aàa †eóe —¡°e ¬âùb∑i ∂·–e –qÆÅ Õ°∑•»· */

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

/* ª°Ø°¢Ö∑i ŒaØ°–eîa */
void post_notice(char *s)
{
  disp_cmsg_sec(s, 1);
}

void clear_scrn(void)
{
  screen_displayed = FALSE;
  hclrscr();
}

/* —¡°e ¿·ü°üi ∂·–e ¡°ã°—¡ */
void init_screen(char *name, int *els, char *bfr)
{
  tname = name;
  elist = els;
  bf = bfr;
}

/* àb œ©óaµA •°—° ç°ü°Œaüi ¶õ∑°à·êa ôEîa */
void protect(int el, int tf)
{
  sb[elp(el)].prot = tf;
}

/* àb ∂a≠°(el)àa ∑≥ùbñE “Å ¶âü°ìe –qÆÅüi ¨È∏˜–eîa */
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

/* Øa«°†aµA¨· ∏˜∑Å–e ∏aûa∂a≠°§Â—°µA îÅ–Å,
 * ∂a≠°ü°ØaÀaµA ∏ÂîiñE ∏aûa∂a≠°∑Å ¨wîÅ §Â—°
 * Ø©πA ∏aûa ∂a≠°§Â—°üi ∫Å°e ∂a≠° ü°ØaÀaµA¨· °y§ÂºÅ∑•ª° ï©ùa∫Öîa.
 * ãaúÂ ∏aûa∂a≠°àa ¥Ùìe âw∂Å µ°üAŒaØ°üi –aª°¥g∑a£aù° π°Ø±!
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
 *  ª°∏˜ñE yπ¡Œa(∏ÈîÅπ¡Œa)µA
 *  –e∫â∑i §e∏Â Ø°≈a¨· °AØ°ª°üi ¬âùb–eîa.
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
 *  ∑≥ùbâ¡ ÆÅ∏˜ ∏b¥ÛµA¨· ≥a∑°ìe —¡°e∑i ãaùa∫Öîa.
 *  ¨w»Å∫â∑e ¬âùbñAª° ¥g∑aì°, ∑° –qÆÅµ¡ î·¶â¥· ¨w»Å∫â ¬âùb–qÆâüi ¶âú·¥°.
 */
void display_template(char *title, int menu_flag)
{
   int i, el, ct; /* sum; */
   char detag[80], *cp1, *cp2;
   bool onoff;

   pushwindow();  /* —e∏Å ∂Âï°∂Å ¨w»Å •°â≈ */

/*   hclrscrxy(-1, -1, hgetmaxax(), hgetmaxay()); */

   ct = no_flds();
   /* ∑≥ùb —¡°e …AñÅü° ãaü°ã° */
   drawbox(1, TITLE_Y+1, hgetmaxax(), hgetmaxay()-2, 1);
   msg_bar(TITLE_Y, title); /* —¡°e ∂·µA ∏b¥Û πA°¢ ¬âùb */

   /* ãa ¥eΩ¢µA ¿w ¨È∏˜ */
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
     data_coord(el);  /* ∏aûa∂a≠° el∑Å ∑≥ùbπ¡Œa àt∑i cur_colâ¡ cur_rowµA ¨È∏˜ */
     hputsxy(cur_col, cur_row, detag); /* —¡°e ¥∑Ø¢∑i ¬âùb */
     cur_col -= (strlen(hdenames[el-1])+1);
     onoff = isbold();
     hsetbold(ON);
     hputsxy(cur_col, cur_row, hdenames[el-1]); /* –eãi ∏aûa∂a≠° ¬âùb */
     hsetbold(onoff);
   }
   screen_displayed = TRUE;
   popwindow();
}

/* —¡°e ∑≥ùbÀiµA¨· ∏aûaüi ∑≥ùb§hìeîa */
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
     else { /* Àb∏˜–e œ©óaµA ª°∏˜ñE –qÆÅ Õ°∑•»·µA¨· DBERROR∑i ï©ùa∫Å¥vîa */
       done = TRUE;
       exitcode = ABORTKEY;
     }
  }   /* while */
  return (exitcode);
}

/* —¡°e ∑≥ùbÀiµA¨· œ©óa∑Å àïÆÅüi âÅ¨e */
static int no_flds(void)
{
  int ct = 0;

  while (*(elist + ct))
    ct++;
  return ct;
}

/* ∏aûa ∂a≠°∑Å ∑≥ùb π¡Œa */
static void data_coord(int el)
{
  cur_col = coord[elp(el)].x;
  cur_row = coord[elp(el)].y;
  hgotoxy(cur_col, cur_row);
}

/* 3∏aü°†aîa ÆÒŒaüi ê˝ìeîa. */
char *ins_comma(char *str)
{
  char tmp[80], tmp2[80];
  int i, j, len, tlen, comma, cnt;

  if(strchr(str, ','))
    return str;

  tlen = strlen(str);  /* ∂•úÅ ã©∑° */
  /* ∑©îe â∑§Ç πAà· */
  for(i = 0, j = 0; i < tlen; i++)
    if(str[i] != ' ')
      tmp[j++] = str[i];
  tmp[j] = '\0';

  len = strlen(tmp);
  /* ÆÒŒa ê˝ã° */
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

/* ÆÒŒaüi πAà·–eîa. */

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
  char *kbd_type[2] = { "–eãi ?§ÈØ¢‘≥", "µw¢Ö  £°äÇ‘≥" };

  bool onoff;
  onoff = isreverse();
  hsetreverse(true);
  kbd_type[0][5 /* ?∂·√° */] = ishan2board() ? '2' : '3';
  hputsxy(-2, -hgetmaxay(), hangulmode ? kbd_type[0] : kbd_type[1]);
  hsetreverse(onoff);
}

static void hookinsertmodetoggle(bool insertmode)
{
  bool onoff;

  onoff = isreverse();
  hsetreverse(true);
  hputsxy(-14, -hgetmaxay(), insertmode ? "¨s∑≥‘≥" : "ÆÅ∏˜‘≥");
  hsetreverse(onoff);
}

/*
 *  —e∏Å ∏aûa §Â—° / ∏aûa∑Å ¡∑ àïÆÅ
 */
void disp_record_number(int file_no, RPTR cur_rec)
{
  char total[20], cur[20], rec_status[40];
  RPTR total_rec;
  bool onoff;

  onoff = isreverse();
  hsetreverse(true);
  /* ¡∑∏aûa ÆÅüi äÅ–eîa */
  total_rec = get_total_record(file_no);
  ltoa(total_rec, total, 10);
  ins_comma(total);
  /* —e∏Å ∏aûa §Â—° */
  if(cur_rec == -1L) {
    strcpy(cur, "∏aûa ∑≥ùb ∫ó");  /* 13∏aàa êÒª° ¥g¥a¥° */
  }
  else if(cur_rec == 0L) {
    strcpy(cur, "∏aûa ÆÅ∏˜ ∫ó");  /* 13∏aàa êÒª° ¥gï°ù¢ */
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
 –eãi ?§ÈØ¢‘≥¨s∑≥‘≥ 2,147,483,648 / 2,147,483,648 ‘≥STUDENTS.DAT‘≥ŸLF10 ¿aü±ŒaŸM
                    +---------------------------+    +----------+
                      ¬AîÅ ∑°†e«q ∏aü°ìe ∏s¥añÅ∏a    ∏b¥Û ∫ó Ãa∑©
 *
 *  file_no  :  —e∏Å ∏b¥Û–aâ° ∑∂ìe Ãa∑© §Â—°
 *  cur_rec  :  —e∏Å ∏b¥Û Ãa∑©µA¨· —e∏Å ùA≈°óa§Â—°( «° ÆÖ¨·)
 *              -1L∑°°e, ¨Åù°∂Ö ∏aûaüi ¬Åàa–aìe âw∂Å∑°â°
 *               0L∑°°e, ∏aûaüi ÆÅ∏˜–aìe âw∂Å∑°îa.
 */
void disp_record_status(int file_no, RPTR cur_rec)
{
/*  char *kbd_type[2] = { "–eãi ?§ÈØ¢‘≥", "µw¢Ö  £°äÇ‘≥" };
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
  hputsxy(-14, -hgetmaxay(), _insertmode ? "¨s∑≥‘≥" : "ÆÅ∏˜‘≥");

  total_rec = get_total_record(file_no);
  ltoa(total_rec, total, 10);
  ins_comma(total);
  if(total_rec != -1L) {
    ltoa(cur_rec, cur, 10);
    ins_comma(cur);
  }
  else
    strcpy(cur, "∏aûa è{");
  sprintf(rec_status, "%13s / %-13s", cur, total);
  hprintfxy(-21, -hgetmaxay(), "%29s", rec_status);
*/
  hprintfxy(-51, -hgetmaxay(), "‘≥%8s.DAT‘≥", strupr(dbfiles[file_no]));
  hputsxy(-67, -hgetmaxay(), "ŸLF10 ¿aü±ŒaŸM");
  hsetreverse(onoff);
}

/*
 *  Ø©πA ∑≥ùb∑i §hìe ¶Å¶Ö
 *
 *  —e∏Å –eãi úa∑°ßaú·ü°µA †xï°ù¢ ∏aûa—w∑i îaØ° ∏˜ü°–a°e îa∑qâ¡ à{îa
 *
 *  H : ∑≥ùb “Å ¥a¢ÅúÂ ¿·ü°üi ¥g∑eîa
 *  D : êiºa (∑≥ùb “Å êiºaàa ëe.∂©.∑© ÆÖ¨·ù° ñA¥· ∑∂ìeª° àÒ¨a
 *  N : Æï∏a ∑≥ùb “Å µ°üeΩ¢ ∏˜ùi, ∂EΩ¢ ¶Å¶ÖµAìe â∑§Ç∑i ¿Å∂ë
 *  Z : Æï∏a ∑≥ùb “Å µ°üeΩ¢ ∏˜ùi, ∂EΩ¢ ¶Å¶ÖµA 0∑i ¿Å∂ë
 *  M : ¢Ö¨·üi Õeª≥–i ÆÅ ∑∂îa.
 *  K : ∑≥ùb§hª° ¥gâ° ãaê∑ àÂê·öÂîa... (M --> K ù° §aé·¥ˆîa)
 *  C : Æï∏a ∑≥ùb “Å µ°üeΩ¢ ∏˜ùi, ∂EΩ¢¶Å¶ÖµA â∑§Ç ¿Å∂Åâ°, 3∏aü° †aîa ÆÒŒa(,) ¨s∑≥
 *      - ãq¥Ç ŒaØ°µA ∫Åù° ≥eîa. ∏aûa «aã°ìe ÆÒŒaåaª° â°ùa–Å¥°–eîa.
 *  G : ãaü± Ãa∑© ∑≥ùb, ØaƒÅê·êa Ãa∑©µA¨· ∑≥ùb§h∑q. –aª°†e ! ¥aª¢ ª°∂• ¥eñQ.
 */

bool hookhgetdata(int *keycodep)
{
  bool ans;
/*  , onoff;
  char kbd_type[] = "–eãi ?§ÈØ¢‘≥"; */


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
      *  ãaü±∑≥ùb(ØaƒÅê· ô°ìe Ãa∑©) ¶Å¶Ö
      *  ãaü±Ãa∑©∑Å ∑°üq∑e ª°ûa Ãa∑©∑Å ∫Å«°üi ∑°∂w–eîa.
      *  òaúa¨· ãaü±∑° ói¥·àaìe Ãa∑©∑Å âw∂Å π°–s«°∑Å ¨a∂w∑e ¶âàaìw–aîa.
      */
   }
   else if(type == 'K') {
     /*
      *  ãaê∑ àÂê· öÂîa.
      */
     return _lastkey;
   }
   else if(type == 'M') {
     /*
      *  °A°° œ©óa
      *  ∂a≠°∑°üq∑° îaüe àıâ¡ äÅ•i∑° ñAì°åa..
      *  ∂a≠°∑°üq.HTL
      *  ∑°úaâ° †eói°e, ñAâVª°. îÅØ• ∂a≠°∑°üq∑e
      *  ¥| 8∏aù° äÅ¶Ö∑° ñAï°ù¢ –Å¥°âVîa.

      sprintf(temp, "%8s.HTL", denames[el]);
      editor(....temp);
      */
   }
   else {  /* ãa ∑°∂A∑Å ∏aûa∑≥ùb */
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
     /* Æï∏a ∑≥ùbâ¡ â≈ùeñE –w°¢∑e ÆÅ∏˜¨w»Åù° */
     if(type == 'C' || type == 'D' || type == 'Z' || type == 'N')
       _insertmode = false;
     onoff = /*isunder(); */ isreverse();
     /* hsetunder(ON);     */ hsetreverse(ON);
     hgetdata(tmpbuf, msk);
     /* hsetunder(onoff); */ hsetreverse(onoff);
     _insertmode = tmpins;
     c = _lastkey;

     /* buffµA¨· ∏˜—w(picture)πAà· */
     pickoutdata(tmpbuf, msk, tmpbuf2);
     while(tmpbuf[0] && len > i) {
       temp[i] = tmpbuf2[i];
       i++;
     }
     _allowcanceldelline = allowcanceldelline, _restoreline = restoreline;
     _cuttail = cuttail, _allowfirstdelline = allowfirstdelline;
     if (c != ESC) { /* ∑≥ùb âiâ¡àa ¬·≠°ñAª° ¥g¥vîa°e */
        switch(type) { /* ∏aûa∂a≠°∑Å —wµA òaúa âiâ¡üi àÒ¨a */
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

/* —¡°eµA¨· ∏aûa∂a≠°üi ¨Â»Ç§hã°∂·–Å */
static int onoff_element(int el)
{
  bool onoff;
  int ch;

  data_coord(el);
  cur_col -= (strlen(hdenames[el-1])+1);
  onoff = isreverse();
  hsetreverse(ON);
  hputsxy(cur_col, cur_row, hdenames[el-1]); /* –eãi ∏aûa∂a≠° ¬âùb */
  hsetreverse(onoff);
  ch = getxch();
  hputsxy(cur_col, cur_row, hdenames[el-1]); /* –eãi ∏aûa∂a≠° ¬âùb */
  return ch;
}

/* –w°¢ ¨Â»Ç °AìA */
static int sel_menu(void)
{
  char *title =
    " ‘Ñ      –w°¢ ¨Â»Ç–aã° °wùw      ‘Ñ ";
  char *menu[] = {
    " 1. –w°¢ ¨Â»Ç ∏Â—≈              SPC ",
    " 2. –w°¢ ¨Â»Ç ∏Â—≈–e îa∑q ∑°ï∑   ‘˙ ",
    " 3. –e –w°¢ îa∑q∑aù° ∑°ï∑       Tab ",
    " 4. –e –w°¢ ∑°∏Â∑aù° ∑°ï∑      #Tab ",
    " 5. πA∑© ¿ı –w°¢∑aù° ∑°ï∑      Home ",
    " 6. πA∑© †aª°†b –w°¢∑aù° ∑°ï∑   End ",
    " 7. °°ñÅ ¨Â»Ç                     + ",
    " 8. °°ñÅ ¨Â»Ç ¬·≠°                - ",
    " 9. ¬·≠°–aâ° †a√±               ESC ",
    " 0. ∏aûa ¬âùb–aâ° †a√±           F7 "
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
 *  ∏aûa ¬âùb ∏b¥ÛµA¨·
 *  ¬âùb–i ∂a≠°üi ¨Â»Ç–eîaà·êa –aìe âw∂ÅµA ≥a∑•îa.
 *  ï©ùa∫Åìe àt∑e ¨Â»ÇñE ∏aûa∂a≠° ü°ØaÀa∑°°a,
 *  ∑° ü°ØaÀa∑° †aª°†b∑e -1∑°îa.
 *  ∑°∏ÂµAìe ¨Â»Çàaìw–e ¬AîÅ ƒeÆÅüi
 *  œaü•»·(80ƒiúÒ ã°∫Ö)µA¨· –e∫âù° ¬âùb–i ÆÅ ∑∂ìe ¥∑∑aù° πA–e∑i
 *  ñÅ¥ˆ∑aêa, µaã°¨·ìe —e∏Å ¨Â»ÇñE ∏aûa∂a≠°àa ¿aª°–aìe ƒeÆÅüi
 *  •°µa∫Åâ°, êa†·ª°ìe ¨a∂w∏aµAâA †{ã°ìe àı∑aù° –eîa.
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
  hputsxy(-1, -hgetmaxay(), " SPC-¨Â»Ç  ‘˙-¨Â»Ç&∑°ï∑  Tab-∑°ï∑  ESC-¬·≠°  ŸLF7-¬âùbŸM ŸL¨Â»ÇñE ƒe ÆÅ   0ƒeŸM");
  /*  hputsxy(-1, -hgetmaxay(),    " SPC-¨Â»Ç  ‘˙-¨Â»Ç&∑°ï∑  Tab-∑°ï∑  ESC-¬·≠°  ŸLF7-¬âùbŸM                       "); */
  hsetreverse(onoff);
/* *************
  onoff = isreverse();
  hsetshadow(ON);
  eputchs(-1, -STATUS_Y, hgetmaxax(), ' ');
  hputsxy(-1, -STATUS_Y, "  [¨a∑°õÅàÅ]-¨Â»Ç∏Â—≈   ‘˙-¨Â»Ç∏Â—≈   ‘ë-‘ê îa∑q–w°¢    F2-¬âùb    ESC-¬·≠°");
  hsetshadow(onoff);
*********** */
  field_ctr = no_flds();
  /* ¨Â»Ç ü°ØaÀa ¡°ã°—¡ */
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
           hputsxy(cur_col-1, cur_row, "Ÿ–");
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
       case QUITKEY : /* ¬·≠° */
         if(yesno(" –w°¢ ¨Â»Ç ∏b¥Û∑i ∫óîe–aØ°âVØsì°åa ? ", 0) == 0) {
           ele_list[0] = 0;
           return NULL;
         }
         break;
       case OUTPUTKEY : /* ¨Â»Ç∑i †a√°â° ∏aûa ¬âùb∑aù° .. */
         if(yesno(" ¨Â»ÇñE –w°¢∑i ¬âùb–aØ°âVØsì°åa ? ", 0) == 0) {
           done = TRUE;
           ele_list[field_ctr] = -1;
         }
         break;
       case ' ' :
         if(!ele_list[field_ptr]) {
           width = headlen(el);
/* *********
           if(line_width+width+1 >= PAPERWIDTH) {
             sprintf(msg, " %dƒe åaª° –·∂wñSì°îa ", PAPERWIDTH);
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
         hputsxy(cur_col-1, cur_row, ele_list[field_ptr] ? "Ÿ–" : "  ");
         break;
       case '\r' :
         if(!ele_list[field_ptr]) {
           width = headlen(el);
/* ************
           if(line_width+width+1 >= PAPERWIDTH) {
             sprintf(msg, " %dƒe åaª° –·∂wñSì°îa ", PAPERWIDTH);
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
         hputsxy(cur_col-1, cur_row, ele_list[field_ptr] ? "Ÿ–" : "  ");
         if(field_ptr+1 == field_ctr)
           field_ptr = 0;
         else
           field_ptr++;
         break;
     }    /* switch */
  }   /* while */
  return ele_list;
}

/* ∂EΩ¢ ∏˜ùi–aâ° µ°üeΩ¢∑Å ß•ƒe∑e â∑§Ç∑aù° ¿Å∂Öîa */
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

/* ¢Ö∏aµi süi µ°üeΩ¢ ∏˜ùi(ß•ƒe∑e â∑§Ç∑aù° ¿Å∂Öîa */
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

/* ¢Ö∏aµi süi µ°üeΩ¢ ∏˜ùi(ß•ƒe∑e 0∑aù° ¿Å∂Öîa */
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

/* ¢Ö∏aµi c¥eµA â∑§Ç†e ói¥·∑∂∑a°e ¿q àt∑i ï©ùa∫Öîa */
int spaces(char *c)
{
   while (*c == ' ')
     c++;
   return !*c;
}

/* ¢Ö∏aµi sàa ëe∂©∑©ù° ñA¥·¨· àbàb∑Å àt∑° ∏‚îw–eàa  */
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
  post_notice("êiºaàa ∏i°µñA¥ˆ¥·∂a, ëe.∂©.∑© ÆÖ¨·ù° ñA¥·¥°–Å∂a");
  return DBERROR;
}

/* —¡°e∑Å °°óe œ©óaµA ∏aûa ∂a≠° àt ¬âùb */
void tally(void)
{
   int *els = elist;

/*   pushwindow();
   hwindow(2, TITLE_Y+2, hgetmaxax()-1, STATUS_Y-1); */
   while (*els)
     put_field(*els++);
/*   popwindow(); */
}

/* ∏aûa ∂a≠°üi —¡°e †aØa«aµ¡ –qçA —¡°eµA ¬âùb–eîa */
void put_field(int el)
{
   data_coord(el);
   disp_element(bf + epos(el, elist), elmask[el - 1], el);
}

/* bìe —¡°e §·Ã·µA¨· —e∏Å œ©óa∑Å ∂·√°  Õ°∑•»·, ∏aûa ∂a≠°üi —¡°eµA ¬âùb */
static void disp_element(char *b, char *msk, int el)
{
   char merge[80];
   register i = 0;

   if(eltype[el-1] == 'G') { /* ãaü± Ãa∑©∑Å âw∂Å */
     /*
      * prime_keyüi Ãa∑©∑°üq∑aù° –aìe PCXÃa∑©∑i ∑™¥·¨·
      * ∏˜–Åª• π¡Œaµ¡ «aã°ù° —¡°eµA ¬âùb–eîa.
      * òaúa¨· ∏aûa∂a≠° ∫óµA ãaü±∑° ∑∂ìe ∏aûaÃa∑©∑Å âw∂ÅµAìe
      * ∫Å«°üi 8∏a ∑°êÅù° –aìeâA πΩâVª°?
      */
     /* put_pcx(prim_key); */ /* PCXÃa∑© •°ã° */
   }
   else if(eltype[el-1] == 'M') {
     hputs(">>¢Ö¨·<<");
   }
   else { /* ãa ∑°∂A∑Å âw∂Å */
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
     hputs(merge);   /* —¡°e»i∑i Õ°–q–e ∏aûa∂a≠°∑Å ¢Ö∏aµi */
   }
}


