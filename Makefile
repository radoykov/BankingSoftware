all: main.exe

main.exe: users.o hashMap.o main.c
	gcc main.c users.o hashMap.o -o main.exe

# Compile users.c
users.o: users.c users.h structures/hashTable/hashMap.h
	gcc -c users.c -o users.o

# Compile hashMap.c
hashMap.o: structures/hashTable/hashMap.c structures/hashTable/hashMap.h
	gcc -c structures/hashTable/hashMap.c -o hashMap.o

# Clean rule
clean:
	del *.exe *.o