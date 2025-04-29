#pragma once
#include <vector>
#include <string>
#include "account/Account.h"

class FinanceManager {
public:
    // Add a new account
    void createAccount(const std::string& name, double initialBalance = 0.0);

    // Add transaction to an account
    void addTransaction(
        const std::string& accountName, 
        double amount, 
        Transaction::Type type, 
        const std::string& description
    );

    // Get total balance across all accounts
    double getTotalBalance() const;

    // Save transactions to file
    void saveToFile(const std::string& filename) const;

    // Load transactions from file
    void loadFromFile(const std::string& filename);

    // Get all accounts
    const std::vector<Account>& getAccounts() const;

private:
    std::vector<Account> m_accounts;

    // Helper to find account by name
    Account* findAccount(const std::string& name);
};
