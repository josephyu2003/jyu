bool isPalindrome(ListNode* head) {
    ListNode *temp1 = head, *temp2 = head, *prev, *temp3;
    while (temp2 && temp2->next)                                                // loop through the entire list
        temp1 = temp1->next, temp2 = temp2->next->next;                         // temp1 goes to the mid, temp2 goes to the end
    prev = temp1, temp1 = temp1->next, prev->next = NULL;                       
    while (temp1)
        temp3 = temp1->next, temp1->next = prev, prev = temp1, temp1 = temp3;   // reverse the list so that temp1 and temp2 go back to the ends
    temp2 = head, temp1 = prev;
    while (temp1)
        if (temp2->val != temp1->val) return false;                             // if the corresp. nodes on each side are not equal, return false
        else temp2 = temp2->next, temp1 = temp1->next;                          // iterate to the next two nodes
    return true;                                                                // if everything passes, return true
}