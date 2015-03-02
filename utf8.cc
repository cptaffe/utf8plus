
#include "utf8.h"
#include "utf8/utf8.h"

#include <cstring>
#include <cstdio>

utf8::rune::rune(int32_t value) {
	this->value = value;
}

int utf8::rune::len(const char byte) {
	return utf8_runelen(byte);
}

bool utf8::rune::isstartbyte(const char byte) {
	return utf8_isstartbyte(byte);
}

int utf8::rune::len() {
	return utf8_runelen((utf8_rune) this->value);
}

int32_t utf8::rune::decode() {
	return utf8_decode(this->value);
}

utf8::rune utf8::rune::encode(int32_t codepoint) {
	return utf8::rune(utf8_encode(codepoint));
}

bool utf8::rune::isvalid() {
	return utf8_isvalid(this->value);
}

utf8::rune utf8::rune::get(const void *mem, size_t size) {
	return utf8::rune(utf8_getr(mem, size));
}
