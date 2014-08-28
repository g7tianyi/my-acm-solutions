// xiaobengdou
// sgu108 Self Numbers
// 1435824  28.03.13 20:11  fairyroad  108  .CPP  Accepted  109 ms  927 kb
#include <cstdio>
#include <algorithm>

struct OUTPUT {
  int input_index, output_index, result;
};

bool compare_in_input_order(OUTPUT a, OUTPUT b) {
  return a.input_index < b.input_index;
}

bool compare_in_output_order(OUTPUT a, OUTPUT b) {
  return a.output_index < b.output_index;
}

int sumdigits[10001];
int N, K;
OUTPUT selfnum[5002];
// slide window to store the latest number to see if they can be generated
bool slide[2][64]; // if the lastest number can reach to slide[i] ? 

// Don't make the assumption that the input indexs sk will less than 5000£¬ or ordered£¬ or no repeat !!!!!!
// The difficulty and charisma lie here
int main() {
  scanf("%d %d", &N, &K);
  for (int i = 0; i < K; ++i) {
    scanf("%d", &selfnum[i].output_index);
    selfnum[i].input_index = i;
  }
  selfnum[K + 1].output_index = 0;
  std::sort(selfnum, selfnum + K, compare_in_output_order);

  // Init the first 10000 digit sums, then we can get a number's digit sum in O(1) time
  for (int i = 0; i <= 10000; ++i)
    sumdigits[i] = i / 1000 + i / 100 % 10 + i / 10 % 10 + i % 10;

  int count = 0, flag = 0, circle = 1, di, out_index = 0;
  std::fill(slide[0], slide[0] + 64, true);
  std::fill(slide[1], slide[1] + 64, true);
  for (int i = 1; i <= N; ++i) {
    if ((i & 63) == 0) {
      std::fill(slide[flag], slide[flag] + 64, true);
      flag = !flag, ++circle;
    }
    if (slide[flag][i & 63]) {
      ++count;
      while (count == selfnum[out_index].output_index) // output_index may be duplicated
        selfnum[out_index++].result = i;
    }
    slide[flag][i & 63] = true;
    di = i + sumdigits[i / 10000] + sumdigits[i % 10000];
    if (di >= 64 * circle)
      slide[!flag][di & 63] = false;
    else
      slide[flag][di & 63] = false;
  }

  printf("%d\n", count);
  std::sort(selfnum, selfnum + K, compare_in_input_order);
  for (int i = 0; i < K; ++i)
    printf("%d ", selfnum[i].result);

  return 0;
}
