#include <iostream>
#include <queue>
using namespace std;

struct thing
{
    int a;
    char b;
    bool operator<(const thing& rhs) const
    {
        return a < rhs.a;
    }
};

int main()
{
    priority_queue<thing> q;
    thing stuff = {42, 'x'};
    q.push(stuff);
    thing otherStuff = q.top();
    q.pop();
    cout << otherStuff.a << endl;    
    return 0;
}