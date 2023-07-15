#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helping functions

char* get_string(char* str) {
    //for forming these strings we need unlimited length array:
    //1-username 2-password 3-goods_name 4-seller_name
    int len = 1;//length of the string allocated so far
    int i = 0;
    while (1) {
        char c;
        c = getchar();
        if (c == ' ' || c == '\n') {//end of the string
            str[i] = '\0';
            break;
        }
        else {//getting string still in progress
            str[i] = c;
            str = (char*)realloc(str, (len + 1) * sizeof(char));
            len++;
            i++;
        }
    }
    return str;
}

int copy_data(Product* dest, Product* src) {
    //copy temp data in w_node
    int l1, l2;
    l1 = strlen(src->name);
    l2 = strlen(src->seller_name);
    dest->name = (char*)malloc((l1 + 1) * sizeof(char));
    dest->seller_name = (char*)malloc((l2 + 1) * sizeof(char));
    strcpy(dest->name, src->name);
    strcpy(dest->seller_name, src->seller_name);
    dest->price = src->price;
    dest->count = src->count;
    dest->rate = src->rate;
    //flag for removing if not satisfying
    dest->filter_flag = 0;
    return 0;
}

//sort

static int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

Product* sort(Product* list) {
    Product* temp;
    Product* result = (Product*)malloc(sizeof(Product));
    result->next = (Product*)malloc(sizeof(Product));
    result->next->next = NULL;
    temp = result;
    temp->name = (char*)malloc(sizeof(char));
    temp->seller_name = (char*)malloc(sizeof(char));
    //save goods name in "names"
    temp = list;
    temp = temp->next;
    char** names;
    int len = 0;
    int i, j, l;
    while (temp->next != NULL) {
        len++;   //length of list 
        temp = temp->next;
    }
    // len = length of list
    names = (char**)malloc(len * sizeof(char*));
    temp = list;
    temp = temp->next;
    for (i = 0; i < len; i++) {
        l = strlen(temp->name);
        names[i] = (char*)malloc((l + 1) * sizeof(char));
        strcpy(names[i], temp->name);
        temp = temp->next;
    }
    //sort "names"
    qsort(names, len, sizeof(char*), compare);
    //put contents based on order of "names" in result for printing result
    temp = result;
    temp = temp->next;
    for (j = 0; j < len; j++) {
        Product* test = list;
        test = test->next;
        while (test->next != NULL) {
            if (strcmp(names[j], test->name) == 0) {
                copy_data(temp, test);
                break;
            }
            test = test->next;
        }
        temp->next = (Product*)malloc(sizeof(Product));
        temp->next->next = NULL;
        temp = temp->next;
    }
    return result;
}

User* user_address_calculater(User* users, char* username, char* role) {
    User* user_address;
    user_address = users;
    while (user_address->next != NULL) {
        int condition1, condition2;
        condition1 = strcmp(username, user_address->name);
        condition2 = strcmp(role, user_address->role);
        if (!condition1 && !condition2) {
            return user_address;
        }
        user_address = user_address->next;
    }
}

User* user_alloc(User* users) {
    users = (User*)malloc(1 * sizeof(User));
    users->next = (User*)malloc(sizeof(User));
    users->next->next = NULL;
    //creating dummy node
    users->name = (char*)malloc(sizeof(char));
    users->password = (char*)malloc(sizeof(char));
    return users;
}

Product* product_alloc(Product* products) {
    products = (Product*)malloc(1 * sizeof(Product));
    products->next = (Product*)malloc(sizeof(Product));
    products->next->next = NULL;
    //creating dummy node
    products->name = (char*)malloc(sizeof(char));
    products->seller_name = (char*)malloc(sizeof(char));
    return products;
}

int check_memory_alloc(User* users, Product* products) {
    if (users == NULL || products == NULL) {
        //Error
        printf("Error!Due to some technical problems we are facing a little trouble\nvisit us later\n");
        return -1;
    }
    else {
        return 0;
    }
}

                            //functions for search

Product* filtered_list_node_address(Product* filtered_list) {
    //this function gives us the node address in which good info should be written
    //extending list and closing it is functioned too
    Product* temp = filtered_list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = (Product*)malloc(sizeof(Product));
    temp->next->next = NULL;
    return temp;
}

int add_filtered_good(Product* products, Product* filtered_list, char* attribute, char* value) {
    Product* temp = products;
    Product* w_node = NULL;
    if (strcmp(attribute, "name") == 0) {
        while (temp->next != NULL) {
            if (strcmp(temp->name, value) == 0) {
                w_node = filtered_list_node_address(filtered_list);
                copy_data(w_node, temp);
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "seller_username") == 0) {
        while (temp->next != NULL) {
            if (strcmp(temp->seller_name, value) == 0) {
                w_node = filtered_list_node_address(filtered_list);
                copy_data(w_node, temp);
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "min_price") == 0) {
        int min_price = atoi(value);
        while (temp->next != NULL) {
            if (temp->price >= min_price) {
                w_node = filtered_list_node_address(filtered_list);
                copy_data(w_node, temp);
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "max_price") == 0) {
        int max_price = atoi(value);
        while (temp->next != NULL) {
            if (temp->price <= max_price) {
                w_node = filtered_list_node_address(filtered_list);
                copy_data(w_node, temp);
            }
            temp = temp->next;
        }
    }
    return 0;
}

int remove_filtered_good(Product* filtered_good, char* attribute, char* value) {
    Product* temp = filtered_good;
    if (strcmp(attribute, "name") == 0) {
        while (temp->next != NULL) {
            if (strcmp(temp->name, value) != 0) {
                temp->filter_flag++;
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "seller_username") == 0) {
        while (temp->next != NULL) {
            if (strcmp(temp->seller_name, value) != 0) {
                temp->filter_flag++;
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "min_price") == 0) {
        int min_price = atoi(value);
        while (temp->next != NULL) {
            if (temp->price < min_price) {
                temp->filter_flag++;
            }
            temp = temp->next;
        }
    }
    else if (strcmp(attribute, "max_price") == 0) {
        int max_price = atoi(value);
        while (temp->next != NULL) {
            if (temp->price > max_price) {
                temp->filter_flag++;
            }
            temp = temp->next;
        }
    }
    return 0;
}

int print_search_result(Product* filtered_list) {
    Product* temp = filtered_list;
    temp = temp->next;
    while (temp->next != NULL) {
        if (temp->filter_flag == 0) {
            printf("%s  |   %d  |   %d  |   %s  |   %d \n", temp->name, temp->price, temp->count, temp->seller_name, temp->rate);
        }
        temp = temp->next;
    }
    return 0;
}

