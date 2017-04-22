#include <iostream>
#include <string>
#include <vector>
#include "sequence.h"
#include "spade.h"
#include "datasetreader.h"

using namespace std;

void printSequences(vector<Sequence*>& sequences){
    for(Sequence* s:sequences){
        cout<<s->printSequence()<<endl;
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
    printSequences(spade.getFrequentSequences());
    cout<<"Minimal infrequent generators: "<<endl;
    printSequences(spade.getMinInfrequentGenerators());

    return 0;
}
