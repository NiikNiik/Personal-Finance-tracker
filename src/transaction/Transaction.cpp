#include "Transaction.h"
#include <sstream> // allows conversion between strings and other typrd
#include <iomanip> // Provides formatting manipulators for input/output streams. Used for the 2 decimals in money

Transaction::Transaction(
	double amount,  // Amount of the transaction
	Type type,  // Type of transaction (INCOME or EXPENSE)
	const std::string& description // Description of the transaction
):

	m_amount(amount),
	m_type(type),
	m_description(description),
	m_timestamp(std::time(nullptr))
{}

double Transaction:: getAmount() const { return m_amount; }
Transaction::Type Transaction::getType() const{ return m_type; }
std::string Transaction::getDescription() const { return m_description; }
time_t Transaction::getTimestamp() const { return m_timestamp; }

std::string Transaction::toString() const{
	std::ostringstream oss; //oss could also mean "output"
	oss << std::fixed << std::setprecision(2);
	
	oss << "Amount: $" << m_amount
	    << " | Type: " << (m_type == Type::INCOME ? "Income" : "Expense")
	    << " | Description: " << m_description;

	return oss.str();
}
