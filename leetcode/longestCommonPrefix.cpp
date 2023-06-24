string longestCommonPrefix(vector<string>& strs) {
    int len2 = INT_MAX, lsc = 0;
    string ss;
    for (string s : strs) {
        if (len2 > s.length()) {
            len2 = s.length();
            ss = s;
        }
    } 
    
    for (int i = 0; i < len2; i += 1) {
        for (string s : strs) {
            if (ss[i] != s[i]) return ss.substr(0,i);
        }
    }


    return ss;
}