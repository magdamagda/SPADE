#include <iostream>
#include <string>
#include <vector>
#include "sequence.h"
#include "spade.h"
#include "datasetreader.h"
#include <unordered_map>
#include "filehelper.h"

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
    int minSup=2;
    string filename="../datasets/tags.data";
    DataSetReader* dataReader = new DataSetReader();
    Spade spade;
    spade.calculate(filename, dataReader, minSup, true);
    FileHelper fileHelper;
    fileHelper.writeEncodedSequencesToFile("../results/freqSequences.txt", spade.getFrequentSequences(), spade.getAtomsCodeToName());
    fileHelper.writeCodeToNameMapToFile("../results/codeToNameMap.txt", spade.getAtomsCodeToName());
    fileHelper.writeSequencesToFile("../results/minInfreqGenerators.txt", spade.getMinInfrequentGenerators());

    //cout<<"Frequent sequences: "<<endl;
    //printEncodedSequences(spade.getFrequentSequences(), spade.getAtomsCodeToName());
    //cout<<"Minimal infrequent generators: "<<endl;
    //printEncodedSequences(spade.getMinInfrequentGenerators(), spade.getAtomsCodeToName());


    return 0;
}
