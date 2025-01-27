#pragma once
#define __QO_CONTAINER_BASE_H__

#define QO_ENABLE_EXPERIMENTAL_CXX
#include "../../Qozero/include/qozero.h"

#define QO_METHOD(container_base , element_type , method_name) \
    container_base##_##element_type##_##method_name

#define __QO_CONTAINER_REGISTERED(container_base , element_type) \
        __QO_##container_base##_##element_type##_REGISTERED \