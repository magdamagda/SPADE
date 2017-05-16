#include "sequencescalculator.h"

SequencesCalculator::SequencesCalculator()
{

}

void SequencesCalculator::calculateClosedSequences(vector<set<Sequence*> > sequences, string file){
    FileHelper f;
    vector<Sequence*> closedSequences;
    cout<<"calculating closed sequences"<<endl;
    for(auto it = sequences.rbegin(); it!=sequences.rend(); ++it){
        cout<<"row"<<endl;
        set<Sequence*> row = *it;
        for(Sequence* s:row){
            cout<<"sequence: "<<s->printSequence()<<" "<<s->isMarked()<<endl;
            if(!s->isMarked()){
                cout<<"closed sequence: "<<s->printSequence()<<endl;
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

    FileHelper f;
    vector<Sequence*> Generators;
    cout<<"calculating Genarators"<<endl;
    for(auto it = sequences.rbegin(); it!=sequences.rend(); ++it){
        cout<<"row"<<endl;
        set<Sequence*> row = *it;
        for(Sequence* s:row){
            cout<<"sequence: "<<s->printSequence()<<" "<<s->isMarked()<<endl;
            if(!s->isMarked()){
                cout<<"Generators: "<<s->printSequence()<<endl;
                Generators.push_back(s);
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

    f.writeSequencesToFile(file, Generators
}

void SequencesCalculator::calculateMaxsequences(vector<set<Sequence*> >sequences, string file){

}

Sequence* SequencesCalculator::getTheSameSequence(vector<set<Sequence*> >sequences, Sequence* sequence){
    unsigned int size = sequence->getSize();
    for(Sequence* s:sequences[size]){
        if(*sequence == *s)
            return s;
    }
    return nullptr;
}
