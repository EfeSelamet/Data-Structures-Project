//Mehmet Efe Selamet 150122058
//Ali Arda Fistikci 150121006

//We used VScode as our code editor and mingw64 as our compiler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function prototypes
struct BSTNode* createNode(char *data);
int getKey(char *data);
int getFreq(char *data);
struct BSTNode* insertNode(struct BSTNode* root, char *data);
void preOrderTraversal(struct BSTNode* root);
struct BSTNode* find (struct BSTNode *p, int data);
int height(struct BSTNode* root);
struct BSTNode* rotation(struct BSTNode* root, int dataKey);
struct BSTNode* rotateLeft(struct BSTNode* root, struct BSTNode* parentPtr);
struct BSTNode* rotateRight(struct BSTNode* root, struct BSTNode* parentPtr);
struct BSTNode* findParent(struct BSTNode *node, int data);

//Binary Search Tree Node Structure
struct BSTNode {
    int key;
    int frequency;
    struct BSTNode *left;
    struct BSTNode *right;
};


int main() {
//this part of code is for checking the file for how many lines are there in the file so we can declair the size of array depending on it
    FILE *file1;
    char filename1[] = "input2.txt"; 
    
    // Open the file and check if it is empty
    file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        printf("No such file exists\n");
        return 1;
    }

    char string[10];
    int lineCount = 0;
    while (fgets(string, 10, file1) != NULL) {
        lineCount++;
    }

//this part of code places the data from the file to an array in the same order

    FILE *file2;
    char filename2[] = "input2.txt"; 
	
    // open the file and check if it is empty
    file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        printf("No such file exists\n");
        return 1;
    }

    char array[lineCount][10];
	int size = 0;
	
    // read data line by line from the file into the array
    while (fgets(array[size], 10, file2) != NULL) {
        size++;
        if (size > lineCount) {
            printf("Array size passed maximum limit\n");
            break;
        }
    }

    // Close the file
    fclose(file1);
    fclose(file2);

    //creats a node for the root of BST
    struct BSTNode* root = NULL;

    //creats the BST with the array
    for (int i = 0; i < lineCount-1; i++) {
        root = insertNode(root, array[i]);
    }

    preOrderTraversal(root);
    
    //asks a number from the user and changes the BST depending on the input
    int number;
    do{
        printf("\nEnter a key value(Enter zero to exit): ");
        scanf("%d",&number);

        find(root,number)->frequency +=1;
        root = rotation(root,number);
        preOrderTraversal(root);
    }while(number != 0);

    preOrderTraversal(root);
	
    return 0;
}

//returns the integer value of key that got from the input file
int getKey(char *data){
    char dataKey[10];
    int i;
    for(i = 0;i < 10;i++){
        if(data[i] != ' '){
            dataKey[i] = data[i];
        }
        else{
            break;
        }
    }
    return atoi(dataKey);
}


//creats nodes with the given key values from the array
struct BSTNode* createNode(char *data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    if (newNode == NULL) {
        return 0;
    }

    newNode->key = getKey(data);
    newNode->frequency = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}


//creats the BST by adding nodes to it
struct BSTNode* insertNode(struct BSTNode* root, char *data) {
    //checks if the root is empty, if yes then creats a node for it
    if (root == NULL) {
        return createNode(data);
    }

    //if the root is not empty then adds it to the BST depending on the key
    if (getKey(data) < root->key) {
        root->left = insertNode(root->left, data);
    } else if (getKey(data) > root->key) {
        root->right = insertNode(root->right, data);
    }


    return root;
}

//prints out the BST in preOrder
void preOrderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        printf("%d,%d ", root->key,root->frequency);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

//finds the node from the BST with the given key value
struct BSTNode* find(struct BSTNode *node, int data)
{
    if (node != NULL){
        if (data < node->key){
            find(node->left , data);
        }
        else if ( data > node->key){ 
            find(node->right , data);
            
        }
        else if(node->key == data) {
            return node;
        }
    }
}
//checks if the given nodes key value is equal to the given data
//this function helps finding the parent of the node with the given key value
int compData(struct BSTNode *node, int data)
{       
    if(node->key == data) {
        return 1;
    }
    else{
        return 0;
    }
}
//returns the parent of the given node
struct BSTNode* findParent(struct BSTNode *node, int data)
{
    if (node != NULL){
        if (data < node->key){
            if(compData(node->left, data)){
                return node;
            }
            else{
                findParent(node->left, data);
            }
        }
        else if ( data > node->key){ 
            if(compData(node->right, data)){
                return node;
            }
            else{
                findParent(node->right, data);
            }  
        }
    }
}

// Right rotation is used for greater frequency values in left child. 
struct BSTNode* rotateRight(struct BSTNode* root,struct BSTNode* parentPtr){
	struct BSTNode* childPtr;
	struct BSTNode* grandPtr = findParent(root,parentPtr->key);

	childPtr = parentPtr->left;
    parentPtr->left = childPtr->right;
    childPtr->right = parentPtr;

    if(parentPtr != root){
        if(grandPtr->key > childPtr->key){
            grandPtr->left = childPtr;
            return root;
        }
        else if(grandPtr->key < childPtr->key){
            grandPtr->right = childPtr;
            return root;
        }
    }
}
//Left rotation is used for greater frequency values in right child.
struct BSTNode* rotateLeft(struct BSTNode* root, struct BSTNode* parentPtr){
	struct BSTNode* childPtr;
    struct BSTNode* grandPtr = findParent(root,parentPtr->key);
	
	childPtr = parentPtr->right;
	parentPtr->right = childPtr->left;
	childPtr->left = parentPtr;

    if(parentPtr != root){
        if(grandPtr->key > childPtr->key){
            grandPtr->left = childPtr;
            return root;
        }
        else if(grandPtr->key < childPtr->key){
            grandPtr->right = childPtr;
            return root;
        }
    }
}

//changes the order of the BST depending on the frequency
struct BSTNode* rotation(struct BSTNode* root,int dataKey){
    struct BSTNode* keyNode;
    struct BSTNode* parentNode;
    if(find(root,dataKey) != root){

        int bool = 1;
        while(bool){
            keyNode = find(root,dataKey);
            parentNode = findParent(root,dataKey);

            if(parentNode->frequency < keyNode->frequency){
                if(parentNode->key < keyNode->key){
                    //if the parent is root we use a different method to rotate
                    if(parentNode == root){
                        struct BSTNode* Parent =  parentNode;
                        struct BSTNode* newRoot =  keyNode;
                        Parent->right = NULL;
                        Parent->right = newRoot->left;
                        newRoot->left = Parent;
                        root = newRoot; 
                        break;
                    }
                    else if(parentNode != root){ 
                        root = rotateLeft(root,parentNode);
                    }
                }

                else if(parentNode->key > keyNode->key){
                    if(parentNode == root){
                        //if the parent is root we use a different method to rotate
                        struct BSTNode* Parent =  parentNode;
                        struct BSTNode* newRoot =  keyNode;
                        Parent->left = NULL;
                        Parent->left = newRoot->right;
                        newRoot->right = Parent;
                        root = newRoot;
                        break;
                    }
                    else if(parentNode != root){ 
                        root = rotateRight(root,parentNode);
                    }
                }
            }
            else{
                bool = 0;
            }
        }
    }
    return root;
}
