#pragma once

class BinInStream : public BinStream {
public:
	BinInStream &operator >> (bool&);
	BinInStream &operator >> (char&);
	BinInStream &operator >> (unsigned char&);
	BinInStream &operator >> (short&);
	BinInStream &operator >> (unsigned short&);
	BinInStream &operator >> (int&);
	BinInStream &operator >> (unsigned int&);
	BinInStream &operator >> (long&);
	BinInStream &operator >> (unsigned long&);
	BinInStream &operator >> (long long&);
	BinInStream &operator >> (unsigned long long&);
	BinInStream &operator >> (float&);
	BinInStream &operator >> (double&);
};