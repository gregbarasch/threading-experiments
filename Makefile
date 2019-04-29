default: build

mkbin:
	@mkdir -p bin

build: mkbin
	@echo "Working..."
	@gcc -pthread src/without_locks.c -o bin/without
	@gcc -pthread src/inside_loop.c -o bin/inside
	@gcc -pthread src/outside_loop.c -o bin/outside
	@echo "Done."


build2: mkbin
	@gcc -pthread src/without_locks.c -o bin/without
	@gcc -pthread src/inside_loop.c -o bin/inside
	@gcc -pthread src/outside_loop.c -o bin/outside


clean:
	@echo "Working..."
	@rm -rf bin 
	@echo "Done."


without: build2
	@bin/without


inside: build2
	@bin/inside


outside: build2
	@bin/outside
