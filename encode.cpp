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

// Classes:
class Node {
public:
    char data; // leaf node 
    int frequency; // frequency of node
    string binary_code; // leaf node
    Node *right, *left;

public:
    // Constructor:
    Node(){return;}

    Node(int f) {
        frequency = f;
    }
    void set_data(char d) {
        data = d;
    }
    void set_code(string c) {
        binary_code = c;
    }
};

class Compare {
public:
    int operator() (const Node& p1, const Node& p2)
    {
        return p2.frequency < p1.frequency;
    }
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

vector<char> create_lines(vector<string> lines) {
    cout << "Filtering" << endl;
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

Node build_tree(priority_queue <Node, vector<Node>, Compare> heap) {
    
    Node *root, *left, *right; // Initialize top node with 0 frequency

    while (heap.size() > 1)
    {
        // Pop off 2 of the smallest nodes and compare
        Node L = heap.top();heap.pop();
        Node R = heap.top();heap.pop();
        left = &L;
        right = &R;

        // cout << a.data << ": " << a.frequency << endl;
        // cout << b.data << ": " << b.frequency << endl;
        // cout << "-----" << endl;
        
        // Merge Nodes:
        Node temp = Node(left->frequency + right->frequency); // create node with combined frequency
        root = &temp;
        root->left = left;
        root->right = right;
        heap.push(*root);
    }
    return *root;
}

void printTree(Node* root) {
    cout << "printing"<< endl;
    if (root == NULL) {
        cout << "return" << endl;
        return;
    }
    printTree(root->left);
    cout << "Frequency: " << root->frequency << endl;
    printTree(root->right);
    return;
}

// Driver Code:
int main(){
    // Declarations
    string file_name = "input.txt"; // Input File name
    size_check(file_name);// Check File Size:
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

    priority_queue <Node, vector<Node>, Compare> heap; // Create Heap
    // Create filtered copy of text:
    for (itr = frequencies.begin(); itr != frequencies.end(); ++itr) { // Loop and add to file
        string c(1, itr->first); // character
        string n = to_string(itr->second); // frequency

        // Create node:
        Node node = Node(itr->second);
        node.data = itr->first;

        // cout << node.data << ": " << node.frequency << endl;
        heap.push(node);

        // Print to frequency file
        // set_lines(c + ":" +  n, "frequency.txt");
    }    

    // Build Huffman Tree:
    Node root = build_tree(heap);
    printTree(&root);
}