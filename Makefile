CFLAGS = -std=c11 -pedantic -Wall -Wextra

CC = gcc
CPP = g++

MODULES = htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c htab_for_each.c htab_free.c htab_hash_function.c htab_init.c htab_lookup_add.c htab_size.c htab_statistics.c
MODULES_O = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_size.o htab_statistics.o

run: wordcount wordcount-dynamic

io.o: io.c io.h
	$(CC) io.c $(CFLAGS) -c -o io.o

htab_%.o: htab_%.c htab.h htab_struct.h
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@

libhtab.a: $(MODULES) htab.h htab_struct.h
	$(CC) $(CFLAGS) -c $(MODULES)
	ar -cr $@ $(MODULES_O)
	ranlib $@

libhtab.so:
	$(CC) $(CFLAGS) -c $(MODULES) -fPIC
	$(CC) $(CFLAGS) -fPIC $(MODULES_O) -shared -o libhtab.so

wordcount.o: wordcount.c io.h htab.h
	$(CC) wordcount.c $(CFLAGS) -c -o wordcount.o

wordcount: wordcount.o libhtab.a io.o
	$(CC) wordcount.o io.o -L. -static -lhtab -o wordcount

wordcount-dynamic: wordcount.o libhtab.so io.o
	$(CC) wordcount.o io.o -Wl,-rpath . -o wordcount-dynamic libhtab.so

# PHONY targets
.PHONY clean:
rm -f *.o *.a *.so wordcount wordcount-dynamic