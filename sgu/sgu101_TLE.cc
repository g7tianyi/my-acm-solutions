#include <iostream>

struct domino {
  int left, right;
  bool visited;
};

struct resitem {
  int id;
  char ch; // rotate
  resitem() :
      id(-1), ch('*') {
  }
  resitem(int _id, char _ch) :
      id(_id), ch(_ch) {
  }
};

int N;
int degree[7];
int hash[7][204];
domino dom[102];
resitem res[102];
int odd_degree_cnt = 0;

inline void swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

bool dfs(int start, int depth) {
  if (depth > N) {
    return true;
  }
  int id = 0;
  for (int i = hash[start][0]; i > 0; --i) {
    id = hash[start][i];
    if (id == 0 || dom[id].visited)
      continue;
    dom[id].visited = true;
    if (dom[id].left == start) {
      res[depth] = resitem(id, '+');
      start = dom[id].right;
    } else {
      res[depth] = resitem(id, '-');
      start = dom[id].left;
    }
    if (dfs(start, depth + 1) && depth == N) {
      for (int i = 1; i <= N; ++i)
        if (!dom[i].visited)
          return false;
      for (int i = 1; i <= N; ++i)
        std::cout << res[i].id << ' ' << res[i].ch << std::endl;
      return true;
    }
    dom[id].visited = false;
  }
  return false;
}

int main() {
  std::cin >> N;
  int le, ri; // left, right
  for (int i = 1; i <= N; ++i) {
    std::cin >> le >> ri;
    ++degree[le];
    ++degree[ri];
    hash[le][++hash[le][0]] = i;
    hash[ri][++hash[ri][0]] = i;
    dom[i].left = le;
    dom[i].right = ri;
  }
  
  fout << "hash[start][0] " << std::endl;
  for (int i = 1; i <= 6; ++i) {
    fout << hash[i][0] << ' ';
  }
  fout << std::endl;

//  std::cout << "degree: ";
//  for (int i = 1; i < 7; ++i)
//    std::cout << i << "->" << degree[i] << ' ';
//  std::cout << std::endl;

  int start = le;
  for (int i = 1; i <= 6; ++i) {
    if (degree[i] & 0x1u)
      ++odd_degree_cnt, start = i;
  }

  if ((odd_degree_cnt && odd_degree_cnt != 2) || !dfs(start, 1)) {
    std::cout << "No solution" << std::endl;
    return 0;
  }

  return 0;

}