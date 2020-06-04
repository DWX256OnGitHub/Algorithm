#include <cstdio>
#include <cctype>

#define N 10

typedef struct Node
{
    int data, left, right;
} TreeNode;
TreeNode node[N];
TreeNode Queue[N];          //数组实现队列

int first = -1, last = -1;

void Push(TreeNode tn);
TreeNode Pop();
void printLeaves(int root, int n);

int charToInt(char ch);

int main()
{
    int n;
    bool isRoot[N];
    int root;

    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
        isRoot[i] = 1;
    for (int i = 0; i < n; i++)
    {
        char cLeft, cRight;
        scanf("%c %c", &cLeft, &cRight);
        getchar();      //读取缓存区的回车符
        node[i].left = charToInt(cLeft);
        node[i].right = charToInt(cRight);
        node[i].data = i;
        //一个节点的左孩子和右孩子一定不是根节点
        if (node[i].left != -1)
            isRoot[node[i].left] = 0;
        if (node[i].right != -1)
            isRoot[node[i].right] = 0;
    }
    //找到根节点
    for (int i = 0; i < n; i++)
    {
        if (isRoot[i])
        {
            root = i;
            break;
        }
    }
    printLeaves(root, n);

    return 0;
}

void Push(TreeNode treeNode)
{
    Queue[++last] = treeNode;
}

TreeNode Pop()
{
    return Queue[++first];
}

//层序遍历树节点并打印出叶节点：队列实现
void printLeaves(int root, int n)
{
    int leaves[N];
    int k = 0;
    Push(node[root]);
    for (int i = 0; i < n; i++)
    {
        TreeNode tn = Pop();
        //左孩子和右孩子都不存在时，将叶节点的值保存到数组中，便于格式化打印
        if (tn.left == -1 && tn.right == -1)
            leaves[k++] = tn.data;
        if (tn.left != -1)
            Push(node[tn.left]);
        if (tn.right != -1)
            Push(node[tn.right]);
    }
    for (int i = 0; i < k-1; i++)
        printf("%d ", leaves[i]);
    printf("%d\n", leaves[k-1]);
}

int charToInt(char ch)
{
    if (isdigit(ch))
        return ch - '0';
    else
        return -1;
}
