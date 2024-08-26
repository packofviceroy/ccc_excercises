//
// Created by Nikita Shuplyakov on 20/06/2023.
//

#ifndef CH6_BANK_H
#define CH6_BANK_H

struct AccountDatabase{
    virtual void transfer(long from, long to, double amount)=0;
    virtual void printAccount(long id)=0;
};

struct InMemoryAccountDatabase:AccountDatabase{
    void transfer(long from, long to, double amount) override
    {
        db[from]-=amount;
        db[to]+=amount;
    }
    void printAccount(long id) override{
        std::cout << "Available " << db[id] << " money on " << id << " account" << std::endl;
    }
    void add_account(long id, double money)
    {
        db.insert(std::make_pair(id, money));
    }
private:
    std::map<long, double> db;
};

struct Logger{
    virtual ~Logger() = default;
    virtual void printLogs(long from, long to, double amount)=0;
};

struct ConsoleLogger:Logger{
    ConsoleLogger(std::string s):appending_string{s}{}
    ConsoleLogger():appending_string{}{}

    void printLogs(long from, long to, double amount) override{
        std::cout << "[log] Transfered " << amount << " From " << from << " To " << to << std::endl;
        if (appending_string.length() !=0)
            std::cout << "With message: " << appending_string << std::endl;
    }

private:
    std::string appending_string;
};

struct FileLogger:Logger {
    FileLogger()=delete;
    FileLogger(std::string path){
        log_file.open(path, std::ios::app);
    }
    void printLogs(long from, long to, double amount) override{
        log_file << "[log] Transfered " << amount << " From " << from << " To " << to << std::endl;
    }
private:
    std::fstream log_file;
};

template <typename T>
struct Bank {
    Bank(Logger* new_logger, AccountDatabase* new_db) {
        logger = new_logger;
        db = new_db;
    }
    Bank(AccountDatabase* new_db) {
        logger = nullptr;
        db = new_db;
    }

    void makeTranfer(T from, T to, double amount)
    {
        db->transfer(from, to, amount);
        if (logger)
            logger->printLogs(from, to, amount);
    }

    void setLogger(Logger* new_logger){
        logger = new_logger;
    }

    void getAccountBalance(T id)
    {
        db->printAccount(id);
    }

private:
    Logger* logger;
    AccountDatabase* db;
};


struct Bank2{
    template<typename AccT1, typename AccT2>
    void makeTransfer(AccT1& acc1, AccT2& acc2, double sum){
        acc1.withdraw(sum);
        acc2.deposit(sum);
    }
    template<typename AccT>
    void report(AccT& a)
    {
        std::cout << "Account has " << a.getBalance() << " money on it" << std::endl;
    }
};

#endif //CH6_BANK_H
