#include "english_time.h"
#include "string.h"

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

static const char* STR_TEEN = "teen";
static const char* STR_OH_CLOCK = "o'clock";
static const char* STR_OH = "o'";
static const char* STR_NOON = "noon";
static const char* STR_MIDNIGHT = "midnight";
static const char* STR_QUARTER = "quarter";
static const char* STR_TO = "to";
static const char* STR_PAST = "past";
static const char* STR_HALF = "half";
static const char* STR_ITS = "it's";
static const char* STR_ALMOST = "almost";
static const char* STR_JUST = "just";

void english_time_2lines(int hours, int minutes, char* str_hour, char* str_minute) {
    
  strcpy(str_hour, "");
  strcpy(str_minute, "");

  if(hours == 0) {
    strcat(str_hour,"twelve");
  }
  else {
    if (hours > 12) {
      hours = hours - 12;
    }
    strcat(str_hour, ONETEENS[hours]);
  }

  if(minutes == 0){
    strcat(str_minute,STR_OH_CLOCK);
  }
  else {
    if(minutes < 20) {
      if(minutes < 10) {
        strcat(str_minute, STR_OH);  
      }
      strcat(str_minute, ONETEENS[minutes]);
      if((minutes == 14) || (minutes > 15)) {
        strcpy(str_minute, ONETEENS[minutes-10]);
        strcat(str_minute, "\n");
        strcat(str_minute, STR_TEEN);
      }
    }
    else {
      strcat(str_minute, TWENS[((minutes/10)%10)-2]);
      if((minutes%10)>0) {
        strcat(str_minute, "\n");
        strcat(str_minute, ONETEENS[minutes%10]); 
      } 
    }
  }
}

void english_time_3lines(int hours, int minutes, char* str_hour, char* str_minute1, char* str_minute2) {
  
  strcpy(str_hour, "");
  strcpy(str_minute1, "");
  strcpy(str_minute2, "");

  if(hours == 0) {
    strcat(str_hour,"twelve");
  }
  else {
    if (hours > 12) {
      hours = hours - 12;
    }
    strcat(str_hour, ONETEENS[hours]);
  }

  if(minutes == 0){
    strcat(str_minute1,STR_OH_CLOCK);
  }
  else {
    if(minutes < 20) {
      if(minutes < 10) {
        strcat(str_minute1, STR_OH);  
      }
      strcat(str_minute1, ONETEENS[minutes]);
      if((minutes == 14) || (minutes > 15)) {
        strcpy(str_minute1, ONETEENS[minutes-10]);
        strcpy(str_minute2, STR_TEEN);
      }
    }
    else {
      strcat(str_minute1, TWENS[((minutes/10)%10)-2]);
      if((minutes%10)>0) {
        strcat(str_minute2, ONETEENS[minutes%10]); 
      } 
    }
  }
}

void fuzzy_time(int hours, int minutes, char* line1, char* line2, char* line3) {

  strcpy(line1, "");
  strcpy(line2, "");
  strcpy(line3, "");

  if (minutes > 0 && minutes < 3) {
    strcat(line1,STR_JUST);
  }
  else if ((minutes >= 3 && minutes < 8) || (minutes >= 53 && minutes < 58)) {
    strcat(line1,ONETEENS[5]);
  }
  else if ((minutes >= 8 && minutes < 13) || (minutes >= 48 && minutes < 53)) {
    strcat(line1,ONETEENS[10]);
  }
  else if ((minutes >= 13 && minutes < 18) || (minutes >= 43 && minutes < 48)) {
    strcat(line1,STR_QUARTER);
  }
  else if ((minutes >= 18 && minutes < 23) || (minutes >= 38 && minutes < 43)) {
    strcat(line1,TWENS[0]);
  }
  else if ((minutes >= 23 && minutes < 28) || (minutes >= 33 && minutes < 38)) {
    strcat(line1,TWENS[0]);
    strcat(line2, ONETEENS[5]);
    strcat(line2," ");
  }
  else if (minutes >= 28 && minutes < 33) {
    strcat(line1,STR_HALF);
  }
  else if (minutes >= 58) {
    strcat(line1,STR_ALMOST);
  }

  if (minutes >= 33) {
    // convert to next our for "to" text
    hours += 1;
    hours %= 24;  // midnight
  }    

  hours %= 12;    // only twelve hour names

  if (minutes == 0 || minutes >= 58){
    strcat(line1,STR_ITS);
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
    if(minutes < 33) {
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