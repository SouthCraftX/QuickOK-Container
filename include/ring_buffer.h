#pragma once
#define __QO_RING_BUFFER_H__

#include "container_base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define QO_RINGBUF(_T_element , method_name) \
        QO_METHOD(qo_ringbuf , _T_element , method_name)     

#define QO_RINGBUF_DEFAULT_INIT_COUNT 16

#define QO_REGISTER_RINGBUF(_T_element) \
    struct _QO_Ringbuf_##_T_element \
    { \
        qo_size_t       buffer_mask; \
        qo_size_t       head_index; \
        qo_size_t       tail_index; \
        _T_element *    elements; \
    } \
    typedef struct _QO_Ringbuf_##_T_element QO_Ringbuf_##_T_element; \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    qo_bool_t \
    QO_RINGBUF(_T_element , init)( \
        QO_Ringbuf_##_T_element * ringbuf \
    ) { \
        return QO_RINGBUF(_T_element , init_count)( \
            ringbuf ,  \
            QO_RINGBUF_DEFAULT_INIT_COUNT \
        ); \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , init_count)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        qo_size_t count \
    ) { \
        QO_ASSERT((count > 0) && QO_IS_POW2(count)); \
        _T_element * buffer = malloc(count * sizeof(_T_element)); \
        if (buffer) \
        { \
            ringbuf->element_count = count; \
            ringbuf->head_index = 0; \
            ringbuf->tail_index = 0; \
            ringbuf->elements = buffer; \
            return qo_true; \
        } \
        return qo_false; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_RINGBUF(_T_element , destroy)( \
        QO_Ringbuf_##_T_element * ringbuf \
    ) { \
        if (ringbuf->elements) \
            free(ringbuf->elements); \
        ringbuf->element_count = 0; \
        ringbuf->head_index = 0; \
        ringbuf->tail_index = 0; \  
        ringbuf->elements = NULL; \
    } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    qo_bool_t \
    QO_RINGBUF(_T_element , is_empty)( \
        QO_Ringbuf_##_T_element * ringbuf \
    ) { \
        return ringbuf->head_index == ringbuf->tail_index; \
    } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    qo_bool_t \
    QO_RINGBUF(_T_element , is_full)( \
        QO_Ringbuf_##_T_element * ringbuf \
    ) { \
        return ((ringbuf->head_index == ringbuf->tail_index) & ringbuf->buffer_mask) \
                == \
                ringbuf->buffer_mask; \
    } \
    \
    QO_GLOBAL_UNIQUE QO_FORCE_INLINE \
    qo_size_t \
    QO_RINGBUF(_T_element , get_count) ( \
        QO_Ringbuf_##_T_element * ringbuf \
    ) { \
        return (ringbuf->head_index - ringbuf->tail_index) & ringbuf->buffer_mask; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , push)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * p_element \
    ) { \
        if (QO_RINGBUF(_T_element , is_full)(ringbuf)) \
            return qo_false; \
        ringbuf->elements[ringbuf->head_index] = *p_element; \
        ringbuf->head_index = ((ringbuf->head_index + 1) & ringbuf->buffer_mask); \
        return qo_true; \
    } \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_RINGBUF(_T_element , push_many)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * elements , \
        qo_size_t count \
    ) { \
        QO_ASSERT(count); \
        qo_size_t pushed_count = 0; \
        qo_bool_t is_pushed = qo_true; \
        do \
        { \
            is_pushed = QO_RINGBUF(_T_element , push)(ringbuf, elements[pushed_count]); \
        } while (is_pushed && (++pushed_count < count)); \
        return pushed_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , pop)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * p_element \
    ) { \
        if (QO_RINGBUF(_T_element , is_empty)(ringbuf)) \
            return qo_false; \
        *p_element = ringbuf->elements[ringbuf->tail_index]; \
        ringbuf->tail_index = ((ringbuf->tail_index + 1) & ringbuf->buffer_mask); \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_size_t \
    QO_RINGBUF(_T_element , pop_many)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * elements , \
        qo_size_t count \
    ) { \
        QO_ASSERT(count); \
        qo_size_t popped_count = 0; \
        qo_bool_t is_popped = qo_true; \
        do \
        { \
            is_popped = QO_RINGBUF(_T_element , pop)(ringbuf, elements[popped_count]); \
        } while (is_popped && (++popped_count < count)); \
        return popped_count; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , peek)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        qo_size_t index , \
        _T_element * p_element \
    ) { \
        if (index >= QO_RINGBUF(_T_element , get_count)(ringbuf)) \
            return qo_false; \
        *p_element = ringbuf->elements[(ringbuf->tail_index + index) & ringbuf->buffer_mask]; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , peek_tail)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * p_element \
    ) { \
        if (QO_RINGBUF(_T_element , is_empty)(ringbuf)) \
            return qo_false; \
        *p_element = ringbuf->elements[(ringbuf->head_index - 1) & ringbuf->buffer_mask]; \
        return qo_true; \
    } \
    \
    QO_GLOBAL_UNIQUE \
    qo_bool_t \
    QO_RINGBUF(_T_element , peek_head)( \
        QO_Ringbuf_##_T_element * ringbuf , \
        _T_element * p_element \
    ) { \
        if (QO_RINGBUF(_T_element , is_empty)(ringbuf)) \
            return qo_false; \
        *p_element = ringbuf->elements[ringbuf->tail_index]; \
        return qo_true; \
    } 
        
#define QO_RINGBUF_POP_ITERATE( _T_element , ringbuf , p_element) \
    for (qo_size_t i = 0; QO_RINGBUF(_T_element , pop)(ringbuf, p_element); i++)

#if defined(__cplusplus)
}
#endif // __cplusplus