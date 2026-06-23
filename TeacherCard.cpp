
#include "TeacherCard.h"


TeacherCard::TeacherCard()
{
}

TeacherCard::TeacherCard(const str & name, const Gender gender, const str & affiliation, const str & cardId) : Card(name, gender, affiliation, cardId)
{
}


TeacherCard::~TeacherCard()
{

}

void TeacherCard::consume()
{
	Card::consume(10);
}

bool TeacherCard::isProperId(const str & id)
{
	return id.length() == 7 && Card::isProperId(id);
}
