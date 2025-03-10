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