#pragma once
#include<string>
using namespace std;

class DSException {
public:
	DSException(const string& msg = "") :message(msg) { }	//	���캯��
	virtual ~DSException() { }
	virtual string toString() const {
		return "Exception" + string(":") + what();
	}
	virtual string what() const {
		return message;
	}

private:
	string message;

};

class DuplicateItemException :public DSException {
public:
	DuplicateItemException(const string& msg = ""):DSException(msg){ }
};