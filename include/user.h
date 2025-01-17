#ifndef USER_HH
#define USER_HH

#include <stdint.h>
#include <stdlib.h>

#define dll __declspec(dllexport)

typedef struct user {
    int Points;
    int Fails;
} User, UserData;

// Basic Functions to manage User points and fails

#define SetUserPoint(userData, x) (userData->Points = x)
#define SetUserFail(userData, x) (userData->Fails = x)

#define IncUserPoint(userData) (userData->Points += 0x01)
#define IncUserFail(userData) (userData->Fails += 0x01)

#define GetUserPoints(userData) (userData->Points)
#define GetUserFails(userData) (userData->Fails)


dll void initUser(UserData **restrict user);
dll void deleteUser(UserData *user);

#endif