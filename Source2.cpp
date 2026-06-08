class Client {
private:
	int id;
	string name;
public:
	Client(int id,string name):id(id),name(name){}
	int getId() const {
		return id;
	}
	string getName() const {
		return name;
	}
};

class Account {
protected:
	int accountId;
	Client client;
	double balance;
public:
	Account(int accountId,Client client, double balance = 0) :accountId(accountId),client(client), balance(balance) {}
	virtual ~Account() = default;
	virual void deposit(double amount) {
		balance += amount;
	}
	int getAccountId() const {
		return accountId;
	}
	string getOwnerName() const {
		return client.getName();
	}
	virtual string getType() const = 0;
	virtual void deposit(double amount) {
		if (amount <= 0) {
			throw invalid_argument("deposit amount must be positive");
		}
		balance += amount;
	}
	virtual void withdraw(double amount) {
		if (amount <= 0) {
			throw invalid_argument("withdrawal amount must be positive");
		}
		if (balance < amount) {
			throw runtime_error("not enough money");
		}
		balance -= amount;
	}
	double getBalance() const { return balance };
	virtual void applyMonthly() = 0;
	virtual void printInfo() const {

		cout << left << setw(12) << accountId

			<< setw(18) << getOwnerName()

			<< setw(18) << getType()

			<< fixed << setprecision(2) << balance << endl
	}
};
class SavingsAccount :public Account {
protected:
	double interestRate;
public:
	SavingsAccount(int accountId, Client client, double balance = 0, double rate) :Account(accountId, client, balance), interestRate(rate) {}
	void applyMonthly() override {
		balance += balance * interestRate;
	}
	string getType() const override {
		return "Savings";
	}
	
};
class CheckingAccount :public Account {
protected:
	double fee;
public:
	CheckingAccount(int accountId, Client client, double balance = 0, double fee) :Account(accountId,client, balance), fee(fee) {}
	void withdraw() override {
		Account::withdraw(amount + fee);
	}
	string getType() const override {
		return "Checking";
	}
	void applyMonthly() override {
		if (balance >= fee) {
			balance -= fee;
		}
	}
};
class CreditAccount :public Account {
protected:
	double debtRate;
	double creditlimit;
	CreditAccount(int accountId, Client client, double balance = 0,double limit, double debt) :Account(accountId, client, balance), creditlimit(limit),debtRate(debt) {}
	string getType() const override {
		return "Credit";
	}
	void withdraw(double amount) override {
		if (amount <= 0) {
			throw invalid_argument("Withdraw amount must be positive");
		}
		if (balance - amount < -creditlimit) {
			throw runtime_error("Credit limit exeeded");
		}
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

