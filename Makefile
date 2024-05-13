CC=g++
CFLAGS=-Wall -Werror -g
LIBS=-l sfml-graphics -l sfml-window -l sfml-system
INCLUDE_HEADERS_DIRECTORY=-Iheaders

SLUG: main.cpp
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)  

%.o: %.c                  
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

clean:
	rm -f src/*.o
	rm -f kmeans

tests : tests/main.cpp
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o test $^ $(LIBS)

.PHONY: clean tests
