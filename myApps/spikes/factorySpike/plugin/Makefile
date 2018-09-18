#Turns ctest into a .so fille (Shared llibrary/DLL for dynamic linking)

CC = g++ # C compiler

CFLAGS = -fPIC # flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libplug.so # target lib
TARGET_STATIC_LIB = libplug.a

SRCS = plug.cpp # source files, header files aren't needed and are figured out by the compiler
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB} ${TARGET_STATIC_LIB} #turns the .a into a shareablle library .so (.dll)

$(TARGET_LIB): $(OBJS) #tunrs the .d files into object .o files
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.cpp=.d):%.d:%.cpp #compiles .c into .d files
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

.PHONY: clean
clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d) ${TARGET_STATIC_LIB}