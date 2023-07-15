#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

             // main function

int utkala(User* users, Product* products) {
    //inputs by the user
/*
 1-signup <username> <password> <role> 2-login <username> <password> <role> 3-logout <> 4-view <>
 5-deposit <money>  6-add_goods <goods_name> <price> <count> 7-show_goods <> 8-buy <goods_name> <count> <sellers_name>
 new commands:
 1-remove_goods <goods_name>  2-change_goods_price <goods_name> <new_price>
 3-rate_goods <goods_name> <seller_name> <rating>     4,5-activation and deactivation of products
 6-search <number_of_condition>
   <attribute> <value>
*/

    char command[30];

    while (1) {
        scanf("%s", command);
        if (!strcmp(command, "signup")) {
            //sign up
            //ask the user for data
            char* username = (char*)malloc(1 * sizeof(char));
            char* password = (char*)malloc(1 * sizeof(char));
            char role[10];
            getchar(); //get a space ...
            username = get_string(username);
            password = get_string(password);
            scanf(" %s", role);
            //signup process
            signup(users, username, password, role);
            //free memory
            free(username);
            free(password);
            continue;
        }
        else if (!strcmp(command, "login")) {
            //login
            //ask data from user
            char* username = (char*)malloc(1 * sizeof(char));
            char* password = (char*)malloc(1 * sizeof(char));
            char role[10];
            getchar(); //get a space ...
            username = get_string(username);
            password = get_string(password);
            scanf(" %s", role);
            //login process
            int r;
            r = login(users, username, password, role);
            if (r == -1) {
                //login failure!
                free(username);
                free(password);
                continue;
            }
            if (r == 0) {
                //login accomplishment
                User* user_ad;
                user_ad = user_address_calculater(users, username, role);
                //user address is kept in user_ad for futher tasks
                free(username);
                free(password);

                //get input commands and continue the program!
                //available input commands from the loged in user:
                /*
                3-logout <> 4-view <>
                5-deposit <money>  6-add_goods <goods_name> <price> <count>
                7-show_goods <> 8-buy <goods_name> <count> <sellers_name>
                new commands:
                1-remove_goods <goods_name>  2-change_goods_price <goods_name> <new_price>
                3-rate_goods <goods_name> <seller_name> <rating>     4,5-activation and deactivation of products
                6-search <number_of_condition>
                  <attribute> <value>
                */

                while (1) {
                    scanf("%s", command);
                    if (!strcmp(command, "logout")) {
                        //user logs out
                        printf("Loged out!\n");
                        break;
                    }
                    else if (!strcmp(command, "view")) {
                        //view , users can see their profiles
                        view(user_ad);
                        continue;
                    }
                    else if (!strcmp(command, "deposit")) {
                        //deposit
                        if (user_ad->role[0] != 'B') {
                            //user aint a buyer and can't deposit!
                            printf("Error!Only buyers can deposit!\n");
                            continue;
                        }
                        int deposit_money;
                        scanf(" %d", &deposit_money);
                        user_ad->money += deposit_money;
                        printf("Deposit accomplished!\n");
                        continue;
                    }
                    else if (!strcmp(command, "add_goods")) {
                        //add goods
                        if (user_ad->role[0] != 'S') {
                            //user ain't a seller and can't add goods
                            printf("Error!Only sellers can add goods!\n");
                            continue;
                        }
                        //ask user for data
                        char* goods_name = (char*)malloc(1 * sizeof(char));
                        int price;
                        int count;
                        getchar(); //get a space ...
                        goods_name = get_string(goods_name);
                        scanf("%d %d", &price, &count);
                        //add good process
                        add_goods(user_ad, products, goods_name, price, count);
                        //free memory
                        free(goods_name);
                        continue;
                    }
                    else if (!strcmp(command, "show_goods")) {
                        if (command[10] != '\0') {
                            printf("Error!Can't read the command!\n");
                            continue;
                        }
                        //show goods
                        show_goods(products);
                        continue;
                    }
                    else if (!strcmp(command, "buy")) {
                        //buy
                        //ask for data from the user
                        char* goods_name = (char*)malloc(1 * sizeof(char));
                        int count;
                        char* seller_name = (char*)malloc(1 * sizeof(char));
                        getchar();   //get a space ..
                        goods_name = get_string(goods_name);
                        scanf(" %d ", &count);
                        seller_name = get_string(seller_name);
                        //process of purchase
                        buy(users, user_ad, products, goods_name, count, seller_name);
                        //free memory
                        free(goods_name);
                        free(seller_name);
                        continue;
                    }
                    else if (!strcmp(command, "remove_goods")) {
                        //remove goods
                        //ask for data
                        char* goods_name = (char*)malloc(1 * sizeof(char));
                        getchar(); //get a space ...
                        goods_name = get_string(goods_name);
                        //removing process
                        remove_goods(user_ad, products, goods_name);
                        free(goods_name);
                        continue;
                    }
                    else if (!strcmp(command, "change_goods_price")) {
                        //change goods price
                        //ask for data
                        char* goods_name = (char*)malloc(1 * sizeof(char));
                        int new_price;
                        getchar();  // get a space ...
                        goods_name = get_string(goods_name);
                        scanf("%d", &new_price);
                        //updating price process
                        change_price(user_ad, products, goods_name, new_price);
                        free(goods_name);
                        continue;
                    }
                    else if (!strcmp(command, "rate_goods")) {
                        //rate a product
                        //ask data from the user
                        char* goods_name = (char*)malloc(1 * sizeof(char));
                        char* seller_name = (char*)malloc(1 * sizeof(char));
                        int rating;
                        getchar();
                        goods_name = get_string(goods_name);
                        seller_name = get_string(seller_name);
                        scanf(" %d", &rating);
                        //rating process
                        rate(user_ad, products, goods_name, seller_name, rating);
                        //free
                        free(goods_name);
                        free(seller_name);
                        continue;
                    }
                    else if (!strcmp(command, "search")) {
                        //search about an attribute and display the sorted result
                        int number_of_attribute;
                        scanf_s("%d", &number_of_attribute);
                        //search inputs and process
                        search(products, number_of_attribute);
                        continue;
                    }
                    else if (!strcmp(command, "signup") || !strcmp(command, "login")) {
                        printf("Error!User is loged in no such command is allowed!\n");
                        continue;
                    }
                    else {
                        //Error
                        printf("Error!Can't run the command!\n");
                        continue;
                    }
                }
                continue;
            }
        }
        else if (!strcmp(command, "Exit")) {
            //user can exit the app
            printf("You have successfully quited the program!Thanks for visiting UT-Kala!\n");
            break;
        }
        else if (!strcmp(command, "logout") || !strcmp(command, "view") || !strcmp(command, "deposit") || !strcmp(command, "add_goods") || !strcmp(command, "show_goods") || !strcmp(command, "buy")) {
            printf("Error!No user has loged in!\n");
            continue;
        }
        else if (!strcmp(command, "remove_goods") || !strcmp(command, "change_goods_price") || !strcmp(command, "rate_goods") || !strcmp(command, "search")) {
            printf("Error!No user has loged in!\n");
            continue;
        }
        else {
            printf("Error!Can't read the command!\n");
        }
    }

    //free memory

    return 0;
}