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

class Stream {
private:
	size_t it = 0;
	std::vector<char> pkg;

public:
	std::vector<char> &data() {
		return pkg;
	}

	template<class T>
	Stream operator << (T &t) {
		char *pos = (char *)&t;
		int size = sizeof(T) / sizeof(char);

		pkg.insert(pkg.end(), pos, pos + sizeof(T) / sizeof(char));

		return *this;
	}

	template<class T>
	Stream operator >> (T &t) {
		t = *(T *)(&*pkg.begin() + it);
		it += sizeof(T) / sizeof(char);
		return *this;
	}
};

template <typename T>
class Command {
private:
	static UINT ID;

public:
	virtual void Serialize(Stream &stream) {
		stream << ID;
		OnSerialize(stream);
	}

	virtual void OnSerialize(Stream &stream) = 0;

	virtual void Derialize(Stream &stream) {
		stream >> ID;
		OnDerialize(stream);
	}

	virtual void OnDerialize(Stream &stream) = 0;
};

template <typename T>
UINT Command<T>::ID;

class One : public Command<One> {
private:
	int data1;
	char data2;

public:
	One(int data1, char data2)
		: data1(data1)
		, data2(data2)
	{
	}

	void OnSerialize(Stream &stream) {
		stream << data1;
		stream << data2;
	}

	void OnDerialize(Stream &stream) {
		stream >> data1;
		stream >> data2;
	}
};

class Two : public Command<Two> {
private:
	float data1;
	bool data2;

public:
	Two(float data1, bool data2)
		: data1(data1)
		, data2(data2)
	{
	}

	void OnSerialize(Stream &stream) {
		stream << data1;
		stream << data2;
	}

	void OnDerialize(Stream &stream) {
		stream >> data1;
		stream >> data2;
	}
};

int main()
{
	return 0;
}