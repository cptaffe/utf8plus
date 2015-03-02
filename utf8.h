
// Copyright (c) 2015 Connor Taffe

#ifndef UTF8_H_
#define UTF8_H_

#include <exception>
#include <cstdint>
#include <string>

namespace utf8 {

const int32_t CODEPOINT_MAX = 0x10ffff;

static size_t strlen(std::string *str);

class rune {
public:
	class exception : public std::exception {
	public:
		enum errcode {
			ERROR,
			INVALID,
			SHORT
		};

		errcode code;

		const char *what() const throw() {
			if (code == ERROR) {
				return "error";
			} else if (code == INVALID) {
				return "invalid rune";
			} else if (code == SHORT) {
				return "memory shorter than rune length";
			} else {
				return "unknown error";
			}
		}

		exception(enum errcode code) {
			this->code = code;
		}
	};

	static const size_t MAXLEN = 4;

	int32_t value;

	// static constructors
	static rune encode(const int32_t codepoint);
	static rune get(const void *mem, size_t size);

	// static methods
	static int len(const char byte);
	static bool isstartbyte(const char byte);

	// methods
	int32_t decode();
	bool isvalid();
	int len();

	rune(int32_t value);
};

class parser {
	char *str;
	size_t index;

public:
	parser(std::string *str);
	~parser();
	rune get();
};

} // namespace utf8

#endif // UTF8_H_
