int lengthOfLongestSubstring(string s) {

    unordered_map<char,int> temp;                                   // temporary map to hold the goods
    int len = s.length();                                           // len -> length of the string
    int cnt = 0;                                                    // cnt -> number of iterations through the largest substring
    int lsd = 0;                                                    // lsd -> least significant digit

    for (int msd = 0; msd < len; msd += 1) {                        // loop over the string with msd -> most significant digit
        if (temp.count(s[msd]) == 0 || temp[s[msd]] < lsd) {        // if the current character is not in the map, or if the table resetted last iteration
            temp[s[msd]] = msd;                                     //   update the table
            cnt = max(cnt, msd - lsd + 1);                          //   if the current substring is the longest, reset count to the substring's length
        } else {                                                    // else
            lsd = temp[s[msd]] + 1;                                 //   reset the table (by resetting lsd)
            temp[s[msd]] = msd;                                     //   update the table 
        }
    }
    
    return cnt;                                                     // return the count

}
