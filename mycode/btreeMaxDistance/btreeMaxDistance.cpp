/*
思路：二叉树的节点间最远距离等于左右子树树高的和
*/
#include <string>
#include <iostream>
#include <stack>

using namespace std;

typedef struct node{
    struct node *left;
    struct node *right;
    char v;
    node(){left=right=NULL; v=0;}
}treeNode;

int getTreeHight(treeNode *root){
    if(root==NULL){
        return 0;
    }
    int left_height = getTreeHight(root->left);
    int right_height = getTreeHight(root->right);
    return (left_height>right_height ? left_height : right_height)+1;
}

int getMaxDistance(treeNode *root){
    int left_height = getTreeHight(root->left);
    int right_height = getTreeHight(root->right);
    return left_height+right_height;
}

/*
     2
 1       3
  0     4
*/
treeNode * build_test_tree(){
    treeNode *nodes = new treeNode[5];
    for(int i=0; i<5; i++){
        nodes[i].v = 'a' + i;
    }
    nodes[1].right = nodes+0;
    nodes[3].left = nodes+4;
    nodes[2].left = nodes+1;
    nodes[2].right = nodes+3;
    return nodes+2;
}

int main(){
    treeNode *tree = build_test_tree();
    cout << "tree maxDistance : " << getMaxDistance(tree) << endl;
    return 0;
}
