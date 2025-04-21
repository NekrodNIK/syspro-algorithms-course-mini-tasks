#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

class FreqStack {  
  std::unordered_map<int, int> freq;
  std::unordered_map<int, std::stack<int>> stacks;
  int max_freq;
  
public:
  void push(int val) {
    freq[val]++;
    stacks[freq[val]].push(val);

    if (freq[val] > max_freq) {
      max_freq = freq[val];
    }
  }

  int pop() {
    auto top = stacks[max_freq].top();
    stacks[max_freq].pop();
    freq[top]--;
    if (stacks[max_freq].empty()) {
      max_freq--;
    }

    return top;
  }
};
