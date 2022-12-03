#include <fstream>
using std::ios;
using std::string;
using std::ifstream;

string clean(string word) {
    string cleaned_word = "";

    for (int i = 0; i < word.size(); i++) {
        if(word[i] >= 'a' && word[i] <= 'z') {
            cleaned_word += word[i];
        } else if(word[i] >= 'A' && word[i] <= 'Z') {
            cleaned_word += word[i] + 32;       // Look at the ASCII table for explanation of 32
        } else {
            break;
        }
    }

    return cleaned_word;
}

int frequency_in_alice(string word) {
    ifstream reader;
    reader.open("alice.txt");

    int freq = 0;
    string temp;

    while(reader >> temp) {
        temp = clean(temp);
        if (temp == word) {
            freq++;
        }
    }

    reader.close();
    return freq;
}

