//
//  Project 1 Starter Code - DNA Profiling
//  Shivam Patel
//  spate585
//  656303359
#include "ourvector.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct User {
  string name;
  ourvector<int> dnaFrequancy;
};
ourvector<string> convertStringtoVector(string x) {
    ourvector<string> result;
    string y = "";
    for (int i = 0; i < (int)x.size(); i++) {
        if (x[i] == ',') {
            if (y != "name") result.push_back(y);
            y = "";
        } else {
            y += x[i];
        }
    }
    result.push_back(y);
    return result;
}
bool isStringMatching(string x, string y, int low, int high) {
    for (int i = low; i <= high; i++) {
        if (x[i] != y[i-low]) return false;
    }
    return true;
}
// function which counts the maximum mathc of the DNA used the for loop and I used
//the if else condition to check hwo much maximum DNA is matched
int countMaximumMatchDna(string dna, string y) {
    int maximum = 0;
    int currMaximum = 0;
    for (int i = 0; i < (int)dna.size(); i++) {
        if (isStringMatching(dna, y, i, i + y.size() - 1)) {
            currMaximum++;
            maximum = max(maximum, currMaximum);
            i = i + y.size() - 1;
        } else {
            currMaximum = 0;
        }
    }
    return maximum;
}
// This function loads the Database and will give the error message
// if fails to opens.
void loadDatabase(ourvector<User*> &userDetails,
    ourvector<string> &pattern, ourvector<int> &dnaProcess) {
    cout << "Loading database..." << endl;
    string word;
    cin >> word;
    ifstream userFile(word);
    if (userFile.fail()) {
        cout << "Error: unable to open '" << word << "'" << endl;
        return;
    }
    getline(userFile, word);
    pattern.clear();
    pattern = convertStringtoVector(word);
    userDetails.clear();
    dnaProcess.clear();
    while (getline(userFile, word)) {
        ourvector<string> temp = convertStringtoVector(word);
        ourvector<int> freq;
        User* userInfo = new User();
        for (int i = 0; i < temp.size(); i++) {
            if (i == 0) {
                userInfo->name = temp[i];
                continue;
            }
            freq.push_back(stoi(temp[i]));
        }
        userInfo->dnaFrequancy = freq;
        userDetails.push_back(userInfo);
    }
}
// loadDNA function loads all the DNA
void loadDna(ourvector<int> &dnaProcess, string &dna) {
    cout << "Loading DNA..." << endl;
    string word;
    cin >> word;
    ifstream userFile(word);
    if (userFile.fail()) {
        cout << "Error: unable to open '" << word << "'" << endl;
        return;
    }
    dnaProcess.clear();
    getline(userFile, dna);
}
// Function dnaProcessing processes all the dna and the if else
//condition checks if the DNA is processed or not.
void dnaProcessing(ourvector<User*> userDetails, string dna,
    ourvector<string> pattern, ourvector<int> &dnaProcess) {
    if (userDetails.size() <= 0) {
        cout << "No database loaded." << endl;
        return;
    }
    if (dna == "") {
        cout << "No DNA loaded." << endl;
        return;
    }
    cout << "Processing DNA..." << endl;
    if (dna == "") return;
    for (int i = 0; i < (int)pattern.size(); i++) {
        dnaProcess.push_back(countMaximumMatchDna(dna, pattern[i]));
    }
}
// searchDna function searches all the dna from the database. Here the
// If else condition checks from the dataabse if the DNA is found or not
// and if it doesn't found the error message will be displayed
// "No DNA loaded" and it will not processed.
void searchDna(ourvector<User*> userDetails, string dna,
    ourvector<int> dnaProcess) {
    if (userDetails.size() <= 0) {
        cout << "No database loaded." << endl;
        return;
    }
    if (dna == "") {
        cout << "No DNA loaded." << endl;
        return;
    }
    if (dnaProcess.size() <= 0) {
        cout << "No DNA processed." << endl;
        return;
    }
    cout << "Searching database..." << endl;
    bool flag = false;
    for (int i = 0; i < (int)userDetails.size(); i++) {
        int j;
        for (j = 0; j < (userDetails[i]->dnaFrequancy).size(); j++) {
            if (dnaProcess[j] != userDetails[i]->dnaFrequancy[j]) break;
        }
        if (j == dnaProcess.size()) {
            flag = true;
            cout << "Found in database!  DNA matches: " << userDetails[i]->name << endl;
            break;
        }
    }
    if (flag == false) {
        cout << "Not found in database. " << endl;
    }
}
// displayDnaDetails functions display all the DnaDetails
// after using the command "display".
void displayDnaDetails(ourvector<User*> userDetails, string dna,
    ourvector<string> pattern, ourvector<int> dnaProcess) {
    if (userDetails.size() <= 0) {
        cout << "No database loaded." << endl;
    } else {
        cout << "Database loaded: " << endl;
        for (int i = 0; i < (int) userDetails.size(); i++) {
            cout << userDetails[i]->name << " ";
            for (int j = 0; j < (int) pattern.size(); j++) {
                cout << userDetails[i]->dnaFrequancy[j];
                if (j != pattern.size()-1) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (dna == "") {
        cout << "No DNA loaded." << endl;
    } else  {
        cout  << "DNA loaded: " << endl;
        cout << dna << endl;
    }
    if (dnaProcess.size() <= 0) {
        cout << endl << "No DNA has been processed." << endl;
    } else {
        cout << endl << "DNA processed, STR counts: " << endl;
        for (int i = 0; i < (int) pattern.size(); i++) {
            cout << pattern[i] << ": ";
            cout << dnaProcess[i] << endl;
        }
        cout << endl;
    }
}
int main() {
    cout << "Welcome to the DNA Profiling Application." << endl;
    string word;
    ourvector<User*> userDetails;
    ourvector<string> pattern;
    ourvector<int> dnaProcess;
    string dna = "";
    while (true) {
        cout << "Enter command or # to exit: ";
        cin >> word;
        if (word == "#") break;
        if (word == "load_db")
            loadDatabase(userDetails, pattern, dnaProcess);
        if (word == "load_dna")
            loadDna(dnaProcess, dna);
        if (word == "process")
            dnaProcessing(userDetails, dna, pattern, dnaProcess);
        if (word == "search")
            searchDna(userDetails, dna, dnaProcess);
        if (word == "display")
            displayDnaDetails(userDetails, dna, pattern, dnaProcess);
    }
    return 0;
}
