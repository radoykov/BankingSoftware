#ifndef USERS_H
#define USERS_H
#define USERNAME_MAX_LEN 50

//user have to be searched by username and id we are using hash map !

typedef struct User
{
    int id;
    char username[USERNAME_MAX_LEN];
    char *hashedPassword; // type will be changed there will be includet sha256 len

} User;

int loginUser(char *username, char *password);
int registerUser(char *username, char *password);

#endif