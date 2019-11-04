#include <stdio.h>
#include "MyList.h"
//#include <graphviz/gvc.h>


int main() {
    List<int> list;
    size_list_t p = list.insertInStart(10);

    size_list_t p4 = list.insertInEnd(20);
//    printf("data %d\n", list.data_[list.tail_]);
//    printf("point %d\n", p4);

//    list.Dump();
    size_list_t p2 = list.insertInEnd(30);
//    printf("data %d\n", list.data_[list.tail_]);
//    printf("point %d\n", p2);

//    size_list_t o1 = list.convertLogicIndex(2);
//    printf("%d\n", o1);

//    printf("point by value %d\n", list.searchByValue(30));
//    list.Dump();
    list.insertInEnd(40);
    list.insertInEnd(50);
    list.insertInEnd(60);
    list.insertInEnd(70);
    list.insertInEnd(80);
    list.insertInEnd(90);
    list.insertInEnd(100);
    list.insertInEnd(110);

//    list.insertBeforeIndex(p2, 60);

    list.deleteIndex(p2);
    list.deleteIndex(p4);

    list.sortList();
    list.Dump();

    size_list_t o1 = list.convertLogicIndex(2);

//    ListConstruct(&list);
    return 0;
}