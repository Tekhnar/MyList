#include <stdio.h>
#include "MyList.h"
//#include <graphviz/gvc.h>


int main() {
    List<int> list;
    size_list_t p = list.insertInStart(10);
    printf("data %d\n", list.data_[list.head_]);
    printf("point %d\n", p);

    /*size_list_t p3 = list.insertInStart(20);
    printf("data %d\n", list.data_[list.tail_]);
    printf("point %d\n", p3);*/

    size_list_t p4 = list.insertInEnd(20);
    printf("data %d\n", list.data_[list.tail_]);
    printf("point %d\n", p4);

//    list.Dump();
    size_list_t p2 = list.insertInEnd(30);
    printf("data %d\n", list.data_[list.tail_]);
    printf("point %d\n", p2);

    list.insertInEnd(40);
    list.insertInEnd(50);

    list.insertBeforeIndex(p2, 60);

    list.insertAfterIndex(p4, 100);
    list.insertInEnd(30);

    list.Dump();


//    ListConstruct(&list);
    return 0;
}