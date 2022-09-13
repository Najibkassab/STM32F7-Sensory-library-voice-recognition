/* Speech Recognition HMM Grammar Vocabulary Description file
 * Copyright (C) 2003-2022 Sensory, Inc. All Rights Reserved.
 * 
 *
 *            source: ./tmp/0wMOzpdBRxfCBWlQQm9XAJmZ4ol2/3082606782/trecs-en_US_12-11-0-0_a7fcfeb44f6bf29ef3e74362ad5f0b0d3f7c63bd.snsr
 *           created: Tue Jun 21 09:07:07 2022
 *   min lib version: 6.5.0
 *   operating point: 5
 *  production ready: NO - development only
 *       license key: yes
 * recognition limit: 107
 *    duration limit: 11.43 hours
 *
 * Created by VoiceHub 1.21.8
 * Project: HomeAutoThf_wakeword
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
#define WAKEWORD_PHRASE_COUNT 3
#define WAKEWORD_PHRASE_0 "SILENCE"	/* Legacy system phrase */
#define WAKEWORD_PHRASE_1 "\x73\x65\x6E\x73\x6F\x72\x79"	/* Phrase: sensory */
#define WAKEWORD_PHRASE_2 "nota"	/* Legacy system phrase */
