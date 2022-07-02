#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <ctime>

using namespace std;

vector<string> AllWords(string fileName);

int main(int argc, char *argv[]) {
    // Part 1: Get all the unique words
    string HalfFile = ".txt";
    string FullFile = argv[1] + HalfFile;
    set<string> singleWords;
    ifstream in;
    string line;
    in.open(FullFile);
    while(getline(in, line)) {
        istringstream sst(line);
        string word;
        while(sst >> word) {
            string onlyLetters = "";
            for(auto i : word) {
                if(isalpha(i)) {
                    onlyLetters += i;
                }
            }
            singleWords.insert(onlyLetters);
        }
    }
    in.close();
    ofstream out;

    string fileNameHalf = "_set.txt";
    string fileNameFull = argv[1] + fileNameHalf;
    out.open(fileNameFull);
    for(auto i : singleWords) {
        out << i << endl;
    }
    out.close();

    // Part 2: Get all the words
    vector<string> allWords = AllWords(argv[1]);

    // Part 3: Make a word map
    map<string,string> wordMap;
    string last = "";
    for(vector<string>::iterator it = allWords.begin(); it != allWords.end(); it++) {
        wordMap[last] = *it;
        last = *it;
    }
    fileNameHalf = "_map.txt";
    fileNameFull = argv[1] + fileNameHalf;
    out.open(fileNameFull);
    for(auto i : wordMap) {
        out << i.first << ", " << i.second << endl;
    }
    out.close();

//    // Part 4: Generate Text from your word map
//    string state = "";
//    for(int i = 0; i < 100; ++i) {
//        cout << wordMap[state] << " ";
//        state = wordMap[state];
//    }
//    cout << endl << endl;
//
//    // Part 5: Make a map where the value is every word after the key
//    map<string, vector<string>> secondMap;
//    state = "";
//    for(vector<string>::iterator it = allWords.begin(); it != allWords.end(); it++) {
//        secondMap[state].push_back(*it);
//        state = *it;
//    }
//
//    srand(time(NULL));
//    state = "";
//    for(int i = 0; i < 100; ++i) {
//        int ind = rand() % secondMap[state].size();
//        cout << secondMap[state][ind] << " ";
//        state = secondMap[state][ind];
//    }
//    cout << endl << endl;

    // Part 6: Make the key give more context
    map<list<string>, vector<string>> thirdMap;
    list<string> state2;
    int M = 3;
    for (int i = 0; i < M; i++) {
        state2.push_back("");
    }
    for(vector<string>::iterator it = allWords.begin(); it != allWords.end(); it++) {
        thirdMap[state2].push_back(*it);
        state2.push_back(*it);
        state2.pop_front();
    }

    state2.clear();
    for (int i = 0; i < M; i++) {
        state2.push_back("");
    }
    for(int i = 0; i < 100; i++) {
        int ind = rand() % thirdMap[state2].size();
        cout << thirdMap[state2][ind] << " ";
        state2.push_back(thirdMap[state2][ind]);
        state2.pop_front();
    }

    //Part 7: Recreate the Odyssey by Homer
    // Insert the text file "Homer" and see what comes!!
    return 0;
}

vector<string> AllWords(string FileName) {
    string HalfFile = ".txt";
    string FullFile = FileName + HalfFile;
    vector<string> allWords;
    ifstream in;
    string line;
    in.open(FullFile);
    while(getline(in, line)) {
        istringstream sst(line);
        string word;
        while(sst >> word) {
            string onlyLetters = "";
            for(auto i : word) {
                if(isalpha(i)) {
                    onlyLetters += i;
                }
            }
            allWords.push_back(onlyLetters);
        }
    }
    in.close();
    ofstream out;

    string fileNameHalf = "_vector.txt";
    string fileNameFull = FileName + fileNameHalf;
    out.open(fileNameFull);
    for(auto i : allWords) {
        out << i << endl;
    }
    out.close();

    return allWords;
}