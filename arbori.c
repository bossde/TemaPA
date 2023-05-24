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

void inorderTraversal(TreeNode* root, Team** head)
{
    //prin intermediul acestei functii, salvez echipele de la task-ul 4 intr-o lista, parcurgand arborele in inordine
    if (root == NULL)
        return;
  
    inorderTraversal(root->left, head);
  
    Team* newNode = (Team*)malloc(sizeof(Team));
    newNode->name = root->TeamNode->name;
    newNode->numberOfPlayers = root->TeamNode->numberOfPlayers;
    newNode->team_points = root->TeamNode->team_points;
    newNode->Players = root->TeamNode->Players;
    newNode->nextTeam = NULL;
  
    if (*head == NULL) {
        *head = newNode;
    } else {
        Team* current = *head;
        while (current->nextTeam != NULL) {
            current = current->nextTeam;
        }
        current->nextTeam = newNode;
    }
  
    inorderTraversal(root->right, head);
}


int nodeHeight(TreeNode* root){
    if(root == NULL) return -1;
    else return root->height;
}

TreeNode* RightRotation(TreeNode* z){
    TreeNode* y = z->left;
    TreeNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max(nodeHeight(z->left),nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right)) + 1;

    return y;
}

TreeNode* LeftRotation(TreeNode* z){
    TreeNode* y = z->right;
    TreeNode* T2 = y->left;
    y->left = z;
    z->right = T2;

    z->height = max(nodeHeight(z->left),nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right)) + 1;

    return y;
}

TreeNode* LRRotation(TreeNode* z){
    z->left = LeftRotation(z->left);
    return RightRotation(z);
}

TreeNode* RLRotation(TreeNode* z){
    z->right = RightRotation(z->right);
    return LeftRotation(z);
}

void PrintLevel2(TreeNode* root, FILE* output) {
    if (root == NULL) return;

    if (root->right != NULL) {
        if (root->right->right != NULL) {
            fprintf(output, "%-32s\n", root->right->right->TeamNode->name);
        }
        if (root->right->left != NULL) {
            fprintf(output, "%-32s\n", root->right->left->TeamNode->name);
        }
    }

    if (root->left != NULL) {
        if (root->left->right != NULL) {
            fprintf(output, "%-32s\n", root->left->right->TeamNode->name);
        }
        if (root->left->left != NULL) {
            fprintf(output, "%-32s\n", root->left->left->TeamNode->name);
        }
    }
}

TreeNode* InsertInAvl(TreeNode* node, Team* TeamToAdd){
    if(node == NULL){
        node = (TreeNode*) malloc(sizeof(TreeNode));
        node->TeamNode = TeamToAdd;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }

    if(TeamToAdd->team_points < node->TeamNode->team_points) node->left = InsertInAvl(node->left,TeamToAdd);
    else if(TeamToAdd->team_points > node->TeamNode->team_points) node->right = InsertInAvl(node->right,TeamToAdd);
    else if(TeamToAdd->team_points == node->TeamNode->team_points){
        if(strcmp(node->TeamNode->name,TeamToAdd->name) > 0) node->left = InsertInAvl(node->left,TeamToAdd);
        else if(strcmp(node->TeamNode->name,TeamToAdd->name) < 0) node->right = InsertInAvl(node->right,TeamToAdd);
}

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    int k = nodeHeight(node->left) - nodeHeight(node->right);

    if(k > 1){
        if(TeamToAdd->team_points < node->left->TeamNode->team_points) return RightRotation(node);
        else if(TeamToAdd->team_points == node->left->TeamNode->team_points){
            if(strcmp(node->left->TeamNode->name,TeamToAdd->name) > 0) return RightRotation(node);
        }
    }

    if(k < -1){
        if(TeamToAdd->team_points > node->right->TeamNode->team_points) return LeftRotation(node);
        else if(TeamToAdd->team_points == node->right->TeamNode->team_points){
            if(strcmp(node->left->TeamNode->name,TeamToAdd->name) < 0) return LeftRotation(node);
        }
    }

    if(k > 1 && TeamToAdd->team_points > node->left->TeamNode->team_points) return LRRotation(node);
    if(k < -1 && TeamToAdd->team_points < node->right->TeamNode->team_points) return RLRotation(node);

    return node;
}



