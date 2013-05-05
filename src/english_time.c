#include "english_time.h"
#include "fuzzy_time_plus.h"

static const char* const ONETEENS[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
};

static const char* const TWENS[] = {
  "twenty",
  "thirty",
  "forty",
  "fifty",
};

static const char* STR_OH_CLOCK = "o'clock";
static const char* STR_NOON = "noon";
static const char* STR_MIDNIGHT = "midnight";
static const char* STR_FIVE = "five";
static const char* STR_TEN = "ten";
static const char* STR_QUARTER = "quarter";
static const char* STR_TWENTY = "twenty";
static const char* STR_TO = "to";
static const char* STR_PAST = "past";
static const char* STR_HALF = "half";
static const char* STR_ITS = "it's";
static const char* STR_ALMOST = "almost";
static const char* STR_JUST = "just";

void fuzzy_time(int hours, int minutes, char* line1, char* line2, char* line3) {

  strcpy(line1, "");
  strcpy(line2, "");
  strcpy(line3, "");

  if (minutes == 0) {
    strcat(line1,STR_ITS);
  }
  else if (minutes < (SHOW_FIVES ? 3 : 8)) {
    strcat(line1,STR_JUST);
  }
  else if (minutes >= (SHOW_FIVES ? 58 : 53)) {
    strcat(line1,STR_ALMOST);
  }
  else if (minutes < 8 || minutes >= 53) {
    strcat(line1,STR_FIVE);
  }
  else if (SHOW_FIVES && (minutes < 13 || minutes >= 48)) {
    strcat(line1,STR_TEN);
  }
  else if (minutes < (SHOW_FIVES ? 18 : 23) || minutes >= (SHOW_FIVES ? 43 : 38)) {
    strcat(line1,STR_QUARTER);
  }
  else if (SHOW_FIVES && (minutes < 28 || minutes >= 33)) {
		strcat(line1,STR_TWENTY);
		if ((minutes >= 23 && minutes < 28) || (minutes >= 33 && minutes < 38)) {
			strcat(line2,STR_FIVE);
			strcat(line2," ");
		}
	}
  else  {
    strcat(line1,STR_HALF);
  }

  if (minutes >= (SHOW_FIVES ? 33 : 38)) {
    // convert to next hour for "to" text
    hours += 1;
    hours %= 24;  // midnight --> 0
  }    

  if (hours > 12) { // leave noon as 12
    hours -= 12;  // only twelve hour names
  }

  if (minutes == 0 || minutes >= (SHOW_FIVES ? 58 : 53)){
    if (hours == 0) {
      strcat(line2, STR_MIDNIGHT);
    }
    else if (hours == 12) {
      strcat(line2, STR_NOON);
    }
    else {
      strcat(line2, ONETEENS[hours]);
      strcat(line3, STR_OH_CLOCK);
    }
  }
  else {
    if(minutes < (SHOW_FIVES ? 33 : 38)) {
      strcat(line2,STR_PAST);
    }
    else {
      strcat(line2,STR_TO);
    }

    if(hours == 0) {
      strcat(line3, STR_MIDNIGHT);
    }
    else if (hours == 12) {
      strcat(line3, STR_NOON);
    }
    else {
      strcat(line3, ONETEENS[hours]);
    }
  }
  
}