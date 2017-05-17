#include <iostream>
#include <string>
#include <vector>
#include "sequence.h"
#include "spade.h"
#include "datasetreader.h"
#include <unordered_map>
#include "filehelper.h"
#include "closedseqrep.h"
#include "sequencescalculator.h"


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
    string filename="../datasets/zaki.txt";
    DataSetReader* dataReader = new DataSetReader();
    Spade spade;
    spade.calculate(filename, dataReader, minSup, true);
    FileHelper::writeEncodedSequencesToFile("../results/freqSequences.txt", spade.getFrequentSequences(), spade.getAtomsCodeToName());
    FileHelper::writeCodeToNameMapToFile("../results/codeToNameMap.txt", spade.getAtomsCodeToName());
    FileHelper::writeSequencesToFile("../results/minInfreqGenerators.txt", spade.getMinInfrequentGenerators());

    vector<set<Sequence*> > freqSeq = spade.getFreqSequencesByLength();
    SequencesCalculator::calculateClosedSequences(freqSeq, "../result/closedSequences.txt");
    SequencesCalculator::calculateGenerators(freqSeq, "../result/Generators.txt");

    int minSupport = 0;
    string datasetPath = "";
    string minInfrequentGeneratorsPath = "";
    string closedFrequentSequencesPath = "";
    string maxFrequentSequencesPath = "";
    string frequentGeneratorsPath = "";
    string sequencesPath = "";
    string sequencesResultPath = "";

    for (int i = 1; i < argc;) {
        string arg = argv[i];

    }

    return 0;
}
