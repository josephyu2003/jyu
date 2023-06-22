int maxProfit(vector<int>& input) {
    
    int len = input.size();                 // len -> number of integer units in vector
    int l = 0, temp = 0, output = 0;        // l -> iteration to "buy stock"; temp -> holder for stock gain at iteration; output -> return value (maximum stock gain)

    for (int r = 1; r < len; r += 1) {      // r -> iteration to "sell stock"
        
        if (input[l] < input[r]) {          // if the brought stock has a lesser value than the sold stock
            temp = input[r] - input[l];     // calculate the stock gain (return value of the market)
            output = max(output, temp);     // if the gain is greater than any previous gains, update the return value
        } 
        
        else {                              // if the brought stock has a greater value than the sold stock
            l = r;                          // make the sold stock the brought stock
        }

    }

    return output;                          // return the greatest stock price after iteration

}