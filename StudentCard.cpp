
#include "StudentCard.h"
#include "timeutil.h"


StudentCard::StudentCard() : Card(), freeCredit(20)
{
}

StudentCard::StudentCard(const str & name, const Gender gender, const str & affiliation, const str & cardId) : Card(name, gender, affiliation, cardId), freeCredit(20), lastConsume(getTime())
{
}

void StudentCard::consume(const int money)
{
	// TODO: 91reset
	if (freeCredit)
	{
		freeCredit--;
		Card::consume(0);
		return;
	}
	Card::consume(money);
}

void StudentCard::consume()
{
	consume(5);
}

bool StudentCard::isProperId(const str & id)
{
	return id.length() == 11 && Card::isProperId(id);
}

