#include "header.h"

TreeNode* newNode(Team* TeamToAdd){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->TeamNode = TeamToAdd;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insert(TreeNode* node, Team* TeamToAdd){
    if(node == NULL) return newNode(TeamToAdd);
    else{
    if(node->TeamNode->team_points > TeamToAdd->team_points) node->left = insert(node->left,TeamToAdd);
    else if(node->TeamNode->team_points < TeamToAdd->team_points) node->right = insert(node->right,TeamToAdd);
    else if(node->TeamNode->team_points == TeamToAdd->team_points){
        if(strcmp(node->TeamNode->name,TeamToAdd->name) > 0) node->left = insert(node->left,TeamToAdd);
        else if(strcmp(node->TeamNode->name,TeamToAdd->name) < 0) node->right = insert(node->right,TeamToAdd);
        }
    }
    return node;
}

void PrintBST(TreeNode* root, FILE* output){
    if(root){
        PrintBST(root->right,output);
        fprintf(output,"%-32s  -  %.2f\n", root->TeamNode->name, root->TeamNode->team_points);
        PrintBST(root->left,output);
    }
}

int height(TreeNode* node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    if(node->left == 0 && node->right == 0) return 0;
    else return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int nodeHeight(TreeNode* root){
    if(root == NULL) return -1;
    else return root->height;
}

TreeNode* RightRotation(TreeNode* root){
    TreeNode* LeftRoot = root->left;
    TreeNode* subTree = LeftRoot->right;

    LeftRoot->right = root;
    root->left = subTree;

    if(nodeHeight(root->left) > nodeHeight(root->right)){
        root->height = nodeHeight(root->left) + 1;
    }
    else root->height = nodeHeight(root->right) + 1;

    if(nodeHeight(LeftRoot->left) > nodeHeight(LeftRoot->right)){
        LeftRoot->height = nodeHeight(LeftRoot->left) + 1;
    }
    else LeftRoot->height = nodeHeight(LeftRoot->right) + 1;

    return LeftRoot;
}

TreeNode* LeftRotation(TreeNode* root){
    TreeNode* RightRoot = root->right;
    TreeNode* subTree = RightRoot->left;

    RightRoot->right = root;
    root->right = subTree;

    if(nodeHeight(root->left) > nodeHeight(root->right)){
        root->height = nodeHeight(root->left) + 1;
    }
    else root->height = nodeHeight(root->right) + 1;

    if(nodeHeight(RightRoot->left) > nodeHeight(RightRoot->right)){
        RightRoot->height = nodeHeight(RightRoot->left) + 1;
    }
    else RightRoot->height = nodeHeight(RightRoot->right) + 1;

    return RightRoot;
}

TreeNode* LRRotation(TreeNode* root){
    root->left = LeftRotation(root->left);
    return RightRotation(root);
}

TreeNode* RLRotation(TreeNode* root){
    root->right = RightRotation(root->right);
    return LeftRotation(root);
}

void FindHeights(TreeNode** root) {
    if (*root == NULL) return;
    else {
        (*root)->height = height(*root);
        FindHeights(&((*root)->left));
        FindHeights(&((*root)->right));
    }
}

void PrintHeights(TreeNode* root, FILE* output){
    if(root){
        PrintHeights(root->right,output);
        fprintf(output,"%d %s\n",root->height,root->TeamNode->name);
        PrintHeights(root->left,output);
    }
}

int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return nodeHeight(node->left) - nodeHeight(node->right);
}

TreeNode* balance(TreeNode* root) {
    if (root == NULL) return root;

    int balanceFactor = getBalance(root);

    if (balanceFactor > 1 && getBalance(root->left) >= 0)
        return RightRotation(root);

    if (balanceFactor < -1 && getBalance(root->right) <= 0)
        return LeftRotation(root);

    if (balanceFactor > 1 && getBalance(root->left) < 0)
        return LRRotation(root);

    if (balanceFactor < -1 && getBalance(root->right) > 0)
        return RLRotation(root);

    return root;
}


void BalanceAVLTree(TreeNode** root) {
    if (*root == NULL) return;
    else {
        BalanceAVLTree(&((*root)->left));
        BalanceAVLTree(&((*root)->right));
        *root = balance(*root);
    }
}

void PrintLevel2(TreeNode* root, FILE* output) {
    if (root == NULL) return;
    if (root->left != NULL) {
        if (root->left->left != NULL) {
            fprintf(output, "%-32s\n", root->left->left->TeamNode->name);
        }
        if (root->left->right != NULL) {
            fprintf(output, "%-32s\n", root->left->right->TeamNode->name);
        }
    }

    if (root->right != NULL) {
        if (root->right->left != NULL) {
            fprintf(output, "%-32s\n", root->right->left->TeamNode->name);
        }
        if (root->right->right != NULL) {
            fprintf(output, "%-32s\n", root->right->right->TeamNode->name);
        }
    }
}

TreeNode* InsertInAvl(TreeNode* root, Team* TeamToAdd){
    if(root == NULL){
        root = (TreeNode*) malloc(sizeof(TreeNode));
        root->TeamNode = TeamToAdd;
        root->height = 0;
        root->left = root->right = 0;
    }

    if(TeamToAdd->team_points < root->TeamNode->team_points){
        root->left = InsertInAvl(root->left,TeamToAdd);
    }

    else if(TeamToAdd->team_points > root->TeamNode->team_points){
        root->right = InsertInAvl(root->right,TeamToAdd);
    }

    else if(TeamToAdd->team_points == root->TeamNode->team_points){
        if(strcmp(TeamToAdd->name,root->TeamNode->name) < 0){
            root->left = InsertInAvl(root->left,TeamToAdd);
        }
        else if(strcmp(TeamToAdd->name,root->TeamNode->name) > 0){
            root->right = InsertInAvl(root->right,TeamToAdd);
        }
    }

    root->height = 1 + fmax(nodeHeight(root->left),nodeHeight(root->right));

    int k = nodeHeight(root->left) - nodeHeight(root->right);

    if(k > 1){
        if(TeamToAdd->team_points < root->left->TeamNode->team_points) return RightRotation(root);
        else if(TeamToAdd->team_points == root->left->TeamNode->team_points){
            if(strcmp(TeamToAdd->name,root->left->TeamNode->name) < 0) return RightRotation(root);
        }
    }
    if(k < -1){
        if(TeamToAdd->team_points > root->right->TeamNode->team_points) return LeftRotation(root);
        else if(TeamToAdd->team_points == root->right->TeamNode->team_points){
            if(strcmp(TeamToAdd->name,root->left->TeamNode->name) < 0) return LeftRotation(root);
        }
    }
    if(k > 1 && TeamToAdd->team_points > root->left->TeamNode->team_points) return RLRotation(root);
    if(k < -1 && TeamToAdd->team_points < root->right->TeamNode->team_points) return LRRotation(root);

    return root;
}

