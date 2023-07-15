#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//data base

/*             by having a data base all the datas from the program will be saved
          this data base contains program datas :   1-users   2-products
    1-load : read data from the file and add to the list    (start)
    2-save : write data in the list in the file      (end)
*/

int load(User* users, Product* products, FILE* users_list, FILE* products_list) {
    Product* pro;
    User* usr;
    //products
    int counter;
    int i;
    int len;
    pro = products;
    pro = pro->next;
    products_list = fopen("goods.txt", "r");
    users_list = fopen("users.txt", "r");
    if (users_list == NULL || products_list == NULL) {
        return -1;
    }
    int line_num = 0;
    while (1) {
        int c = getc(products_list);
        if (c == '\n')
            line_num++;
        if (c == EOF)
            break;
    }
    len = ftell(products_list);
    fseek(products_list, 0, SEEK_SET);
    for (i = 0; i < line_num - 1; i++) {
        pro->name = (char*)malloc((len) * sizeof(char));
        pro->seller_name = (char*)malloc((len) * sizeof(char));
        fscanf(products_list, "%s %d %d %s %d %d %d", pro->name, &(pro->price), &(pro->count), pro->seller_name, &(pro->rate), &(pro->sum_of_rates), &(pro->number_of_rates));
        pro->next = (Product*)malloc(sizeof(Product));
        pro->next->next = NULL;
        pro = pro->next;
    }
    fclose(products_list);
    //users
    len = ftell(users_list);
    usr = users;
    int role_type, c;
    while (1) {
        int c = getc(users_list);
        if (c == '\n')
            line_num++;
        if (c == EOF)
            break;
    }
    fseek(users_list, 0, SEEK_SET);
    for (i = 0; i < line_num - 1; i++) {
        c = getc(users_list);
        if (c == 'u') {
            usr = usr->next;
            role_type = strcmp(usr->role, "Buyer");
            usr->name = (char*)malloc(len * sizeof(char));
            usr->password = (char*)malloc(len * sizeof(char));
            fscanf(users_list, "%s %s %s %d", usr->name, usr->password, usr->role, &(usr->money));
            //allocating users products list
            usr->products = (Product*)malloc(sizeof(Product));
            usr->products->name = (char*)malloc(sizeof(char));
            usr->products->seller_name = (char*)malloc(sizeof(char));
            usr->products->next = (Product*)malloc(sizeof(Product));
            usr->products->next->next = NULL;
            // assign
            pro = usr->products;
            //extending users list
            usr->next = (User*)malloc(sizeof(User));
            usr->next->next = NULL;
        }
        if (c == 'p') {
            if (role_type == 0) {
                pro = pro->next;
                pro->name = (char*)malloc(len * sizeof(char));
                pro->seller_name = (char*)malloc(len * sizeof(char));
                fscanf(users_list, "%s %d %d %s %d", pro->name, &(pro->price), &(pro->count), pro->seller_name, &(pro->rate_permission));
                pro->next = (Product*)malloc(sizeof(Product));
                pro->next->next = NULL;
            }
            else {
                pro = pro->next;
                pro->name = (char*)malloc(len * sizeof(char));
                fscanf(users_list, "%s %d %d", pro->name, &(pro->price), &(pro->count));
                pro->next = (Product*)malloc(sizeof(Product));
                pro->next->next = NULL;
            }
        }
    }
    fclose(users_list);
    printf("Welcome to UT-Kala!Data base is loaded!\n");
    return 0;
}

int save(User* users, Product* products, FILE* users_list, FILE* products_list) {
    Product* pro;
    User* usr;
    //products
     /*    write format  :   name-price-count-seller name-rate-rate sum-rate num      (-) stands for ' '   */
    products_list = fopen("goods.txt", "w");
    pro = products;
    pro = pro->next;
    while (pro->next != NULL) {
        fprintf(products_list, "%s %d %d %s %d %d %d\n", pro->name, pro->price, pro->count, pro->seller_name, pro->rate, pro->sum_of_rates, pro->number_of_rates);
        pro = pro->next;
    }
    fclose(products_list);
    //users
    /*   write format  :  if(buyer) u username-password-role-money
                                    p name-price-count-seller name-rate permission             (-) stands for ' '
                          if(seller) u username-password-role-money
                                     p name-price-count
    */
    users_list = fopen("users.txt", "w");
    usr = users;
    usr = usr->next;
    while (usr->next != NULL) {
        if (usr->role[0] == 'S') {
            fprintf(users_list, "u%s %s %s %d\n", usr->name, usr->password, usr->role, usr->money);
            pro = usr->products;
            pro = pro->next;
            while (pro->next != NULL) {
                fprintf(users_list, "p%s %d %d\n", pro->name, pro->price, pro->count);
                pro = pro->next;
            }
        }
        else {
            fprintf(users_list, "u%s %s %s %d\n", usr->name, usr->password, usr->role, usr->money);
            pro = usr->products;
            pro = pro->next;
            while (pro->next != NULL) {
                fprintf(users_list, "p%s %d %d %s %d\n", pro->name, pro->price, pro->count, pro->seller_name, pro->rate_permission);
                pro = pro->next;
            }
        }
        usr = usr->next;
    }
    fclose(users_list);
    /* all the data in "users" and "products" list have been written in file
       next time which users start the program these datas will be implemented in the lists for further uses */
    printf("Data base is saved!\n");
    return 0;
}