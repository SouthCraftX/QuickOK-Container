#pragma once
#define __QO_FWLIST_H__

#include "container_base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define QO_FWLIST(_T_element , method_name) \
        QO_METHOD(qo_fwlist , _T_element , method_name)     

// You must user QO_CONTAINER_REGISTERED to check whether the type is registered 
// before using the macro
/// @code {.c}
/// #if !defined(QO_CONTAINER_REGISTERED(YourDataType))
///     QO_REGISTER_FWLIST_TYPE(YourDataType)
/// #    define QO_CONTAINER_REGISTERED(QO_FWList , YourDataType)
/// #endif
/// @endcode
#define QO_REGISTER_FWLIST(_T_element)                              \
    struct _QO_FWListNode_##_T_element \
    {    \
        _T_element      data; \
        _T_element *    next; \
    };                                          \
    typedef struct _QO_FWListNode_##_T_element QO_FWListNode_##_T_element; \
    struct _QO_FWList_##_T_element               \
    {                                          \
        qo_size_t                       element_count;         \
        QO_FWListNode_##_T_element *    head;  \               
        QO_FWListNode_##_T_element *    tail;  \   
        QO_FWListNode_##_T_element *    current; \
    };                                         \    
    typedef struct _QO_FWList_##_T_element QO_FWList_##_T_element; \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , init)( \
        QO_FWList_##_T_element * list \
    ) { \
        list->element_count = 0; \
        list->head = NULL; \
        list->tail = NULL; \
        list->current = NULL; \
    } \
    /* Mirror old_list. This method does NOT allocate new individual nodes for @p empty_list! */\
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , mirror)( \
        QO_FWList_##_T_element * old_list , \
        QO_FWList_##_T_element * empty_list \
    ) { \
        empty_list->element_count = old_list->element_count; \
        empty_list->head = old_list->head; \
        empty_list->tail = old_list->tail; \
        empty_list->current = old_list->current; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , is_empty)( \
        QO_FWList_##_T_element * list \
    ) {return list->element_count == 0; } \
    \
    QO_GLOBAL_UNIQUE \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , get_current)( \
        QO_FWList_##_T_element * list , \
    ) {return list->current; } \
    \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , get_head)( \
        QO_FWList_##_T_element * list \
    ) {return list->head; } \
    \
    QO_GLOBAL_UNIQUE \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , get_tail)( \
        QO_FWList_##_T_element * list \
    ) {return list->tail; } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , get_element_count)( \
        QO_FWList_##_T_element * list \
    ) {return list->element_count; } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , to_head)( \
        QO_FWList_##_T_element * list  \
    ) {list->current = list->head; } \
    \
    void \
    QO_FWLIST(_T_element , to_tail)( \
        QO_FWList_##_T_element * list  \
    ) {list->current = list->tail; } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , locate)( \
        QO_FWList_##_T_element * list , \
        qo_size_t index \
    ) { \
        if (index >= list->element_count) { \
            return qo_false; \
        } \
        list->current = list->head; \
        for (qo_size_t i = 0; i < index; i++) { \
            list->current = list->current->next; \
        } \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , duplicate_node)( \
        QO_FWListNode_##_T_element * node \
    ) { \
        QO_FWListNode_##_T_element * new_node = (QO_FWListNode_##_T_element *)malloc(sizeof(QO_FWListNode_##_T_element)); \
        if (new_node) \
        { \
            new_node->data = node->data; \
            new_node->next = NULL; \
        } \
        return new_node; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , reverse_head)( /* Reverse head two nodes*/\
        QO_FWList_##_T_element * list  \
    ) { \
        if (list->head == NULL) { \
            return qo_false; \
        } \
        if (list->head->next == NULL) { \
            return qo_false; \
        } \
        QO_FWListNode_##_T_element * temp = list->head->next->next; \
        list->head->next->next = list->head; \
        list->head = list->head->next; \
        list->head->next->next = temp; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , reverse)( \
        QO_FWList_##_T_element * list  \
    ) { \
        QO_FWListNode_##_T_element * head = list->head; \
        QO_FWListNode_##_T_element * prev = NULL; \
        QO_FWListNode_##_T_element * current = head; \
        QO_FWListNode_##_T_element * next = NULL; \
        while (current != NULL) \
        { \
            next = current->next; \
            current->next = prev; \
            prev = current; \
            current = next; \
        } \
        head = prev; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_next_node)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert \
    ) { /* Here, we must ensure these are at least a node in the list */ \ 
        list->tail->next = node_to_insert; \
        list->tail = node_to_insert; \
        list->element_count++; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_next_nodes)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert , \
        qo_size_t node_count \
    ) { \
        QO_FWListNode_##_T_element * node = node_to_insert; \
        for (qo_size_t i = 0; i < node_count; i++) \
        { \
            QO_FWLIST(_T_element , insert_next_node)(list , node); \
            node = node->next; \
        } \
    } \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , insert_next_element)( \
        QO_FWList_##_T_element *    list , \
        _T_element                  element \
    ) { \
        QO_FWListNode_##_T_element * node = malloc(sizeof(QO_FWListNode_##_T_element)); \
        /*  TODO: Replace malloc with qo_malloc */ \
        if (node) \
        { \
            node->data = element; \
            node->next = NULL; \
            QO_FWLIST(_T_element , insert_next_node)(list , node); \
            return qo_true; \
        } \
        return qo_false; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , insert_next_elements)( \
        QO_FWList_##_T_element * list , \
        _T_element * elements , \
        qo_size_t element_count \
    ) { \
        qo_size_t inserted_count = 0; \
        for(; inserted_count < element_count; inserted_count++) {  \
            if(QO_FWLIST(_T_element , insert_next_element)(list , elements[inserted_count]))  \
                return inserted_count; \
        } \
        return inserted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_head_node)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert \
    ) { \
        if (list->head == NULL) \
        { \
            list->head = node_to_insert; \
            list->tail = node_to_insert; \
            list->element_count++; \
            return; \
        } \
        node_to_insert->next = list->head; \
        list->head = node_to_insert; \
        list->element_count++; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_head_nodes)( \
        QO_FWList_##_T_element *        list , \
        QO_FWListNode_##_T_element *    nodes_to_insert , \
        qo_size_t                       node_count \
    ) { \
        QO_FWListNode_##_T_element * node = node_to_insert; \
        qo_size_t inserted_count = 0; \
        for(; inserted_count < node_count; inserted_count++) {  \
            QO_FWLIST(_T_element , insert_head_node)(list , node); \
            node = node->next; \
        } \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , insert_head_element)( \
        QO_FWList_##_T_element *    list , \
        _T_element                  element \
    ) { \
        QO_FWListNode_##_T_element * node = malloc(sizeof(QO_FWListNode_##_T_element)); \
        /*  TODO: Replace malloc with qo_malloc */ \
        if (node) \
        { \
            node->data = element; \
            node->next = NULL; \
            QO_FWLIST(_T_element , insert_head_node)(list , node); \
            return qo_true; \
        } \
        return qo_false; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , insert_head_elements)( \
        QO_FWList_##_T_element * list , \
        _T_element * elements , \
        qo_size_t element_count \
    ) { \
        qo_size_t inserted_count = 0; \
        for(; inserted_count < element_count; inserted_count++) {  \
            if(QO_FWLIST(_T_element , insert_head_element)(list , elements[inserted_count]))  \
                return inserted_count; \
        } \
        return inserted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_tail_node)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert \
    ) { \
        if (list->tail == NULL) \
        { \
            list->head = node_to_insert; \
            list->tail = node_to_insert; \
            list->element_count++; \
            return; \
        } \
        element->next = list->tail; \
        list->tail = element; \
        list->element_count++; \
    } \ 
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_tail_nodes)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert , \
        qo_size_t node_count \
    ) { \
        QO_FWListNode_##_T_element * node = node_to_insert; \
        for (qo_size_t i = 0; i < node_count; i++) \
        { \
            QO_FWLIST(_T_element , insert_tail_node)(list , node); \
            node = node->next; \
        } \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , insert_tail_element)( \
        QO_FWList_##_T_element *    list , \
        _T_element                  element \
    ) { \
        QO_FWListNode_##_T_element * node = malloc(sizeof(QO_FWListNode_##_T_element)); \
        /*  TODO: Replace malloc with qo_malloc */ \
        if (node) \
        { \
            node->data = element; \
            node->next = NULL; \
            QO_FWLIST(_T_element , insert_tail_node)(list , node); \
            return qo_true; \
        } \
        return qo_false; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , insert_tail_elements)( \
        QO_FWList_##_T_element * list , \
        _T_element * elements , \
        qo_size_t element_count \
    ) { \
        qo_size_t inserted_count = 0; \
        for(; inserted_count < element_count; inserted_count++) {  \
            if(QO_FWLIST(_T_element , insert_tail_element)(list , elements[inserted_count]))  \
                return inserted_count; \
        } \
        return inserted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , insert_node_at)( \
        QO_FWList_##_T_element * list , \
        QO_FWListNode_##_T_element * node_to_insert , \
        qo_size_t index \
    ) { \
        QO_FWListNode_##_T_element * current = list->current; \
        QO_FWLIST(_T_element , locate)(list , index); \
        QO_FWLIST(_T_element , insert_next_node)(list , node_to_insert); \
        list->current = current; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_FWLIST(_T_element , insert_element_at)( \
        QO_FWList_##_T_element * list , \
        _T_element element , \
        qo_size_t index \
    ) { \
        QO_FWListNode_##_T_element * node = malloc(sizeof(QO_FWListNode_##_T_element)); \
        /*  TODO: Replace malloc with qo_malloc */ \
        if (node) \
        { \
            node->data = element; \
            node->next = NULL; \
            QO_FWLIST(_T_element , insert_node_at)(list , node , index); \
            return qo_true; \
        } \
        return qo_false; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , delete_at)( \
        QO_FWList_##_T_element * list , \
        qo_size_t index \
    ) { \
        QO_FWListNode_##_T_element * current = list->current; \
        QO_FWLIST(_T_element , locate)(list , index - 1); \
        QO_FWLIST(_T_element , delete_next)(list); \
        list->current = current; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , delete_next)( \
        QO_FWList_##_T_element * list \
    ) { \
        QO_FWListNode_##_T_element * node = list->current->next; \
        list->current->next = list->current->next->next; \
        free(node); \
        list->element_count--; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_FWLIST(_T_element , delete_head)( \
        QO_FWList_##_T_element * list \
    ) { \
        QO_FWListNode_##_T_element * node = list->head; \
        list->head = list->head->next; \
        free(node); \
        list->element_count--; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , delete_after)( \
        QO_FWList_##_T_element * list , \
        qo_size_t index \
    ) { \
        QO_FWListNode_##_T_element * node = NULL; \
        qo_size_t original_element_count = list->element_count; \
        QO_FWLIST(_T_element , locate)(list , index); \
        while(list->current->next) { \
            node = list->current->next; \
            list->current->next = list->current->next->next; \
            free(node); \
            list->element_count--; \
        } \
        return original_element_count - list->element_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , delete_before)( \
        QO_FWList_##_T_element * list , \
        qo_size_t index \
    ) { \
        QO_FWListNode_##_T_element * node = NULL; \
        qo_size_t original_element_count = list->element_count; \
        /* TODO: */ \
    } \
    \
    QO_GLOBAL_UNIQUE \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , unlink_next)( \
        QO_FWList_##_T_element * list \
    ) { \
        QO_FWListNode_##_T_element * node = list->current->next; \
        list->current->next = list->current->next->next; \
        return node; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    QO_FWListNode_##_T_element * \
    QO_FWLIST(_T_element , unlink_head)( \
        QO_FWList_##_T_element * list \
    ) { \
        QO_FWListNode_##_T_element * node = list->head; \
        list->head = list->head->next; \
        return node; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_FWLIST(_T_element , delete_all)( \
        QO_FWList_##_T_element * list \
    ) { \
        QO_FWListNode_##_T_element * node = list->head; \
        while(node) { \
            QO_FWListNode_##_T_element * next = node->next; \
            free(node); \
            node = next; \
        } \
        list->head = NULL; \
        list->tail = NULL; \
        list->current = NULL; \
        list->element_count = 0; \
        return list->element_count; \
    } \
    

#define QO_FWLIST_ITERATE(_T_element , list , p_current) \
    for(p_current = list->head; 
        p_current != NULL; \
        p_current = p_current->next
    ) 

#if defined(__cplusplus)
}
#endif // __cplusplus