#define MAXACCOUNTLENGTH 10
#define MINACCOUNTLENGTH 4
#define MAXPASSLENGTH 16
#define MINPASSLENGTH 6
#define MAXTABLESIZE 1000000
#define MAXD 5
#define KEYLENGTH 16
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef char ElementType[KEYLENGTH + 1];
typedef int  Index;
typedef int CountType;
/******************* 单链表的定义 *************************/
typedef struct LNode * PtrToLNode;
struct LNode{
    ElementType Account; /* 比较ACCOUNT */
    ElementType  PassWord;
    struct LNode * Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******************** 散列表类型 ************************/
typedef struct TblNode * HashTable;
struct TblNode{     /* 散列表结点定义 */
    int TableSize;  /* 表的最大长度 */
    List Heads;     /* 指向链表头结点的数组 */
};
int NextPrime (int N);
Index Hash(ElementType Key, int TableSize);
 
/******************** 哈希表的创建 ************************/
HashTable CreateTable( int TableSize){
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* 保证散列表最大长度是素数 */
    H->TableSize = NextPrime(TableSize);
    
    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(sizeof(struct LNode) * H->TableSize);
    /* 初始化表头结点 */
    for( i = 0; i < H->TableSize ; i++){
        H->Heads[i].PassWord[0] = '\0';
        H->Heads[i].Account[0] = '\0';
        H->Heads[i].Next = NULL;
    }
    return H;
}
/******************** 遍历哈希表的寻找 ************************/
Position Find(HashTable H, ElementType Key){
    Position p;
    Index Pos;
    Pos = Hash (Key, H->TableSize);
    p = H->Heads[Pos].Next;
    while( p && strcmp(p->Account, Key)){
        p = p->Next;
    }
    return  p;  /* 此时P或者指向找到的结点，或者为NULL */
}
/******************** 哈希表的插入 ************************/
bool Insert(HashTable H, PtrToLNode NewNode){
    Position p, NewCell;
    Index Pos;
    
    p = Find(H, NewNode->Account);
    if(!p){ /* 一般都插入到头节点中 */
        printf("New: OK\n");
        /* 拷贝 */
        NewCell = (PtrToLNode)malloc(sizeof(struct LNode));
        strcpy(NewCell->Account, NewNode->Account);
        strcpy(NewCell->PassWord, NewNode->PassWord);
        Pos = Hash(NewNode->Account, H->TableSize);
        
        /* 插入 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }else{
        /* 已存在 */
        printf("ERROR: Exist\n");
        return false; /* ALREADY EXIST!!! */
    }
}
/******************** Destroy *************************/
void DestroyTable ( HashTable H ){
    int i;
    Position p, tmp;
    
    for( i = 0; i < H->TableSize; i++){
        p = H->Heads[i].Next;
        while (p) {
            tmp = p->Next;
            free(p);
            p = tmp;
        }
    }
    free( H->Heads );
    free( H );
}
/******************** 寻找 Next Prime *************************/
int NextPrime (int N){
    int i, p = (N % 2) ? N + 2 : N + 1;  /*从大于N的下一个奇数开始 */
    
    while( p <= MAXTABLESIZE){
        for( i = (int) sqrt(p); i > 2; i--){
            if( !(p%i) )
                break;   /* 说明P不是素数 */
        }
        if ( i == 2 )  break; /* for正常结束，说明p是素数 */
        else  p += 2;
    }
    return p;
}
/******************** 寻找 Next Prime ************************/
Index Hash(ElementType Key, int TableSize){
    int NewKey = atoi(Key + MINACCOUNTLENGTH);
    return NewKey % TableSize;
}
/******************** 主函数 ************************/
int main(int argc, const char * argv[]) {
    int N, i;
    ElementType Acount, Password;
    HashTable H;
    char op = '\0';
    
    scanf("%d\n", &N);
    H = CreateTable( N * 2);
    for( i = 0; i < N; i++){
        scanf("%c ", & op);
        if( op == 'L'){
            scanf("%s %s\n", Acount, Password);
            
            PtrToLNode p =  Find(H, Acount);
            if( p && strcmp(p->PassWord, Password) == 0){        /* 找到了且密码相等 */
                printf("Login: OK\n");
            }else if(p && strcmp(p->PassWord, Password) != 0 ){  /* 找到了但密码不等 */
                printf("ERROR: Wrong PW\n");
            }else{                                                /* 没找到 */
                printf("ERROR: Not Exist\n");
            }
            
        }
        if( op == 'N'){
            scanf("%s %s\n", Acount, Password);
            //test(Accout, Password);  测验后这样写可以的
            
            PtrToLNode NewCell = malloc(sizeof(struct LNode));
            strcpy(NewCell->Account, Acount);
            strcpy(NewCell->PassWord, Password);
            NewCell->Next = NULL;
            Insert(H, NewCell);
            free(NewCell);
        }
    }
    
    DestroyTable( H );
    return 0;
}
/******************** TEST ************************/
void test(ElementType Accout, ElementType Password){
    printf("%s %s\n", Accout, Password);
    printf("Length of Account is %d, Length of Password is %d", strlen(Accout), strlen(Password));
}
