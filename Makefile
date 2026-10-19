CC      = gcc
CFLAGS  = -Iinclude -fPIC
PREFIX ?= $(HOME)/.local

SRCS    = $(wildcard src/*.c)
OBJS    = $(patsubst src/%.c, build/%.o, $(SRCS))

.PHONY: all clean run test install dirs



all: dirs lib/libapp.a lib/libapp.so bin/client

dirs:
	@mkdir -p build lib bin

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

lib/libapp.a: $(OBJS)
	$(AR) rcs $@ $^

lib/libapp.so: $(OBJS)
	$(CC) -shared -o $@ $^

bin/client: apps/main.c lib/libapp.a
	$(CC) $(CFLAGS) $< -Llib -lapp -o $@

clean:
	rm -rf build/* lib/* bin/*

run: bin/client
	./bin/client

bin/test: tests/test_main.c lib/libapp.a
	$(CC) $(CFLAGS) $< -Llib -lapp -o $@

test: bin/test
	./bin/test

install: all
	mkdir -p $(PREFIX)/include $(PREFIX)/lib
	cp include/*.h $(PREFIX)/include/
	cp lib/libapp.* $(PREFIX)/lib/