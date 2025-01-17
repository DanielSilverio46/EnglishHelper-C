build-dll:
	if [ ! -d ./bin/ ]; then \
	mkdir bin; \
	fi

	if [ ! -d ./bin/dll/ ]; then \
	mkdir bin/dll; \
	fi

	windres src/app_resources.rc -O coff -o src/app_resources.res
	clang -D_CRT_SECURE_NO_DEPRECATE -Wdeprecated-declarations -v -shared -lcomctl32 -luser32 -lgdi32 -I./include -o bin/dll/flow.dll src/user.c src/word.c src/window_flow.c; \
	clang -D_CRT_SECURE_NO_DEPRECATE -Wdeprecated-declarations -v -lbin/dll/flow -luser32 -I./include -o bin/dll/english.exe src/main.c src/app_resources.res

build:
	if [ ! -d ./bin/ ]; then \
	mkdir bin; \
	fi

	if [ ! -d ./bin/single/ ]; then \
	mkdir bin/single; \
	fi

	windres src/app_resources.rc -O coff -o src/app_resources.res
	clang -D_CRT_SECURE_NO_DEPRECATE -Wdeprecated-declarations -v -I ./include -lcomctl32 -luser32 -lgdi32 -o bin/single/english.exe src/log.c src/user.c src/window_flow.c src/word.c src/main.c src/app_resources.res
