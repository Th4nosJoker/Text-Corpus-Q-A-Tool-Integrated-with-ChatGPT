// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    vector<string> sentences;
    vector<vector<int>> locations;

    void insert_sentence_util(const int& book_code, const int& page, const int& paragraph, const int& sentence_no, string sentence);

    int get_pattern_offset(const string& sentence , const string& pattern);

    void compute_bad_char_table(const string& pattern , vector<int>& bad_char);

    Node* search_util(string pattern , int& n_matches);

public: 
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);
};