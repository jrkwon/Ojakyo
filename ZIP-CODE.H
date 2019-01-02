/*
 *  과제    :  주소로 우편번호 찾기, 우편번호에서 주소 찾기
 *  만든 이 :  권재락 (한양대학교 전자통신공학과 인공지능연구실)
 *  만든 날 :  93.08.21
 *  파일    :  ZIP-CODE.H
 *  하는 일 :  우편번호 과제에 쓰이는 자료의 짜임새
 */

#ifndef _ZIPCODE_H_
#define _ZIPCODE_H_
#endif

#include "typedefs.h"

#define  MYUNLEN      30     /* 읍, 면, 동 단위의 최대 길이 */

/*
 * 색인 배열의 짜임새
 */
struct idxdata_t {
  byte szGun[MYUNLEN];       /* 군, (대도시의 경우 구) */
  int  nZip1;                /* 우편번호의 앞자리 */
  int  nOffSet;              /* 이 자료의 색인 */
};

/*
 *  자료 파일의 짜임새
 */
struct zipdata_t {
  int  nZip2;                 /* 우편번호의 뒷부분 */
  byte szMyun[MYUNLEN];        /* 동, 군, 따위 MYUNLEN = 30 */
};

byte *addr2zip(byte *szAddr, char *szRet);
byte *zip2addr(byte *szZip, byte *szRet);

