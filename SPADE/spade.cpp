#include "spade.h"

Spade::Spade()
{

}

void Spade::calculate(string& input, DataSetReader* dataReader, unsigned int minSup, bool generateMinInfGen){
    vector<IdList*> freqOneSeq = this->readFrequentOneSeq(input, dataReader, minSup, generateMinInfGen);
    this->EnumerateFrequentSeq(freqOneSeq, minSup, generateMinInfGen);
    if(generateMinInfGen){
        this->calculateFreqSequencesByLength();
        this->pruneInfrequentGenerators();
    }
}

vector <IdList*> Spade::readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup, bool generateMinInfGen){
    set<int> allSequencesNum;
    dataReader->open(input);
    vector <IdList*> oneSeq;
    map<unsigned int, IdList*> atomsIdLists;
    Transaction* t = dataReader->getTransaction();
    while(t!=nullptr){
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

vector <IdList*> Spade::temporalJoin(IdList* first, IdList* second){
    vector <IdList*> result;
    Sequence* seq1 = first->getSequence();
    Sequence* seq2 = second->getSequence();
    bool seq1Singleton = seq1->isLastSingleton();
    bool seq2Singleton = seq2->isLastSingleton();

    if(seq1==seq2){
        if(seq1Singleton){
            IdList* sequence = this->firstSecondJoin(first, second);
            if(sequence!=nullptr){
                result.push_back(sequence);
            }
            return result;
        }
        else{
            return result;
        }
    }

    if(seq1Singleton && seq2Singleton){
        IdList* sequence = this->equalityJoin(first, second);
        if (sequence!=nullptr) result.push_back(sequence);
        sequence = this->firstSecondJoin(first, second);
        if (sequence!=nullptr) result.push_back(sequence);
        sequence = this->firstSecondJoin(second, first);
        if (sequence!=nullptr) result.push_back(sequence);
    } else if (seq1Singleton && !seq2Singleton){
        IdList* sequence = this->firstSecondJoin(second, first);
        if (sequence!=nullptr) result.push_back(sequence);
    } else if (!seq1Singleton && seq2Singleton){
        IdList* sequence = this->firstSecondJoin(first, second);
        if (sequence!=nullptr) result.push_back(sequence);
    } else{
        IdList* sequence = this->equalityJoin(first, second);
        if (sequence!=nullptr) result.push_back(sequence);
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
    if (result->size()>0){
        result->updateSeqSupport();
        return result;
    }
    delete result->getSequence();
    delete result;
    return nullptr;
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
    if (result->size()>0){
        result->updateSeqSupport();
        return result;
    }
    delete result->getSequence();
    delete result;
    return nullptr;
}

void Spade::EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup, bool generateMinInfGen){
    if (sequences.size() == 0){
        return;
    }
    for(auto it1 = sequences.begin(); it1!=sequences.end(); ++it1){
        vector<IdList*> newFreqSequences;
        for(auto it2 = it1; it2!=sequences.end(); ++it2){
            if((*it1)->getSequence()->getEventsWithoutLastElement() != (*it2)->getSequence()->getEventsWithoutLastElement()){
                this->EnumerateFrequentSeq(newFreqSequences, minSup, generateMinInfGen);
                newFreqSequences = vector<IdList*>();
                break;
            }
            cout<<(*it1)->getSequence()->printSequence()<<"  "<<(*it2)->getSequence()->printSequence()<<endl;
            vector<IdList*> newSequences = this->temporalJoin(*it1, *it2);
            for(IdList* s:newSequences){
                if(s->size()>minSup){
                    s->sortEvents();
                    newFreqSequences.push_back(s);
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
        this->EnumerateFrequentSeq(newFreqSequences, minSup, generateMinInfGen);
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
