/* javaSpeak.i */
%module javaSpeak
%{
/* Put header files here or function declarations like below */
  extern int getRate(int current);
  extern int setRate(int rate);
  extern int getPitch(int current);
  extern int setPitch(int pitch);
  extern int getRange(int current);
  extern int setRange(int range);
  extern int getPunctuation(int current);
  extern int setPunctuation(int punct);
  extern int getCapitals(int current);
  extern int setCapitals(int cap);
  extern int speakText(const char *text);
  extern int speakKey(const char *key_name);
  extern int speakChar(wchar_t character);
  extern int cancel();
  extern int isTalking();
  extern int synchronize();
  extern int terminate();
  extern int initialize();
  %}

extern int getRate(int current);
extern int setRate(int rate);
extern int getPitch(int current);
extern int setPitch(int pitch);
extern int getRange(int current);
extern int setRange(int range);
extern int getPunctuation(int current);
extern int setPunctuation(int punct);
extern int getCapitals(int current);
extern int setCapitals(int cap);
extern int speakText(const char *text);
extern int speakKey(const char *key_name);
extern int speakChar(wchar_t character);
extern int cancel();
extern int isTalking();
extern int synchronize();
extern int terminate();
extern int initialize();
