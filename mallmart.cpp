
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createRevision(istream& fold, istream& fnew, ostream& frevision);
bool revise(istream& fold, istream& frevision, ostream& fnew);

int main() {
    return 0;
}

// helpfer functions for creating revision file 
bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, char& delim, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
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

