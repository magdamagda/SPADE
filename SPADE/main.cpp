#include <iostream>
#include <string>
#include <vector>
#include "sequence.h"
#include "spade.h"
#include "datasetreader.h"
#include <unordered_map>

using namespace std;

void printSequences(vector<Sequence*>& sequences){
    for(Sequence* s:sequences){
        cout<<s->printSequence()<<endl;
    }
}

void printEncodedSequences(vector<Sequence*>& sequences, unordered_map<unsigned int, string>& codeToName){
    for(Sequence* s:sequences){
        cout<<s->printEncodedSequence(codeToName)<<endl;
    }
}

int main(int argc, char *argv[])
{
    int minSup=1;
    string filename="../datasets/zaki.txt";
    DataSetReader* dataReader = new DataSetReader();
    Spade spade;
    spade.calculate(filename, dataReader, minSup);
    cout<<"Frequent sequences: "<<endl;
    printEncodedSequences(spade.getFrequentSequences(), spade.getAtomsCodeToName());
    cout<<"Minimal infrequent generators: "<<endl;
    printEncodedSequences(spade.getMinInfrequentGenerators(), spade.getAtomsCodeToName());

    // coding/encoding
    // mail
    // reprezentacje
    // empty sequence as frequent sequence

    return 0;
}
