#include "AutoCounter.h"
#include "TPStash.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
    PStash<AutoCounter> acStash;
    for(int i = 0; i < 10; i++) 
        acStash.add(AutoCounter::create());
    cout << "Removing 5 manually: " << endl;
    for(int j = 0; j < 5; j++)
        delete acStash.remove(j);
    cout << "Remove two without deleting them" << endl;
    cout << acStash.remove(5) << endl;
    cout << acStash.remove(6) << endl;
    cout << "The destructoe cleans up the rest:" << endl;
    ifstream in("TPStashTest.cpp");
    PStash<string> stringStash;
    string line;
    while(getline(in, line))
        stringStash.add(new string(line));
    for(int u = 0; stringStash[u]; u++)
        cout << "stringStash[" << u << "] = " << *stringStash[u] << endl;
} ///:~
