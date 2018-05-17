#Turns ctest into a .so fille (Shared llibrary/DLL for dynamic linking)

CC = gcc # C compiler
AR = ar # archiver for creating .a (.lib, not static)
AR_FLAGS_CREATE = -c
AR_FLAGS_VERBOSE = -v
AR_FLAGS_APPEND = -q
AR_FLAGS = $(AR_FLAGS_CREATE) $(AR_FLAGS_VERBOSE) $(AR_FLAGS_APPEND)

CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libctest.so # target lib
TARGET_STATIC_LIB = libctest.a

SRCS = ctest1.c ctest2.c # source files, header files aren't needed and are figured out by the compiler
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB} ${TARGET_STATIC_LIB} #turns the .a into a shareablle library .so (.dll)

$(TARGET_STATIC_LIB): $(OBJS) #turns the .o files into an archived .a lib
	$(AR) $(AR_FLAGS) $@ $^

$(TARGET_LIB): $(OBJS) #tunrs the .d files into object .o files
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c #compiles .c into .d files
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d) #Not sure what this does?

.PHONY: clean
clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) ${TARGET_STATIC_LIB}