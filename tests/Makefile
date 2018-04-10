LDFLAGS = -L/usr/local/lib

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
DEPS = fluid.o pipe.o

CFLAGS = $(shell sdl2-config --cflags)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

testPipe: testPipe.o $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
