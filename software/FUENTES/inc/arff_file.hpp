#ifndef ARFF_FILE_HPP
#define ARFF_FILE_HPP

#include "structures.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

class ARFF_file
{
private:
    Data data;

public:
    ARFF_file(const string & path);
    const Data & get_data() const;
    unsigned int get_num_records() const;
};

#endif // ifndef ARFF_FILE_HPP