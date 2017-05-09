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
#include <iterator>

class Spade
{
public:
    Spade();
    void calculate(string& input, DataSetReader* dataReader, unsigned int minSup);
    vector<Sequence*>& getFrequentSequences(){
        return freqSequences;
    }
    vector<Sequence*>& getMinInfrequentGenerators(){
        return minInfreqGenerators;
    }
    unordered_map<unsigned int, string>& getAtomsCodeToName(){
        return this->atomsCodeToName;
    }

private:
    vector<Sequence*> freqSequences;
    vector<Sequence*> closedFreqSequences;
    vector<Sequence*> freqGenerators;
    vector<Sequence*> minInfreqGenerators;
    unordered_map<unsigned int, string> atomsCodeToName;
    unordered_map<string, unsigned int> atomsNameToCode;

    unsigned int addToAtoms(string atom);
    vector <IdList*> readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup);
    vector <IdList*> temporalJoin(IdList* first, IdList* second, vector<Sequence *> &freqSequences);
    IdList* equalityJoin(IdList* first, IdList* second, vector<Sequence *> &freqSequences);
    IdList* firstSecondJoin(IdList* first, IdList* second, vector<Sequence *> &freqSequences);
    void EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup);
    bool prune(Sequence* sequence, vector<Sequence *> &freqSequences);
    bool isSequenceFrequent(Sequence* sequence, vector<Sequence *> freqSequences);

};

#endif // SPADE_H
