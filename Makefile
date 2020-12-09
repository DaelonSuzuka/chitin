MAKEFLAGS += -s

FILES := src/main.c 
FILES += src/shell/shell.c 
FILES += src/shell/shell_keys.c 
FILES += src/shell/shell_cursor.c 
FILES += src/shell/shell_command_processor.c
FILES += src/shell/shell_history.c
FILES += src/shell/shell_builtins.c


run: 
	clang -pthread -lm -Isrc -o main $(FILES)
	./main