all: time.so

time.so: time.c
	cc -bundle -undefined dynamic_lookup -o time.so time.c -Ilua_src
