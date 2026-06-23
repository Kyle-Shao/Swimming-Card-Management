#pragma once
#include <string>

class Bill
{
public:
	Bill();
	Bill(const std::string &cardId, const int amount, const int balance, const long long int timestamp);
	~Bill();
private:
	std::string cardId;
	int amount;
	int balance;
	long long int timestamp;
};

