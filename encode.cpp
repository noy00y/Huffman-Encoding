#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
using namespace std;

// Public Stuff:
vector<char> convert = {'\t', '\v', '\r', '\n'};
vector<char> other = {'.', ',', ' '};
map<char, int> frequencies;
// frequencies['line[q]']++;

// Functions:
void size_check(string file_name) {
    ifstream file(file_name, ios::binary);
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    if (file_size > 100000) {
        cout << "File size exceeds maximum input of 100 KB" << endl;
        throw invalid_argument("File size exceeds maximum input of 100 KB");
    }else {cout << "File size within 100 KB limit" << endl;}
    return;
}

vector<string> get_lines(string file_name) {
    cout << "Getting Lines from file" << endl;
    fstream file;
    vector<string> lines;
    file.open(file_name, ios::in);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

// vector<string> set_lines(string file_name) {
//     return;
// }

vector<char> create_lines(vector<string> lines) {
    cout << "Removing white spaces" << endl;
    vector<char> copy;
    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        for (int q = 0; q < line.size(); q++) {
            // Eval Each Condition --> Confirm lowercase and push
            if (isalpha(line[q])) {
                if (isupper(line[q])) {line[q] = tolower(line[q]);}
                copy.push_back(line[q]);
            }
            // Number Condition --> Push
            else if (isdigit(line[q])) {
                copy.push_back(line[q]);
            }
            // Whitespace condition --> Convert
            else if (count(convert.begin(), convert.end(), line[q])) {
                line[q] = ' ';
                copy.push_back(line[q]);
            }
            // Other Characters
            else if (count(other.begin(), other.end(), line[q])) {
                copy.push_back(line[q]);
            }
            // Check Ignored
            // else {cout << line[q];}
        }
        // cout << lines[i] << endl;
    }
    return copy;
}



// Driver Code:
int main(){
    string file_name = "input.txt"; // Declarations:
    size_check(file_name);// Check File Size:
    vector<string> lines = get_lines(file_name); // Get Lines from File
    vector<char> copy = create_lines(lines); // using this char copy we will create a bin file from the converted accii characters (binary)
    

    return 0;
}