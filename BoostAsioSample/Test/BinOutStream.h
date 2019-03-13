#pragma once

class BinOutStream : public BinStream {
public:
	BinOutStream& operator << (bool&);
	BinOutStream& operator << (char&);
	BinOutStream& operator << (unsigned char&);
	BinOutStream& operator << (short&);
	BinOutStream& operator << (unsigned short&);
	BinOutStream& operator << (int&);
	BinOutStream& operator << (unsigned int&);
	BinOutStream& operator << (long&);
	BinOutStream& operator << (unsigned long&);
	BinOutStream& operator << (long long&);
	BinOutStream& operator << (unsigned long long&);
	BinOutStream& operator << (float&);
	BinOutStream& operator << (double&);
};