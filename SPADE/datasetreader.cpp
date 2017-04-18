#include "datasetreader.h"

DataSetReader::DataSetReader()
{

}

bool DataSetReader::open(string& filename){
    this->f = ifstream(filename);
    return f.is_open();
}

bool DataSetReader::end(){
    return f.eof();
}

Transaction *DataSetReader::getTransaction(){
    if(f.eof())
        return nullptr;
    Transaction* transaction = new Transaction;
    int n;
    string item;
    f>>transaction->sid>>transaction->eid>>n;
    for(int i=0; i<n; i++){
        f>>item;
        transaction->items.push_back(item);
    }
    return transaction;
}

void DataSetReader::close(){
    f.close();
}
