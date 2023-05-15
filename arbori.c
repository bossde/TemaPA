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
        fprintf(output,"%-32s - %.2f\n", root->TeamNode->name, root->TeamNode->team_points);
        PrintBST(root->left,output);
    }
}


