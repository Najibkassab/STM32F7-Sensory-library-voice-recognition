/* Speech Recognition HMM Grammar Vocabulary Description file
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

//extern u32 gs_wakeword_grammarLabel;
#ifndef NETLABEL
#define NETLABEL
//extern u32 dnn_wakeword_netLabel;
#endif

/* The following phrases (Hex format) correspond to the word IDs emitted by the recognizer. */
#define WAKEWORD_PHRASE_COUNT 4
#define WAKEWORD_PHRASE_0 " "	/* Legacy system phrase */
#define WAKEWORD_PHRASE_1 "\x68\x69\x20\x62\x72\x61\x63\x65\x6C\x65\x74"		/* Phrase: hi_bracelet */
#define WAKEWORD_PHRASE_2 "\x68\x65\x79\x20\x62\x72\x61\x63\x65\x6C\x65\x74"	/* Phrase: hey_bracelet */
#define WAKEWORD_PHRASE_3 " "	/* Legacy system phrase */
