#include <string>
#include <vector>
#include<memory>
#include <iostream>
using namespace std;
void showMenu() {

    cout << "\n========== CORE BANKING SIMULATION ==========\n";

    cout << "1. Show all accounts\n";

    cout << "2. Deposit money\n";

    cout << "3. Withdraw money\n";

    cout << "4. Transfer money\n";

    cout << "5. Apply monthly update\n";

    cout << "6. Rollback last operation\n";

    cout << "7. Show history\n";

    cout << "0. Exit\n";

    cout << "Choose option: ";

}

// ===================== MAIN =====================

int main() {

    Bank bank;

    Client c1(1, "Yasmin");

    Client c2(2, "Ali");

    Client c3(3, "Amina");

    bank.addAccount(make_unique<SavingsAccount>(1001, c1, 1000, 0.05));

    bank.addAccount(make_unique<CheckingAccount>(1002, c2, 700, 2));

    bank.addAccount(make_unique<CreditAccount>(1003, c3, 300, 1000, 0.03));

    int choice;

    do {

        showMenu();

        cin >> choice;

        try {

            if (choice == 1) {

                bank.showAccounts();

            }

            else if (choice == 2) {

                int id;

                double amount;

                cout << "Enter account ID: ";

                cin >> id;

                cout << "Enter amount: ";

                cin >> amount;

                bank.executeCommand(

                    make_unique<DepositCommand>(bank.getAccount(id), amount)

                );

            }

            else if (choice == 3) {

                int id;

                double amount;

                cout << "Enter account ID: ";

                cin >> id;

                cout << "Enter amount: ";

                cin >> amount;

                bank.executeCommand(

                    make_unique<WithdrawCommand>(bank.getAccount(id), amount)

                );

            }

            else if (choice == 4) {

                int fromId, toId;

                double amount;

                cout << "Enter sender account ID: ";

                cin >> fromId;

                cout << "Enter receiver account ID: ";

                cin >> toId;

                cout << "Enter amount: ";

                cin >> amount;

                bank.executeCommand(

                    make_unique<TransferCommand>(

                        bank.getAccount(fromId),

                        bank.getAccount(toId),

                        amount

                    )

                );

            }

            else if (choice == 5) {

                bank.executeCommand(

                    make_unique<MonthlyUpdateCommand>(bank.getAllAccounts())

                );

            }

            else if (choice == 6) {

                bank.rollbackLast();

            }

            else if (choice == 7) {

                bank.showHistory();

            }

            else if (choice == 0) {

                cout << "Program finished." << endl;

            }

            else {

                cout << "Invalid option." << endl;

            }

        }

        catch (const exception& e) {

            cout << "Error: " << e.what() << endl;

        }

    } while (choice != 0);
}
//Модель банковской системы(Core Banking
//	Simulation)
//	Суть проекта : Проектирование внутренней логики банка : ведение счетов, проведение транзакций, начисление процентов и кредитный конвейер.
//	﻿﻿Техническое задание :
//﻿﻿Иерархия счетов : Абстрактный класс Account.Наследники : SavingsAccount(сберегательный, с начислением% по правилу), CheckingAccount(расчетный, с комиссией за переводы), CreditAccount(кредитный, с возможностью ухода в минус под процент.
//	﻿﻿Безопасность транзакций : Класс Transaction, инкапсулирующий перевод между счетами.Реализовать механизм отката транзакции(rollback()) при возникновении ошибок(например, нехватка средств на стороне отправителя в момент финализации).
//	﻿﻿Паттерн Command(Команда) : Все операции(депозит, снятие, перевод,
//		начисление процентов) реализуются как объекты - команды.Это позволяет хранить историю операций в std : vector<std. : unique_ptr<Command>> для аудита.
//	﻿﻿Бизнес - логика : Класс Bank, управляющий клиентами и счетами.Корректная обработка исключений(throw - catch) при попытках несанкционированного доступа или нарушении лимитов.

