CPPFLAGS=-std=c++14 -ggdb3
random_ip: main.o
	$(CXX) -o $@ $?

clean:
	rm -f *.o random_ip
