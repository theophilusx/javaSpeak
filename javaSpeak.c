/*
  A VERY simple interface to espeak to support emacspeak. This file
  is really to be used with SWIG to generate a java interface so that then
  it can be possible to generate a clojure interface

*/

#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <espeak/speak_lib.h>

int initFlag = 0;
/* espeak_POSITION_TYPE position_type; */
espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_PLAYBACK;
/* void* user_data; */
/* t_espeak_callback *SynthCallback; */
/* espeak_PARAMETER Parm; */

/* unsigned int Size; */
/* unsigned int position= 0; */
/* unsigned int end_position= 0; */
/* unsigned int flags= espeakCHARS_AUTO | espeakENDPAUSE; */
/* unsigned int *unique_identifier; */

int getRate(int current) {
  int rate = -1;

  if ( 1 == initFlag ) {
    rate = espeak_GetParameter(espeakRATE, current);
  }
  return rate;
}

int setRate(int rate) {
  espeak_ERROR rc;

  if ( 450 < rate ) {
    rate = 450;
  } else if ( 80 > rate ) {
    rate = 80;
  }

  if ( 1 == initFlag ) {
    rc = espeak_SetParameter(espeakRATE, rate, 0);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_SetParameter(espeakRATE, rate, 0);
      return -1;
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int getPitch(int current) {
  int pitch = -1; 

  if ( 1 == initFlag ) {
    pitch = espeak_GetParameter(espeakPITCH, current);
  }
  return pitch;
}

int setPitch(int pitch) {
  espeak_ERROR rc;

  if ( 100 < pitch ) {
    pitch = 100;
  } else if ( 0 > pitch ) {
    pitch = 0;
  }

  if ( 1 == initFlag ) {
    rc = espeak_SetParameter(espeakPITCH, pitch, 0);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_SetParameter(espeakPITCH, pitch, 0);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int getRange(int current) {
  int range = -1;

  if ( 1 == initFlag ) {
    range = espeak_GetParameter(espeakRANGE, current);
  }
  return range;
}

int setRange(int range) {
  espeak_ERROR rc;

  if ( 100 < range ) {
    range = 100;
  } else if ( 0 > range ) {
    range = 0;
  }

  if ( 1 == initFlag ) {
    rc = espeak_SetParameter(espeakRANGE, range, 0);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_SetParameter(espeakRANGE, range, 0);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int getPunctuation(int current) {
  int punct = -1;

  if ( 1 == initFlag ) {
    punct = espeak_GetParameter(espeakPUNCTUATION, current);
  }
  return punct;
}

int setPunctuation(int punct) {
  espeak_ERROR rc;

  if ( 0 != punct 
       || 1 != punct
       || 2 != punct ) {
    punct = 2;
  }

  if ( 1 == initFlag ) {
    rc = espeak_SetParameter(espeakPUNCTUATION, punct, 0);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_SetParameter(espeakPUNCTUATION, punct, 0);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int getCapitals(int current) {
  int cap;

  if ( 1 == initFlag ) {
    cap = espeak_GetParameter(espeakCAPITALS, current);
  }
  return cap;
}

int setCapitals(int cap) {
  espeak_ERROR rc;

  if ( 3 <= cap ) {
    cap = 10;
  } else if ( 2 != cap
	      || 1 != cap
	      || 0 != cap ) {
    cap = 0;
  }

  if ( 1 == initFlag ) {
    rc = espeak_SetParameter(espeakCAPITALS, cap, 0);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_SetParameter(espeakCAPITALS, cap, 0);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int speakText(const char *text) {
  size_t size;
  unsigned int pos = 0;
  espeak_POSITION_TYPE pos_type = POS_CHARACTER;
  unsigned int pos_end = 0;
  unsigned int flags = espeakCHARS_AUTO | espeakENDPAUSE | espeakSSML;
  unsigned int unique_id = 0;
  void *user_data = NULL;
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    size = strlen(text) + 1;
    rc = espeak_Synth(text, size, pos, pos_type, pos_end, flags, &unique_id, 
		      user_data);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_Synth(text, size, pos, pos_type, pos_end, flags, &unique_id, 
			user_data);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}
      
int speakKey(const char *key_name) {
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    rc = espeak_Key(key_name);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_Key(key_name);      
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int speakChar(wchar_t character) {
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    rc = espeak_Char(character);
    if ( EE_BUFFER_FULL == rc ) {
      sleep(3);
      rc = espeak_Char(character);
      if ( EE_OK != rc ) {
	return -1;
      }
    }
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int cancel() {
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    rc = espeak_Cancel();
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int isTalking() {
  int status = 0;

  if ( 1 == initFlag ) {
    status = espeak_IsPlaying();
  }
  return status;
}

int synchronize() {
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    rc = espeak_Synchronize();
    if ( EE_INTERNAL_ERROR == rc ) {
      return -1;
    }
  }
  return 0;
}

int terminate() {
  espeak_ERROR rc;

  if ( 1 == initFlag ) {
    rc = espeak_Terminate();
    if ( EE_INTERNAL_ERROR == rc ) {
	return -1;
    }
  }
  return 0;
}

int initialize() {
  int Buflength = 512;
  int Options = 0;
  char *path = NULL;
  espeak_ERROR rc;

  if ( 1 == initFlag )
    return 0;

  rc = espeak_Initialize(output, Buflength, path, Options );
  if ( EE_INTERNAL_ERROR == rc ) {
    return -1;
  }

  initFlag = 1;
  return 0;
}

/* int main(int argc, char **argv) { */
/*   int rate; */
/*   int pitch; */
/*   wchar_t l = 'A'; */

/*   printf("Call initialize\n"); */
/*   initialize();  */
/*   /\* printf("get 1st rate"); *\/ */
/*   /\* rate = getRate(0); *\/ */
/*   /\* printf("Default rate: %d\n", rate); *\/ */
/*   /\* printf("Get second rate\n"); *\/ */
/*   /\* rate = getRate(1); *\/ */
/*   /\* printf("Current rate: %d\n", rate); *\/ */
/*   /\* setRate(300); *\/ */
/*   /\* rate = getRate(0); *\/ */
/*   /\* printf("Default rate: %d\n", rate); *\/ */
/*   /\* rate = getRate(1); *\/ */
/*   /\* printf("Real rate: %d\n", rate); *\/ */
/*   /\* pitch = getPitch(1); *\/ */
/*   /\* printf("Real Pitch: %d\n", pitch); *\/ */
/*   /\* setPitch(110); *\/ */
/*   /\* pitch = getPitch(1); *\/ */
/*   /\* printf("new pitch: %d\n", pitch); *\/ */
/*   speakChar(l); */
/*   synchronize(); */
/*   speakKey("B"); */
/*   synchronize(); */
/*   speakText("This is a very first test. Let's hope it works!"); */
/*   synchronize(); */
/*   return 0; */
/* } */

    

