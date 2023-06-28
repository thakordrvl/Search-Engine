#include <bits/stdc++.h>
using namespace std;

class TrieNode{

    public:
    unordered_map<char, TrieNode *> children;
    bool isEndOfWord = false;
};

class Trie{

public:

    TrieNode *root;

    Trie(){
        root = new TrieNode();
    }

    void insert(string str);
    void remove(string str);
    bool _remove(TrieNode *current, string str, int index);
    bool search_exact(string str);
    vector<string> search_pre(string str);

};

void Trie::insert(string str)
{
    TrieNode *current = root;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];

        if (current->children.find(ch) != current->children.end())
            current = current->children[ch];
        
        else{

            current->children.insert({ch, new TrieNode()});
            current = current->children[ch];
        }
    }

    current->isEndOfWord = true;
}

bool Trie::search_exact(string str){
    
    TrieNode *current = root;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            return NULL;
        }
    }
   
    return current->isEndOfWord;
}

void get_words_dfs(TrieNode *current, string pre, vector<string> &results)
{
    if (current == NULL){
        return;
    }

    if (current->isEndOfWord){
        results.push_back(pre);
    }

    for (auto it : current->children){
        get_words_dfs(it.second, (pre + it.first), results);
    }
}

vector<string> Trie::search_pre(string str){

    TrieNode *current = root;
    vector<string> results;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end()){
            current = current->children[ch];
        }

        else{
            return results;
        }
    }

    get_words_dfs(current, str, results);
    return results;
}

// Delete a string
void Trie::remove(string str)
{
    _remove(root, str, 0);
}

bool Trie::_remove(TrieNode *current, string str, int index){
    
    if (index == str.length()){
        // End of the word ?
        if (!current->isEndOfWord){
            return false; // word don't exist.
        }
        current->isEndOfWord = false;

        // if no more children
        return current->children.size() == 0; // true?
    }

    char ch = str[index];

    if (!current->children[ch]){
        return false; // word don't exist.
    }

    bool shouldDeleteCurrentNode = _remove(current->children[ch], str, index + 1);

    // after recursion
    if (shouldDeleteCurrentNode)
    {
        current->children.erase(ch);
        return current->children.size() == 0; // true ?
    }

    return false;
}
 