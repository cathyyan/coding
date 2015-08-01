# Notes on LeetCode problems

## Reverse Nodes in k-Group

Pay attention to that the last less-than-K segment does not need a reversal!

```cpp
// Reverse a given list by reversing one at a time.
ListNode* Reverse(ListNode* head) {
    ListNode* new_head = nullptr;
    while (head) {
        // Every time reverse the 'next' field of 'head'.
        ListNode* tmp = head->next;
        head->next = new_head;
        new_head = head;
        head = tmp;
    }
    return new_head;
}

// Reverse every k nodes in a given singly-linked list.
ListNode* ReverseEveryK(ListNode* head, int k) {
    assert(k > 0);
    
    // Head and tail of the result list.
    ListNode* h = nullptr;
    ListNode* t = nullptr;
    
    while (head) {
        ListNode* tmp_head = head;
        
        // Count k nodes.
        ListNode* prev = nullptr;
        int remaining = k;
        while (head && remaining) {
            prev = head;
            head = head->next;
            --remaining;
        }
        prev->next = nullptr;
        // tmp_head is the head and prev is the tail node of the current segment.
        
        if (remaining) {      // THIS IS THE LAST and less-than-k segment!!!   <-------  HERE
            // Note that the last less-than-K segment should not be reversed.
            if (!t) {
                h = tmp_head;
                t = head;
            } else {
                t->next = tmp_head;
                t = head;
            }
        } else {
            Reverse(tmp_head);
            if (!t) {
                h = prev;
                t = tmp_head;
            } else {
                t->next = prev;
                t = tmp_head;
            }
        }
    }
    
    return h;
}
```

## Next ...
