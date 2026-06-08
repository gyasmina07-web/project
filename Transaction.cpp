#include <string>
#include <vector>
#include<memory>
#include <iostream>
#include "Source2.cpp"
#include "Command.cpp"
#include "Bank.cpp"
class Transaction {
protected:
	static int nextId;
	int transactionId;
	bool executed;
public:
	Transaction():transactionId(nextId++),executed(false){}
	virtual void execute() = 0;
	virtual void rollback() = 0;
	virtual string getDescription() const = 0;
	virtual  ~Transaction() = default;
	int getId() const {
		return transactionId;
	}
};
int Transaction::nextId = 1;
class TransferTransaction:public Transaction {
private:
	Account& from;
	Account& to;
	double amount;
	bool executed = false;
public:
	TransferTransaction(Account &from,Account &to,double amount):from(from),to(to),amount(amount){}
	void execute() override {

		from.withdraw(amount);
		try {
			to.deposit(amount);
			executed = true;
		}
		catch{
			from.deposit(amount);
			throw;
		}
	}


	void rollback() override {

		if (!executed) return;

		to.withdraw(amount);

		from.deposit(amount);
		executed = false;

	}
	string getDescription() const override {
		return "Transfer " + to_string(amount) + " from account " + to_string(from.getAccountId()) + " to account " + to_string(to.getAccountId());
	}
};