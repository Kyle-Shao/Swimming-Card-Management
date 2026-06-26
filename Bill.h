#pragma once
#include <string>
#include <ctime>
#include <iostream>

class Bill
{
public:
	Bill();
	Bill(const std::string &cardId, const int amount, const int balance, const std::time_t timestamp);
	~Bill();

	friend std::istream &operator>>(std::istream &is, Bill &bill);
	friend std::ostream &operator<<(std::ostream &os, const Bill &bill);

private:
	std::string cardId;
	int amount;
	int balance;
	std::time_t timestamp;
};

