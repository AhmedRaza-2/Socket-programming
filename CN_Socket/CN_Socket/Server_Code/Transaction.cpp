#include <iostream>
#include <fstream>
#include <string>
#include "Transaction.h"
using namespace std;

Transaction::Transaction() {
    transaction_id = 0;
    transaction_amount = 0.0;
}
Transaction::Transaction(int transaction_id, float transaction_amount ) {
    this->transaction_id = transaction_id;
    this->transaction_amount = transaction_amount;
}
Transaction::Transaction(const Transaction& obj) {
    this->transaction_id = obj.transaction_id;
    this->transaction_amount = obj.transaction_amount;
}

void Transaction::set_transaction_id(int transaction_id) {
    this->transaction_id = transaction_id;
}
void Transaction::set_transaction_amount(float transaction_amount) {
    this->transaction_amount = transaction_amount;
}

int Transaction::get_transaction_id()const {
    return transaction_id;
}
float Transaction::get_transaction_amount()const {
    return transaction_amount;
}

string Transaction::tostring_t() {
    return to_string(transaction_id) + "\t" + to_string(transaction_amount) + "\t";
}
void Transaction::store_to_file() {
    ofstream fout("Transaction.txt", ios::app);
    if (!fout) {
        cerr << "Error: Unable to open transactions file." << endl;
        return;
    }
    fout << transaction_id << "\t" << transaction_amount << "\t" << endl;
    fout.close();
}
void Transaction::view_from_file() {
    ifstream fin("transactions.txt");
    if (!fin) {
        cerr << "Error: Unable to open transactions file." << endl;
        return;
    }
    int id=0,customer_id;
    float amount=0;
    string customer_name;
    while (fin>>transaction_id>>transaction_amount) {
        cout << "Transaction ID: " << id << "\nAmount: " << amount;
    }
    fin.close();
}