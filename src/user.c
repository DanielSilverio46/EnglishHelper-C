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

// DrawPointsUser
void userScoreToString(HDC hdc, RECT *rect, int points, int fails)
{
	char PointsStr[0x0c] = "Points: ", FailsStr[0x0b] = "Fails: ";

	intToStr(points, &PointsStr[0x08], ((sizeof(PointsStr) - 0x08) / sizeof(char)));
	intToStr(fails, &FailsStr[0x07], ((sizeof(PointsStr) - 0x07) / sizeof(char)));

	// Drawing points and fails of user
	rect->left += 0x32;
	rect->right -= 0x32; 
	rect->top += 0x3c;

	DrawText(hdc, PointsStr, (int8_t)0xff, rect, DT_TOP | DT_LEFT);
	DrawText(hdc, FailsStr, (int8_t)0xff, rect, DT_TOP | DT_RIGHT);

	// Reset Values of RectS
	rect->left -= 0x32;
	rect->right += 0x32;
	rect->top -= 0x3c;
}
