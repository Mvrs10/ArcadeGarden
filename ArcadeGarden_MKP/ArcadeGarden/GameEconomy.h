#pragma once
#include <iostream>
#include <memory>

using namespace std;
class Wallet; // Forward declaration
class Item {
public:
    std::shared_ptr< Wallet > walletPtr;
    ~Item() { cout << "Item destroyed" << endl; }
};
class Wallet {
public:
    std::weak_ptr< Item > itemPtr; // Creates a cycle
    ~Wallet() { std::cout << "Wallet destroyed" << endl; }
    template <typename T> T AddCurrency(T extra, T current); // Template
};

double Do_Game_Utility();