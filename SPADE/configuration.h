#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <fstream>

class Configuration
{
public:
    Configuration(std::string path);
    int minSupport;
    std::string datasetPath;
    std::string frequentSequencesPath;
    std::string minInfrequentGeneratorsPath;
    std::string closedFrequentSequencesPath;
    std::string maxFrequentSequencesPath;
    std::string frequentGeneratorsPath;
    std::string sequencesPath;
    std::string sequencesResultPath;
    std::string itemsCodesPath;
    void parseConfiguration(std::string path);
};

#endif // CONFIGURATION_H
