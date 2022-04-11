
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// structure for binary tree
typedef struct bintree{
    struct query* data;
    struct bintree* left;
    struct bintree* right;
}bintree;
// structure for query
typedef struct query{
    char word[21];
    int depth;
    int freq;
}query;


// function prototype
bintree* createNode(char* word);
bintree* binTree(char word[], bintree* root, int *numArr);
void MergeSort(query** arr, int start, int end);
void MergeArray(query** arr, int start, int mid, int end);
void MakeArray(bintree* root, query** arr, int* i);
void searchword(bintree* root, char word[]);
void print(query** arr, int index);
void freeTree(bintree* root);

int main(){
    int totalwords=0;
    int action;
    int *NumArr = calloc(1, sizeof(int));
    char word[21];
    // getting the number of words
    scanf("%d", &totalwords);
    // creating a root node for the tree
    bintree* root=NULL;
    while(totalwords!=0){
        scanf("%d %s", &action, word);
        // adding the names to the tree
        if(action==1){
            root=binTree(word, root, NumArr);
        }
        // searching in the tree
        if(action==2)
            searchword(root, word);
        
        totalwords --;
    }
    // allocating space for the array
    query** arr=(query**)malloc(*NumArr*(sizeof(query*)));
    // allocating space for index pointer
    int* index=calloc(1,sizeof(int));
    // transferring the data from the tree into the array
    MakeArray(root, arr, index);
    // number of the array indexes
    int num = *NumArr - 1;
    // free the memory
    free(NumArr);
    free(index);
    // sort our the array
    MergeSort(arr, 0, num);
    // print the result
    print(arr, num);
    // free the memory for the tree
    freeTree(root);
    //free the array
    free(arr);

    return 0;
}

//create new node if not existed
bintree* createNode(char* word)
{
    bintree* temp;
    // allocating space for the new node
    temp=(bintree*)malloc(sizeof(bintree));
    // set left and right child into NULL
    temp->left=NULL;
    temp->right=NULL;
    temp->data=(query*)malloc(sizeof(query));
    // setting data depth into 0
    temp->data->depth=0;
    // setting data frequancy into 1
    temp->data->freq=1;
    // copy the word into the structure
    strcpy(temp->data->word, word);
    
    return temp;
}
// making the binary tree
bintree* binTree(char word[], bintree* root, int *numArr)
{
    // make a root if not existed
    if(root==NULL){
        // keep track of the number of nodes
        *numArr = *numArr + 1;
        return createNode(word);
    }
    // checking for the order of the words
    int num=strcmp(word, root->data->word);
    // word goes to the left children
    if(num<0){
        root->left =  binTree(word,root->left, numArr);
        root->left->data->depth = (root->data->depth + 1);
    }
    // word goes to the right children
    if(num>0){
        root->right = binTree(word, root->right, numArr);
        root->right->data->depth = (root->data->depth + 1);
    }
    // word is equal root
    if(num==0)
        // increase the freqancy of the word
        root->data->freq++;
    return root;
}
void MergeSort(query** arr, int start, int end)
{
  // making sure there are more than one items to sort
  if(start<end)
  {
    int mid;
    // find the mid value
    mid=(start+end)/2;
    // sort the right side of array
    MergeSort(arr, start, mid);
    // sort the left side of array
    MergeSort(arr,mid+1, end);
    // put everything in one array
    MergeArray(arr, start, mid+1,end);

  }
}
// sort the array using merge sort
void MergeArray(query** arr, int start, int mid, int end)
{
  // finding the length of the array
  int length=end-start+1;
  // allocating enough space for the array
  query **temp=(query**)malloc(length*sizeof(query*));
  //index to the sorted arrays
  int i=start;
  int j=mid;
  //this is the index number of the temp array
  int index=0;
  // copying the sorted values into temp array
  while((i<mid) || (j<=end))
  {
    // filling up the first half of the array
    if(j>end || (i<mid && arr[i]->freq<arr[j]->freq))
    {
      temp[index]=arr[i];
      i++;
      index++;
    }
    else if((arr[i]->freq > arr[j]->freq) || i>= mid){
        temp[index]=arr[j];
        j++;
        index++;
    }
    else if(strcmp(arr[i]->word, arr[j]->word)<0){
        temp[index]= arr[j];
        j++;
        index++;
    }
        
    // filling up the second half of the array
    else
    {
      temp[index]=arr[i];
      i++;
      index++;
    }
  }
  //copy everthing into the main array
  for(int k=start; k<=end; k++)
  {
    arr[k]=temp[k-start];
  }
  // free the memory
  free(temp);
}
// transferring the data from the tree into the array
void MakeArray(bintree* root,query** arr, int* i)
{
    if(root !=NULL)
    {
        // putting the data into index i
        arr[*i]=root->data;
        // increase the index
        (*i) = (*i) + 1;
        // going to the left of tree
        MakeArray(root->left, arr, i);
        // going to the right of tree
        MakeArray(root->right, arr,i);
        
    }
}
void searchword(bintree* root, char word[])
{
    // word does not exist
    if (root==NULL){
        printf("-1 -1\n");
        return;}
    
    int num=strcmp(word, root->data->word);
    // word found
    if (num==0) {
        printf("%d %d\n", root->data->freq, root->data->depth);
    }
    // going to the left of the tree
    if(num<0)
        return searchword(root->left, word);
    // going to the right of the tree
    if(num>0)
        return searchword(root->right, word);
    
}
void print(query** arr, int index)
{
    int i=0;
    // printing the result in descending order
    for(i=index; i>= 0 ; i--)
        printf("%s %d\n", arr[i]->word, arr[i]->freq);
}
//free the tree recursively
void freeTree(bintree* root)
{
    // free the memory if root is not null
    if(root == NULL)
        return;
    free(root->data);
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
