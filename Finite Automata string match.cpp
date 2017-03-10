//finite automata string match
//http://www.geeksforgeeks.org/pattern-searching-set-5-efficient-constructtion-of-finite-automata/
//preprocess time O(m * ALPHABET_SIZE)
//process time O(n)
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

using namespace std;

#define ALPHABET_SIZE 256

void build_fa(const string& pattern, vector< vector<int> >& state_fun)
{
    int lps = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        state_fun[0][i] = 0;
    state_fun[0][pattern[0]] = 1;

    int m = pattern.size();
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < ALPHABET_SIZE; j++)
        {
            state_fun[i][j] = state_fun[lps][j];
        }
        if (i < m)
        {
            state_fun[i][pattern[i]] = i + 1;
            lps = state_fun[lps][pattern[i]];
        }
    }       
}

void string_match(const string& text, const string& pattern)
{
    int n = text.size(), m = pattern.size();
    vector< vector<int> > state(m + 1, vector<int>(ALPHABET_SIZE));
    build_fa(pattern, state);

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        j = state[j][text[i]];
        if (j == m)
        {
            cout << "found in position " << i - m + 1<< endl;
            cout << text << endl << string(i - m + 1, ' ') << pattern << endl;
        }
    }
}

int main()
{
    string text("AABAABA");
    string pattern("AABA");
    string_match(text, pattern);
}
