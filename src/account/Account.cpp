#pragma once
#include <vector>
#include <string>
#include "transaction/Transaction.h"

Account::Account(
	const std::string& name,
	double initialBalance = 0.0
): 

	m_name(name)
	m_Balance(initialBalance)
{}

std::string Account::getName() const { return m_name; }
double Account::getBalance() const{ return m_Balance; }

// Add a transaction to the account
void Account::addTransaction(const Transaction& transaction) {
	// Add the transaction to the list of transactions
	m_transactions.push_back(transaction);

	// Update account balance based on transaction type
	if (transaction.getType() == Transaction::Type::INCOME) {
        	m_balance += transaction.getAmount();
    	} else if (transaction.getType() == Transaction::Type::EXPENSE) {
        	m_balance -= transaction.getAmount();
    }
}

// Get current balance
double Account::getBalance() const {
    return m_balance;
}

// Get account name
std::string Account::getName() const {
    return m_name;
}

// Get all transactions
const std::vector<Transaction>& Account::getTransactions() const {
    return m_transactions;
}
