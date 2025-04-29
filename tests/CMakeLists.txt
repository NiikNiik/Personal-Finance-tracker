# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
add_executable(finance_tests 
    test_transaction.cpp
    test_account.cpp
    test_finance_manager.cpp
    # Source files to test
    ../src/transaction/Transaction.cpp
    ../src/account/Account.cpp
    ../src/manager/FinanceManager.cpp
)

# Include directories for tests
target_include_directories(finance_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(finance_tests 
    ${GTEST_LIBRARIES}
    pthread
)

# Add tests to CTest
add_test(NAME FinanceTrackerTests COMMAND finance_tests)
