#pragma once

#include "Card.h"

class StudentCard : public Card
{
public:
	StudentCard();
	StudentCard(const str &name, const Gender gender, const str &affiliation, const str &cardId);
	~StudentCard() = default;
	void consume(const int money) override;
	void consume() override;
	bool isProperId(const str &id) override;
private:
	unsigned int freeCredit;
	long long int lastConsume;
};

