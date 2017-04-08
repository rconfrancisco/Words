//Sample program to print out 10 most popular words in a file.  
//Reading from stdin.
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctype.h>

struct Node_t {
  int count;
  std::string word;
  bool operator<(const Node_t& rhs) const {
    if(this->count < rhs.count) return true;
    return false;
  }
  Node_t (const Node_t& rhs): count(rhs.count), word(rhs.word) {}
  explicit Node_t (const std::string& in_word) : count(0), word(in_word) {}
  Node_t (const int cnt, const std::string& in_word) 
    : count(cnt), word(in_word) {}

  Node_t& operator=(const Node_t& rhs) {
    if(this != &rhs) {
      this->count = rhs.count;
      this->word  = rhs.word;
    }
    return *this;
  }

};

typedef std::pair<std::string, int> NodePair_t;

typedef std::unordered_map<std::string, int> Map_t;
typedef Map_t::iterator                      MapItr_t;
typedef std::priority_queue<Node_t, std::vector<Node_t> > PriorityQueue_t;

void countWord(Map_t& myMap, const std::string& word) {
  MapItr_t itr = myMap.find(word);
  if(itr == myMap.end()) {
    myMap[word]=1;
  }
  else {
    ++itr->second;
  }
  return;
}

class MaxHeap_t {
  
private:

public:

  PriorityQueue_t m_heap;

  MaxHeap_t(){};
  void operator() (const NodePair_t& pair) {
    Node_t node(pair.second, pair.first);
    m_heap.push(node);
    return;
  }

  void print_heap(const int max_count) {

    int count = 0;
    while((!m_heap.empty()) && (count < max_count)) {
      std::cout << m_heap.top().word  << " - " 
		<< m_heap.top().count << std::endl;
      m_heap.pop();
      ++count;
    }
    return;
  }
  
};

std::string& normalizeWord(std::string& word) {
  for(size_t i=0; i < word.length(); ++i) {
    word[0]=tolower(word[0]);
  }
  return word;
}

int main(int argc, char* argv[]) {
  
  int maxCount=0;
  if(argc > 1) maxCount = atoi(argv[1]);
  if(maxCount < 1) maxCount=10;

  Map_t       myMap;
  std::string word;
  while (std::cin >> word) {
    countWord(myMap, normalizeWord(word));
  }

  MaxHeap_t myMaxHeap;
  myMaxHeap = std::for_each(myMap.begin(), myMap.end(), myMaxHeap);
  myMaxHeap.print_heap(maxCount);
  return 0;
}
