#include <bits/stdc++.h>
using namespace std;

vector<string> get_array_from_file(string src){

    fstream file(src);
    vector<string> words;

    if (!file){
        cerr << "\nCan't Open File " << src << " Some Error Occurred.!\n";
        return words;
    }

    while (!file.eof())
    {
        string word;
        getline(file, word);
        if (word.size())
            words.push_back(word);
    }

    return words;
}
// ? KMP Matching.
// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(string pat, int M, int lps[]){
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0){
                len = lps[len - 1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
int KMPSearch(string pat, string txt){

    int M = pat.size();
    int N = txt.size();
    int lps[M];
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]

    while (i < N){

        if (pat[j] == txt[i]){

            j++;
            i++;
        }

        if (j == M){
            // printf("Found pattern at index %d ", i - j);
            return i - j;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]){
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

vector<string> search(vector<string> v, string pat){

    vector<string> results;

    for (auto str : v){
        
        if (KMPSearch(pat, str) != -1){

            results.push_back(str);
        }
    }
    
    return results;
}
