#pragma once
#define __QO_LIST_H__

#include "container_base.h"

#define QO_LIST(_T_element) QO_METHOD(QO_List , _T_element)

#define QO_LIST_TYPE(_T_element) \
    struct _QO_ListNode_##_T_element \
    { \
        _T_element                  data; \
        QO_ListNode_##_T_element *  next; \
        QO_ListNode_##_T_element *  prev; \
    }; \
    typedef QO_ListNode_##_T_element * QO_ListNodePtr_##_T_element; \
    struct _QO_List_##_T_element \
    { \
        qo_size_t                       element_count; \
        QO_ListNode_##_T_element *      head; \
        QO_ListNode_##_T_element *      tail; \
        QO_ListNode_##_T_element *      current; \
    }; \
    typedef struct _QO_List_##_T_element QO_List_##_T_element; \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_LIST(_T_element , init)( \
        QO_List_##_T_element * list \
    ) { \
        list->element_count = 0; \
        list->head = NULL; \
        list->tail = NULL; \
        list->current = NULL; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    void \
    QO_LIST(_T_element , destroy)( \
        QO_List_##_T_element * list \
    ) { \
        QO_LIST(_T_element , clear)(list); \
    } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    QO_ListNode##_T_element * \
    QO_LIST(_T_element , get_head)( \
        QO_List_##_T_element * list \
    ) { return list->head; } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    QO_ListNode##_T_element * \
    QO_LIST(_T_element , get_tail)( \
        QO_List_##_T_element * list \
    ) { return list->tail; } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    QO_ListNode##_T_element * \
    QO_LIST(_T_element , get_current)( \
        QO_List_##_T_element * list \
    ) { return list->current; } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , get_count)( \
        QO_List_##_T_element * list \
    ) { return list->element_count; } \
    \
    QO_FORCE_INLINE QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , to_prev)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->current->prev) \
            list->current = list->current->prev; \
        return !!(list->current->prev); \  
    } \
    \
    QO_FORCE_INLINE QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , to_next)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->current->next) \
            list->current = list->current->next; \
        return !!(list->current->next); \
    } \
    \
    QO_FORACE_INLINE QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , to_head)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->head) \
            list->current = list->head; \
        return !!(list->head); \
    } \
    \
    QO_FORCE_INLINE QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , to_tail)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->tail) \
            list->current = list->tail; \
        return !!(list->tail); \
    } \
    QO_GLOBAL_UNIQUE \
    void \
    QO_LIST(_T_element , mirror)( \
        QO_List_##_T_element * old_list , \
        QO_List_##_T_element * empty_list \
    ) { \
        empty_list->element_count = old_list->element_count; \
        empty_list->head = old_list->tail; \
        empty_list->tail = old_list->head; \
        empty_list->current = old_list->current; \
    } \
    \ 
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_current)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->element_count == 0 || list->next == NULL) { \
            return qo_false; \
        } \
        QO_ListNode_##_T_element * prev = list->current->prev; \
        QO_ListNode_##_T_element * next = list->current->next; \
        prev->next = next; \
        next->prev = prev; \
        free(list->current); \
        list->current = next; \
        list->element_count--; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_head)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->element_count == 0) \
            return qo_false; \
        QO_ListNode_##_T_element * head = list->head; \
        list->head = head->next; \
        free(head); \
        list->element_count--; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_tail)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->element_count == 0) \
            return qo_false; \
        QO_ListNode_##_T_element * tail = list->tail; \
        list->tail = tail->prev; \
        free(tail); \
        list->element_count--; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , clear)( \
        QO_List_##_T_element * list \
    ) { \
        qo_size_t count = list->element_count; \
        while (list->head != NULL) { \
            QO_LIST(_T_element , delete_head)(list); \
        } \
        return count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , locate)( \
        QO_List_##_T_element * list , \
        qo_size_t index \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        list->current = list->head; \
        for (qo_size_t i = 0; i < index; i++) \
            list->current = list->current->next; \
        return qo_true; \
    } \
    QO_GLOBAL_UNIQUE \
    void \
    QO_LIST(_T_element , insert_node_ahead)( \
        QO_List_##_T_element * list , \
        QO_ListNode_##_T_element * node \
    ) { \
        node->next = list->head; \
        node->prev = list->head->prev; \
        list->head->prev = node; \
        list->head = node; \
        list->element_count++; \
    } \
    QO_GLOBAL_UNIQUE \
    void \
    QO_LIST(_T_element , insert_node_behind)( \
        QO_List_##_T_element * list , \
        QO_ListNode_##_T_element * node \
    ) { \
        node->next = list->current; \
        node->prev = list->current->prev; \
        list->current->prev = node; \
        list->element_count++; \
    } \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , insert_element_ahead)( \
        QO_List_##_T_element * list , \
        _T_element element \
    ) { \
        QO_ListNode_##_T_element * node = malloc(sizeof(QO_ListNode_##_T_element)); \
        if (node) \
            QO_LIST(_T_element , insert_node_ahead)(list, node); \
        return !!(node); \
    } \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , insert_element_behind)( \
        QO_List_##_T_element * list , \
        _T_element element \
    ) { \
        QO_ListNode_##_T_element * node = malloc(sizeof(QO_ListNode_##_T_element)); \
        if (node) \
            QO_LIST(_T_element , insert_node_behind)(list, node); \
        return !!(node); \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , insert_element_at)( \
        QO_List_##_T_element * list , \
        qo_size_t index , \
        _T_element element \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        QO_ListNode_##_T_element * node = malloc(sizeof(QO_ListNode_##_T_element)); \
        if (node) \
            QO_LIST(_T_element , insert_node_ahead)(list, node); \
        return !!(node); \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t
    QO_LIST(_T_element , delete_next)( \
        QO_List_##_T_element * list \
    ) { \
        if (list->current->next) \
            return qo_false; \
        QO_ListNode_##_T_element * next = list->current->next; \
        list->current->next = next->next; \
        next->next->prev = list->current; \
        free(next); \
        list->element_count--; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QOLIST(_T_element , insert_element_reverse_at)( \
        QO_List_##_T_element * list , \
        qo_size_t index , \
        _T_element element \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        QO_ListNode_##_T_element * node = malloc(sizeof(QO_ListNode_##_T_element)); \
        if (node) \
        { \
            list->current = list->tail; \
            for (qo_size_t i = 0; i < index; i++) \
                list->current = list->current->prev; \
            QO_LIST(_T_element , insert_node_behind)(list, node); \
        } \
        return !!(node); \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_at)( \
        QO_List_##_T_element * list , \
        qo_size_t index \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        list->current = list->head; \
        for (qo_size_t i = 0; i < index; i++) \
            list->current = list->current->next; \
        list->current->prev->next = list->current->next; \
        list->current->next->prev = list->current->prev; \
        free(list->current); \
        list->element_count--; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_head_many)( \
        QO_List_##_T_element * list , \
        qo_size_t count \
    ) { \
        if (count >= list->element_count) \
            return qo_false; \
        for (qo_size_t i = 0; i < count; i++) \
            QO_LIST(_T_element , delete_head)(list); \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_LIST(_T_element , delete_tail_many)( \
        QO_List_##_T_element * list , \
        qo_size_t count \
    ) { \
        if (count >= list->element_count) \
            return qo_false; \
        for (qo_size_t i = 0; i < count; i++) \
            QO_LIST(_T_element , delete_tail)(list); \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , delete_many_at)( \
        QO_List_##_T_element * list , \
        qo_size_t index , \
        qo_size_t count \
    ) { \
        qo_size_t deleted_count = 0; \
        if (index >= list->element_count) \
            return qo_false; \
        list->current = list->head; \
        for (qo_size_t i = 0; i < index; i++) \
            list->current = list->current->next; \
        for (; deleted_count < count; deleted_count++) \
        { \
            list->current->next->prev = list->current->prev; \
            list->current->prev->next = list->current->next; \
            free(list->current); \
        } \
        list->element_count -= deleted_count; \
        return deleted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , delete_all)( \
        QO_List_##_T_element * list \
    ) { \
        qo_size_t deleted_count = 0; \
        for(; list->element_count > 0; deleted_count++) \
            QO_LIST(_T_element , delete_head)(list); \
        return deleted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , delete_reverse_many_at)( \
        QO_List_##_T_element * list , \
        qo_size_t index , \
        qo_size_t count \
    ) { \
        qo_size_t deleted_count = 0; \
        if (index >= list->element_count) \
            return qo_false; \
        list->current = list->tail; \  
        count = QO_MIN(count , list->element_count - index); \
        for (qo_size_t i = 0; i < index; i++) \
            list->current = list->current->prev; \
        for (; deleted_count < count; deleted_count++) \
        { \
            list->current->prev->next = list->current->next; \
            list->current->next->prev = list->current->prev; \
            free(list->current); \
        } \
        list->element_count -= deleted_count; \
        return deleted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , delete_after)( \
        QO_List_##_T_element * list , \
        qo_size_t index \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        qo_size_t nodes_to_delete = list->element_count - index - 1; \
        for (qo_size_t i = 0; i < nodes_to_delete; i++) { \
            QO_ListNode_##_T_element * node = list->current->next; \
            list->current->next = node->next; \
            node->next->prev = list->current; \
            free(node); \
        } \
        list->element_count -= nodes_to_delete; \
        return nodes_to_delete; \
    } \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , delete_before)( \
        QO_List_##_T_element * list , \
        qo_size_t index \
    ) { \
        if (index >= list->element_count) \
            return qo_false; \
        qo_size_t nodes_to_delete = index; \
        for (qo_size_t i = 0; i < nodes_to_delete; i++) \
            QO_LIST(_T_element , delete_head)(list); \
        return nodes_to_delete; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , insert_next_nodes)( \
        QO_List_##_T_element * list , \
        QO_ListNode_##_T_element * nodes , \
        qo_size_t count \
    ) { \
        QO_ListNode_##_T_element * new_node = NULL; \
        qo_size_t inserted_count = 0; \
        for (;inserted_count < count; i++) \
        { \
            new_node = (QO_ListNode_##_T_element *)malloc(sizeof(QO_ListNode_##_T_element)); \
            if (new_node) \
            { \
                new_node->data = nodes[i].data; \
                new_node->next = list->current->next; \
                new_node->prev = list->current; \
                QO_LIST(_T_element , insert_next_node)(list , new_node); \
            } \
            else break; \
        } \
        return inserted_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_LIST(_T_element , insert_prev_nodes)( \
        QO_List_##_T_element * list , \
        QO_ListNode_##_T_element * nodes , \
        qo_size_t count \
    ) { \
        QO_ListNode_##_T_element * new_node = NULL; \
        qo_size_t inserted_count = 0;
        for (;inserted_count < count; i++) \
        { \
            new_node = (QO_ListNode_##_T_element *)malloc(sizeof(QO_ListNode_##_T_element)); \
            if (new_node) \
            { \
                new_node->data = nodes[i].data; \
                new_node->next = list->current; \
                new_node->prev = list->current->prev; \
                QO_LIST(_T_element , set_head)(list , new_node); \
            } \
            else break; \
        } \
        return inserted_count; \
    } \


#define QO_LIST_ITERATE(_T_element , list , p_current) \
    for (QO_ListNode_##_T_element * p_current = list->head; \
         p_current != NULL; \
         p_current = p_current->next)

#define QO_LIST_REVERSE_ITERATE(_T_element , list , p_current) \
    for (QO_ListNode_##_T_element * p_current = list->tail; \
         p_current != NULL; \
         p_current = p_current->prev)







