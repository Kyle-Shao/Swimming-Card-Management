
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
	std::time_t now = getTime();

	// lastConsume < 9.1 < now  -->  reset freeCredit
	std::tm lastTm = *std::localtime(&lastConsume);
	std::tm nowTm = *std::localtime(&now);

	int lastAcademicYear = lastTm.tm_year + 1900;
	if (lastTm.tm_mon < 8) lastAcademicYear--;  // tm_mon: 0=Jan, 8=Sep

	int nowAcademicYear = nowTm.tm_year + 1900;
	if (nowTm.tm_mon < 8) nowAcademicYear--;

	if (nowAcademicYear > lastAcademicYear)
		freeCredit = 20;

	lastConsume = now;

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

std::istream &operator>>(std::istream &is, StudentCard &card)
{
	is >> static_cast<Card &>(card);
	is.read(reinterpret_cast<char *>(&card.freeCredit), sizeof(card.freeCredit));
	is.read(reinterpret_cast<char *>(&card.lastConsume), sizeof(card.lastConsume));
	return is;
}

std::ostream &operator<<(std::ostream &os, const StudentCard &card)
{
	os << static_cast<const Card &>(card);
	os.write(reinterpret_cast<const char *>(&card.freeCredit), sizeof(card.freeCredit));
	os.write(reinterpret_cast<const char *>(&card.lastConsume), sizeof(card.lastConsume));
	return os;
}

