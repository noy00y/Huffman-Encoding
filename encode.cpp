#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <iterator>
#include <typeinfo>
#include <queue>
using namespace std;

// Public Stuff:
vector<char> convert = {'\t', '\v', '\r', '\n'};
vector<char> other = {'.', ',', ' '};
vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
map<char, int> frequencies;

// Structures:
struct Node {
    char data;
    int frequency;
    string binary_code;
    struct Node *right, *left;

    // Constructor:
    Node(char d, int f) {
        data = d;
        frequency = f;
        right = NULL;
        left = NULL;
    }

    Node(int f) {
        frequency = f;
        right = NULL;
        left = NULL;
    }

    // Comparison Operator for Queue
    bool operator<(const Node& node) const {return frequency > node.frequency;} 
};

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

vector<char> create_lines(vector<string> lines) {
    vector<char> copy;
    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        for (int q = 0; q < line.size(); q++) {
            // Eval Each Condition --> Confirm lowercase and push
            if (isalpha(line[q])) {
                if (isupper(line[q])) {line[q] = tolower(line[q]);}
                copy.push_back(line[q]);
                frequencies[line[q]]++;
            }
            // Number Condition --> Push
            else if (isdigit(line[q])) {
                copy.push_back(line[q]);
                frequencies[line[q]]++;
            }
            // Whitespace condition --> Convert
            else if (count(convert.begin(), convert.end(), line[q])) {
                line[q] = ' ';
                copy.push_back(line[q]);
                frequencies[line[q]]++;
            }
            // Other Characters
            else if (count(other.begin(), other.end(), line[q])) {
                copy.push_back(line[q]);
                frequencies[line[q]]++;
            }
            // Check Ignored
            // else {cout << line[q];}
        }
    }
    return copy;
}

void set_lines(string line, string file_name) {
    ofstream file;
    file.open(file_name, std::ios_base::app);
    file << line << "\n";
    file.close();
    return;
}

// Driver Code:
int main(){
    // Declarations
    string file_name = "input.txt"; // Input File name
    size_check(file_name); // Check File Size:
    vector<string> lines = get_lines(file_name); // Get Lines from File

    // Create frequencies.txt:
    map<char, int>::iterator itr;

    // Initialize the frequencies:
    for (int i = 0; i < other.size(); i++) {
        frequencies[other[i]] = 0;
    }
    for (int i = 0; i < alphabet.size(); i++) {
        frequencies[alphabet[i]] = 0;
    }   
    for (int i = 0; i < numbers.size(); i++) {
        frequencies[numbers[i]] = 0;
    }

    vector<char> copy = create_lines(lines); // using this char copy we will create a bin file from the converted accii characters (binary)

    priority_queue <Node> heap; // Create Heap
    // Create filtered copy of text:
    for (itr = frequencies.begin(); itr != frequencies.end(); ++itr) { // Loop and add to file
        string c(1, itr->first); // character
        string n = to_string(itr->second); // frequency

        // Create node:
        Node node = {itr->first, itr->second};
        // cout << node.data << ": " << node.frequency << endl;
        heap.push(node);
        // Print to frequency file
        // set_lines(c + ":" +  n, "frequency.txt");
    }    
    cout << "--------------------------------------------" << endl;
    while (heap.empty() == false) {
        Node node = heap.top();
        cout << node.data << ": " << node.frequency << endl;
        heap.pop();
    }

    // Build Huffman Tree:
    // Node root = build_tree(heap);
    // printTree(&root);
}