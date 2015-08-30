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
## 241. Different Ways to Add Parentheses
## 240. Search a 2D Matrix II
## 239. Sliding Window Maximum 
## 238. Product of Array Except Self 
## 237. Delete Node in a Linked List 
## 236. Lowest Common Ancestor of a Binary Tree
## 235. Lowest Common Ancestor of a Binary Search Tree 
## 234. Palindrome Linked List 
## 233. Number of Digit One
## 232. Implement Queue using Stacks 
## 231. Power of Two 
## 230. Kth Smallest Element in a BST
## 229. Majority Element II
## 228. Summary Ranges 
## 227. Basic Calculator II
## 226. Invert Binary Tree 
## 225. Implement Stack using Queues 
## 224. Basic Calculator 
## 223. Rectangle Area 
## 222. Count Complete Tree Nodes
## 221. Maximal Square 
## 220. Contains Duplicate III 
## 219. Contains Duplicate II
## 218. The Skyline Problem
## 217. Contains Duplicate 
## 216. Combination Sum III
## 215. Kth Largest Element in an Array
## 214. Shortest Palindrome
## 213. House Robber II
## 212. Word Search II 
## 211. Add and Search Word - Data structure design
## 210. Course Schedule II 
## 209. Minimum Size Subarray Sum
## 208. Implement Trie (Prefix Tree) 
## 207. Course Schedule
## 206. Reverse Linked List
## 205. Isomorphic Strings 
## 204. Count Primes 
## 203. Remove Linked List Elements
## 202. Happy Number 
## 201. Bitwise AND of Numbers Range 
## 200. Number of Islands
## 199. Binary Tree Right Side View
## 198. House Robber 
## 191. Number of 1 Bits 
## 190. Reverse Bits 
## 189. Rotate Array 
## 188. Best Time to Buy and Sell Stock IV 
## 187. Repeated DNA Sequences 
## 186. Reverse Words in a String II 
## 179. Largest Number 
## 174. Dungeon Game 
## 173. Binary Search Tree Iterator
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
