#pragma once

#include "Card.h"
#include <vector>
#include <hash_map>

class CardManager
{
public:
	CardManager();
	~CardManager() = default;

	// File IO
	void readFile();
	void saveFile();

	// Card Operations
	void createStudentCard(std::string &sno, std::string &name, Gender gender, const std::string &affiliation);
	void createTeacherCard(std::string &tno, std::string &name, Gender gender, const std::string &affiliation);
	Card &getCard(std::string &cardId);
private:
	std::hash_map<std::string, Card> cards;
};

