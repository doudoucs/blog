//
//  main.cpp
//  tree
//
//  Created by 焦媛 on 2017/2/8.
//  Copyright © 2017年 焦媛. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include "stdio.h"

using namespace std;


//链表结构的定义
struct ListNode{
    int m_nValue;
    ListNode * m_pNext;
};


//1. 求单链表中结点的个数 时间复杂度为O（n）
int getListNodeNum(ListNode *pHead){
    if(pHead == NULL){
        return 0;
    }
    int num =0;
    ListNode * pCurrent = pHead;
    while(pCurrent != NULL){
        num++;
        pCurrent = pCurrent->m_pNext;
    }
    return num;
}

//2、遍历输出节点
void printList(ListNode *pHead){
    if(pHead == NULL){
        return;
    }
    ListNode * tmpNode = pHead;
    while(tmpNode != NULL){
        printf("%d\t",tmpNode->m_nValue);
        tmpNode = tmpNode->m_pNext;
    }
}

void printList1(ListNode *pHead){
    if(pHead == NULL){
        return;        //递归出口
    }else{
        printf("%d\t",pHead->m_nValue);
        printList1(pHead->m_pNext);
    }
}

//3. 将单链表反转 时间复杂度为O（n）
ListNode * ReverseList(ListNode *pHead){
    if(pHead ==NULL || pHead->m_pNext == NULL){
        return pHead;
    }
    ListNode* pCurrent = pHead;
    ListNode* new_head = NULL;
    ListNode* tmpNode = NULL;
    while(pCurrent !=NULL){
        tmpNode = pCurrent;
        pCurrent = pCurrent->m_pNext;
        tmpNode->m_pNext= new_head;
        new_head = tmpNode;
    }
    return new_head;
}

//4. 查找单链表中的倒数第K个结点（k > 0） 先倒置，任何正找K个
ListNode * getRKNode(ListNode *pHead,int K){
    if(pHead ==NULL || pHead->m_pNext == NULL){
        return pHead;
    }
    
    ListNode * rList = ReverseList(pHead);

    ListNode * node = NULL;
    while (K && rList!=NULL) {
        node = rList;
        rList = rList->m_pNext;
        K--;
    }
    return node;
}

//4.1 查找单链表中的倒数第K个结点（k > 0） 正向len-K+1
ListNode * getRKNode1(ListNode *pHead,int K){
    if(pHead ==NULL || pHead->m_pNext == NULL){
        return pHead;
    }
    
    int len  = getListNodeNum(pHead);
    int num  = len-K+1;
    
    ListNode * node = NULL;
    while (num && pHead!=NULL) {
        node = pHead;
        pHead = pHead->m_pNext;
        num--;
    }
    return node;
}

//4.2 查找单链表中的倒数第K个结点（k > 0） 1-k,k-尾部
ListNode * getRKNode2(ListNode *pHead,int K){
    if(pHead ==NULL || pHead->m_pNext == NULL){
        return pHead;
    }
    
    
    ListNode * node1 = pHead;
    ListNode * node2 = pHead;
    while (K > 1 && node1 != NULL) {
        node1 = node1->m_pNext;
        K--;

    }
    if(K > 1){
        return NULL;
    }
    while (node1->m_pNext != NULL) {
        node1 = node1->m_pNext;
        node2 = node2->m_pNext;
    }
    return node2;
}

//5、查找单链表的中间结点
ListNode* getMiddleNode(ListNode *pHead){
    if(pHead ==NULL || pHead->m_pNext == NULL){
        return pHead;
    }
    ListNode* last = pHead;
    ListNode* middle = pHead;
    while(last->m_pNext != NULL){
        last = last->m_pNext;
        middle = middle->m_pNext;
        if(last->m_pNext !=NULL){
            last = last->m_pNext;
        }
    }
    return middle;
}

//6、从尾到头打印单链表  借助栈 stack
void RPrintList(ListNode *pHead){
    printf("倒序遍历链表：");
    if(pHead == NULL){
         printf("链表为空\n");
        return;
    }
    if(pHead->m_pNext == NULL){
        printf("%d\n",pHead->m_nValue);
        return;
    }
    stack<int> s;
    while(pHead !=NULL){
        s.push(pHead->m_nValue);
        pHead =pHead->m_pNext;
    }
    while (!s.empty()) {
        printf("%d\t",s.top());
        s.pop();
    }
    printf("\n");
    return;
}

//6、从尾到头打印单链表  递归
void RPrintList1(ListNode *pHead){
    if(pHead == NULL){
        return;
    }else{
        RPrintList1(pHead->m_pNext);
        printf("%d\t",pHead->m_nValue);
    }
}


//7、已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序  非递归
/**
 <#Description#>

 @param pHead1 <#pHead1 description#>
 @param pHead2 <#pHead2 description#>
 @return <#return value description#>
 */
ListNode* mergeList(ListNode *pHead1 ,ListNode *pHead2){
    if(pHead1 == NULL){
        return pHead2;
    }
    if(pHead2 == NULL){
        return pHead1;
    }
    ListNode* mergerHead;
    if(pHead1->m_nValue < pHead2->m_nValue){
        mergerHead = pHead1;
        pHead1 = pHead1->m_pNext;
        mergerHead->m_pNext=NULL;
        
    }else{
        mergerHead = pHead2;
        pHead2 = pHead2->m_pNext;
        mergerHead->m_pNext=NULL;
    }
    ListNode* tmpHeadNode = mergerHead;
    while(pHead1!= NULL && pHead2!= NULL){
        if(pHead1->m_nValue < pHead2->m_nValue){
            tmpHeadNode->m_pNext= pHead1;
            pHead1 = pHead1->m_pNext;
            tmpHeadNode = tmpHeadNode->m_pNext;
            tmpHeadNode->m_pNext=NULL;
        }else{
            tmpHeadNode->m_pNext= pHead2;
            pHead2 = pHead2->m_pNext;
            tmpHeadNode = tmpHeadNode->m_pNext;
            tmpHeadNode->m_pNext=NULL;
        }
    }
    if(pHead1 != NULL){
        tmpHeadNode->m_pNext=pHead1;
    }else if(pHead2 != NULL){
        tmpHeadNode->m_pNext=pHead2;
    }
    return mergerHead;
}

ListNode* mergeList1(ListNode *pHead1 ,ListNode *pHead2){
    if(pHead1 == NULL){
        return pHead2;
    }
    if(pHead2 == NULL){
        return pHead1;
    }
    ListNode* mergerHead = NULL;
    if(pHead1->m_nValue < pHead2->m_nValue){
        mergerHead = pHead1;
        mergerHead->m_pNext = mergeList1(pHead1->m_pNext,pHead2);
    }else{
        mergerHead = pHead2;
        mergerHead->m_pNext = mergeList1(pHead1,pHead2->m_pNext);
    }
    return mergerHead;
}

//8、是否存在环 存在返回环节点
ListNode * IsExitsLoop(ListNode *pHead){
    ListNode * pFast = pHead; // 快指针每次前进两步
    ListNode * pSlow = pHead; // 慢指针每次前进一步
    while(pFast->m_pNext!=NULL && pSlow!=NULL){
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
       // printf("%d \t %d\n",pSlow->m_nValue,pFast->m_nValue);
        if(pFast == pSlow){
            return pFast;
        }
        
    }
    return NULL;
}

int getLoopLen(ListNode *pNode){
    ListNode * pFast = pNode; // 快指针每次前进两步
    ListNode * pSlow = pNode; // 慢指针每次前进一步
    int len = 0;
    while(pFast->m_pNext!=NULL && pSlow!=NULL){
        pFast = pFast->m_pNext->m_pNext;
        pSlow = pSlow->m_pNext;
        //printf("%d \t %d\n",pSlow->m_nValue,pFast->m_nValue);
        len++;
        if(pFast == pSlow){
            return len;
        }
    }
    return len;
}

ListNode* getLoopNode(ListNode *pHead,ListNode *pNode){
    while(pHead && pNode){
        if(pHead == pNode){
            return pNode;
        }
        pHead = pHead->m_pNext;
        pNode = pNode->m_pNext;
    }
    return NULL;
}

ListNode* createNode(){
    ListNode *head = NULL;
    ListNode *p1=NULL;
    ListNode *p2=NULL;
    
    p1 = (struct ListNode *)malloc(sizeof(struct ListNode));
    scanf("%d",&(p1->m_nValue));
    
    while (p1->m_nValue) {
        if(head == NULL){
            head = p2 = p1;
        }else{
            p2->m_pNext=p1;
            p2=p1;
            p1 = (struct ListNode *)malloc(sizeof(struct ListNode));
            scanf("%d",&(p1->m_nValue));
        }
        p2->m_pNext=NULL;
    }
    free(p1);
    p1=NULL;
    return head;
}


int main(int argc, const char * argv[]) {
    
    struct ListNode *list = NULL;
    //struct ListNode *list = (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *list1= (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *list2= (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *list3= (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *list4= (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *list5= (struct ListNode *)malloc(sizeof(struct ListNode));
//
//    
//    struct ListNode *new_list = (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *new_list1= (struct ListNode *)malloc(sizeof(struct ListNode));
//    
//    
//    list5->m_nValue=6;
//    list5->m_pNext=NULL;
//    
//    list4->m_nValue=5;
//    list4->m_pNext=list5;
//
//    
//    list3->m_nValue=4;
//    list3->m_pNext=list4;
//    
//    list2->m_nValue=3;
//    list2->m_pNext=list3;
//    
//    list1->m_nValue=2;
//    list1->m_pNext=list2;
//    
//    list->m_nValue=1;
//    list->m_pNext = list1;
//    
//    list5->m_pNext=list2;
//    
//    
//    new_list1->m_nValue=8;
//    new_list1->m_pNext=NULL;
//    
//    new_list->m_nValue=3;
//    new_list->m_pNext = new_list1;
    
//    printf("链表节点数: %d \n",getListNodeNum(list));
//    printf("遍历链表: ");
//    printList(list);
//    printf("\n");
    
    list = createNode();
    
    printList(list);
    printList1(list);
//    struct ListNode *node3 = IsExitsLoop(list);
//    if(node3 != NULL){
//        printf("链表存在环\n");
//        printf("链表环的长度: %d \n",getLoopLen(node3));
//        struct ListNode *node4 = getLoopNode(list,node3);
//        printf("链表环的入口节点: %d \n",node4->m_nValue);
//
//    }else{
//        printf("链表不存在环 \n");
//    }
    
    
    
    
    
//    printf("倒序链表: ");
//    struct ListNode *rlist = ReverseList(list);
//    printList(rlist);
//    printf("\n");
//    printf("遍历链表: ");
//    printList(new_list);
//    printf("\n");
//    int K= 2;
//    //printf("链表倒数第%d个节点: %d \n",K,getRKNode(list,K)->m_nValue);
//    
//    struct ListNode *node = getRKNode1(list,K);
//    if(node != NULL){
//        printf("链表倒数第%d个节点: %d \n",K,node->m_nValue);
//    }else{
//        printf("链表倒数第%d个节点: 未找到 \n",K);
//    }
//    struct ListNode *node1 = getRKNode2(list,K);
//    if(node1 != NULL){
//        printf("链表倒数第%d个节点: %d \n",K,node1->m_nValue);
//    }else{
//        printf("链表倒数第%d个节点: 未找到 \n",K);
//    }
//    
//    struct ListNode *node3 = getMiddleNode(list);
//    if(node3 != NULL){
//        printf("链表中间节点: %d \n",node3->m_nValue);
//    }else{
//        printf("链表中间节点: 未找到 \n");
//    }
//    RPrintList(list);
//    RPrintList1(list);
    
    //mergeList(list, new_list);
    
//    printf("合并后的链表1: ");
//    printList(mergeList1(list, new_list));
//    printf("\n");
    
//    printf("合并后的链表: ");
//    printList(mergeList(list, new_list));
//    printf("\n");

    
    

    
    free(list);
//    free(list1);
//    free(list2);
//    free(list3);
    return 0;

}



//////////////////////////////////////////////////


//二叉树结构定义
struct TreeNode
{
    int m_nValue;
    struct TreeNode* m_pLeft;
    struct TreeNode* m_pRight;
};


//1、求二叉树中的节点个数
int getNodeNum(struct TreeNode* root)
{
    if(root == NULL){
        return 0;
    }
    return getNodeNum(root->m_pLeft) + getNodeNum(root->m_pRight) + 1;
    
}

//2、求二叉树的深度
int getTreeDepth(struct TreeNode* root)
{
    if(root == NULL){
        return 0;
    }
    int left = getTreeDepth(root->m_pLeft);
    int right = getTreeDepth(root->m_pRight);
    return left > right ? (left+1) : (right+1);
}

//3、前序遍历
void pre(struct TreeNode* root)
{
    if(root == NULL){
        return;
    }
    printf("%d \t", root->m_nValue);
    pre(root->m_pLeft);
    pre(root->m_pRight);
    
}

//4、中序遍历
void middle(struct TreeNode* root)
{
    if(root == NULL){
        return;
    }
    middle(root->m_pLeft);
    printf("%d \t", root->m_nValue);
    middle(root->m_pRight);
    
}

//5、后序遍历
void post(struct TreeNode* root)
{
    if(root == NULL){
        return;
    }
    post(root->m_pLeft);
    post(root->m_pRight);
    printf("%d \t", root->m_nValue);
    
}

//6、分层遍历二叉树（按层次从上往下，从左往右）
void level(struct TreeNode* root){
    if(root == NULL){
        return ;
    }
    queue<struct TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        struct TreeNode* p_node;
        p_node =  q.front();
        if(p_node->m_pLeft != NULL)
        {
            q.push(p_node->m_pLeft);
        }
        if(p_node->m_pRight != NULL)
        {
            q.push(p_node->m_pRight);
        }
        printf("%d \t", p_node->m_nValue);
        q.pop();
    }
}

//7、将二叉查找树变为有序的双向链表（要求不能创建新节点，只调整指针）
void Convert(struct TreeNode * pRoot,struct TreeNode * & pFirstNode, struct TreeNode * & pLastNode)
{
    
}

//8、求二叉树第K层的节点个数
int getKLevelNum(struct TreeNode* root ,int k){
    if(root == NULL || k < 1){
        return 0;
    }
    if(k == 1){
        return 1;
    }
    int left ,right;
    left = getKLevelNum(root->m_pLeft,k-1);
    right= getKLevelNum(root->m_pRight, k-1);
    return (left+right);
}

//9、求二叉树中叶子节点的个数
int getLeafNodeNum(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    if(root->m_pLeft == NULL && root->m_pRight == NULL){
        return 1;
    }
    int left ,right;
    left = getLeafNodeNum(root->m_pLeft);
    right = getLeafNodeNum(root->m_pRight);
    return (left+right);
}

//10、判断两棵二叉树是否结构相同
int compare(struct TreeNode* root1,struct TreeNode* root2)
{
    if(root1 == NULL && root2 == NULL){
        return true;
    }else if (root1 == NULL || root2 == NULL){
        return false;
    }
    int rst1,rst2;
    rst1 = compare(root1->m_pLeft,root2->m_pLeft);
    rst2 = compare(root1->m_pRight,root2->m_pRight);
    return (rst1 & rst2);
}

//11、判断二叉树是不是平衡二叉树
bool IsAVL(struct TreeNode* root,int& height){
    if(root == NULL){
        height = 0;
        return true;
    }
    int heightLeft;
    bool resultLeft = IsAVL(root->m_pLeft, heightLeft);
    int heightRight;
    bool resultRight = IsAVL(root->m_pRight, heightRight);
    if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1) // 左子树和右子树都是AVL，并且高度相差不大于1，返回真
    {
        height = max(heightLeft, heightRight) + 1;
        return true;
    }
    else
    {
        height = max(heightLeft, heightRight) + 1;
        return false;
    }
}

//12、 求二叉树的镜像 （左右交换）
TreeNode* Mirror(struct TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    struct TreeNode* left = Mirror(root->m_pLeft);
    struct TreeNode* right = Mirror(root->m_pRight);
    root->m_pLeft = right;
    root->m_pRight = left;
    return root;
    
}
//13、判断二叉树是不是完全二叉树
bool IsCompleteBinaryTree(struct TreeNode* root)
{
    
    if(root == NULL){
        return false;
    }
    queue<struct TreeNode*> q;
    q.push(root);
    bool mustHaveNoChild = false;  //标记是否已经遇到走子树为空的情况
    bool result = true;
    while (!q.empty()) {
        struct TreeNode* node = q.front();
        q.pop();
        if(mustHaveNoChild){
            if(node->m_pLeft != NULL || node->m_pRight != NULL){
                result = false;
                break;
            }
        }else{
            if(node->m_pLeft != NULL && node->m_pRight != NULL){
                q.push(node->m_pLeft);
                q.push(node->m_pRight);
            }else if(node->m_pLeft != NULL && node->m_pRight == NULL){
                mustHaveNoChild = true;
                q.push(node->m_pLeft);
            }else if(node->m_pLeft == NULL && node->m_pRight != NULL){
                result = false;
                break;
            }else{
               mustHaveNoChild = true;
            }
        }
    }
    return result;
}


//int main(int argc, const char * argv[]) {
//    
//    struct TreeNode *tree;
//    struct TreeNode *left_tree;
//    struct TreeNode *right_tree;
//    
//    
//    tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
//    left_tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
//    right_tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
//    
//    tree->m_nValue=5;
//    tree->m_pLeft=left_tree;
//    tree->m_pRight=right_tree;
//    
//    left_tree->m_nValue=3;
//    left_tree->m_pRight=NULL;
//    left_tree->m_pLeft=(struct TreeNode*)malloc(sizeof(struct TreeNode));
//    left_tree->m_pLeft->m_nValue=2;
//    left_tree->m_pLeft->m_pLeft=NULL;
//    left_tree->m_pLeft->m_pRight=NULL;
//
//    
//    
//    right_tree->m_nValue=6;
//    right_tree->m_pLeft=NULL;
//    right_tree->m_pRight=NULL;
//    
//    
//    printf("二叉树的节点数 : %d \n", getNodeNum(tree));
//    printf("二叉树的深度 : %d \n", getTreeDepth(tree));
//    printf("前序遍历 : ");
//    pre(tree);
//    printf("\n");
//    printf("中序遍历 : ");
//    middle(tree);
//    printf("\n");
//    printf("后序遍历 : ");
//    post(tree);
//    printf("\n");
//    printf("按层遍历 : ");
//    level(tree);
//    printf("\n");
//    printf("第K层的节点个数 : %d \n",getKLevelNum(tree,3));
//    printf("叶子节点数: %d \n",getLeafNodeNum(tree));
//    int height;
//    printf("是不是平衡二叉树 : %d \t",IsAVL(tree,height));
//    printf("二叉树高度: %d \n",height);
//    
////    struct TreeNode * tree1 = Mirror(tree);
////    printf("镜像的前序遍历 : ");
////    pre(tree1);
////    printf("\n");
//     printf("是不是完全二叉树 : %d \n",IsCompleteBinaryTree(tree));
//    return 0;
//}
