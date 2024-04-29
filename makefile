CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
EXEC = main
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEPS = $(wildcard header/*.h)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(DEPS)
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(EXEC)
	rm -rf obj

format:
	@for file in $(SRC) $(DEPS); do \
		clang-format -i $$file; \
	done
