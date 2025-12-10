#include <vector>
#include <iostream>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& vec) {
        size_t m = vec.size();
        n = 1;
        while (n < m) n <<= 1; 
        segment_tree.resize(2 * n - 1, 0);
        for (size_t i = 0; i < m; ++i) {
            segment_tree[get_new_index(i)] = vec[i];
        }
        for (int i = n - 2; i >= 0; --i) {
            segment_tree[i] = segment_tree[2 * i + 1] + segment_tree[2 * i + 2];
        }
    }
    
    int Request(size_t left, size_t right) {
        if (left > right) return 0;
        size_t Left = get_new_index(left);
        size_t Right = get_new_index(right);
        int ans = 0;
        while (Left < Right) {
            if (Left % 2 == 0) {
                ans += segment_tree[Left];
                Left++;
            }
            if (Right % 2 == 1) {
                ans += segment_tree[Right];
                Right--;
            }
            Left = parent(Left);
            Right = parent(Right);
        }
        if (Left == Right) {
            ans += segment_tree[Left];
        }
        return ans;
    }
    
    void Update(size_t index, int value) {
        size_t i = get_new_index(index);
        segment_tree[i] = value;
        while (i > 0) {
            i = parent(i);
            segment_tree[i] = segment_tree[2 * i + 1] + segment_tree[2 * i + 2];
        }
    }

private:
    std::vector<int> segment_tree;
    size_t n;
    size_t parent(size_t i) {
        return (i - 1) / 2;
    }
    size_t get_new_index(size_t i) {
        return n - 1 + i;
    }
};

int main() {
    std::vector<int> vec = {1, 5, 8, 9, 7, 6, 4, 9};
    SegmentTree st(vec);
    std::cout << "Сумма на отрезке [2, 5]: " << st.Request(2, 5) << "\n";
    std::cout << "Сумма на отрезке [0, 7]: " << st.Request(0, 7) << "\n";
    st.Update(3, 10);
    std::cout << "Сумма на отрезке [2, 5] после обновления: " << st.Request(2, 5) << "\n";
    return 0;
}