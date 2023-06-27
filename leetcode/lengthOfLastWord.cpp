class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s == "") return 0;
        int h, l = -1;
        for (int i = s.length() - 1; i > -1; i -= 1) {
            if (s[i] != ' ') {
                h = i;
                break;
            }
        }
        for (int i = h; i > -1; i -= 1) {
            if (s[i] == ' ') {
                l = i;
                break;
            }
        }

        return h - l;
    }
};