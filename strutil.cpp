#include "strutil.h"

void writeStr(std::ostream &os, const std::string &s)
{
	const size_t len = s.size();
	if (len > 65536)
	{
		throw std::runtime_error("String length exceeds maximum size");
	}
	os.write(reinterpret_cast<const char *>(&len), sizeof(len));
	os.write(s.data(), static_cast<std::streamsize>(len));
}

void readStr(std::istream &is, std::string &s)
{
	size_t len;
	is.read(reinterpret_cast<char *>(&len), sizeof(len));
	if (len > 65536)
	{
		throw std::runtime_error("String length exceeds maximum size");
	}
	s.resize(len);
	is.read(&s[0], static_cast<std::streamsize>(len));
}
