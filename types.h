#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    m_success,
    m_failure
} Status;

typedef enum
{
    m_edit,
    m_view,
    m_unsupported
} OperationType;

#endif
