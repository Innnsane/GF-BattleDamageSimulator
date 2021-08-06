﻿#include "calculation.h"

struct doll_info doll_origin[600] = {	//0为空，空缺的人形也赋值0，人形id对应数组
    //星级. 枪种 1HG 2SMG 3RF 4AR 5MG 6SG 心智
    //伤害. 射速. 命中.
    //暴击(RF/SG(0.4)-AR/HG(0.2)-MG/SMG(0.05)). 爆伤(1.5). 穿甲(15). 弹量(0).
    {},             //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 1 ,"柯尔特左轮¤" , 5 , 1 , 1 , 37  , 50  , 51 , 80  , 6 , 5 , 12 },
    { 2 ,   "M1911¤" , 4 , 1 , 1 , 29  , 58  , 52 , 78  , 1 , 4 , 12 },
    { 3 ,        "M9", 3 , 1 , 1 , 29  , 61  , 56 , 66  , 5 , 3.2 , 12 },
    { 4 ,       "蟒蛇", 5 , 1 , 0 , 40  , 49  , 81 , 82  , 6 , 5 , 12 },
    { 5 ,  "纳甘左轮¤" , 4 , 1 , 1 , 35  , 45  , 48 , 100 , 6 , 5 , 12 },
    { 6 ,   "托卡列夫" , 3 , 1 , 0 , 31  , 52  , 47 , 66  , 6 , 8 , 12 },
    { 7 ,  "斯捷奇金¤" , 5 , 1 , 1 , 32  , 66  , 51 , 69  , 6 , 8 , 12 },
    { 8 ,   "马卡洛夫" , 3 , 1 , 0 , 26  , 61  , 61 , 96  , 6 , 6 , 12 },
    { 9 ,      "P38" , 2 , 1 , 0 , 28  , 57  , 49 , 81  , 3 , 15 , 16 },
    { 10 ,     "PPK" , 2 , 1 , 0 , 25  , 63  , 59 , 100 , 6 , 8 , 12 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 11 ,      "P08" , 3 , 1 , 0 , 31  , 55  , 46 , 80  , 6 , 8 , 12 },
    { 12 ,     "C96¤" , 4 , 1 , 1 , 32  , 64  , 52 , 71  , 3 , 15 , 16 },
    { 13 ,      "92式" , 3 , 1 , 0 , 31  , 61  , 46 , 80  , 6 , 8 , 12 },
    { 14 ,"阿斯特拉左轮" , 3 , 1 , 0 , 33  , 52  , 45 , 68 , 6 , 8 , 12 },
    { 15 ,   "格洛克17" , 3 , 1 , 0 , 29  , 61  , 58 , 87 , 6 , 8 , 12 },
    { 16 ,     "汤姆森" , 5 , 2 , 0 , 31  , 82  , 12 , 56 , 8 , 4 , 16 },
    { 17 ,        "M3" , 2 , 2 , 0 , 30  , 68  , 13 , 67 , 3 , 0 , 16 },
    { 18 ,    "MAC-10" , 3 , 2 , 0 , 28  , 91  , 11 , 68 , 1 , 4 , 16 },
    { 19 ,     "FMG-9" , 3 , 2 , 0 , 26  , 92  , 13 , 90 , 6 , 5 , 8 },
    { 20 ,    "Vector" , 5 , 2 , 0 , 30  , 101 , 11 , 71 , 3 , 0 , 16 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 21 ,  "PPsh-41" , 2 , 2 , 0 , 26  , 93  , 11 , 56 , 3 , 0 , 16 },
    { 22 ,   "PPS-43" , 3 , 2 , 0 , 33  , 74  , 13 , 65 , 3 , 0 , 16 },
    { 23 ,    "PP-90" , 4 , 2 , 0 , 25  , 96  , 13 , 86 , 4 , 15 , 16 },
    { 24 ,  "PP-2000" , 2 , 2 , 0 , 30  , 80  , 11 , 74 , 3 , 0 , 16 },
    { 25 ,    "MP-40" , 2 , 2 , 0 , 29  , 76  , 13 , 58 , 3 , 0 , 16 },
    { 26 ,     "MP5¤" , 5 , 2 , 1 , 32  , 90  , 14 , 71 , 8 , 4 , 16 },
    { 27 ,      "蝎式" , 3 , 2 , 0 , 24  , 95  , 13 , 83 , 3 , 0 , 16 },
    { 28 ,      "MP7" , 5 , 2 , 0 , 30  , 91  , 13 , 69 , 6 , 5 , 8 },
    { 29 , "司登MkⅡ¤" , 4 , 2 , 1 , 29  , 86  , 17 , 79 , 3 , 0 , 16 },
    {}, //30

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 31 , "伯莱塔38型" , 2 , 2 , 0 , 33  , 75  , 10 , 52  , 5 , 3.2 , 16 },
    { 32 ,  "微型乌兹¤" , 4 , 2 , 1 , 26  , 104 , 13 , 83  , 3 , 0 , 16 },
    { 33 ,       "M45" , 2 , 2 , 0 , 30  , 74  , 12 , 62  , 1 , 0 , 12 },
    { 34 ,   "M1加兰德" , 3 , 3 , 0 , 120 , 37  , 62 , 28  , 5 , 0 , 11 },
    { 35 ,      "M1A1" , 3 , 3 , 0 , 95  , 38  , 67 , 42  , 5 , 15 , 16 },
    { 36 ,       "春田" , 4 , 3 , 0 , 128 , 32  , 72 , 40  , 5 , 0 , 11 },
    { 37 ,      "M14¤" , 4 , 3 , 1 , 111 , 44  , 74 , 28  , 5 , 5 , 8 },
    { 38 ,       "M21" , 3 , 3 , 0 , 118 , 35  , 74 , 27  , 5 , 0 , 11 },
    { 39 , "莫辛-纳甘¤" , 5 , 3 , 1 , 136 , 31  , 89 , 40  , 5 , 0 , 11 },
    { 40 ,    "SVT-38" , 2 , 3 , 0 , 110 , 34  , 59 , 34  , 5 , 0 , 11 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 41 ,   "西蒙诺夫" , 2 , 3 , 0 , 100 , 34  , 59 , 34  , 5 , 5 , 8 },
    { 42 ,      "PTRD" , 4 , 3 , 0 , 159 , 28  , 75 , 29  , 8 , 0 , 9 },
    { 43 ,       "SVD" , 4 , 3 , 0 , 130 , 37  , 80 , 33  , 5 , 5 , 8 },
    { 44 ,    "SV-98¤" , 4 , 3 , 1 , 128 , 37  , 81 , 29  , 5 , 0 , 11 },
    {}, //45
    { 46 ,    "Kar98k" , 5 , 3 , 0 , 135 , 34  , 78 , 41  , 8 , 0 , 16 },
    { 47 ,       "G43" , 2 , 3 , 0 , 111 , 40  , 58 , 28  , 8 , 5 , 8 },
    { 48 ,    "WA2000" , 5 , 3 , 0 , 130 , 39  , 82 , 30  , 5 , 5 , 8 },
    { 49 ,    "56式半" , 3 , 3 , 0 , 103 , 36  , 65 , 36  , 5 , 5 , 8 },
    { 50 ,"李-恩菲尔德" , 5 , 3 , 0 , 135 , 36  , 78 , 40  , 5 , 5 , 8 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 51 ,   "FN-49¤" , 4 , 3 , 1 , 120 , 34  , 64 , 33  , 5 , 5 , 8 },
    { 52 ,     "BM59" , 2 , 3 , 0 , 104 , 38  , 52 , 25  , 5 , 5 , 8 },
    { 53 ,  "NTW-20¤" , 6 , 3 , 1 , 170 , 30  , 82 , 31  , 7 , 0 , 9 },
    { 54 ,    "M16A1" , 4 , 4 , 0 , 47  , 75  , 46 , 44  , 5 , 4 , 16 },
    { 55 ,    "M4A1¤" , 5 , 4 , 1 , 50  , 80  , 50 , 50  , 4 , 10 , 16 },
    { 56 ,"M4 SOPⅡ¤" , 5 , 4 , 1 , 52  , 79  , 51 , 46  , 8 , 0 , 16 },
    { 57 ,"ST AR-15¤" , 5 , 4 , 1 , 50  , 78  , 55 , 52  , 4 , 15 , 16 },
    { 58 ,    "AK-47" , 3 , 4 , 0 , 53  , 65  , 35 , 34  , 5 , 5 , 8 },
    { 59 ,   "AK-74U" , 5 , 2 , 0 , 35  , 83  , 13 , 67  , 6 , 5 , 16 },
    { 60 ,  "AS Val¤" , 5 , 4 , 1 , 47  , 75  , 46 , 51  , 5 , 6 , 16 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 61 ,   "StG44¤" , 4 , 4 , 1 , 58  , 66  , 50 , 38  , 8 , 0 , 16 },
    { 62 ,      "G41" , 5 , 4 , 0 , 50  , 77  , 48 , 40  , 4 , 10 , 16 },
    { 63 ,      "G3¤" , 4 , 4 , 1 , 58  , 54  , 55 , 39  , 8 , 0 , 16 },
    { 64 ,     "G36¤" , 5 , 4 , 1 , 51  , 76  , 48 , 45  , 4 , 10 , 16 },
    { 65 ,   "HK416¤" , 6 , 4 , 1 , 55  , 79  , 51 , 47  , 6 , 0 , 16 },
    { 66 ,   "56-1式" , 4 , 4 , 0 , 52  , 69  , 35 , 35  , 8 , 0 , 16 },
    {}, //67
    { 68 ,   "L85A1 " , 2 , 4 , 0 , 46  , 78  , 43 , 43  , 6 , 5 , 8 },
    { 69 ,    "FAMAS" , 4 , 4 , 0 , 44  , 81  , 48 , 40  , 8 , 0 , 16 },
    { 70 ,      "FNC" , 3 , 4 , 0 , 51  , 73  , 46 , 37  , 5 , 5 , 8 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却/弹量
    { 71 ,    "加利尔" , 2 , 4 , 0 , 50  , 66  , 44 , 43  , 5 , 15 , 16 },
    { 72 ,   "TAR-21" , 4 , 4 , 0 , 49  , 79  , 48 , 44  , 6 , 5 , 16 },
    { 73 ,      "AUG" , 5 , 4 , 0 , 55  , 75  , 57 , 46  , 4 , 7 , 16 },
    { 74 ,  "SIG-510" , 2 , 4 , 0 , 56  , 59  , 41 , 37  , 5 , 5 , 8 },
    { 75 ,   "M1918¤" , 5 , 5 , 1 , 101 , 115 , 34 , 34  , 8 , 6 , 18 , 8 },
    {}, //76
    { 77 ,     "M2HB" , 3 , 5 , 0 , 102 , 100 , 18 , 16  , 0 , 0 , 0 , 10 },
    { 78 ,      "M60" , 4 , 5 , 0 , 92  , 111 , 26 , 26  , 8 , 6 , 18 , 9 },
    { 79 , "M249 SAW" , 3 , 5 , 0 , 79  , 139 , 35 , 36  , 8 , 8 , 18 , 8 },
    { 80 ,  "M1919A4" , 3 , 5 , 0 , 96  , 99  , 26 , 22  , 3 , 6 , 18 , 9 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 81 ,   "LWMMG¤" , 4 , 5 , 1 , 103 , 92  , 27 , 24  , 3 , 6 , 18 , 10 },
    { 82 ,     "DP28" , 2 , 5 , 0 , 88  , 114 , 28 , 31  , 8 , 8 , 18 , 9 },
    {}, //83
    { 84 ,      "RPD" , 3 , 5 , 0 , 82  , 121 , 34 , 34  , 8 , 6 , 18 , 8 },
    { 85 ,       "PK" , 4 , 5 , 0 , 93  , 83  , 21 , 22  , 0 , 0 , 0 , 11 },
    { 86 ,     "MG42" , 3 , 5 , 0 , 87  , 132 , 23 , 26  , 8 , 6 , 18 , 10 },
    { 87 ,     "MG34" , 2 , 5 , 0 , 85  , 120 , 22 , 25  , 8 , 6 , 18 , 10 },
    { 88 ,      "MG3" , 4 , 5 , 0 , 85  , 130 , 26 , 21  , 8 , 8 , 18 , 10 },
    { 89 ,     "布伦¤" , 4 , 5 , 1 , 97  , 103 , 34 , 29  , 8 , 8 , 18 , 8 },
    { 90 ,    "FNP-9" , 2 , 1 , 0 , 28  , 61  , 53 , 83  , 6 , 8 , 12 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 91 ,   "MP-446¤" , 4 , 1 , 1 , 31  , 60  , 57 , 80  , 6 , 8 , 12 },
    { 92 ,"Spectre M4" , 2 , 2 , 0 , 25  , 88  , 12 , 66  , 6 , 5 , 8 },
    { 93 ,      "IDW¤" , 4 , 2 , 1 , 26  , 75  , 15 , 88  , 6 , 5 , 8 },
    { 94 ,     "64式¤" , 4 , 2 , 1 , 27  , 93  , 11 , 67  , 5 , 4 , 16 },
    { 95 ,"汉阳造88式¤" , 4 , 3 , 1 , 114 , 37  , 66 , 37  , 6 , 6 , 8 },
    { 96 ,  "灰熊Mk Ⅴ" , 5 , 1 , 0 , 38  , 54  , 51 , 66  , 6 , 8 , 12 },
    { 97 ,     "M950A" , 5 , 1 , 0 , 30  , 72  , 55 , 68  , 6 , 8 , 12 },
    { 98 ,     "SPP-1" , 4 , 1 , 0 , 35  , 48  , 61 , 75  , 6 , 8 , 12 },
    { 99 ,      "Mk23" , 4 , 1 , 0 , 29  , 63  , 53 , 66  , 6 , 8 , 12 },
    { 100 ,       "P7" , 4 , 1 , 0 , 32  , 61  , 62 , 83  , 6 , 8 , 12 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 101 ,    "UMP9¤" , 5 , 2 , 1 , 29  , 87  , 17 , 80  , 5 , 4.5 , 16 },
    { 102 ,    "UMP40" , 4 , 2 , 0 , 27  , 85  , 14 , 75  , 1 , 0 , 666 },
    { 103 ,   "UMP45¤" , 5 , 2 , 1 , 28  , 82  , 13 , 74  , 1 , 4 , 16 },
    { 104 ,     "G36C" , 5 , 2 , 0 , 32  , 83  , 13 , 65  , 8 , 4 , 16 },
    { 105 ,   "OTs-12" , 3 , 4 , 0 , 42  , 72  , 54 , 54  , 4 , 10 , 16 },
    { 106 ,      "FAL" , 5 , 4 , 0 , 57  , 72  , 43 , 38  , 6 , 0 , 16 },
    { 107 ,    "F2000" , 2 , 4 , 0 , 42  , 81  , 44 , 40  , 5 , 5 , 8 },
    { 108 ,   "CZ-805" , 3 , 4 , 0 , 43  , 75  , 49 , 41  , 8 , 0 , 16 },
    { 109 ,      "MG5" , 5 , 5 , 0 , 85  , 120 , 27 , 27  , 0 , 0 , 0 , 11 },
    { 110 ,    "FG-42" , 2 , 5 , 0 , 87  , 121 , 28 , 33  , 3 , 6 , 18 , 8 },

                     //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 111 ,   "AAT-52" , 2 , 5 , 0 , 79  , 118 , 24 , 22  , 8 , 6 , 18 , 10 },
    { 112 ,    "内格夫" , 5 , 5 , 0 , 84  , 139 , 35 , 36  , 0 , 25 , 1 , 9 },
    { 113 ,"谢尔久科夫" , 3 , 1 , 0 , 33  , 59  , 58 , 68  , 6 , 8 , 12 },
    { 114 ,"维尔德MkⅡ" , 5 , 1 , 0 , 28  , 52  , 71 , 90  , 6 , 6 , 12 },
    { 115 ,     "索米" , 5 , 2 , 0 , 28  , 93  , 15 , 56  , 6 , 5 , 8 },
    { 116 ,     "Z-62" , 3 , 2 , 0 , 28  , 77  , 15 , 77  , 3 , 0 , 16 },
    { 117 ,    "PSG-1" , 4 , 3 , 0 , 120 , 39  , 73 , 26  , 5 , 0 , 11 },
    { 118 ,    "9A-91" , 4 , 4 , 0 , 42  , 78  , 49 , 50  , 5 , 6 , 16 },
    { 119 ,   "OTs-14" , 5 , 4 , 0 , 49  , 75  , 54 , 54  , 5 , 6 , 16 },
    { 120 ,  "ARX-160" , 3 , 4 , 0 , 49  , 73  , 48 , 48  , 8 , 0 , 16 },

                      //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 121 ,      "Mk48" , 4 , 5 , 0 , 90  , 116 , 25 , 26  , 3 , 6 , 18 , 10 },
    { 122 ,       "G11" , 5 , 4 , 0 , 43  , 95  , 44 , 41  , 6 , 4.5 , 16 },
    { 123 ,       "P99" , 3 , 1 , 0 , 31  , 61  , 56 , 87  , 6 , 8 , 12 },
    { 124 ,"Super SASS" , 3 , 3 , 0 , 115 , 39  , 65 , 27  , 5 , 0 , 11 },
    { 125 ,       "MG4" , 5 , 5 , 0 , 84  , 139 , 34 , 34  , 8 , 8 , 18 , 9 },
    { 126 ,      "NZ75" , 5 , 1 , 0 , 33  , 63  , 62 , 74  , 6 , 8 , 12 },
    { 127 ,      "79式" , 5 , 2 , 0 , 32  , 88  , 12 , 70  , 5 , 4.5 , 16 },
    { 128 ,       "M99" , 5 , 3 , 0 , 157 , 32  , 81 , 32  , 8 , 0 , 9 },
    { 129 ,      "95式" , 5 , 4 , 0 , 55  , 71  , 52 , 46  , 2 , 15 , 16 },
    { 130 ,      "97式" , 5 , 4 , 0 , 54  , 72  , 51 , 46  , 2 , 15 , 16 },

                      //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 131 ,    "EVO 3" , 3 , 2 , 0 , 23  , 93 , 13 , 68  , 3 , 0 , 16 },
    { 132 ,     "59式" , 3 , 1 , 0 , 28  , 61 , 62 , 96  , 6 , 8 , 12 },
    { 133 ,     "63式" , 2 , 4 , 0 , 51  , 73 , 40 , 40  , 5 , 15 , 116  },
    { 134 ,     "AR70" , 3 , 4 , 0 , 50  , 71 , 44 , 41  , 8 , 0 , 16 },
    { 135 ,   "SR-3MP" , 5 , 2 , 0 , 31  , 90 , 12 , 67  , 4 , 5 , 8 },
    { 136 ,    "PP-19" , 4 , 2 , 0 , 26  , 91 , 14 , 74  , 3 , 0 , 16 },
    { 137 , "PP-19-01" , 4 , 2 , 0 , 27  , 85 , 13 , 68  , 1 , 4 , 16},
    { 138 ,     "6P62" , 3 , 4 , 0 , 69  , 54 , 37 , 33  , 5 , 5 , 8 },
    { 139 , "Bren Ten" , 2 , 1 , 0 , 31  , 58 , 51 , 63  , 6 , 8 , 12 },
    { 140 ,      "PSM" , 3 , 1 , 0 , 24  , 65 , 67 , 112 , 6 , 8 , 12 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 141 , "USP Compact" , 2 , 1 , 0 , 24  , 64 , 60 , 86  , 6 , 8 , 12  },
    { 142 ,  "Five-seveN" , 5 , 1 , 0 , 31  , 66 , 57 , 97  , 6 , 8 , 12  },
    { 143 ,       "RO635" , 5 , 2 , 0 , 27  , 97 , 14 , 71  , 3 , 5 , 12 },
    { 144 ,        "MT-9" , 3 , 2 , 0 , 25  , 88 , 13 , 60  , 5 , 3.5 , 16 },
    { 145 ,      "OTs-44" , 3 , 3 , 0 , 157 , 32 , 67 , 32  , 8 , 0 , 9 },
    { 146 ,         "G28" , 4 , 3 , 0 , 119 , 39 , 80 , 29  , 5 , 5 , 8 },
    { 147 ,      "SSG 69" , 3 , 3 , 0 , 130 , 30 , 82 , 39  , 5 , 5 , 8 },
    { 148 ,    "IWS 2000" , 5 , 3 , 0 , 162 , 32 , 78 , 29  , 6 , 10 , 16 },
    { 149 ,     "AEK-999" , 4 , 5 , 0 , 89  , 120, 29 , 28  , 8 , 6 , 18 , 10 },
    { 150 ,       "希普卡" , 4 , 2 , 0 , 24  , 95 , 14 , 79  , 6 , 5 , 8 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 151 ,      "M1887" , 5 , 6 , 0 , 39  , 22 , 12 , 12  , 15 , 0 , 16 , 4 , 22 },
    { 152 ,      "M1897" , 3 , 6 , 0 , 35  , 26 , 11 , 11  , 8 , 0 , 16 , 4 , 21 },
    { 153 ,        "M37" , 4 , 6 , 0 , 33  , 26 , 12 , 12  , 8 , 0 , 16 , 4 , 22 },
    { 154 ,       "M500" , 3 , 6 , 0 , 31  , 29 , 11 , 10  , 10 , 6 , 16 , 4 , 21 },
    { 155 ,       "M590" , 4 , 6 , 0 , 32  , 31 , 11 , 10  , 10 , 6 , 16 , 4 , 22 },
    { 156 ,"Super-Shorty", 4 , 6 , 0 , 28  , 30 , 14 , 19  , 10 , 6 , 16 , 3 , 20 },
    { 157 ,        "KSG" , 5 , 6 , 0 , 29  , 30 , 13 , 12  , 8 , 8 , 16 , 5 , 24 },
    { 158 ,      "KS-23" , 3 , 6 , 0 , 40  , 25 , 9  , 10  , 8 , 0 , 16 , 3 , 21 },
    { 159 ,     "RMB-93" , 3 , 6 , 0 , 30  , 28 , 11 , 13  , 8 , 0 , 16 , 4 , 22 },
    { 160 ,   "Saiga-12" , 5 , 6 , 0 , 29  , 35 , 12 , 11  , 8 , 0 , 16 , 5 , 23 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 161 ,     "97式霰"   , 4 , 6 , 0 , 33 , 27 , 12 , 13 , 8 , 8 , 16 , 3 , 20 },
    { 162 ,     "SPAS-12" , 4 , 6 , 0 , 33 , 32 , 11 , 9  , 8 , 8 , 16 , 4 , 21 },
    { 163 ,       "AA-12" , 5 , 6 , 0 , 30 , 39 , 12 , 11  , 8 , 8 , 16 , 5 , 22 },
    { 164 ,        "FP-6" , 5 , 6 , 0 , 31 , 28 , 13 , 12  , 10 , 8 , 16 , 4 , 24 },
    { 165 ,       "M1014" , 4 , 6 , 0 , 31 , 32 , 12 , 11  , 10 , 8 , 16 , 4 , 21 },
    { 166 ,        "CZ75" , 5 , 1 , 0 , 34 , 66 , 62 , 74  , 6 , 0 , 12 },
    { 167 ,        "HK45" , 3 , 1 , 0 , 34 , 55 , 58 , 80  , 6 , 8 , 12 },
    { 168 ,    "Spitfire" , 4 , 1 , 0 , 33 , 59 , 60 , 71  , 6 , 8 , 12},
    { 169 ,         "SCW" , 3 , 2 , 0 , 30 , 91 , 12 , 68  , 6 , 5 , 8 },
    { 170 ,    "Ash-12.7" , 3 , 4 , 0 , 65 , 59 , 41 , 36  , 6 , 5 , 8 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 171 ,     "利贝罗勒" , 4 , 4 , 0 , 64  , 63 , 44 , 40  , 6 , 5 , 16 },
    { 172 ,         "RFB" , 5 , 4 , 0 , 69  , 54 , 68 , 49  , 6 , 8 , 16 },
    { 173 ,         "PKP" , 5 , 5 , 0 , 95  , 127, 31 , 29  , 0 , 0 , 0 , 10 },
    { 174 ,     "八一式马" , 3 , 3 , 0 , 123 , 32 , 79 , 41  , 8 , 5 , 8 },
    { 175 ,      "ART556" , 5 , 4 , 0 , 53  , 69 , 53 , 49  , 6 , 5 , 16 },
    { 176 ,         "TMP" , 3 , 2 , 0 , 28  , 93 , 14 , 77  , 6 , 5 , 8 },
    { 177 ,        "KLIN" , 4 , 2 , 0 , 25  , 95 , 11 , 74  , 3 , 0 , 16 },
    { 178 ,          "F1" , 3 , 2 , 0 , 26  , 79 , 14 , 60  , 1 , 4 , 16 },
    { 179 ,      "DSR-50" , 5 , 3 , 0 , 163 , 31 , 87 , 33  , 8 , 0 , 9 },
    { 180 ,       "PzB39" , 4 , 3 , 0 , 148 , 32 , 71 , 31  , 6 , 0 , 16 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 181 ,         "T91" , 5 , 4 , 0 , 51  , 76  , 44 , 46  , 5 , 8 , 16 },
    { 182 ,       "wz.29" , 3 , 3 , 0 , 113 , 32  , 65 , 33  , 6 , 5 , 8 },
    { 183 ,       "竞争者" , 5 , 1 , 0 , 46  , 44  , 85 , 82  , 6 , 0 , 12 },
    { 184 ,      "T-5000" , 4 , 3 , 0 , 126 , 36  , 85 , 28  , 6 , 6 , 8 },
    { 185 ,       "阿梅利" , 4 , 5 , 0 , 83  , 149 , 38 , 42  , 8 , 8 , 18 , 8 },
    { 186 ,        "P226" , 3 , 1 , 0 , 29  , 61  , 58 , 63  , 6 , 8 , 12 },
    { 187 ,        "Ak 5" , 4 , 4 , 0 , 51  , 75  , 48 , 38  , 5 , 5 , 8 },
    { 188 ,     "S.A.T.8" , 5 , 6 , 0 , 29  , 33  , 13 , 12  , 2 , 5 , 8 , 4 , 22 },
    { 189 ,     "USAS-12" , 4 , 6 , 0 , 29  , 37  , 11 , 10  , 1 , 8 , 16 , 5 , 22 },
    { 190 ,      "NS2000" , 3 , 6 , 0 , 33  , 27  , 12 , 11  , 8 , 0 , 16 , 5 , 20 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 191 ,         "M12" , 3 , 2 , 0 , 26  , 76  , 15 , 64  , 3 , 0 , 16 },
    { 192 ,        "JS05" , 5 , 3 , 0 , 158 , 31  , 88 , 32  , 6 , 0 , 16 },
    { 193 ,         "T65" , 3 , 4 , 0 , 54  , 76  , 44 , 40  , 5 , 8 , 16 },
    { 194 ,          "K2" , 5 , 4 , 0 , 50  , 78  , 51 , 42  , 8 , 0 , 3 },
    { 195 ,        "HK23" , 3 , 5 , 0 , 80  , 135 , 34 , 34  , 8 , 8 , 18 , 9 },
    { 196 ,     "Zas M21" , 5 , 4 , 0 , 55  , 74  , 48 , 41  , 4 , 0 , 16 },
    { 197 ,"卡尔卡诺M1891" , 5 , 3 , 0 , 138 , 34  , 85 , 42  , 6 , 7.5 , 8 },
    { 198 ,"卡尔卡诺M91/38", 5 , 3 , 0 , 146 , 34  , 90 , 44  , 6 , 0 , 8 },
    { 199 ,        "80式" , 4 , 5 , 0 , 93  , 118 , 26 , 24  , 8 , 6 , 18 , 10 },
    { 200 ,         "XM3" , 4 , 3 , 0 , 130 , 35  , 90 , 32  , 8 , 5 , 8 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 201 ,       "猎豹M1" , 3 , 3 , 0 , 143 , 30 , 77 , 28  , 8 , 0 , 9 },
    { 202 ,         "雷电" , 4 , 1 , 0 , 46  , 37 , 57 , 60  , 4 , 0 , 12 },
    { 203 ,         "蜜獾" , 4 , 2 , 0 , 33  , 82 , 13 , 60  , 6 , 5 , 8 },
    { 204 ,     "芭莉斯塔" , 5 , 3 , 0 , 139 , 36  , 92 , 35  , 8 , 0 , 16 },
    { 205 ,       "AN-94" , 5 , 4 , 0 , 55  , 76  , 67 , 48  , 6 , 5 , 8 },
    { 206 ,       "AK-12" , 5 , 4 , 0 , 56  , 78  , 62 , 52  , 6 , 5 , 8 },
    { 207 ,      "CZ2000" , 4 , 4 , 0 , 48  , 78  , 44 , 46  , 4 , 10 , 16 },
    { 208 ,        "HK21" , 5 , 5 , 0 , 92  , 135 , 29 , 33  , 8 , 8 , 18 , 10 },
    { 209 ,      "OTs-39" , 3 , 2 , 0 , 27  , 74  , 14 , 72  , 5 , 3.5 , 16 },
    { 210 ,        "CZ52" , 3 , 1 , 0 , 33  , 53  , 50 , 68  , 6 , 8 , 12 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 211 ,         "SRS" , 5 , 3 , 0 , 135 , 35  , 82 , 35  , 6 , 5 , 8 },
    { 212 ,          "K5" , 4 , 1 , 0 , 29  , 62  , 52 , 81  , 6 , 8 , 12 },
    { 213 ,        "C-MS" , 5 , 2 , 0 , 32  , 87  , 15 , 75  , 1 , 0 , 1 },
    { 214 ,         "ADS" , 5 , 4 , 0 , 50  , 78  , 54 , 45  , 5 , 5 , 16 },
    { 215 ,         "MDR" , 5 , 4 , 0 , 56  , 76  , 50 , 41  , 4 , 10 , 16 },
    { 216 ,         "XM8" , 4 , 4 , 0 , 48  , 79  , 46 , 42  , 8 , 0 , 16 },
    { 217 ,        "SM-1" , 3 , 3 , 0 , 95  , 40  , 79 , 40  , 5 , 15 , 16 },
    { 218 ,         "T77" , 3 , 2 , 0 , 24  , 92  , 11 , 69  , 4 , 15 , 16 },
    { 0 },
    { 220 ,      "MP-443" , 3 , 1 , 0 , 33  , 59  , 53 , 71  , 6 , 8 , 12 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 221 ,      "GSh-18" , 3 , 1 , 0 , 33  , 52  , 48 , 86  , 6 , 6 , 12 },
    { 222 ,      "TAC-50" , 5 , 3 , 0 , 155 , 32  , 83 , 31  , 10 , 0 , 16 },
    { 223 ,     "Model L" , 3 , 4 , 0 , 50  , 73  , 45 , 41  , 5 , 5 , 8 },
    { 224 ,       "PM-06" , 5 , 2 , 0 , 29  , 83  , 15 , 75  , 4 , 10 , 16 },
    { 225 ,     "Cx4 风暴" , 4 , 2 , 0 , 34  , 64  , 16 , 74  , 6 , 10 , 16 },
    { 226 ,        "Mk12" , 4 , 3 , 0 , 101 , 46  , 82 , 32  , 6 , 5 , 8 },
    { 227 ,        "A-91" , 4 , 4 , 0 , 52  , 75  , 50 , 37  , 8 , 10 , 16 },
    { 228 ,         "樱花" , 5 , 2 , 0 , 29  , 76  , 14 , 67  , 8 , 5 , 16 },
    { 229 ,        "M870" , 5 , 6 , 0 , 33  , 29  , 13 , 12  , 10 , 6 , 16 , 4 , 23 },
    { 230 ,         "OBR" , 3 , 3 , 0 , 117 , 37  , 80 , 32  , 6 , 6 , 8 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 231 ,       "M82A1" , 5 , 3 , 0 , 158 , 34  , 77 , 30  , 6 , 0 , 8 },
    { 232 ,      "MP-448" , 3 , 1 , 0 , 26  , 60  , 62 , 99  , 6 , 8 , 12 },
    { 233 ,     "Px4 风暴" , 5 , 1 , 0 , 35  , 57  , 69 , 93  , 6 , 8 , 12 },
    { 234 ,        "JS 9" , 5 , 2 , 0 , 27  , 89  , 15 , 86  , 6 , 5 , 8 },
    { 235 ,     "SPR A3G" , 4 , 3 , 0 , 130 , 35  , 83 , 31  , 8 , 5 , 8 },
    { 236 ,         "K11" , 5 , 4 , 0 , 53  , 76  , 54 , 37  , 6 , 0 , 16 },
    { 237 ,      "SAR-21" , 4 , 4 , 0 , 44  , 80  , 46 , 38  , 4 , 6 , 16 },
    { 238 ,        "88式" , 5 , 5 , 0 , 86  , 126 , 33 , 35  , 8 , 6 , 18 , 10 },
    { 239 ,        "03式" , 3 , 4 , 0 , 51  , 71  , 47 , 39  , 6 , 5 , 8 },
    { 240 ,        "Mk46" , 4 , 5 , 0 , 78  , 142 , 34 , 36  , 8 , 6 , 18 , 9 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 241 ,       "RT-20" , 3 , 3 , 0 , 158 , 27  , 78 , 28  , 8 , 0 , 9 },
    { 242 ,         "P22" , 5 , 1 , 0 , 28  , 62  , 66 , 110  , 6 , 8 , 12 },
    { 243 ,       "64式自" , 5 , 4 , 0 , 67  , 63  , 62 , 43  , 5 , 3 , 16 },
    { 244 ,       "TEC-9" , 3 , 1 , 0 , 28  , 63  , 46 , 63  , 6 , 8 , 12 },
    { 245 ,         "P90" , 5 , 2 , 0 , 30  , 93  , 15 , 83  , 6 , 5 , 12 },
    { 0 },
    { 247 ,         "K31" , 4 , 3 , 0 , 126 , 39  , 78 , 37  , 6 , 5 , 8 },
    { 248 ,       "杰里科" , 4 , 1 , 0 , 31  , 60  , 50 , 64  , 6 , 8 , 12 },
    { 249 ,        "62式" , 3 , 5 , 0 , 87  , 122 , 31 , 28  , 8 , 6 , 18 , 9 },
    { 250 ,      "HS2000" , 5 , 1 , 0 , 33  , 62  , 61 , 87  , 6 , 8 , 12 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 251 ,       "X95" , 5 , 2 , 0 , 34  , 90  , 13 , 67  , 4 , 5 , 8 },
    { 252 ,      "KSVK" , 4 , 3 , 0 , 158 , 31  , 78 , 30  , 10 , 5 , 16 },
    { 253 ,     "刘易斯" , 5 , 5 , 0 , 102 , 116 , 31 , 31  , 8 , 6 , 18 , 10 },
    { 254 ,  "UKM-2000" , 4 , 5 , 0 , 90  , 115 , 26 , 26  , 8 , 8 , 18 , 11 },
    { 255 ,     "侦察者" , 3 , 3 , 0 , 114 , 35  , 78 , 35  , 5 , 5 , 8 },
    { 256 ,        "隼" , 3 , 3 , 0 , 140 , 32  , 71 , 28  , 6 , 0 , 1 },
    { 257 ,      "M200" , 5 , 3 , 0 , 145 , 34  , 96 , 31  , 6 , 9 , 16 },
    { 258 ,     "马盖尔" , 3 , 4 , 0 , 47  , 70  , 47 , 43  , 6 , 10 , 16 },
    { 259 ,      "PM-9" , 5 , 2 , 0 , 28  , 102 , 13 , 85  , 6 , 5 , 8 },
    { 260 ,     "PA-15" , 5 , 1 , 0 , 35  , 64  , 65 , 76  , 6 , 3 , 12 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 261 ,    "QBU-88" , 5 , 3 , 0 , 126 , 42  , 87 , 41  , 8 , 0 , 16 },
    { 262 ,      "EM-2" , 4 , 4 , 0 , 57  , 61  , 48 , 48  , 6 , 0 , 16 },
    { 263 ,      "MG36" , 5 , 5 , 0 , 85  , 129 , 34 , 36  , 8 , 6 , 18 , 10 },
    { 264 ,      "绍沙" , 4 , 5 , 0 , 102 , 81  , 34 , 30  , 6 , 0 , 2 , 9 },
    { 265 ,      "HK33" , 3 , 4 , 0 , 49  , 73  , 51 , 46  , 4 , 10 , 16 },
    { 266 ,       "R93" , 5 , 3 , 0 , 133 , 39  , 97 , 34  , 6 , 5 , 8 },
    { 267 ,      "MP41" , 3 , 2 , 0 , 30  , 77  , 13 , 60  , 1 , 4 , 16 },
    { 268 ,     "T-CMS" , 3 , 3 , 0 , 120 , 37  , 75 , 27  , 5 , 5 , 8 },
    { 269 ,       "P30" , 4 , 1 , 0 , 32  , 55  , 62 , 85  , 3 , 0 , 3 },
    { 270 ,      "四式" , 4 , 3 , 0 , 112 , 39  , 74 , 37  , 6 , 5 , 8 },

                       //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 271 ,        "K3" , 3 , 5 , 0 , 78  , 134 , 30 , 35  , 8 , 8 , 18 , 9 },
    { 272 ,   "沙漠之鹰" , 5 , 1 , 0 , 41  , 55  , 57 , 66  , 6 , 8 , 12 },
    { 273 ,   "SSG3000" , 4 , 3 , 0 , 126 , 37  , 77 , 30  , 6 , 9 , 16 },
    { 274 ,       "ACR" , 5 , 4 , 0 , 54  , 77  , 54 , 48  , 6 , 5 , 8 },
    { 275 ,  "M1895 CB" , 4 , 5 , 0 , 90  , 131 , 26 , 23  , 3 , 0 , 5.5 , 10 },
    { 276 ,      "Kord" , 5 , 5 , 0 , 109 , 110 , 22 , 21  , 0 , 0 , 3 , 9 },
    { 277 ,      "VP70" , 3 , 1 , 0 , 31  , 60  , 54 , 75  , 6 , 8 , 12 },
    { 278 ,     "Six12" , 3 , 6 , 0 , 34  , 30  , 13 , 13  , 8 , 0 , 16 , 4 , 20 },
    { 279 ,     "INSAS" , 3 , 4 , 0 , 49  , 71  , 52 , 45  , 5 , 5 , 8 },
    { 0 },
                      //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 281 ,     "CAWS" , 5 , 6 , 0 , 30  , 35  , 12 , 13  , 8 , 5 , 16 , 5 , 23 },
    { 282 ,    "DP-12" , 5 , 6 , 0 , 31  , 30  , 13 , 13  , 3 , 0 , 16 , 5 , 23 },
    { 283 ,    "解放者" , 4 , 6 , 0 , 36  , 30  , 12 , 15  , 8 , 8 , 16 , 4 , 21 },
    { 0 },
    { 0 },
    { 0 },
    { 286 , "SIG556-3" , 5 , 4 , 0 , 51  , 76  , 46 , 45  , 5 , 0 , 4 },
    { 287 , "SIG556" , 5 , 4 , 0 , 51  , 76  , 46 , 45  , 5 , 0 , 4 },
    { 288 , "SIG556-2" , 5 , 4 , 0 , 51  , 76  , 46 , 45  , 5 , 0 , 4 },
    { 289 ,       "R5" , 5 , 4 , 0 , 55  , 76  , 54 , 43  , 4 , 10 , 16 },
    { 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },

    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },

                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 401 ,       "诺爱尔" , 1 , 1 , 0 , 39  , 65  , 60 , 82  , 6 , 0 , 12 },
    { 402 ,    "艾尔菲尔特" , 1 , 6 , 0 , 36  , 28  , 13 , 9  , 10 , 0 , 16 , 5 , 23 },
    { 403 ,       "琪亚娜" , 1 , 1 , 0 , 31  , 64  , 53 , 76  , 6 , 3 , 12 },
    { 404 ,     "雷电芽衣" , 1 , 3 , 0 , 146  , 34  , 70 , 32  , 6 , 3 , 16 },
    { 405 ,     "布洛妮娅" , 1 , 3 , 0 , 132  , 37  , 77 , 33  , 5 , 5 , 0 },
    { 406 ,       "德丽莎" , 1 , 1 , 0 , 30  , 54  , 47 , 79  , 1 , 5 , 12 },
    { 407 ,    "无量塔姬子" , 1 , 4 , 0 , 58  , 64  , 45 , 42  , 1 , 5 , 16 },
    { 408 ,         "希儿" , 1 , 6 , 0 , 35  , 27  , 11 , 13  , 1 , 0 , 3 , 5 , 22 },
    { 409 ,       "克莉尔" , 1 , 1 , 0 , 31  , 61  , 62 , 88  , 6 , 0 , 8 },
    { 410 ,         "菲尔" , 1 , 1 , 0 , 31  , 61  , 62 , 88  , 6 , 0 , 8 },

    { 0 },{ 0 },{ 0 },{ 0 },{ 0 },{ 0 },
                        //星级/枪种/心智/伤害  /射速 /命中 /闪避 /前置/持续/冷却
    { 417 ,       "JILL" , 1 , 1 , 0 , 30  , 55  , 53 , 96  , 6 , 0 , 16 },
    { 418 ,        "SEI" , 1 , 1 , 0 , 30  , 53  , 59 , 77  , 6 , 5 , 10 },
    { 419 ,    "DOROTHY" , 1 , 2 , 0 , 28  , 79  , 15 , 87  , 1 , 0 , 2 },
    { 420 ,     "STELLA" , 1 , 3 , 0 , 117 , 35  , 84 , 36  , 6 , 5 , 8 },
    { 421 ,       "ALMA" , 1 , 5 , 0 , 89  , 129 , 31 , 23  , 8 , 4 , 18 , 9 },
    { 422 ,       "DANA" , 1 , 6 , 0 , 38  , 26  , 15 , 13  , 8 , 0 , 18 , 1 , 22},

};





//暴击(RF/SG(0.4)-AR/HG(0.2)-MG/SMG(0.05))  1HG 2SMG 3RF 4AR 5MG 6SG
void prepare()
{
    //设置暴击属性并对特殊人形提前说明
    if(doll[0].id == 4){doll[0].critical_per = 0.4;}
    else if(doll[0].id == 272){doll[0].critical_per = 0.4;}
    else if(doll[0].id == 183 || doll[0].id == 202){doll[0].critical_per = 0.4;}
    else if(doll[0].id == 273 || doll[0].id == 56 || doll[0].id == 73 || doll[0].id == 172){doll[0].critical_per = 0.3;}
    else {
        if(doll[0].type == 1){doll[0].critical_per = 0.2;}
        else if(doll[0].type == 4){doll[0].critical_per = 0.2;}
        else if(doll[0].type == 2 || doll[0].type == 5){doll[0].critical_per = 0.05;}
        else if(doll[0].type == 3 || doll[0].type == 6){doll[0].critical_per = 0.4;}
    }

    if(doll[0].type != 6){  doll[0].fire_number = 5; }

    doll[0].crit_damage_rate = 1.5;
    doll[0].armor_piercing = 15;
    doll[0].skill1_cd *= FA;
    doll[0].skill1_last *= FA;
    doll[0].skill1_before *= FA;

    doll[0].injury_reduction = 1;
    doll[0].injury_advanced = 1;
}







