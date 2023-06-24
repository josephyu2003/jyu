bool isPalindrome(int x) {
    
    if (x < 0) return false;
    if (x == 0) return true;
    
    int l = 0, r = floor(log10(x));
    while (l <= r) {
        int ldiv = pow(10,l);
        int rdiv = pow(10,r);
        if ((x / ldiv) % 10 != (x / rdiv) % 10) return false;
        l += 1;
        r -= 1;
    }
    
    return true;

}