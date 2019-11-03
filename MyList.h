//
// Created by texnar on 29/10/2019.
//
#include "stdlib.h"
#include "stdio.h"

//#define check_OK();


#ifndef LIST_MYLIST_H
#define LIST_MYLIST_H
typedef int list_t;
typedef int size_list_t;

template <typename T>
struct List {
    T* data_;
    T* next_;
    T* prev_;

    size_list_t head_;
    size_list_t tail_;
    size_list_t free_;
    size_list_t size_;
    size_list_t length_;

    explicit List (size_list_t DEFAULT_LENGTH = 10, size_list_t DEFAULT_HYSTERESIS = 3);

    ~List();

    List (const List<T>& that) = delete;

    void check_OK ();
    void printError (size_list_t num_error);

    void Dump ();

    size_list_t insertInEnd (T value);
    size_list_t insertInStart (T value);
    size_list_t insertBeforeIndex (size_list_t index, T value);
    size_list_t insertAfterIndex (size_list_t index, T value);
};

    /*unsigned char text_error[][20] = {
            "dfsdfsdf",
            "fdfefef",
            "dwdwd"
    };*/
#include "MyList.cpp"

#endif //LIST_MYLIST_H
