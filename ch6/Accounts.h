//
// Created by Nikita Shuplyakov on 20/06/2023.
//

#ifndef CH6_ACCOUNTS_H
#define CH6_ACCOUNTS_H


struct Account{
    Account() : balance{0} {};
    Account(double balance) : balance{balance} {};
    virtual ~Account() = default;
    virtual double getBalance(){return balance;};
    virtual void withdraw(double sum){
        balance-=sum;
    }
    virtual void deposit(double sum){
        balance+=sum;
    }

private:
    double balance;
};

struct SavingAccount:Account{};
struct CheckingAccount:Account{};

#endif //CH6_ACCOUNTS_H
