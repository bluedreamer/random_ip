CPPFLAGS=-std=c++14 -ggdb3
random_ip: main.o
	$(CXX) -o $@ $?

install:
	cp random_ip ~/bin

clean:
	rm -f *.o random_ip
