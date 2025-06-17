#ifndef TRANSACTION_H
#define TRANSACTION_H
using namespace std;
class Transaction {
private:
	int transaction_id;
	float transaction_amount;
public:
	Transaction();
	Transaction(int transaction_id,float transaction_amount);
	Transaction(const Transaction& obj);
	void set_transaction_id(int transaction_id);
	void set_transaction_amount(float transaction_amount);
	int get_transaction_id()const;
	float get_transaction_amount()const;

	string tostring_t();
	void store_to_file();
	void view_from_file();
};
#endif
