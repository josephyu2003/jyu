int romanToInt(string ltr) {                // ltr -> letters

    unordered_map<char, int> lgd;           // lgd -> legend
        
    lgd['I'] = 1;                           // map out each possible letter to their integer values
    lgd['V'] = 5;
    lgd['X'] = 10;
    lgd['L'] = 50;
    lgd['C'] = 100;
    lgd['D'] = 500;
    lgd['M'] = 1000;
        
    int sum = 0;                            // sum -> sum of the parts
        
    for(int i = 0; i < ltr.length(); i++){  // loop over letters
        if(lgd[s[i]] < lgd[s[i+1]]){        // if the next letter has a larger value
            sum -= lgd[s[i]];               // subtract the corresp. value from the sum (from the legend)
        }
        else{          
            sum += lgd[s[i]];               // otherwise, add the corresp. value to the sum
        }
    }

    return sum;                             // return the resulting sum (the converted form of the roman numeral)
}