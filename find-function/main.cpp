#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "freq.h"
#include "load_map.h"

int main() {
    map<string, int> frequencies = load_map();
    map<string, int>::iterator finder;
    string word;

    do {
        cout << "Enter the word (enter 'q' to quit):\n";
        cin >> word;
        word = clean(word);

        finder = frequencies.find(word);

        if (finder == frequencies.end()) {
            frequencies[word] = frequency_in_alice(word);
            cout << "The frequency is: " << frequencies[word] << endl << endl;
        } else {
            cout << "The frequency is: " << finder->second << endl << endl;
        }

    } while (word != "q");

    overwrite_map(frequencies);
}