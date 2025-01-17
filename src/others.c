#include <stdint.h>

int intToStr(unsigned int num, char *store, int length_store)
{
	uint8_t decimal_places = 0x00;

	if (num >= 0x64) decimal_places = 0x02;
	else if (num >= 0x0A) decimal_places = 0x01;

	if (decimal_places >= length_store) return 0x01;

	store[decimal_places+0x01] = '\0'; 

	do {
		store[decimal_places] = (char)(num % 0x0A) + 0x30;
		num /= 0x0A;
		decimal_places--;
	} while (num > 0x00);

	return 0x00;
}
