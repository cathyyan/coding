# Notes on LeetCode problems

## Binary search - extended

Find a target. Return its first/last occurrence if it exists; otherwise return the first/last position where it would be if it was in the number vector.

Notes:
*   Always return `start` when `start > end` is true.
*   For the first position, go to the first half when `target <= nums[mid]`; while for the last position, always go to the second half when `target >= nums[mid]`.

```cpp
// Find the first occurrence of 'target' if it exists. Otherwise return
// the leftmost position where to put it in the vector if we would insert it.
int firstAt(const std::vector<int>& nums, int start, int end, int target) {
  if (start > end) { return start; }    // <<----- Always return `start`.
  
  int mid = (start + end) / 2;
  if (target <= nums[mid]) {            // <<------ for the first position
    return firstAt(nums, start, mid - 1, target);
  }
  return firstAt(nums, mid + 1, end, target);
}

// Find the last occurrence of 'target' if it exists. Otherwise return
// the rightmost position where to put it in the vector if we would insert it.
int lastAt(const std::vector<int>& nums, int start, int end, int target) {
  if (start > end) { return start; }    // <<----- Always return `start`. SAME HERE.
  
  int mid = (start + end) / 2;
  if (target >= nums[mid]) {            // <<------ for the first position
    return lastAt(nums, mid + 1, end, target);
  }
  return lastAt(nums, start, mid - 1, target);
}

std::vector<int> searchRange(const std::vector<int>& nums, int target) {
  int size = nums.size();
  int first = firstAt(nums, 0, size - 1, target);
  int last = lastAt(nums, 0, size - 1, target);
  if (first < size && nums[first] == target) {
    return {first, last - 1};
  }
  return {-1, -1};
}
```

## Reverse iterators (such as `rbegin()`, `rend()`)

Their `base()` returns the next element (in normal order) to the one it is logically pointing to. That is, `v.rbegin().base()` is `v.end()` and `v.rend().base()` is `v.begin()`. See the following diagram (from cppreference.com) for details.

![Reverse iterators](http://upload.cppreference.com/mwiki/images/3/39/range-rbegin-rend.svg)

I used reverse iterators to solve Permunation. See code below:

```c++
  void nextPermutation(std::vector<int>& nums) {
    auto it = std::adjacent_find(nums.rbegin(), nums.rend(), std::greater<int>());
    // 'it' points to the first ont, going backward, that is greater than its next. 
    if (it == nums.rend()) { // in descending order. Simply reverse.
      std::reverse(nums.begin(), nums.end());
    } else {
      // 'other' points to the first element after 'it' that is greater than *(it+1)
      // (going backwards). Such an element always exits.
      auto other = std::find_if(
        nums.rbegin(), it + 1,
        std::bind(std::greater<int>(), std::placeholders::_1, *(it + 1)));
      std::iter_swap(it + 1, other);
      std::sort(it.base() - 1, nums.end());   // <-- 'it.base() - 1' is 'it' !!
    }
  }
```

(I know that c++ provides [`std::next_permutation()`][cpp_1].)

[cpp_1]: http://en.cppreference.com/w/cpp/algorithm/next_permutation

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

## Two Sum

Very sweet approach I saw for the first time. Sounds similar to binary search. See the comments for details.

```c++
// Two-pointer solution for Two Sum.
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
  std::vector<int> result;
  
  // 1. sort the given numbers in ascending order.
  std::vector<int> indices(nums.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(), [&nums](int a, int b) {
    return nums[a] < nums[b];
  });
  
  // 2. two pointers: b(egin) and e(nd). Every time we sum up
  // the two numbers pointed by them and compare the result
  // with 'target'.
  int b = 0, e = static_cast<int>(indices.size()) - 1;
  while (b < e) {
    int sum = nums[indices[b]] + nums[indices[e]];
    // Three cases may happen.
    if (sum < target) {
      // In this case, the sum of any pair starting with 'b' is
      // less than target. Drop them.
      ++b;
    } else if (sum > target) {
      // In this case, the sum of any pair ending with 'e' is
      // less than target. Drop them.
      --e;
    } else {
      // Save the result we just found.
      result.push_back(std::min(indices[b], indices[e]) + 1);
      result.push_back(std::max(indices[b], indices[e]) + 1);
      // The equal case. Similarly, drop all either starting
      // with 'b' OR ending with 'e'.
      // ++b; --e;
      //
      // Since there is at most one solution. Simply return here.
      break;
    }
  }
  return result;
}
```
