#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;
void getPostOrder(vector<int> preOrder, int preL, vector<int> inOrder, int inL,
                  vector<int> &postOrder, int postL, int n)
{
    if (n == 0) return ;
    if (n == 1) {
        postOrder[postL] = preOrder[preL];
        return ;
    }
    auto root = preOrder[preL];
    postOrder[postL + n - 1] = root;
    int i = 0;
    while (i < n) {
        if (inOrder[inL + i] == root) break;
        ++i;
    }
    int L = i, R = n - i - 1;
    getPostOrder(preOrder, preL + 1, inOrder, inL, postOrder, postL, L);
    getPostOrder(preOrder, preL + L + 1, inOrder, inL + L + 1, postOrder, postL + L, R);
}

vector<vector<int>> getOrder(int N)
{
    vector<int> preOrder(N, 0);
    vector<int> inOrder(N, 0);
    stack<int> st;
    int preL = 0, inL = 0;

    for (int i = 0; i < 2*N; ++i) {
        string str; int tmp;
        cin >> str;
        if (str == "Push") {
            cin >> tmp;
            preOrder[preL++] = tmp;
            st.push(tmp);
        } else if (str == "Pop") {
            inOrder[inL++] = st.top();
            st.pop();
        }
    }
    return {preOrder, inOrder};
}

int main()
{
    int N;
    cin >> N;
    auto res = getOrder(N);
    vector<int> postOrder(N, 0);
    getPostOrder(res[0], 0, res[1], 0, postOrder, 0, N);

    int i = 0;
    for (; i < N-1; ++i) {
        cout << postOrder[i] << " ";
    }
    cout << postOrder[i] << endl;
    return 0;
}
