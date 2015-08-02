# Notes on LeetCode problems

## KMP implementation tricks

[KMP](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) is a fast `strstr()` algorithm. It is also easy to understand and implementation. However there are several tips on implement.

```
Do NOT ever call failure function on 0, to avoid endless loops.
```

It makes sense in that when you are at 0, there is no way to go backward more. The solo purpose of setting `f[0]` to 0 is for the convenience of populating the failure function array, whose code is shown below.

```c++
std::vector<int> buildFailureFunc(const std::string& needle) {
  std::vector<int> f(needle.length(), 0);
  for (std::size_t i = 2; i < needle.length(); ++i) {
    for (int k = f[i - 1]; k >= 0; k = k == 0 ? -1 : f[k]) {    // <--- NOTE HERE!!!
      if (needle[k] == needle[i - 1]) {
        f[i] = k + 1;
        break;
      }
    }
  }
  return f;
}
```

And the use of the failure function to implement `strstr()` is demonstrated as below.

```c++
int strStr(std::string haystack, std::string needle) {
  std::vector<int> f = buildFailureFunc(needle);
  std::size_t i = 0, j = 0;
  while (i < haystack.size() && j < needle.size()) {
    if (haystack[i] == needle[j]) {
      ++i, ++j;
    } else if (j) {                  < ---- SAME HERE!
      j = f[j];
    } else {
      ++i;
    }
  }
  if (j == needle.size()) {
    return i - j;
  }
  return -1;
}
```

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
