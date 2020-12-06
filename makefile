CC=g++
CFLAGS=-std=c++11 -Wall -Werror -Wextra -o
DEPS=Bigraph.hxx Bigraph.cxx matching.cxx
TARGET=matcher
RM=rm

all: $(DEPS)
	if [ ! -e "$(TARGET)" ]; then \
		$(CC) $(CFLAGS) $(TARGET) matching.cxx; \
	fi

clean:
	$(RM) $(TARGET)
