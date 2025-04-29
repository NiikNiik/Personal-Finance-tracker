#include "FinanceManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void FinanceManager::createAccount(const std::string& name, double initialBalance){
    // Check if account with same name already exists
    for (const auto& account : m_accounts) {
        if (account.getName() == name) {
            throw std::runtime_error("Account with name " + name + " already exists");
        }
    }

    // Create and add new account
    m_accounts.emplace_back(name, initialBalance);
}

// Add transaction to an account
void Finance::addTransaction(
     const std::string& accountName, 
     double amount, 
     Transaction::Type type, 
     const std::string& description
){
    // Find the account
    Account* account = findAccount(accountName);

    // If account not found, throw an exception
    if (!account) {
        throw std::runtime_error("Account not found: " + accountName);
    }

    // Create and add transaction
    Transaction transaction(amount, type, description);
    account->addTransaction(transaction);
};

// Get total balance across all accounts
double FinanceManager::getTotalBalance() const{
    double totalBalance = 0.0;
    
    // Sum balances of all accounts
    for (const auto& account : m_accounts) {
        totalBalance += account.getBalance();
    }

    return totalBalance;
};

// Save transactions to file
void FinanceManager::saveToFile(const std::string& filename) const{
    // Open file for writing
    std::ofstream file(filename);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Write each account's transactions
    for (const auto& account : m_accounts) {
        // Write account name
        file << "Account: " << account.getName() << "\n";

        // Write each transaction
        for (const auto& transaction : account.getTransactions()) {
            file << (transaction.getType() == Transaction::Type::INCOME ? "INCOME" : "EXPENSE")
                 << "," << transaction.getAmount()
                 << "," << transaction.getDescription()
                 << "," << transaction.getTimestamp() 
                 << "\n";
        }

        // Separator between accounts
        file << "---\n";
    }

    file.close();
};

// Load transactions from file
void FinanceManager::loadFromFile(const std::string& filename){
    // Clear existing accounts
    m_accounts.clear();

    // Open file for reading
    std::ifstream file(filename);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    Account* currentAccount = nullptr;

    // Read file line by line
    while (std::getline(file, line)) {
        // Check for account header
        if (line.substr(0, 8) == "Account:") {
            std::string accountName = line.substr(9);
            // Create a new account
            createAccount(accountName);
            // Get pointer to newly created account
            currentAccount = &m_accounts.back();
            continue;
        }

        // Skip separator
        if (line == "---") continue;

        // Parse transaction
        std::istringstream iss(line);
        std::string typeStr, amountStr, description, timestampStr;

        // Parse CSV line
        std::getline(iss, typeStr, ',');
        std::getline(iss, amountStr, ',');
        std::getline(iss, description, ',');
        std::getline(iss, timestampStr);

        // Convert strings to appropriate types
        Transaction::Type type = (typeStr == "INCOME") 
            ? Transaction::Type::INCOME 
            : Transaction::Type::EXPENSE;
        
        double amount = std::stod(amountStr);
        time_t timestamp = std::stoll(timestampStr);

        // Create and add transaction
        if (currentAccount) {
            Transaction transaction(amount, type, description);
            currentAccount->addTransaction(transaction);
        }
    }

    file.close();
};

// Get all accounts
const std::vector<Account>& FinanceManager::getAccounts() const{
	return m_accounts;
};

// Helper method to find an account by name
Account* FinanceManager::findAccount(const std::string& name) {
    // Find account with matching name
    for (auto& account : m_accounts) {
        if (account.getName() == name) {
            return &account;
        }
    }
    
    // Return nullptr if no account found
    return nullptr;
}
