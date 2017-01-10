#include "dlinklist.h"
#include <stdio.h>
#include <stdlib.h>


Dlist *dll_create() {
    Dlist *dl = (Dlist*) malloc(sizeof(Dlist));
    dll_initialize(dl);
    return dl;
}
void dll_initialize(Dlist *dl) {
    dl->size = 0;
    dl->first = NULL;
    dl->last = NULL;
    return;
}
int dll_add_last(Dlist *dl, ITEMTYPE e) {
    DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
    aux->data = e;
    if (dl->size == 0) {
        aux->prev = NULL;
        aux->next = NULL;
        dl->first = aux;
        dl->last = aux;    
        dl->size++;
        return 1;
        
    }
    else if(dl->size == 1) {
        aux->next = NULL;
        aux->prev = dl->first;
        dl->first->next = aux;
        dl->last = aux;
        dl->size++;
        return 1;
    }
    else {
        aux->prev = dl->last;
        dl->last->next = aux;
        aux->next = NULL;
        dl->last = aux;
        dl->size++;
        return 1;
    } 
    return 0;
}

/* 在尾部插入节点 */
int dll_add(Dlist *dl, DllNode *pNode)
{
    if (dl->size == 0) {
        pNode->prev = NULL;
        pNode->next = NULL;
        dl->first = pNode;
        dl->last = pNode;    
        dl->size++;
        return 1;
        
    }
    else if(dl->size == 1) {
        pNode->next = NULL;
        pNode->prev = dl->first;
        dl->first->next = pNode;
        dl->last = pNode;
        dl->size++;
        return 1;
    }
    else {
        pNode->prev = dl->last;
        dl->last->next = pNode;
        pNode->next = NULL;
        dl->last = pNode;
        dl->size++;
        return 1;
    }
    
    return 0;

}

int dll_add_in_front(Dlist *dl, DllNode *pNode)
{
    if (dl->size == 0) {
        pNode->prev = NULL;
        pNode->next = NULL;
        dl->first = pNode;
        dl->last = pNode;    
        dl->size++;
        return 1;
        
    }
    else if(dl->size == 1) {
        pNode->next = NULL;
        pNode->prev = dl->first;
        dl->first->next = pNode;
        dl->last = pNode;
        dl->size++;
        return 1;
    }
    else {
        dl->first->next = pNode;
        pNode->prev = NULL;
        pNode->next = dl->first;
        dl->first = pNode;
        dl->size++;
        return 1;
    } 
    return 0;

}


/* 删除指针节点*/ 
int dll_delete(Dlist *dl, DllNode* pNodeInput)
{
    int dllNum = 0;
    DllNode* pNodeTmp = 0;    
    DllNode* pNode = 0;

    if (dl->size == 0) {
        return 1;
    }
    else if(dl->size == 1) {
        pNodeInput->next = NULL;   //test_dll_add1
        pNodeInput->prev = NULL;   //
        dl->size = 0;
        dl->first = NULL;
        dl->last = NULL;
        return 0;
    }
    
    else 
    {
        //for(dllNum = 0, pNodeTmp = pNode = dl->first; dllNum < dl->size; dllNum++, pNode = pNodeTmp, pNode = pNode->next)
        DLL_SAFE_SCAN(dllNum, pNode, pNodeTmp, dl)
        {
            if (pNode == pNodeInput)
            {
                
                /* if first or last */
                if (pNode == dl->first)
                {
                    dl->first = pNode->next;
                    pNode->next->prev = NULL;
                }
                else if (pNode == dl->last)
                {
                    dl->last = pNode->prev;
                    pNode->prev->next = NULL;
                }
                else
                {
                    /* delete node*/   //test_dll_add2del1
                    pNode->prev->next = pNode->next;
                    pNode->next->prev = pNode->prev;
                }
                
                pNode->next = NULL;
                pNode->prev = NULL;
                dl->size --;
                
                break;
            }
        }
    }
   
    return 0;
}


void dll_print(Dlist *dl) {
    DllNode *aux = (DllNode *) malloc(sizeof(DllNode));
    aux = dl->first;
    int i;
    for(i = 0; i < dl->size; i++) {
        printf("%d\n", aux->data);
        aux = aux->next;
    }
    printf("\n\n\n");
    free(aux);
    return;
}



int add_dlist(Dlist *dl, ITEMTYPE e, int index) {
    if(index < 0 || index > dl->size) {
        return 0;
    }
    else if (index == dl->size || dl->size == 0) {
        dll_add_last(dl,e);
        return 1;
    }
    else if(dl->size != 0 && index == 0) {
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux->data = e;
        aux->prev = NULL;
        aux->next = dl->first;
        dl->first = aux;
        dl->size++;
        return 1;
    }
    else {
        DllNode *aux1 = (DllNode*) malloc(sizeof(DllNode));
        DllNode *aux2 = (DllNode*) malloc(sizeof(DllNode));
        DllNode *aux3 = (DllNode*) malloc(sizeof(DllNode));
        aux1 = dl->first;
        aux2 = dl->first;
        
        int i;
        for(i = 0; i < index; i++) {
            aux1 = aux1->next;
        }
        for(i = 0; i < index - 1; i++) {
            aux2 = aux2->next;
        }
        aux3->data = e;
        aux2->next = aux3;
        aux3->prev = aux2;
        aux1->prev = aux3;
        aux3->next = aux1;
        dl->size++;
        return 1;
    }
    return 0;
}
int remove_dlist(Dlist *dl, int index, ITEMTYPE *e) {
    if(index < 0 || index > dl->size || dl->size == 0) {
        return 0;
    }
    else if(index == 0) {
        *e = dl->first->data;
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux = dl->first->next;
        dl->first = aux;
        dl->first->prev = NULL;
        dl->size--;
        return 1;
    }
    else if(index == dl->size - 1) {
        *e = dl->last->data;
        dl->last = dl->last->prev;
        dl->size--;
        return 1;
    } 
    else {
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux = dl->first;
        int i;
        for(i = 0; i < index - 1; i++) {
            aux = aux->next;
        }
        *e = aux->next->data;
        aux->next = aux->next->next;
        dl->size--;
        return 1;
    }
    return 0;        
}

int remove_element_dlist(Dlist *dl, ITEMTYPE e) {
    if(dl->size == 0 || contains_dlist(dl,e) == 0) {
        return 0;    
    }
    else {
        int i;
        ITEMTYPE k;
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux = dl->first;
        for(i = 0; i < dl->size; i++) {
            if(aux->data == e) {
                remove_dlist(dl,i,&k);
            }
            if(contains_dlist(dl,e) == 0) {
                return 1;
            }
            aux = aux->next;
        }

    }
    return 0;
}

/*  判断包含元素吗*/
int contains_dlist(Dlist *dl, ITEMTYPE e) {
    DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
    aux = dl->first;
    int i;
    for(i = 0; i < dl->size; i++) {
        if(aux->data == e) {
            return 1;
        }
        aux = aux->next;
    }
    free(aux);
    return 0;
}

int dll_size(Dlist *dl) {
    return dl->size;
}
int dll_is_empty(Dlist *dl) {
    if(dl->size == 0) {
        return 1;
    }
    return 0;
}
int set_dlist(Dlist *dl, int index, ITEMTYPE e) {
    if(index < 0  || index >= dl->size) {
        return 0;
    }
    else {
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux = dl->first;
        int i;
        for(i = 0; i != index ; i++) {
            aux = aux->next;
        }
        aux->data = e;
        return 1;
    }
    return 0;
}
int get_dlist(Dlist *dl, int index, ITEMTYPE *e) {
    if(index < 0 || index >= dl->size) {
        return 0;
    }
    else {
        DllNode *aux = (DllNode*) malloc(sizeof(DllNode));
        aux = dl->first;
        int i;
        for(i = 0; i != index; i++) {
            aux = aux->next;
        }
        *e = aux->data;
        return 1;
    }
    return 0;
}
 

/*
int get_dlist(List *l, int index, ITEMTYPE *e);

;*/


#ifdef __TEST
#include <assert.h>

int test_dll_add4()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    dll_add(dl, &stNode3);
    dll_add(dl, &stNode4);

    dll_print(dl);

    return  (dll_size(dl) == 4);
}
 
/*  插入一个 删除一个*/
int test_dll_add1()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    //dll_add(dl, &stNode2);
    //dll_add(dl, &stNode3);
    //dll_add(dl, &stNode4);

    dll_delete(dl, &stNode1);

    dll_print(dl);

    return  (dll_size(dl) == 0);
}


/*  插入2个 删除第一个*/
int test_dll_add2del1()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    //dll_add(dl, &stNode3);
    //dll_add(dl, &stNode4);

    dll_delete(dl, &stNode1);

    dll_print(dl);

    return  (dll_size(dl) == 1);
}

/*  插入2个 删除第2个*/
int test_dll_add2dellast()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    //dll_add(dl, &stNode3);
    //dll_add(dl, &stNode4);

    dll_delete(dl, &stNode2);

    dll_print(dl);

    return  (dll_size(dl) == 1);
}


/*  插入3个 删除第2个*/
int test_dll_add3delmid()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    dll_add(dl, &stNode3);
    //dll_add(dl, &stNode4);

    dll_delete(dl, &stNode2);

    dll_print(dl);

    return  (dll_size(dl) == 2);
}

/*  插入4个 删除第2个*/
int test_dll_add4delmid()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    dll_add(dl, &stNode3);
    dll_add(dl, &stNode4);

    dll_delete(dl, &stNode2);
    dll_delete(dl, &stNode1);

    dll_print(dl);

    return  (dll_size(dl) == 2);
}




/*  插入4个 删除后2个*/
int test_dll_add4del2()
{
    DllNode stNode1 = {0 ,0, 10};
    DllNode stNode2 = {0 ,0, 20};
    DllNode stNode3 = {0 ,0, 30};
    DllNode stNode4 = {0 ,0, 40};

    Dlist *dl = dll_create();

    dll_add(dl, &stNode1);
    dll_add(dl, &stNode2);
    dll_add(dl, &stNode3);
    dll_add(dl, &stNode4);

    dll_delete(dl, &stNode3);
    dll_delete(dl, &stNode4);

    dll_print(dl);

    return  (dll_size(dl) == 2);
}


int test_dll_add4aa()
{
    ITEMTYPE removed;
    DllNode *pNode = 0;
    Dlist *dl = dll_create();
    dll_add_last(dl,10);
    dll_add_last(dl,20);
    dll_add_last(dl,30);  
    dll_add_last(dl,40);
#if 0
    add_dlist(dl,70,1);
    add_dlist(dl,80,0); 
    remove_dlist(dl,5,&removed);
    remove_dlist(dl,2,&removed);
    remove_dlist(dl,0,&removed); 
    set_dlist(dl,0,35);
    remove_element_dlist(dl,20);   
    remove_dlist(dl,0,&removed);  

    dll_print(dl); 
     
#endif
    int n;
    int pDllNum = 0;


//    for(pDllNum = 0, pNode = dl->first; pDllNum < dl->size; pDllNum++, pNode = pNode->next)
    for(pDllNum = 0, pNode = dl->first; pDllNum < dl->size; pDllNum++, pNode = pNode->next)
    {
        printf("%d\n", pNode->data);
    }

    DLL_SCAN(pDllNum, pNode, dl)
    {
        printf("2 %d\n", pNode->data);
    }
    
    
    get_dlist(dl,0,&n); 
    printf("testando get_dlist(dl,0,&n) = %d\n",n);

}

int main() 
{   

    int ret;

    ret = test_dll_add4del2();
    assert(ret);
        
    ret = test_dll_add4delmid();
    assert(ret);

    ret = test_dll_add3delmid();
    assert(ret);
    
    ret = test_dll_add2dellast();
    assert(ret); 

#if 1
    ret = test_dll_add2del1();
    assert(ret); 
       

    ret = test_dll_add1();
    assert(ret);

    ret = test_dll_add4();
    assert(ret);
#endif
    

    return 0;

} 


#endif 
