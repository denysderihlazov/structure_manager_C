#include <stdio.h>
#include <stdlib.h>

#define HELP_INFO \
" ---struct manager--- \n"\
"   Usage instructions:\n\n" \
"1) To add an element to the structure:\n" \
"   Run: ./main <data>\n" \
"   Example: ./main -22\n" \
"\nAttention: \n\n" \
"The <data> of structure must be an integer!\n"


struct item {
    int data;
    struct item *next;
};

void printHelpInfo()
{
    printf(HELP_INFO);
    exit(0);
}

int strCompare(char *str1, char *str2)
{
    int i = 0;
    while(*(str1+i) != '\0' && *(str2+i) != '\0') {
        if((int)*(str1+i) == (int)*(str2+i) && (int)*(str1+i+1) == (int)*(str2+i+1)) {
            i++;
        } else {
            return 0;
        }
    }
    return 1;
}

int parseStrToInt(char *str)
{
    int answer = 0;
    char *args;
    int isNegative = 0;

    if(*str == '-') {
        isNegative = 1;
        str++; // to skip minus sign
    }
    
    for(args = str; *args != '\0'; ++args) {
        if(((int)*args - (int)'0') < 0 || ((int)*args - (int)'0') > 9) {
            fprintf(stderr, "Is not a digit!\n");
            printHelpInfo();
        }

        if(answer == 0) {
            answer += (int)*args - (int)'0';
        } else {
            answer = answer*10 + (int)*args - (int)'0';
        }
    }

    if(isNegative) {
        answer *= -1;
    }
    
    return answer;
}

int countStructSum(struct item **Tree)
{
    int sum = 0;
    const struct item *tmp = *Tree;
    while(tmp != NULL) {
        sum += tmp->data;
        tmp = tmp->next;
    }
    return sum;
}

int *searchFirstElByData(int dataToSearch, struct item *head)
{
    struct item *currentNode = head;
    
    while(currentNode != NULL) {
        if(currentNode->data == dataToSearch) {
            return (void *)currentNode;
        }
        currentNode = currentNode->next;
    }

    return NULL; // returns null when nothing had found
}

// delete all Nodes by data identifier
void deleteAllNodesByData(int dataToDelete, struct item **head)
{
    struct item *tempNode;
    struct item *currentNode = *head;

    // Delete all comparisons at the beggining
    while (currentNode != NULL && currentNode->data == dataToDelete) {
        tempNode = currentNode;
        *head = currentNode->next;
        currentNode = currentNode->next;
        free(tempNode);
    }

    while(currentNode != NULL && currentNode->next != NULL) {
        if(currentNode->next->data == dataToDelete) {
            tempNode = currentNode->next;
            currentNode->next = tempNode->next;
            free(tempNode);
        } else {
            currentNode = currentNode->next;
        }
    }
}

void insertNodeByIndex(int dataToInsert, int indexToInsert, struct item **head)
{
    if (indexToInsert < 0) {
        return; // Wrong index
    }

    struct item *newNode = malloc(sizeof(struct item));
    if(newNode == NULL) {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    newNode->data = dataToInsert;
    newNode->next = NULL;

    if(indexToInsert == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct item *prevNode = NULL;
    struct item *currentNode = *head;
    int currentIndex = 0;

    while(currentNode != NULL && currentIndex < indexToInsert) {
        prevNode = currentNode;
        currentNode = currentNode->next;
        currentIndex++;
    }

    if(currentIndex == indexToInsert) {
        prevNode->next = newNode;
        newNode->next = currentNode;
    } else {
        free(newNode); // Out of arr size
    }
}

void addNode(int currentData, struct item **head)
{
    struct item *newNode = malloc(sizeof(struct item));
    newNode->data = currentData;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
    } else {
        struct item *currentNode = *head;
        while(currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("Too few arguments\n");
        printHelpInfo();
    }

    if(strCompare(argv[1], "-h") || strCompare(argv[1], "--help")) {
        printHelpInfo();
    }

    struct item *Tree = malloc(sizeof(struct item));
    Tree->data = 0;
    Tree->next = NULL;

    // add an elem to Tree struct
    if(argc == 2) {
        int currentData = parseStrToInt(argv[1]);

        addNode(currentData+2, &Tree);
        addNode(currentData+1, &Tree);
        addNode(currentData, &Tree);
        addNode(currentData+2, &Tree);
        addNode(currentData+1, &Tree);
        addNode(currentData+1, &Tree);
        addNode(currentData+1, &Tree);
    }
    
    printf("The sum is: %d\n", countStructSum(&Tree));
    if(searchFirstElByData(15, Tree)) {
        printf("Your element %d found and its addres is: %p\n", 15, searchFirstElByData(15, Tree));
    }
    deleteAllNodesByData(12, &Tree);
    insertNodeByIndex(15, 1, &Tree);
    printf("The sum is: %d\n", countStructSum(&Tree));

    while(Tree != NULL) {
        struct item *temp = Tree;
        Tree = Tree->next;
        free(temp);
    }

    return 0;
}
