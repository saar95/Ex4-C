#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define WORD 254
#define LINE 255
#define NUM_LETTERS ((int)26)


typedef struct node {
char letter;
long unsigned int count;
struct node* children[NUM_LETTERS];
} node;


char* getword(char w[]) {
	char* t = malloc(sizeof(char)*WORD+1);
    int i=0;
    if (t!=NULL)
    {
        while (w[i] != '\n' && w[i] != ' ' && w[i] != '\0' && (int)w[i] != 13){
		t[i]=w[i];
		i++;
        }
        t[i] = '\0';
	    
    }
    return t;
}

char* realWord(char w[]){  //need to get a word from getword
    int j=0;    
    for(int i = 0; w[i]!='\0'; i++){
        w[i] = tolower(w[i]);
    }
   	char* word = malloc(sizeof(char)*WORD+1);
    if(word==NULL)
        return "-1";
    for (int i = 0; w[i]!='\0'; i++)  //97-122  
    {
        if (w[i]>=97 && w[i]<=122)
        {
            word[j]=w[i];
            j++;
        }
    }   
    word[j]='\0';
    return word;    
}
void initilazeNode(node *node, char letter){

        node->letter=letter;
        node->count=0;
        for (int i = 0; i < NUM_LETTERS; i++)
        {
            node->children[i]=NULL;
        }
}

void printAtoZ(node *node, char* word){
    if(!node){
        return;
    }
    int len =0;
    if(node->letter != ' '){
        len = strlen(word);
        word[len] = node->letter;
        word[len+1] = '\0';
    }

    bool flag = false;
    if(node->count > 0){
        printf("%s %ld \n", word, node->count);
        flag = true;
    }

    if(node->count == 0 || flag == true){
       for(int i=0; i<NUM_LETTERS; i++){
           printAtoZ(node->children[i], word);
       }
    }

    if(node->letter != ' ')
        word[len] = '\0';

}

void destroy(node* node){
    if(!node){
        return;
    }
    for(int i=0; i<NUM_LETTERS; i++){
           destroy(node->children[i]);
    }
    free(node);
}

int main(int argc, char const *argv[])
{   char buff [LINE];
    int ascii=0;
    int count=0;

    node* head = malloc(sizeof(node));
    if(head==NULL)
        return -1;
    initilazeNode(head,' ');
    char* tempword;
    char* word;
    node* tempNode;
    while (fgets(buff, LINE ,stdin)!=NULL)
    {
        count=0;
        while(count < strlen(buff)){
   		    tempword = getword(buff+count);
            word=realWord(tempword);
            node* current_node=head;
            for (int i = 0; word[i]!='\0'; i++){
                ascii=(int)word[i];
                tempNode=current_node->children[ascii-97];
                if(!tempNode ){
                    tempNode = malloc(sizeof(*tempNode));
                    if(!tempNode)
                        return -1;
                    initilazeNode(tempNode,word[i]);
                    current_node->children[ascii-97]=tempNode;
                }
                if (word[i+1]=='\0')
                {
                    tempNode->count +=1;
                    current_node=head;
                    break;
                }
                current_node=current_node->children[ascii-97];

            }
            count += strlen(tempword) + 1;
            free(tempword);
            free(word);
        }    
    }

    char* final_word = malloc(sizeof(char)*WORD+1);
    if(final_word==NULL)
        return ' ';

    final_word[0] = '\0';
    printAtoZ(head,final_word);
    free(final_word);

    destroy(head);
    return 0;
}

