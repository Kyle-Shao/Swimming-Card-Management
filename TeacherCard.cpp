
#include "TeacherCard.h"


TeacherCard::TeacherCard() = default;

TeacherCard::TeacherCard(const str & name, const Gender gender, const str & affiliation, const str & cardId) : Card(name, gender, affiliation, cardId) {}

TeacherCard::~TeacherCard() = default;

void TeacherCard::consume()
{
	Card::consume(1000);
}

bool TeacherCard::isProperId(const str & id)
{
	return id.length() == 7 && Card::isProperId(id);
}

std::istream &operator>>(std::istream &is, TeacherCard &card)
{
	is >> static_cast<Card &>(card);
	return is;
}

std::ostream &operator<<(std::ostream &os, const TeacherCard &card)
{
	os << static_cast<const Card &>(card);
	return os;
}
