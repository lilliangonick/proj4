
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>

#include "Hashtable.h"

using namespace std;

#define N_LENGTH 4
#define CAPACITY 1000 // can change later
#define ALL_FLAG true

void createRevision(istream &fold, istream &fnew, ostream &frevision)
{
    // Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
    string oldFile;
    string newFile;
    string reviseString;
    HashTable table(CAPACITY);

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
    for (size_t offset = 0; offset < oldFile.size(); ALL_FLAG ? offset += 1 : offset += N_LENGTH)
    {
        string substring = oldFile.substr(offset, N_LENGTH); // offset is where we slice (exclusive)
        // IF STATEMENT IS INEFFICIENT FIX LATER
        if (substring.size() != N_LENGTH)
        {
            break;
        }
        table.insert(substring, offset);
    }

    // Start processing the new file's string, starting from offset j=0, until j reaches the end of the string
    // Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
    int offset = 0;
    while (offset <= newFile.size())
    {
        // If we have another room to grab a N-character substring
        if (offset + N_LENGTH <= newFile.size())
        {
            string substring = newFile.substr(offset, N_LENGTH);
            pair<string, int> data = table.find(substring);
            if (data.second != -1)
            { // if the substring was in the hash table
                // TODO See how long match is (OPTIMIZATION)
                //  DO COPY INSTRUCTION
                reviseString += "#" + to_string(data.second) + "," + to_string(N_LENGTH);
                offset += N_LENGTH; // once optimization, substring.size()
            }
            else
            {
                // TODO MUST OPTIMIZE LATER (single char copying right now)
                // TODO CHANGE DELIMINATOR (can not hard code the deliminator)
                string deliminator = "~";
                reviseString += "+" + deliminator + newFile[offset] + deliminator;
                offset += 1;
            }
        }
        else // if run out of n length strings
        {
            string substring = newFile.substr(offset, newFile.size() - offset);
            string deliminator = "~";
            reviseString += "+" + deliminator + substring + deliminator;
            break;
        }
    }
    cout << reviseString;
    frevision << reviseString;
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
    // testHashtable();
    return 0;
}

// to create/compile:
// g++ *.cpp -o mallmart && ./mallmart

// store the first char in each substring
// iterate through whole string

// delimator: look for a character that does not exist in the sequence we are adding/copying

// first 
// take in string and return something that is not in that string 