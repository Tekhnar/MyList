//
// Created by texnar on 29/10/2019.
//
//#include "MyList.h"
template <typename T>
List<T>::List(size_list_t DEFAULT_LENGTH, size_list_t DEFAULT_HYSTERESIS) :
    length_ (10),
    data_ ((T*) calloc (DEFAULT_LENGTH, sizeof(list_t))),
    next_ ((T*) calloc (DEFAULT_LENGTH, sizeof(list_t))),
    prev_ ((T*) calloc (DEFAULT_LENGTH, sizeof(list_t))),
    size_ (0),
    free_ (1),
    head_ (0),
    tail_ (0)
{
    prev_[0] = 0;
    next_[0] = 0;

    for (size_list_t i = 1; i < length_; i++){
        prev_[i] = -1;
        next_[i] = i + 1;
    }
    next_[length_ - 1] = 0;

}

template <typename T>
List<T>::~List()
{
    length_ = 0;
    free (data_);
    free (next_);
    free (prev_);
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

template <typename T>
size_list_t List<T>::insertInEnd(T value)
{
//    Dump();
    /*check_OK();

    size_list_t tmp = free_;
    free_ = next_[free_];
    next_[tmp] = 0;

    if (size_ == 0) {
        head_ = tmp;
        prev_[tail_] = 0;
    }
    if (size_ > 0) {
        prev_[tmp] = tail_;
//        next_[tmp] = 0;
        next_[tail_] = tmp;
    }

    tail_ = tmp;

    data_ [tmp] = value;
    size_++;*/
    return insertAfterIndex(tail_, value);
}

template <typename T>
size_list_t List<T>::insertInStart(T value)
{
    /*check_OK();

    size_list_t tmp = free_;
    free_ = next_[free_];
    prev_[tmp] = 0;

    if (size_ == 0) {
        tail_ = tmp;
        next_[tmp] = 0;
    }
    else if (size_ > 0) {
        prev_[head_] = tmp;
        next_[tmp] = head_;
        prev_[tmp] = 0;
    }

    head_ = tmp;
    data_ [tmp] = value;
    size_++;
    return tmp;*/
    return insertBeforeIndex (head_, value);
}

template <typename T>
size_list_t List<T>::insertBeforeIndex (size_list_t index, T value)
{
    check_OK();
    if (index < 0 || index >length_) printError(6);

    size_list_t new_index = free_;
    free_ = next_[free_];


    if (size_ == 0){
        if (head_ == index){
            /*will do this function*/
            tail_ = new_index;
            next_[new_index] = 0;
            prev_[new_index] = 0;

            head_ = new_index;
        } else printError(4);
    }
    else if (size_ > 0) {
        if (head_ == index){
            /*will do this function*/
            prev_[head_] = new_index;
            next_[new_index] = head_;
            prev_[new_index] = 0;

            head_ = new_index;
        } else {
            next_[new_index] = index;
            prev_[new_index] = prev_[index];
            next_[prev_[index]] = new_index;
            prev_[index] = new_index;
        }
    }

    data_ [new_index] = value;
    size_++;
    return new_index;
}

template <typename T>
size_list_t List<T>::insertAfterIndex(size_list_t index, T value)
{
    check_OK();
    if (index < 0 || index >length_) printError(6);

    size_list_t new_index = free_;
    free_ = next_[free_];

    if (size_ == 0){
        if (index == tail_){
            head_ = new_index;
            prev_[tail_] = 0;
            next_[new_index] = 0;

            tail_ = new_index;
        }
        else printError (4);
    }
    else if (size_ > 0) {
        if (tail_ == index){
            /*will do this function*/
            prev_[new_index] = tail_;
            next_[new_index] = 0;
            next_[tail_] = new_index;

            tail_ =new_index;
        } else {
            prev_[new_index] = index;
            next_[new_index] = next_[index];
            prev_[next_[index]] = new_index;
            next_[index] = new_index;
        }
    }

    data_ [new_index] = value;
    size_++;
    return new_index;
}
template <typename T>
void List<T>::check_OK () {
    if (prev_[free_] != -1) printf("Error, prev_[free_]!= -1");
    if (size_ == 1) {
        if (next_[head_] != 0 || prev_[tail_] != 0) printError(1);
    }
    else if (size_ > 1) {
        size_list_t index = head_;
//
//        printf("Head %d\n", head_);
        for (size_list_t i = 1; i < size_; i++) {
            index = next_[index];
        }
        if (index != tail_) printError(2);
//        printf("Head %d\n", index);
//        printf("tail %d\n", tail_);
        index = tail_;
        for (size_list_t i = 1; i < size_; i++) {
            index = prev_[index];
        }

        if (index != head_) printError(3);
    }
    else if (size_ < 0) printError(5);

//    abort();
}

template <typename T>
void List<T>::printError (size_list_t num_error){
    if (num_error == 1) printf("Error, index 'next_' != index 'tail_'\n");
    if (num_error == 2) printf("Error in index list\nCan't go to 'tail'\n");
    if (num_error == 3) printf("Error in index list\nCan't go to 'head'\n");
    if (num_error == 4) printf("Error, size of List = 0\n");
    if (num_error == 5) printf("Error, size of List < 0\n");
    if (num_error == 6) printf("Error, give invalid index\n");
    abort();
}

template <typename T>
void List<T>::Dump(){
    FILE* file = fopen("text_picture.dot", "wb");
    fprintf(file, "digraph structs {\n");
    fprintf(file, "rankdir=HR;\n");

    for (size_list_t i = 0; i < size_ + 1; i++){
        fprintf(file, "Index%d [shape=record, label=\" <index> Index%d | Value: %d| <next> next: %d | <prev> prev: %d \" ];\n", i, i, data_[i], next_[i], prev_[i]);
    }

    size_list_t index = head_;
    for (size_list_t i = 1; i < size_+1; i++) {
        fprintf(file, "Index%d: <next> -> Index%d : <index>;\n", i, next_[i]);
        index = next_[index];
    }
//    if (index != tail_) printError(2);
//    index = tail_;
    index = tail_;
    for (size_list_t i = 1; i < size_+1; i++) {
        fprintf(file, "Index%d: <prev> -> Index%d : <index>;\n", i, prev_[i]);
//        index = next_[index];
        index = prev_[index];
    }
//
//    if (index != head_) printError(3);

    fprintf(file, "}\n");
    fclose(file);
}


