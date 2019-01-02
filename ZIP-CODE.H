/*
 *  ����    :  �ּҷ� ������ȣ ã��, ������ȣ���� �ּ� ã��
 *  ���� �� :  ����� (�Ѿ���б� ������Ű��а� �ΰ����ɿ�����)
 *  ���� �� :  93.08.21
 *  ����    :  ZIP-CODE.H
 *  �ϴ� �� :  ������ȣ ������ ���̴� �ڷ��� ¥�ӻ�
 */

#ifndef _ZIPCODE_H_
#define _ZIPCODE_H_
#endif

#include "typedefs.h"

#define  MYUNLEN      30     /* ��, ��, �� ������ �ִ� ���� */

/*
 * ���� �迭�� ¥�ӻ�
 */
struct idxdata_t {
  byte szGun[MYUNLEN];       /* ��, (�뵵���� ��� ��) */
  int  nZip1;                /* ������ȣ�� ���ڸ� */
  int  nOffSet;              /* �� �ڷ��� ���� */
};

/*
 *  �ڷ� ������ ¥�ӻ�
 */
struct zipdata_t {
  int  nZip2;                 /* ������ȣ�� �޺κ� */
  byte szMyun[MYUNLEN];        /* ��, ��, ���� MYUNLEN = 30 */
};

byte *addr2zip(byte *szAddr, char *szRet);
byte *zip2addr(byte *szZip, byte *szRet);

