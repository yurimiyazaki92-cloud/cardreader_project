#include "cardhandling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//date
void get_current_date(char *buf, size_t sz) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, sz, "%Y-%m-%d", tm_info);
}


//card
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


//file

void save_to_file(const AccessList *list, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: could not open file for writing.\n");
        return;
    }

    fwrite(&list->count, sizeof(int), 1, fp);
    fwrite(list->cards, sizeof(Card), list->count, fp);

    fclose(fp);
}

void load_from_file(AccessList *list, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return;
    }

    int count;
    fread(&count, sizeof(int), 1, fp);

    Card *cards = malloc(sizeof(Card) * count);
    fread(cards, sizeof(Card), count, fp);

    list->cards = cards;
    list->count = count;

    fclose(fp);
}