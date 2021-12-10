

%.o: %.cpp $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)


	main.o: main.cpp
    $(CC) -c main.cpp main.o $(LDFLAGS)