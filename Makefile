.PHONY: build

build:
	gcc -Wall -shared -fPIC -undefined dynamic_lookup -o password.so src/password.c
