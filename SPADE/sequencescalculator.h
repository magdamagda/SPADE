#ifndef SEQUENCESCALCULATOR_H
#define SEQUENCESCALCULATOR_H

#include <vector>
#include <string>
#include <set>
#include "filehelper.h"
#include "sequence.h"
#include <iostream>

using namespace std;

class SequencesCalculator
{
public:
    SequencesCalculator();
    static void calculateClosedSequences(vector<set<Sequence*> >sequences, string file);
    static void calculateGenerators(vector<set<Sequence*> >sequences, string file);
    static void calculateMaxsequences(vector<set<Sequence*> >sequences, string file);
    static Sequence* getTheSameSequence(vector<set<Sequence*> >sequences, Sequence* sequence);

};

#endif // SEQUENCESCALCULATOR_H
