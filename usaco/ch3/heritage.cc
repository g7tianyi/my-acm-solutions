/*
 ID: fairyroad
 LANG: C++
 TASK: heritage
 */

 /**
  Compiling...
  Compile: OK

  Executing...
     Test 1: TEST OK [0.000 secs, 3360 KB]
     Test 2: TEST OK [0.000 secs, 3360 KB]
     Test 3: TEST OK [0.000 secs, 3360 KB]
     Test 4: TEST OK [0.000 secs, 3360 KB]
     Test 5: TEST OK [0.000 secs, 3360 KB]
     Test 6: TEST OK [0.000 secs, 3360 KB]
     Test 7: TEST OK [0.000 secs, 3360 KB]
     Test 8: TEST OK [0.000 secs, 3360 KB]
     Test 9: TEST OK [0.000 secs, 3360 KB]

  All tests OK.
  YOUR PROGRAM ('heritage') WORKED FIRST TIME!  That's fantastic
  -- and a rare thing.  Please accept these special automated
  congratulations.
 */
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;

ifstream fin("heritage.in");
ofstream fout("heritage.out");
string preorder, inorder, postorder = "";

void dfs(string& pre, string& in) {
  if (pre.empty() || in.empty())
    return;
  char root = pre[0];
  postorder = root + postorder;
  size_t pos_i = in.find_first_of(root);
  string left_i = in.substr(0, pos_i);
  string right_i = in.substr(pos_i + 1, in.size());
  size_t pos_p = right_i.size();
  string right_p = pre.substr(pre.size() - pos_p, pre.size());
  string left_p = pre.substr(1, pre.size() - pos_p - 1);
  dfs(right_p, right_i);
  dfs(left_p, left_i);
}

int main() {
  fin >> inorder >> preorder;
  dfs(preorder, inorder);
  fout << postorder << std::endl;
  return 0;
}
