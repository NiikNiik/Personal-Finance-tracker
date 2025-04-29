#pragma once
#include <vector> 
#include <string>
#include "transaction/Transaction.h"

class Account {
public 
	Account(const std::string& name, double initialBalance  = 0.0);
	
	// Add a transaction
	void addTransaction(const Transaction& transaction);
	
	//Get balance
	double getBalance() const;

	//Get account name
	std::string getName() const;

	//Get all transactions
	const std::vector<Transaction>& getTransactions() const;

private:
	std::string m_name;
	double m_balancel
	std::vector<Transaction>m_transactions;

}
