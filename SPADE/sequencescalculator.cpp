#include "sequencescalculator.h"

SequencesCalculator::SequencesCalculator()
{

}

void SequencesCalculator::calculateClosedSequences(vector<set<Sequence*> > sequences, string file){
    unmarkAllSequences(sequences);
    FileHelper f;
    vector<Sequence*> closedSequences;
    for(auto it = sequences.rbegin(); it!=sequences.rend(); ++it){
        set<Sequence*> row = *it;
        for(Sequence* s:row){
            if(!s->isMarked()){
                closedSequences.push_back(s);
            }
            vector<Sequence*> subsequences = s->getSubsequences();
            for(Sequence* subs:subsequences){
                Sequence* subs_sup = getTheSameSequence(sequences, subs);
                if(s->getSupport() == subs_sup->getSupport()){
                    subs_sup->mark(true);
                }
                delete subs;
            }
        }
    }

    f.writeSequencesToFile(file, closedSequences);
}

void SequencesCalculator::calculateGenerators(vector<set<Sequence*> >sequences, string file){
    unmarkAllSequences(sequences);
    FileHelper f;
    vector<Sequence*> Generators;
    for(auto it = sequences.rbegin(); it!=sequences.rend(); ++it){
        set<Sequence*> row = *it;
        for(Sequence* s:row){
            vector<Sequence*> subsequences = s->getSubsequences();
            for(Sequence* subs:subsequences){
                Sequence* subs_sup = getTheSameSequence(sequences, subs);
                if(s->getSupport() == subs_sup->getSupport()){
                    s->mark(true);
                }
                delete subs;
                if(s->isMarked()){
                    break;
                }
            }
        } 
    }

    for(set<Sequence*> row:sequences){
        for(Sequence* s:row){
            if(!s->isMarked())
                Generators.push_back(s);
        }
    }

    f.writeSequencesToFile(file, Generators);
}

void SequencesCalculator::calculateMaxsequences(vector<set<Sequence*> >sequences, string file){
    unmarkAllSequences(sequences);
    FileHelper f;
    vector<Sequence*> maxSequences;
    for(auto it = sequences.rbegin(); it!=sequences.rend(); ++it){
        set<Sequence*> row = *it;
        for(Sequence* s:row){
            if(!s->isMarked()){
                maxSequences.push_back(s);
            }
            vector<Sequence*> subsequences = s->getSubsequences();
            for(Sequence* subs:subsequences){
                Sequence* subs_sup = getTheSameSequence(sequences, subs);
                subs_sup->mark(true);
                delete subs;
            }
        }
    }

    f.writeSequencesToFile(file, maxSequences);
}

Sequence* SequencesCalculator::getTheSameSequence(vector<set<Sequence*> >sequences, Sequence* sequence){
    unsigned int size = sequence->getSize();
    for(Sequence* s:sequences[size]){
        if(*sequence == *s)
            return s;
    }
    return nullptr;
}

void SequencesCalculator::unmarkAllSequences(vector<set<Sequence*> >sequences){
    for(set<Sequence*> row:sequences){
        for(Sequence* s:row){
            s->mark(false);
        }
    }
}
