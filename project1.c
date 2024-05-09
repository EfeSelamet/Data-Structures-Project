//Mehmet Efe Selamet 150122058
//Ali Arda Fistikci 150121006

//We used VScode as our code editor and mingw64 as our compiler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function prototypes
int compFreq(char string1[],char string2[]);
struct BSTNode* createNode(char *data);
int getKey(char *data);
int getFreq(char *data);
struct BSTNode* insertNode(struct BSTNode* root, char *data);
void preOrderTraversal(struct BSTNode* root);

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
    char filename1[] = "input.txt"; 
    int size = 0;

    // Open the file and check if it is empty
    file1 = fopen(filename1, "r");
    if (file1 == NULL) {
        printf("Error occured when opening file %s\n", filename1);
        return 1;
    }

    char string[10];
    int lineCount = 0;
    while (fgets(string, 10, file1) != NULL) {
        lineCount++;
    }

    //this part of code places the data from the file to an array in the same order

    FILE *file2;
    char filename2[] = "input.txt"; 

    // open the file and check if it is empty
    file2 = fopen(filename2, "r");
    if (file2 == NULL) {
        printf("Error occured when opening file %s\n", filename2);
        return 1;
    }

    char array[lineCount][10];

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

    //uses an algorithm to sort the array depending on the frequency
    int i, j;
    char temp[10];
    for (i = 0; i < lineCount; i++) { 
        for (j = i + 1; j < lineCount; j++) {  
            if (compFreq(array[i],array[j])) { 
                strcpy(temp,array[i]); 
                strcpy(array[i],array[j]); 
                strcpy(array[j],temp); 
            } 
        } 
    }


    //prints the array
    for (int i = 0; i < size; i++) {
        printf("%s", array[i]);
    }

    //creats a node for the root of BST
    struct BSTNode* root = NULL;

    //creats the BST with the array
    for (int i = 0; i < lineCount-1; i++) {
        root = insertNode(root, array[i]);
    }

    preOrderTraversal(root);
    return 0;
}


//compares the frequency values of indeces from array to sort the array
int compFreq(char string1[],char string2[]){
    char newString1[10];
    char newString2[10];
    int value1;
    int value2;

    int i,j;
    for(i = 0;i < 10;i++){
        if(string1[i] == ' '){
            for(i++,j = 0;i < 10;i++,j++){
                newString1[j] = string1[i];
            }
        }
    }

    for(i = 0;i < 10;i++){
        if(string2[i] == ' '){
            for(i++,j = 0;i < 10;i++,j++){
                newString2[j] = string2[i];
            }
        }
    }
    
    value1 = atoi(newString1);
    value2 = atoi(newString2);

    if(value1 < value2){
        return 1;
    }
    else{
        return 0;
    }
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

//returns the integer value of frequency that got from the input file
int getFreq(char *data){
    char dataFreq[10];
    int i,j;
    for(i = 0;i < 10;i++){
        if(data[i] == ' '){
            for(i++,j = 0;i < 10;i++,j++){
                dataFreq[j] = data[i];
            }
        }
    }
    return atoi(dataFreq);
}


//creats nodes with the given key values from the array
struct BSTNode* createNode(char *data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    if (newNode == NULL) {
        return 0;
    }

    newNode->key = getKey(data);
    newNode->frequency = getFreq(data);
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
        printf("%d ", root->key);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}