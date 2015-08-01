# Merge Two Sorted Lists

This problem is very simple and is what everyone should have learned from their textbook during college. I just want to point out a trick here, that is, when at least one of the two list pointers is not NULL, we can get a _reference_ to where we are going to grab the next new node. This trick results shorter and more concise code.

```cc
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;  // New list's head pointer
        ListNode* tail = nullptr;  // New list's tail pointer
        
        while (l1 || l2) {
            // There are remaining nodes to merge into the new list              <<----  HERE
            ListNode*& drop = l1 && (!l2 || l1->val < l2->val) ? l1 : l2;
            
            // append 'drop' to the new list
            if (tail) {
                tail->next = drop;
                tail = drop;
            } else {
                head = tail = drop;
            }
            
            drop = drop->next;
            tail->next = nullptr;
        }
        
        return head;
    }
```
