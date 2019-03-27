CXX=g++
CFLAGS=-I./include -std=c++11
OBJS=src/example.o

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

bin: $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f bin $(OBJS)
