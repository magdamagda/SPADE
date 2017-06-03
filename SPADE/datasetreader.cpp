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
    try{
        if(!f.good())
            return nullptr;
        Transaction* transaction = new Transaction;
        int n;
        string item;
        if(f>>transaction->sid){
            f>>transaction->eid>>n;
            for(int i=0; i<n; i++){
                f>>item;
                transaction->items.push_back(item);
            }
            return transaction;
        }
        return nullptr;
    }
    catch(exception e){
        cout<<"Error reading file"<<endl;
        return nullptr;
    }
}

void DataSetReader::close(){
    f.close();
}
