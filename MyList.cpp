#include "MyList.h"

//
// Created by texnar on 29/10/2019.
//
//#include "MyList.h"
template <typename T>
List<T>::List(size_list_t DEFAULT_LENGTH) :
    length_ (10),
    data_ ((T*) calloc (DEFAULT_LENGTH, sizeof(T))),
    next_ ((T*) calloc (DEFAULT_LENGTH, sizeof(T))),
    prev_ ((T*) calloc (DEFAULT_LENGTH, sizeof(T))),
    size_ (0),
    free_ (1),
    head_ (0),
    tail_ (0),
    list_is_sort (false)
{
    prev_[0] = 0;
    next_[0] = 0;

    fillingPoisonousValues();
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
    return insertAfterIndex(tail_, value);
}

template <typename T>
size_list_t List<T>::insertInStart(T value)
{
    return insertBeforeIndex(head_, value);
}

template <typename T>
size_list_t List<T>::insertBeforeIndex (size_list_t index, T value)
{
    check_OK();
    if (index < 0 || index >length_) printError(6);
    autoIncreaseLength();
    list_is_sort = false;

    size_list_t new_index = free_;
    free_ = next_[free_];


    if (size_ == 0){
        if (head_ == index){
            next_[new_index] = 0;
            prev_[new_index] = 0;

            tail_ = new_index;
            head_ = new_index;
        } else printError(4);
    }
    else if (size_ > 0) {
        if (head_ == index){
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
    autoIncreaseLength();
    if (index != tail_) list_is_sort = false;
    size_list_t new_index = free_;
    free_ = next_[free_];

    if (size_ == 0){
        if (index == tail_){
            prev_[new_index] = 0;
            next_[new_index] = 0;

            tail_ = new_index;
            head_ = new_index;
        } else printError (4);
    }
    else if (size_ > 0) {
        if (tail_ == index){
            prev_[new_index] = tail_;
            next_[new_index] = 0;
            next_[tail_] = new_index;

            tail_ = new_index;
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
void List<T>::deleteIndex(size_list_t index) {
    check_OK();
    if (index < 0 || index >length_) printError(6);

    if (index == head_){
        head_ = next_[index];
        prev_[next_[index]] = 0;
        next_[index] = free_;
        prev_[index] = -1;
        free_ = index;
    }
    else if (index == tail_){
        tail_ = prev_[index];
        next_[prev_[index]] = 0;
        next_[index] = free_;
        prev_[index] = -1;
        free_ = index;
    } else {
        next_[prev_[index]] = next_[index];
        prev_[next_[index]] = prev_[index];
        data_[index] = 0;
        prev_[index] = -1;
        next_[index] = free_;
        free_ = index;
    }

    if (size_ == 1){
        head_ = 0;
        tail_ = 0;
    }
    size_--;
}
template <typename T>
size_list_t List<T>::convertLogicIndex(size_list_t logic)
{
    check_OK();

    if (list_is_sort) {
        return logic;
    } else {
        if (logic < 1 || logic > size_) printError(7);

        size_list_t tmp_logic = head_;
        for (size_list_t i = 1; i < logic; i++) {
            tmp_logic = next_[tmp_logic];
        }
        return tmp_logic;
    }
}

template <typename T>
size_list_t  List<T>::searchByValue(T value)
{
    check_OK();

    bool found = false;
    size_list_t tmp_index = head_;
    for (size_list_t i = 0; i < size_; i++){
        if (data_[tmp_index] == value){
            found = true;
            break;
        }
        tmp_index = next_[tmp_index];
    }
    if (found == true) return tmp_index;
    else return 0;
}

template <typename T>
void List<T>::autoIncreaseLength(size_list_t MULTIPLICATION_FACTOR)
{
    if (size_ + 1 == length_ - 1) {
        T* temp_point_data = (T*) realloc(data_, length_ * MULTIPLICATION_FACTOR * sizeof(T));
        if (temp_point_data == nullptr) printError(8);
        else data_ = temp_point_data;

        T* temp_point_next = (T*) realloc(next_, length_ * MULTIPLICATION_FACTOR * sizeof(T));
        if (temp_point_next == nullptr) printError(9);
        else next_ = temp_point_next;

        T* temp_point_prev = (T*) realloc(prev_, length_ * MULTIPLICATION_FACTOR * sizeof(T));
        if (temp_point_prev == nullptr) printError(10);
        else prev_ = temp_point_prev;

        length_ = length_ * MULTIPLICATION_FACTOR;

        fillingPoisonousValues();
    }
}

template <typename T>
void List<T>::sortList()
{
    check_OK();

    bool found_data = false;
    for (size_list_t i = 1; i < length_; i++) {
        if (prev_[i] == -1) {
            for (size_list_t j = length_ - 1; j > i; j--){
                if (prev_[j] != -1) {
                    if (j == head_) head_ = i;
                    if (j == tail_) tail_ = i;
                    if (i == free_) free_ = j;
                    next_[prev_[j]] = i;
                    prev_[next_[j]] = i;
                    prev_[i] = prev_[j];
                    next_[i] = next_[j];
                    data_[i] = data_[j];

                    prev_[j] = -1;
                    data_[j] = 0;
                    found_data = true;
                    break;
                }
            }

            if (!found_data) break;

            found_data = false;
        }
//        if (found_data) break;
    }


    size_list_t *logic_index = getLogicIndexArray();
    qsort(logic_index, 1, size_);
    closeLogicIndexArray(logic_index);
    fillingNewIndex();
    fillingPoisonousValues();
    list_is_sort = true;
}

template <typename T>
void List<T>::fillingNewIndex()
{
    for (size_list_t i = 1; i < size_ + 1; i++) {
        next_[i] = i + 1;
        prev_[i] = i - 1;
    }
    if (size_ > 0) next_[size_] = 0;
    head_ = 1;
    tail_ = size_;
}

template <typename T>
void List<T>::qsort(size_list_t *logic_index, T left, T right)
{

    T i, last;
    if (left >= right)
        return;
    sort_swap(logic_index, left, (left + right) / 2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (logic_index[i] < logic_index[left])
            sort_swap(logic_index, ++last, i);
    sort_swap(logic_index, left, last);
    qsort(logic_index, left, last - 1);
    qsort(logic_index,last + 1, right);
}

template <typename T>
void List<T>::sort_swap(size_list_t *logic_index,T first, T second)
{
    size_list_t temp_logoc_index = logic_index[first];
    T temp_data = data_[first];

    logic_index[first] = logic_index[second];
    data_[first] = data_[second];

    logic_index[second] = temp_logoc_index;
    data_[second] = temp_data;
}

template <typename T>
size_list_t* List<T>::getLogicIndexArray()
{
    size_list_t * logic_index = (size_list_t *) calloc (length_, sizeof(T));
    size_list_t temp_index = head_;
    for (size_list_t i = 0; i < size_; i++){
        logic_index[temp_index] = i;
        temp_index = next_[temp_index];
    }
    return logic_index;
}

template <typename T>
void List<T>::closeLogicIndexArray(size_list_t* array)
{
    free(array);
}
template <typename T>
void List<T>::fillingPoisonousValues()
{
    for (size_list_t i = size_ + 1; i < length_; i++){
        data_[i] = 0;
        next_[i] = i + 1;
        prev_[i] = -1;
    }
    next_[length_ - 1] = 0;
    free_ = size_ + 1;
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
    if (num_error == 7) printf("Error, invalid logic index\n");
    if (num_error == 8) printf("Error in realloc data\n");
    if (num_error == 9) printf("Error in realloc next\n");
    if (num_error == 10) printf("Error in realloc prev\n");
    abort();
}

template <typename T>
void List<T>::Dump (){
    FILE* file = fopen("text_picture.dot", "wb");
    fprintf(file, "digraph structs {\n");
    fprintf(file, "rankdir=HR;\n");

    for (size_list_t i = 0; i < length_; i++){
        fprintf(file, "Index%d [shape=record, label=\" <index> Index%d | Value: %d| <next> next: %d | <prev> prev: %d \" ];\n", i, i, data_[i], next_[i], prev_[i]);
    }
    fprintf(file, "System [shape=record, label=\" <head> Head | <tail> Tail | <free> Free\" ];\n");
    fprintf(file, "System: <head> -> Index%d : <index>;\n", head_);
    fprintf(file, "System: <tail> -> Index%d : <index>;\n", tail_);
    fprintf(file, "System: <free> -> Index%d : <index>;\n", free_);

    size_list_t index = head_;
    for (size_list_t i = 1; i < length_; i++) {
        fprintf(file, "Index%d: <next> -> Index%d : <index>;\n", i, next_[i]);
        index = next_[index];
    }

    index = tail_;
    for (size_list_t i = 1; i < length_; i++) {
        if (prev_[i] != -1){
            fprintf(file, "Index%d: <prev> -> Index%d : <index>;\n", i, prev_[i]);
            index = prev_[index];
        }
    }



    fprintf(file, "}\n");
    fclose(file);
    system("dot text_picture.dot -T png -o test.png");
}



