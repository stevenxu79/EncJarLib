ifeq ($(shell uname), Linux)
  CC         = g++ -fPIC 
  LIBLINK    = -shared 
  INCLUDEDIR = -I /opt/jdk1.8.0_111/include -I /opt/jdk1.8.0_111/include/linux
  TARGET     = liblibEncJarLib.so
endif

ifeq ($(shell uname), Darwin)
  CC		 = g++ 
  LIBLINK    = -dynamiclib
  TARGET     = libdecrypt.dylib
  INCLUDEDIR = -I/System/Library/Frameworks/JavaVM.framework/Headers
endif

OBJS = com_seassoon_encrypt_Encrypt.o com_seassoon_encrypt_EncryptJar.o

$(TARGET):$(OBJS)
	$(CC) $(LIBLINK) -o $(TARGET) $(OBJS)



com_seassoon_encrypt_Encrypt.o: com_seassoon_encrypt_Encrypt.cpp com_seassoon_encrypt_Encrypt.h
	$(CC) $(INCLUDEDIR) -c com_seassoon_encrypt_Encrypt.cpp

com_seassoon_encrypt_EncryptJar.o: com_seassoon_encrypt_EncryptJar.cpp com_seassoon_encrypt_EncryptJar.h
	$(CC) $(INCLUDEDIR) -c com_seassoon_encrypt_EncryptJar.cpp	
	
.PHONY:clean
clean:
	rm $(TARGET) $(OBJS)
