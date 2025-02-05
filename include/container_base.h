#pragma once
#define __QO_CONTAINER_BASE_H__

#define QO_ENABLE_EXPERIMENTAL_CXX
#include "../../Qozero/include/qozero.h"

#define QO_METHOD(container_base , element_type , method_name) \
    container_base##_##element_type##_##method_name

#define __QO_CONTAINER_REGISTERED(container_base , element_type) \
        __QO_##container_base##_##element_type##_REGISTERED \

#if __STDC_VERSION__ >= 201112L // Reserve for future user
#define __QO_NATIVE_TYPENAME(x) _Generic(x, \
    qo_uint8_t:     "uint8_t", \
    qo_uint16_t:    "uint16_t", \
    qo_uint32_t:    "uint32_t", \
    qo_uint64_t:    "uint64_t", \
    qo_int8_t:      "int8_t", \
    qo_int16_t:     "int16_t", \
    qo_int32_t:     "int32_t", \
    qo_int64_t:     "int64_t", \
    qo_pointer_t:   "voidp", \
    qo_cstring_t:   "char*", \
    qo_ccstring_t:  "const char*", \
    qo_fp32_t:      "float", \
    qo_fp64_t:      "double", \
    qo_bool_t:      "bool", \
    default:        #x \
)
#endif // #if __STDC_VERSION__ >= 201112L