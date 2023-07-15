#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "helping_functions.h"
#include "command_functions.h"
#include "process_function.h"
#include "data_base.h"

//------------------------------------------------------------------------------------

//Main

int main() {

    printf("    |  Advanced UT-Kala  |\n");

    // allocating list for data structure
    User* users = NULL;
    Product* products = NULL;
    users = user_alloc(users);
    products = product_alloc(products);

    //check for memory alloc
    int r = check_memory_alloc(users, products);
    if (r == -1)
        return -1;

    //opening data base
    FILE* users_list = NULL;
    FILE* products_list = NULL;

    //loading data base
    load(users, products, users_list, products_list);

    utkala(users, products);     // main process

    //save data base
    save(users, products, users_list, products_list);

    return 0;
}