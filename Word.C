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
};

typedef std::pair<std::string, int> NodePair_t;

typedef std::vector<std::string> Vector_t;
typedef std::unordered_map<std::string, int> Map_t;
typedef Map_t::iterator                      MapItr_t;
typedef std::priority_queue<Node_t, std::vector<Node_t> > PriorityQueue_t;

static PriorityQueue_t myMaxHeap;

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

void makeHeap(const NodePair_t& pair) {
  Node_t node;
  node.word  = pair.first;
  node.count = pair.second;
  myMaxHeap.push(node);
  return;
}

void printHeap(PriorityQueue_t& max_heap, const int max_count) {

  int count=0;
  while(!myMaxHeap.empty() && (count < max_count)) {
    std::cout << myMaxHeap.top().word << " - " << myMaxHeap.top().count << std::endl;
    myMaxHeap.pop();
    ++count;
  }
  return;
}

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

  std::for_each(myMap.begin(), myMap.end(), makeHeap);
  printHeap(myMaxHeap, maxCount);
  return 0;
}
