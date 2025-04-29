#pragma once
#include <string> 
#include <ctime> 

class Transaction{
public:
	//Enum through transaction type
	enum class Type{
	   INCOME,
	   EXPENSE
	};

	//constructor
	Transaction(double amount, Type type, const std::string& description);

	//Getter
	double getAmount() const;
	Type getType() const;
	std::string getDescription() const;
	time_t getTimestamp const;

	//String representation of transaction
	std::string toString() const;

private:
	double m_amount;
	Type m_type;
	std::string m_description;
	time_t m_timestamp;


};
