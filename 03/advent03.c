#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include <orcania.h>
#include <yder.h>

#include "../advent.h"

#define PROGNAME "advent03"

// add this as code generation step as an alternate solution to part 1
//grep -o -E 'mul\([0-9]***,[0-9]***\)' advent03.txt

int mul(int x, int y)
{
    return(x * y);
}


int main(int argc, char** argv) {

    clock_t start_time = clock();

    Parameters* p = malloc(sizeof(Parameters));
    ConfigError ppe = getParameters(argc, argv, p);

    if(p->verbosity_count>0)
    {
	    y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Initializing logs mode: file, logs level: debug");
    }
    else
    {
	    y_init_logs(PROGNAME, Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_INFO, NULL, "Initializing logs mode: file, logs level: info");
    }

    int a = 0;

/*** sample **/
//a = a + mul(2,4);
//a = a + mul(5,5);
//a = a + mul(11,8);
//a = a + mul(8,5);

/*
a = a + mul(514,727);
a = a + mul(550,305);
a = a + mul(94,564);
a = a + mul(260,379);
a = a + mul(790,810);
a = a + mul(557,683);
a = a + mul(220,10);
a = a + mul(654,746);
a = a + mul(89,191);
a = a + mul(302,490);
a = a + mul(335,535);
a = a + mul(241,166);
a = a + mul(758,530);
a = a + mul(938,70);
a = a + mul(412,287);
a = a + mul(230,620);
a = a + mul(410,577);
a = a + mul(720,516);
a = a + mul(373,78);
a = a + mul(793,973);
a = a + mul(85,246);
a = a + mul(396,22);
a = a + mul(515,670);
a = a + mul(38,415);
a = a + mul(200,147);
a = a + mul(328,235);
a = a + mul(571,33);
a = a + mul(679,122);
a = a + mul(440,923);
a = a + mul(971,274);
a = a + mul(833,181);
a = a + mul(468,401);
a = a + mul(446,956);
a = a + mul(391,995);
a = a + mul(284,629);
a = a + mul(922,806);
a = a + mul(183,352);
a = a + mul(547,62);
a = a + mul(753,602);
a = a + mul(956,732);
a = a + mul(481,556);
a = a + mul(905,420);
a = a + mul(327,771);
a = a + mul(45,757);
a = a + mul(366,653);
a = a + mul(807,855);
a = a + mul(48,816);
a = a + mul(370,665);
a = a + mul(155,426);
a = a + mul(132,914);
a = a + mul(296,176);
a = a + mul(361,479);
a = a + mul(506,495);
a = a + mul(481,87);
a = a + mul(541,563);
a = a + mul(495,427);
a = a + mul(640,499);
a = a + mul(967,918);
a = a + mul(505,225);
a = a + mul(90,482);
a = a + mul(620,841);
a = a + mul(719,850);
a = a + mul(931,185);
a = a + mul(39,103);
a = a + mul(687,103);
a = a + mul(282,494);
a = a + mul(342,554);
a = a + mul(407,74);
a = a + mul(324,781);
a = a + mul(90,925);
a = a + mul(828,16);
a = a + mul(438,549);
a = a + mul(91,548);
a = a + mul(835,662);
a = a + mul(489,462);
a = a + mul(53,461);
a = a + mul(273,777);
a = a + mul(119,879);
a = a + mul(585,949);
a = a + mul(22,105);
a = a + mul(439,876);
a = a + mul(111,687);
a = a + mul(432,628);
a = a + mul(287,508);
a = a + mul(111,655);
a = a + mul(518,391);
a = a + mul(301,138);
a = a + mul(654,521);
a = a + mul(910,877);
a = a + mul(123,641);
a = a + mul(488,741);
a = a + mul(301,649);
a = a + mul(259,148);
a = a + mul(83,94);
a = a + mul(232,572);
a = a + mul(889,281);
a = a + mul(256,607);
a = a + mul(382,953);
a = a + mul(433,147);
a = a + mul(197,749);
a = a + mul(935,21);
a = a + mul(299,881);
a = a + mul(264,731);
a = a + mul(713,161);
a = a + mul(360,529);
a = a + mul(971,836);
a = a + mul(567,429);
a = a + mul(522,696);
a = a + mul(80,121);
a = a + mul(619,728);
a = a + mul(420,324);
a = a + mul(144,181);
a = a + mul(261,691);
a = a + mul(189,450);
a = a + mul(533,22);
a = a + mul(231,586);
a = a + mul(107,724);
a = a + mul(691,859);
a = a + mul(726,544);
a = a + mul(316,707);
a = a + mul(798,459);
a = a + mul(612,148);
a = a + mul(634,978);
a = a + mul(477,947);
a = a + mul(828,259);
a = a + mul(595,267);
a = a + mul(351,552);
a = a + mul(67,280);
a = a + mul(586,844);
a = a + mul(521,525);
a = a + mul(379,96);
a = a + mul(478,481);
a = a + mul(123,281);
a = a + mul(249,626);
a = a + mul(190,620);
a = a + mul(21,142);
a = a + mul(117,186);
a = a + mul(940,708);
a = a + mul(960,867);
a = a + mul(135,71);
a = a + mul(79,533);
a = a + mul(886,320);
a = a + mul(376,296);
a = a + mul(791,363);
a = a + mul(133,626);
a = a + mul(474,459);
a = a + mul(311,372);
a = a + mul(243,118);
a = a + mul(302,760);
a = a + mul(145,293);
a = a + mul(259,51);
a = a + mul(99,991);
a = a + mul(137,230);
a = a + mul(226,287);
a = a + mul(590,394);
a = a + mul(474,995);
a = a + mul(309,511);
a = a + mul(553,164);
a = a + mul(618,347);
a = a + mul(210,454);
a = a + mul(297,766);
a = a + mul(961,326);
a = a + mul(340,326);
a = a + mul(329,543);
a = a + mul(28,451);
a = a + mul(428,233);
a = a + mul(710,863);
a = a + mul(944,973);
a = a + mul(582,87);
a = a + mul(569,58);
a = a + mul(746,840);
a = a + mul(74,146);
a = a + mul(517,818);
a = a + mul(22,727);
a = a + mul(226,816);
a = a + mul(247,12);
a = a + mul(620,264);
a = a + mul(586,607);
a = a + mul(684,722);
a = a + mul(11,63);
a = a + mul(662,331);
a = a + mul(631,2);
a = a + mul(987,288);
a = a + mul(261,47);
a = a + mul(650,139);
a = a + mul(561,710);
a = a + mul(788,270);
a = a + mul(151,849);
a = a + mul(531,530);
a = a + mul(99,868);
a = a + mul(119,337);
a = a + mul(250,122);
a = a + mul(708,536);
a = a + mul(480,332);
a = a + mul(891,459);
a = a + mul(852,128);
a = a + mul(418,844);
a = a + mul(69,312);
a = a + mul(91,636);
a = a + mul(894,19);
a = a + mul(116,57);
a = a + mul(651,74);
a = a + mul(169,494);
a = a + mul(44,491);
a = a + mul(29,368);
a = a + mul(961,385);
a = a + mul(586,30);
a = a + mul(378,568);
a = a + mul(375,803);
a = a + mul(21,508);
a = a + mul(921,355);
a = a + mul(980,691);
a = a + mul(200,735);
a = a + mul(212,991);
a = a + mul(751,323);
a = a + mul(102,317);
a = a + mul(51,80);
a = a + mul(454,897);
a = a + mul(793,439);
a = a + mul(982,538);
a = a + mul(386,116);
a = a + mul(373,106);
a = a + mul(59,223);
a = a + mul(233,653);
a = a + mul(547,404);
a = a + mul(150,196);
a = a + mul(514,824);
a = a + mul(332,418);
a = a + mul(590,783);
a = a + mul(55,422);
a = a + mul(436,985);
a = a + mul(675,976);
a = a + mul(172,297);
a = a + mul(866,305);
a = a + mul(938,509);
a = a + mul(100,651);
a = a + mul(163,66);
a = a + mul(217,127);
a = a + mul(39,897);
a = a + mul(966,889);
a = a + mul(488,570);
a = a + mul(878,77);
a = a + mul(670,359);
a = a + mul(56,569);
a = a + mul(614,976);
a = a + mul(852,588);
a = a + mul(532,868);
a = a + mul(603,823);
a = a + mul(517,713);
a = a + mul(338,824);
a = a + mul(230,684);
a = a + mul(288,730);
a = a + mul(688,399);
a = a + mul(968,380);
a = a + mul(433,704);
a = a + mul(848,947);
a = a + mul(590,692);
a = a + mul(102,487);
a = a + mul(406,710);
a = a + mul(962,153);
a = a + mul(419,854);
a = a + mul(201,493);
a = a + mul(779,883);
a = a + mul(966,261);
a = a + mul(513,694);
a = a + mul(657,498);
a = a + mul(310,762);
a = a + mul(320,448);
a = a + mul(886,159);
a = a + mul(912,558);
a = a + mul(614,536);
a = a + mul(224,83);
a = a + mul(266,718);
a = a + mul(939,819);
a = a + mul(24,251);
a = a + mul(86,947);
a = a + mul(694,25);
a = a + mul(285,650);
a = a + mul(95,593);
a = a + mul(931,886);
a = a + mul(110,763);
a = a + mul(784,109);
a = a + mul(354,211);
a = a + mul(637,881);
a = a + mul(947,709);
a = a + mul(284,267);
a = a + mul(259,860);
a = a + mul(462,151);
a = a + mul(7,166);
a = a + mul(478,668);
a = a + mul(118,569);
a = a + mul(105,134);
a = a + mul(137,598);
a = a + mul(561,283);
a = a + mul(262,658);
a = a + mul(7,931);
a = a + mul(345,667);
a = a + mul(3,959);
a = a + mul(522,907);
a = a + mul(986,967);
a = a + mul(754,736);
a = a + mul(750,438);
a = a + mul(510,757);
a = a + mul(139,401);
a = a + mul(332,919);
a = a + mul(218,127);
a = a + mul(504,583);
a = a + mul(649,222);
a = a + mul(878,444);
a = a + mul(340,684);
a = a + mul(852,617);
a = a + mul(569,36);
a = a + mul(298,203);
a = a + mul(263,671);
a = a + mul(197,758);
a = a + mul(893,114);
a = a + mul(269,55);
a = a + mul(81,174);
a = a + mul(93,146);
a = a + mul(681,428);
a = a + mul(793,537);
a = a + mul(163,958);
a = a + mul(540,501);
a = a + mul(331,537);
a = a + mul(928,496);
a = a + mul(127,943);
a = a + mul(18,669);
a = a + mul(443,860);
a = a + mul(624,669);
a = a + mul(941,338);
a = a + mul(483,529);
a = a + mul(254,159);
a = a + mul(731,125);
a = a + mul(912,606);
a = a + mul(851,526);
a = a + mul(689,174);
a = a + mul(919,455);
a = a + mul(320,219);
a = a + mul(267,831);
a = a + mul(84,102);
a = a + mul(291,186);
a = a + mul(973,390);
a = a + mul(772,422);
a = a + mul(184,89);
a = a + mul(197,267);
a = a + mul(703,592);
a = a + mul(376,816);
a = a + mul(949,642);
a = a + mul(399,146);
a = a + mul(526,131);
a = a + mul(787,620);
a = a + mul(310,482);
a = a + mul(360,720);
a = a + mul(561,462);
a = a + mul(403,894);
a = a + mul(555,514);
a = a + mul(18,725);
a = a + mul(901,195);
a = a + mul(814,623);
a = a + mul(4,986);
a = a + mul(833,296);
a = a + mul(162,231);
a = a + mul(38,18);
a = a + mul(225,613);
a = a + mul(494,841);
a = a + mul(586,498);
a = a + mul(818,498);
a = a + mul(795,500);
a = a + mul(285,406);
a = a + mul(404,65);
a = a + mul(489,759);
a = a + mul(312,151);
a = a + mul(393,302);
a = a + mul(614,161);
a = a + mul(927,228);
a = a + mul(432,16);
a = a + mul(539,745);
a = a + mul(970,413);
a = a + mul(533,997);
a = a + mul(574,681);
a = a + mul(978,225);
a = a + mul(453,460);
a = a + mul(840,804);
a = a + mul(570,880);
a = a + mul(367,248);
a = a + mul(303,242);
a = a + mul(547,184);
a = a + mul(196,377);
a = a + mul(727,421);
a = a + mul(199,873);
a = a + mul(962,772);
a = a + mul(534,770);
a = a + mul(356,156);
a = a + mul(801,644);
a = a + mul(273,584);
a = a + mul(692,224);
a = a + mul(779,81);
a = a + mul(786,30);
a = a + mul(328,225);
a = a + mul(914,292);
a = a + mul(83,290);
a = a + mul(257,792);
a = a + mul(949,612);
a = a + mul(813,824);
a = a + mul(5,572);
a = a + mul(243,781);
a = a + mul(579,115);
a = a + mul(861,206);
a = a + mul(859,273);
a = a + mul(865,638);
a = a + mul(756,102);
a = a + mul(521,726);
a = a + mul(830,632);
a = a + mul(331,573);
a = a + mul(294,77);
a = a + mul(113,420);
a = a + mul(463,386);
a = a + mul(740,88);
a = a + mul(685,334);
a = a + mul(973,106);
a = a + mul(867,634);
a = a + mul(535,483);
a = a + mul(478,385);
a = a + mul(965,153);
a = a + mul(484,578);
a = a + mul(847,771);
a = a + mul(921,939);
a = a + mul(981,816);
a = a + mul(161,41);
a = a + mul(129,507);
a = a + mul(554,49);
a = a + mul(618,748);
a = a + mul(214,987);
a = a + mul(870,285);
a = a + mul(581,483);
a = a + mul(434,655);
a = a + mul(242,610);
a = a + mul(614,631);
a = a + mul(357,150);
a = a + mul(949,239);
a = a + mul(802,54);
a = a + mul(209,916);
a = a + mul(637,422);
a = a + mul(502,914);
a = a + mul(860,112);
a = a + mul(828,62);
a = a + mul(370,262);
a = a + mul(693,119);
a = a + mul(399,511);
a = a + mul(395,383);
a = a + mul(741,712);
a = a + mul(296,759);
a = a + mul(585,923);
a = a + mul(163,233);
a = a + mul(553,949);
a = a + mul(545,530);
a = a + mul(646,888);
a = a + mul(908,145);
a = a + mul(872,423);
a = a + mul(724,993);
a = a + mul(359,478);
a = a + mul(186,893);
a = a + mul(592,52);
a = a + mul(164,308);
a = a + mul(377,499);
a = a + mul(658,47);
a = a + mul(759,688);
a = a + mul(623,353);
a = a + mul(830,695);
a = a + mul(755,160);
a = a + mul(138,691);
a = a + mul(161,105);
a = a + mul(542,698);
a = a + mul(274,212);
a = a + mul(196,596);
a = a + mul(759,422);
a = a + mul(861,458);
a = a + mul(126,262);
a = a + mul(615,656);
a = a + mul(266,494);
a = a + mul(695,332);
a = a + mul(471,679);
a = a + mul(387,568);
a = a + mul(777,56);
a = a + mul(874,481);
a = a + mul(22,505);
a = a + mul(395,566);
a = a + mul(326,815);
a = a + mul(189,720);
a = a + mul(418,532);
a = a + mul(561,959);
a = a + mul(518,185);
a = a + mul(327,206);
a = a + mul(501,728);
a = a + mul(219,962);
a = a + mul(7,809);
a = a + mul(768,798);
a = a + mul(353,892);
a = a + mul(506,552);
a = a + mul(703,677);
a = a + mul(801,431);
a = a + mul(330,809);
a = a + mul(764,131);
a = a + mul(258,284);
a = a + mul(338,578);
a = a + mul(990,919);
a = a + mul(69,711);
a = a + mul(907,255);
a = a + mul(781,224);
a = a + mul(400,377);
a = a + mul(224,640);
a = a + mul(97,222);
a = a + mul(723,191);
a = a + mul(755,122);
a = a + mul(348,579);
a = a + mul(939,550);
a = a + mul(21,125);
a = a + mul(138,133);
a = a + mul(482,114);
a = a + mul(732,224);
a = a + mul(823,749);
a = a + mul(980,685);
a = a + mul(51,373);
a = a + mul(523,713);
a = a + mul(461,976);
a = a + mul(108,138);
a = a + mul(194,793);
a = a + mul(914,754);
a = a + mul(692,138);
a = a + mul(853,262);
a = a + mul(863,596);
a = a + mul(722,58);
a = a + mul(885,728);
a = a + mul(468,630);
a = a + mul(200,579);
a = a + mul(10,435);
a = a + mul(298,190);
a = a + mul(9,631);
a = a + mul(273,471);
a = a + mul(325,690);
a = a + mul(267,174);
a = a + mul(339,952);
a = a + mul(307,862);
a = a + mul(636,749);
a = a + mul(592,773);
a = a + mul(338,514);
a = a + mul(127,711);
a = a + mul(146,911);
a = a + mul(860,601);
a = a + mul(806,306);
a = a + mul(410,847);
a = a + mul(73,481);
a = a + mul(172,949);
a = a + mul(732,513);
a = a + mul(11,422);
a = a + mul(190,688);
a = a + mul(450,687);
a = a + mul(171,95);
a = a + mul(631,790);
a = a + mul(893,598);
a = a + mul(39,888);
a = a + mul(290,685);
a = a + mul(463,742);
a = a + mul(118,146);
a = a + mul(39,34);
a = a + mul(489,439);
a = a + mul(874,442);
a = a + mul(975,618);
a = a + mul(732,833);
a = a + mul(17,484);
a = a + mul(509,882);
a = a + mul(813,280);
a = a + mul(741,365);
a = a + mul(734,644);
a = a + mul(595,285);
a = a + mul(439,186);
a = a + mul(976,645);
a = a + mul(308,113);
a = a + mul(127,972);
a = a + mul(781,845);
a = a + mul(949,130);
a = a + mul(612,396);
a = a + mul(343,689);
a = a + mul(970,425);
a = a + mul(83,136);
a = a + mul(960,152);
a = a + mul(714,401);
a = a + mul(455,389);
a = a + mul(293,806);
a = a + mul(959,603);
a = a + mul(744,798);
a = a + mul(389,91);
a = a + mul(625,376);
a = a + mul(7,35);
a = a + mul(792,652);
a = a + mul(527,656);
a = a + mul(220,657);
a = a + mul(62,191);
a = a + mul(13,233);
a = a + mul(780,237);
a = a + mul(216,970);
a = a + mul(954,521);
a = a + mul(645,579);
a = a + mul(695,53);
a = a + mul(927,488);
a = a + mul(815,350);
a = a + mul(650,656);
a = a + mul(452,286);
a = a + mul(438,390);
a = a + mul(353,213);
a = a + mul(920,652);
a = a + mul(971,287);
a = a + mul(4,595);
a = a + mul(332,353);
a = a + mul(64,192);
a = a + mul(33,846);
a = a + mul(13,41);
a = a + mul(728,587);
a = a + mul(501,624);
a = a + mul(187,871);
a = a + mul(563,884);
a = a + mul(685,629);
a = a + mul(741,377);
a = a + mul(69,647);
a = a + mul(338,68);
a = a + mul(752,772);
a = a + mul(193,86);
a = a + mul(492,628);
a = a + mul(20,602);
a = a + mul(34,881);
a = a + mul(777,504);
a = a + mul(425,245);
a = a + mul(504,651);
a = a + mul(193,8);
a = a + mul(247,144);
a = a + mul(857,787);
a = a + mul(57,598);
a = a + mul(799,387);
a = a + mul(963,99);
a = a + mul(606,12);
a = a + mul(615,921);
a = a + mul(379,934);
a = a + mul(871,792);
a = a + mul(206,542);
a = a + mul(154,161);
a = a + mul(663,226);
a = a + mul(320,293);
a = a + mul(865,92);
a = a + mul(834,118);
a = a + mul(36,886);
a = a + mul(777,447);
a = a + mul(942,312);
a = a + mul(810,261);
a = a + mul(356,987);
a = a + mul(33,198);
a = a + mul(752,594);
a = a + mul(478,705);
a = a + mul(878,617);
a = a + mul(951,929);
a = a + mul(193,497);
a = a + mul(670,912);
a = a + mul(872,457);
a = a + mul(411,192);
a = a + mul(830,878);
a = a + mul(103,203);
a = a + mul(574,907);
a = a + mul(288,478);
a = a + mul(418,593);
a = a + mul(554,90);
a = a + mul(978,459);
a = a + mul(470,763);
a = a + mul(342,6);
a = a + mul(192,104);
a = a + mul(309,253);
a = a + mul(98,92);
a = a + mul(690,632);
a = a + mul(880,975);
a = a + mul(233,433);
a = a + mul(663,3);
a = a + mul(965,150);
a = a + mul(503,640);
a = a + mul(146,66);
a = a + mul(37,741);
a = a + mul(714,547);
*/

    char* str = fileslurp("advent03.txt");

    int i = 0;
    bool enabled = true;
    while(i < strlen(str))
    {
        if(str[i]=='d' && str[i+1]=='o' && str[i+2]=='(' && str[i+3]==')' && enabled == false)
        {
            ylogd("enabling");
            enabled = true;
            i = i + 3;
        }
        if(str[i]=='d' && str[i+1]=='o' && str[i+2]=='n' && str[i+3]=='\'' && str[i+4]=='t' && str[i+5]=='(' && str[i+6]==')' && enabled == true)
        {
            ylogd("disabling");
            enabled = false;
            i = i + 6;
        }
        if(enabled == true || p->part2 == 0)
        {
            if(str[i]==109 && str[i+1]=='u' && str[i+2]=='l' && str[i+3]=='\(')
            {
                char aa[4];
                char bb[4];
                ylogd("mul instruction");
                int k = 0;
                while(str[i+4+k]>=48 && str[i+4+k]<=57)
                {
                    ylogd("%c", str[i+4+k]);
                    aa[k] = str[i+4+k];
                    k++;
                }
                if(str[i+4+k]==',')
                {
                    aa[k]='\0';
                    int num1 = atoi(aa);

                    int j = 0;
                    char* temp;
                    while(str[i+4+k+1+j]>=48 && str[i+4+k+1+j]<=57)
                    {
                        ylogd("%c", str[i+4+k+1+j]);
                        bb[j] = str[i+4+k+1+j];
                        j++;
                    }

                    if(str[i+4+k+1+j]==')')
                    {
                        bb[j]='\0';
                        int num2 = atoi(bb);
                        ylogd("%c", str[i+4+k+1+j]);
                        i=i+4+k+1+j;

                        a = a + mul(num1, num2);
                    }
                    else
                    {
                        ylogd("malformed mul instruction )");
                        i = i + k + 4 + 1 +j;
                    }
                }
                else
                {
                    ylogd("malformed mul instruction ,");
                    i = i + k + 4;
                }
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    ylogi("sum of program is: %i", a);
    free(str);
    free(p);
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    ylogi("time : %f", elapsed_time);
    y_close_logs();
    return 0;
}
