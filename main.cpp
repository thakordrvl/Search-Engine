#include <bits/stdc++.h>
#include<fstream>
#include "trie.cpp"
#include "utils.cpp"
using namespace std;

// Title: Intelligent Text Search Engine
// Description: Designed and implemented an intelligent text search engine using advanced data structures and algorithms. 
// Leveraged a Trie-based indexing system to provide efficient search capabilities for large datasets. 
// Implemented features such as exact match search and prefix-based autocompletion. 
// Demonstrated proficiency in data structures, algorithm design, and optimization. 
// Empowered users to quickly find relevant information with minimal input, enhancing search efficiency and user experience.

int main(){

    string filename;
    Trie T;
    vector<string> data;
    int choice;
    cout << "Enter File name to load data from. ( music | movies | words ) :\n";
    cin >> filename;
    cerr << "loading ...";
    data = get_array_from_file(filename + ".txt");
    cerr << "Done.\n";
    
    for (auto word : data){
        T.insert(word);
    }

    do{

        cout << "------------------------\n";
        cout << "MENU\n";
        cout << "1. Exact Search.\n";
        cout << "2. Prefix Search.\n";
        cout << "3. Universal Search.\n";
        cout << "0. Exit.\n";

        cin >> choice;
        getchar();
        string pattern;
        
        if (choice){

            cout << "Enter Search Text (leave empty to list all) : ";
            getline(cin, pattern);
        }

        switch (choice){

            case 1:

                if (T.search_exact(pattern)){
                    cout << "String Exists.\n";
                }
                else{
                    cout << "NOT Found.\n";
                }

                break;

            case 2:

                for (string w : T.search_pre(pattern)){
                    cout << w << endl;
                }

                break;

            case 3:
                for (string w : search(data, pattern))
                {
                    cout << w << endl;
                }
                break;

            default:
                break;
        }

        cout << "\n\npress any key to continue.";
        getchar();

    } while (choice);

    return 0;
}


