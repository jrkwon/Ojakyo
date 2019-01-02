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

/* ¹¡ÐsÑw Å¡—a· ¬wÑ¡ ¥eÑÅµA ¬a¶w–A“e Ðe‹i ·q­¡ ¬‚·¥ */

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

/* KSC5601‰Á 7§¡Ëa µÅ¬÷Ñw Å¡—aŸi ¶áÐe Å¡—aÎa */

byte *fixedcode[2] = {
    "ˆaˆbˆeˆhˆiˆjˆkˆqˆsˆtˆuˆvˆwˆxˆyˆ{ˆ|ˆ}ˆˆ‚ˆ…ˆ‰ˆ‘ˆ“ˆ•ˆ–ˆ—ˆ¡ˆ¢ˆ¥ˆ©ˆµˆ·ˆÁˆÅ"
    "ˆÉˆáˆâˆåˆèˆéˆëˆñˆóˆõˆöˆ÷ˆøˆûˆüˆý‰A‰E‰I‰Q‰S‰U‰V‰W‰a‰b‰c‰e‰h‰i‰q‰s‰u‰v‰w"
    "‰{‰‰…‰‰‰“‰•‰¡‰¢‰¥‰¨‰©‰«‰­‰°‰±‰³‰µ‰·‰¸‰Á‰Â‰Å‰É‰Ë‰Ñ‰Ó‰Õ‰×‰á‰å‰é‰ñ‰ö‰÷ŠA"
    "ŠBŠEŠIŠQŠSŠUŠWŠaŠeŠiŠsŠuŠŠ‚Š…ŠˆŠ‰ŠŠŠ‹ŠŠ‘Š“Š•Š—Š˜Š¡Š¢Š¥Š©Š¶Š·ŠÁŠÕŠáŠâ"
    "ŠåŠéŠñŠóŠõ‹A‹E‹I‹a‹b‹e‹h‹i‹j‹q‹s‹u‹w‹‹¡‹¢‹¥‹¨‹©‹«‹±‹³‹µ‹·‹¸‹¼ŒaŒbŒcŒe"
    "ŒiŒkŒqŒsŒuŒvŒwŒ{ŒŒ‚Œ…Œ‰Œ‘Œ“Œ•Œ–Œ—Œ¡Œ¢Œ©ŒáŒâŒãŒåŒéŒñŒóŒõŒöŒ÷ABEQU"
    "Waeiuv{¡¢¥§©±³µ·¸¹ÁÂÉÖ×áâ÷ŽAŽEŽIŽQŽSŽWŽaŽ"
    "Ž‚Ž…Ž‰ŽŽ‘Ž“Ž•Ž—Ž˜Ž¡Ž©Ž¶Ž·ŽÁŽÂŽÅŽÉŽÑŽÓŽÖŽáŽåŽéŽñŽóAabegikpqs"
    "uw{¡¢¥©±³µ·abcehijkqsuvwxy{}‚…‰‘“•"
    "–—¡¢¥©±·áâäåéëìñóõö÷ý‘A‘B‘E‘I‘Q‘S‘U‘V‘W‘a‘b‘e‘i‘q"
    "‘s‘v‘w‘z‘‘…‘¡‘¢‘¥‘©‘«‘±‘³‘µ‘·‘¼‘½‘Á‘Å‘É‘Ö’A’E’I’Q’S’U’a’b’e’i’s’u’w’"
    "’‚’…’ˆ’‰’‘’“’•’—’¡’¶’Á’á’å’é’ñ’ó“A“B“I“Q“S“W“a“b“e“i“j“k“q“s“u“w“x“|“"
    "“…“‰“¡“¢“¥“©“¯“±“³“µ“·“¼”a”b”c”e”h”i”j”k”l”p”q”s”u”v”w”x”y”}””‚”…”‰”‘"
    "”“”•”–”—”¡”á”â”ã”å”è”é”ë”ì”ñ”ó”õ”÷”ù”ü•A•B•E•I•Q•S•U•V•W•a•e•i•v•w••…"
    "•¡•¢•¥•¨•©•«•­•±•³•µ•·•¹•»•Á•Å•É•á•ö–A–E–I–Q–S–U–a––‚–…–‰–‘–“–•–—–¡–¶"
    "–Á–×–á–å–é–ó–õ–÷—A—E—I—Q—W—a—b—e—h—i—k—q—s—u—w——¡—¢—¥—¨—©—±—³—µ—¶—·—¸"
    "˜a˜b˜e˜i˜q˜s˜u˜v˜w˜}˜˜‚˜…˜‰˜‘˜“˜•˜–˜—˜á˜â˜å˜é˜ë˜ì˜ñ˜ó˜õ˜ö˜÷˜ý™A™B™E™I"
    "™Q™S™U™V™W™a™v™¡™¢™¥™©™·™Á™É™ášAšEšš‚š…š‰šš‘š—šÁšášåšéšñšóš÷›a›b›e›h"
    "›i›q›s›u››…›‰›‘›“›¡›¥›©›±›³›µ›·œaœbœeœiœqœsœuœvœwœxœ|œ}œœ‚œ…œ‰œ‘œ“œ•"
    "œ–œ—œ¡œ¢œ¥œµœ·œáœâœåœéœñœóœõœöœ÷œýABEIQSUWabeiqsuvw"
    "…“•¡¢¥©±³µ·ÁÅ×öžAžEžIžQžSžUžWžažežižsžužwžž‚ž…ž‰ž‘ž“ž•"
    "ž—ž¡ž¶žÁžážâžåžéžñžõž÷ŸAŸBŸEŸIŸQŸSŸUŸWŸaŸbŸeŸiŸqŸsŸuŸwŸxŸ{Ÿ|Ÿ¡Ÿ¢Ÿ¥Ÿ©Ÿ±"
    "Ÿ³ŸµŸ· a b e g h i j k q s u w x { }  ‚ … ‰ ‘ “ • – — ˜ ¡ ¢ © · á â å"
    " é ë ñ ó õ ÷ ø ý¡A¡B¡E¡I¡Q¡S¡U¡V¡W¡a¡b¡e¡i¡u¡v¡w¡y¡¡¡¡¢¡¤¡¥¡©¡«¡±¡³¡µ"
    "¡·¡Á¡Å¡Ö¡×¢A¢E¢I¢S¢U¢W¢a¢e¢i¢s¢u¢¢‚¢ƒ¢…¢ˆ¢‰¢Š¢‹¢‘¢“¢•¢—¢›¢¢¡¢¥¢©¢³¢µ"
    "¢Á¢á¢å¢é£A£E£I£Q£U£a£e£i£q£u£¡£¢£¥£¨£©£«£±£³£µ£¶£·£¹£»¤a¤b¤c¤d¤e¤h¤i¤j"
    "¤k¤l¤q¤s¤u¤w¤{¤¤‚¤…¤‰¤‘¤“¤•¤–¤—¤›¤¡¤¢¤¥¤³¤á¤â¤å¤è¤é¤ë¤ñ¤ó¤õ¤÷¤ø¥A¥B¥E"
    "¥H¥I¥Q¥S¥U¥V¥W¥a¥b¥e¥i¥s¥u¥v¥w¥{¥¥…¥¡¥¢¥£¥¥¥©¥±¥³¥µ¥·¥Á¥Å¥Ö¥á¥ö¦A¦B¦E"
    "¦I¦Q¦S¦a¦e¦¦‚¦…¦ˆ¦‰¦Š¦‹¦‘¦“¦•¦—¦›¦œ¦¡¦©¦¶¦Á¦á¦â¦å¦é¦÷§A§E§I§Q§U§W§a§b"
    "§e§i§q§s§u§¡§¢§¥§©§«§±§³§µ§·§¸§¹¨a¨b¨e¨i¨k¨q¨s¨u¨v¨w¨}¨¨‚¨…¨‰¨‘¨“¨•¨–"
    "¨—¨¡¨¢¨±¨á¨â¨å¨è¨é¨ñ¨õ¨ö¨÷©A©W©a©b©q©s©u©v©w©¡©¢©¥©©©±©³©·ªAªaªwªª‚ª…"
    "ª‰ª‘ª•ª—«A«W«a«e«i«q«s«¡«¢«¥«©«±«³«µ«·¬a¬b¬d¬e¬h¬i¬j¬k¬q¬s¬u¬v¬w¬{¬¬‚"
    "¬…¬‰¬‘¬“¬•¬–¬—¬¡¬¢¬¥¬©¬±¬³¬µ¬·¬Á¬Å¬É¬Ñ¬×¬á¬â¬ã¬ä¬å¬è¬é¬ë¬ì¬ñ¬ó¬õ¬ö¬÷¬ü"
    "­A­B­E­I­Q­S­U­V­W­a­b­e­i­q­s­u­v­w­­…­‰­—­¡­¢­£­¥­©­«­±­³­µ­·­»­Á­Â"
    "­Å­É­×­á­å­é­ñ­õ­ö®A®E®I®Q®S®U®a®b®e®i®q®s®u®w®®‚®…®ˆ®‰®‘®“®•®—®™®›®œ"
    "®¡®¶®Á®Â®Å®É®Ñ®×®á®â®å®é®ñ®ó®õ®÷¯A¯B¯I¯Q¯U¯W¯a¯b¯e¯i¯j¯q¯s¯u¯w¯¡¯¢¯¥¯¨"
    "¯©¯°¯±¯³¯µ¯·¯¼°a°b°d°e°i°q°s°v°w°}°°‚°…°‰°‘°“°–°—°·°á°â°å°é°ë°ñ°ó°ö°÷"
    "±A±E±I±W±¡±¢±¥±¨±©±«±±±³±·±Á±Â±Å±Ö±á±ö²A²E²I²Q²S²a²²‚²…²‰²‘²“²—²¡²¶²Á"
    "²á²å³W³a³b³e³i³k³p³q³s³³…³‰³‘³¡³¢³¥³©³±³³³µ³·´a´b´e´f´g´i´j´k´p´q´s´u"
    "´v´w´{´|´´‚´…´‰´‘´“´•´–´—´¡´¢´¥´©´¬´±´³´µ´·´»´½´Á´Å´É´Ó´á´â´å´æ´è´é´ê"
    "´ë´ñ´ó´ô´õ´ö´÷´ø´ú´üµAµBµEµIµQµSµUµWµaµbµcµeµiµkµlµqµsµtµuµvµwµ{µ|µ}µ"
    "µ…µ‰µ‘µ“µ•µ–µ¡µ¢µ¥µ©µªµ«µ­µ°µ±µ³µµµ·µ¹µÁµÂµÅµÉµÑµÓµÕµÖµ×µáµâµåµñµõµ÷¶A"
    "¶B¶E¶I¶Q¶S¶U¶W¶a¶b¶e¶i¶q¶s¶u¶w¶¶‚¶…¶‰¶Š¶‹¶‘¶“¶•¶—¶¡¶¢¶¥¶©¶±¶³¶¶¶·¶Á¶Â"
    "¶Å¶É¶Ñ¶Ó¶×¶á¶â¶å¶é¶ñ¶ó¶õ¶÷·A·B·E·I·Q·S·U·W·Y·a·b·e·i·o·q·s·u·w·x·y·z·{"
    "·|·}··…·‰·‘·•·¡·¢·¥·©·ª·«·°·±·³·µ·¶···¸·¼¸a¸b¸e¸g¸h¸i¸k¸q¸s¸u¸v¸w¸x¸"
    "¸‚¸…¸‰¸‘¸“¸•¸–¸—¸¡¸¢¸¥¸§¸©¸±¸·¸Á¸Å¸É¸á¸â¸å¸é¸ë¸ñ¸ó¸õ¸÷¸ø¹A¹B¹E¹I¹Q¹S¹U"
    "¹W¹a¹e¹i¹q¹s¹v¹w¹¹¡¹¢¹¥¹©¹«¹±¹³¹µ¹·¹¸¹¹¹½¹Á¹Â¹É¹Ó¹Õ¹×¹á¹ö¹÷ºAºEºIºQºS"
    "ºUºWºaºbºeºwºº‚º…º‰ºŠº‹º‘º“º•º—º¡º¶ºÁºáºâºåºéºñºóºõ»A»E»I»Q»a»b»e»i»q"
    "»s»u»w»¡»¢»¥»¨»©»«»±»³»µ»·»¸»»»¼¼a¼b¼e¼g¼i¼l¼q¼s¼u¼v¼w¼¼‚¼…¼‰¼‘¼“¼•¼–"
    "¼—¼¡¼¥¼·¼á¼â¼å¼é¼ñ¼ó¼õ¼ö¼÷½A½W½a½v½¡½¢½¥½©½±½³½µ½·½¹½Á½Â½É½Ö½á½ö¾A¾E¾I"
    "¾Q¾S¾w¾¾‚¾…¾‰¾‘¾“¾—¾¡¾¶¾·¾á¿A¿a¿q¿u¿w¿¡¿¢¿¥¿©¿±¿³¿·¿¸¿½ÀaÀbÀeÀgÀiÀqÀs"
    "ÀuÀvÀwÀxÀÀ‚À…À‰À‘À“À•À–À—À¡À¥À§À©À±À·ÀáÀâÀåÀéÀñÀóÀõÀöÀ÷ÁAÁBÁEÁIÁQÁSÁU"
    "ÁWÁaÁeÁvÁÁ…Á—Á¡Á¢Á¥Á©Á±Á³ÁµÁ·ÁÁÁÅÁÉÁ×ÂAÂEÂIÂQÂSÂUÂWÂaÂqÂÂ‚Â…Â‰Â‘Â“Â•"
    "Â—Â¡Â¶ÂÁÂÅÂáÂåÂéÂñÂóÂõÂ÷ÃAÃEÃIÃQÃWÃaÃbÃeÃiÃqÃsÃuÃwÃ¡Ã¢Ã¥Ã¨Ã©ÃªÃ±Ã³ÃµÃ·"
    "ÄaÄbÄeÄiÄqÄsÄuÄwÄÄ‚Ä…Ä‰Ä‘Ä“Ä•Ä–Ä—Ä¡Ä¢Ä·ÄáÄâÄåÄèÄéÄñÄóÄõÄöÄ÷ÅAÅBÅEÅIÅQ"
    "ÅSÅUÅWÅaÅeÅiÅqÅsÅuÅvÅwÅÅ¡Å¢Å¥Å©Å±Å³ÅµÅ·ÅÁÅÂÅÅÅÉÅÑÅ×ÅáÅ÷ÆAÆIÆaÆÆ‚Æ…Æ‰"
    "Æ‘Æ“Æ•Æ—Æ¡Æ¥Æ©Æ·ÆÁÆ×ÆáÆâÆåÆéÆñÆóÆõÆ÷ÇAÇEÇIÇQÇaÇbÇeÇiÇqÇsÇwÇ¡Ç¢Ç¥Ç©Ç±Ç³"
    "ÇµÇ·ÈaÈbÈeÈiÈjÈqÈsÈuÈvÈwÈÈ‚È…È‰È‘È“È•È–È—È¡È·ÈáÈâÈåÈéÈëÈñÈóÈõÈöÈ÷ÉAÉB"
    "ÉEÉIÉQÉSÉUÉWÉaÉeÉvÉÉ…É¡É¢É¥É©É±É³ÉµÉ·É¼ÉÁÉÅÉáÊAÊEÊUÊWÊaÊÊ‚Ê…Ê‰Ê‘Ê“Ê•"
    "Ê—Ê¡Ê¶ÊÁÊáÊâÊåÊéÊñÊóÊ÷ËAËEËIËQËWËaËbËeËhËiËkËqËsËuËË…Ë‰Ë‘Ë“Ë¡Ë¢Ë¥Ë©Ë±"
    "Ë³ËµË·ÌaÌbÌcÌeÌiÌkÌqÌsÌuÌvÌwÌ{ÌÌ‚Ì…Ì‰Ì‘Ì“Ì•Ì–Ì—Ì¡Ì¢ÌáÌâÌåÌéÌñÌóÌõÌöÌ÷"
    "ÍAÍBÍEÍIÍQÍSÍUÍWÍaÍeÍiÍqÍsÍvÍwÍÍ‰Í“Í•Í¡Í¢Í¥Í©Í±Í³ÍµÍ·ÍÁÍ×ÎAÎEÎaÎeÎiÎs"
    "ÎuÎÎ‚Î…ÎˆÎ‰Î‹Î‘Î“Î•Î—Î¡Î·ÎáÎåÎéÎñÎõÏAÏEÏIÏQÏUÏWÏaÏeÏiÏqÏsÏuÏ¡Ï¢Ï¥Ï©Ï±"
    "Ï³ÏµÏ·ÐaÐbÐeÐiÐnÐqÐsÐuÐwÐÐ‚Ð…Ð‰Ð‘Ð“Ð•Ð–Ð—Ð¡Ð·ÐáÐâÐåÐéÐëÐñÐóÐõÐ÷ÑAÑBÑE"
    "ÑIÑQÑSÑUÑWÑaÑbÑeÑiÑqÑsÑuÑvÑwÑÑ…Ñ‰Ñ“Ñ¡Ñ¢Ñ¥Ñ©Ñ®Ñ±Ñ³ÑµÑ·Ñ»ÑÁÑÂÑÅÑÉÑÕÑ×Ñá"
    "ÑâÑåÑõÑ÷ÒAÒBÒEÒIÒSÒUÒWÒaÒeÒiÒsÒuÒÒ‚Ò…Ò‰ÒŽÒ‘Ò•Ò—Ò¡Ò¥Ò©Ò±Ò·ÒÁÒÂÒÅÒÉÒ×Òá"
    "ÒâÒåÒéÒñÒóÒõÒ÷ÓAÓBÓEÓIÓQÓUÓWÓaÓbÓeÓgÓhÓiÓjÓqÓsÓuÓwÓ{ÓÓ…Ó‰Ó‘Ó“Ó—Ó¡Ó¢Ó¥"
    "Ó©Ó±Ó³ÓµÓ·",
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
 * ˆb Ðe‹i Å¡—aµA ˜aŸe ‹aœÏ¢ Å¡—a ÉA·¡§i
 *
 * ÔÄ Ô³ ÔÚ Ô¿ ÔÙ ÔÀ ÔÃ ÔÂ Ô´ ÔÁ ÔÅ ÔÍ Ôº ÔÉ Ô» Ô¼ ÔÈ ÔÌ ÔË Ô¹ ÔÊ ÔÎ
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
 *  ¬q¥¡ ¹¡ÐsÑw Å¡—a(0)µÁ 7§¡Ëa µÅ¬÷Ñw Å¡—a(1) ¬a·¡· ¥eÑÅ
 *
 *  µ) hgconv(0, 1, hg): ¬q¥¡ ¹¡ÐsÑw Å¡—aŸi 7§¡Ëa µÅ¬÷Ñw Å¡—a¡
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
 *  ¹¡ÐsÑw Å¡—aˆe· ¬wÑ¡ ¥eÑÅ
 *
 *  0: ¬q¥¡ ¹¡ÐsÑw    1: ¬q¬÷ ¹¡ÐsÑw
 *  2: ‹q¬÷ ¹¡ÐsÑw    3: Old KS ¹¡ÐsÑw
 *  4: DKBII ¹¡ÐsÑw
 *
 *  µ) comb2comb(0, 2, hg): ¬q¥¡ ¹¡ÐsÑw Å¡—a·i ‹q¬÷ ¹¡ÐsÑw Å¡—a¡
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
 *  ¬q¥¡ ¹¡ÐsÑw Å¡—a(0)a 7§¡Ëa µÅ¬÷Ñw Å¡—a(1)Ÿi KSC5601 µÅ¬÷Ñw Å¡—a¡ ¥eÑÅ
 *
 *  µ) tocomplete(0, hg): ¬q¥¡ ¹¡ÐsÑw Å¡—aŸi KSC5601 µÅ¬÷Ñw Å¡—a¡
 *      tocomplete(1, hg): 7§¡Ëa µÅ¬÷Ñw Å¡—aŸi KSC5601 µÅ¬÷Ñw Å¡—a¡
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
 *  KSC5601 µÅ¬÷Ñw Å¡—aŸi ¬q¥¡ ¹¡ÐsÑw Å¡—a(0)a 7§¡Ëa µÅ¬÷Ñw Å¡—a(1)¡ ¥eÑÅ
 *
 *  µ) tocombi(0, hg): KSC5601 µÅ¬÷Ñw Å¡—aŸi ¬q¥¡ ¹¡ÐsÑw Å¡—a¡
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
 *  7ˆa»¡ Ðe‹i Å¡—aˆe·  ¬wÑ¡ ¥eÑÅ
 *
 *  0 : ¬q¥¡ ¹¡ÐsÑw    1 : ¬q¬÷ ¹¡ÐsÑw
 *  2 : ‹q¬÷ ¹¡ÐsÑw    3 : Old KS ¹¡ÐsÑw
 *  4 : DKBII ¹¡ÐsÑw   5 : KSC5601 µÅ¬÷Ñw
 *  6 : 7§¡Ëa µÅ¬÷Ñw
 *
 *  µ) htrans(5, 0, hg): KSC5601 µÅ¬÷Ñw Å¡—aŸi ¬q¥¡ ¹¡ÐsÑw Å¡—a¡
 *      htrans(0, 5, hg): ¬q¥¡ ¹¡ÐsÑw Å¡—aŸi KSC5601 µÅ¬÷Ñw Å¡—a¡
 */
int htrans(byte s, byte d, byte *hg)
{
    int xcode;

    if (s == d)         /* Å¡—aˆa ˆ{·a¡e ¥eÑÅÐi Ï©¶a ´ô”a */
      return NOERROR;
    if (s < 5 && d < 5) /* ¹¡ÐsÑw ¡Ÿ¡ ¬wÑ¡ ¥eÑÅ */
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