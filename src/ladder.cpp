#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}


using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {

    // len of both
    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len2 - len1) > d) {
        return false;
    }

    int diffCount = 0;
    int in1 = 0;
    int in2 = 0;
    
    while (in1 < len1 && in2 < len2) {
        if (str1[in1] != str2[in2]) {
            ++diffCount;
            if (diffCount > 1) 
                return false;
            if (len1 == len2) {
                ++in1;
                ++in2;
            } else if (len1 > len2) {
                ++in1;
            } else {
                ++in2;
            }
        } else {
            ++in1;
            ++in2;
        }
    }

    // if (in1 < len1 || in2 < len2) {
    //     ++diffCount;
    // }
    return diffCount <= 1;  
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    // checks for file
    if (!file) {
        cerr << "File not open " << file_name << endl;
        return;
    }
    // load words & safely close
    for (string word; file >> word; ) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    // if empty returns 
    if (ladder.empty()) {
        cout << "No word ladder found:\n";
        return;
    }
    // ladder found
    cout << "Word ladder found: " << endl;
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    // pushes start word
    ladder_queue.push({begin_word});

    // tracker
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder; 
                    } 
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}