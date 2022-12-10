#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// File Class:


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

void remove(vector<string> lines) {
    cout << "Removing white spaces" << endl;
}

// Driver Code:
int main(){
    string file_name = "input.txt"; // Declarations:
    size_check(file_name);// Check File Size:
    vector<string> lines = get_lines(file_name); // Get Lines from File
    

    return 0;
}