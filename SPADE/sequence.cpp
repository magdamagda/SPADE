#include "sequence.h"

Sequence::Sequence(vector<vector<unsigned int> > &events)
{
    this->events = events;
}

void Sequence::addEvent(vector<unsigned int> event){
    events.push_back(event);
}

bool Sequence::isSubset(Sequence &other){
    vector < vector<unsigned int> > otherEvents = other.getEvents();
    return isSubset(otherEvents);
}

bool Sequence::isSuperset(Sequence &other){
    return other.isSubset(this->events);
}

bool Sequence::isSubset(const vector < vector<unsigned int> > &otherEvents){
    int nextEvent = 0;
    for (unsigned int i=0; i<events.size(); ++i){
        unsigned int j;
        for(j=nextEvent; j<otherEvents.size(); ++j){
            if(includes(otherEvents[j].begin(), otherEvents[j].end(), events[i].begin(), events[i].end())){
                nextEvent=j+1;
                continue;
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

vector < vector<unsigned int> > Sequence::getEventsWithoutLastElement(){
    if (isLastSingleton()){
        return vector < vector<unsigned int> >(events.begin(), events.end()-1);
    }
    vector < vector<unsigned int> > result=events;
    if(events.size()>0){
        result.back().pop_back();
    }
    return result;
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
