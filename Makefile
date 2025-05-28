all: main.exe

main.exe: users.o hashMap.o accounts.o sha256.o main.c
	gcc main.c users.o hashMap.o accounts.o sha256.o -o main.exe

# Compile sha256.o
sha256.o: sha256.c sha256.h
	gcc -c sha256.c -o sha256.o

# Compile accounts.o
accounts.o: accounts.c accounts.h structures/hashTable/hashMap.h
	gcc -c accounts.c -o accounts.o

# Compile users.o
users.o: users.c users.h structures/hashTable/hashMap.h
	gcc -c users.c -o users.o

# Compile hashMap.o
hashMap.o: structures/hashTable/hashMap.c structures/hashTable/hashMap.h
	gcc -c structures/hashTable/hashMap.c -o hashMap.o

# Clean rule
clean:
	del *.exe *.o