#      Filename: Makefile
# Creation Date: Sunday, 01 April 2012 01:50 PM EST
# Last Modified: Sunday, 01 April 2012 03:07 PM EST
#        Author: Tim Cross <tcross@une.edu.au>
#   Description:
#

SWIG_WRAPPERS=javaSpeak.java javaSpeakJNI.java javaSpeak_wrap.c \
              SWIGTYPE_p_wchar_t.java

all : libjavaSpeak.so Main.class

libjavaSpeak.so : javaSpeak.o javaSpeak_wrap.o
	gcc -shared javaSpeak.o javaSpeak_wrap.o -o libjavaSpeak.so -l espeak 

Main.class : Main.java $(SWIG_WRAPPERS)
	javac *.java

javaSpeak.o : javaSpeak.c
	gcc -c -fpic -O2 -fno-strict-aliasing javaSpeak.c

javaSpeak_wrap.o: javaSpeak_wrap.c
	gcc -c -fpic -O2 -fno-strict-aliasing javaSpeak_wrap.c \
        -I /usr/lib/jvm/default-java/include \
        -I /usr/lib/jvm/default-java/include/linux 

$(SWIG_WRAPPERS) : javaSpeak.i
	swig -java javaSpeak.i

.PHONEY : clean
clean : 
	-rm $(SWIG_WRAPPERS) *.o *.class *.so

