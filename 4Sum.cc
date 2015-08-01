class Solution {
public:
  // Type for a list of pairs
  using PairList = std::vector<std::pair<int, int>>;
  
  void addIfNotAddedYet(std::vector<std::vector<int>>& results,
                        std::unordered_set<std::string>& added,
                        const std::vector<int>& nums,
                        const std::pair<int, int>& p1,
                        const std::pair<int, int>& p2) {
    std::vector<int> indices = {p1.first, p1.second, p2.first, p2.second};
    std::sort(indices.begin(), indices.end(), [&](int a, int b){
      return nums[a] < nums[b];
    });
    
    string key;
    std::vector<int> ans;
    std::for_each(indices.begin(), indices.end(), [&](int index) {
      key.append(" " + std::to_string(nums[index]));
      ans.emplace_back(nums[index]);
    });
    
    if (added.find(key) == added.end()) {
      added.insert(key);
      results.emplace_back(std::move(ans));
    }
  }
  
  std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    if (nums.size() < 4) { return {}; }
      
    // sum -> [list of (i, j) pairs summing up to the sum]
    std::map<int, PairList> arr;
    for (size_t i = 0; i + 1 < nums.size(); ++i) {
      for (size_t j = i + 1; j < nums.size(); ++j) {
        arr[nums[i] + nums[j]].emplace_back(i, j);
      }
    }
    
    // Run two sum
    std::vector<std::vector<int>> results;
    std::unordered_set<std::string> added;
    auto s_it = arr.begin(), e_it = std::prev(arr.end());
    while (s_it != arr.end() && s_it->first <= e_it->first) {
      int sum = s_it->first + e_it->first;
      if (sum == target) {
        for (const auto& p1 : s_it->second) {
          for (const auto& p2 : e_it->second) {
            if (p1.second < p2.first || p2.second < p1.first) {
              addIfNotAddedYet(results, added, nums, p1, p2);
            }
          }
        } 
      }
      if (sum >= target) {
        if (e_it == arr.begin()) { break; }
        --e_it;
      }
      if (sum <= target) {
        ++s_it;
      }
    }  // end of while()
    
    return results;
  }
  
};
