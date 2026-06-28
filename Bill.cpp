#include "Bill.h"

#include <utility>
#include "strutil.h"

Bill::Bill() : amount(), balance(), timestamp() {}

Bill::Bill(std::string cardId, const int amount, const int balance, const std::time_t timestamp) : cardId(std::move(cardId)), amount(amount), balance(balance), timestamp(timestamp) {}

Bill::~Bill() = default;

std::istream &operator>>(std::istream &is, Bill &bill)
{
	readStr(is, bill.cardId);
	is.read(reinterpret_cast<char *>(&bill.amount), sizeof(bill.amount));
	is.read(reinterpret_cast<char *>(&bill.balance), sizeof(bill.balance));
	is.read(reinterpret_cast<char *>(&bill.timestamp), sizeof(bill.timestamp));
	return is;
}

std::ostream &operator<<(std::ostream &os, const Bill &bill)
{
	writeStr(os, bill.cardId);
	os.write(reinterpret_cast<const char *>(&bill.amount), sizeof(bill.amount));
	os.write(reinterpret_cast<const char *>(&bill.balance), sizeof(bill.balance));
	os.write(reinterpret_cast<const char *>(&bill.timestamp), sizeof(bill.timestamp));
	return os;
}
