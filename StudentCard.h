#pragma once

#include "Card.h"

class StudentCard final : public Card
{
public:
	StudentCard();
	StudentCard(const str &name, Gender gender, const str &affiliation, const str &cardId);
	~StudentCard() override = default;
	void consume(int money) override;
	void consume() override;
	static bool isProperId(const str &id);
	[[nodiscard]] unsigned int getFreeCredit() const { return freeCredit; }
	[[nodiscard]] CardType getCardType() const override { return CardType::STUDENT; }

	friend std::istream &operator>>(std::istream &is, StudentCard &card);
	friend std::ostream &operator<<(std::ostream &os, const StudentCard &card);

private:
	unsigned int freeCredit;
	std::time_t lastConsume;
};

