class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        e = curr = head
        s = head = ListNode()
        n = 0
        prev = None
        while curr:
            n+=1
            #reversing nodes
            nt = curr.next
            curr.next = prev
            prev = curr
            curr = nt
            #joining the last and current part on reaching the partition point
            if n % k == 0 and n>=k:
                s.next = prev
                s = e
                e = curr   
        #checking whether the list is completely divided in k parts or not
        if n>=k and n%k != 0:
            #reversing direction of reversal from the right end
            prev,curr = curr,prev
            while prev != e:
                nt = curr.next
                curr.next = prev
                prev = curr
                curr = nt
        s.next = e
        return head.next
