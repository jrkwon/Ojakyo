/*
 *  ‰Á¹A    :  ¶Íe¤åÑ¡ Àx‹¡ (º­¡ ÙÐ ÙÑ ¶Íe¤åÑ¡)
 *   e—e ·¡ :  Š¥ ¸ œb
 *   e—e i :  93.08.22
 *  Ða“e ·© :  º­¡Ÿi ·³b¤h´a ¶Íe¤åÑ¡ Àx‹¡, ¶Íe¤åÑ¡ ·³b¤h´a º­¡ Àx‹¡
 */

/*
 *  ¶Íe¤åÑ¡· Ëb»·
 *  ---------------
 *  1. ˆ{·e Š(»¡¤w·e Š…, ¯¡ —w)µA ”Ð¬á ¶Íe¤åÑ¡· ´|¸aŸ¡ˆa ˆ{”a
 *     µŸi —i´á ¬÷•·Š· ¶Íe¤åÑ¡“e [133-...]·¡”a.
 *     (·©¦ »¡¤w•¡¯¡· ‰w¶“e µ¶A)
 *     "‰w‹¡•¡ ¦Àå¯¡ qŠ ŠA´e•·"· ‰w¶, ¦Àå¯¡ qŠµÁ ¦Àå¯¡ ¦‚Š“e
 *     ¶Íe¤åÑ¡ˆa ”aŸa”a.
 *  2. ¹A1•·, 2•·, 3•· ·¡œå¯¢·a¡ Š¬÷–E •·· ¶Íe¤åÑ¡“e
 *     ..•·· ¶Íe¤åÑ¡ + •·¤åÑ¡Ða¡e ŠÐi ® ·¶”a
 *     µŸi —i¡e, ¬w‰•·· ¶Íe¤åÑ¡“e 139-200·¡‰¡
 *     ¬w‰1•··e 139-201, ¬w‰2•··e 139-202, .... ¬w‰10•··e 139-210·¡”a
 *
 *  ´i‰¡Ÿ¡»q
 *  --------
 *  1. ¶Íe¤åÑ¡· ´| ­A¸aŸ¡ˆa ˆ{·e ˆõ·i ·¡¶w.
 *
 *     ¬á¶‰[] = { { "ˆwqŠ", 135, 0 }, { "¬áÁ¡Š", 137, 36 }, ... };
 *                                 --
 *                                 ¸ažaÌa·©µA¬á º‰¤åÑ¡
 *  2. ¸aža Ìa·©· Š¹¡
 *     struct zipdata_t {
 *       int  zip2;                 // ¶Íe¤åÑ¡· –õ¦¦…
 *       byte dong[DONG_LENGTH];    // •·, Š…, ˜a¶á MAX_LENGTH = 30
 *     };
 *
 *  ¯©¹A µ
 *  -------
 *  1. º­¡µA¬á ¶Íe¤åÑ¡ Àx‹¡
 *   1.1 ·©¤e¸â·¥ ‰w¶
 *     "¬á¶‰¯¡ ¬÷•·Š Ð—”w2•·"
 *     "¬á¶‰"·¡œe ¬‚·¥·a¡ ¬á¶‰· ˆb Šˆa ¸á¸w–E ¤µi·i È‚Ða‰¡
 *     ·¡ ¤µi´eµA¬á "¬÷•·Š"Ÿi Àx“e”a. Àx·a¡e, ‰i‰Á ¤µiµA ‹a ¶Íe¤åÑ¡
 *     ´| ­A¸aŸ¡Ÿi ý“e”a. ·¡ µµA¬á“e "133"·¡”a
 *     ‹a ”a·qµA“e ¯©¹A Ìa·©· ¢‰Ÿ¡¸â ¶áÃ¡Ÿi ¸á¸wÐe ‰µ·a¡ ·¡•·Ðaµa
 *     "Ð—”w•·"(•· ¤a¡ ´|µA ·¶“e ®•¸a“e ¸qŒe ¨–‰¡ Àx“e”a)·i Àx“e”a.
 *     ˆá‹¡µA“e 070·¡ ¸á¸w–A´á ·¶‰¡, µ¶A“e ´ô”a.
 *     ˜aœa¬á 070 + 2(•·¤åÑ¡)ˆa Àx“e ¶Íe¤åÑ¡· –õ¦¦…·¡”a.
 *     ‰i‰Á¡... 133-791·¡œa“e ¢…¸aµi·i Â‰bÐe”a.
 *     (*)¢…¹A¸ñ : ¯©¹A¡ ¹¥¸Ða»¡ ´g“e •·•¡ ˆñ¬‚µA ¬÷‰·Ða“e ‰w¶ˆa ¬—‹¥”a.
 *                 Ð—”w•··e 2•· Œa»¡ ¤cµA ´ô·aa, Ð—”w3•··¡œa‰¡ ·³bÐ•¡
 *                 ·¡Ÿi  b·i ¤w¤ó·¡ ´ô”a.
 *    1.2 •¡-¯¡-Š-•· · ‰w¶
 *      "‰w‹¡•¡ ¦Àå¯¡ qŠ ŠA´e•·"
 *      "¦Àå¯¡"µÁ "qŠ"Ÿi ¦›µa(¦Àå¯¡_qŠ)¬‚·¥¤µiµA¬á ˆñ¬‚Ða‰¡,
 *      a á»¡ "ŠA´e•·"·a¡ ¸ažaÌa·© ˆñ¬‚
 *  2. ¶Íe¤åÑ¡µA¬á º­¡ Àx‹¡
 *     "213-917"
 *     "213"·i ˆa»¡‰¡ ¬‚·¥ ¤µi·i Èq¬‚Ð¬á ·¡ˆõ·¡ "ˆw¶¥•¡ ¡wºŠ…"·±·i ´e”a
 *     ·¡¹A, Ìa·©µA¬á ¡wºŠ…µA ”Ðe ¶Íe¤åÑ¡ˆa —i´á ·¶“e ¢‰Ÿ¡¸â ¶áÃ¡¡ ·¡•·
 *     Ðe ”a·q, ˆá‹¡µA¬á 917·¡œe ¶Íe¤åÑ¡Ÿi ˆa»¥ ˆõ·¡ ·¶“e»¡ ¥¥”a.
 *     ·¶·a¡e, ˆá‹¡µA ·¶“e ¢…¸aµi·i "ˆw¶¥•¡ ¡wºŠ…"‰Á ¦›µa¬á Â‰bÐe”a
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "zip-code.h"
#include "zip-idx.h"

#define  ZIPCODEFILE  "ZIP-CODE.DAT"    /* ¶Íe¤åÑ¡ ¸aža Ìa·© ·¡Ÿq */
#define  LINEBUFSIZE  256
#define  SECTBUFSIZE  35                /* º­¡µA¬á ˆb ”e¶á· ÂA” ¤áÌá Ça‹¡ */

static FILE *FileOpen(byte *szFileName, byte *szMode)
{
  FILE *fpFp;

  fpFp = fopen(szFileName, szMode);
  if(fpFp)
    return fpFp;
  fprintf(stderr, "File open Error....(%s)", strupr(szFileName));
  return NULL;
}

static void SplitData(byte *szBuf, byte *szDo, byte *szGun, byte *szMyun, byte *szRi, byte *szTail)
{
  sscanf(szBuf, "%s %s %s %s %s", szDo, szGun, szMyun, szRi, szTail);
}

static void BufferClear(byte *szDo, byte *szGun, byte *szMyun, byte *szRi, byte *szTail)
{
  szDo[0] = szGun[0] = szMyun[0] = szRi[0] = szTail[0] = NULL;
}

static int GetMyunNumber(byte *szMyun)
{
  int nCnt, nNum;

  nNum = 0;
  for(nCnt = strlen(szMyun)-3; nCnt >= 0; nCnt--)
    if(!isdigit(szMyun[nCnt]))
      break;
  if(nCnt >= 0) {
    nNum = atoi(&szMyun[nCnt+1]);
  }
  return nNum;
}

static byte *OmitMyunNumber(byte *szMyun)
{
  int nCnt;

  for(nCnt = strlen(szMyun)-3; nCnt >= 0; nCnt--)
    if(!isdigit(szMyun[nCnt]))
      break;
  if(nCnt >= 0) {
    szMyun[nCnt+1] = NULL;
  }
  strcat(szMyun, "•·");
  return szMyun;
}

static int GetMaxNumber(byte *szMyun)
{
  int nCnt, nNum;

  nNum = 0;
  for(nCnt = strlen(szMyun)-1; nCnt >= 0; nCnt--)
    if(!isdigit(szMyun[nCnt]))
      break;
  if(nCnt >= 0) {
    nNum = atoi(&szMyun[nCnt+1]);
  }
  return nNum;
}

static byte *OmitMaxNumber(byte *szMyun)
{
  int nCnt;

  for(nCnt = strlen(szMyun)-1; nCnt >= 0; nCnt--)
    if(!isdigit(szMyun[nCnt]))
      break;
  if(nCnt >= 0) {
    szMyun[nCnt+1] = NULL;
  }
  return szMyun;
}

static byte *GetLastChar(byte *szStr)
{
  return &szStr[strlen(szStr)-2];
}

/*
 * º­¡¡ ¶Íe¤åÑ¡ Àx‹¡
 */
byte *addr2zip(byte *szAddr, char *szRet)
{
  FILE *fpData;                   /* ¶Íe¤åÑ¡ ¸aža Ìa·© Í¡·¥Èá */
  byte szBuf[LINEBUFSIZE];        /* ¶¥¯¡ ¸aža Ìa·©·i ·ª·i ˜ ³a“e ¤áÌá */
  byte szZip[LINEBUFSIZE];        /* Àx·e ¶Íe¤åÑ¡ */
  byte szDo[SECTBUFSIZE];         /* Ëb¥i¯¡, »¢Ði¯¡, •¡ */
  byte szGun[SECTBUFSIZE];        /* Š, Š… */
  byte szMyun[SECTBUFSIZE];       /* ·s, ¡e, •· */
  byte szRi[SECTBUFSIZE];         /* Ÿ¡ */
  byte szTail[SECTBUFSIZE];       /* µ¶A ÀáŸ¡Ÿi ¶áÐe ‰·ˆe */
  byte szTmp[SECTBUFSIZE];        /* ¢…¸aµi ¹¡¸b·i ¶áÐe ·±¯¡¸á¸w­¡ */
  byte szTmp2[SECTBUFSIZE];       /* ¢…¸aµi ¹¡¸b·i ¶áÐe ·±¯¡¸á¸w­¡ */
  int nDongNo;                    /* •·¤åÑ¡Ÿi ¸á¸w */
  int nMaxNo;                     /* ÂA” •·¤åÑ¡Ÿi ¸á¸w */
  int nCount;
  int nLineNo;
  int nCnt;
  int nTmp;
  struct idxdata_t *pIdxData;     /* ¬‚·¥ ¤µi· Í¡·¥Èá */

  fpData = FileOpen(ZIPCODEFILE, "r");
  if(fpData == NULL)
    return NULL;

  if(szAddr[0] == NULL)
    return NULL;

  nDongNo = 0;
  BufferClear(szDo, szGun, szMyun, szRi, szTail);
  SplitData(szAddr, szDo, szGun, szMyun, szRi, szTail);

  /*
   *  •¡-¯¡-Š-•· ·¥ ‰w¶ ÀáŸ¡
   */
  if(!strcmp(GetLastChar(szGun), "¯¡") && !strcmp(GetLastChar(szMyun), "Š")) {
    sprintf(szTmp, "%s_%s", szGun, szMyun);
    strcpy(szGun, szTmp);
    strcpy(szMyun, szRi);
    szRi[0] = NULL;
    szTail[0] = NULL;
  }
  /*
   *  •··¡ŸqµA¬á ¤åÑ¡“e ˜a¡ ¸á¸wÐa‰¡, ¤åÑ¡Ÿi ¨… •··¡Ÿq·i  e—e”a
   */
  if(!strcmp(GetLastChar(szMyun), "•·")) {
    nDongNo = GetMyunNumber(szMyun);
    if(nDongNo)
      OmitMyunNumber(szMyun);
  }
  /*
   *  ˆw¶¥•¡ µw¶©Š… º—•·¡e »¢•·2Ÿ¡ ¬÷Á¥
   *  ·¡ º­¡· ‰w¶, "º—•·¡e"· ¶Íe¤åÑ¡µÁ "»¢•·2Ÿ¡ ¬÷Á¥"· ¶Íe¤åÑ¡ˆa
   *  ¬á¡ ”aŸa”a. ·¡ ‰w¶“e "º—•·¡e"µA ‰Åe–E º­¡“e º—•·¡e –õ¦¦…•¡
   *  Í¡Ðq¯¡Åa¬á ˆñ¬‚Ða•¡¢ Ð´¡Ðe”a
   */
  if(szRi[0]) {
    sprintf(szTmp, "%s %s %s", szMyun, szRi, szTail);
    strcpy(szMyun, szTmp);
  }

  /*
   *  szDo ´|· –‹i¸a¡ ¬á¶‰, ¦¬e, ... —w·i ´i´a…”a
   */
  for(nCnt = 0; szSiDo[nCnt][0]; nCnt++)
    if(!strncmp(szSiDo[nCnt], szDo, 4))
      break;
  if(szSiDo[nCnt][0] == NULL)           /* ¸i¡µ–E ¯¡,•¡ ·¡Ÿq */
    return NULL;
  pIdxData = idxsido[nCnt];

  for(nCnt = 0; pIdxData[nCnt].szGun[0]; nCnt++)
    if(!strcmp(pIdxData[nCnt].szGun, szGun))
      break;
  if(pIdxData[nCnt].szGun[0] == NULL)  /* ¸i¡µ–E Š, Š…, »¡¤w•¡¯¡ ·¡Ÿq */
    return NULL;
  itoa(pIdxData[nCnt].nZip1, szZip, 10);
  nLineNo = pIdxData[nCnt].nOffSet;
  nCount = pIdxData[nCnt+1].nOffSet-pIdxData[nCnt].nOffSet;

  /*
   *  ¬‚·¥–A´á ·¶“e ¶áÃ¡Œa»¡ ·¡•·
   */
  for(nCnt = 0; nCnt < nLineNo; nCnt++)
    fgets(szBuf, LINEBUFSIZE, fpData);
  /*
   *  ¸aža §¡Ša
   *  ¸ažaÌa·© Š¹¡
   *
   *  230 w¶•·
   *  200¡e¡¢•·
   *  ....
   */
  for(nCnt = 0; nCnt < nCount; nCnt++) {
    fgets(szBuf, LINEBUFSIZE, fpData);
    strcpy(szTmp, szBuf+3);
    szBuf[3] = NULL;
    /*  a»¡ b· \n¢…¸a ´ô´…”a */
    nTmp = strlen(szTmp)-1;
    if(nTmp >= 0)
      szTmp[nTmp] = NULL;
    nMaxNo = GetMaxNumber(szTmp);
    strcpy(szTmp, OmitMaxNumber(szTmp));
    if(!strncmp(szTmp, szMyun, strlen(szMyun))) {
      if(nDongNo <= nMaxNo) {
        nTmp = atoi(szBuf) + nDongNo;
        sprintf(szTmp2, "%s-%03d", szZip, nTmp);
        strcpy(szZip, szTmp2);
        break;
      }
      else
        return NULL;
    }
  }
  fclose(fpData);
  strcpy(szRet, szZip);
  return (nCnt == nCount) ? NULL : szZip;
}

/*
 *  ¶Íe¤åÑ¡¡ º­¡ Àx‹¡
 */
byte *zip2addr(byte *szZip, byte *szRet)
{
  FILE *fpData;                   /* ¶Íe¤åÑ¡ ¸aža Ìa·© Í¡·¥Èá */
  byte szBuf[LINEBUFSIZE];        /* ¶¥¯¡ ¸aža Ìa·©·i ·ª·i ˜ ³a“e ¤áÌá */
  byte szAddr[LINEBUFSIZE];       /* Àx·e º­¡ */
  byte szZip1[4];                 /* ¶Íe¤åÑ¡ ´| ½¢ ­A¸aŸ¡ */
  byte szZip2[4];                 /* ¶Íe¤åÑ¡ –á ½¢ ­A¸aŸ¡ */
  byte szTmp[LINEBUFSIZE];
  byte szTmp2[LINEBUFSIZE];
  struct idxdata_t *pIdxData;     /* ¬‚·¥ ¤µi· Í¡·¥Èá */
  byte *pTmp, bNo;
  int nLineNo;
  int nMaxNo;
  int nCount;
  int nCnt, nCnt2, nTmp;
  bool flag;

  fpData = FileOpen(ZIPCODEFILE, "r");
  if(fpData == NULL)
    return NULL;

  if(szZip[0] == NULL)
    return NULL;

  strcpy(szZip1, szZip);
  szZip1[3] = NULL;
  strcpy(szZip2, szZip+4);

  /*
   *  ¶Íe¤åÑ¡ ´| ­A¸aŸ¡Ÿi ˆa»¡‰¡ ¬‚·¥¤µi·i ˆñ¬‚Ðe”a
   */
  flag = false;
  for(nCnt = 0; idxsido[nCnt] && !flag; nCnt++) {
    pIdxData = idxsido[nCnt];
    for(nCnt2 = 0; pIdxData[nCnt2].nZip1; nCnt2++) {
      if(atoi(szZip1) == pIdxData[nCnt2].nZip1) {
        sprintf(szAddr, "%s %s", szSiDo[nCnt], pIdxData[nCnt2].szGun);
        flag = true;
        break;
      }
    }
  }
  if(!idxsido[nCnt])
    return NULL;

  nLineNo = pIdxData[nCnt2].nOffSet;
  nCount = pIdxData[nCnt2+1].nOffSet-pIdxData[nCnt2].nOffSet;

  /*
   *  ¬‚·¥–A´á ·¶“e ¶áÃ¡Œa»¡ ·¡•·
   */
  for(nCnt = 0; nCnt < nLineNo; nCnt++)
    fgets(szBuf, LINEBUFSIZE, fpData);
  /*
   *  ¸aža §¡Ša
   *  ¸ažaÌa·© Š¹¡
   *
   *  230 w¶•·
   *  200¡e¡¢•·
   *  ....
   */
  flag =  false;
  for(nCnt = 0; nCnt < nCount; nCnt++) {
    fgets(szBuf, LINEBUFSIZE, fpData);
    strcpy(szTmp, szBuf+3);
    szBuf[3] = NULL;
    nTmp = strlen(szTmp)-1;
    if(nTmp >= 0)
      szTmp[nTmp] = NULL;
    if(!strcmp(szBuf, szZip2)) {
      sprintf(szTmp2, "%s %s", szAddr, szTmp);
      strcpy(szAddr, szTmp2);
      flag = true;
      break;
    }
  }
  /*
   *  Àx‹¡ ¯©Ì·¡‰¡ ¶Íe¤åÑ¡· –õ¸aŸ¡ˆa '0'·a¡ {a»¡ ´g·a¡e
   *  Ñ¢¯¡ ..1•·, ..2•·.. ˜a¶áˆa ´a“¥ˆa Àx´a¥¥”a
   */
  if(nCnt == nCount && !flag) {
    rewind(fpData);
    for(nCnt = 0; nCnt < nLineNo; nCnt++)
      fgets(szBuf, LINEBUFSIZE, fpData);
    bNo = szZip2[strlen(szZip2)-1];
    szZip2[strlen(szZip2)-1] = '0';
    for(nCnt = 0; nCnt < nCount; nCnt++) {
      fgets(szBuf, LINEBUFSIZE, fpData);
      strcpy(szTmp, szBuf+3);
      szBuf[3] = NULL;
      /*  a»¡ b· \n¢…¸a ´ô´…”a */
      nTmp = strlen(szTmp)-1;
      if(nTmp >= 0)
        szTmp[nTmp] = NULL;
      nMaxNo = GetMaxNumber(szTmp);
      strcpy(szTmp, OmitMaxNumber(szTmp));
      szTmp[strlen(szTmp)-2] = NULL;
      if(!strcmp(szBuf, szZip2)) {
        if((bNo-'0') <= nMaxNo) {
          sprintf(szTmp2, "%s %s%c•·", szAddr, szTmp, bNo);
          strcpy(szAddr, szTmp2);
          break;
        }
        else
          return NULL;
      }
    }
  }
  /*
   *  10•··¡ ñ“e ˆõ•¡ ·¶‘A ‹aa...
   */
  if(nCnt == nCount && szZip2[strlen(szZip2)-1] == '0') {
    rewind(fpData);
    for(nCnt = 0; nCnt < nLineNo; nCnt++)
      fgets(szBuf, LINEBUFSIZE, fpData);
    szZip2[strlen(szZip2)-2] -= 1;
    for(nCnt = 0; nCnt < nCount; nCnt++) {
      fgets(szBuf, LINEBUFSIZE, fpData);
      strcpy(szTmp, szBuf+3);
      szBuf[3] = NULL;
      /*  a»¡ b· \n¢…¸a ´ô´…”a */
      nTmp = strlen(szTmp)-1;
      if(nTmp >= 0)
        szTmp[nTmp] = NULL;
      nMaxNo = GetMaxNumber(szTmp);
      strcpy(szTmp, OmitMaxNumber(szTmp));
      szTmp[strlen(szTmp)-2] = NULL;
      if(!strcmp(szBuf, szZip2)) {
        if(bNo-'0'+10 <= nMaxNo) {
          sprintf(szTmp2, "%s %s1%c•·", szAddr, szTmp, bNo);
          strcpy(szAddr, szTmp2);
          break;
        }
        else
          return NULL;
      }
    }
  }

  fclose(fpData);

  /* º­¡ º—µA —i´á ·¶“e '_'·i ‰·¤‚·a¡ ¤aŽ…”a */
  pTmp = strchr(szAddr, '_');
  if(pTmp)
    *pTmp = ' ';
  strcpy(szRet, szAddr);
  return (nCnt == nCount) ? NULL : szAddr;
}

