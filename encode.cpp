#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Functions:
void size_check(ifstream& file) {
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    if (file_size > 100000) {
        cout << "File size exceeds maximum input of 100 KB" << endl;
        throw invalid_argument("File size exceeds maximum input of 100 KB");
    }
    return;
}

void remove(ifstream& fileIn, ofstream& fileOut) {
    char next;
    fileIn.get(next);
    
    do {
        cout << "Char: " << next << endl;
        fileIn.get(next);
    } while (!fileIn.get(next));
}

// Driver Code:
int main(){
    // Declarations:
    string file_name = "input.txt";
    ifstream fileIn(file_name, ios::binary);
    ofstream fileOut;
    
    // Check File Size:
    size_check(fileIn);

    // Remove all required characters from the file:
    remove(fileIn, fileOut);

    return 0;
}