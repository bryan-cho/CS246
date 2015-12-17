#include <iostream>
#include <cstdlib>

struct Wallet {
    static Wallet* instance;
    static Wallet* getInstance();
    static void cleanup();
    Wallet();
    int money;
    void addMoney(int amount);
};

void Wallet::cleanup() {
    delete instance;
}

Wallet* Wallet::instance = NULL;
Wallet* Wallet::getInstance() {
    if (instance == NULL) {
        instance = new Wallet;
        atexit(cleanup);
    }
    return instance;
}

Wallet::Wallet() : money(0) {}

void Wallet::addMoney(int amount) {
    this->money += amount;
}

struct Expense {
    const int amt;
    Wallet *wallet;
    Expense (int amt) : amt(amt) {
        wallet = Wallet::getInstance();
    }
    void pay() {
        this->wallet->addMoney(-1 * this->amt);
    }
};

int main() {
    Expense a(10);
    Expense b(15);
    Expense c(10);
    Wallet *wallet = Wallet::getInstance();
    Expense pay(-1000);
    pay.pay();
    std::cout << wallet->money << std::endl;
    a.pay();
    std::cout << wallet->money << std::endl;
    b.pay();
    std::cout << wallet->money << std::endl;
    c.pay();
    std::cout << wallet->money << std::endl;
}
