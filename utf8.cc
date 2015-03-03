
// Copyright (c) 2015 Connor Taffe

#include "utf8.h"
#include "utf8/utf8.h"

#include <stdexcept>
#include <cstring>
#include <cstdio>

size_t utf8::strlen(std::string *str) {
	size_t len = utf8_strlen(str->c_str());
	if (len == utf8_CP_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (len == utf8_CP_ERROR) {
		throw std::logic_error("utf8_strlen indicated error");
	} else {
		return len;
	}
}

utf8::rune::rune(int32_t value) {
	this->value = value;
}

int utf8::rune::len(const char byte) {
	int len = utf8_runelen(byte);
	if (len == utf8_CP_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (len == utf8_CP_ERROR) {
		throw std::logic_error("utf8_runelen indicated error");
	} else {
		return len;
	}
}

bool utf8::rune::isstartbyte(const char byte) {
	return utf8_isstartbyte(byte);
}

int utf8::rune::len() {
	return utf8::rune::len(((char *) &this->value)[0]);
}

int32_t utf8::rune::decode() {
	int32_t cp = utf8_decode(this->value);
	if (cp == utf8_CP_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (cp == utf8_CP_ERROR) {
		throw std::logic_error("utf8_decode indicated error");
	} else {
		return cp;
	}
}

utf8::rune utf8::rune::encode(int32_t codepoint) {
	utf8::rune rune = utf8::rune(utf8_encode(codepoint));
	if (rune.value == utf8_RUNE_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (rune.value == utf8_RUNE_ERROR) {
		throw std::logic_error("utf8_encode indicated error");
	} else if (rune.value == utf8_RUNE_SHORT) {
		throw utf8::rune::exception(utf8::rune::exception::SHORT);
	} else {
		return rune;
	}
}

bool utf8::rune::isvalid() {
	return utf8_isvalid(this->value);
}

utf8::rune utf8::rune::get(const void *mem, size_t size) {
	utf8::rune rune = utf8::rune(utf8_getr(mem, size));
	if (rune.value == utf8_RUNE_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (rune.value == utf8_RUNE_ERROR) {
		throw std::logic_error("utf8_getr indicated error");
	} else if (rune.value == utf8_RUNE_SHORT) {
		throw utf8::rune::exception(utf8::rune::exception::SHORT);
	} else {
		return rune;
	}
}

utf8::parser::parser(std::string str) {
	c_parser = utf8_pinit(str.c_str());
}

utf8::parser::~parser() {
	utf8_pfree((utf8_parser *) c_parser);
}

utf8::rune utf8::parser::get() {
	utf8::rune rune((int32_t) utf8_pget((utf8_parser *) c_parser));
	if (rune.value == utf8_RUNE_INVALID) {
		throw utf8::rune::exception(utf8::rune::exception::INVALID);
	} else if (rune.value == utf8_RUNE_ERROR) {
		throw std::logic_error("utf8_pget indicated error");
	} else if (rune.value == utf8_RUNE_SHORT) {
		throw utf8::rune::exception(utf8::rune::exception::SHORT);
	} else {
		return rune;
	}
}
