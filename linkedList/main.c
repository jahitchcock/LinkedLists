//Joshua Hitchcock
//Inventory program using linked lists

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void insert(int *, int *, int *);
void input();
void inputOne();
struct Parts *Locate (int *);
char menu();
void List();
struct Parts *Find();
void modify();
struct Parts *FindLast(int *);
void delRecord();

//Structure declaration for inventory items
struct Parts
{
    int partNum, quantity, price;
    struct Parts *nextaddr;

};

//declaration of pointer start of linked list
struct Parts *firstPart;



int main()
{
    char choice=menu();
    while (choice !='G')
    {

        switch (choice)
        {
            case 'A':
                input();
                break;
            case 'B':
                List();
                break;
            case 'C':
                Find();
                break;
            case 'D':
                inputOne();
                break;
            case 'E':
                modify();
                break;
            case 'F':
                delRecord();
                break;
            default:
                printf("Invalid Entry!\n\n");
                break;
        }
        choice=menu();

    }
    return 0;
}

//Menu for program
char menu()
{
    char choice;
    printf("\nWould You like to\n");
    printf("A. Enter information into inventory\n");
    printf("B. See all of the inventory\n");
    printf("C. Look-up an item\n");
    printf("D. Add an Item\n");
    printf("E. Change an Item\n");
    printf("F. Remove an Item\n");
    printf("G. Exit\n");
    printf("Enter A-G: ");
    scanf("\n%c",&choice);
    choice=toupper(choice);
    return choice;
}

//Input information to be added to linked list.
void input()
{
    int partNum, quantity, price;
    printf("Enter records one at a time.");
    printf("\nEnter -1 for partnumber to stop.");
    while (1)
    {
        printf("\nEnter part number:");
        scanf("%d",&partNum);
        if (partNum==-1)
            break;
        printf("Enter part quantity:");
        scanf("%d",&quantity);
        printf("Enter part price:");
        scanf("%d",&price);
            insert(&partNum,&quantity,&price);
    }
}

//Inserts data into linked list
void insert (int *partNum, int *quantity, int *price)
{
    struct Parts *newaddr,*here;

    newaddr=(struct Parts *) malloc(sizeof(struct Parts));
    if (firstPart==NULL)
    {
        newaddr->nextaddr=NULL;
        firstPart=newaddr;
    }
    else if (*partNum < firstPart->partNum)
    {
        newaddr->nextaddr = firstPart;
        firstPart = newaddr;
    }
    else
    {
        here = Locate(partNum);
        newaddr->nextaddr=here->nextaddr;
        here->nextaddr=newaddr;
    }
    newaddr->partNum=*partNum;
    newaddr->price=*price;
    newaddr->quantity=*quantity;
}

//Finds the correct insertion point for inventory input
struct Parts *Locate(int *partNum)
{
    struct Parts *one, *two;
    one=firstPart;
    two = one->nextaddr;

    if (two==NULL)
    return(one);
    while(1)
    {
        if (*partNum<two->partNum)
        break;
        else if (two->nextaddr==NULL)
        {
            one=two;
            break;
        }
        else
        {
            one=two;
            two=one->nextaddr;
        }
    }
    return(one);
}

//Displays entire linked list
void List()
{
    struct Parts *contents;

    contents=firstPart;
    printf("The Parts Inventory:");
    while (contents!=NULL)
    {
        printf("\nPart Number: %d",contents->partNum);
        printf("\nQuantity   : %d",contents->quantity);
        printf("\nPrice      : $%d\n",contents->price);
        contents=contents->nextaddr;
    }
}

//Displays one item from linked list
void inputOne()
{
    int partNum, quantity, price;
    printf("Enter record.");

        printf("\nEnter part number:");
        scanf("%d",&partNum);
        printf("Enter part quantity:");
        scanf("%d",&quantity);
        printf("Enter part price:");
        scanf("%d",&price);
        insert(&partNum,&quantity,&price);
    }

//Finds a single item in the linked list
struct Parts *Find()
{
   int part;
   struct Parts *one, *two;

   printf("\nEnter record to lookup: ");
   scanf("%d",&part);

    one=firstPart;
    two = one->nextaddr;

    if (two!=NULL)
    {
        while(1)
        {
        if (part==one->partNum)
        break;
        else if (two->nextaddr==NULL)
            {
            one=two;
            break;
            }
        else
            {
            one=two;
            two=one->nextaddr;
            }
        }
    }
        printf("\nPart Number: %d",one->partNum);
        printf("\nQuantity   : %d",one->quantity);
        printf("\nPrice      : $%d\n",one->price);
        return(one);

}

//Edit a single item in the list
void modify()
{
    struct Parts *item;
    int entry;
    item=Find();
    printf("\nEnter new Quantity: ");
    scanf("%d",&entry);
    item->quantity=entry;
    printf("\nEnter new price   : ");
    scanf("%d",&entry);
    item->price=entry;
}

//Attempts to find address of previous part in linked list
struct Parts *FindLast(int *partNum)
{
    struct Parts *one, *two, *zero;
    one=firstPart;
    two = one->nextaddr;
    zero=one;

    if (two==NULL)
    return(zero);
    while(1)
    {
        if (*partNum<two->partNum)
        break;
        else if (two->nextaddr==NULL)
        {
            zero=one;
            one=two;
            break;
        }
        else
        {
            zero=one;
            one=two;
            two=one->nextaddr;
        }
    }
    return(zero);
}

//Attempts to remove a single record
void delRecord()
{
    struct Parts *item, *prev, *next;
    item=Find();
    next=item->nextaddr;
    prev=FindLast(&item->partNum);
    prev->nextaddr=next;
    free(item);
}
