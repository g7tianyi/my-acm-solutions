/*
 * Complete the function below.
 */
int maxXor(int l, int r) {
int result = -1;
    for (int i = l; i < r; ++i) {
        for (int j = i + 1; j <= r; ++j) {
            result = std::max(result, (i ^ j));
        }
    }
    return result;
}

