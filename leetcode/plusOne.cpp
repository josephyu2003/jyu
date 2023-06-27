class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;

        if (digits[i] != 9) {
            digits[i] += 1;
            return digits;
        }

        for (; i > -1; i--) {
            if (digits[i] == 9)  digits[i] = 0;
            else {
                digits[i] += 1;
                return digits;
            }
        }

        digits.resize(digits.size() + 1);
        digits[0] = 1;
        return digits;

    }
};