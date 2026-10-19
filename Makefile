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
	$(CC) -shared -o $@ $^ -lm

bin/client: app/main.c lib/libapp.a
	$(CC) $(CFLAGS) $< -Llib -lapp -lm -o $@

clean:
	rm -rf build/* lib/* bin/*

run: bin/client
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./bin/client

TEST_SRCS = $(wildcard tests/*.c)
bin/test: $(TEST_SRCS) lib/libapp.a
	@mkdir -p bin
	$(CC) $(CFLAGS) $(TEST_SRCS) -Llib -lapp -lm -o $@

test: bin/test
	LD_LIBRARY_PATH=lib:$$LD_LIBRARY_PATH ./bin/test

install: all
	mkdir -p $(PREFIX)/include $(PREFIX)/lib
	cp include/*.h $(PREFIX)/include/
	cp lib/libapp.* $(PREFIX)/lib/