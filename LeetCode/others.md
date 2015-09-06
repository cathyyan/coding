## 263. Ugly Numbers
```cpp
class Solution {
public:
    long long largestDivisor(long long num) {
        long long d = sqrt(num);
        while (d > 1) {
            if (num % d == 0) break;
            --d;
        }
        return d;
    }
    
    bool isUgly(long long num) {
        if (!num) return false;
        long long my_num = abs(num);
        long long d = largestDivisor(my_num);
        if (d == 1) return num == 1 || num == 2 || num == 3 || num == 5;
        return isUgly(d) && isUgly(num / d);
    }
};
```

## 258. Add Digits
```cpp
class Solution {
public:
    int addDigits(int num) {
        while (num >= 10) {
            int tmp = 0;
            while (num) {
                tmp += num % 10;
                num /= 10;
            }
            num = tmp;
        }
        return num;
    }
};
```
## 257. Binary Tree Paths
## 256. Paint House  
## 255. Verify Preorder Sequence in Binary Search Tree 
## 254. Factor Combinations  
## 253. Meeting Rooms II 
## 252. Meeting Rooms  
## 251. Flatten 2D Vector  
## 250. Count Univalue Subtrees  
## 249. Group Shifted Strings  
## 248. Strobogrammatic Number III 
## 247. Strobogrammatic Number II  
## 246. Strobogrammatic Number 
## 245. Shortest Word Distance III 
## 244. Shortest Word Distance II  
## 243. Shortest Word Distance 
## 242. Valid Anagram
```cpp
class Solution {
public:
    map<char, int> Freq(const string& s) {
        map<char, int> f;
        for (auto ch : s) { ++f[ch]; }
        return f;
    }
    
    bool isAnagram(string s, string t) {
        return s.length() == t.length() && Freq(s) == Freq(t);
    }
};
```
## 241. Different Ways to Add Parentheses
## 240. Search a 2D Matrix II
## 239. Sliding Window Maximum 
## 238. Product of Array Except Self 
## 237. Delete Node in a Linked List 
```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        // It's not the tail. so...
        int val = node->next->val;
        node->next = node->next->next;
        node->val = val;
    }
};
```
## 236. Lowest Common Ancestor of a Binary Tree
## 235. Lowest Common Ancestor of a Binary Search Tree 
## 234. Palindrome Linked List 
## 233. Number of Digit One
## 232. Implement Queue using Stacks 
## 231. Power of Two 
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n <= 0 ? false : 0 == (n & n - 1);
    }
};
```
## 230. Kth Smallest Element in a BST
## 229. Majority Element II
## 228. Summary Ranges 
```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;
        int s = 0;
        for (size_t i = 1; i <= nums.size(); ++i) {
            if (i == nums.size() || nums[i] != nums[i - 1] + 1) {
                ret.emplace_back(
                    s == i - 1 ? std::to_string(nums[s]) :
                                 std::to_string(nums[s]) + "->" + std::to_string(nums[i - 1]));
                s = i;
            }
        }
        return ret;
    }
};
```
## 227. Basic Calculator II
## 226. Invert Binary Tree 
## 225. Implement Stack using Queues 
## 224. Basic Calculator 
## 223. Rectangle Area 
## 222. Count Complete Tree Nodes
## 221. Maximal Square 
## 220. Contains Duplicate III 
## 219. Contains Duplicate II
```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, size_t> m;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (m.count(nums[i]) && i - m[nums[i]] <= k) {
                return true;
            }
            m[nums[i]] = i;
        }
        return false;
    }
};
```
## 218. The Skyline Problem
## 217. Contains Duplicate 
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s;
        for (const auto num : nums) {
            if (!s.insert(num).second) return true;
        }
        return false;
    }
};
```

## 216. Combination Sum III
## 215. Kth Largest Element in an Array
## 214. Shortest Palindrome
## 213. House Robber II
## 212. Word Search II 
## 211. Add and Search Word - Data structure design
Use Trie.

```cpp
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() : exists_(false) {
        for(int i = 0; i < 26; ++i) next_[i] = nullptr;
    }

    bool exists_;
    TrieNode* next_[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode* n = root;
        for (char ch : word) {
            if (n->next_[ch - 'a'] == nullptr) {
                n->next_[ch - 'a'] = new TrieNode();
            }
            n = n->next_[ch - 'a'];
        }
        n->exists_ = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(TrieNode* n, const string& word, int pos) {
        if (pos >= word.length()) {
            return n->exists_;
        }
        if (word[pos] == '.') {
            for (int i = 0; i < 26; ++i) {
                if (n->next_[i] && search(n->next_[i], word, pos + 1)) {
                    return true;
                }
            }
            return false;
        }
        return n->next_[word[pos] - 'a'] && search(n->next_[word[pos] - 'a'], word, pos + 1);
    }
    
    bool search(string word) {
        return search(root, word, 0);
    }
    
private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

class WordDictionary {
public:

    // Adds a word into the data structure.
    void addWord(string word) {
        t_.insert(word);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return t_.search(word);
    }
    
private:
    Trie t_;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
```
## 210. Course Schedule II 

Same as #207.

```cpp
class Solution {
public:
    using Graph = unordered_map<int, unordered_set<int>>;

    pair<Graph, vector<int>> BuildGraph(int numCourses, const vector<pair<int, int>>& prerequisitesconst) {
        Graph g;
        vector<int> in_degrees(numCourses, 0);
        for (int i = 0; i < numCourses; ++i) {
            g[i] = {};
        }
        for (const auto& pv : prerequisitesconst) {
            if (g[pv.second].insert(pv.first).second) {
                ++in_degrees[pv.first];
            }
        }
        return {g, in_degrees};
    }

    int FindFirstWithoutIncomingEdges(const vector<int>& degrees) {
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 0) return i;
        }
        return -1;
    }

    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> order;
        
        auto gv = BuildGraph(numCourses, prerequisites);
        Graph& g = gv.first;
        vector<int>& in_degrees = gv.second;
        int next = -1;
        while ((next = FindFirstWithoutIncomingEdges(in_degrees)) >= 0) {
            order.emplace_back(next);
            for (const auto& tmp : g[next]) { --in_degrees[tmp]; }
            in_degrees[next] = -1;
        }
        return *std::max_element(in_degrees.begin(), in_degrees.end()) < 0 ? order : vector<int>();
    }
};
```
## 209. Minimum Size Subarray Sum
```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty()) return 0;
        int left = 0, right = 0, sum = nums.front(), ans = 0;
        while (right < nums.size()) {
            if (sum >= s) {
                if (!ans || ans > right - left + 1) {
                    ans = right - left + 1;
                }
                sum -= nums[left];
                ++left;
            } else {
                ++right;
                sum += nums[right];
            }
        }
        return ans;
    }
};
```

## 208. Implement Trie (Prefix Tree) 
```cpp
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() : exists_(false) {
        for(int i = 0; i < 26; ++i) next_[i] = nullptr;
    }

    bool exists_;
    TrieNode* next_[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode* n = root;
        for (char ch : word) {
            if (n->next_[ch - 'a'] == nullptr) {
                n->next_[ch - 'a'] = new TrieNode();
            }
            n = n->next_[ch - 'a'];
        }
        n->exists_ = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode* n = root;
        for (char ch : word) {
            if (n->next_[ch - 'a'] == nullptr) {
                return false;
            }
            n = n->next_[ch - 'a'];
        }
        return n->exists_;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode* n = root;
        for (char ch : prefix) {
            if (n->next_[ch - 'a'] == nullptr) {
                return false;
            }
            n = n->next_[ch - 'a'];
        }
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
```
## 207. Course Schedule

Check whether a graph is a DAG ([Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting)).

```cpp
class Solution {
public:
    using Graph = unordered_map<int, unordered_set<int>>;
    
    pair<Graph, vector<int>> BuildGraph(int numCourses, const vector<pair<int, int>>& prerequisitesconst) {
        Graph g;
        vector<int> in_degrees(numCourses, 0);
        for (int i = 0; i < numCourses; ++i) {
            g[i] = {};
        }
        for (const auto& pv : prerequisitesconst) {
            if (g[pv.first].insert(pv.second).second) {
                ++in_degrees[pv.second];
            }
        }
        return {g, in_degrees};
    }
    
    int FindFirstWithoutIncomingEdges(const vector<int>& degrees) {
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 0) return i;
        }
        return -1;
    }
    
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        auto gv = BuildGraph(numCourses, prerequisites);
        Graph& g = gv.first;
        vector<int>& in_degrees = gv.second;
        int next = -1;
        while ((next = FindFirstWithoutIncomingEdges(in_degrees)) >= 0) {
            for (const auto& tmp : g[next]) { --in_degrees[tmp]; }
            in_degrees[next] = -1;
        }
        return *std::max_element(in_degrees.begin(), in_degrees.end()) < 0;
    }
};
```
## 206. Reverse Linked List
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = nullptr;
        while (head) {
            ListNode* tmp = head->next;
            head->next = new_head;
            new_head = head;
            head = tmp;
        }
        return new_head;
    }
};
```
## 205. Isomorphic Strings 
## 204. Count Primes 
```cpp
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> is_prime(n, true);
        is_prime[1] = is_prime[0] = false;
        int k = 2;
        while (k < n) {
            if (is_prime[k]) {
                for (int x = 2; x * k < n; ++x)
                    is_prime[x * k] = false;
            }
            ++k;
        }
        
        int count = 0;
        for (auto x : is_prime) { count += x; }
        return count;
    }
};
```
## 203. Remove Linked List Elements
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;
        for (ListNode* p = &dummy; p;) {
            if (p->next && p->next->val == val) {
                ListNode* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            } else {
                p = p->next;
            }
        }
        return dummy.next;
    }
};
```
## 202. Happy Number 
```cpp
class Solution {
public:
    int toNext(int n) {
        int sum = 0;
        while (n) {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        return sum;
    }
    
    bool isHappy(int n) {
        unordered_set<int> seen;
        int next = n;
        while (true) {
            if (next == 1) return true;
            if (seen.count(next)) return false;
            seen.insert(next);
            next = toNext(next);
        }
        return false;
    }
};
```
## 201. Bitwise AND of Numbers Range 

Calculate whether each bit should be set. See inline comments.

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        unsigned ret = 0;
        for (unsigned k = 0; k <= 31; ++k) {
            unsigned two_k = 1 << k;
            // Check whether bit #k should be set.
            // It should be set if and only if [m, n] falls entirely into
            // [p * 2 ^ k, (p + 1) * 2 ^ k) for some positive odd p.
            bool to_set = false;
            for (unsigned p = m / two_k; ; ++p) {
                unsigned lower = p * two_k, upper = (p + 1) * two_k;
                if (lower > n) break;
                if (m < upper && n >= upper) break;
                if (lower <= m && upper > n && p % 2) {
                    to_set = true;
                    break;
                }
            }
            if (to_set) { ret = ret | two_k; }
        }
        return static_cast<int>(ret);
    }
};
```

## 200. Number of Islands

BFS/DFS.

```cpp
class Solution {
public:
  using Grid = vector<vector<char>>;
  
  int numIslands(Grid& grid) {
    if (grid.empty()) return 0;
    const int R = grid.size(), C = grid.front().size();
    int ret = 0;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        ret += Label(grid, i, j);
      }
    }
    return ret;
  }
  
private:
  // Lable the island containing (x, y).
  int Label(Grid& grid, int x, int y) {
    if (grid[x][y] == '0') return 0;
    
    const int R = grid.size(), C = grid.front().size();
    const int DIRECTIONS[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    // Run BFS starting from (x, y)
    queue<pair<int, int>> q;
    q.push({x, y});
    grid[x][y] = '0';
    while (!q.empty()) {
      pair<int, int> tmp = q.front(); q.pop();
      for (int d = 0; d < 4; ++d) {
        int xx = tmp.first + DIRECTIONS[d][0], yy = tmp.second + DIRECTIONS[d][1];
        if (xx >= 0 && xx < R && yy >= 0 && yy < C && grid[xx][yy] == '1') {
          grid[xx][yy] = '0';
          q.push({xx, yy});
        }
      }
    }
    
    return 1;
  }
};
```
## 199. Binary Tree Right Side View
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        vector<TreeNode*> cur_level = {root};
        while (!cur_level.empty()) {
            result.emplace_back(cur_level.back()->val);
            vector<TreeNode*> next_level;
            for (TreeNode* n : cur_level) {
                if (n->left) next_level.emplace_back(n->left);
                if (n->right) next_level.emplace_back(n->right);
            }
            cur_level = next_level;
        }
        return result;
    }
};
```
## 198. House Robber 
DP.
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<vector<int>> profit(2, vector<int>(nums.size(), 0));
        profit[0][0] = 0;
        profit[1][0] = nums[0];
        for (size_t p = 1; p < nums.size(); ++p) {
            profit[0][p] = std::max(profit[0][p - 1], profit[1][p - 1]);
            profit[1][p] = profit[0][p - 1] + nums[p];
        }
        return std::max(profit[0].back(), profit[1].back());
    }
};
```
## 191. Number of 1 Bits 

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t a = 0xAAAAAAAA;
        uint32_t b = 0xCCCCCCCC;
        uint32_t c = 0xF0F0F0F0;
        uint32_t d = 0xFF00FF00;
        uint32_t e = 0xFFFF0000;
      
        uint32_t t = ((n & a) >> 1) + (n & ~a);
        t = ((t & b) >> 2) + (t & ~b);
        t = ((t & c) >> 4) + (t & ~c);
        t = ((t & d) >> 8) + (t & ~d);
        t = ((t & e) >> 16) + (t & ~e);
        return t;
    }
};
```
## 190. Reverse Bits 

```cpp
    uint32_t reverseBits(uint32_t n) {
        bitset<32> bs(n);
        for (int i = 0, j = 31; i < j; ++i, --j) {
            bool tmp = bs[i];
            bs[i] = bs[j];
            bs[j] = tmp;
        }
        return bs.to_ulong();
    }
```
    
## 189. Rotate Array 

1. O(k * n), TLE
```cpp
    void rotate(vector<int>& nums, int k) {
        if (nums.empty()) return;
        
        while (k--) {
            int tmp = nums.back();
            for (size_t i = 0; i + 1 < nums.size(); ++i) {
                nums[i + 1] = nums[i];
            }
            nums.front() = tmp;
        }
    }
```
2. O(n) + GCD running time, 48ms
```cpp
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    void rotate(vector<int>& nums, int k) {
        int d = gcd(nums.size(), k);
        int n = nums.size() / d;
        for (int i = 0; i < d; ++i) {
            int a = nums[i], index = i;
            for (int j = 0; j < n; ++j) {
                index = (index + k) % nums.size();
                std::swap(a, nums[index]);
            }
        }
    }
```
3. O(n), 24ms
```cpp
    void rotate(vector<int>& nums, int k) {
        int count = k % nums.size();
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + count);
        std::reverse(nums.begin() + count, nums.end());
    }
```

## 188. Best Time to Buy and Sell Stock IV 

At first I used the dictionary approach to implement the DP. However I got
TLE. Guessing it was due to too much time spent on converting integers to
strings to compose hash keys.

```cpp
class Solution {
public:
  int maxProfit(int k, vector<int>& prices) {
    return 2 * k >= prices.size() ? MP(prices) : MP(k, prices);
  }
  
private:
  // Version 1: if we have sufficient budget for transactions, we
  // can transact as many as we want.
  int MP(const vector<int>& prices) {
    int ret = 0;
    for (size_t p = 1; p < prices.size(); ++p) {
      if (prices[p] > prices[p - 1]) {
        ret += prices[p] - prices[p - 1];
      }
    }
    return ret;
  }
  
  // Version 1: we have limited budget.
  int MP(int k, const vector<int> prices) {
    vector<vector<vector<int>>> profit(
      prices.size() + 1,
      vector<vector<int>>(2, vector<int>(k + 1, numeric_limits<int>::min())));
    
    for (int i = 0; i <= k; ++i) { profit[0][0][i] = 0; }
    for (int d = 1; d < prices.size() + 1; ++d) {
      for (int i = 0; i <= k; ++i) {
        profit[d][0][i] = std::max(profit[d - 1][0][i],
                                   profit[d - 1][1][i] + prices[d - 1]);
      }
      for (int i = 0; i <= k; ++i) {
        profit[d][1][i] = std::max(
          profit[d - 1][1][i],
          i > 0 ? profit[d - 1][0][i - 1] - prices[d - 1] : numeric_limits<int>::min());
      }
    }
    
    return profit[prices.size()][0][k];
  }
};
```

## 187. Repeated DNA Sequences 

Representing a string as an integer to reduce memory footprint is the key to avoid 'Memory Limit Exceeded' errors.

```cpp
class Solution {
public:
    int ToInt(char ch) {
        switch (ch) {
            case 'A': return 1;
            case 'C': return 2;
            case 'G': return 3;
            case 'T': return 4;
            default: return -1;
        }
    }
    
    char ToChar(int n) {
        switch (n) {
            case 1: return 'A';
            case 2: return 'C';
            case 3: return 'G';
            case 4: return 'T';
            default: return ' ';
        }
    }
    
    int ToInt(const string& s) {
        int ret = 0;
        for (size_t p = 0; p < s.length(); ++p) {
            ret = ret * 5 + ToInt(s[p]);
        }
        return ret;
    }
    
    string ToStr(int n) {
        string s;
        while (n) {
            s.append(1, ToChar(n % 5));
            n /= 5;
        }
        std::reverse(s.begin(), s.end());
        return s;
    }
    
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, int> freq;
        for (size_t p = 0; p + 10 <= s.length(); ++p) {
            string tmp = s.substr(p, 10);
            ++freq[ToInt(tmp)];
        }
        vector<string> results;
        for (const auto pv : freq) {
            if (pv.second > 1) {
                results.emplace_back(ToStr(pv.first));
            }
        }
        return results;
    }
};
```
## 186. Reverse Words in a String II 
## 179. Largest Number 

A number `a` has to go before `b` if and only if `string(ab) > string(ba)`.

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> ns(nums.size());
        transform(nums.begin(), nums.end(), ns.begin(), [](int n) {
            return to_string(n);
        });
        sort(ns.begin(), ns.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });
        return accumulate(ns.begin(), ns.end(), string{},
            [](const string& a, const string& b) {
                if (a == "0" && b == "0") return a;
                return a + b;
            });
    }
};
```
## 174. Dungeon Game

When sometimes you cannot go forward, think about going backward.

```cpp
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        const int R = dungeon.size(), C = dungeon.front().size();
        // Minimum health needed before entering (i,j).
        vector<vector<int>> mh(R + 1, vector<int>(C + 1, numeric_limits<int>::max()));
        mh[R][C - 1] = mh[R - 1][C] = 1;
        for (int i = R - 1; i >= 0; --i) {
          for (int j = C - 1; j >= 0; --j) {
            int tmp = std::min(mh[i + 1][j], mh[i][j + 1]);
            mh[i][j] = std::max(tmp - dungeon[i][j], 1);
          }
        }
        return mh[0][0];
    }
};
```

## 173. Binary Search Tree Iterator

```cpp
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) : next_(nullptr) {
        if (root) s_.push(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        next_ = nullptr;
        while (!s_.empty()) {
            TreeNode* tmp = s_.top();
            if (tmp->left) {
                s_.push(tmp->left);
                tmp->left = nullptr;
            } else {
                s_.pop();
                next_ = tmp;
                if (tmp->right) s_.push(tmp->right);
                break;
            }
        }
        return next_ != nullptr;
    }

    /** @return the next smallest number */
    int next() {
        return next_->val;
    }
    
private:
    stack<TreeNode*> s_;
    TreeNode* next_;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
```

## 172. Factorial Trailing Zeroes

```cpp
class Solution {
public:
    int trailingZeroes(int n) {
        return countFives(n);
    }
    
    int countFives(int n) {
        int count = 0;
        long long k = 5;  // n = 2147483647
        while (n >= k) {
            count += n / k;
            k *= 5;
        }
        return count;
    }
};
```
## 171. Excel Sheet Column Number

```cpp
class Solution {
public:
    int titleToNumber(string s) {
        int r = 0;
        for (const char c : s) {
            r = r * 26 + c - 'A' + 1;
        }
        return r;
    }
};
```

## 170. Two Sum III - Data structure design  
