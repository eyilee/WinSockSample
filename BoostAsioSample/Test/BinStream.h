#pragma once

class BinStream {
protected:
	size_t it;
public:
	std::vector<char> bytes;

public:
	std::vector<char> &data() {
		return bytes;
	}

	template<class T>
	BinStream operator << (T &t) {
		char *pos = (char *)&t;
		int size = sizeof(T) / sizeof(char);

		bytes.insert(bytes.end(), pos, pos + sizeof(T) / sizeof(char));

		return *this;
	}

	template<class T>
	BinStream operator >> (T &t) {
		t = *(T *)(&*bytes.begin() + it);
		it += sizeof(T) / sizeof(char);
		return *this;
	}
};