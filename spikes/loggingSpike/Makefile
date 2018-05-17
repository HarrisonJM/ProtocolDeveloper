CC = g++ # C compiler

#g++ -std=c++11 -Wall -pedantic -g -O0 -DBOOST_LOG_DYN_LINK  -c main.cpp loggerObject.cpp

CFLAGS =-I.

#LDFLAGS = -lboost_log_setup -lboost_log -lboost_thread -lpthread -lboost_date_time
LIBLOCS = -L/usr/local/lib -I/usr/include/boost
LDFLAGS = -lboost_log_setup -lboost_log -lboost_thread -lpthread -lboost_date_time
RM = rm -f  # rm command
TARGET_OUT = logSpike.out # target lib

# source files, header files aren't needed and are figured out by the compiler
SRCS = main.cpp loggerObject.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_OUT}

$(TARGET_OUT): $(OBJS) #turns the .d files into object .o files
	$(CC) ${LDFLAGS} -o $@ $^ #tab means it is to be interpreted by the shell

$(SRCS:.cpp=.d):%.d:%.cpp #compiles .c into .d files
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^

.PHONY: clean
clean:
	${RM} ${TARGET_OUT} ${OBJS} $(SRCS:.cpp=.d) ${TARGET_STATIC_LIB}