#include <iostream>
#include <map>
#include <fstream>
#include "Bank.h"
#include "Accounts.h"

/*
 *  6.1.  Режим ряда значений — это значение, которое появляется чаще всего.
 *  Реализуйте функцию mode («режим»), используя следующую сигнатру:
 *  int mode (const int * values, size_t length). Если вы столкнулись с ошибкой,
 *  такой как ввод с несколькими режимами и без значений, верните ноль.
 *
 *  6.2. Реализуйте mode как шаблонную функцию.
 *
 *  6.3. Модифицируйте mode,чтобы принимать концепт Integer.
 *  Убедитесь,что mode не может быть создана с типами с плавающей точкой, такими как double.
 *
 *  6.4. Перепишите mean из листинга 6.13 для принятия массива,а не указателя и аргументов длины.
 *  Используйте листинг 6.33 как руководство.
 *
 *  6.5. Используя пример из главы 5,сделайте Bank классом шаблона,
 *  который принимает параметр шаблона. Используйте этот параметр типа в качестве
 *  типа учетной записи вместо long. Убедитесь, что код все еще работает, используя класс Bank<long>.
 *
 *  6.6. Реализуйте класс Account и создайте экземпляр Bank <Account>.
 *  Реализуйте функции в Account, чтобы отслеживать баланс.
 *
 *  6.7. Сделайте Account интерфейсом.РеализуйтеCheckingAccount(«расчетный счет»)
 *  и SavingsAccount («сберегательный счет»). Создайте программу с несколькими расчетными
 *  и сберегательными счетами. Используйте Bank<Account> для совершения нескольких транзакций между счетами.
 *
 */

//1-3
template <typename T>
T mode (const T* values, size_t length)
{
    static_assert(std::is_integral<T>(), "Should be integral class");
    T answer = 0;
    int max_count = 0;
    std::map<T, int> map_values;
    if (!length)
        return answer;

    for (int i = 0; i < length; i++)
    {
        map_values[values[i]]++;
    }

    for (std::pair<T,int> pair : map_values)
    {
        if (pair.second > max_count) {
            answer = pair.first;
            max_count = pair.second;
        }
    }
    return answer;
}

//4
template <typename T, size_t length>
T mean(T (&arr)[length]){
    static_assert(std::is_arithmetic<T>(), "Should be arithmetic");
    static_assert(length > 0, "Must be at least 1 element");

    T answ = 0;
    for (int i = 0; i < length; i++)
    {
       answ += arr[i];
    }
    return answ/length;
};

int main() {
    int modes[] = {1,1,1,2,3,4,1,2,3,1,5};
    std::cout << mode(modes,11) << std::endl;
//    Wrong
//    double modes_d[] = {1.0f,1.0f,1.0f,2.0f,3.0f,4.0f,1.0f,2.0f,3.0f,1.0f,5.0f};
//    std::cout << mode(modes_d,11);
    char chars[] = {1};
    std::cout << mean(modes) << std::endl;

    std::cout << mean(chars) << std::endl;

    InMemoryAccountDatabase* mdb = new InMemoryAccountDatabase();
    mdb->add_account(99, 500);
    mdb->add_account(1, 56);
    mdb->add_account(13, 69);
    mdb->add_account(14, 88);

    Bank<long> a{mdb};

    a.makeTranfer(1, 13, 31);
    a.getAccountBalance(13);
    a.getAccountBalance(1);

    Bank2 b2{};
    SavingAccount acc1{};
    CheckingAccount acc2{};

    b2.makeTransfer(acc1, acc2, 100.f);
    b2.report(acc1);
    b2.report(acc2);

    return 0;
}
