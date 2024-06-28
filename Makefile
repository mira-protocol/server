SRC    = $(wildcard server/*.c) $(wildcard server/**/*.c)
DEPS   = $(wildcard server/*.h) $(wildcard server/**/*.h)
DEPS  += $(wildcard mira_server/*)
OBJ    = $(addsuffix .o,$(subst server/,bin/,$(basename ${SRC})))
OUT    = mira-server
FLAGS  = -std=c99 -Wall -Wextra -pedantic -g -I.
LIBS   = -lpthread

compile: ./bin $(OBJ) $(SRC) $(DEPS)
	$(CC) $(OBJ) $(LIBS) -o $(OUT)

./bin:
	mkdir -p bin

bin/%.o: server/%.c $(DEPS)
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm -r bin/* $(OUT)
	if [ -f bin ]; then rm -r bin; fi
	if [ -f $(OUT) ]; then rm $(OUT); fi


