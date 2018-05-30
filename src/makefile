ifeq ($(shell uname), Linux)
  CC         = g++ -fPIC 
  LIBLINK    = -shared 
  INCLUDEDIR = -I /opt/jdk1.8.0_111/include -I /opt/jdk1.8.0_111/include/linux
  TARGET     = libencrypt.so
endif

ifeq ($(shell uname), Darwin)
  CC		 = g++ 
  LIBLINK    = -dynamiclib
  TARGET     = libdecrypt.dylib
  INCLUDEDIR = -I/System/Library/Frameworks/JavaVM.framework/Headers
endif

OBJS = decrypt.o com_seassoon_encrypt_Encrypt.o

$(TARGET):$(OBJS)
	$(CC) $(LIBLINK) -o $(TARGET) $(OBJS)

decrypt.o: decrypt.cpp
	$(CC) $(INCLUDEDIR) -c decrypt.cpp

com_seassoon_encrypt_Encrypt.o: com_seassoon_encrypt_Encrypt.cpp com_seassoon_encrypt_Encrypt.h
	$(CC) $(INCLUDEDIR) -c com_seassoon_encrypt_Encrypt.cpp
	
.PHONY:clean
clean:
	rm $(TARGET) $(OBJS)
