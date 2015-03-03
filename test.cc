
// Copyright (c) 2015 Connor Taffe

#include "utf8.h"

// testing purposes
int main() {
	int32_t codepoint = 0x5555;
	utf8::rune rune = utf8::rune::encode(codepoint);
	printf("U+%X->%#x->%.4s\n", codepoint, rune.decode(),  (char *) &rune.value);
	printf("len: %d\n", (int) utf8::strlen((std::string *) "hello, world!"));
	utf8::parser parser(std::string((char *) "hello, world!"));
	int32_t val = parser.get().value;
	printf("%#x->%.4s\n", val, (char *) &val);
}
