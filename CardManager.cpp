#include "CardManager.h"
#include "StudentCard.h"
#include "TeacherCard.h"
#include <fstream>
#include <ranges>
#include <stdexcept>


CardManager::CardManager() = default;


void CardManager::createStudentCard(const std::string &sno, const std::string &name, const Gender gender, const std::string &affiliation)
{
	if (!StudentCard::isProperId(sno))
	{
		throw std::runtime_error("Invalid student card ID format: " + sno);
	}
	if (cards.contains(sno))
	{
		throw std::runtime_error("Card ID already exists: " + sno);
	}
	cards[sno] = std::make_unique<StudentCard>(name, gender, affiliation, sno);
}

void CardManager::createTeacherCard(const std::string &tno, const std::string &name, const Gender gender, const std::string &affiliation)
{
	if (!TeacherCard::isProperId(tno))
	{
		throw std::runtime_error("Invalid teacher card ID format: " + tno);
	}
	if (cards.contains(tno))
	{
		throw std::runtime_error("Card ID already exists: " + tno);
	}
	cards[tno] = std::make_unique<TeacherCard>(name, gender, affiliation, tno);
}

Card &CardManager::getCard(const std::string &cardId) const {
	if (!cards.contains(cardId)) {
		throw std::runtime_error("Card ID does not exist: " + cardId);
	}
	return *cards.at(cardId);
}

bool CardManager::hasCard(const std::string &cardId) const {
	return cards.contains(cardId);
}

void CardManager::readFile()
{
	std::ifstream ifs("cards.dat", std::ios::binary);
	if (!ifs) return;
	cards.clear();

	char typeTag;
	while (ifs.read(&typeTag, 1))
	{
		if (const auto cardType = static_cast<CardType>(typeTag); cardType == CardType::STUDENT)
		{
			auto card = std::make_unique<StudentCard>();
			ifs >> *card;
			cards[card->getCardId()] = std::move(card);
		}
		else if (cardType == CardType::TEACHER)
		{
			auto card = std::make_unique<TeacherCard>();
			ifs >> *card;
			cards[card->getCardId()] = std::move(card);
		}
	}
}

void CardManager::saveFile()
{
	std::ofstream ofs("cards.dat", std::ios::binary);
	for (const auto &card: cards | std::views::values)
	{
		const auto typeTag = static_cast<char>(card->getCardType());
		ofs.write(&typeTag, 1);

		if (const auto *sc = dynamic_cast<const StudentCard *>(card.get()))
		{
			ofs << *sc;
		}
		else if (const auto *tc = dynamic_cast<const TeacherCard *>(card.get()))
		{
			ofs << *tc;
		}
		else {
			throw std::runtime_error("Unknown card type");
		}
	}
}
