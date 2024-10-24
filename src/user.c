#include <stdint.h>

struct User {
    uint16_t Points;
    uint16_t Fails;
};

void initUser(void) 
{
    struct User *user = (struct User*)malloc(sizeof(struct User));

    user->Points = 0x00;
    user->Fails = 0x00;
}

void SetUserPoints(struct User* user, uint16_t points)
{
	user->Points = points;
}

void SetUserFaills(struct User* user, uint16_t faills)
{
	user->Fails = faills;
}

void AddUserPoints(struct User* user, int points_to_sum)
{
	if (points_to_sum == NULL) points_to_sum = 1;
	user->Points += points_to_sum;
}

void AddUserFaills(struct User* user, int faills_to_sum)
{
	if (faills_to_sum == NULL) faills_to_sum = 1;
	user->Points += faills_to_sum;
}

unsigned int GetUserPoints(struct User* user)
{
	return user->Points;
}

unsigned int GetUserFails(struct User* user)
{
	return user->Fails;
}