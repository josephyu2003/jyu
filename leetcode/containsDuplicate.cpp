bool containsDuplicate(vector<int>& input) {
    
    int len = input.size();                     // len -> number of integer units within vector
    unordered_map<int,int> temp;                // temp -> hash table to save units that were detected once through iteration
    
    for (int i = 0; i < len; i += 1) {          // iterate through the entire vector
        if (temp[input[i]] == 1) return true;   // if any unit gets detected twice, cancel the loop and succeed
        else temp[input[i]] = 1;                // else, add the unit to the hash table
    }

    return false;                               // if successes not found, return false

}
