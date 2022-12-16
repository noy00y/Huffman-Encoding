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
map<char, string> codes;

// Utils:
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

// Structures and their methods:
struct Node {
    char data;
    int frequency;
    struct Node *right, *left;
};

Node *create_node(int frequency) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->frequency = frequency;
    node->right = node->left = NULL;
    return node;
}

struct Heap {
    int size;
    int capacity;
    struct Node** array;
};

Heap *create_heap(int capaacity) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capaacity;
    heap->array = (struct Node**)malloc(heap->capacity * sizeof(Node*));
    return heap;
}

// Functions:
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void heapify(Heap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1; // get left node
    int right = 2 * index + 2; // get right node
 
    // If left child smaller then "smallest" node --> set left child to smallest
    if (left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency) {smallest = left;}
 
    // If right child smaller then "smallest" node --> set right child to smallest
    if (right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency) {smallest = right;}
 
    // If root node is not the smallest --> swap with smallest
    if (smallest != index) {
        swap(&heap->array[smallest], &heap->array[index]);
        heapify(heap, smallest); // heapify again with new root
    }
    return;
}

void insert(Heap *heap, Node *node) {
    ++heap->size; // increment heap size
    int i = heap->size - 1; // index --> leaf node
    // While node frequenecy less then parent node frequency
    while (i && node->frequency < heap->array[(i - 1) / 2]->frequency) {
        heap->array[i] = heap->array[(i - 1) / 2]; // set parent as leaf index
        i = (i - 1) / 2; // change index
    }
    heap->array[i] = node; // set node at index
    return;
}

void build_heap(Heap *heap) {
    int n = heap->size - 1;
    int i;

    // Heapify at each parent node
    for (i = (n - 1) / 2; i >= 0; --i) {
        heapify(heap, i);
    }
    return;
}

Node *pop(Heap *heap) {
    Node* node = heap->array[0]; // get min node from heap
    heap->array[0] = heap->array[heap->size - 1]; // set root as a leaf node
    --heap->size; // Decrement size of heap
    heapify(heap, 0);
    return node;
}

Node *build_tree(Heap *heap) {
    Node *left, *right, *root;
    while (heap->size > 1) {
        left = pop(heap);
        right = pop(heap);
        root = create_node(left->frequency + right->frequency);
        root->left = left;
        root->right = right;
        insert(heap, root);
    }
    return pop(heap);
}

void assign_codes(Node *node, char arr[], int index) {
    cout << node->data << ": ";
    string temp = "";
    for (int i = 0; i < index; ++i) {
        // cout << arr[i];
        temp.push_back(arr[i]);
    }
    cout << temp << endl;
    string c(1, node->data);
    codes.insert({node->data, temp});
    set_lines(c + ":" + temp, "codes.txt");
    return;
}

// string c(1, itr->first); // character
// string n = to_string(itr->second); // frequency

void create_codes(Node *root, char arr[], int index) {
    if (root->left) {
        arr[index] = '0';
        create_codes(root->left, arr, index + 1);
    }
    if (root->right) {
        arr[index] = '1';
        create_codes(root->right, arr, index + 1);
    }
    if (!(root->left) && !(root->right)) {
        assign_codes(root, arr, index);
    }
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
    // Create filtered copy of text:
    Heap *heap = create_heap(39);
    int counts = 0;


    // Loop and add to file:
    for (itr = frequencies.begin(); itr != frequencies.end(); ++itr) { 
        string c(1, itr->first); // character
        string n = to_string(itr->second); // frequency

        // Create node and push to heap
        heap->array[counts] = create_node(itr->second);
        heap->array[counts]->data = itr->first;
        ++counts;
        set_lines(c + ":" +  n, "frequency.txt");
    }
    heap->size = 39;
    build_heap(heap);    
    cout << "--------------------------------------------" << endl;

    // Build Huffman Tree:
    Node *root = build_tree(heap);
    char arr[100];
    create_codes(root, arr, 0);

    // Loop Through Codes:

}