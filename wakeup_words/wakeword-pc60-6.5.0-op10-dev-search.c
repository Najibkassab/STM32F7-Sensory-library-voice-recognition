/* Speech Recognition HMM Grammar file V60 for pc60 platform
 * Copyright (C) 2003-2022 Sensory, Inc. All Rights Reserved.
 * 
 *
 *            source: ./tmp/2yFxS2WhVNS8xkWIHYhyocBz9ai1/3888678165/trecs-44134638b52fbe98051baa645b171a1078b68f50.snsr
 *           created: Tue May 10 07:13:44 2022
 *   min lib version: 6.5.0
 *   operating point: 10
 *  production ready: NO - development only
 *       license key: yes
 * recognition limit: 107
 *    duration limit: 11.43 hours
 *
 * Created by VoiceHub 1.20.1
 * Project: Wake_Word_wakeword
 *
 * This model will stop working after a preset number of recognition events
 * and/or a after a preset number of audio "bricks" have been processed.
 *
 * ------------------------- DO NOT USE IN A PRODUCT -------------------------
 */

const char *wakeword_phrases[] = {WAKEWORD_PHRASE_0, WAKEWORD_PHRASE_1, WAKEWORD_PHRASE_2, WAKEWORD_PHRASE_3};
const unsigned short gs_wakeword_grammarLabel[] = {

   60,	 // 0x003c
  217,	 // 0x00d9
   66,	 // 0x0042
    0,	 // 0x0000
    2,	 // 0x0002
   64,	 // 0x0040
   32,	 // 0x0020
    0,	 // 0x0000
   32,	 // 0x0020
  179,	 // 0x00b3
  231,	 // 0x00e7
 1000,	 // 0x03e8
    0,	 // 0x0000
   27,	 // 0x001b
  200,	 // 0x00c8
 1000,	 // 0x03e8
  300,	 // 0x012c
    2,	 // 0x0002
   94,	 // 0x005e
   25,	 // 0x0019
    3,	 // 0x0003
    3,	 // 0x0003
   66,	 // 0x0042
   66,	 // 0x0042
    7,	 // 0x0007
    2,	 // 0x0002
    0,	 // 0x0000
    7,	 // 0x0007
    0,	 // 0x0000
    0,	 // 0x0000
    1,	 // 0x0001
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
28771,	 // 0x7063
  102,	 // 0x0066
  106,	 // 0x006a
  294,	 // 0x0126
  344,	 // 0x0158
  350,	 // 0x015e
  356,	 // 0x0164
  488,	 // 0x01e8
  620,	 // 0x026c
  648,	 // 0x0288
    0,	 // 0x0000
  664,	 // 0x0298
  678,	 // 0x02a6
  690,	 // 0x02b2
    0,	 // 0x0000
  954,	 // 0x03ba
 1700,	 // 0x06a4
 1800,	 // 0x0708
    6,	 // 0x0006
32771,	 // 0x8003
    8,	 // 0x0008
32773,	 // 0x8005
    7,	 // 0x0007
32772,	 // 0x8004
    3,	 // 0x0003
32768,	 // 0x8000
    4,	 // 0x0004
32770,	 // 0x8002
    5,	 // 0x0005
32769,	 // 0x8001
   16,	 // 0x0010
32779,	 // 0x800b
    8,	 // 0x0008
    7,	 // 0x0007
32774,	 // 0x8006
   20,	 // 0x0014
32783,	 // 0x800f
   18,	 // 0x0012
32782,	 // 0x800e
   22,	 // 0x0016
32785,	 // 0x8011
   11,	 // 0x000b
32777,	 // 0x8009
   14,	 // 0x000e
32780,	 // 0x800c
   24,	 // 0x0018
32789,	 // 0x8015
   15,	 // 0x000f
32778,	 // 0x800a
   17,	 // 0x0011
32781,	 // 0x800d
   28,	 // 0x001c
32794,	 // 0x801a
   22,	 // 0x0016
   20,	 // 0x0014
32786,	 // 0x8012
   21,	 // 0x0015
32787,	 // 0x8013
   30,	 // 0x001e
32795,	 // 0x801b
   26,	 // 0x001a
32791,	 // 0x8017
   33,	 // 0x0021
32799,	 // 0x801f
   27,	 // 0x001b
32793,	 // 0x8019
   37,	 // 0x0025
32803,	 // 0x8023
   31,	 // 0x001f
32797,	 // 0x801d
   38,	 // 0x0026
32804,	 // 0x8024
   35,	 // 0x0023
32800,	 // 0x8020
   36,	 // 0x0024
32802,	 // 0x8022
   43,	 // 0x002b
32809,	 // 0x8029
   45,	 // 0x002d
32810,	 // 0x802a
   41,	 // 0x0029
32807,	 // 0x8027
   48,	 // 0x0030
32815,	 // 0x802f
   42,	 // 0x002a
32808,	 // 0x8028
   51,	 // 0x0033
32817,	 // 0x8031
   47,	 // 0x002f
32812,	 // 0x802c
   54,	 // 0x0036
32820,	 // 0x8034
   49,	 // 0x0031
32814,	 // 0x802e
   58,	 // 0x003a
32824,	 // 0x8038
   52,	 // 0x0034
32818,	 // 0x8032
   59,	 // 0x003b
32825,	 // 0x8039
   56,	 // 0x0038
32821,	 // 0x8035
   57,	 // 0x0039
32823,	 // 0x8037
   64,	 // 0x0040
32830,	 // 0x803e
   65,	 // 0x0041
32831,	 // 0x803f
   62,	 // 0x003e
32828,	 // 0x803c
   63,	 // 0x003f
32829,	 // 0x803d
  104,	 // 0x0068
  105,	 // 0x0069
   95,	 // 0x005f
   98,	 // 0x0062
  114,	 // 0x0072
   97,	 // 0x0061
   99,	 // 0x0063
  101,	 // 0x0065
  108,	 // 0x006c
  101,	 // 0x0065
  116,	 // 0x0074
    0,	 // 0x0000
  104,	 // 0x0068
  101,	 // 0x0065
  121,	 // 0x0079
   95,	 // 0x005f
   98,	 // 0x0062
  114,	 // 0x0072
   97,	 // 0x0061
   99,	 // 0x0063
  101,	 // 0x0065
  108,	 // 0x006c
  101,	 // 0x0065
  116,	 // 0x0074
    0,	 // 0x0000
   65,	 // 0x0041
   64,	 // 0x0040
65535,	 // 0xffff
    0,	 // 0x0000
    0,	 // 0x0000
   12,	 // 0x000c
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
21632,	 // 0x5480
 3109,	 // 0x0c25
 3117,	 // 0x0c2d
 2940,	 // 0x0b7c
 2717,	 // 0x0a9d
 2620,	 // 0x0a3c
 2666,	 // 0x0a6a
 2794,	 // 0x0aea
 2773,	 // 0x0ad5
 2783,	 // 0x0adf
 2598,	 // 0x0a26
 2998,	 // 0x0bb6
 2203,	 // 0x089b
 2956,	 // 0x0b8c
 2786,	 // 0x0ae2
 2407,	 // 0x0967
 2497,	 // 0x09c1
 2414,	 // 0x096e
 2389,	 // 0x0955
 2584,	 // 0x0a18
 2214,	 // 0x08a6
 2595,	 // 0x0a23
 1923,	 // 0x0783
 2547,	 // 0x09f3
 2395,	 // 0x095b
 2008,	 // 0x07d8
 1951,	 // 0x079f
 2032,	 // 0x07f0
 2180,	 // 0x0884
 2239,	 // 0x08bf
 2059,	 // 0x080b
 2330,	 // 0x091a
 1863,	 // 0x0747
 2399,	 // 0x095f
 1850,	 // 0x073a
 1916,	 // 0x077c
 2385,	 // 0x0951
 2205,	 // 0x089d
 2511,	 // 0x09cf
 2347,	 // 0x092b
 2494,	 // 0x09be
 2488,	 // 0x09b8
 2572,	 // 0x0a0c
 2592,	 // 0x0a20
 2729,	 // 0x0aa9
 2713,	 // 0x0a99
 2668,	 // 0x0a6c
 2702,	 // 0x0a8e
 2887,	 // 0x0b47
 3044,	 // 0x0be4
 2598,	 // 0x0a26
 3094,	 // 0x0c16
 2719,	 // 0x0a9f
 3063,	 // 0x0bf7
 2704,	 // 0x0a90
 3167,	 // 0x0c5f
 3039,	 // 0x0bdf
 2797,	 // 0x0aed
 2989,	 // 0x0bad
 2916,	 // 0x0b64
 3138,	 // 0x0c42
 3187,	 // 0x0c73
 3025,	 // 0x0bd1
 3096,	 // 0x0c18
 3004,	 // 0x0bbc
 2896,	 // 0x0b50
 2796,	 // 0x0aec
    1,	 // 0x0001
    2,	 // 0x0002
    1,	 // 0x0001
    3,	 // 0x0003
    1,	 // 0x0001
    1,	 // 0x0001
    1,	 // 0x0001
    4,	 // 0x0004
    1,	 // 0x0001
    7,	 // 0x0007
    1,	 // 0x0001
    6,	 // 0x0006
    1,	 // 0x0001
    5,	 // 0x0005
  169,	 // 0x00a9
    1,	 // 0x0001
    2,	 // 0x0002
    1,	 // 0x0001
  169,	 // 0x00a9
    1,	 // 0x0001
    2,	 // 0x0002
    2,	 // 0x0002
   13,	 // 0x000d
   12,	 // 0x000c
   10,	 // 0x000a
    2,	 // 0x0002
    1,	 // 0x0001
    0,	 // 0x0000
65535,	 // 0xffff
 2807,	 // 0x0af7
 2807,	 // 0x0af7
 2807,	 // 0x0af7
 2807,	 // 0x0af7
 2807,	 // 0x0af7
 2807,	 // 0x0af7
   32,	 // 0x0020
   96,	 // 0x0060
   31,	 // 0x001f
  111,	 // 0x006f
   35,	 // 0x0023
   91,	 // 0x005b
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   35,	 // 0x0023
   82,	 // 0x0052
   32,	 // 0x0020
   96,	 // 0x0060
    0,	 // 0x0000
    0,	 // 0x0000
   31,	 // 0x001f
  111,	 // 0x006f
   35,	 // 0x0023
   91,	 // 0x005b
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   34,	 // 0x0022
  170,	 // 0x00aa
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   35,	 // 0x0023
   82,	 // 0x0052
    0,	 // 0x0000
    0,	 // 0x0000
   50,	 // 0x0032
  310,	 // 0x0136
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   34,	 // 0x0022
  170,	 // 0x00aa
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   39,	 // 0x0027
  276,	 // 0x0114
    0,	 // 0x0000
    0,	 // 0x0000
   50,	 // 0x0032
  310,	 // 0x0136
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   39,	 // 0x0027
  276,	 // 0x0114
   30,	 // 0x001e
  196,	 // 0x00c4
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   30,	 // 0x001e
  196,	 // 0x00c4
    0,	 // 0x0000
    0,	 // 0x0000
   35,	 // 0x0023
  118,	 // 0x0076
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   35,	 // 0x0023
  118,	 // 0x0076
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   40,	 // 0x0028
  313,	 // 0x0139
    0,	 // 0x0000
    0,	 // 0x0000
   39,	 // 0x0027
  276,	 // 0x0114
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   34,	 // 0x0022
  150,	 // 0x0096
   34,	 // 0x0022
  150,	 // 0x0096
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   25,	 // 0x0019
 1536,	 // 0x0600
   34,	 // 0x0022
32768,	 // 0x8000
65535,	 // 0xffff
   25,	 // 0x0019
 1664,	 // 0x0680
   37,	 // 0x0025
32770,	 // 0x8002
65535,	 // 0xffff
   25,	 // 0x0019
 1792,	 // 0x0700
   40,	 // 0x0028
32772,	 // 0x8004
65535,	 // 0xffff
    0,	 // 0x0000
    0,	 // 0x0000
   36,	 // 0x0024
    6,	 // 0x0006
    0,	 // 0x0000
    0,	 // 0x0000
    0,	 // 0x0000
   42,	 // 0x002a
    7,	 // 0x0007
    2,	 // 0x0002
    0,	 // 0x0000
    1,	 // 0x0001
   39,	 // 0x0027
    8,	 // 0x0008
    1,	 // 0x0001
    0,	 // 0x0000
    0,	 // 0x0000
   35,	 // 0x0023
    9,	 // 0x0009
32774,	 // 0x8006
    0,	 // 0x0000
    0,	 // 0x0000
   41,	 // 0x0029
    9,	 // 0x0009
32776,	 // 0x8008
    0,	 // 0x0000
    0,	 // 0x0000
   38,	 // 0x0026
    9,	 // 0x0009
32778,	 // 0x800a
   16,	 // 0x0010
 1920,	 // 0x0780
   43,	 // 0x002b
32780,	 // 0x800c
32782,	 // 0x800e
   25,	 // 0x0019
 1281,	 // 0x0501
   30,	 // 0x001e
32785,	 // 0x8011
65535,	 // 0xffff
    0,	 // 0x0000
    2,	 // 0x0002
   45,	 // 0x002d
   16,	 // 0x0010
    9,	 // 0x0009
   25,	 // 0x0019
 1409,	 // 0x0581
   33,	 // 0x0021
32787,	 // 0x8013
65535,	 // 0xffff
   25,	 // 0x0019
  257,	 // 0x0101
    6,	 // 0x0006
32789,	 // 0x8015
65535,	 // 0xffff
    0,	 // 0x0000
    1,	 // 0x0001
   32,	 // 0x0020
   18,	 // 0x0012
   12,	 // 0x000c
    0,	 // 0x0000
    0,	 // 0x0000
   29,	 // 0x001d
   20,	 // 0x0014
   10,	 // 0x000a
    0,	 // 0x0000
    0,	 // 0x0000
   44,	 // 0x002c
   19,	 // 0x0013
32791,	 // 0x8017
    0,	 // 0x0000
    0,	 // 0x0000
    5,	 // 0x0005
   22,	 // 0x0016
   13,	 // 0x000d
    0,	 // 0x0000
    0,	 // 0x0000
   31,	 // 0x001f
   23,	 // 0x0017
32793,	 // 0x8019
   16,	 // 0x0010
 2051,	 // 0x0803
   46,	 // 0x002e
32795,	 // 0x801b
   16,	 // 0x0010
    0,	 // 0x0000
    0,	 // 0x0000
   28,	 // 0x001c
   23,	 // 0x0017
32797,	 // 0x801d
    0,	 // 0x0000
    1,	 // 0x0001
   48,	 // 0x0030
   24,	 // 0x0018
   19,	 // 0x0013
    0,	 // 0x0000
    0,	 // 0x0000
    4,	 // 0x0004
   23,	 // 0x0017
32799,	 // 0x801f
   16,	 // 0x0010
  896,	 // 0x0380
   21,	 // 0x0015
32801,	 // 0x8021
32803,	 // 0x8023
    0,	 // 0x0000
    3,	 // 0x0003
   47,	 // 0x002f
   25,	 // 0x0019
32806,	 // 0x8026
   16,	 // 0x0010
 2180,	 // 0x0884
   49,	 // 0x0031
32808,	 // 0x8028
   24,	 // 0x0018
    0,	 // 0x0000
    2,	 // 0x0002
   20,	 // 0x0014
   28,	 // 0x001c
   23,	 // 0x0017
    0,	 // 0x0000
    4,	 // 0x0004
   51,	 // 0x0033
   30,	 // 0x001e
   25,	 // 0x0019
    0,	 // 0x0000
    0,	 // 0x0000
   19,	 // 0x0013
   29,	 // 0x001d
32810,	 // 0x802a
   16,	 // 0x0010
 1027,	 // 0x0403
   24,	 // 0x0018
32812,	 // 0x802c
   28,	 // 0x001c
    0,	 // 0x0000
    4,	 // 0x0004
   50,	 // 0x0032
   32,	 // 0x0020
32814,	 // 0x802e
    0,	 // 0x0000
    1,	 // 0x0001
   23,	 // 0x0017
   33,	 // 0x0021
   29,	 // 0x001d
   16,	 // 0x0010
  645,	 // 0x0285
   15,	 // 0x000f
32816,	 // 0x8030
   30,	 // 0x001e
    0,	 // 0x0000
    3,	 // 0x0003
   22,	 // 0x0016
   34,	 // 0x0022
32818,	 // 0x8032
   16,	 // 0x0010
 1156,	 // 0x0484
   27,	 // 0x001b
32820,	 // 0x8034
   33,	 // 0x0021
    0,	 // 0x0000
    5,	 // 0x0005
   14,	 // 0x000e
   37,	 // 0x0025
   32,	 // 0x0020
    0,	 // 0x0000
    4,	 // 0x0004
   26,	 // 0x001a
   38,	 // 0x0026
   34,	 // 0x0022
    0,	 // 0x0000
    5,	 // 0x0005
   13,	 // 0x000d
   40,	 // 0x0028
32822,	 // 0x8036
    0,	 // 0x0000
    4,	 // 0x0004
   25,	 // 0x0019
   39,	 // 0x0027
32824,	 // 0x8038
   16,	 // 0x0010
 2309,	 // 0x0905
   52,	 // 0x0034
32826,	 // 0x803a
   38,	 // 0x0026
   16,	 // 0x0010
  131,	 // 0x0083
    3,	 // 0x0003
32828,	 // 0x803c
   37,	 // 0x0025
    0,	 // 0x0000
    5,	 // 0x0005
   54,	 // 0x0036
   43,	 // 0x002b
   39,	 // 0x0027
    0,	 // 0x0000
    6,	 // 0x0006
    2,	 // 0x0002
   45,	 // 0x002d
   40,	 // 0x0028
    0,	 // 0x0000
    5,	 // 0x0005
   53,	 // 0x0035
   44,	 // 0x002c
32830,	 // 0x803e
   16,	 // 0x0010
 2435,	 // 0x0983
   55,	 // 0x0037
32832,	 // 0x8040
   43,	 // 0x002b
    0,	 // 0x0000
    3,	 // 0x0003
    1,	 // 0x0001
   46,	 // 0x002e
32834,	 // 0x8042
   16,	 // 0x0010
  513,	 // 0x0201
   12,	 // 0x000c
32836,	 // 0x8044
   45,	 // 0x002d
    0,	 // 0x0000
    6,	 // 0x0006
   57,	 // 0x0039
   48,	 // 0x0030
   44,	 // 0x002c
    0,	 // 0x0000
    3,	 // 0x0003
   56,	 // 0x0038
   50,	 // 0x0032
32838,	 // 0x8046
    0,	 // 0x0000
    0,	 // 0x0000
   11,	 // 0x000b
   51,	 // 0x0033
   46,	 // 0x002e
   16,	 // 0x0010
 2561,	 // 0x0a01
   58,	 // 0x003a
32840,	 // 0x8048
   48,	 // 0x0030
    0,	 // 0x0000
    1,	 // 0x0001
   10,	 // 0x000a
   53,	 // 0x0035
32842,	 // 0x804a
    0,	 // 0x0000
    0,	 // 0x0000
   60,	 // 0x003c
   54,	 // 0x0036
   50,	 // 0x0032
   16,	 // 0x0010
  388,	 // 0x0184
    9,	 // 0x0009
32844,	 // 0x804c
   51,	 // 0x0033
    0,	 // 0x0000
    1,	 // 0x0001
   59,	 // 0x003b
   55,	 // 0x0037
32846,	 // 0x804e
   16,	 // 0x0010
 2693,	 // 0x0a85
   61,	 // 0x003d
32848,	 // 0x8050
   54,	 // 0x0036
    0,	 // 0x0000
    4,	 // 0x0004
    8,	 // 0x0008
   58,	 // 0x003a
   53,	 // 0x0035
    0,	 // 0x0000
    5,	 // 0x0005
   63,	 // 0x003f
   59,	 // 0x003b
   55,	 // 0x0037
    0,	 // 0x0000
    4,	 // 0x0004
    7,	 // 0x0007
   61,	 // 0x003d
32850,	 // 0x8052
    0,	 // 0x0000
    5,	 // 0x0005
   62,	 // 0x003e
   60,	 // 0x003c
32852,	 // 0x8054
   16,	 // 0x0010
  769,	 // 0x0301
   18,	 // 0x0012
32854,	 // 0x8056
   59,	 // 0x003b
   16,	 // 0x0010
  769,	 // 0x0301
   18,	 // 0x0012
32856,	 // 0x8058
   58,	 // 0x003a
    0,	 // 0x0000
    3,	 // 0x0003
   17,	 // 0x0011
   64,	 // 0x0040
   60,	 // 0x003c
    0,	 // 0x0000
    3,	 // 0x0003
   17,	 // 0x0011
   65,	 // 0x0041
   61,	 // 0x003d
    0,	 // 0x0000
    1,	 // 0x0001
   16,	 // 0x0010
65535,	 // 0xffff
32858,	 // 0x805a
    0,	 // 0x0000
    1,	 // 0x0001
   16,	 // 0x0010
65535,	 // 0xffff
32860,	 // 0x805c
};
