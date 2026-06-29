#pragma once
#include "Card.h"

class TeacherCard final : public Card
{
public:
	TeacherCard();
	TeacherCard(const str &name, Gender gender, const str &affiliation, const str &cardId);
	~TeacherCard() override;
	void consume() override;
	static bool isProperId(const str &id);
	[[nodiscard]] CardType getCardType() const override { return CardType::TEACHER; }

	friend std::istream &operator>>(std::istream &is, TeacherCard &card);
	friend std::ostream &operator<<(std::ostream &os, const TeacherCard &card);
};

