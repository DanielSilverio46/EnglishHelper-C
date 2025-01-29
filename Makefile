CC = clang
CFLAGS = -g
RM = rm -f

MAKEDIROS = ""
OS := $(shell uname)

ifeq ($(OS),Windows_NT)
	MAKEDIROS = make_dir_windows

	MAIN = windows
	OUT = bin/single/"english helper.exe"
endif

ifeq ($(OS),Linux)
	MAKEDIROS = make_dir_linux

	CFLAGS += -lX11
	MAIN = linux
	OUT = bin/linux/"english helper.o"
endif

default: make_dir_bin $(MAKEDIROS) build

make_dir_bin:
	if [ ! -d ./bin/ ]; then mkdir bin; fi

make_dir_linux:
	if [ ! -d ./bin/linux/ ]; then \
		mkdir ./bin/linux; \
	fi \

make_dir_windows:
	if [ ! -d ./bin/dll/ ]; then \
		mkdir ./bin/dll; \
	fi \
	if [! -d ./bin/single]; then \
		mkdir ./bin/dll; \
	fi \

build:
	$(CC) $(CFLAGS) -o $(OUT) src/$(MAIN).c
