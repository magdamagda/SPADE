#ifndef DATASETREADER_H
#define DATASETREADER_H

#include <vector>
#include <fstream>
#include <string>
#include "transaction.h"

using namespace std;

class DataSetReader
{
public:
    DataSetReader();
    bool open(string& filename);
    Transaction* getTransaction();
    void close();
    bool end();

private:
    ifstream f;


};

#endif // DATASETREADER_H
