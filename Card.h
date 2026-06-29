#pragma once

#include <string>
#include <vector>
#include "Bill.h"

#define str std::string

enum Gender
{
	MALE,
	FEMALE
};

enum class CardType : char
{
	STUDENT = 1,
	TEACHER = 2
};

class Card
{
public:
	Card();
	Card(str name, Gender gender, str affiliation, str cardId);

	// Getter / Setter
	[[nodiscard]] str getName() const;
	void setName(const str &newName);
	[[nodiscard]] Gender getGender() const;
	void setGender(Gender newGender);
	[[nodiscard]] str getAffiliation() const;
	void setAffiliation(const str &newAffiliation);
	[[nodiscard]] str getCardId() const;
	[[nodiscard]] bool isLost() const;
	void setIsLost(bool newLost);
	[[nodiscard]] int getBalance() const;
	[[nodiscard]] std::vector<Bill> &getBills();

	// Safety check
	static bool isProperId(const str &id);

	// Type identification for polymorphic serialization
	[[nodiscard]] virtual CardType getCardType() const = 0;

	// Balance operations
	virtual void consume(int money);
	void charge(int money);
	virtual void consume();

	// Bill recording
	void recordBill(int amount);

	// File IO
	friend std::istream &operator>>(std::istream &is, Card &card);
	friend std::ostream &operator<<(std::ostream &os, const Card &card);

	virtual ~Card();
private:
	std::string name;
	Gender gender; 
	std::string affiliation;
	std::string cardId;
	bool lost;
	int balance;
	std::vector<Bill> bills;
};
