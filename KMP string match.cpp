//KMP string match algorithm (Knuth, Morris and Pratt)
//O(n)
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//longest proper prefix which is also proper suffix
void compute_lps(const string& s, vector<int>& lps)
{
    int length = 0;
    lps[0] = 0;
    int i = 1;
    while (i < s.size())
    {
        if (s[i] == s[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length == 0)
            {
                lps[i] = 0;
                i++;
            }
            else
                length = lps[length - 1];
        }
    }
}

void kmp(const string& text, const string& pattern)
{
    int n = text.size(), m = pattern.size();
    vector<int> lps(m);
    compute_lps(pattern, lps);

    int i = 0;
    int j = 0;
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            cout << "found in position " << i - j << endl;
            cout << text << endl << string(i - j, ' ') << pattern << endl;
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main()
{
    string text("AABAABA");
    string pattern("AABA");
    kmp(text, pattern);
}