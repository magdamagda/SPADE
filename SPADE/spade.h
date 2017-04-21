#ifndef SPADE_H
#define SPADE_H

#include "sequence.h"
#include "transaction.h"
#include "idlist.h"
#include "datasetreader.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

class Spade
{
public:
    Spade();
    void calculate(string& input, DataSetReader* dataReader, unsigned int minSup);
    // test comment

private:
    vector<Sequence*> freqSequences;
    vector<Sequence*> closedFreqSequences;
    vector<Sequence*> freqGenerators;
    vector<Sequence*> minInfreqGenerators;
    unordered_map<unsigned int, string> atomsCodeToName;
    unordered_map<string, unsigned int> atomsNameToCode;

    unsigned int addToAtoms(string atom);
    vector <IdList*> readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup);
    vector <IdList*> readFrequentTwoSeq(vector <IdList*>& freqOneSeq, unsigned int minSup);
    vector <IdList*> temporalJoin(IdList* first, IdList* second);
    void EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup);

};

#endif // SPADE_H
