#include "spade.h"

Spade::Spade()
{

}

void Spade::calculate(string& input, DataSetReader* dataReader, unsigned int minSup){
    vector<IdList*> freqOneSeq = this->readFrequentOneSeq(input, dataReader, minSup);
    this->EnumerateFrequentSeq(freqOneSeq, minSup);
}

vector <IdList*> Spade::readFrequentOneSeq(string& input, DataSetReader* dataReader, unsigned int minSup){
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
        }
        delete t;
        t = dataReader->getTransaction();
    }
    dataReader->close();

    for(auto & atomIdList:atomsIdLists){
        unsigned int support = atomIdList.second->size();
        atomIdList.second->getSequence()->setSupport(support);
        if(support > minSup){
            atomIdList.second->sortEvents();
            oneSeq.push_back(atomIdList.second);
            this->freqSequences.push_back(atomIdList.second->getSequence());
        }
        else{
            this->minInfreqGenerators.push_back(atomIdList.second->getSequence());
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

void Spade::EnumerateFrequentSeq(vector <IdList*> sequences, unsigned int minSup){
    if (sequences.size() == 0){
        return;
    }
    vector<IdList*> newFreqSequences;
    for(auto it1 = sequences.begin(); it1!=sequences.end(); ++it1){
        for(auto it2 = it1; it2!=sequences.end(); ++it2){
            if((*it1)->getSequence()->getEventsWithoutLastElement() != (*it2)->getSequence()->getEventsWithoutLastElement()){
                break;
            }
            vector<IdList*> newSequences = this->temporalJoin(*it1, *it2);
            for(IdList* s:newSequences){
                if(s->size()>minSup){
                    s->sortEvents();
                    newFreqSequences.push_back(s);
                    this->freqSequences.push_back(s->getSequence());
                }
                else{
                    this->minInfreqGenerators.push_back(s->getSequence());
                    delete s;
                }
            }
        }
    }
    this->EnumerateFrequentSeq(newFreqSequences, minSup);
}
