#pragma once

#include "Card.h"
#include <ctime>

class StudentCard : public Card
{
public:
	StudentCard();
	StudentCard(const str &name, const Gender gender, const str &affiliation, const str &cardId);
	~StudentCard() = default;
	void consume(const int money) override;
	void consume() override;
	bool isProperId(const str &id) override;

	friend std::istream &operator>>(std::istream &is, StudentCard &card);
	friend std::ostream &operator<<(std::ostream &os, const StudentCard &card);

private:
	unsigned int freeCredit;
	std::time_t lastConsume;
};

