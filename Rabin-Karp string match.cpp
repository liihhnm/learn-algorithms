//Rabin-Karp string match
//preprocess time O(m)
//average process time O(n)
//worsest time O( (n - m + 1) * m)
/*****************************************************************************************
*  hash( txt[s+1 .. s+m] ) = (d * ( hash( txt[s .. s+m-1]) – txt[s] * h ) + txt[s + m] ) mod q
*
*  hash( txt[s .. s+m-1] ) : Hash value at shift s.
*  hash( txt[s+1 .. s+m] ) : Hash value at next shift (or shift s+1)
*  d: Number of characters in the alphabet
*  q: A prime number
*  h: d^(m-1) mod q
*****************************************************************************************/
#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define ALPHABET_SIZE 256

void rabin_karp(const string& text, const string& pattern, int q)
{
    int n = text.size(), m = pattern.size();
    int t = 0, p = 0;
    int h = 1;
    //calculate h (d ^ (m - 1) mod q)
    for (int i = 0; i < m - 1; i++)
        h = (h * ALPHABET_SIZE) % q;
    //calculate pattern number mod q, first m characters of text mod q
    for (int i = 0; i < m; i++)
    {
        t = (ALPHABET_SIZE * t + text[i]) % q;
        p = (ALPHABET_SIZE * p + pattern[i]) % q;
    }

    //shift the pattern over text one by one
    for (int i = 0; i <= n - m; i++)
    {
        if (t == p)
        {
            if (text.compare(i, m, pattern) == 0)
            {
                cout << "found in position " << i << endl;
                cout << text << endl << string(i, ' ') << pattern << endl;
            }
        }

        //calculate next hash value
        if (i < n - m)
        {
            t = (ALPHABET_SIZE * (t - text[i] * h) + text[i + m]) % q;
            //might get negative value
            if (t < 0)
                t += q;
        }
    }
}

int main()
{
    string text("AABAABA");
    string pattern("AABA");
    rabin_karp(text, pattern, 201);
}

