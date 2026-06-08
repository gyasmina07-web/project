#include <string>
#include <vector>
#include<memory>
#include <iostream>
#include "Source2.cpp"
class Command {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~Command() = default;
	virtual string getDescription() const = 0;

};
class DepositCommand:public Command{
private:
	Account& acc;
	double amount;
	bool executed;
public:
	DepositCommand(Account& a,double amt):acc(a),amount(amt),executed(false){}
	void execute() override {
		acc.deposit(amount);
		executed = true;
	}
	void undo() override {
		if (executed) {
			acc.withdraw(amount);
			executed = false;
		}
	}
	string getDescription() const override {
		return "deposit " + to_string(amount) + "to account" + to_string(account.getAccountId());
	}
};
class WithdrawCommand :public Command {
private:
	Account& acc;
	double amount;
	bool executed;
public:
	WithdrawCommand(Account& a, double amt) : acc(a), amount(amt), executed(false){}
	void execute() override {
		acc.withdraw(amount);
		executed(true);
	}
	void undo() override {
		if (executed) {
			acc.deposit(amount);
			executed = false;
		}
	}
	string getDescription() const override {
		return "Withdraw " + to_string(amount) + " from account " + to_string(account.getAccountId());
	}
};

class TransferCommand :public Command {
private:
	TransferTransaction transaction;
public:
	TransferCommand(Account& from, Account& to, double amount) :transaction(from, to, amount) {}
	void execute() override {
		transaction.execute();
	}
	void undo() override {
		transaction.rollback();
	}
	string getDescription() const override {
		return transaction.getDescription();
	}
};
class MonthlyUpdateCommand :public Command {
private:
	vector<Account*>accounts;
	vector<double>oldBalances;
	bool executed;
public:
	MonthlyUpdateCommand(vector<Account*>accounts) :accounts(accounts), executed(false){}
	void execute() override {
		oldBalances.clear();
		for (Account* acc : accounts) {
			oldBalances.push_back(acc->getBalance());
			acc->applyMonthly();

		}
		executed = true;

	}
	void undo() override {
		if (!executed) {
			return;
		}
		for (size_t i = 0;i < accounts.size();i++) {
			double current = accounts[i]->getBalance();
			double old = oldBalances[i];
			if (currents > old) {
				accounts[i]->withdraw(current - old);
			}
			else if (old > current) {
				accounts[i]->deposit(old - current);
			}
		}
		executed = false;
	}
	string getDescription()const override {
		return "Monthly update foe all accounts";
	}
};