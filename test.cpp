#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    map<char, int> frequencies;
    frequencies['a']++;
    frequencies['a']++;
    frequencies['b']++;
    frequencies['b']++;
    frequencies['b']++;
    frequencies['c']++;

    map<char, int>::iterator it;
    for (it = frequencies.begin(); it != frequencies.end(); ++it) {
        cout << it->first << ": " << it->second;
        cout << endl;
    }

    return 0;
} 