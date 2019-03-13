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
#include <bitset>

#include "biniostream.h"

class Stream {
private:
	size_t it = 0;
	std::vector<char> bytes;

public:
	std::vector<char> &data() {
		return bytes;
	}

	template<class T>
	Stream operator << (T &t) {
		char *pos = (char *)&t;
		int size = sizeof(T) / sizeof(char);

		bytes.insert(bytes.end(), pos, pos + sizeof(T) / sizeof(char));

		return *this;
	}

	template<class T>
	Stream operator >> (T &t) {
		t = *(T *)(&*bytes.begin() + it);
		it += sizeof(T) / sizeof(char);
		return *this;
	}
};

class ICommand {
public:
	virtual UINT getId() = 0;
	virtual void excute() = 0;
	virtual void serialize(Stream &stream) = 0;
	virtual void deserialize(Stream &stream) = 0;
};

template <typename T>
class Command : public ICommand {
public:
	static UINT ID;

public:
	UINT getId() { return ID; }

	virtual void excute() = 0;

	virtual void serialize(Stream &stream) {
		stream << ID;
		onSerialize(stream);
	}

	virtual void deserialize(Stream &stream) {
		stream >> ID;
		onDeserialize(stream);
	}

	virtual void onSerialize(Stream &stream) = 0;
	virtual void onDeserialize(Stream &stream) = 0;
};

template <typename T>
UINT Command<T>::ID;

class ICommandGenerator {
public:
	virtual ICommand *Create(Stream stream) = 0;
};

template <typename T>
class CommandGenerator : public ICommandGenerator {
public:
	virtual ICommand *Create(Stream stream) {
		T *command = new T();
		command->onDeserialize(stream);
		return command;
	}
};

class CommandBook {
private:
	std::vector<ICommandGenerator *> commands;

public:
	UINT book(ICommandGenerator *command) {
		commands.push_back(command);
		return (UINT)commands.size() - 1;
	}

	ICommand *getCommand(Stream stream) {
		UINT ID;
		stream >> ID;
		return commands[ID]->Create(stream);
	}
};

class One : public Command<One> {
private:
	int data1;
	char data2;

public:
	One() {}

	One(int data1, char data2)
		: data1(data1)
		, data2(data2)
	{
	}

	void excute() {
		std::cout << "class: One" << std::endl;
		std::cout << " data1: " << data1 << std::endl;
		std::cout << " data2: " << data2 << std::endl;
	}

	void onSerialize(Stream &stream) {
		stream << data1;
		stream << data2;
	}

	void onDeserialize(Stream &stream) {
		stream >> data1;
		stream >> data2;
	}
};

class Two : public Command<Two> {
private:
	float data1;
	bool data2;

public:
	Two() {}

	Two(float data1, bool data2)
		: data1(data1)
		, data2(data2)
	{
	}

	void excute() {
		std::cout << "class: Two" << std::endl;
		std::cout << " data1: " << data1 << std::endl;
		std::cout << " data2: " << data2 << std::endl;
	}

	void onSerialize(Stream &stream) {
		stream << data1;
		stream << data2;
	}

	void onDeserialize(Stream &stream) {
		stream >> data1;
		stream >> data2;
	}
};

int main()
{
	bool b = true;
	char c = 'c';
	unsigned char uc = 'u';
	short s = 32767;
	unsigned short us = 32768;
	int i = 2147483647;
	unsigned int ui = 2147483648;
	long l = 2147483647;
	unsigned long ul = 2147483648;
	long long ll = 9223372036854775807;
	unsigned long long ull = 9223372036854775808;
	float f = 0.99f;
	double d = 0.999;

	std::cout << "origin:" << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << uc << std::endl;
	std::cout << s << std::endl;
	std::cout << us << std::endl;
	std::cout << i << std::endl;
	std::cout << ui << std::endl;
	std::cout << l << std::endl;
	std::cout << ul << std::endl;
	std::cout << ll << std::endl;
	std::cout << ull << std::endl;
	std::cout << f << std::endl;
	std::cout << d << std::endl;

	BinOutStream outstream;
	outstream << b;
	outstream << c;
	outstream << uc;
	outstream << s;
	outstream << us;
	outstream << i;
	outstream << ui;
	outstream << l;
	outstream << ul;
	outstream << ll;
	outstream << ull;
	outstream << f;
	outstream << d;

	BinInStream instream;
	instream.bytes = outstream.bytes;
	instream >> b;
	instream >> c;
	instream >> uc;
	instream >> s;
	instream >> us;
	instream >> i;
	instream >> ui;
	instream >> l;
	instream >> ul;
	instream >> ll;
	instream >> ull;
	instream >> f;
	instream >> d;

	std::cout << "after:" << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << uc << std::endl;
	std::cout << s << std::endl;
	std::cout << us << std::endl;
	std::cout << i << std::endl;
	std::cout << ui << std::endl;
	std::cout << l << std::endl;
	std::cout << ul << std::endl;
	std::cout << ll << std::endl;
	std::cout << ull << std::endl;
	std::cout << f << std::endl;
	std::cout << d << std::endl;

	CommandBook commands;

	// regesiter commands
	One::ID = commands.book(new CommandGenerator<One>());
	Two::ID = commands.book(new CommandGenerator<Two>());

	// socket stream
	Stream stream1;

	// client send message to server
	One *one = new One(10, 'A');
	one->serialize(stream1);

	// server get message
	ICommand *command = commands.getCommand(stream1);
	command->excute();

	// socket stream
	Stream stream2;

	// client send message to server
	Two *two = new Two(0.123f, true);
	two->serialize(stream2);

	// server get message
	command = commands.getCommand(stream2);
	command->excute();

	system("pause");
	return 0;
}