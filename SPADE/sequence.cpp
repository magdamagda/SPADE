#include "sequence.h"

Sequence::Sequence(){
    marked = false;
}

Sequence::Sequence(unsigned int atom){
    marked = false;
    this->events = vector<vector<unsigned int> >();
    this->events.push_back(vector<unsigned int>());
    this->events[0].push_back(atom);
}

Sequence::Sequence(vector<vector<unsigned int> > &events)
{
    marked = false;
    this->events = events;
}

Sequence::Sequence(Sequence *other){
    marked = false;
    this->events = other->getEvents();
}

void Sequence::addEvent(vector<unsigned int> event){
    events.push_back(event);
}

void Sequence::addEvent(unsigned int element){
    events.push_back(vector<unsigned int>());
    events.back().push_back(element);
}

void Sequence::addElementToLastEvent(unsigned int element){
    events.back().push_back(element);
}

bool Sequence::isSubset(Sequence &other){
    vector < vector<unsigned int> > otherEvents = other.getEvents();
    return isSubset(otherEvents);
}

bool Sequence::isSuperset(Sequence &other){
    return other.isSubset(this->events);
}

bool Sequence::isSubset(Sequence *other){
    vector < vector<unsigned int> > otherEvents = other->getEvents();
    return isSubset(otherEvents);
}

bool Sequence::isSuperset(Sequence *other){
    return other->isSubset(this);
}

bool Sequence::isSubset(const vector < vector<unsigned int> > &otherEvents){
    int nextEvent = 0;
    for (unsigned int i=0; i<events.size(); ++i){
        unsigned int j;
        for(j=nextEvent; j<otherEvents.size(); ++j){
            if(includes(otherEvents[j].begin(), otherEvents[j].end(), events[i].begin(), events[i].end())){
                nextEvent=j+1;
                break;
            }
        }
        if(j==otherEvents.size()){
            return false;
        }
    }
    return true;
}

bool Sequence::isLastSingleton(){
    if(events.size()>0){
        return events.back().size()==1;
    }
    return false;
}

vector<vector<unsigned int> > Sequence::getEventsWithoutLastElement(){
    if (isLastSingleton()){
        return vector < vector<unsigned int> >(events.begin(), events.end()-1);
    }
    vector < vector<unsigned int> > result=events;
    if(events.size()>0){
        result.back().pop_back();
    }
    return result;
}

unsigned int Sequence::getLastElement(){
    return events.back().back();
}

string Sequence::printSequence(){
    string result="<";
    for(auto event:events){
        result+="(";
        for(unsigned int element : event){
            result+=to_string(element);
            result+=",";
        }
        result+=")";
    }
    result+=">";
    return result;
}

string Sequence::printEncodedSequence(const unordered_map<unsigned int, string> &atomsCodeToName){
    string result="<";
    for(auto event:events){
        result+="(";
        for(unsigned int element : event){
            result+=atomsCodeToName.at(element);
            result+=",";
        }
        result+=")";
    }
    result+=">";
    return result;
}

unsigned int Sequence::getSize(){
    unsigned int size = 0;
    for(auto event:events){
        size+=event.size();
    }
    return size;
}

vector<Sequence*> Sequence::getSubsequences(){
    vector<Sequence*> result;
    unsigned int numOfAtoms = this->getSize();
    /*if(numOfAtoms > 0){
        result.push_back(new Sequence());
    }*/
    for(unsigned int i = 0; i<numOfAtoms; ++i){
        unsigned int pos = 0;
        Sequence* subsequence = new Sequence();
        for(vector<unsigned int> event:this->events){
            vector<unsigned int> subsequence_event;
            for(unsigned int element : event){
                if(pos!=i){
                    subsequence_event.push_back(element);
                }
                pos++;
            }
            if (subsequence_event.size()>0){
                subsequence->addEvent(subsequence_event);
            }
        }
        result.push_back(subsequence);
    }
    return result;
}

bool Sequence::operator==(Sequence & other){
    return this->events==other.events;
}
