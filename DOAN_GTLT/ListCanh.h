#ifndef LISTCANH_H
#define LISTCANH_H
#include "Canh.h"
#include <iostream>

typedef struct
{
    int count;
    Canh* head;
}ListCanh;



void initListCanh(ListCanh& listCanh)
{
    listCanh.count = 0;
    listCanh.head = NULL;
}

void printList(ListCanh& listCanh)
{
    Canh* cur = listCanh.head;
    while (cur != NULL)
    {
        std::cout << "(" << cur->r << ", " << cur->s << ") ";
        cur = cur->next;
    }
}

void detroyListCanh(ListCanh& l)
{
    Canh* cur = l.head;
    while (cur != NULL)
    {
        l.head = cur->next;
        delete cur;
        cur = l.head;
    }
}

void addCanh(ListCanh& l, Canh canh)
{
    if (l.head == NULL)
    {
        l.head = new Canh;
        l.count = 1;
        l.head->r = canh.r;
        l.head->s = canh.s;
        l.head->next = NULL;
    }
    else
    {
        Canh* cur = l.head;
        Canh* temp = new Canh;
        temp->r = canh.r;
        temp->s = canh.s;
        temp->next = NULL;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = temp;
        l.count++;
    }
}
void sortListCanh(ListCanh& l)
{
    if (l.count < 2)
    {
        return;
    }
    // sap xep doan thu 1
    Canh* cur = l.head;
    Canh* temp;
    while (cur->next != NULL)
    {
        if (l.head->r == cur->next->s)
        {
            temp = cur->next;
            cur->next = temp->next;
            temp->next = l.head;
            l.head = temp;
            cur = l.head;
        }
        else
        {
            cur = cur->next;
        }
    }
    // sap xep doan thu 2
    cur = l.head;
    while (cur->s == cur->next->r)
    {
        cur = cur->next;
        if (cur->next == NULL)
        {
            return; // neu chi co 1 khuc
        }
    }
    Canh* cur2 = cur->next;
    Canh* cur3 = cur2;
    while (cur3->next != NULL)
    {
        if (cur2->r == cur3->next->s)
        {
            temp = cur3->next;
            cur3->next = temp->next;
            temp->next = cur2;
            cur2 = temp;
            cur3 = cur2;
            cur->next = cur2;
        }
        else
        {
            cur3 = cur3->next;
        }
    }
}
void copyListCanh(ListCanh& listCanh, ListCanh& o)
{
    if (o.count != 0)
    {
        Canh* cur = o.head;
        listCanh.head = new Canh;
        listCanh.count = o.count;
        listCanh.head->r = cur->r;
        listCanh.head->s = cur->s;
        listCanh.head->next = NULL;
        Canh* cur2 = listCanh.head;
        Canh* temp;
        cur = cur->next;
        while (cur != NULL)
        {
            temp = new Canh;
            temp->r = cur->r;
            temp->s = cur->s;
            temp->next = NULL;
            cur2->next = temp;
            cur2 = cur2->next;
            cur = cur->next;
        }
    }
}

#endif
