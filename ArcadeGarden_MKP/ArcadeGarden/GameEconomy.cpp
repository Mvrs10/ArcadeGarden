#include "GameEconomy.h"
#include <memory>
#include <cmath> // for std::round
#include <iomanip>

using namespace std;
template <typename T> T Wallet::AddCurrency(T extra, T current) { // Template
    if (current <= 100) {
        extra *= static_cast<T>(1.5);
    }
    else if (current > 100 && current < 500) {
        extra *= static_cast<T>(1.3333);
    }
    T result = current + extra;

    // Round to 2 decimal places
    result = std::round(result * 100) / 100;
    cout << "MK_Bucks Loaded: M$" << std::setprecision(2) << std::fixed << result << endl;
    return result;
}

double Do_Game_Utility() {
    double result;
    std::shared_ptr< Wallet > walletPtr = std::make_shared< Wallet >();
    std::shared_ptr< Item > itemPtr = std::make_shared< Item >();
    walletPtr->itemPtr = itemPtr;
    itemPtr->walletPtr = walletPtr; // No cycle now
    result = walletPtr->AddCurrency(100.00, 400.05);
    cout << "End of scope" << endl;
    return result;
}