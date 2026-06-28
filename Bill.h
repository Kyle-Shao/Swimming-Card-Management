#pragma once

#include <ctime>
#include <string>
#include <iostream>

class Bill
{
public:
	Bill();
	Bill(std::string cardId, int amount, int balance, std::time_t timestamp);
	[[nodiscard]] int getAmount() const { return amount; }
	[[nodiscard]] int getBalance() const { return balance; }
	[[nodiscard]] std::time_t getTimestamp() const { return timestamp; }
	~Bill();

	friend std::istream &operator>>(std::istream &is, Bill &bill);
	friend std::ostream &operator<<(std::ostream &os, const Bill &bill);

private:
	std::string cardId;
	int amount;
	int balance;
	std::time_t timestamp;
};

