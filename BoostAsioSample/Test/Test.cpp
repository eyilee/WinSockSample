#include "pch.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>

class Package : public std::vector<char> {

};

class Myclass {
	size_t it = 0;
	Package pkg;

public:

	template<class T>
	Myclass operator << (T &t) {
		char *pos = (char *)&t;
		int size = sizeof(T) / sizeof(char);

		pkg.insert(pkg.end(), pos, pos + sizeof(T) / sizeof(char));

		return *this;
	}

	template<class T>
	Myclass operator >> (T &t) {
		t = *(T *)(&*pkg.begin() + it);
		it += sizeof(T) / sizeof(char);
		return *this;
	}

	void print() {
		size_t length = pkg.size();

		for (size_t i = 0; i < length; i++)
		{
			std::cout << std::hex << (int)pkg[i] << " ";
		}

		std::cout << std::endl;
	}
};

struct Newclass {
	int a;
	char b;
};

int main()
{
	Myclass my;
	bool b = true;
	my << b;
	int i = 65535;
	my << i;
	my.print();

	bool c;
	my >> c;
	int j;
	my >> j;

	std::cout << c << std::endl;
	std::cout << j << std::endl;

	Newclass nc{ 1, 'a' };
	my << nc;
	Newclass nc2;
	my >> nc2;

	std::cout << nc2.a << std::endl;
	std::cout << nc2.b << std::endl;

	system("pause");
	return 0;
}