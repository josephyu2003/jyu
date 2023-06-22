ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* sum = new ListNode();
    ListNode* ans = sum;                                // ans -> answer, sum -> total sum
    int i, cr = 0;                                      // cr -> carry, i -> iterated sum
    while (l1 != NULL || l2 != NULL || cr) {            // loop over both initial lists (and carry)
        i = 0;                                          // reset the iterated sum
        if (l1!=NULL) {
            i += l1->val;                               // add the first value
            l1 = l1->next;
        }
        if (l2!=NULL) {
            i += l2->val;                               // add the second value
            l2 = l2->next;
        }
        i += cr;                                        // add the carry
        cr = i/10;                                      // update the carry with the ten's place
        i = i%10;                                       // reduce the sum to the one's place
        ListNode* next = new ListNode(i);               
        sum->next = next;                               // add a new node
        sum = sum->next;                                // increment the node
    }
    sum = ans;
    ans = ans->next;
    delete sum;                                         // delete the first node (to prevent leak)
    return ans;                                         // return the resulting list
}
