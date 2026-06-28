
#include "Card.h"

#include <utility>
#include "timeutil.h"
#include "strutil.h"

Card::Card() : gender(), lost(false), balance() {}

Card::Card(str name, const Gender gender, str affiliation, str cardId) : name(std::move(name)), gender(gender), affiliation(std::move(affiliation)), cardId(std::move(cardId)), lost(false), balance(0) {}

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

void Card::setGender(const Gender newGender)
{
	this->gender = newGender;
}

str Card::getAffiliation() const
{
	return affiliation;
}

void Card::setAffiliation(const str & newAffiliation)
{
	affiliation = newAffiliation;
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

int Card::getBalance() const
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
		if (const char c = id.at(i); c < '0' || c > '9')
		{
			return false;
		}
	}
	return true;
}

void Card::consume(const int money)
{
	if (balance < money) {
		throw std::runtime_error("Not enough balance");
	}
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
	const auto bill = Bill(cardId, amount, balance, getTime());
	bills.push_back(bill);
}

std::istream &operator>>(std::istream &is, Card &card)
{
	readStr(is, card.name);
	readStr(is, card.affiliation);
	readStr(is, card.cardId);
	is.read(reinterpret_cast<char *>(&card.lost), sizeof(card.lost));
	is.read(reinterpret_cast<char *>(&card.balance), sizeof(card.balance));
	int g;
	is.read(reinterpret_cast<char *>(&g), sizeof(g));
	card.gender = static_cast<Gender>(g);
	size_t billCount;
	is.read(reinterpret_cast<char *>(&billCount), sizeof(billCount));
	card.bills.clear();
	for (size_t i = 0; i < billCount; i++)
	{
		Bill bill;
		is >> bill;
		card.bills.push_back(bill);
	}
	return is;
}

std::ostream &operator<<(std::ostream &os, const Card &card)
{
	writeStr(os, card.name);
	writeStr(os, card.affiliation);
	writeStr(os, card.cardId);
	os.write(reinterpret_cast<const char *>(&card.lost), sizeof(card.lost));
	os.write(reinterpret_cast<const char *>(&card.balance), sizeof(card.balance));
	const int gen = card.gender;
	os.write(reinterpret_cast<const char *>(&gen), sizeof(gen));
	const size_t sz = card.bills.size();
	os.write(reinterpret_cast<const char *>(&sz), sizeof(sz));
	for (const auto &bill : card.bills)
	{
		os << bill;
	}
	return os;
}

Card::~Card() = default;
