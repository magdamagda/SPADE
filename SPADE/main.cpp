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
#include "representation.h"
#include "closedseqrep.h"
#include "generatorsrepnegativeborder.h"
#include "generatorsreppositiveborder.h"


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
    SequencesCalculator::calculateClosedSequences(freqSeq, "../results/closedSequences.txt");
    SequencesCalculator::calculateGenerators(freqSeq, "../results/Generators.txt");
    SequencesCalculator::calculateMaxsequences(freqSeq, "../results/MaxSequences.txt");

    /*int minSupport = 0;
    string datasetPath = "";
    string frequentSequencesPath = "";
    string minInfrequentGeneratorsPath = "";
    string closedFrequentSequencesPath = "";
    string maxFrequentSequencesPath = "";
    string frequentGeneratorsPath = "";
    string sequencesPath = "";
    string sequencesResultPath = "";
    string itemsCodesPath = "";

    for (int i = 1; i < argc; i+=2) {
        string arg = argv[i];
        if(arg=="--minSup")
            minSupport = atoi(argv[i+1]);
        else if(arg == "--data")
            datasetPath = argv[i+1];
        else if(arg == "--freqseq")
            frequentSequencesPath = argv[i+1];
        else if(arg == "--mingen")
            minInfrequentGeneratorsPath = argv[i+1];
        else if(arg == "--closed")
            closedFrequentSequencesPath = argv[i+1];
        else if(arg == "--gen")
            frequentGeneratorsPath = argv[i+1];
        else if(arg == "--maxseq")
            maxFrequentSequencesPath = argv[i+1];
        else if(arg == "--seq")
            sequencesPath = argv[i+1];
        else if(arg == "--result")
            sequencesResultPath = argv[i+1];
        else if(arg == "--codes")
            itemsCodesPath = argv[i+1];
    }

    if(!datasetPath.empty()){
        DataSetReader* dataReader = new DataSetReader();
        Spade spade;
        spade.calculate(filename, dataReader, minSupport, !minInfrequentGeneratorsPath.empty());
        if(!frequentSequencesPath.empty())
            FileHelper::writeEncodedSequencesToFile(frequentSequencesPath, spade.getFrequentSequences(), spade.getAtomsCodeToName());
        if(!itemsCodesPath.empty())
            FileHelper::writeCodeToNameMapToFile(itemsCodesPath, spade.getAtomsCodeToName());
        if(!minInfrequentGeneratorsPath.empty())
            FileHelper::writeSequencesToFile(minInfrequentGeneratorsPath, spade.getMinInfrequentGenerators());
        if(!closedFrequentSequencesPath.empty())
            SequencesCalculator::calculateClosedSequences(spade.getFreqSequencesByLength(), closedFrequentSequencesPath);
        if(!frequentGeneratorsPath.empty())
            SequencesCalculator::calculateGenerators(spade.getFreqSequencesByLength(), frequentGeneratorsPath);
        if(!maxFrequentSequencesPath.empty())
            SequencesCalculator::calculateMaxsequences(spade.getFreqSequencesByLength(), maxFrequentSequencesPath);
    }

    if(!sequencesPath.empty() && !sequencesResultPath.empty() && !itemsCodesPath.empty()){
        unordered_map<string, unsigned int> nameToCode = FileHelper::readNameToCodeMap(itemCodesPath);
        if(!closedFrequentSequencesPath.empty()){
            ClosedSeqRep r(closedFrequentSequencesPath, nameToCode);
            r.calculateSupport(sequencesPath, sequencesResultPath);
        }
        if(!frequentGeneratorsPath.empty() && !minInfrequentGeneratorsPath.empty()){
            GeneratorsRepNegativeBorder r(frequentGeneratorsPath, minInfrequentGeneratorsPath, nameToCode);
            r.calculateSupport(sequencesPath, sequencesResultPath);
        }
        if(!frequentGeneratorsPath.empty() && !maxFrequentSequencesPath.empty()){
            GeneratorsRepPositiveBorder r(frequentGeneratorsPath, maxFrequentSequencesPath, nameToCode);
            r.calculateSupport(sequencesPath, sequencesResultPath);
        }
    }*/

    return 0;
}
