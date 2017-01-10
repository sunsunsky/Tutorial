/*************************************************
Copyright (C), 2016-2020, Tech. Co., Ltd.
File name:dll.h
Author:  sunhao 
Version:  1.0
Date:   2017-01-06
Description:  
Function List: 
1. ....
History: 
1. Date: 2017-01-06
Author:sunhao
Modification:
2. ...
*************************************************/

#ifndef __DLINKLIST_H_INCLUDED
#define __DLINKLIST_H_INCLUDED
#define ITEMTYPE int 

typedef struct DllNode_S {
    struct DllNode_S *prev;
    struct DllNode_S *next;
    ITEMTYPE data;
}DllNode;

typedef struct {
    DllNode *first;
    DllNode *last;
    int size;
}Dlist;

#define DLL_SCAN(dllNum, pNode, dl) \
    for((dllNum) = 0, (pNode) = ((Dlist*)(dl))->first; (dllNum) < (((Dlist*)(dl))->size); (dllNum)++, pNode = ((DllNode *)(pNode))->next)

#define DLL_SAFE_SCAN(dllNum, pNode, pNodeTmp, dl) \
    for((dllNum) = 0, (pNodeTmp) = pNode = ((Dlist*)(dl))->first; (dllNum) < ((Dlist*)(dl))->size; (dllNum)++, pNodeTmp = pNode = ((DllNode *)(pNodeTmp))->next)

Dlist *dll_create();
void dll_initialize(Dlist *dl);
int dll_add_last(Dlist *dl, ITEMTYPE e);
//int add_dlist(Dlist *dl, ITEMTYPE e, int index);
int dll_add(Dlist *dl, DllNode *pNode);
int dll_add_in_front(Dlist *dl, DllNode *pNode);
int dll_delete(Dlist *dl, DllNode* pNodeInput);
int dll_size(Dlist *dl);
int dll_is_empty(Dlist *dl);
void dll_print(Dlist *dl);



int remove_dlist(Dlist *dl, int index, ITEMTYPE *e);
int remove_element_dlist(Dlist *dl, ITEMTYPE e);
int get_dlist(Dlist *dl, int index, ITEMTYPE *e);
int set_dlist(Dlist *dl, int index, ITEMTYPE e);
int index_of_dlist(Dlist *dl, ITEMTYPE e);
int contains_dlist(Dlist *dl, ITEMTYPE e);



#endif
