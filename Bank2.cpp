#include <string>
#include <vector>
#include<memory> 
#include <iostream>
#include "Source2.cpp"
#include "Command.cpp"
#include "Bank.cpp"
#include "Transaction.cpp"
class Bank {
private:
    map<int, unique_ptr<Account>> accounts;
    vector<unique_ptr<Command>> history;
public:
    void addAccount(unique_ptr<Account> account) {
        int id = account->getAccountId();
        if (accounts.count(id)) {
            throw runtime_error("Account with this ID already exists");
        }
        accounts[id] = move(account);
    }
    Account& getAccount(int id) {
        if (!accounts.count(id)) {
            throw runtime_error("Account not found");
        }
        reutn* accounts[id];
    }
    void executeCommand(unique_ptr<Command> command) {
        command->execute();
        cout << "Operation completed: " << command->getDescription() << endl;
        history.push_back(move(command));
    }
    //void executeTransaction(unique_ptr<Transaction> tx) {

    //    tx->execute();

    //    history.push_back(move(tx));

    //}

    void rollbackLast() {

        if (history.empty()) {
            cout << "No operations to rollback" << endl;
            return;
        }
        cout << "Rollback:" << history.back()->getDescription() << endl;
        history.back()->undo();
        history.pop_back();

    }
    void showAccounts() const {
        cout << "====================ACCOUNTS====================" << endl;
        cout << left << setw(12) << "ID" << setw(18) << "Type" << "Balance" << endl;
        cout << "-----------------------------------------------\n";
        for (const auto& pair : acounts) {
            pair.second->printInfo();
        }
        cout << "===============================================\n";
    }
    void showHistory() const {
        cout << "\n==================HISTORY=====================\n";
        if (history.empty()) {
            cout << "History is empty" << endl;
        }
        else {
            for (size_t i = 0;i < history.size();i++) {
                cout << i + 1 << "." << history[i]->getDescription << endl;
            }
        }
        cout << "==================================================\n";
    }
    vector<Account*> getAllAccounts() {
        vector<Account*> result;
        for (auto& pair : accounts) {
            result.push_back(pair.second.get());
        }
        return result;
    }
};
