#include "main.h"
using namespace std;

void configuration(string fileName)
{
    string config_data;
    ifstream file(fileName);
    if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                config_data += line;
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << fileName << std::endl;
        }
}

