
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "Hashtable.h"

using namespace std;

#define N_LENGTH 8



void createRevision(istream &fold, istream &fnew, ostream &frevision)
{
    // Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
    string oldFile;
    string newFile;

    if (!fold)
    {
        cerr << "Error: Cannot open fold!" << endl;
        return;
    }

    string foldLine;
    while (getline(fold, foldLine))
    {
        oldFile += foldLine + "\n";
    }

    if (!fnew)
    {
        cerr << "Error: Cannot open fnew!" << endl;
        return;
    }

    string fnewLine;
    while (getline(fnew, fnewLine))
    {
        newFile += fnewLine + "\n";
    }

    // cout << oldFile;
    // cout << newFile;

    // For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in
    // the old file's string, into a table (e.g. hash table or binary search tree). You might use 8 for N, or maybe 16
    
    
};
bool revise(istream &fold, istream &frevision, ostream &fnew);

// helpfer functions for creating revision file
bool getInt(istream &inf, int &n)
{
    char ch;
    if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream &inf, char &cmd, char &delim, int &length, int &offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x'; // signals end of file
        return true;
    }
    switch (cmd)
    {
    case '+':
        return inf.get(delim).good();
    case '#':
    {
        char ch;
        return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
    }
    case '\r':
    case '\n':
        return true;
    }
    return false;
}

// fold: an already-opened input source (for yesterday's full file, say)
// frevision: an already-opened input source (the revision file)
// fnew: an already-opened output destination to which you will write the file resulting from applying the revision file to the first input.

void testHashtable()
{
    HashTable table(8);

    table.insert("abc", 1005);
    table.insert("lilly", 1);
    assert((table.find("abc").second == 1005));
    assert((table.find("lilly") == pair<string, int>("lilly", 1)));
    assert((table.find("max") == pair<string, int>("", -1)));

    cout << "ALL TESTS PASSED" << endl;
}

int main()
{

    ifstream oldfile("old.txt");
    ifstream newfile("new.txt");
    ofstream outfile("output.txt");
    createRevision(oldfile, newfile, outfile);
    testHashtable();
    return 0;
}

// to create/compile:
// g++ *.cpp -o mallmart && ./mallmart