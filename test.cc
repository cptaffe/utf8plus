
#include "utf8.h"

// testing purposes
int main() {
	int32_t code = utf8::rune::encode(0x5555).decode();
	printf("%d->%.4s\n", utf8::rune::encode(0x5555).value, (char *) &code);
}
