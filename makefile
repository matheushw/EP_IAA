# Matheus Barcellos de Castro Cunha   		NUSP: 11208238

FLAGS = -pthread -Wall -pedantic -g -std=c99 -D _POSIX_C_SOURCE=199309L
OBJS = sort.o
EXEC = sort

.PHONY: clean

all: sort

sort: $(OBJS)
	$(CXX) $(FLAGS) $^ -o $@
	make clean

%.o: %.c
	$(CXX) $(FLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *~