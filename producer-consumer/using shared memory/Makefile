libIPC.a: lib_sem.o lib_shm.o
	ar rv libIPC.a lib_sem.o lib_shm.o
	mkdir -p ./lib
	mv libIPC.a ./lib

main: main.o libIPC.a
	gcc -o main main.o -L./lib -lIPC

clean:
	rm lib_shm.o lib_sem.o main.o main

run:
	./main

libIPC.so: lib_sem.o lib_shm.o
	gcc -fPIC -c lib_sem.c -o lib_sem.o
	gcc -fPIC -c lib_shm.c -o lib_shm.o
	gcc -shared -o libIPC.so lib_sem.o lib_shm.o
	mkdir -p ./lib
	mv libIPC.so ./lib

mainSO: main.o libIPC.so
	gcc -o main main.o -L./lib -lIPC -Wl,-R ./lib
