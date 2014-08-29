/*
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3512 KB]
   Test 2: TEST OK [0.000 secs, 3512 KB]
   Test 3: TEST OK [0.000 secs, 3512 KB]
   Test 4: TEST OK [0.000 secs, 3512 KB]
   Test 5: TEST OK [0.000 secs, 3512 KB]
   Test 6: TEST OK [0.000 secs, 3512 KB]
   Test 7: TEST OK [0.000 secs, 3512 KB]
   Test 8: TEST OK [0.000 secs, 3512 KB]
   Test 9: TEST OK [0.000 secs, 3512 KB]
   Test 10: TEST OK [0.000 secs, 3512 KB]
   Test 11: TEST OK [0.000 secs, 3512 KB]
   Test 12: TEST OK [0.000 secs, 3512 KB]

All tests OK.
Your program ('ditch') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!

*/

/*
 ID:fairyroad
 LANG:C++
 TASK:ditch
 */

#include <fstream>
#include <limits>

std::ifstream fin("ditch.in");
std::ofstream fout("ditch.out");

int graph[201][201], dislabel[201], vh[201];
int max_flow = 0, node_count, edge_count, delta;
bool found;

void SAP(int curr_node) {
  if (curr_node == node_count) {
    max_flow += delta;
    found = true;
    return;
  }

  int temp = delta, i, minh = node_count - 1;
  for (i = 1; i <= node_count; i++) {
    if (graph[curr_node][i] > 0) {
      if (dislabel[i] + 1 == dislabel[curr_node]) {
        delta = std::min(delta, graph[curr_node][i]);
        SAP(i);
        if (dislabel[1] >= node_count)
          return;
        if (found)
          break;
        delta = temp;
      }
      minh = std::min(minh, dislabel[i]);
    }
  }

  if (found) {
    graph[curr_node][i] -= delta;
    graph[i][curr_node] += delta;
  } else {
    vh[dislabel[curr_node]]--;
    if (vh[dislabel[curr_node]] == 0)
      dislabel[1] = node_count;
    dislabel[curr_node] = minh + 1;
    vh[dislabel[curr_node]]++;
  }
}

int main() {
  fin >> edge_count >> node_count;

  int start, end, capacity;
  for (int i = 1; i <= edge_count; i++) {
    fin >> start >> end >> capacity;
    graph[start][end] += capacity;
  }

  vh[0] = node_count;
  while (dislabel[1] < node_count) {
    delta = std::numeric_limits<int>::max();
    found = false;
    SAP(1);
  }

  fout << max_flow << std::endl;
  return 0;
}

