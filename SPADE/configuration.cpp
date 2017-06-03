#include "configuration.h"

Configuration::Configuration(std::string path)
{
    parseConfiguration(path);
}

void Configuration::parseConfiguration(std::string path){
    std::filebuf fb;
    if (fb.open (path, std::ios::in))
    {
        std::istream is(&fb);
        using boost::property_tree::ptree;
        ptree pt;
        read_xml(is, pt);
        this->minSupport = pt.get<int>("config.min-support");
        this->datasetPath = pt.get<std::string>("config.dataset");
        this->frequentSequencesPath = pt.get<std::string>("config.freq-sequences");
        this->minInfrequentGeneratorsPath = pt.get<std::string>("config.min-inf-generators");
        this->closedFrequentSequencesPath = pt.get<std::string>("config.freq-closed-seq");
        this->frequentGeneratorsPath = pt.get<std::string>("config.freq-generators");

        this->maxFrequentSequencesPath = pt.get<std::string>("config.max-sequences");
        this->itemsCodesPath = pt.get<std::string>("config.codes");
        this->sequencesPath = pt.get<std::string>("config.sequences");
        this->sequencesResultPath = pt.get<std::string>("config.sequences-support");

        fb.close();
    }
}
