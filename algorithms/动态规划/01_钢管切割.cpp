/** 钢条切割问题
 * 给定一条长度为 n 的钢条的一个价格表 p，要求切割出最大收益。
 */

#include <iostream>

using namespace std;


class Solution {
public:

    // 自顶向下
    int memoized_cut_rod(int p[], int n) {
        int r[n];
        // 初始化最大价值数组
        // 将钢条长度为 1 的情况（只有一种分割可能）独立，避免 f(1) = f(1) + f(0) 的死循环
        // 其余位置置 0
        r[0] = p[0];
        for (int i = 1; i < n; i++) r[i] = 0;
        return memoized_cut_rod_aux(p, n, r);
    }
    int memoized_cut_rod_aux(int p[], int n, int r[]) {
        // 若钢条长度为 0，则最大价值为 0
        if (!n) return 0;
        // 备忘机制，使用 线性空间复杂度 降低 指数时间复杂度
        if (r[n - 1] > 0) return r[n - 1];
        // 使用变量 s 来避免无效循环，最大切割长度确定为 p.size()
        int q = 0, s = n > 10 ? 10 : n;
        // 从大到小进行分割，降低遍历深度，优先计算子问题
        for (int i = s; i > 0; i--) {
            int t = memoized_cut_rod_aux(p, n - i, r) + p[i - 1];
            q = q > t ? q : t;
        }
        // 保存 n 长度的最大价值
        r[n - 1] = q;
        return q;
    }

    // 自底向上
    // 不需要频繁调用递归函数。时间复杂度系数更小
    int bottom_up_cut_rod(int p[], int n) {
        int r[n + 1];
        for (int i = 0; i <= n; i++) r[i] = 0;
        // 从长度为 1 到 n 计算最大价值 r[j]
        for (int j = 1; j <= n; j++) {
            int q = 0, s = j > 10 ? 10 : j;
            // 分别切割 1 到 max(j, 10) 的长度 i，计算价值 t
            for (int i = 1; i <= s; i++) {
                int t = p[i - 1] + r[j - i];
                q = q > t ? q : t;
            }
            r[j] = q;
        }
        return r[n];
    }
};


int main(int argc, char const *argv[]) {

    // 价格表 p, 切割下来的长度若为 i + 1，则对应价格为 p[i]
    // 实际上，cut_rod 函数内默认 p.size() = 10
    int p[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    // 钢条长度 n
    int n = 25;

    Solution s;
    cout << s.memoized_cut_rod(p, n) << endl;
    cout << s.bottom_up_cut_rod(p, n) << endl;
}

