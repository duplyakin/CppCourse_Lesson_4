#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include "logger.h"

template <class T> struct Hasher {
  size_t operator()(const T& obj) const;   

};
template <> struct Hasher<std::string> {
  size_t operator()(const std::string& str) const {
    // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
    int prime = 31;
    size_t hash = 0;
    int power = str.length() - 1;

    for (auto it = str.begin(); it != str.end(); ++it, --power) {
      hash += static_cast<size_t>(*it) * std::pow(prime, power);
    }
    return hash;
 }
};

template <> struct Hasher<int> {
  size_t operator()(const int& value ) const {
    return value;
 }
};



struct Node {//следует сложить р
  int key;
  std::string value;

  Node(int key, const std::string& value);
  bool operator == (const Node& rhs) const;
};

Node::Node(int key, const std::string& value)
  : key(key)
  , value(value) {
}

bool Node::operator == (const Node& rhs) const {
  if (key == rhs.key) 
    return true;
  else
    return false;
}

std::ostream& operator << (std::ostream& out, const Node& node) {
  out << "{" << node.key << ", " << node.value << "}";
}

template <typename T>
void print(T array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

template <> struct Hasher<Node> {
  size_t operator()(const Node& node ) const {
    size_t hash = 0;
    struct Hasher<std::string> x;
    struct Hasher<int> y;
    hash = x(node.value) + y(node.key);
    return hash;
 }
};


int main(int argc, char** argv) {
  DBG("[Lesson 4]: Hashing home 1");

  std::unordered_set<std::string, Hasher<std::string>> hash_set_string = {"zero", "first", "two" ,"three", "four", "five"};
  std::unordered_set<int, Hasher<int>> hash_set_int = {1, 5, 15, 13, 6456, -100000, 0, 19};


  Node node_array[10] = {
  Node(5, "five"), Node(8, "eight"),
  Node(1, "one"), Node(12, "twelve"), Node(-4, "-four"), Node(-7, "-seven"),
  Node(3, "three"), Node(5, "five"), Node(9, "nine"), Node(0, "zero")};
  
  DBG("Sorting <Node>");
  std::unordered_set<Node, Hasher<Node>> hash_set_node = {node_array[0], node_array[1], node_array[2], node_array[3], node_array[4], node_array[5]};


  std::cout << "SET:" << std::endl;
  INF("Hash of string variables");  
  std::copy(hash_set_string.begin(), hash_set_string.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;
  INF("Hash of int variables"); 
  std::copy(hash_set_int.begin(), hash_set_int.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  INF("Hash of Node variables"); 
  std::copy(hash_set_node.begin(), hash_set_node.end(), std::ostream_iterator<Node>(std::cout, " "));
  std::cout << std::endl;

  DBG("[Lesson 4]: Hashing home 1 [END]");
  return 0;
}
