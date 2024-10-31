build-dll:
	if [ ! -d ./bin/ ]; then \
	mkdir bin; \
	fi

	clang -D_CRT_SECURE_NO_DEPRECATE -Wdeprecated-declarations -v -g -shared -lcomctl32 -luser32 -lgdi32 -o bin/flow.dll src/window_flow.c src/word.c; \
	clang -D_CRT_SECURE_NO_DEPRECATE -Wdeprecated-declarations -g -lbin/flow -luser32 -o bin/english.exe src/main.c; \