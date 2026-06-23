#include "Bill.h"


Bill::Bill()
{
}

Bill::Bill(const std::string & cardId, const int amount, const int balance, const long long int timestamp) : cardId(cardId), amount(amount), balance(balance), timestamp(timestamp)
{
}


Bill::~Bill()
{
}
