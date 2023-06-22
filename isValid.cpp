bool isValid(string input) {
    int len = input.length();                       // len -> length of input
    unordered_map<char,char> prthMap;               // prthMap -> map of parathesises (see below)

    prthMap['('] = ')';
    prthMap['{'] = '}';
    prthMap['['] = ']';

    for (int step = 0; step < len; step += 2) {     // loop over the input on twos
        if (prthMap[input[step]] != input[step+1])  // if the current character doesn't corresp. to the next char (based on the map)
            return false;                           //    cancel the loop immediately and return false
    }

    return true;                                    // return true with no discrep. are found
}