#include "pch.h"
#include "BinStream.h"
#include "BinOutStream.h"

BinOutStream& BinOutStream::operator << (bool& b) {
	char p = (char)b;
	bytes.push_back(p);
	return *this;
}

BinOutStream& BinOutStream::operator << (char& c) {
	bytes.push_back(c);
	return *this;
}

BinOutStream& BinOutStream::operator << (unsigned char& uc) {
	bytes.push_back(uc);
	return *this;
}

BinOutStream& BinOutStream::operator << (short& s) {
	short t = htons(s);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(short));
	return *this;
}

BinOutStream& BinOutStream::operator << (unsigned short& us) {
	unsigned short t = htons(us);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(unsigned short));
	return *this;
}

BinOutStream& BinOutStream::operator << (int& i) {
	int t = htonl(i);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(int));
	return *this;
}

BinOutStream& BinOutStream::operator << (unsigned int& ui) {
	unsigned int t = htonl(ui);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(unsigned int));
	return *this;
}

BinOutStream& BinOutStream::operator << (long& l) {
	long t = htonl(l);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(long));
	return *this;
}

BinOutStream& BinOutStream::operator << (unsigned long& ul) {
	unsigned long t = htonl(ul);
	char *p = (char*)&t;
	bytes.insert(bytes.end(), p, p + sizeof(unsigned long));
	return *this;
}

BinOutStream& BinOutStream::operator << (long long& ll) {
	unsigned long* t = reinterpret_cast<unsigned long*>(&ll);
	t[0] = htonl(t[0]);
	t[1] = htonl(t[1]);
	char *p = (char*)t;
	bytes.insert(bytes.end(), p, p + sizeof(long long));
	return *this;
}

BinOutStream& BinOutStream::operator << (unsigned long long& ull) {
	unsigned long* t = reinterpret_cast<unsigned long*>(&ull);
	t[0] = htonl(t[0]);
	t[1] = htonl(t[1]);
	char *p = (char*)t;
	bytes.insert(bytes.end(), p, p + sizeof(unsigned long long));
	return *this;
}

BinOutStream& BinOutStream::operator << (float& f) {
	unsigned long* t = reinterpret_cast<unsigned long*>(&f);
	*t = htonl(*t);
	char *p = (char*)t;
	bytes.insert(bytes.end(), p, p + sizeof(float));
	return *this;
}

BinOutStream& BinOutStream::operator << (double& d) {
	unsigned long* t = reinterpret_cast<unsigned long*>(&d);
	t[0] = htonl(t[0]);
	t[1] = htonl(t[1]);
	char *p = (char*)t;
	bytes.insert(bytes.end(), p, p + sizeof(double));
	return *this;
}
