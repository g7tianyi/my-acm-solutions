/**
 * xiaobengdou
 * sgu104 Little shop of flowers
 * 1432321  17.03.13 22:01  fairyroad  104  .CPP  Accepted  15 ms 951 kbs
 */
#include <cstdio>
#include <limits>

struct DP {
  int maxv, pre;
};

const int MAX_RANGE = 102;
int F, V; // flowers, vase
int value[MAX_RANGE][MAX_RANGE];
int positions[MAX_RANGE];

// dp[i][j] stands for the max aesthetic value 
// of the first i flowers ending in vase j
// dp[i][j] = max(dp[i-1][j-k] + value[i][j]), where k in [1, V-F+1] 
//
// Watch out that if there can be always a negative value 
// where a flower be in all of its legal vase 

DP dp[MAX_RANGE][MAX_RANGE];

int main() {
  scanf("%d %d", &F, &V);

  for (int i = 1; i <= F; ++i)
    for (int j = 1; j <= V; ++j)
      scanf("%d", &value[i][j]);

  int range = V - F + 1, total_max = 0, total_max_pos = 0, imax, jmax, pre;
  for (int i = 1; i <= F; ++i) { // flower
    imax = std::numeric_limits<int>::min();
    for (int j = i; j < range + i && j <= V; ++j) { // end position
      jmax = dp[i - 1][j - 1].maxv + value[i][j];
      pre = j - 1;
      for (int k = 2; k <= range && j - k >= i - 1; ++k) {
        if (jmax < dp[i - 1][j - k].maxv + value[i][j]) {
          jmax = dp[i - 1][j - k].maxv + value[i][j];
          pre = j - k;
        }
      }
      dp[i][j].maxv = jmax;
      dp[i][j].pre = pre;
      if (imax < jmax) {
        imax = jmax;
        total_max_pos = j;
      }
    }
    total_max = imax;
  }

  printf("%d\n", total_max);

  for (int i = F; i > 0; --i) {
    positions[i] = total_max_pos;
    total_max_pos = dp[i][total_max_pos].pre;
  }

  for (int i = 1; i <= F; ++i)
    printf("%d ", positions[i]);

  return 0;
}
