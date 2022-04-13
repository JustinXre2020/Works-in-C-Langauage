#include "illini_book.hpp"

// Your code here!
IlliniBook::IlliniBook(const std::string& people_fpath, const std::string& relations_fpath) {
  std::ifstream ifs_people{people_fpath};
  std::vector<int> peoples;                                                       // a vector for all nodes
  int value = 0;
  while (ifs_people.good()) {
    ifs_people >> value;
    if (!ifs_people.fail()) {
      peoples.push_back(value);
    } else {
      ifs_people.clear();
      ifs_people.ignore(1, '\n');
    }
  }
  std::ifstream ifs_relation{relations_fpath};
  std::vector<std::vector<std::string>> ll;                                       // a vector for all relations
  for (std::string line; std::getline(ifs_relation, line); line = "") {
    std::vector<std::string> v = utilities::Split(line, ',');
    ll.push_back(v);
  }

  for (size_t i = 0; i < ll.size(); ++i) {
    int curr_node = std::stoi(ll[i][0]);
    int node_connect = std::stoi(ll[i][1]);
    if (graph_.count(curr_node) == 0) {                                           // if current node does not exist in graph
      graph_.insert({curr_node, std::list<std::pair<int, std::string>>()});       // initialize it
    }                                                                             // e.g. {1, {3, "128"}}   
    graph_.find(curr_node)->second.push_back({node_connect, ll[i][2]});           
    if (graph_.count(node_connect) == 0) {                                        // if connected node does not exist in graph
      graph_.insert({node_connect, std::list<std::pair<int, std::string>>()});    // initialize it
    }
    graph_.find(node_connect)->second.push_back({curr_node, ll[i][2]});           // add two times to make it symmetric
  }
  for (size_t j = 0; j < peoples.size(); ++j) {
    if (graph_.count(peoples[j]) == 0) {
      graph_.insert({peoples[j], std::list<std::pair<int, std::string>>()});
    }
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<std::pair<int, int>> q;      // create a queue to traverse the graph
  q.push({uin_1, 0});                     // add the start node to the queue
  std::map<int, bool> visited;            // create a map to store visited nodes
 
  for (const auto& t : graph_) {          // initialize the map
    visited.insert({t.first, false});
  }
 
  while (!q.empty()) {
    std::pair<int, int> np = q.front();   // get value from the queue
 
    if (np.first == uin_2) {              // if the value matches, return true (they are related)
      return true;
    }
    for (const auto& each_node : graph_.find(np.first)->second) {   // traverse the node's adjacency list
      if (!visited[each_node.first]) {    // if we haven't traversed the node, update its value in queue
        visited[each_node.first] = true;
        int x = q.front().second;
        x++;
        q.push({each_node.first, x});
      }
    }
    q.pop();                              // pop out the node
  }
  return false;
}


bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string& relationship) const {
  std::queue<std::pair<int, int>> q;      // create a queue to traverse the graph
  q.push({uin_1, 0});                     // add the start node to the queue
  std::map<int, bool> visited;            // create a map to store visited nodes
 
  for (const auto& t : graph_) {          // initialize the map
    visited.insert({t.first, false});
  }
 
  while (!q.empty()) {
    std::pair<int, int> np = q.front();   // get value from the queue
 
    if (np.first == uin_2) {              // if the value matches, return true (they are related)
      return true;
    }
    for (const auto& each_node : graph_.find(np.first)->second) {   // traverse the node's adjacency list
      if (!visited[each_node.first] && each_node.second == relationship) { // if we haven't traversed the node, 
        visited[each_node.first] = true;                                   // and its edge matches the passed-in relationship
        int x = q.front().second;                                          // update its value in queue
        x++;
        q.push({each_node.first, x});
      }
    }
    q.pop();                              // pop out the node
  }
  return false;
}


int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<std::pair<int, int>> q;      // create a queue to traverse the graph
  q.push({uin_1, 0});                     // add the start node to the queue
  std::map<int, bool> visited;            // create a map to store visited nodes
 
  for (const auto& t : graph_) {          // initialize the map
    visited.insert({t.first, false});
  }
 
  while (!q.empty()) {
    std::pair<int, int> np = q.front();   // get value from the queue
 
    if (np.first == uin_2) {              // if the value matches, return its value in queue (they are related)
      return q.front().second;
    }
    for (const auto& each_node : graph_.find(np.first)->second) {   // traverse the node's adjacency list
      if (!visited[each_node.first]) {    // if we haven't traversed the node, update its value in queue
        visited[each_node.first] = true;
        int x = q.front().second;
        x++;
        q.push({each_node.first, x});
      }
    }
    q.pop();                              // pop out the node
  }
  return -1;
}


int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string& relationship) const {
  std::queue<std::pair<int, int>> q;      // create a queue to traverse the graph
  q.push({uin_1, 0});                     // add the start node to the queue
  std::map<int, bool> visited;            // create a map to store visited nodes
 
  for (const auto& t : graph_) {          // initialize the map
    visited.insert({t.first, false});
  }
 
  while (!q.empty()) {
    std::pair<int, int> np = q.front();   // get value from the queue
 
    if (np.first == uin_2) {              // if the value matches, return its value in queue (they are related)
      return q.front().second;
    }
    for (const auto& each_node : graph_.find(np.first)->second) {   // traverse the node's adjacency list
      if (!visited[each_node.first] && each_node.second == relationship) { // if we haven't traversed the node, 
        visited[each_node.first] = true;                                   // and its edge matches the passed-in relationship
        int x = q.front().second;                                          // update its value in queue
        x++;
        q.push({each_node.first, x});
      }
    }
    q.pop();                              // pop out the node
  }
  return -1;
}


std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::queue<std::pair<int, int>> q;      // create a queue to traverse the graph
  q.push({uin, 0});                       // add the start node to the queue
  std::map<int, bool> visited;            // create a map to store visited nodes
  std::vector<int> path;                  // a vector to record steps to reach other nodes from uin

  for (const auto& t : graph_) {          // initialize the map
    visited.insert({t.first, false});
  }
 
  while (!q.empty()) {
    std::pair<int, int> np = q.front();   // get value from the queue
    bool done = false;                    // a condition that whether all nodes with steps n are found or not

    for (const auto& each_node : graph_.find(np.first)->second) {   // traverse the node's adjacency list
      if (!visited[each_node.first]) {    // if we haven't traversed the node, update its value in queue
        visited[each_node.first] = true;
        int x = q.front().second;
        x++;
        q.push({each_node.first, x});
        if (x == n && each_node.first != uin) {
          path.push_back(each_node.first);
        } else if (x > n) {               // if all nodes with steps n are found, break the for loop
          break;
          done = true;
        }
      }
    }
    q.pop();
    if (done)                             // if all nodes with steps n are found, break the while loop as well
      break;
  }
  return path;
}


size_t IlliniBook::CountGroups() const {
  std::set<std::set<int>> ss;
  std::vector<int> verticies;
  for (const auto& entry : graph_) {          // find every node in the graph and store it
    verticies.push_back(entry.first);
  }
  std::map<int, bool> visited;
  for (const auto& t : graph_) {              // set up visited nodes as all false
    visited.insert({t.first, false});
  }

  for (int node: verticies) {                 // traverse each node to find how many connected components
    if (visited[node])                        // if teh node has been traversed, skip the node
      continue;
    std::queue<std::pair<int, int>> q;        // by removing duplicates of traversal
    std::set<int> path;

    q.push({node, 0});
    path.insert(node); 
    while (!q.empty()) {
      std::pair<int, int> np = q.front();     
      for (const auto& each_node : graph_.find(np.first)->second) {    // find the adjacent nodes of the current node
        if (!visited[each_node.first]) {      // if we haven't traversed the node, update its value in queue
          visited[each_node.first] = true;
          int x = q.front().second;
          x++;
          q.push({each_node.first, x});
          path.insert(each_node.first);       // update the node into path set                      
        }
      }
      q.pop();
    }
    ss.insert(path);                          // insert the set of traversed nodes (path) into the set
  }
  return ss.size();
}


size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::set<std::set<int>> ss;
  std::vector<int> verticies;
  for (const auto& entry : graph_) {          // find every node in the graph and store it
    verticies.push_back(entry.first);
  }
  std::map<int, bool> visited;
  for (const auto& t : graph_)                // set up visited nodes as all false
    visited.insert({t.first, false});
  
  for (int node: verticies) {                 // traverse each node to find how many connected components
    if (visited[node])                        // if the node has been traversed, skip the node
      continue;
    std::queue<std::pair<int, int>> q;        
    std::set<int> path;
    q.push({node, 0});
    path.insert(node);      
    while (!q.empty()) {
      std::pair<int, int> np = q.front();     
      for (const auto& each_node : graph_.find(np.first)->second) {    // find the adjacent nodes of the current node
        if (!visited[each_node.first] && each_node.second == relationship) { // if we haven't traversed the node, 
          visited[each_node.first] = true;                                   // and its edge matches the passed-in relationship
          int x = q.front().second;                                          // update its value in queue
          x++;
          q.push({each_node.first, x});
          path.insert(each_node.first);                                // update the node into path set                     
        }
      }
      q.pop();
    }
    ss.insert(path);                          // insert the set of traversed nodes (path) into the set
  }
  return ss.size();
}


size_t IlliniBook::CountGroups(const std::vector<std::string>& relationships) const {
  std::set<std::string> relations;            // save all relationships in a set 
  for (const std::string& s : relationships) {
    relations.insert(s);
  }
  std::set<std::set<int>> ss;
  std::vector<int> verticies;
  for (const auto& entry : graph_) {          // find every node in the graph and store it
    verticies.push_back(entry.first);
  }
  std::map<int, bool> visited;
  for (const auto& t : graph_)                // set up visited nodes as all false
    visited.insert({t.first, false});
  
  for (int node: verticies) {                 // traverse each node to find how many connected components
    if (visited[node])                        // if the node has been traversed, skip the node
      continue;
    std::queue<std::pair<int, int>> q;        
    std::set<int> path;
    q.push({node, 0});
    path.insert(node);      
    while (!q.empty()) {
      std::pair<int, int> np = q.front();     
      for (const auto& each_node : graph_.find(np.first)->second) {    // find the adjacent nodes of the current node
        if (!visited[each_node.first] && relations.count(each_node.second) != 0) { // if we haven't traversed the node, 
          visited[each_node.first] = true;                                   // and its edge matches the passed-in relationship
          int x = q.front().second;                                          // update its value in queue
          x++;
          q.push({each_node.first, x});
          path.insert(each_node.first);                                      // update the node into path set      
        }
      }
      q.pop();
    }
    ss.insert(path);                          // insert the set of traversed nodes (path) into the set
  }
  return ss.size();
}


// std::ostream& operator<<(std::ostream& os, const IlliniBook& graph) {
//   os << "Contents:" << std::endl;

//   for (const auto& pair : graph.graph_) {
//     os << "  " << pair.first << ": [";
//     int i = pair.second.size() - 1;
//     for (const auto& list_entry : pair.second) {
//       os << list_entry.first << "--" << list_entry.second;
//       if (i != 0) os << ", ";
//       i -= 1;
//     }

//     os << "]" << std::endl;
//   }

//   return os;
// }
