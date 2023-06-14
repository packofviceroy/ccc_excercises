#include <iostream>
#include <fstream>
#include <map>

struct BaseStruct{
    static int count;
    void PrintCount()
    {
        std::cout << count << std::endl;
    }
private:
};
int BaseStruct::count = 0;

struct DerivedStruct: BaseStruct{
    DerivedStruct(){count++;}
};
/*
5.1. В Bank не была внедрена система бухгалтерского учета. Разработайте
        интерфейс под названием AccountDatabase , который может извлекать
        и устанавливать суммы на банковских счетах (идентифицируемых с помощью long id).
5.2. Создайте InMemoryAccountDatabase , реализующую AccountDatabase .
5.3. Добавьте ссылочный элемент AccountDatabase в Bank . Используйте внедрение
        через конструктор для добавления InMemoryAccountDatabase в Bank .
5.4. Измените ConsoleLogger , чтобы принимать const char* при создании. При
        записи в ConsoleLogger добавьте эту строку к выводу журнала. Обратите внимание,
        что можно изменить поведение при ведении журнала, не изменяя Bank .
*/
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

struct Bank {
    Bank(Logger* new_logger, AccountDatabase* new_db) {
        logger = new_logger;
        db = new_db;
    }
    Bank(AccountDatabase* new_db) {
        logger = nullptr;
        db = new_db;
    }

    void makeTranfer(long from, long to, double amount)
    {
        db->transfer(from, to, amount);
        if (logger)
            logger->printLogs(from, to, amount);
    }

    void setLogger(Logger* new_logger){
        logger = new_logger;
    }

    void getAccountBalance(long id)
    {
        db->printAccount(id);
    }

private:
    Logger* logger;
    AccountDatabase* db;
};


int main() {

    //Test inheriting of static members of
    // parent class
    std::cout << "Hello, World!" << std::endl;
    DerivedStruct a1;
    DerivedStruct a2;
    DerivedStruct a3;
    BaseStruct b1;

    b1.PrintCount();
    //Task
    FileLogger flog{"./log"};
    ConsoleLogger cloger;
    ConsoleLogger cloger2{"MONEY HAVE BEEN SENT"};

    InMemoryAccountDatabase mdb;
    mdb.add_account(99, 500);
    mdb.add_account(1, 56);
    mdb.add_account(13, 69);
    mdb.add_account(14, 88);


    Bank b{&mdb};

    b.makeTranfer(1, 13, 31);
    b.getAccountBalance(13);
    b.getAccountBalance(1);
    b.setLogger(&cloger);
    b.makeTranfer(99, 14, 100);
    b.getAccountBalance(14);
    b.setLogger(&flog);
    b.makeTranfer(99, 1, 200);
    b.getAccountBalance(1);
    b.getAccountBalance(99);
    b.setLogger(&cloger2);
    b.makeTranfer(13, 1, 1);

    return 0;
}
