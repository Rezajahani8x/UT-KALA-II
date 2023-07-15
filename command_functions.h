#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//   main_branch functions

int signup(User* users, char* username, char* password, char* role) {
    if (strcmp(role, "Buyer") && strcmp(role, "Seller")) {
        //Error
        printf("Error!Role you have entered is unvalid\n");
        return -1;
    }
    User* temp;
    temp = users;
    while (temp->next != NULL) {
        int condition1, condition2;
        condition1 = strcmp(username, temp->name);
        condition2 = strcmp(role, temp->role);
        if (!condition1 && !condition2) {
            printf("Error!This username is already taken for this role!\n");
            return -1;
        }
        temp = temp->next;
    }
    //Errors has been checked and now we can add the user to the list
    int len;
    len = strlen(username);
    temp->name = (char*)malloc((len + 1) * sizeof(char));
    len = strlen(password);
    temp->password = (char*)malloc((len + 1) * sizeof(char));
    //determining user's data
    strcpy(temp->name, username);
    strcpy(temp->password, password);
    strcpy(temp->role, role);
    temp->money = 0;
    temp->products = (Product*)malloc(1 * sizeof(Product));
    temp->products->next = (Product*)malloc(1 * sizeof(Product));
    temp->products->next->next = NULL;
    temp->products->name = (char*)malloc(sizeof(char));
    temp->products->seller_name = (char*)malloc(sizeof(char));
    //Extending the list
    temp->next = (User*)malloc(1 * sizeof(User));
    temp->next->next = NULL;

    printf("Signup accomplished\n");

    return 0;
}

int login(User* users, char* username, char* password, char* role) {
    int result;
    result = -1; //result=-1 means user can't login
    User* temp;
    temp = users;
    while (temp->next != NULL) {
        int condition1, condition2, condition3;
        condition1 = strcmp(username, temp->name);
        condition2 = strcmp(password, temp->password);
        condition3 = strcmp(role, temp->role);
        if (!condition1 && !condition2 && !condition3) {
            //all three inputs are appropiate , user can login
            result = 0;
            break;
        }
        temp = temp->next;
    }
    if (result == 0) {
        printf("Login accomplished!\n");
        return 0;
    }
    else {
        printf("Error!Login failed!Username or password or role may be incorrect!\n");
        return -1;
    }
}

int view(User* user_ad) {
    int type_of_user;
    type_of_user = strcmp(user_ad->role, "Buyer");//if buyer 0 if seller 1
    printf(" *    Profile   * \n");
    printf(" Name : %s\n", user_ad->name);
    printf(" Role : %s\n", user_ad->role);
    printf(" Money : %d\n", user_ad->money);
    printf(" Products : \n");
    Product* temp;
    temp = user_ad->products;
    temp = temp->next;
    if (type_of_user == 0) {//buyer
        while (temp->next != NULL) {
            printf("%s %d %d %s\n", temp->name, temp->price, temp->count, temp->seller_name);
            temp = temp->next;
        }
    }
    else {//seller
        while (temp->next != NULL) {
            printf("%s %d %d\n", temp->name, temp->price, temp->count);
            temp = temp->next;
        }
    }
    return 0;
}

int add_goods(User* user_ad, Product* products, char* goods_name, int price, int count) {
    int t = 0;//if t is 0 means product doesn't exist if 1 it does!
    Product* temp;
    temp = products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            if (price != temp->price) {
                //Error
                printf("Error!Product already exists and price doesn't match!\n");
                return -1;
            }
            if (price == temp->price) {
                if (strcmp(user_ad->name, temp->seller_name) != 0) {
                    printf("Error!You can't add this good it is already added!\n");
                    return -1;
                }
                //just increase count of the product!
                temp->count += count;
                printf("Increasing number of product accomplished!\n");
                t = 1;
                break;
            }
        }
        temp = temp->next;
    }
    if (t == 1) {
        temp = user_ad->products;
        while (temp->next != NULL) {
            if (strcmp(goods_name, temp->name) == 0) {
                temp->count += count;
                return 0;
            }
            temp = temp->next;
        }
    }
    //if program reaches this part means the product is new
    //product list should be updated - user product part should be updated

    //products list
    temp = products;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    int len;
    len = strlen(goods_name);
    temp->name = (char*)malloc((len + 1) * sizeof(char));
    len = strlen(user_ad->name);
    temp->seller_name = (char*)malloc((len + 1) * sizeof(char));
    strcpy(temp->name, goods_name);
    temp->price = price;
    temp->count = count;
    strcpy(temp->seller_name, user_ad->name);
    temp->number_of_rates = 0;
    temp->sum_of_rates = 0;
    temp->rate = 0;

    //Extend
    temp->next = (Product*)malloc(1 * sizeof(Product));
    temp->next->next = NULL;

    //user product list
    temp = user_ad->products;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    len = strlen(goods_name);
    temp->name = (char*)malloc((len + 1) * sizeof(char));
    strcpy(temp->name, goods_name);
    temp->price = price;
    temp->count = count;

    //Extend
    temp->next = (Product*)malloc(1 * sizeof(Product));
    temp->next->next = NULL;

    printf("You have added your product!\n");

    return 0;
}

int remove_goods(User* user_ad, Product* products, char* goods_name) {
    //to remove a product the node should be deleted in 2 places 1-products list 2-seller's purchaseable goods
    int r = -1;                         //if it stays -1 means no product could be found with that name
    Product* temp;
    temp = products;
    while (temp->next != NULL) {
        if (strcmp(temp->name, goods_name) == 0) {
            if (strcmp(user_ad->name, temp->seller_name) == 0) {
                if (user_ad->role[0] == 'S') {
                    r = 0;
                }
                else {
                    r = -2;
                }
            }
            else {
                r = -2;
            }
            break;
        }
        temp = temp->next;
    }
    if (r == -1) {
        printf("Error!Such product is not available!\n");
        return -1;
    }
    if (r == -2) {
        printf("Error!You are not allowed to remove due to your role and security reasons!\n");
        return -1;
    }
    //Errors have been checked and now the main concept should be conducted
    /*
    a->b->c
    let 'b' be the node which we want to delete.
    task is to conncet a to c   ==>    a->c
     */
    temp = products;
    Product* prev = NULL;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0 && strcmp(user_ad->name, temp->seller_name) == 0 && user_ad->role[0] == 'S') {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    //product list has been updated time to update user profile data
    temp = user_ad->products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Removing product is accomplished!\n");
    return 0;
}

int change_price(User* user_ad, Product* products, char* goods_name, int new_price) {
    //1-check for errors 2-update the price in two stages {1-products list 2-user list}
    //conditions : 1-new_price!=current_price 2-availablity 3-user should be the seller of the product
    Product* temp1;
    temp1 = products;
    while (temp1->next != NULL) {
        if (strcmp(goods_name, temp1->name) == 0) {
            if (strcmp(temp1->seller_name, user_ad->name) == 0) {
                if (new_price != temp1->price) {
                    if (temp1->rate < 2 && temp1->number_of_rates >= 5) {
                        printf("Error!Update failure!Product is deactivated!\n");
                        return -1;
                    }
                    //All the errors have been checked so far if it is executed till here means everything's set for the update
                    temp1->price = new_price;
                    //second stage
                    temp1 = user_ad->products;
                    while (temp1->next != NULL) {
                        if (strcmp(temp1->name, goods_name) == 0) {
                            temp1->price = new_price;
                            printf("Price update accomplished!\n");
                            return 0;
                        }
                        temp1 = temp1->next;
                    }
                }
                else {
                    printf("Error!Update failure!\n");
                    return -1;
                }
            }
            else {
                printf("Error!Seller's name doesn't match!\n");
                return -1;
            }
        }
        temp1 = temp1->next;
    }
    printf("Error!Product is not available!\n");
    return -1;
}

int show_goods(Product* products) {
    //sort products
    Product* list = NULL;
    list = sort(products);

    printf("   *     Products    *\n");
    printf(" Name   |   Price   |   Count   |   Seller's Name   |   Rate\n");
    Product* temp = list;
    temp = temp->next;
    while (temp->next != NULL) {
        if (temp->number_of_rates >= 5 && temp->rate < 2) {
            temp = temp->next;
            continue;
        }
        printf("%s  |   %d  |   %d  |   %s  |   %d\n", temp->name, temp->price, temp->count, temp->seller_name, temp->rate);
        temp = temp->next;
    }
    return 0;
}

int buy(User* users, User* user_ad, Product* products, char* goods_name, int count, char* seller_name) {
    //buy has 2 stages 1-money transfer 2-list updates {products-seller-buyer}

    //checking for possible errors
    //1-not enough money 2-not enough avail 3-deactivated 4-wrong good name 5-wrong seller name 6-user role
    if (user_ad->role[0] == 'S') {//6
        printf("Error!This command is only allowed for buyers!\n");
        return -1;
    }
    int r = -1;
    Product* temp = products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            r = 0;
            if (temp->number_of_rates >= 5 && temp->rate < 2) {//3
                printf("Error!Purchase failure!Product is temporarily disabled!\n");
                return -1;
            }
            if (strcmp(seller_name, temp->seller_name) != 0) { //5
                printf("Error!Seller name doesn't match!\n");
                return -1;
            }
            if (user_ad->money - temp->price < 0) {//1
                printf("Error!Purchase failure due to payment reasons!\n");
                return -1;
            }
            if (temp->count - count < 0) {//2
                printf("Error!Not enough avaialable product ready to be sold!\n");
                return -1;
            }
            break;
        }
        temp = temp->next;
    }
    if (r == -1) {//4
        printf("Error!Product doesn't exist!\n");
        return -1;
    }
    User* seller = users;
    while (seller->next != NULL) {
        if (strcmp(seller_name, seller->name) == 0) {
            break;
            //seller is holding address of the seller of the to purchase product!
        }
        seller = seller->next;
    }
    //main stages
    //if program reaches here means it has passed all the possible errors and temp is currently holding the to purchase good
    //1-Money transfer
    int transfer_money;
    transfer_money = temp->price * count;
    user_ad->money = user_ad->money - transfer_money;
    seller->money = seller->money + transfer_money;
    //saving price of the product
    int good_price = temp->price;
    //2-List updates
          //Products list
    temp->count = temp->count - count;
    //Seller profile
    temp = seller->products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            temp->count = temp->count - count;
            break;
        }
        temp = temp->next;
    }
    //Buyer profile
    r = 0;
    temp = user_ad->products;
    while (temp->next != NULL) {
        if (strcmp(temp->name, goods_name) == 0) {
            //user has already purchased this product so only count should increase
            temp->count += count;
            r = 1;
            break;
        }
        temp = temp->next;
    }
    if (r == 0) {   // it's the first time purchase for the user - temp is holding the address which should be written in
        //allocate memory
        int l;
        l = strlen(goods_name);
        temp->name = (char*)malloc((l + 1) * sizeof(char));
        l = strlen(seller_name);
        temp->seller_name = (char*)malloc((l + 1) * sizeof(char));
        strcpy(temp->name, goods_name);
        strcpy(temp->seller_name, seller_name);
        temp->price = good_price;
        temp->count = count;
        temp->rate_permission = 1;
        temp->next = (Product*)malloc(1 * sizeof(Product));
        temp->next->next = NULL;
    }
    printf("Purchase accomplished!\n");
    return 0;
}

int rate(User* user_ad, Product* products, char* goods_name, char* seller_name, int rating) {
    //this function is used for rating a product which is purchased ...
    //checking for possible errors
    /*
     1-wrong product name 2-wrong seller name 5-not purchased the product
     3-already rated 4-user aint a buyer
    */
    if (user_ad->role[0] != 'B') { //4
        printf("Error!Rate is not allowed for none-buyer users!\n");
        return -1;
    }
    int r = -1;
    Product* temp = user_ad->products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            r = 0;
            if (temp->rate_permission == 0) { //3
                printf("Error!No more rates are allowed!\n");
                return -1;
            }
            break;
        }
        temp = temp->next;
    }
    if (r == -1) { //1 & 5
        printf("Error!Such product is not available in your purchased goods list!\n");
        return -1;
    }
    if (strcmp(temp->seller_name, seller_name) == 1) { //2
        printf("Error!Seller name does not match!\n");
        return -1;
    }
    //all possible errors have been checked and now we can proceed to next stage in which actuall process is dealt with
    //rate stage
    temp->rate_permission = 0;
    temp = products;
    while (temp->next != NULL) {
        if (strcmp(goods_name, temp->name) == 0) {
            break;
        }
        temp = temp->next;
    }
    temp->number_of_rates++;
    temp->sum_of_rates += rating;
    temp->rate = temp->sum_of_rates / temp->number_of_rates;
    printf("Rate accomplished!\n");
    return 0;
}


int search(Product* products, int att_num) {
    //allocating linked list for keeping filtered products to show after search
    Product* filtered_list = (Product*)malloc(sizeof(Product));
    filtered_list->name = (char*)malloc(1 * sizeof(char));
    filtered_list->seller_name = (char*)malloc(1 * sizeof(char));
    filtered_list->next = (Product*)malloc(sizeof(Product));
    filtered_list->next->next = NULL;
    //search inputs
    int i = 0;
    //1 main way to get search input
/*    char** attribute = (char**)malloc(4 * sizeof(char*));
    char** value = (char**)malloc(4 * sizeof(char*));
    attribute[0] = (char*)malloc(1 * sizeof(char));
    value[0] = (char*)malloc(1 * sizeof(char));
    for (i = 1; i < 4; i++) {
        attribute[i] = (char*)malloc(1 * sizeof(char));
        value[i] = (char*)malloc(1 * sizeof(char));
    }
             // *********************
    for (i = 0; i < att_num; i++) {
        attribute[i] = get_string(attribute[i]);
        value[i] = get_string(value[i]);
    }
 */
 //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

 //2     backup plan for search input
    char attribute[4][20];
    char value[4][20];
    for (i = 0; i < att_num; i++) {
        scanf("%s %s", attribute[i], value[i]);
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    //manage filtered list by attributes
    /*
     1-add goods in "products" satisfying attribute[0] to "filtered list"
     2-remove goods not satisfying attribute[1:3] in "filtered list"
     {* removing means increase filter_flag and don't print if it ain't 0 *}
    */
    add_filtered_good(products, filtered_list, attribute[0], value[0]);
    for (i = 1; i < att_num; i++) {
        remove_filtered_good(filtered_list, attribute[i], value[i]);
    }

    //sort filtered list
    Product* list = NULL;
    list = sort(filtered_list);

    //print appropriate result
    printf("    Search Result    \n");
    print_search_result(list);

    return 0;
}