/**
 * xiaobengdou
 * sgu101 domino
 * 
 * 1431877  16.03.13 12:37  fairyroad  101  .CPP  Accepted  31 ms 923 kb
 */

#include <iostream>
#include <cstring>

struct node {
  int id;
  int next;
  char rotate; // '+' or '-'
  node() :
      id(0), next(0), rotate('@') { // illegal state
  }
  node(int i, int n, char r) :
      id(i), next(n), rotate(r) {
  }
};

int N;
int degree[7];
node graph[7][203];
bool visited[102];
bool viscount;
int odd_degree_cnt;

void dfs(int start) {
  for (int i = graph[start][202].id; i > 0; --i) {
    node curr = graph[start][i];
    if (!visited[curr.id]) {
      visited[curr.id] = true;
      dfs(curr.next);
    }
  }
}

// Normal dfs search like 
// dfs (start, depth) {
//   find a new start
//   mark start as visited
//   if not dfs(newstart, depth+1)
//   mark start as not visited
// }
// will TLE
// watch out that when a partial chain was met
// it must be one end of whole chain
// so here comes the following optimazition

void get_result(int start) {
  for (int i = graph[start][202].id; i > 0; --i) {
    node curr = graph[start][i];
    if (!visited[curr.id]) { 
      visited[curr.id] = true;
      get_result(curr.next);
      std::cout << curr.id << ' ' ;
      char ch = curr.rotate == '+' ? '-' : '+';
      std::cout << ch << std::endl;
    }
  }
}

int main() {
  std::cin >> N;
  int le, ri; // left, right
  for (int i = 1; i <= N; ++i) {
    std::cin >> le >> ri;
    ++degree[le];
    ++degree[ri];
    graph[le][++graph[le][202].id] = node(i, ri, '+');
    graph[ri][++graph[ri][202].id] = node(i, le, '-');
  }

  int start = le;
  for (int i = 0; i <= 6; ++i) {
    if (degree[i] & 0x1u)
      ++odd_degree_cnt, start = i;
  }

  if (odd_degree_cnt && odd_degree_cnt != 2) {
    std::cout << "No solution" << std::endl;
    return 0;
  }

  dfs(start);
  for (int i = 1; i <= N; ++i)
    if (!visited[i]) {
      std::cout << "No solution" << std::endl;
      return 0;
    }
  
  memset(visited, false, sizeof(visited));
  get_result(start);

  return 0;
}
