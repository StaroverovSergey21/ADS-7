// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
  struct ITEM {
    T value;
    ITEM* next;
    ITEM* prev;
  };
  ITEM* head;
  ITEM* tail;
  ITEM* curr;
  ITEM* create(const T& value) {
    ITEM* tmp = new ITEM;
    tmp->value = value;
    tmp->next = nullptr;
    tmp->prev = nullptr;
    return tmp;
  }

 public:
  TPQueue() :head(nullptr), tail(nullptr), curr(nullptr) {}
  ~TPQueue() {}
  void push(const T& value) {
    if (tail && head) {
      ITEM* tmp = head;
      if (tmp->value.prior < value.prior) {
        tmp = create(value);
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
      } else {
        while (tmp->next) {
          if (tmp->next->value.prior < value.prior) {
            ITEM * temp = create(value);
            temp->next = tmp->next;
            tmp->prev = temp->prev;
            tmp->next = temp;
            temp->prev = tmp;
            break;
          } else {
            tmp = tmp->next;
          }
        }
      }
      if (!tmp->next) {
        tail->next = create(value);
        tail->next->prev = tail;
        tail = tail->next;
      }
    } else {
      head = create(value);
      tail = head;
    }
  }
  T pop() {
    ITEM* tmp = head->next;
    T value = head->value;
    delete head;
    head = tmp;
    return value;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
