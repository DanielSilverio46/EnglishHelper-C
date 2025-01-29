#include "user.h"

dll void initUser(UserData **restrict user)
{
    *user = (UserData*)malloc(sizeof(UserData));

    SetUserPoint((*user), 0x00);
    SetUserFail((*user), 0x00);
}

dll void deleteUser(UserData *user)
{
	free(user);
}