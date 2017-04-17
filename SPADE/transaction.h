#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>

using namespace std;

class Transaction
{
public:
    Transaction();
    unsigned int sid;
    unsigned int eid;
    vector<string> items;
};

#endif // TRANSACTION_H
