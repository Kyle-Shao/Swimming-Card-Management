#pragma once

#include "Card.h"
#include <unordered_map>
#include <memory>

class CardManager
{
public:
	CardManager();
	~CardManager() = default;

	// File IO
	void readFile();
	void saveFile();

	// Card Operations
	void createStudentCard(const std::string &sno, const std::string &name, Gender gender, const std::string &affiliation);
	void createTeacherCard(const std::string &tno, const std::string &name, Gender gender, const std::string &affiliation);
	Card &getCard(const std::string &cardId);
private:
	std::unordered_map<std::string, std::unique_ptr<Card>> cards;
};

