#include <gtest/gtest.h>
#include "manager/FinanceManager.h"
#include <fstream>
#include <cstdio>  // for removing files

class FinanceManagerTest : public ::testing::Test {
protected:
    FinanceManager* manager;

    void SetUp() override {
        // Create a fresh FinanceManager for each test
        manager = new FinanceManager();
    }

    void TearDown() override {
        // Clean up after each test
        delete manager;
    }

    // Helper method to create test data
    void createTestAccounts() {
        manager->createAccount("Checking", 1000.0);
        manager->createAccount("Savings", 5000.0);
    }
};

// Test creating accounts
TEST_F(FinanceManagerTest, CreateAccountTest) {
    // Create two accounts
    manager->createAccount("Checking", 1000.0);
    manager->createAccount("Savings", 5000.0);

    // Verify account creation
    EXPECT_EQ(manager->getAccounts().size(), 2);
    
    // Check first account details
    EXPECT_EQ(manager->getAccounts()[0].getName(), "Checking");
    EXPECT_DOUBLE_EQ(manager->getAccounts()[0].getBalance(), 1000.0);
    
    // Check second account details
    EXPECT_EQ(manager->getAccounts()[1].getName(), "Savings");
    EXPECT_DOUBLE_EQ(manager->getAccounts()[1].getBalance(), 5000.0);
}

// Test adding transactions
TEST_F(FinanceManagerTest, AddTransactionTest) {
    // Create test accounts
    createTestAccounts();

    // Add transactions to checking account
    manager->addTransaction(
        "Checking", 
        500.0, 
        Transaction::Type::INCOME, 
        "Salary"
    );
    manager->addTransaction(
        "Checking", 
        -200.0, 
        Transaction::Type::EXPENSE, 
        "Groceries"
    );

    // Add transactions to savings account
    manager->addTransaction(
        "Savings", 
        1000.0, 
        Transaction::Type::INCOME, 
        "Investment Return"
    );

    // Verify total balance
    EXPECT_DOUBLE_EQ(manager->getTotalBalance(), 6300.0);
}

// Test total balance calculation
TEST_F(FinanceManagerTest, TotalBalanceTest) {
    createTestAccounts();

    // Add various transactions
    manager->addTransaction("Checking", 500.0, Transaction::Type::INCOME, "Salary");
    manager->addTransaction("Checking", -200.0, Transaction::Type::EXPENSE, "Groceries");
    manager->addTransaction("Savings", 1000.0, Transaction::Type::INCOME, "Bonus");

    // Verify balance
    EXPECT_DOUBLE_EQ(manager->getTotalBalance(), 6300.0);
}

// Test file saving and loading
TEST_F(FinanceManagerTest, FileSaveLoadTest) {
    // Create test file path
    std::string testFilePath = "test_transactions.txt";

    // Create and populate accounts
    createTestAccounts();
    manager->addTransaction("Checking", 500.0, Transaction::Type::INCOME, "Salary");
    manager->addTransaction("Savings", 1000.0, Transaction::Type::INCOME, "Bonus");

    // Save to file
    manager->saveToFile(testFilePath);

    // Create a new manager to load from file
    FinanceManager loadedManager;
    loadedManager.loadFromFile(testFilePath);

    // Verify loaded data
    EXPECT_EQ(loadedManager.getAccounts().size(), 2);
    EXPECT_DOUBLE_EQ(loadedManager.getTotalBalance(), 7500.0);

    // Clean up test file
    std::remove(testFilePath.c_str());
}

// Test duplicate account creation
TEST_F(FinanceManagerTest, DuplicateAccountTest) {
    // First account creation should succeed
    manager->createAccount("Checking", 1000.0);

    // Second account with same name should throw
    EXPECT_THROW({
        manager->createAccount("Checking", 2000.0);
    }, std::runtime_error);
}

// Test adding transaction to non-existent account
TEST_F(FinanceManagerTest, TransactionToNonExistentAccountTest) {
    EXPECT_THROW({
        manager->addTransaction(
            "NonExistentAccount", 
            500.0, 
            Transaction::Type::INCOME, 
            "Test Transaction"
        );
    }, std::runtime_error);
}

// Test complex transaction scenarios
TEST_F(FinanceManagerTest, ComplexTransactionTest) {
    manager->createAccount("Checking", 1000.0);

    // Multiple transactions
    struct TestTransaction {
        double amount;
        Transaction::Type type;
        std::string description;
    };

    std::vector<TestTransaction> transactions = {
        {500.0, Transaction::Type::INCOME, "Salary"},
        {-200.0, Transaction::Type::EXPENSE, "Groceries"},
        {-50.0, Transaction::Type::EXPENSE, "Coffee"},
        {100.0, Transaction::Type::INCOME, "Refund"}
    };

    // Add all transactions
    for (const auto& trans : transactions) {
        manager->addTransaction(
            "Checking", 
            trans.amount, 
            trans.type, 
            trans.description
        );
    }

    // Verify final balance
    EXPECT_DOUBLE_EQ(manager->getAccounts()[0].getBalance(), 1350.0);
}

// Main function for running all tests
int main(int argc, char **argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run all tests
    return RUN_ALL_TESTS();
}
