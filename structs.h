//Advanced UT-KALA

//================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------------------------------------------------------------------------------------------


/*
 #UT-kala with new options

 1-Data base : Using file to store the data

2-Linked list : Using linked list as a data structure to store datas in runtime instead of arrays

3-New commands :
  1.remove_goods <goods_name>
  2.change_goods_price <goods_name> <new_price>
  3.rate_goods <goods_name> <seller_username> <rating>
  4. [deleting goods from the list if avg_rate is lower than 2 if 5 votes are already confirmed]
  5. [getting goods back to the list if avg_rate gets higher than 2 or 2 by votes of previous purchasers]
  6.show_goods
     ^ it's like the command in the first phase but a little difference in details to show
     {1-name 2-price 3-count 4-seller_name 5-avg_rate}
  7.search <num_of_condition>
    <attribute> <value>
         ...
     attribute={name , seller_username , min_price , max_price}


   <in command 6 and 7 datas should be sorted>
*/

//-------------------------------------------------------------------------------------

//Data structures and typdefs

struct product {
    char* name;
    char* seller_name;
    int price;
    int count;
    int rate;

    //^^^^^^^^^^^^^^^^^
    int number_of_rates;
    int sum_of_rates;
    //These elements are not directly used but used fot other uses.
    int rate_permission;
    int filter_flag;
    //^^^^^^^^^^^^^^^^^

    struct product* next;
};

struct user {
    char* name;
    char* password;
    char role[10];
    int money;
    struct product* products;

    struct user* next;
};

typedef struct product Product;
typedef struct user User;