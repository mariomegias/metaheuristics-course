#include "../inc/arff_file.hpp"

ARFF_file::ARFF_file(const string & path)
{
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error while opening file. " << path << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    bool reading_data = false;

    while (getline(file, line)) {
        if (!reading_data) {
            if (line.find("@data") != string::npos) {
                reading_data = true;
            }
        } else {
            stringstream ss(line);
            vector<string> record;
            string value;
            while (getline(ss, value, ',')) {
                record.push_back(value);
            }
            data.output.push_back(record.back());
            record.pop_back();
            vector<double> record_attributes;
            for (auto& v : record) {
                record_attributes.push_back(stod(v));
            }
            data.input.push_back(record_attributes);
        }
    }
    file.close();
}

const Data & ARFF_file::get_data() const {
    return data;
}

unsigned int ARFF_file::get_num_records() const {
    return data.input.size();
}