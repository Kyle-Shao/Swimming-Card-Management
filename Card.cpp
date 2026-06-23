
#include "Card.h"
#include "timeutil.h"


Card::Card() : lost(false) {}

Card::Card(const str &name, const Gender gender, const str &affiliation, const str &cardId) : name(name), gender(gender), affiliation(affiliation), cardId(cardId), lost(false), balance(0) {}

str Card::getName() const
{
	return name;
}

void Card::setName(const str & newName)
{
	name = newName;
}

Gender Card::getGender() const
{
	return gender;
}

void Card::setGender(const Gender gender)
{
	this->gender = gender;
}

str Card::getAffiliation() const
{
	return affiliation;
}

void Card::setAffiliation(const str & newAffi)
{
	affiliation = newAffi;
}

str Card::getCardId() const
{
	return cardId;
}

bool Card::isLost() const
{
	return lost;
}

void Card::setIsLost(const bool newLost)
{
	lost = newLost;
}

int Card::getBalance()
{
	return balance;
}

std::vector<Bill>& Card::getBills()
{
	return bills;
}

bool Card::isProperId(const str & id)
{
	for (size_t i = 0; i < id.length(); i++)
	{
		char c = id.at(i);
		if (c < '0' || c > '9')
		{
			return false;
		}
	}
	return true;
}

void Card::consume(const int money)
{
	balance -= money;
	recordBill(-money);
}

void Card::charge(const int money)
{
	balance += money;
	recordBill(money);
}

void Card::consume()
{
}

void Card::recordBill(const int amount)
{
	Bill bill = Bill(cardId, amount, balance, getTime());
	bills.push_back(bill);
}

void Card::read(std::istream is)
{
	is >> 
}

Card::~Card() = default;
