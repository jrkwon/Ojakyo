/*****************************************************
 *                                                   *
 *      Index table for combination code             *
 *      and character set for fixed code             *
 *                                                   *
 *      Sambo, Samsung, GoldStar, Old KS, DKBII      *
 *      and KSC5601, 7 Bit Fixed                     *
 *                                                   *
 *      Assembly programmed by Kim, J.W.             *
 *      C converted by Shin, S.D.                    *
 *      Source arranged & modified by Lim, Y.K.      *
 *                                                   *
 *      Modified by Kwon, J.R. in 1993. 07. 30       *
 *                                                   *
 *****************************************************/

#include <string.h>
#include <stdlib.h>

#include "typedefs.h"
#include "hancode.h"

#pragma warn -ucp

typedef struct {
    unsigned c: 5;
    unsigned b: 5;
    unsigned a: 5;
    unsigned i: 1;
} hangul;

/* ���s�w š�a�� �wѡ �e�ŵA �a�w�A�e �e�i �q�� ���� */

char M1[5][32] = {
    {0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,0},
    {0,1,2,0,3,0,0,4,5,6,0,0,0,0,0,0,0,7,8,9,0,10,11,12,13,14,15,16,17,18,19,0},
    {0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,0,0},
    {0,1,2,3,4,5,6,7,8,9,10,11,0,0,0,0,0,0,0,0,0,0,0,12,13,14,15,16,17,18,19,0},
};

char M2[5][32] = {
    {0,0,0,1,2,3,4,5,0,0,6,7,8,9,10,11,0,0,12,13,14,15,16,17,0,0,18,19,20,21,0,0},
    {0,0,0,1,2,3,4,5,0,0,6,7,8,9,10,11,0,0,12,13,14,15,16,17,0,0,18,19,20,21,0,0},
    {0,0,1,2,3,4,5,6,0,0,7,8,9,10,11,12,0,0,13,14,15,16,17,18,0,0,19,20,21,0,0,0},
    {0,0,1,2,0,3,4,5,0,6,7,8,0,9,10,11,0,12,13,14,0,15,16,17,0,18,19,20,0,21,0,0},
    {0,0,0,1,2,3,4,5,0,0,6,7,8,9,10,11,0,0,12,13,14,15,16,17,0,0,18,19,20,21,0,0},
};

char M3[5][32] = {
    {0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,0,17,18,19,20,21,22,23,24,25,26,27,0,0},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,0,0,0,0},
    {0,1,2,3,4,5,6,7,0,8,9,10,11,12,13,14,15,16,17,0,18,19,20,21,22,0,23,24,25,26,27,0},
    {0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,0,0,0},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,00,0,0},
};

char MM1[5][20] = {
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
    {0,1,2,4,7,8,9,17,18,19,21,22,23,24,25,26,27,28,29,30},
    {9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28},
    {0,1,2,3,4,5,6,7,8,9,10,11,23,24,25,26,27,28,29,30},
};

char MM2[5][22]= {
    {2,3,4,5,6,7,10,11,12,13,14,15,18,19,20,21,22,23,26,27,28,29},
    {2,3,4,5,6,7,10,11,12,13,14,15,18,19,20,21,22,23,26,27,28,29},
    {31,2,3,4,5,6,7,10,11,12,13,14,15,18,19,20,21,22,23,26,27,28},
    {1,2,3,5,6,7,9,10,11,13,14,15,17,18,19,21,22,23,25,26,27,29},
    {2,3,4,5,6,7,10,11,12,13,14,15,18,19,20,21,22,23,26,27,28,29},
};

char MM3[5][28] = {
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19,20,21,22,23,24,25,26,27,28,29},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27},
    {0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,16,17,18,20,21,22,23,24,26,27,28,29,30},
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27},
};

/* KSC5601�� 7���a �Ŭ��w š�a�i ���e š�a�a */

byte *fixedcode[2] = {
    "�a�b�e�h�i�j�k�q�s�t�u�v�w�x�y�{�|�}����������������������������������"
    "�Ɉ����������������������A�E�I�Q�S�U�V�W�a�b�c�e�h�i�q�s�u�v�w"
    "�{���������������������������������������ŉɉˉщӉՉ׉��������A"
    "�B�E�I�Q�S�U�W�a�e�i�s�u�����������������������������������������Պ��"
    "�������A�E�I�a�b�e�h�i�j�q�s�u�w���������������������������a�b�c�e"
    "�i�k�q�s�u�v�w�{��������������������������������������A�B�E�Q�U"
    "�W�a�e�i�u�v�{���������������������������ɍ֍׍����A�E�I�Q�S�W�a��"
    "�����������������������������ŎɎюӎ֎�����A�a�b�e�g�i�k�p�q�s"
    "�u�w�{�����������������a�b�c�e�h�i�j�k�q�s�u�v�w�x�y�{�}��������������"
    "����������������������������������A�B�E�I�Q�S�U�V�W�a�b�e�i�q"
    "�s�v�w�z�����������������������������őɑ֒A�E�I�Q�S�U�a�b�e�i�s�u�w��"
    "����������������������������A�B�I�Q�S�W�a�b�e�i�j�k�q�s�u�w�x�|��"
    "�������������������������a�b�c�e�h�i�j�k�l�p�q�s�u�v�w�x�y�}����������"
    "�����������������������������A�B�E�I�Q�S�U�V�W�a�e�i�v�w����"
    "�����������������������������ŕɕ���A�E�I�Q�S�U�a��������������������"
    "���ז��������A�E�I�Q�W�a�b�e�h�i�k�q�s�u�w������������������������"
    "�a�b�e�i�q�s�u�v�w�}�����������������������������������A�B�E�I"
    "�Q�S�U�V�W�a�v�������������ə�A�E������������������������a�b�e�h"
    "�i�q�s�u�������������������������a�b�e�i�q�s�u�v�w�x�|�}��������������"
    "�����������������������������A�B�E�I�Q�S�U�W�a�b�e�i�q�s�u�v�w��"
    "�������������������������ŝם��A�E�I�Q�S�U�W�a�e�i�s�u�w��������������"
    "������������������A�B�E�I�Q�S�U�W�a�b�e�i�q�s�u�w�x�{�|����������"
    "�������a�b�e�g�h�i�j�k�q�s�u�w�x�{�}��������������������������������"
    "�������������A�B�E�I�Q�S�U�V�W�a�b�e�i�u�v�w�y��������������������"
    "�����š֡עA�E�I�S�U�W�a�e�i�s�u��������������������������������������"
    "������A�E�I�Q�U�a�e�i�q�u���������������������������a�b�c�d�e�h�i�j"
    "�k�l�q�s�u�w�{�������������������������������������������A�B�E"
    "�H�I�Q�S�U�V�W�a�b�e�i�s�u�v�w�{�������������������������ť֥���A�B�E"
    "�I�Q�S�a�e�����������������������������������������A�E�I�Q�U�W�a�b"
    "�e�i�q�s�u�����������������������a�b�e�i�k�q�s�u�v�w�}����������������"
    "���������������������A�W�a�b�q�s�u�v�w���������������A�a�w������"
    "���������A�W�a�e�i�q�s�����������������a�b�d�e�h�i�j�k�q�s�u�v�w�{����"
    "���������������������������������ŬɬѬ׬������������������"
    "�A�B�E�I�Q�S�U�V�W�a�b�e�i�q�s�u�v�w����������������������������������"
    "�ŭɭ׭��������A�E�I�Q�S�U�a�b�e�i�q�s�u�w������������������������"
    "�������®ŮɮѮ׮����������A�B�I�Q�U�W�a�b�e�i�j�q�s�u�w��������"
    "���������������a�b�d�e�i�q�s�v�w�}�����������������������������"
    "�A�E�I�W���������������������±űֱ���A�E�I�Q�S�a��������������������"
    "���W�a�b�e�i�k�p�q�s�������������������������a�b�e�f�g�i�j�k�p�q�s�u"
    "�v�w�{�|�������������������������������������������ŴɴӴ�������"
    "������������������A�B�E�I�Q�S�U�W�a�b�c�e�i�k�l�q�s�t�u�v�w�{�|�}��"
    "�����������������������������������������µŵɵѵӵյֵ׵��������A"
    "�B�E�I�Q�S�U�W�a�b�e�i�q�s�u�w����������������������������������������"
    "�ŶɶѶӶ׶����������A�B�E�I�Q�S�U�W�Y�a�b�e�i�o�q�s�u�w�x�y�z�{"
    "�|�}���������������������������������������a�b�e�g�h�i�k�q�s�u�v�w�x��"
    "���������������������������������Ÿɸ�������������A�B�E�I�Q�S�U"
    "�W�a�e�i�q�s�v�w�����������������������������¹ɹӹչ׹�����A�E�I�Q�S"
    "�U�W�a�b�e�w�����������������������������������A�E�I�Q�a�b�e�i�q"
    "�s�u�w���������������������������a�b�e�g�i�l�q�s�u�v�w����������������"
    "���������������������A�W�a�v���������������������½ɽֽ���A�E�I"
    "�Q�S�w����������������������A�a�q�u�w�������������������a�b�e�g�i�q�s"
    "�u�v�w�x�������������������������������������������������A�B�E�I�Q�S�U"
    "�W�a�e�v�������������������������������A�E�I�Q�S�U�W�a�q"
    "¡¶�������������������A�E�I�Q�W�a�b�e�i�q�s�u�wáâåèéêñóõ÷"
    "�a�b�e�i�q�s�u�wāĂąĉđēĕĖėġĢķ���������������������A�B�E�I�Q"
    "�S�U�W�a�e�i�q�s�u�v�wŁšŢťũűųŵŷ�����������������A�I�aƁƂƅƉ"
    "ƑƓƕƗơƥƩƷ���������������������A�E�I�Q�a�b�e�i�q�s�wǡǢǥǩǱǳ"
    "ǵǷ�a�b�e�i�j�q�s�u�v�wȁȂȅȉȑȓȕȖȗȡȷ���������������������A�B"
    "�E�I�Q�S�U�W�a�e�vɁɅɡɢɥɩɱɳɵɷɼ�������A�E�U�W�aʁʂʅʉʑʓʕ"
    "ʗʡʶ�����������������A�E�I�Q�W�a�b�e�h�i�k�q�s�uˁ˅ˉˑ˓ˡˢ˥˩˱"
    "˳˵˷�a�b�c�e�i�k�q�s�u�v�w�{̡̢̖̗́̂̅̉̑̓̕������������������"
    "�A�B�E�I�Q�S�U�W�a�e�i�q�s�v�ẃ͉͓͕ͥͩ͢͡ͱͳ͵ͷ�����A�E�a�e�i�s"
    "�u΁΂΅ΈΉ΋ΑΓΕΗΡη�����������A�E�I�Q�U�W�a�e�i�q�s�uϡϢϥϩϱ"
    "ϳϵϷ�a�b�e�i�n�q�s�u�wЁЂЅЉБГЕЖЗСз�������������������A�B�E"
    "�I�Q�S�U�W�a�b�e�i�q�s�u�v�wсхщѓѡѢѥѩѮѱѳѵѷѻ��������������"
    "���������A�B�E�I�S�U�W�a�e�i�s�uҁ҂҅҉Ҏґҕҗҡҥҩұҷ������������"
    "���������������A�B�E�I�Q�U�W�a�b�e�g�h�i�j�q�s�u�w�{ӁӅӉӑӓӗӡӢӥ"
    "өӱӳӵӷ",
    "_U_V_W_X_Y_Y_Y_Z_[_\\_]_^___`_`_a_b_b_c_d_e_f_g_h_h_h_i_i_i_i_j_j_j_j_j"
    "_j_k_l_m_n_o_o_p_q_r_r_s_s_t_t_t_u_v_w_w_w_x_y_y_z_{_|_}_}_~`!`#`#`$`%"
    "`&`'`'`'`'`'`(`)`*`+`,`-`-`-`.`/`0`1`1`2`3`4`5`5`5`5`5`6`7`8`8`8`8`9`:"
    "`:`;`;`;`;`;`<`=`=`=`=`=`>`?`@`A`B`C`D`D`E`F`G`H`H`H`H`I`J`J`J`K`K`L`L"
    "`L`L`L`L`M`N`O`P`Q`R`S`S`T`U`V`W`X`Y`Y`Z`Z`[`[`\\`\\`]`]`^`^`^`_```a`b`c"
    "`d`d`e`f`f`f`g`h`i`i`i`j`j`j`j`j`j`j`j`j`k`l`m`m`m`n`o`o`o`p`q`q`q`q`q"
    "`q`r`r`r`s`s`s`s`t`u`v`v`w`x`y`y`z`{`|`}`~`~`~`~a@a@aAaBaBaBaBaBaBaCaD"
    "aEaFaGaHaIaIaIaIaIaJaJaJaJaKaKaKaKaKaKaKaLaLaLaLaLaLaMaMaNaOaPaPaPaQaQ"
    "aRaRaSaTaTaUaVaWaWaWaWaXaYaZa[a[a\\a]a]a^a_b@bAbBbCbDbEbFbGbGbHbIbJbKbL"
    "bMbNbObObObObObPbQbRbSbTbUbUbVbWbWbWbWbXbYbZb[b\\b]b]b]b^b^b^b_c@cAcAcB"
    "cBcCcDcEcEcEcFcGcHcIcIcJcKcLcMcNcOcOcOcOcPcQcQcQcQcQcQcRcRcRcRcRcRcScT"
    "cTcUcUcVcVcVcVcVcWcWcWcXcXcXcXcXcYcYcYcZcZcZc[c\\c]c^c_c_d@d@d@dAdBdCdD"
    "dDdDdEdFdGdHdHdIdJdJdKdKdLdMdNdOdPdQdRdSdSdTdUdVdWdWdXdXdYdZd[d\\d]d^d_"
    "d_e@e@eAeAeBeCeCeDeDeEeEeEeFeGeHeIeJeKeLeLeMeNeNeNeOeOePePePePePePePeP"
    "eQeReSeTeUeUeUeVeWeWeXeXeXeXeXeXeYeZe[e\\e]e^e_e_e_f@fAfBfCfDfEfEfFfGfH"
    "fHfHfIfIfIfIfJfJfKfKfKfKfKfLfMfNfOfPfPfQfRfSfTfTfUfVfWfXfYfZf[f\\f\\f]f^"
    "f_g@gAgBgCgCgCgCgDgDgEgEgFgFgGgGgGgGgHgIgJgKgLgLgMgMgMgMgNgNgOgPgPgPgQ"
    "gQgQgQgQgQgQgQgRgSgSgSgTgTgTgTgUgUgVgWgWgWgXgXgYgYgZg[g[g\\g\\g\\g]g^g_h@"
    "hAhBhBhChDhDhDhDhDhEhFhFhFhFhFhFhGhHhIhJhKhLhMhNhOhOhOhPhQhRhShThUhVhW"
    "hXhYhZh[h[h[h\\h]h^h_i@iAiBiCiDiEiFiGiHiIiJiKiKiLiLiMiNiOiPiQiRiSiTiUiV"
    "iViViViWiXiYiZi[i\\i]i^i^i^i^i^i_i_i_i_i_i_i_j@j@j@j@j@jAjBjCjDjEjFjGjH"
    "jHjIjIjIjIjIjIjIjIjIjIjJjKjLjMjNjNjNjOjPjQjRjSjTjUjVjWjWjWjXjYjZj[j\\j]"
    "j^j_k@kAkBkCkDkEkFkGkGkHkIkJkKkLkMkNkOkPkQkRkSkTkTkTkUkVkVkVkVkVkWkXkY"
    "kZkZk[k[k\\k]k]k]k^k_l@lAlBlBlClClClDlDlElFlFlFlGlHlHlIlJlKlLlMlMlNlOlP"
    "lQlQlQlQlQlQlQlQlQlQlQlRlRlRlRlRlSlTlUlVlWlXlXlXlYlYlZl[l[l\\l]l^l_l_m@"
    "m@m@m@m@mAmAmAmBmBmCmCmDmEmEmFmGmHmImJmJmKmLmLmLmMmNmOmPmQmRmRmSmTmUmV"
    "mVmWmXmYmZm[m\\m]m^m_n@nAnAnBnBnCnDnDnDnDnDnEnFnGnGnHnHnInJnKnLnMnNnNnO"
    "nOnPnPnPnPnPnQnRnSnTnUnVnWnWnXnYnYnYnZn[n[n\\n]n^n_o@oAoBoBoCoCoCoDoDoD"
    "oEoEoEoEoEoFoGoHoHoIoJoJoKoKoLoMoNoNoNoNoNoNoOoOoOoOoOoPoPoPoPoPoPoQoQ"
    "oRoSoSoSoSoToUoVoWoWoXoXoYoZo[o\\o]o^o_p@p@p@p@p@p@pApApBpCpDpEpFpFpGpG"
    "pGpGpGpHpIpIpJpKpLpLpLpLpMpNpNpOpOpOpOpOpOpOpPpPpPpPpPpQpRpRpRpRpSpTpU"
    "pVpWpWpWpWpWpXpYpZp[p[p\\p\\p\\p\\p\\p\\p\\p\\p]p^p^p_p_q@q@qAqBqCqDqEqFqGqHqI"
    "qJqKqLqLqLqLqMqNqNqNqOqOqOqPqQqQqQqQqQqQqRqSqTqTqUqUqVqVqVqWqXqYqZq[q["
    "q\\q]q^q_r@rArBrBrBrCrCrDrDrDrDrDrErErErErErErFrGrGrHrIrIrJrJrKrLrMrMrM"
    "rMrMrMrNrNrNrNrNrNrOrOrOrOrOrOrPrPrQrQrQrQrQrQrRrSrTrUrVrWrWrXrYrYrYrZ"
    "r[r[r\\r\\r\\r]r]r]r^r^r_s@s@sAsAsAsBsBsBsCsDsDsEsFsGsHsIsJsKsLsMsNsOsPsQ"
    "sRsSsTsUsVsWsXsYsZsZs[s\\s\\s\\s\\s]s^s_s_s_s_s_s_s_s_s_t@tAtBtCtCtCtCtDtE"
    "tFtFtFtFtGtGtGtHtItItItItItJtJtJtJtJtJtJtJtJtJtJtJtKtLtLtLtLtLtLtLtLtL"
    "tLtLtLtMtNtOtPtPtPtQtRtStStStStTtUtVtWtWtXtYtZt[t\\t]t^t_u@u@u@uAuBuCuD"
    "uEuFuFuGuHuIuJuKuLuLuLuLuMuNuOuPuQuRuSuSuSuTuUuVuWuWuWuWuXuYuZu[u\\u]u^"
    "u^u_v@vAvBvCvDvDvEvFvGvHvIvJvKvKvLvMvNvOvPvQvRvRvRvSvTvTvUvVvWvWvXvYvZ"
    "vZvZvZvZv[v[v\\v]v^v_w@wAwAwBwCwDwEwFwFwGwHwIwJwJwJwJwKwLwMwMwMwMwMwMwN"
    "wNwOwOwOwOwOwOwPwQwRwRwRwRwRwSwTwUwVwWwWwWwXwYwZw[w\\w]w^w_w_w_x@x@xAxA"
    "xBxCxCxCxCxDxDxExFxFxFxGxHxIxJxKxLxLxLxLxMxMxNxOxPxQxQxRxSxSxTxTxTxTxT"
    "xTxTxUxUxUxUxUxVxWxXxYxZxZx[x\\x]x^x_y@yAyByCyDyEyFyFyGyGyHyIyJyJyKyLyM"
    "yMyMyNyNyNyOyOyPyQyQyQyQyQyQyQyQyQyQyRySyTyUyVyWyXyYyZy[y\\y]y^y_y_y_z@"
    "z@zAzBzBzBzBzCzCzCzDzEzFzGzGzHzIzIzJzJzKzLzMzMzMzMzMzMzMzMzMzNzNzNzNzN"
    "zNzNzOzOzPzPzQzRzSzTzTzTzUzVzWzXzYzYzYzZzZzZzZzZzZzZz[z[z[z[z\\z]z^z_{!"
    "{#{#{${%{&{'{'{({){*{+{,{-{.{/{0{1{2{3{3{4{5{5{5{5{5{6{7{7{7{7{7{7{7{8"
    "{9{9{9{9{:{;{<{={={={={={>{>{>{>{>{?{@{@{@{@{@{@{@{A{A{A{A{A{A{A{A{A{A"
    "{A{A{A{B{C{C{D{D{D{D{D{D{D{D{D{E{F{F{F{G{H{I{J{J{J{J{K{L{M{N{O{P{Q{R{S"
    "{T{U{V{W{X{Y{Z{Z{[{[{[{[{\\{]{]{]{]{]{]{^{_{`{a{b{c{d{d{e{f{g{g{h{h{h{h"
    "{h{i{i{j{j{j{j{k{l{m{n{n{n{o{p{p{p{q{q{r{r{r{r{r{r{r{r{r{s{t{u{v{w{x{x"
    "{y{z{z{{{{{|{|{|{|{|{|{|{}{}{}{}{}{~|!|!|!|#|#|#|$|%|&|'|'|(|(|)|*|+|,"
    "|-|.|/|0|1|1|1|2|3|3|4|5|6|7|7|7|7|7|7|7|8|9|:|:|;|<|=|>|?|?|@|@|A|B|B"
    "|B|C|C|D|E|F|F|F|F|G|G|G|H|I|J|K|L|L|M|N|N|N|N|N|N|N|O|O|O|O|P|P|Q|Q|R"
    "|R|R|R|S|S|S|S|S|S|S|T|T|U|U|U|U|U|U|V|V|V|V|W|W|X|Y|Z|Z|Z|[|\\|]|^|_|_"
    "|`|a|b|c|d|e|e|f|g|h|h|i|j|k|l|m|n|n|n|n|o|o|o|p|q|r|s|s|t|u|u|u|v|w|x"
    "|y|z|{|{|{|{|{|{|{|{|{|||}|~}!}#}$}$}%}%}%}%}%}&}&}&}&}&}'}(}(})})})})"
    "}*}*}*}*}+}+}+}+}+}+}+},},},},},}-}.}/}/}0}0}1}1}2}3}3}3}3}3}4}5}6}7}8"
    "}9}9}:};}<}=}>}?}?}@}A}B}C}D}E}F}G}H}H}H}H}H}H}I}I}I}J}K}L}M}N}N}N}O}O"
    "}P}P}Q}R}R}R}R}R}S}T}U}U}U}U}V}W}W}W}W}X}Y}Z}[}\\}\\}\\}]}]}]}]}]}^}^}^}^"
    "}^}_}`}a}a}b}b}c}c}d}e}e}e}e}e}e}e}e}f}f}f}f}f}f}g}h}i}j}j}j}k}l}m}n}o"
    "}p}q}r}s}t}u}v}v}w}x}y}z}{}|}}}}}~}~~!~#~$~$~%~&~&~'~(~(~)~)~*~+~,~-~."
    "~/~/~/~/~/~0~1~2~3~4~5~5~6~7~8~8~8~8~9~:~;~<~<~=~>~?~@~@~A~B~C~D~E~F~F"
    "~F~F~F~F~G~H~H~H~H~H~I~J~J~J~J~J~K~L~M~N~N~O~P~P~P~Q~R~R~R~S~S~S~S~S~T"
    "~T~T~U~V~V~V~V~W~W~W~W~W~W~X~Y~Z~[~[~[~\\~]~^~_~_~`~a~b~c~c~c~c~c~d~d~e"
    "~f~g~g~h~~"
};

/*
 * �b �e�i š�a�A �a�e �a��Ϣ š�a �A���i
 *
 * �� Գ �� Կ �� �� �� �� Դ �� �� �� Ժ �� Ի Լ �� �� �� Թ �� ��
 *  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
 */
byte GR[7][45] = {
    {212,196,212,179,212,218,212,191,212,217,212,192,212,195,212,194,212,180,
     212,193,212,197,212,205,212,186,212,201,212,187,212,188,212,200,212,204,
     212,203,212,185,212,202,212,206},
    {246,196,246,179,246,218,246,191,246,217,246,192,246,195,246,194,246,180,
     246,193,246,197,246,205,246,186,246,201,246,187,246,188,246,200,246,204,
     246,203,246,185,246,202,246,206},
    { 29, 29, 28, 32, 21, 29, 25, 32, 23, 32, 22, 29,  1, 29, 31, 29,  2, 32,
      30, 29,  5, 29, 29, 29, 28, 32, 21, 29, 25, 32, 23, 32, 22, 29,  1, 29,
      31, 29,  2, 32, 30, 29,  5, 29},
    {244,196,244,179,244,218,244,191,244,217,244,192,244,195,244,194,244,180,
     244,193,244,197,244,205,244,186,244,201,244,187,244,188,244,200,244,204,
     244,203,244,185,244,202,244,206},
    {196,196,179, 32,218,196,191, 32,217, 32,192,196,195,196,194,196,180, 32,
     193,196,197,196,205,205,186, 32,201,205,187, 32,188, 32,200,205,204,205,
     203,205,185, 32,202,205,206,205},
    {196,196,179, 32,218,196,191, 32,217, 32,192,196,195,196,194,196,180, 32,
     193,196,197,196,205,205,186, 32,201,205,187, 32,188, 32,200,205,204,205,
     203,205,185, 32,202,205,206,205},
    {166,161,166,162,166,163,166,164,166,165,166,166,166,167,166,168,166,169,
     166,170,166,171,166,172,166,173,166,174,166,175,166,176,166,177,166,178,
     166,179,166,180,166,181,166,182},
};

/* Comparing routine for binary search */
static int compare(const byte *p1, const byte *p2)
{
    if (*p1 != *p2) return (*p1 - *p2);
    else return (*(p1 + 1) - *(p2 + 1));
}

/*
 *  �q�� ���s�w š�a(0)�� 7���a �Ŭ��w š�a(1) �a���� �e��
 *
 *  ��) hgconv(0, 1, hg): �q�� ���s�w š�a�i 7���a �Ŭ��w š�a��
 */
static int hgconv(int s, int d, byte *hg)
{
    byte *p,*p1;
    int loc;

    p = bsearch(hg, fixedcode[s], 2350, 2, compare);
    if (p == NULL) return ERROR;

    if (s != 0) {         /* case of 7bit */
        do p1 = p, p -= 2;
        while (*(p1 + 1) == *(p + 1));
        p = p1;
    }

    loc = (int)(p - fixedcode[s]);
    *hg = fixedcode[d][loc];
    *(hg + 1) = fixedcode[d][loc + 1];

    return NOERROR;
}

/*
 *  ���s�w š�a�e�� �wѡ �e��
 *
 *  0: �q�� ���s�w    1: �q�� ���s�w
 *  2: �q�� ���s�w    3: Old KS ���s�w
 *  4: DKBII ���s�w
 *
 *  ��) comb2comb(0, 2, hg): �q�� ���s�w š�a�i �q�� ���s�w š�a��
 */
static int comb2comb(int s, int d, byte *hg)
{
    hangul ch;
    byte *p;

    p = (byte *)&ch;
    *(p + 1) = hg[0], *p = hg[1];
    ch.a = MM1[d][M1[s][ch.a]];
    ch.b = MM2[d][M2[s][ch.b]];
    ch.c = MM3[d][M3[s][ch.c]];
    hg[0] = *(p + 1), hg[1] = *p;

    return NOERROR;
}

/*
 *  �q�� ���s�w š�a(0)�a 7���a �Ŭ��w š�a(1)�i KSC5601 �Ŭ��w š�a�� �e��
 *
 *  ��) tocomplete(0, hg): �q�� ���s�w š�a�i KSC5601 �Ŭ��w š�a��
 *      tocomplete(1, hg): 7���a �Ŭ��w š�a�i KSC5601 �Ŭ��w š�a��
 */
int tocomplete(int s, byte *hg)
{
    bool iskss, ishanja;
    byte *p,*p1;
    int loc, c2, ksspos, hanjapos;

    if (hg[0] >= 0xd9 && hg[0] <= 0xde) {
        iskss = true;
        c2 = hg[1];
        if ((c2 -= 0x31) < 0) iskss = false;
        else if (c2 <= 0x4d) ;
        else if ((c2 -= 0x12) < 0) iskss = false;
        else if (c2 <= 0xbb) ;
        else iskss = false;
        if (!iskss) return ERROR;
        ksspos = (hg[0] - 0xd9) * 94 * 2 + c2;

        hg[0] = 0xa1 + ksspos / 94;
        hg[1] = 0xa1 + ksspos % 94;

        return NOERROR;
    } else if (hg[0] >= 0xe0 && hg[0] <= 0xf9) {
        ishanja = true;
        c2 = hg[1];
        if ((c2 -= 0x31) < 0) ishanja = false;
        else if (c2 <= 0x4d) ;
        else if ((c2 -= 0x12) < 0) ishanja = false;
        else if (c2 <= 0xbb) ;
        else ishanja = false;
        if (!ishanja) return ERROR;
        hanjapos = (hg[0] - 0xe0) * 94 * 2 + c2;

        hg[0] = 0xca + hanjapos / 94;
        hg[1] = 0xa1 + hanjapos % 94;

        return NOERROR;
    }

    p = bsearch(hg, fixedcode[s], 2350, 2, compare);
    if (p == NULL) return ERROR;

    if (s != 0) {
        do p1 = p, p -= 2;
        while (*(p1 + 1) == *(p + 1));
        p = p1;
    }

    loc = (int)(p - fixedcode[s]) / 2;
    *hg = (loc / 94) + 0xb0;
    *(hg + 1)= (loc % 94) + 0xa1;

    return NOERROR;
}

/*
 *  KSC5601 �Ŭ��w š�a�i �q�� ���s�w š�a(0)�a 7���a �Ŭ��w š�a(1)�� �e��
 *
 *  ��) tocombi(0, hg): KSC5601 �Ŭ��w š�a�i �q�� ���s�w š�a��
 */
int tocombi(int d, byte *hg)
{
    bool iskss, ishanja;
    byte *p;
    int loc, c2, ksspos, hanjapos;

    if (hg[0] >= 0xa1 && hg[0] <= 0xac) {
        iskss = true;
        c2 = hg[1];
        if ((c2 -= 0xa1) < 0) iskss = false;
        else if (c2 >= 0x5e) iskss = false;

        if (!iskss) return ERROR;
        ksspos = (hg[0] - 0xa1) * 94 + c2;

        hg[0] = 0xd9 + ksspos / 94 / 2;
        hg[1] = 0x31 + ksspos % (94 * 2);
        if (hg[1] > 0x7e) hg[1] += 0x12;

        return NOERROR;
    } else if (hg[0] >= 0xca && hg[0] <= 0xfd) {
        ishanja = true;
        c2 = hg[1];
        if ((c2 -= 0xa1) < 0) ishanja = false;
        else if (c2 >= 0x5e) ishanja = false;

        if (!ishanja) return ERROR;
        hanjapos = (hg[0] - 0xca) * 94 + c2;

        hg[0] = 0xe0 + hanjapos / 94 / 2;
        hg[1] = 0x31 + hanjapos % (94 * 2);
        if (hg[1] > 0x7e) hg[1] += 0x12;

        return NOERROR;
    }

    loc = (*hg - 176) * 94;
    loc += (*(hg + 1) - 161);

    p = fixedcode[d] + loc * 2;
    *hg = *p;
    *(hg + 1) = *(p + 1);

    return NOERROR;
}

/*
 *  7�a�� �e�i š�a�e��  �wѡ �e��
 *
 *  0 : �q�� ���s�w    1 : �q�� ���s�w
 *  2 : �q�� ���s�w    3 : Old KS ���s�w
 *  4 : DKBII ���s�w   5 : KSC5601 �Ŭ��w
 *  6 : 7���a �Ŭ��w
 *
 *  ��) htrans(5, 0, hg): KSC5601 �Ŭ��w š�a�i �q�� ���s�w š�a��
 *      htrans(0, 5, hg): �q�� ���s�w š�a�i KSC5601 �Ŭ��w š�a��
 */
int htrans(byte s, byte d, byte *hg)
{
    int xcode;

    if (s == d)         /* š�a�a �{�a�e �e���i ϩ�a ���a */
      return NOERROR;
    if (s < 5 && d < 5) /* ���s�w ���� �wѡ �e�� */
      return comb2comb(s, d, hg);

    switch (s) {
      case 1 :
      case 2 :
        comb2comb(s, 1, hg);
      case 0 :
        if(d == 6)
          return hgconv(0, 1, hg);
        return tocomplete(0, hg);
      case 6 :
        if(d == 5)
          return tocomplete(1, hg);
        if (hgconv(1, 0, hg) != 0)
          return ERROR;
        if (d > 0)
          comb2comb(1, d, hg);
        break;
      case 5 :
        if (d == 6)
          return tocombi(1, hg);
        xcode = tocombi(0, hg);
        if (d > 0)
          comb2comb(1, d, hg);
        return xcode;
    }

    return NOERROR;
}
