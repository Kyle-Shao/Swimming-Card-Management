#pragma once

#include <string>
#include <vector>
#include "Bill.h"
#include <iostream>

#define str std::string

enum Gender
{
	MALE,
	FEMALE
};

class Card
{
public:
	Card();
	Card(const str &name, const Gender gender, const str &affiliation, const str &cardId);

	// Getter / Setter
	[[nodiscard]] str getName() const;
	void setName(const str &newName);
	[[nodiscard]] Gender getGender() const;
	void setGender(const Gender gender);
	[[nodiscard]] str getAffiliation() const;
	void setAffiliation(const str &newAffi);
	[[nodiscard]] str getCardId() const;
	[[nodiscard]] bool isLost() const;
	void setIsLost(const bool newLost);
	[[nodiscard]] int getBalance();
	[[nodiscard]] std::vector<Bill> &getBills();

	// Safety check
	virtual bool isProperId(const str &id);

	// Balance operations
	virtual void consume(const int money);
	void charge(const int money);
	virtual void consume();

	// Bill recording
	void recordBill(const int amount);

	// File IO
	virtual void read(std::istream is);
	virtual void write(std::ostream os);

	virtual ~Card();
private:
	std::string name;
	Gender gender; 
	std::string affiliation;
	const std::string cardId;
	bool lost;
	int balance;
	std::vector<Bill> bills;
};
