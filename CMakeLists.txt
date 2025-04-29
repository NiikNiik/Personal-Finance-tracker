cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceTracker VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add main executable
add_executable(finance_tracker 
    src/main.cpp
    src/transaction/Transaction.cpp
    src/account/Account.cpp
    src/manager/FinanceManager.cpp
)

# Include directories
target_include_directories(finance_tracker PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

# Enable testing
enable_testing()

# Add test subdirectory
add_subdirectory(tests)
