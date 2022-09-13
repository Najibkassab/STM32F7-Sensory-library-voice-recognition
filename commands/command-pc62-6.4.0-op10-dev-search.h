/* Speech Recognition HMM Grammar Vocabulary Description file
 * Copyright (C) 2003-2022 Sensory, Inc. All Rights Reserved.
 * 
 *
 *            source: ./tmp/2yFxS2WhVNS8xkWIHYhyocBz9ai1/536171638/trecs-en_US_12-11-0-1_488f1ff14fbdbfd780ddfb576eeeddf125e8f729.snsr
 *           created: Thu Sep  8 16:58:08 2022
 *   min lib version: 6.4.0
 *   operating point: 10
 *  production ready: NO - development only
 *       license key: yes
 * recognition limit: 107
 *    duration limit: 11.43 hours
 *
 * Created by VoiceHub 1.23.0
 * Project: Command_Set_command
 *
 * This model will stop working after a preset number of recognition events
 * and/or a after a preset number of audio "bricks" have been processed.
 *
 * ------------------------- DO NOT USE IN A PRODUCT -------------------------
 */

//extern u32 gs_command_grammarLabel;
#ifndef NETLABEL
#define NETLABEL
//extern u32 dnn_command_netLabel;
#endif

/* The following phrases (Hex format) correspond to the word IDs emitted by the recognizer. */
#define COMMAND_PHRASE_COUNT 10
#define COMMAND_PHRASE_0 "SILENCE"	/* Legacy system phrase */
#define COMMAND_PHRASE_1 "\x63\x61\x70\x74\x75\x72\x65"	/* Phrase: capture */
#define COMMAND_PHRASE_2 "\x73\x68\x6F\x6F\x74"	/* Phrase: shoot */
#define COMMAND_PHRASE_3 "\x63\x61\x6D\x65\x72\x61\x5F\x6F\x6E"	/* Phrase: camera_on */
#define COMMAND_PHRASE_4 "\x63\x61\x6D\x65\x72\x61\x5F\x6F\x66\x66"	/* Phrase: camera_off */
#define COMMAND_PHRASE_5 "\x70\x6F\x77\x65\x72\x5F\x6F\x6E"	/* Phrase: power_on */
#define COMMAND_PHRASE_6 "\x70\x6F\x77\x65\x72\x5F\x6F\x66\x66"	/* Phrase: power_off */
#define COMMAND_PHRASE_7 "\x73\x6C\x65\x65\x70\x5F\x6D\x6F\x64\x65\x5F\x6F\x6E"	/* Phrase: sleep_mode_on */
#define COMMAND_PHRASE_8 "\x73\x6C\x65\x65\x70\x5F\x6D\x6F\x64\x65\x5F\x6F\x66\x66"	/* Phrase: sleep_mode_off */
#define COMMAND_PHRASE_9 "nota"	/* Legacy system phrase */
