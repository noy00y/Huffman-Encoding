#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<char, int> frequencies;
    frequencies['a']++;
    frequencies['a']++;
    frequencies['a']++;
    
    for (int i = 0; i < frequencies.size(); i++) {
        cout << frequencies[i];
    }

    return 0;
}