class Account {
protected:
	string owner;
	double balance;
public:
	Account(string owner, double balance = 0) :owner(owner), balance(balance) {}
	virtual ~Account() = default;
	virual void deposit(double amount) {
		balance += amount;
	}
	virtual void withdraw(double amount) {
		if (balance < amount) {
			throw runtime_error("not enough money");
		}
		else {
			balance -= amount;
		}
	}
	double getBalance() const { return balance };
	virtual void applyMonthly() = 0;
};
class SavingsAccount :public Account {
protected:
	double interestRate;
public:
	SavingsAccount(string owner, double balance = 0, double rate) :Account(owner, balance), interestRate(rate) {}
	void applyMonthly() override {
		balance += balance * interestRate;
	}
};
class CheckingAccount :public Account {
protected:
	double fee;
public:
	CheckingAccount(string owner, double balance = 0, double fee) :Account(owner, balance), fee(fee) {}
	void withdraw() override {
		Account::withdraw(amount + fee);
	}
	void applyMonthly() override {}
};
class CreditAccount :public Account {
protected:
	double debtRate;
	CreditAccount(string ownwer, double balance = 0, double debt) :Account(owner, balance), debtRate(debt) {}
	void withdraw() override {
		balance -= amount;
	}
	void applyMonthly() override {
		if (balance < 0) {
			balance *= debtRate;
		}
	}
};

//Модель банковской системы(Core Banking
//	Simulation)
//	Суть проекта : Проектирование внутренней логики банка : ведение счетов, проведение транзакций, начисление процентов и кредитный конвейер.
//	﻿﻿Техническое задание :
//﻿﻿Иерархия счетов : Абстрактный класс Account.
// Наследники : SavingsAccount(сберегательный, с начислением% по правилу),
//  CheckingAccount(расчетный, с комиссией за переводы),
//  CreditAccount(кредитный, с возможностью ухода в минус под процент.\
// 
//	﻿﻿Безопасность транзакций : Класс Transaction, инкапсулирующий перевод между счетами.
// Реализовать механизм отката транзакции(rollback()) при возникновении ошибок(например, нехватка средств на стороне отправителя в момент финализации).
//	﻿﻿Паттерн Command(Команда) : Все операции(депозит, снятие, перевод,
//		начисление процентов) реализуются как объекты - команды.Это позволяет хранить историю операций в std : vector<std. : unique_ptr<Command>> для аудита.
//	﻿﻿Бизнес - логика : Класс Bank, управляющий клиентами и счетами.Корректная обработка исключений(throw - catch) при попытках несанкционированного доступа или нарушении лимитов.

