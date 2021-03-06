/*
 *  ���A    :  ���e��ѡ �x�� (���� �� �� ���e��ѡ)
 *  �e�e �� :  �� �� �b
 *  �e�e �i :  93.08.22
 *  �a�e �� :  �����i ���b�h�a ���e��ѡ �x��, ���e��ѡ ���b�h�a ���� �x��
 */

/*
 *  ���e��ѡ�� �b��
 *  ---------------
 *  1. �{�e ��(���w�e ��, �� �w)�A ��Ё�� ���e��ѡ�� �|�a���a �{�a
 *     ���i �i�� �������� ���e��ѡ�e [133-...]���a.
 *     (���� ���w������ �w���e ���A)
 *     "�w���� ���寡 �q�� �A�e��"�� �w��, ���寡 �q���� ���寡 �����e
 *     ���e��ѡ�a �a�a�a.
 *  2. �A1��, 2��, 3�� ���寢�a�� �����E ���� ���e��ѡ�e
 *     ..���� ���e��ѡ + ����ѡ�a�e ���i �� ���a
 *     ���i �i�e, �w������ ���e��ѡ�e 139-200����
 *     �w��1���e 139-201, �w��2���e 139-202, .... �w��10���e 139-210���a
 *
 *  �i�����q
 *  --------
 *  1. ���e��ѡ�� �| �A�a���a �{�e ���i ���w.
 *
 *     �ᶉ[] = { { "�w�q��", 135, 0 }, { "������", 137, 36 }, ... };
 *                                 --
 *                                 �a�a�a���A�� ����ѡ
 *  2. �a�a �a���� ����
 *     struct zipdata_t {
 *       int  zip2;                 // ���e��ѡ�� ������
 *       byte dong[DONG_LENGTH];    // ��, ��, �a�� MAX_LENGTH = 30
 *     };
 *
 *  ���A ��
 *  -------
 *  1. �����A�� ���e��ѡ �x��
 *   1.1 ���e�ⷥ �w��
 *     "�ᶉ�� ������ З�w2��"
 *     "�ᶉ"���e �����a�� �ᶉ�� �b ���a ��w�E ���i�i Ȃ�a��
 *     �� ���i�e�A�� "������"�i �x�e�a. �x�a�e, �i�� ���i�A �a ���e��ѡ
 *     �| �A�a���i ���e�a. �� ���A��e "133"���a
 *     �a �a�q�A�e ���A �a���� ������ ��á�i ��w�e ���a�� �����a�a
 *     "З�w��"(�� �a�� �|�A ���e ���a�e �q�e ������ �x�e�a)�i �x�e�a.
 *     �ዡ�A�e 070�� ��w�A�� ����, ���A�e ���a.
 *     �a�a�� 070 + 2(����ѡ)�a �x�e ���e��ѡ�� ���������a.
 *     �i����... 133-791���a�e ���a�i�i �b�e�a.
 *     (*)���A�� : ���A�� �����a�� �g�e ���� �񬂵A �����a�e �w���a �����a.
 *                 З�w���e 2�� �a�� �c�A ���a�a, З�w3�����a�� ���bЁ��
 *                 ���i �b�i �w�� ���a.
 *    1.2 ��-��-��-�� �� �w��
 *      "�w���� ���寡 �q�� �A�e��"
 *      "���寡"�� "�q��"�i ���a(���寡_�q��)�������i�A�� ���a��,
 *      �a�ỡ "�A�e��"�a�� �a�a�a�� ��
 *  2. ���e��ѡ�A�� ���� �x��
 *     "213-917"
 *     "213"�i �a���� ���� ���i�i �q��Ё�� ������ "�w���� �w����"���i �e�a
 *     ���A, �a���A�� �w�����A ���e ���e��ѡ�a �i�� ���e ������ ��á�� ����
 *     �e �a�q, �ዡ�A�� 917���e ���e��ѡ�i �a�� ���� ���e�� ���a.
 *     ���a�e, �ዡ�A ���e ���a�i�i "�w���� �w����"�� ���a�� �b�e�a
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "zip-code.h"
#include "zip-idx.h"

#define  ZIPCODEFILE  "ZIP-CODE.DAT"    /* ���e��ѡ �a�a �a�� ���q */
#define  LINEBUFSIZE  256
#define  SECTBUFSIZE  35                /* �����A�� �b �e�᷁ �A�� ���� �a�� */

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
  strcat(szMyun, "��");
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
 * ������ ���e��ѡ �x��
 */
byte *addr2zip(byte *szAddr, char *szRet)
{
  FILE *fpData;                   /* ���e��ѡ �a�a �a�� ͡���� */
  byte szBuf[LINEBUFSIZE];        /* ���� �a�a �a���i ���i �� �a�e ���� */
  byte szZip[LINEBUFSIZE];        /* �x�e ���e��ѡ */
  byte szDo[SECTBUFSIZE];         /* �b�i��, ���i��, �� */
  byte szGun[SECTBUFSIZE];        /* ��, �� */
  byte szMyun[SECTBUFSIZE];       /* �s, �e, �� */
  byte szRi[SECTBUFSIZE];         /* �� */
  byte szTail[SECTBUFSIZE];       /* ���A �១�i ���e ���e */
  byte szTmp[SECTBUFSIZE];        /* ���a�i ���b�i ���e ������w�� */
  byte szTmp2[SECTBUFSIZE];       /* ���a�i ���b�i ���e ������w�� */
  int nDongNo;                    /* ����ѡ�i ��w */
  int nMaxNo;                     /* �A�� ����ѡ�i ��w */
  int nCount;
  int nLineNo;
  int nCnt;
  int nTmp;
  struct idxdata_t *pIdxData;     /* ���� ���i�� ͡���� */

  fpData = FileOpen(ZIPCODEFILE, "r");
  if(fpData == NULL)
    return NULL;

  if(szAddr[0] == NULL)
    return NULL;

  nDongNo = 0;
  BufferClear(szDo, szGun, szMyun, szRi, szTail);
  SplitData(szAddr, szDo, szGun, szMyun, szRi, szTail);

  /*
   *  ��-��-��-�� �� �w�� �១
   */
  if(!strcmp(GetLastChar(szGun), "��") && !strcmp(GetLastChar(szMyun), "��")) {
    sprintf(szTmp, "%s_%s", szGun, szMyun);
    strcpy(szGun, szTmp);
    strcpy(szMyun, szRi);
    szRi[0] = NULL;
    szTail[0] = NULL;
  }
  /*
   *  �����q�A�� ��ѡ�e �a�� ��w�a��, ��ѡ�i �� �����q�i �e�e�a
   */
  if(!strcmp(GetLastChar(szMyun), "��")) {
    nDongNo = GetMyunNumber(szMyun);
    if(nDongNo)
      OmitMyunNumber(szMyun);
  }
  /*
   *  �w���� �w���� �����e ����2�� ����
   *  �� ������ �w��, "�����e"�� ���e��ѡ�� "����2�� ����"�� ���e��ѡ�a
   *  �ᝡ �a�a�a. �� �w���e "�����e"�A �ŝe�E �����e �����e ��������
   *  ͡�q���a�� ���a���� Ё���e�a
   */
  if(szRi[0]) {
    sprintf(szTmp, "%s %s %s", szMyun, szRi, szTail);
    strcpy(szMyun, szTmp);
  }

  /*
   *  szDo �|�� ���i�a�� �ᶉ, ���e, ... �w�i �i�a���a
   */
  for(nCnt = 0; szSiDo[nCnt][0]; nCnt++)
    if(!strncmp(szSiDo[nCnt], szDo, 4))
      break;
  if(szSiDo[nCnt][0] == NULL)           /* �i���E ��,�� ���q */
    return NULL;
  pIdxData = idxsido[nCnt];

  for(nCnt = 0; pIdxData[nCnt].szGun[0]; nCnt++)
    if(!strcmp(pIdxData[nCnt].szGun, szGun))
      break;
  if(pIdxData[nCnt].szGun[0] == NULL)  /* �i���E ��, ��, ���w���� ���q */
    return NULL;
  itoa(pIdxData[nCnt].nZip1, szZip, 10);
  nLineNo = pIdxData[nCnt].nOffSet;
  nCount = pIdxData[nCnt+1].nOffSet-pIdxData[nCnt].nOffSet;

  /*
   *  �����A�� ���e ��á�a�� ����
   */
  for(nCnt = 0; nCnt < nLineNo; nCnt++)
    fgets(szBuf, LINEBUFSIZE, fpData);
  /*
   *  �a�a ���a
   *  �a�a�a�� ����
   *
   *  230�w����
   *  200�e����
   *  ....
   */
  for(nCnt = 0; nCnt < nCount; nCnt++) {
    fgets(szBuf, LINEBUFSIZE, fpData);
    strcpy(szTmp, szBuf+3);
    szBuf[3] = NULL;
    /* �a���b�� \n���a �����a */
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
 *  ���e��ѡ�� ���� �x��
 */
byte *zip2addr(byte *szZip, byte *szRet)
{
  FILE *fpData;                   /* ���e��ѡ �a�a �a�� ͡���� */
  byte szBuf[LINEBUFSIZE];        /* ���� �a�a �a���i ���i �� �a�e ���� */
  byte szAddr[LINEBUFSIZE];       /* �x�e ���� */
  byte szZip1[4];                 /* ���e��ѡ �| �� �A�a�� */
  byte szZip2[4];                 /* ���e��ѡ �� �� �A�a�� */
  byte szTmp[LINEBUFSIZE];
  byte szTmp2[LINEBUFSIZE];
  struct idxdata_t *pIdxData;     /* ���� ���i�� ͡���� */
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
   *  ���e��ѡ �| �A�a���i �a���� �������i�i ���e�a
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
   *  �����A�� ���e ��á�a�� ����
   */
  for(nCnt = 0; nCnt < nLineNo; nCnt++)
    fgets(szBuf, LINEBUFSIZE, fpData);
  /*
   *  �a�a ���a
   *  �a�a�a�� ����
   *
   *  230�w����
   *  200�e����
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
   *  �x�� ��́���� ���e��ѡ�� ���a���a '0'�a�� �{�a�� �g�a�e
   *  Ѣ�� ..1��, ..2��.. �a��a �a���a �x�a���a
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
      /* �a���b�� \n���a �����a */
      nTmp = strlen(szTmp)-1;
      if(nTmp >= 0)
        szTmp[nTmp] = NULL;
      nMaxNo = GetMaxNumber(szTmp);
      strcpy(szTmp, OmitMaxNumber(szTmp));
      szTmp[strlen(szTmp)-2] = NULL;
      if(!strcmp(szBuf, szZip2)) {
        if((bNo-'0') <= nMaxNo) {
          sprintf(szTmp2, "%s %s%c��", szAddr, szTmp, bNo);
          strcpy(szAddr, szTmp2);
          break;
        }
        else
          return NULL;
      }
    }
  }
  /*
   *  10���� ��e ���� ���A �a�a...
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
      /* �a���b�� \n���a �����a */
      nTmp = strlen(szTmp)-1;
      if(nTmp >= 0)
        szTmp[nTmp] = NULL;
      nMaxNo = GetMaxNumber(szTmp);
      strcpy(szTmp, OmitMaxNumber(szTmp));
      szTmp[strlen(szTmp)-2] = NULL;
      if(!strcmp(szBuf, szZip2)) {
        if(bNo-'0'+10 <= nMaxNo) {
          sprintf(szTmp2, "%s %s1%c��", szAddr, szTmp, bNo);
          strcpy(szAddr, szTmp2);
          break;
        }
        else
          return NULL;
      }
    }
  }

  fclose(fpData);

  /* ���� ���A �i�� ���e '_'�i �����a�� �a���a */
  pTmp = strchr(szAddr, '_');
  if(pTmp)
    *pTmp = ' ';
  strcpy(szRet, szAddr);
  return (nCnt == nCount) ? NULL : szAddr;
}

