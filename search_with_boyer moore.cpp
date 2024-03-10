// Do NOT add any other includes
#include "search_1.h"

void SearchEngine::insert_sentence_util(const int& book_code, const int& page, const int& paragraph, const int& sentence_no, string sentence){
    for (char &c : sentence){
        c = tolower(c);
    }

    sentences.push_back(sentence);
    vector<int> location = {book_code, page, paragraph, sentence_no};
    locations.push_back(location);
}

void SearchEngine::compute_bad_char_table(const string& pattern , vector<int>& bad_char){
    int pat_len = pattern.length();

    for(int i = 0 ; i < pat_len ; i++){
        bad_char[static_cast<int>(pattern[i])] = i;
    }
}

int SearchEngine::get_pattern_offset(const string& sentence , const string& pattern){
    int sen_len = sentence.length();
    int pat_len = pattern.length();

    if(pat_len == 0 || sen_len < pat_len){
        return -1;
    }

    vector<int> bad_char(128, -1);
    compute_bad_char_table(pattern, bad_char);

    int offset = 0 , limit = sen_len - pat_len;
    while(offset <= limit){
        int i = pat_len - 1;
        while(i >= 0 && pattern[i] == sentence[offset + i]){
            i--;
        }

        if(i < 0){
            return offset;
        }else{
            offset += (i - bad_char[static_cast<int>(sentence[offset + i])] > 0) ? i - bad_char[static_cast<int>(sentence[offset + i])] : 1;
        }
    }

    return -1;
}

Node* SearchEngine::search_util(string pattern , int& n_matches){
    for(char &c : pattern){
        c = tolower(c);
    }

    Node *sentinel_head = new Node(-1, -1, -1, -1, -1);
    Node *tail = sentinel_head;

    for(int i = 0 ; i < sentences.size() ; i++){
        int offset = get_pattern_offset(sentences[i] , pattern);
        if(offset != -1){
            n_matches++;
            Node *node = new Node(locations[i][0], locations[i][1], locations[i][2], locations[i][3], offset);
            tail->right = node;
            node->left = tail;
            tail = node;
        }
    }

    Node *head = sentinel_head->right;
    delete sentinel_head;
    sentinel_head = nullptr;

    return head;
}

SearchEngine::SearchEngine(){
    
}

SearchEngine::~SearchEngine(){
    
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    insert_sentence_util(book_code , page , paragraph , sentence_no , sentence);
}

Node* SearchEngine::search(string pattern, int& n_matches){
    return search_util(pattern , n_matches);
}