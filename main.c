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

struct item *processStructure(int structureData, struct item Tree)
{
    // check if structure exists
    // create structure el
    // if empty -> init
    //  data - argv[1]
    //  next = NULL
    // if prev el == TRUE -> prev.next = current
    
    struct item *tmp = &Tree;


    return tmp;
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

    // add el to Tree struct
    if(argc == 2) {
        struct item *Tree = malloc(sizeof(struct item));
        int currentData = parseStrToInt(argv[1]);

        Tree = processStructure(currentData, *Tree);
    }

    return 0;
}

// init structure
// add structure
// delete structure
// search el through the structure
// insert structure
