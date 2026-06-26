#include "CardManager.h"
#include "StudentCard.h"
#include "TeacherCard.h"
#include <fstream>
#include <stdexcept>


CardManager::CardManager()
{
}


CardManager::~CardManager()
{
}

void CardManager::createStudentCard(std::string &sno, std::string &name, Gender gender, const std::string &affiliation)
{
	if (cards.find(sno) != cards.end())
	{
		throw std::runtime_error("Card ID already exists: " + sno);
	}
	StudentCard card(name, gender, affiliation, sno);
	cards[sno] = card;
}

void CardManager::createTeacherCard(std::string &tno, std::string &name, Gender gender, const std::string &affiliation)
{
	if (cards.find(tno) != cards.end())
	{
		throw std::runtime_error("Card ID already exists: " + tno);
	}
	TeacherCard card(name, gender, affiliation, tno);
	cards[tno] = card;
}

Card &CardManager::getCard(std::string &cardId)
{
	return cards.at(cardId);
}

void CardManager::readFile()
{
	std::ifstream ifs("cards.dat", std::ios::binary);
	if (!ifs) return;
	cards.clear();
	Card card;
	while (ifs >> card)
	{
		cards[card.getCardId()] = card;
	}
}

void CardManager::saveFile()
{
	std::ofstream ofs("cards.dat", std::ios::binary);
	for (const auto &[id, card] : cards)
	{
		ofs << card;
	}
}
