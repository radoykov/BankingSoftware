all: main.exe

main.exe: users.o hashMap.o accounts.o sha256.o database.o main.c
	gcc -g main.c users.o hashMap.o accounts.o sha256.o database.o -o main.exe

# Compile database.o
database.o: database.c database.h
	gcc -g -c database.c -o database.o

# Compile sha256.o
sha256.o: sha256.c sha256.h
	gcc -g -c sha256.c -o sha256.o

# Compile accounts.o
accounts.o: accounts.c accounts.h structures/hashTable/hashMap.h
	gcc -g -c accounts.c -o accounts.o

# Compile users.o
users.o: users.c users.h structures/hashTable/hashMap.h
	gcc -g -c users.c -o users.o

# Compile hashMap.o
hashMap.o: structures/hashTable/hashMap.c structures/hashTable/hashMap.h
	gcc -g -c structures/hashTable/hashMap.c -o hashMap.o

# Clean rule
clean:
	del *.exe *.o