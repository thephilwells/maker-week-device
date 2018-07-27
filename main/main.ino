#include <epd2in7.h>
#include <fonts.h>
#include <epdpaint.h>
#include <epdif.h>
#include <SPI.h>

#define COLORED     0
#define UNCOLORED   1

String outerLetters[7] = {"O","M","A","D","B","R"};
String outerLetterString = "OMADBR";
String wordList[49];

int possibleScore = 188;
int playerScore = 0;
int wordsFound = 0;
String alert = "BEE excited!\0";
char alertX[50] = "BEE impressed!\0";

String centerLetter = "T";
String northwestLetter = outerLetters[0];
String northeastLetter = outerLetters[1];
String eastLetter = outerLetters[2];
String southeastLetter = outerLetters[3];
String southwestLetter = outerLetters[4];
String westLetter = outerLetters[5];

const char string_0[] PROGMEM = "ABBOT";
const char string_1[] PROGMEM = "ABORT";
const char string_2[] PROGMEM = "AORTA";
const char string_3[] PROGMEM = "ATOM";
const char string_4[] PROGMEM = "ATTAR";
const char string_5[] PROGMEM = "BOAT";
const char string_6[] PROGMEM = "BOOT";
const char string_7[] PROGMEM = "BOTTOM";
const char string_8[] PROGMEM = "BRAT";
const char string_9[] PROGMEM = "DART";
const char string_10[] PROGMEM = "DARTBOARD";
const char string_11[] PROGMEM = "DATA";
const char string_12[] PROGMEM = "DOORMAT";
const char string_13[] PROGMEM = "DOTARD";
const char string_14[] PROGMEM = "DRAT";
const char string_15[] PROGMEM = "MARMOT";
const char string_16[] PROGMEM = "MART";
const char string_17[] PROGMEM = "MATADOR";
const char string_18[] PROGMEM = "MOAT";
const char string_19[] PROGMEM = "MOOT";
const char string_20[] PROGMEM = "MORTAR";
const char string_21[] PROGMEM = "MOTOR";
const char string_22[] PROGMEM = "MOTORBOAT";
const char string_23[] PROGMEM = "MOTTO";
const char string_24[] PROGMEM = "ORATOR";
const char string_25[] PROGMEM = "RATATAT";
const char string_26[] PROGMEM = "ROBOT";
const char string_27[] PROGMEM = "ROOT";
const char string_28[] PROGMEM = "ROTATOR";
const char string_29[] PROGMEM = "ROTO";
const char string_30[] PROGMEM = "ROTOR";
const char string_31[] PROGMEM = "TABARD";
const char string_32[] PROGMEM = "TABOO";
const char string_33[] PROGMEM = "TABOR";
const char string_34[] PROGMEM = "TARO";
const char string_35[] PROGMEM = "TAROT";
const char string_36[] PROGMEM = "TART";
const char string_37[] PROGMEM = "TARTAR";
const char string_38[] PROGMEM = "TATTOO";
const char string_39[] PROGMEM = "TOAD";
const char string_40[] PROGMEM = "TOMATO";
const char string_41[] PROGMEM = "TOMB";
const char string_42[] PROGMEM = "TOOT";
const char string_43[] PROGMEM = "TORO";
const char string_44[] PROGMEM = "TORT";
const char string_45[] PROGMEM = "TRAM";
const char string_46[] PROGMEM = "TROD";
const char string_47[] PROGMEM = "TROT";
const char string_48[] PROGMEM = "MORTARBOARD";

const static char* const dictionary_table[] PROGMEM = {string_0,string_1,string_2,string_3,string_4,string_5,string_6,string_7,string_8,string_9,string_10,string_11,string_12,string_13,string_14,string_15,string_16,string_17,string_18,string_19,string_20,string_21,string_22,string_23,string_24,string_25,string_26,string_27,string_28,string_29,string_30,string_31,string_32,string_33,string_34,string_35,string_36,string_37,string_38,string_39,string_40,string_41,string_42,string_43,string_44,string_45,string_46,string_47,string_48};
const static int TEMPLATE_X_COORDS[] PROGMEM = {29,29,29,29,28,29,24,25,26,27,28,29,30,31,32,33,23,24,33,34,22,23,34,35,21,35,36,42,43,44,45,46,20,21,36,37,40,41,42,46,47,48,19,20,37,40,48,19,37,38,39,40,48,49,19,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,38,39,49,92,93,124,125,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,49,50,91,92,94,95,122,123,125,126,18,19,38,39,49,50,89,90,96,121,127,128,18,19,38,39,49,87,88,97,98,119,120,129,130,18,19,38,39,49,86,99,100,117,118,131,18,19,38,39,48,49,84,85,101,102,115,116,132,133,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,46,47,48,82,83,103,114,134,135,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,80,81,104,105,112,113,136,137,18,19,38,39,40,41,42,43,44,46,47,48,79,106,107,110,111,138,18,19,38,39,48,49,77,78,108,109,139,140,18,19,38,39,49,77,108,109,140,18,19,38,39,49,77,108,109,140,18,19,38,39,49,50,77,108,109,140,19,30,31,32,38,39,49,50,77,108,109,140,19,26,30,31,32,38,39,49,77,108,109,140,19,20,25,26,31,38,39,40,48,49,77,108,109,140,20,25,37,38,39,40,48,77,108,109,140,20,21,25,37,40,41,42,46,47,48,77,108,109,140,21,22,25,36,37,42,43,44,45,46,77,108,109,140,22,23,24,25,35,36,77,108,109,140,23,24,25,33,34,35,77,108,109,140,25,26,27,28,29,30,31,32,33,77,108,109,140,28,29,30,77,108,109,140,77,108,109,140,77,108,109,140,77,108,109,140,77,108,109,140,77,78,108,109,139,140,75,76,78,79,106,107,110,111,138,139,141,142,73,74,80,81,104,105,106,111,112,113,136,137,143,144,29,30,31,71,72,82,83,103,104,113,114,115,134,135,145,146,28,29,30,31,70,71,83,84,85,101,102,115,116,132,133,134,146,147,28,29,30,31,68,69,85,86,99,100,117,118,131,132,148,149,27,28,29,30,31,32,66,67,87,88,97,98,99,118,119,120,129,130,150,151,27,28,29,30,31,32,33,65,88,89,90,96,97,120,121,127,128,129,152,26,27,28,31,32,33,63,64,90,91,92,94,95,122,123,125,126,127,153,154,26,27,28,32,33,34,61,62,92,93,94,123,124,125,155,156,25,26,27,28,32,33,34,61,62,92,93,124,125,155,156,16,17,18,19,20,21,22,23,24,25,26,27,33,34,35,36,37,38,39,40,41,42,43,44,45,61,62,92,93,124,125,155,156,14,15,16,17,18,19,20,21,22,23,24,25,26,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,61,62,92,93,124,125,155,156,14,15,16,45,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,124,125,155,156,14,15,46,47,61,62,92,93,94,123,124,125,155,156,14,15,46,47,63,64,90,91,92,94,95,122,123,125,126,127,153,154,14,15,46,47,65,88,89,90,96,97,120,121,127,128,129,152,14,15,46,47,66,67,87,88,97,98,99,118,119,120,129,130,150,151,14,15,46,47,68,69,85,86,99,100,117,118,131,132,148,149,14,15,46,47,70,71,83,84,85,101,102,115,116,132,133,134,146,147,14,15,46,47,71,72,82,83,102,103,104,113,114,134,135,145,146,14,15,46,47,73,74,80,81,104,105,106,111,112,113,136,137,143,144,14,15,46,47,75,76,78,79,106,107,110,111,138,139,141,142,14,15,46,47,77,78,108,109,139,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,108,109,140,14,15,46,47,77,78,108,109,139,140,14,15,46,47,79,106,107,110,111,138,14,15,46,47,80,81,104,105,112,113,136,137,14,15,46,47,82,83,103,114,134,135,14,15,46,47,84,85,101,102,115,116,132,133,14,15,46,47,86,99,100,117,118,131,14,15,46,47,87,88,97,98,119,120,129,130,14,15,46,47,89,90,96,121,127,128,14,15,46,47,91,92,94,95,122,123,125,126,14,15,46,47,92,93,124,125,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,14,15,46,47,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,14,15,46,47,131,156,14,15,46,47,130,157,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,46,47,129,158,14,15,45,46,47,129,158,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,129,158,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,129,158,129,158,129,158,129,158,129,158,129,158,129,158,129,158,129,158,129,158,129,158,129,158,130,157,131,156,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155};
const static int TEMPLATE_Y_COORDS[] PROGMEM = {7,8,9,10,11,11,12,12,12,12,12,12,12,12,12,12,13,13,13,13,14,14,14,14,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31,31,32,32,32,32,32,32,32,32,32,32,32,32,33,33,33,33,33,33,33,33,33,33,33,33,34,34,34,34,34,34,34,34,34,34,34,34,34,34,35,35,35,35,35,35,35,35,35,35,35,36,36,36,36,36,36,36,36,36,36,36,36,36,36,37,37,37,37,37,37,37,37,37,37,37,37,37,37,38,38,38,38,38,38,38,38,38,38,39,39,39,39,39,39,39,39,39,39,40,40,40,40,40,40,40,40,40,40,40,40,40,41,41,41,41,41,41,41,42,42,42,42,43,43,43,43,44,44,44,44,45,45,45,45,46,46,46,46,46,46,47,47,47,47,47,47,47,47,47,47,47,47,48,48,48,48,48,48,48,48,48,48,48,48,48,48,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,59,59,59,59,59,59,59,59,59,59,59,59,59,59,60,60,60,60,60,60,60,60,60,60,60,60,61,61,61,61,61,61,61,61,61,61,61,61,62,62,62,62,62,62,62,62,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63,64,64,64,64,64,64,64,64,64,64,64,64,65,65,65,65,65,65,65,65,65,65,65,65,66,66,66,66,66,66,66,66,66,66,66,66,67,67,67,67,67,67,67,67,67,67,67,67,68,68,68,68,68,68,68,68,68,68,68,68,69,69,69,69,69,69,69,69,69,69,69,69,70,70,70,70,70,70,70,70,70,70,70,70,71,71,71,71,71,71,71,71,71,71,71,71,72,72,72,72,72,72,72,72,72,72,72,72,73,73,73,73,73,73,73,73,73,73,73,73,73,73,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,79,79,79,79,79,79,79,79,79,79,79,79,79,79,79,79,79,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,82,82,82,82,82,82,82,82,82,82,83,83,83,83,83,83,83,83,84,84,84,84,84,84,84,84,85,85,85,85,85,85,85,85,86,86,86,86,86,86,86,86,87,87,87,87,87,87,87,87,88,88,88,88,88,88,88,88,89,89,89,89,89,89,89,89,90,90,90,90,90,90,90,90,91,91,91,91,91,91,91,91,92,92,92,92,92,92,92,92,93,93,93,93,93,93,93,93,94,94,94,94,94,94,94,94,95,95,95,95,95,95,95,95,96,96,96,96,96,96,96,96,97,97,97,97,97,97,97,97,98,98,98,98,98,98,98,98,99,99,99,99,99,99,99,99,100,100,100,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,102,102,102,102,102,102,102,102,102,102,102,102,103,103,103,103,103,103,103,103,103,103,104,104,104,104,104,104,104,104,104,104,104,104,105,105,105,105,105,105,105,105,105,105,106,106,106,106,106,106,106,106,106,106,106,106,107,107,107,107,107,107,107,107,107,107,108,108,108,108,108,108,108,108,108,108,108,108,109,109,109,109,109,109,109,109,110,110,110,110,111,111,111,111,112,112,112,112,113,113,113,113,114,114,114,114,115,115,115,115,116,116,116,116,117,117,117,117,118,118,118,118,119,119,119,119,120,120,120,120,121,121,121,121,122,122,122,122,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,125,125,126,126,126,126,126,126,127,127,127,127,127,127,128,128,128,128,128,128,129,129,129,129,129,129,130,130,130,130,130,130,131,131,131,131,131,131,132,132,132,132,132,132,133,133,133,133,133,133,134,134,134,134,134,134,135,135,135,135,135,135,136,136,136,136,136,136,137,137,137,137,137,137,138,138,138,138,138,138,139,139,139,139,139,139,140,140,140,140,140,140,141,141,141,141,141,141,142,142,142,142,142,142,143,143,143,143,143,143,144,144,144,144,144,144,145,145,145,145,145,145,146,146,146,146,146,146,147,147,147,147,147,147,148,148,148,148,148,148,149,149,149,149,149,149,150,150,150,150,150,150,151,151,151,151,151,151,152,152,152,152,152,152,153,153,153,153,153,153,154,154,154,154,154,154,155,155,155,155,155,155,156,156,156,156,156,156,157,157,157,157,157,157,158,158,158,158,158,158,159,159,159,159,159,159,160,160,160,160,160,160,161,161,161,161,161,161,162,162,162,162,162,162,163,163,163,163,163,163,164,164,164,164,164,164,165,165,165,165,165,165,166,166,166,166,166,166,167,167,167,167,167,167,168,168,168,168,168,168,169,169,169,169,169,169,170,170,170,170,170,170,171,171,171,171,171,171,172,172,172,172,172,172,173,173,173,173,173,173,174,174,174,174,174,174,175,175,175,175,175,175,176,176,176,176,176,176,177,177,177,177,177,177,178,178,178,178,178,178,179,179,179,179,179,179,180,180,180,180,180,180,181,181,181,181,181,181,182,182,182,182,182,182,183,183,183,183,183,183,184,184,184,184,184,184,185,185,185,185,185,185,186,186,186,186,186,186,187,187,187,187,187,187,188,188,188,188,188,188,189,189,189,189,189,189,190,190,190,190,190,190,191,191,191,191,191,191,192,192,192,192,192,192,193,193,193,193,193,193,194,194,194,194,194,194,195,195,195,195,195,195,196,196,196,196,196,196,197,197,197,197,197,197,198,198,198,198,198,198,199,199,199,199,199,199,200,200,200,200,200,200,201,201,201,201,201,201,202,202,202,202,202,202,203,203,203,203,203,203,204,204,204,204,204,204,205,205,205,205,205,205,206,206,206,206,206,206,207,207,207,207,207,207,208,208,208,208,208,208,209,209,209,209,209,209,210,210,210,210,210,210,211,211,211,211,211,211,212,212,212,212,212,212,213,213,213,213,213,213,214,214,214,214,214,214,215,215,215,215,215,215,216,216,216,216,216,216,217,217,217,217,217,217,218,218,218,218,218,218,219,219,219,219,219,219,220,220,220,220,220,220,221,221,221,221,221,221,222,222,222,222,222,222,223,223,223,223,223,223,224,224,224,224,224,224,225,225,225,225,225,225,226,226,226,226,226,226,227,227,227,227,227,227,228,228,228,228,228,228,229,229,229,229,229,229,230,230,230,230,230,230,231,231,231,231,231,231,232,232,232,232,232,232,233,233,233,233,233,233,234,234,234,234,234,234,235,235,235,235,235,235,236,236,236,236,236,236,237,237,237,237,237,237,238,238,238,238,238,238,239,239,239,239,239,239,240,240,240,240,240,240,240,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,243,243,244,244,245,245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255,255,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,};

char pangram[12] = "MORTARBOARD";

class Button
{
  int pin;                         // Arduino address
  unsigned long previousPress;    // last time button was pressed
  int state;                       // stores current pin state
  int debounce_threshold;              // how long to wait between debounces

  public:
  // constructor
  // call once in setup()
  Button(int pinInput)
  {
    // initialize variables
    pin = pinInput;
    previousPress = millis(); // records time of last known button press
    state = HIGH;
    debounce_threshold = 200;

    // initialize hardware
    pinMode(pin, INPUT_PULLUP);
  }

  // call this frequently, in loop()
  // updates the button variables 
  // returns true if a new button-press should be registered
  bool Update()
  {
    bool returnPress = false;
    int currentState = digitalRead(pin);

    bool buttonHasBeenPressed = (currentState != state);
    int timeSinceLastPress = (millis() - previousPress);
    bool debounceThresholdHasBeenPassed = (timeSinceLastPress > debounce_threshold);
    
    if (buttonHasBeenPressed && debounceThresholdHasBeenPassed)
    {
      returnPress = (currentState == LOW);
      state = currentState;
    }

    if (returnPress){
      previousPress = millis();
      return true;
    } else {
      return false;
    }
  }

};

// set up control buttons
Button btnSubmit(12);
Button btnShuffle(5);
Button btnDelete(4);

// set up hex buttons
int hexButtonCount = 1;
Button btnsHex[1] = {3};
Button centerHex(6);

// set up logic variables
String currentWord = "";

Epd epd;
void setup()
{
  Serial.begin(9600);
  Serial.println("Outer letters: "+outerLetters[0]+outerLetters[1]+outerLetters[2]);
  Serial.println("Center letter: "+centerLetter);
  
  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  redraw();
}

void loop()
{
  // check hex button presses
  for (int i = 0; i < hexButtonCount; i++){
    bool pressed = btnsHex[i].Update();
    if (pressed){
      currentWord += outerLetters[i];
      Serial.println(currentWord);
    }
  }

  bool centerPressed = centerHex.Update();
  if (centerPressed)
  {
    currentWord += centerLetter;
    Serial.println(currentWord);
  }

  bool deletePressed = btnDelete.Update();
  if (deletePressed)
  {
    if (currentWord == "")
    {
      // do nothing
      Serial.println(currentWord);
    }
    else
    {
      currentWord.remove(currentWord.length() -1);
      Serial.println(currentWord);
    }
  }

  bool shufflePressed = btnShuffle.Update();
  if (shufflePressed)
  {
    Serial.println("Shuffling..");
    shuffle();
    Serial.println("Outer letters: "+outerLetters[0]+outerLetters[1]+outerLetters[2]);
    Serial.println("Center letter: "+centerLetter);
  }

  bool pressed = btnSubmit.Update();
  if (pressed){
    submit(currentWord);
    currentWord = "";
  }
}

void submit(String submission)
{
  // check for word in dictionary
  char buffer[12];
  bool inDictionary;
  bool isError = _validateSubmission(submission);
  if (isError == true)
  {
    inDictionary = true; // otherwise we'll get 'not in word list' alert
  }
  else
  {
    for (int i=0; i < 49; i++) {
      inDictionary = false;
  
      strcpy_P(buffer, (char*)pgm_read_word(&dictionary_table[i]));
      String buffString = String(buffer);
      if (submission == buffString)
      {
        inDictionary = true;
        // add word to list of found words
        wordList[wordsFound++] = submission;
      
        // add word value to player's score
        int wordValue = _calculateWordValue(submission);
        playerScore += wordValue;
      
        // set alert
        if (submission == String(pangram))
        {
          String tmp = "PANGRAM! +" + String(wordValue) + " ("+submission+")\0";
          tmp.toCharArray(alertX, 50);
        }
        else
        {
          alert = _mapWordValueToMessage(wordValue)+" +" + wordValue + " ("+submission+")\0";
          alert.toCharArray(alertX, 50);
        }
        // re-draw screen
  
        break;
      }
    }
  }
  if (inDictionary == false)
  {
    alert = submission+" not in word list.\0";
    alert.toCharArray(alertX, 50);
  }
  redraw();
}

bool _validateSubmission(String submission)
{
  /// too short
  if (submission.length()<4)
  {
    alert = "Too short! ("+submission+")\0";
    alert.toCharArray(alertX, 50);
    return true;
  }

  /// bad letters
  for (int i=0; i < submission.length(); i++)
  {
    String letter = String(submission.charAt(i));
    if (outerLetterString.indexOf(String(letter)) == -1)
    {
      if (letter != centerLetter)
      {
        alert = "Bad letters! ("+submission+")\0";
        alert.toCharArray(alertX, 50);
        return true;
      }
    }
  }

  /// missing center letter
  bool hasCenterLetter = false;
  for (int j=0; j < submission.length(); j++)
  {
    String letter = String(submission.charAt(j));
    if (letter == centerLetter)
    {
      hasCenterLetter = true;
      break;
    }
  }
  if (hasCenterLetter == false)
  {
    alert = "Missing key letter! ("+submission+")\0";
    alert.toCharArray(alertX, 50);
    return true;
  }

  // already found
  for (int k=0; k < 49; k++)
  {
    if (submission == wordList[k])
    {
      alert = "Already found! ("+submission+")\0";
      alert.toCharArray(alertX, 50);
      return true;
    }
  }
  
  return false;
}

int _calculateWordValue(String submission)
{
  if (submission == String(pangram))
  {
    return String(pangram).length() + 7;
  }
  if (submission.length() == 4)
  {
    return 1;
  }
  return submission.length();
}

String _mapWordValueToMessage(int value)
{
  if (value <= 4)
  {
    return "Good!";
  }
  if (value > 4 && value <=6)
  {
    return "Nice!";
  }
  return "Awesome!";
}

void shuffle()
{
  for (int i=0; i < 6; i++)
  {
    int n = random(0, 6);
    String temp = outerLetters[n];
    outerLetters[n] = outerLetters[i];
    outerLetters[i] = temp;
  }
  northwestLetter = outerLetters[0];
  northeastLetter = outerLetters[1];
  eastLetter = outerLetters[2];
  southeastLetter = outerLetters[3];
  southwestLetter = outerLetters[4];
  westLetter = outerLetters[5];
  outerLetterString = outerLetters[0] + outerLetters[1] + outerLetters[2] + outerLetters[3] + outerLetters[4] + outerLetters[5] + outerLetters[6];
}

char* str2char(String s)
{
  int n = s.length();
  char char_array[n+1];
  strcpy(char_array, s.c_str());
  return char_array;
}

void redraw()
{
    epd.ClearFrame();

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  unsigned char image[1204];
  
  Paint paint(image, 32, 176);    //width should be the multiple of 8 
  
  paint.SetRotate(ROTATE_90);

  // alert
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 6, alertX, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 10, 60, paint.GetWidth(), paint.GetHeight());
  
  // northwest letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "O", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 96, 32, paint.GetWidth(), paint.GetHeight());

  // center letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "T", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 80, 60, paint.GetWidth(), paint.GetHeight());
  
  // north letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "M", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 115, 60, paint.GetWidth(), paint.GetHeight());

  // northeast letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "A", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 96, 88, paint.GetWidth(), paint.GetHeight());

  // southwest letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "R", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 32, paint.GetWidth(), paint.GetHeight());

  // southeast letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "D", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 88, paint.GetWidth(), paint.GetHeight());

  // south letter
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "B", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 50, 60, paint.GetWidth(), paint.GetHeight());

  // score
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(9, 0, "0 / 188", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 119, 120, paint.GetWidth(), paint.GetHeight());

  // input
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(9, 0, "MORTARBOARD_", &Font16, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 120, paint.GetWidth(), paint.GetHeight());
  

  /* This displays the data from the SRAM in e-Paper module */
  epd.DisplayFrame();

  /* Deep sleep */
  epd.Sleep();
}

