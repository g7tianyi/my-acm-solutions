/**
 * HDU 1864, 最大报销额
 * DP. 0-1 packing problem.
 */
#include <cstdio>
#include <cstring>

enum {
    MAX_RECIPE = 32, MAX_ITEM_PRICE = 601, MAX_RECIPE_PRICE = 1001
};
double recipe[MAX_RECIPE];
double dp[MAX_RECIPE];
int main() {
    double maxMoney;
    int nRecipes;
    while (scanf("%lf %d", &maxMoney, &nRecipes) != EOF && nRecipes) {
        int nItems, k = 0;
        char type;
        double money, items[3];
        memset(recipe, 0, sizeof(recipe));
        for (int i = 0; i < nRecipes; ++i) {
            scanf("%d", &nItems);
            double sum = 0;
            bool valid = true;
            memset(items, 0, sizeof(items));
            for (int j = 0; j < nItems; ++j) {
                scanf(" %c:%lf", &type, &money);
                if (type != 'A' && type != 'B' && type != 'C') {
                    valid = false;
                    break;
                }
                items[type - 'A'] += money;
                sum += money;
            }
            if (valid
                    && items[0] < MAX_ITEM_PRICE
                    && items[1] < MAX_ITEM_PRICE
                    && items[2] < MAX_ITEM_PRICE
                    && sum < MAX_RECIPE_PRICE) {
                recipe[k++] = sum;
            }
        }
        nRecipes = k;

        /**
         * F(i), the maximum money of reimbursing the first i recipes
         * F(i) = max {
         *   F(j) + recipe(i), if F(j) + recipe(i) <= maxMoney,
         *   where j in [0, i).
         * }
         */
        memset(dp, 0, sizeof(dp));
        dp[0] = recipe[0] <= maxMoney ? recipe[0] : 0;
        double result = dp[0];
        for (int i = 1; i < nRecipes; ++i) {
            for (int j = 0; j < i; ++j) {
                money = dp[j] + recipe[i];
                if (dp[i] < money && money <= maxMoney) {
                    dp[i] = money;
                }
            }
            result = dp[i] > result ? dp[i] : result;
        }

        printf("%.2lf\n", result);
    }
    return 0;
}

