#include <stdio.h>
#include "unistd.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
// 
typedef struct {
    int card_number;  // card number
    bool access;            // Access (True,False)
    char date[20];         // date (YYYY-MM-DD)
} Card;

typedef struct {
    Card *cards;  // card details
    int count;    // number of cards
} AccessList;

void get_current_date(char *buf, size_t sz) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, sz, "%Y-%m-%d", tm_info);
}


void add_card(AccessList *list, int card_number){

    int new_count = list->count + 1;
    Card *new_cards = malloc(sizeof(Card) * new_count);

    for (int i = 0; i < list->count; i++) {
        new_cards[i] = list->cards[i];
    }
    new_cards[new_count - 1].card_number = card_number;
    new_cards[new_count - 1].access = true;
    get_current_date(new_cards[new_count - 1].date, sizeof(new_cards[new_count - 1].date));

    free(list->cards);
    list->cards = new_cards;
    list->count = new_count;

    return;


}

int find_card(AccessList *list, const int *card_number) {
    for (int i = 0; i < list->count; i++) {
        if (list->cards[i].card_number == *card_number)
            return i;
    }
    return -1;
}


bool check_access(AccessList *list, const int *card_number){
    int i = find_card(list, card_number);
    if(i == -1) return false;
    return list->cards[i].access;
}

void give_access(AccessList *list, const int *card_number) {
    int i = find_card(list, card_number);
    if(i != -1) list->cards[i].access = true;
}

void remove_access(AccessList *list, const int *card_number) {
    int i = find_card(list, card_number);
    if(i != -1) list->cards[i].access = false;
}

int input_int(const char *msg) {
    char buf[64];
    int value;

    while (1) {
        printf("%s", msg);

        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        if (sscanf(buf, "%d", &value) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a number.\n");
    }
}



int main(void) {

    AccessList list = {NULL, 0};
    int cardnumber;

    while(1){
        int choice;

        printf("\nAdmin meny\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("5. FAKE TEST SCAN CARD\n");
        printf("=============================\n");

        choice = input_int("Choose a number (1-5) ");

        switch (choice) {
            case 1:
                printf("CURRENTLY LAMP IS GREEN\n");
                sleep(3);
                break;

            case 2:
                printf("List all cards in system...\n");
                for (int i = 0; i < list.count; i++) {
                    printf("%d: cardnumber:%d | access(1=True):%d | date of register:%s\n",
                        i + 1,
                        list.cards[i].card_number,
                        list.cards[i].access,
                        list.cards[i].date);
                    }
                printf("Press Enter to continue\n");
                getchar();

                break;

            case 3:

                cardnumber = input_int("Enter card number: ");

                if (find_card(&list, &cardnumber) != -1 && check_access(&list, &cardnumber) == true){
                    int choice3 = input_int("This card has access.Enter 1 for access, 2 for no access. \n");
                    switch(choice3){
                        case 1:
                        break;
                        case 2:
                        remove_access(&list, &cardnumber);
                        printf("Removed access\n");
                        break;
                        default:
                        printf("Invalid selection\n");
                        break;
                    }
                }
                else if(find_card(&list, &cardnumber) != -1 && check_access(&list, &cardnumber) != true){
                    int choice4 =input_int("This card doesn't have access.Enter 1 for access, 2 for no access. \n");
                    switch(choice4){
                        case 1:
                        give_access(&list, &cardnumber);
                        printf("Access given\n");
                        break;
                        case 2:
                        break;
                        default:
                        printf("Invalid selection\n");
                        break;
                    }
                }
                else{
                    printf("The card is not registerd.Do you want to add the card?\n");
                    int choice5 = input_int("Press 1 for adding, press 2 for cancel. \n");
                    switch(choice5){
                        case 1:
                        add_card(&list, cardnumber);
                        printf("the card is registered\n");
                        break;
                        case 2:
                        break;
                        default:
                        printf("Invalid selection\n");
                        break;

                    }

                }
                printf("Press Enter to continue\n");
                getchar();
                break;
            case 4:
                printf("Exit...\n");
                return 0;
                break;
            case 5:
                printf("FAKE TEST SCAN CARD\n");
                cardnumber = input_int("Enter card number: ");
                if (find_card(&list, &cardnumber) != -1 && check_access(&list, &cardnumber) == true){
                    printf("CURRENTLY LAMP IS: Green\n");
                }
                else if(find_card(&list, &cardnumber) != -1 && check_access(&list, &cardnumber) != true){
                    printf("CURRENTLY LAMP IS: Red\n");
                }
                else{
                    printf("CURRENTLY LAMP IS: Off\n");
                }
                printf("Press Enter to continue\n");
                getchar();
                break;

            default:
                printf("Invalid selection\n");
                printf("Press Enter to continue\n");
                getchar();
                break;
        }
    }

    return 0;
}
