#pragma once
#include "Card.h"

class TeacherCard : public Card
{
public:
	TeacherCard();
	TeacherCard(const str &name, const Gender gender, const str &affiliation, const str &cardId);
	~TeacherCard();
	void consume() override;
	bool isProperId(const str &id) override;
};

