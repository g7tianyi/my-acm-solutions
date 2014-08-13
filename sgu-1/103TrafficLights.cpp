/**
 * xiaobengdou
 * sgu103 Traffic Lights
 * 1434738  24.03.13 18:46  fairyroad  103  .CPP  Accepted  15 ms 1251 kb
 */
#include <cstdio>
#include <deque>
#include <algorithm>

struct LightTime {
  int bp[3]; // blue, purple and the sum
};

struct Node {
  int state; // "B" => 0 or "P" => 1
  int residue;
  int cost;
  int prev;
};

int start, dest;
Node crossing[302];
LightTime lasts[302];
int roads[302][302];

inline int min(int a, int b) {
  return a < b ? a : b;
}

// Be vary vareful about the fucking transformations
inline void change_state(Node& node, int id, int cost) {
  if (cost == 0)
    return;
  if (cost > 0) { // moving forward
    int more = cost % (lasts[id].bp[2]);
    // Syllogism. See the attachted files 103TrafficLights.png  
    if (more < node.residue ) {
      node.residue -= more;
    } else if (more < node.residue + lasts[id].bp[!node.state]) {
      node.residue = lasts[id].bp[!node.state] + node.residue - more;
      node.state = !node.state;
    } else {
      node.residue = lasts[id].bp[2] + node.residue - more;
    }
  } else { // moving backward
    cost = -cost;
    int more = cost % (lasts[id].bp[2]);
    if (more <= lasts[id].bp[node.state] - node.residue) {
      node.residue += more;
    } else if (more <= lasts[id].bp[2] - node.residue) {
      node.residue = more - (lasts[id].bp[node.state] - node.residue);
      node.state = !node.state;
    } else {
      node.residue = more + node.residue - lasts[id].bp[2] ;
    }
  }
}

inline bool existed_in_path(int node, int to_check) {
  if (to_check == start)
    return true;
  while (node && node != start) {
    if (node == to_check)
      return true;
    node = crossing[node].prev;
  }
  return false;
}

int main() {
  int N, M;
  scanf("%d %d %d %d\n", &start, &dest, &N, &M);
  char ch = 'B';
  for (int i = 1; i <= N; ++i) {
    scanf("%c %d %d %d\n", &ch, &crossing[i].residue, &lasts[i].bp[0],
        &lasts[i].bp[1]);
    crossing[i].state = (ch == 'B' ? 0 : 1);
    lasts[i].bp[2] = lasts[i].bp[0] + lasts[i].bp[1];
  }
  int begin, end, cost;
  for (int i = 0; i < M; ++i) {
    scanf("%d %d %d", &begin, &end, &cost);
    roads[begin][end] = cost, roads[end][begin] = cost;
    ++roads[begin][0], ++roads[end][0];
  }

  
  // SPFA algorithm:
  // The basic idea of SPFA is the same as Bellman¨CFord algorithm in that each vertex is used as a candidate to relax its adjacent vertices. 
  // The improvement over the latter is that instead of trying all vertices blindly
  // SPFA maintains a queue of candidate vertices and adds a vertex to the queue only if that vertex is relaxed. 
  // This process repeats until no more vertex can be relaxed.
  // Compared to the basic BFS, each node in SPFA can be pushed into the checking queue more than one time. 

  std::deque<int> Q; // Store the id of Nodes
  Q.push_back(start);

  while (!Q.empty()) {
    int curr = Q.front();

    int wait_cost = 0, j = 0; // j, count of directly connects
    Node from = crossing[curr];

    for (int i = 1; i <= N && j < roads[curr][0]; ++i) {
      if (!roads[curr][i])
        continue;
      ++j; // a directly connected node found

      Node to = crossing[i];

      if ((to.cost && from.cost >= to.cost)
          || existed_in_path(crossing[curr].prev, i))
        continue;

      change_state(to, i, from.cost - to.cost);

      if (from.state == to.state) {
        wait_cost = 0;
      } else if (from.residue < to.residue) {
        wait_cost = from.residue;
      } else if (from.residue > to.residue) {
        wait_cost = to.residue;
      } else {
        if (lasts[curr].bp[!from.state] == lasts[i].bp[!to.state]) { // next state
          if (lasts[curr].bp[from.state] == lasts[i].bp[to.state]) {
            continue; // dead circular switch
          } else {
            wait_cost = from.residue + lasts[curr].bp[!from.state]
                + min(lasts[curr].bp[from.state], lasts[i].bp[to.state]);
          }
        } else {
          wait_cost = from.residue
              + min(lasts[curr].bp[!from.state], lasts[i].bp[!to.state]);
        }
      }

      if (!to.cost || to.cost > from.cost + wait_cost + roads[curr][i]) { // never visited or a shorter path found
        change_state(to, i, wait_cost + roads[curr][i]);
        crossing[i].cost = from.cost + wait_cost + roads[curr][i];
        crossing[i].prev = curr;
        crossing[i].residue = to.residue;
        crossing[i].state = to.state;
        if (i != dest && (std::find(Q.begin(), Q.end(), i) == Q.end())) // can be optimized by introduing a bool in_queue[];
          Q.push_back(i);
      }
    }

    Q.pop_front();
  }

  printf("%d\n", crossing[dest].cost);

  if (crossing[dest].cost) {
    int path[302], count = 0, i = dest;
    while (i != start) {
      path[count++] = i;
      i = crossing[i].prev;
    }
    path[count++] = start;

    for (i = count - 1; i >= 0; --i)
      printf("%d ", path[i]);
  }
  return 0;
}
