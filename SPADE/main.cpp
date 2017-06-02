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
#include "tictoc.h"


using namespace std;

int main(int argc, char *argv[])
{
    int minSupport = 0;
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
        TicToc::tic();
        spade.calculate(datasetPath, dataReader, minSupport, !minInfrequentGeneratorsPath.empty());
        TicToc::toc("SPADE");
        if(!frequentSequencesPath.empty()){
            FileHelper::writeEncodedSequencesToFile(frequentSequencesPath, spade.getFrequentSequences(), spade.getAtomsCodeToName());
            cout<<"Discovered "<<spade.getFrequentSequences().size()<<" frequent sequences"<<endl;
        }
        if(!itemsCodesPath.empty())
            FileHelper::writeCodeToNameMapToFile(itemsCodesPath, spade.getAtomsCodeToName());
        if(!minInfrequentGeneratorsPath.empty()){
            FileHelper::writeSequencesToFile(minInfrequentGeneratorsPath, spade.getMinInfrequentGenerators());
            cout<<"Discovered "<<spade.getMinInfrequentGenerators().size()<<" minimal infrequent generators"<<endl;
        }
        if(!closedFrequentSequencesPath.empty()){
            TicToc::tic();
            SequencesCalculator::calculateClosedSequences(spade.getFreqSequencesByLength(), closedFrequentSequencesPath);
            TicToc::toc("Closed sequences");
        }
        if(!frequentGeneratorsPath.empty()){
            TicToc::tic();
            SequencesCalculator::calculateGenerators(spade.getFreqSequencesByLength(), frequentGeneratorsPath);
            TicToc::toc("Frequent generators");
        }
        if(!maxFrequentSequencesPath.empty()){
            TicToc::tic();
            SequencesCalculator::calculateMaxsequences(spade.getFreqSequencesByLength(), maxFrequentSequencesPath);
            TicToc::toc("Maximal sequences");
        }
    }

    /*if(!sequencesPath.empty() && !sequencesResultPath.empty() && !itemsCodesPath.empty()){
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
