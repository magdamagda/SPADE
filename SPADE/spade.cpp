#include "spade.h"

Spade::Spade()
{

}

void Spade::calculate(string& input, DataSetReader* dataReader, unsigned int minSup, bool generateMinInfGen){
    vector<IdList*> freqOneSeq = this->readFrequentOneSeq(input, dataReader, minSup, generateMinInfGen);
    this->EnumerateFrequentSeq(freqOneSeq, minSup, generateMinInfGen);
    this->calculateFreqSequencesByLength();
    if(generateMinInfGen){
        this->pruneInfrequentGenerators();
    }
}

vector <IdList*> Spade::readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup, bool generateMinInfGen){
    set<int> allSequencesNum;
    dataReader->open(input);
    vector <IdList*> oneSeq;
    map<unsigned int, IdList*> atomsIdLists;
    Transaction* t = dataReader->getTransaction();
    int transactionsNum = 0;
    while(t!=nullptr && t->items.size() > 0){
        transactionsNum++;
        for (string &itemName:t->items){
            unsigned int item;
            if (this->atomsNameToCode.find(itemName) == this->atomsNameToCode.end()){
                item = this->addToAtoms(itemName);
                atomsIdLists[item] = new IdList(new Sequence(item));
            }
            else{
                item = this->atomsNameToCode[itemName];
            }
            atomsIdLists[item]->addSidEid(t->sid, t->eid);
            allSequencesNum.insert(t->sid);
        }
        delete t;
        t = dataReader->getTransaction();
    }
    dataReader->close();
    cout<<transactionsNum<<" transactions read"<<endl;

    // add empty sequence
    Sequence* emptySequence = new Sequence();
    emptySequence->setSupport(allSequencesNum.size());
    if(emptySequence->getSupport() > minSup){
        this->freqSequences.push_back(emptySequence);
    }
    else if(generateMinInfGen)
        this->minInfreqGenerators.push_back(emptySequence);
    else
        delete emptySequence;

    for(auto & atomIdList:atomsIdLists){
        unsigned int support = atomIdList.second->size();
        atomIdList.second->getSequence()->setSupport(support);
        if(support > minSup){
            atomIdList.second->sortEvents();
            oneSeq.push_back(atomIdList.second);
            this->freqSequences.push_back(atomIdList.second->getSequence());
        }
        else if(generateMinInfGen){
            this->minInfreqGenerators.push_back(atomIdList.second->getSequence());
            delete atomIdList.second;
        } else {
            delete atomIdList.second->getSequence();
            delete atomIdList.second;
        }
    }

    return oneSeq;
}


unsigned int Spade::addToAtoms(string atom){
    unsigned int code = this->atomsNameToCode.size();
    this->atomsNameToCode[atom] = code;
    this->atomsCodeToName[code] = atom;
    return code;
}

unordered_map<Sequence *, vector<IdList *> > Spade::temporalJoin(IdList* first, IdList* second){
    unordered_map<Sequence *, vector<IdList *> > result;
    Sequence* seq1 = first->getSequence();
    Sequence* seq2 = second->getSequence();
    bool seq1Singleton = seq1->isLastSingleton();
    bool seq2Singleton = seq2->isLastSingleton();

    if(seq1==seq2){
        if(seq1Singleton){
            IdList* sequence = this->firstSecondJoin(first, second);
            if(sequence!=nullptr){
                result[first->getSequence()].push_back(sequence);
            }
            return result;
        }
        else{
            return result;
        }
    }

    if(seq1Singleton && seq2Singleton){
        IdList* sequence = this->equalityJoin(first, second);
        result[first->getSequence()].push_back(sequence);
        sequence = this->firstSecondJoin(first, second);
        result[first->getSequence()].push_back(sequence);
        sequence = this->firstSecondJoin(second, first);
        result[second->getSequence()].push_back(sequence);
    } else if (seq1Singleton && !seq2Singleton){
        IdList* sequence = this->firstSecondJoin(second, first);
        result[second->getSequence()].push_back(sequence);
    } else if (!seq1Singleton && seq2Singleton){
        IdList* sequence = this->firstSecondJoin(first, second);
        result[first->getSequence()].push_back(sequence);
    } else{
        IdList* sequence = this->equalityJoin(first, second);
        result[first->getSequence()].push_back(sequence);
    }

    return result;
}

IdList* Spade::equalityJoin(IdList* first, IdList* second){
    Sequence* seq1 = first->getSequence();
    Sequence* seq2 = second->getSequence();

    Sequence* newSequence = new Sequence(seq1);
    newSequence->addElementToLastEvent(seq2->getLastElement());
    IdList* result = new IdList(newSequence);

    for (auto& sequence:(*first)){
        unsigned int sid = sequence.first;
        if(second->isSid(sid)){
            vector<unsigned int> secondEvents = second->getEventsBySid(sid);
            vector<unsigned int> commonEvents;
            set_intersection(sequence.second.begin(), sequence.second.end(), secondEvents.begin(), secondEvents.end(),back_inserter(commonEvents));
            for(unsigned int eid:commonEvents)
                result->addSidEid(sid, eid);
        }
    }
    result->updateSeqSupport();
    return result;
}

IdList *Spade::firstSecondJoin(IdList* first, IdList* second){
    Sequence* seq1 = first->getSequence();
    Sequence* seq2 = second->getSequence();

    Sequence* firstSecondSeq = new Sequence(seq1);
    firstSecondSeq->addEvent(seq2->getLastElement());
    IdList* result = new IdList(firstSecondSeq);

    for (auto& sequence:(*first)){
        unsigned int sid = sequence.first;
        if(second->isSid(sid)){
            vector<unsigned int> secondEvents = second->getEventsBySid(sid);
            for(unsigned int eid2:secondEvents){
                for(unsigned int eid1:sequence.second){
                    if(eid2>eid1){
                        result->addSidEid(sid, eid2);
                    }
                    else{
                        break;
                    }
                }
            }

        }
    }

    result->updateSeqSupport();
    return result;
}

vector < vector <Sequence* > > Spade::equiwalenceClasses(vector<Sequence*>){
    vector< vector <Sequence*> > result;

    return result;
}

void Spade::EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup, bool generateMinInfGen){
    if (sequences.size() == 0){
        return;
    }
    unordered_map<Sequence *, vector<IdList *> > sequencesTree;
    for(auto it1 = sequences.begin(); it1!=sequences.end(); ++it1){
        for(auto it2 = it1; it2!=sequences.end(); ++it2){
            //cout<<(*it1)->getSequence()->printSequence()<<"  "<<(*it2)->getSequence()->printSequence()<<endl;
            unordered_map<Sequence *, vector<IdList *> > newSequences = this->temporalJoin(*it1, *it2);
            for(auto & parent:newSequences){
                for(IdList* s:parent.second){
                    if(s->size()>minSup){
                        s->sortEvents();
                        sequencesTree[parent.first].push_back(s);
                        this->freqSequences.push_back(s->getSequence());
                    }
                    else if(generateMinInfGen){
                        this->minInfreqGenerators.push_back(s->getSequence());
                        delete s;
                    } else {
                        delete s->getSequence();
                        delete s;
                    }
                }
            }
        }
        this->EnumerateFrequentSeq(sequencesTree[(*it1)->getSequence()], minSup, generateMinInfGen);
    }
    for(auto s:sequences){
        delete s;
    }
    //this->EnumerateFrequentSeq(newFreqSequences, minSup, generateMinInfGen);
}

bool Spade::prune(Sequence* sequence){
    for(Sequence* subsequence:sequence->getSubsequences()){
        if(!isSequenceFrequent(subsequence)){
            return true;
        }
    }
    return false;
}

bool Spade::isSequenceFrequent(Sequence* sequence){
    unsigned int size = sequence->getSize();
    if(freqSequencesByLength.size() <= size){
        return false;
    }
    for(Sequence* freqSequence:this->freqSequencesByLength[size]){
        if(*sequence == *freqSequence)
            return true;
    }
    return false;
}

void Spade::pruneInfrequentGenerators(){
    vector<Sequence*> prunedInfGenerators;
    for(Sequence* s:this->minInfreqGenerators){
        if(prune(s)){
            delete s;
        }
        else{
            prunedInfGenerators.push_back(s);
        }
    }
    this->minInfreqGenerators = prunedInfGenerators;
}

void Spade::calculateFreqSequencesByLength(){
    for(auto s:this->freqSequences){
        unsigned int size = s->getSize();
        if(size == this->freqSequencesByLength.size()){
            this->freqSequencesByLength.push_back(set<Sequence*>());
        }
        this->freqSequencesByLength[size].insert(s);
    }
}
