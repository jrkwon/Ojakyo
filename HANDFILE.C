/* #define DEBUG */

/*
 *  handfile.c
 *
 *  database data file manager
 *  92.  7. 16
 */

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "handbms.h"

#define flocate(r,l) ((long)(sizeof(FHEADER)+(((r)-1)*(l))))

static int handle [MAXFILS];
FHEADER fh [MAXFILS];

/*
 *  ¸aža Ìa·©·i  e—e”a.
 *  ¬÷‰·Ða¡e Ìa·© Ð…—i·i, ¯©ÌÐa¡e -1·i •©aº…”a.
 */
int file_create(name, len)
char *name;
int len;
{
  int fp;
  FHEADER hd;

  unlink(name);
  fp = creat(name, CMODE);
  close(fp);
  fp = open(name, OPENMODE);
  if(fp == -1)
    return DBERROR;
  hd.next_record = 1;
  hd.first_record = 0;
  hd.total_record = 0;
  hd.record_length = len;
  write(fp, (char *) &hd, sizeof hd);
  close(fp);
  return fp;
}

/* --------------  open a file ---------------- */
int file_open(name)
char *name;
{
	int fp;

	for (fp = 0; fp < MAXFILS; fp++)
		if (handle [fp] == 0)
			break;
	if (fp == MAXFILS)
		return DBERROR;
	if ((handle [fp] = open(name, OPENMODE)) == DBERROR) {
      /*
       *  µa‹¡¬á ¯©ÌÐa¡e, Ìa·©·i  e—e ÒµA ”a¯¡
       *  ·¡ Ðq®Ÿi Ñ¡Â‰Ð¬á µi‹¡Ÿi ¯¡•¡Ðe”a.
       *  ˜aœa¬á Ð…—i(handle[])·i ”a¯¡ Á¡‹¡ÑÁ ¯¡Åaº´á´¡ Ðe”a.
       */
       handle[fp] = 0;
	   return DBERROR;
    }
	lseek(handle [fp], 0L, 0);
	read(handle [fp], (char *) &fh [fp], sizeof(FHEADER));
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10ld",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	return fp;
}

/* --------------- close a file ----------------- */
void file_close(fp)
int fp;
{
	lseek(handle [fp], 0L, 0);
	write(handle [fp], (char *) &fh [fp], sizeof(FHEADER));
	close(handle [fp]);
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10d",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	handle [fp] = 0;
}

/* -------------- get total record number --------- */
RPTR get_total_record(int fp)
{
  return fh[fp].total_record;
}

/* -------------- create a new record ------------- */
RPTR new_record(fp, bf)
int fp;
char *bf;
{
	RPTR rcdno;
	FHEADER *c;

	if (fh [fp].first_record)	{  /* »¡¶¡»¥ ¸ažaˆa ·¶”a¡e, ‹aˆõ  å¸á À¶…”a */
		rcdno = fh [fp].first_record;
		if ((c = (FHEADER *)malloc(fh [fp].record_length)) == NULL)	{
			errno = D_OM;
			dberror();
		}
		get_record(fp, rcdno, c);
		fh [fp].first_record = c->next_record;
		free(c);
	}
	else
		rcdno = fh [fp].next_record++;

  fh[fp].total_record++;
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10ld",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	put_record(fp, rcdno, bf);
	return rcdno;
}

/* ---------------- retrieve a record -------------- */
int get_record(fp, rcdno, bf)
int fp;
RPTR rcdno;
char *bf;
{
	if (rcdno >= fh [fp].next_record)
		return DBERROR;
	lseek(handle [fp], flocate(rcdno, fh [fp].record_length), 0);
	read(handle [fp], bf, fh [fp].record_length);
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10ld",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	return DBOK;
}

/* ---------------- rewrite a record -------------- */
int put_record(fp, rcdno, bf)
int fp;
RPTR rcdno;
char *bf;
{
	if (rcdno > fh [fp].next_record)
		return DBERROR;
	lseek(handle [fp], flocate(rcdno, fh [fp].record_length), 0);
	write(handle [fp], bf, fh [fp].record_length);
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10ld",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	return DBOK;
}

/* -------------- delete a record ---------------- */
int delete_record(fp, rcdno)
int fp;
RPTR rcdno;
{
  FHEADER *bf;

  if (rcdno > fh [fp].next_record)
	return DBERROR;
  if ((bf = (FHEADER *)	malloc(fh [fp].record_length)) == NULL)	{
	errno = D_OM;
	dberror();
  }
  set_mem(bf, fh [fp].record_length, '\0');
  bf->next_record = fh [fp].first_record;
  bf->first_record = -1;
  fh [fp].first_record = rcdno;
  fh [fp].total_record--;         /* 93.08.01 */
  put_record(fp, rcdno, bf);
  free(bf);
#ifdef DEBUG
hprintfxy(1, 1, "first : %10ld\nnext : %10ld\ntotal : %10ld",
                 fh[fp].first_record, fh[fp].next_record, fh[fp].total_record);
getch();
#endif
	return DBOK;
}

