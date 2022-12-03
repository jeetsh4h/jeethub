#include <fstream>
#include <map>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::ios;
using std::map;
using std::endl;
using std::string;
using std::stringstream;


// the first value in the text file is pre-defined
// this was created when I added "=" as a test case
// this made the word a nullstr__, which somehow gave the frequency as 61
// therefore that value just got manually editedj

map<string, int> load_map() {
    map<string, int> frequencies;
    
    ifstream reader;
    reader.open("frequency-table.txt");

    stringstream X;
    string record;
    string key;
    string value;
    int val;

    while (getline(reader, record)) {
        X << record;

        getline(X, key, ':');
        
        getline(X, value, ';');
        val = stoi(value);
        
        frequencies[key] = val;
        X.clear();
    }

    reader.close();
    return frequencies;
}


void overwrite_map(map<string, int> freq) {
    ofstream writer;
    writer.open("frequency-table.txt");
    
    map<string, int>::iterator it;
    for (it = freq.begin(); it != freq.end(); it++) {
        writer << it->first << ':' << it->second << ";\n";
    }

    writer.close();
}