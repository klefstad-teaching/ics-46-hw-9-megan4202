#include "./ladder.h"

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int length1 = str1.size();
    int length2 = str2.size();
    if (abs(length1 - length2) > d) return false;
    int i = 0, j = 0;
    while (i < length1 && j < length2) {
        if (str1[i] != str2[j]) {
            if (d <= 0) return false;
            int remainingDiff = d;
            for (int k = 1; k <= remainingDiff; ++k) {
                if (i + k < length1 && str1[i + k] == str2[j]) {
                    i += k;
                    d -= k;
                    break;
                } else if (j + k < length2 && str1[i] == str2[j + k]) {
                    j += k;
                    d -= k;
                    break;
                }
            }
            if (remainingDiff == d) --d;
        }
        ++i;
        ++j;
    }
    return length1 - i + length2 - j <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return false;
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    in.close();
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        for (const string& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return vector<string>();
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word : ladder)
        cout << word << ' ';
    cout << endl;
}

void error(string word1, string word2, string msg) {
    cout << "Word ladder error between words \"" << word1 << "\" and \"" << word2 << "\": " << msg << endl;
}