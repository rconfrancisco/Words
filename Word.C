//Sample program to print out 10 most popular words in a file.  
//Reading from stdin.
#include <iostream>
#include <istream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unistd.h>

constexpr int      default_words=10;
static int         maxWords=default_words;
static std::string filename;

void usage(char* prog) {

  std::cout << prog 
	    << "[options]\n"
	    << "-f filename - required\n" 
	    << "-n words - default " << default_words << "\n"
	    << "-h help this menu\n";

  exit(0);
}

void menu(int argc, char* argv[]) {

  int ch=0;
  while ((ch = getopt(argc, argv, "n:f:?Hh")) != -1) {
    switch (ch) {
    case 'n':
      maxWords = atoi(optarg);
      if(maxWords <=0) maxWords = default_words;
      break;
      
    case 'f':
      filename.assign(optarg);
      break;

    case '?':
    case 'h':
    case 'H':
    default:
      usage(argv[0]);
      break;
    }
  }
  if(filename.length() == 0) {
    usage(argv[0]);
  }
  return;
}

struct Node_t {
  int count;
  std::string word;
  bool operator<(const Node_t& rhs) const {
    if(this->count > rhs.count) return true;
    return false;
  }
  Node_t () : count(0) {};
  explicit Node_t (const std::string& in_word) : count(0), word(in_word) {}
  Node_t (const int cnt, const std::string& in_word) : count(cnt), word(in_word) {}
};

typedef std::pair<std::string, int> NodePair_t;

typedef std::unordered_map<std::string, int> Map_t;
typedef Map_t::iterator                      MapItr_t;
typedef std::vector<Node_t>                  NodeHeap_t;

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

class MinHeap_t {
  
private:
  size_t m_topWords;

public:

  NodeHeap_t m_heap;

  void setTopWords(const size_t num) {
    m_topWords = num;
    return;
  }

  MinHeap_t(const size_t num=5) : m_topWords(num){};

  void operator() (const NodePair_t& pair) {
    Node_t node(pair.second, pair.first);
    m_heap.push_back(node);
    std::push_heap(m_heap.begin(),  m_heap.end());
    if(m_heap.size() > m_topWords) {
      std::pop_heap(m_heap.begin(), m_heap.end());
      m_heap.pop_back();
    }
    return;
  }

  void print_heap() {
    int len=m_heap.size();
    for(int i=len-1; i >=0; --i) {
      std::cout << m_heap[i].word  << " - " 
		<< m_heap[i].count << std::endl;
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
  
  menu(argc, argv);

  Map_t       myMap;
  std::string word;

  std::ifstream ifs;
  ifs.open(filename);

  while (ifs >> word) {
    countWord(myMap, normalizeWord(word));
  }

  MinHeap_t myMinHeap(maxWords);
  std::for_each(myMap.begin(), myMap.end(), [&] (const NodePair_t& pair) { 
      myMinHeap.operator()(pair);
    } );
  myMinHeap.print_heap();
  return 0;
}
