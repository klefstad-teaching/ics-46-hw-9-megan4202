#include "./ladder.h"

int main() {
    string start_word, end_word;
    cout << "Enter two words to find the minimum word ladder between.\n";
    cout << "Start word: ";
    cin >> start_word;
    cout << "End word: ";
    cin >> end_word;
    if (start_word == end_word)
        error(start_word, end_word, "start and end words can not be the same");
    else {
        set<string> word_list;
        load_words(word_list, "../src/words.txt");
        vector<string> word_ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(word_ladder);
    }
}