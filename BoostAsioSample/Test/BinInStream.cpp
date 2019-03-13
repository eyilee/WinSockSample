#include "pch.h"
#include "BinStream.h"
#include "BinInStream.h"

BinInStream& BinInStream::operator >> (bool& b) {
	b = *(bool*)(&*bytes.begin());
	bytes.erase(bytes.begin());
	return *this;
}

BinInStream& BinInStream::operator >> (char& c) {
	c = *(char*)(&*bytes.begin());
	bytes.erase(bytes.begin());
	return *this;
}

BinInStream& BinInStream::operator >> (unsigned char& uc) {
	uc = *(unsigned char*)(&*bytes.begin());
	bytes.erase(bytes.begin());
	return *this;
}

BinInStream& BinInStream::operator >> (short& s) {
	s = *(short*)(&*bytes.begin());
	s = ntohs(s);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(short));
	return *this;
}

BinInStream& BinInStream::operator >> (unsigned short& us) {
	us = *(unsigned short*)(&*bytes.begin());
	us = ntohs(us);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(unsigned short));
	return *this;
}

BinInStream& BinInStream::operator >> (int& i) {
	i = *(int*)(&*bytes.begin());
	i = ntohl(i);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(int));
	return *this;
}

BinInStream& BinInStream::operator >> (unsigned int& ui) {
	ui = *(unsigned int*)(&*bytes.begin());
	ui = ntohl(ui);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(unsigned int));
	return *this;
}

BinInStream& BinInStream::operator >> (long& l) {
	l = *(long*)(&*bytes.begin());
	l = ntohl(l);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(long));
	return *this;
}

BinInStream& BinInStream::operator >> (unsigned long& ul) {
	ul = *(unsigned long*)(&*bytes.begin());
	ul = ntohl(ul);
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(unsigned long));
	return *this;
}

BinInStream& BinInStream::operator >> (long long& ll) {
	unsigned long* t = (unsigned long*)(&*bytes.begin());
	t[0] = ntohl(t[0]);
	t[1] = ntohl(t[1]);
	ll = *(long long*)(&*bytes.begin());
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(long long));
	return *this;
}

BinInStream& BinInStream::operator >> (unsigned long long& ull) {
	unsigned long* t = (unsigned long*)(&*bytes.begin());
	t[0] = ntohl(t[0]);
	t[1] = ntohl(t[1]);
	ull = *(unsigned long long*)(&*bytes.begin());
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(long long));
	return *this;
}

BinInStream& BinInStream::operator >> (float& f) {
	unsigned long* t = (unsigned long*)(&*bytes.begin());
	*t = ntohl(*t);
	f = *(float*)(&*bytes.begin());
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(float));
	return *this;
}

BinInStream& BinInStream::operator >> (double& d) {
	unsigned long* t = (unsigned long*)(&*bytes.begin());
	t[0] = ntohl(t[0]);
	t[1] = ntohl(t[1]);
	d = *(double*)(&*bytes.begin());
	bytes.erase(bytes.begin(), bytes.begin() + sizeof(double));
	return *this;
}
