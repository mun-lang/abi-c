#ifndef MUN_ABI_H_
#define MUN_ABI_H_

#include <stdint.h>

/** <div rustbindgen derive="PartialEq"> */
typedef struct
{
    uint8_t b[16];
} MunGuid;

typedef struct
{
    MunGuid guid;
    const char *name;
} MunTypeInfo;

typedef enum
{
    MunPrivacyPublic = 0,
    MunPrivacyPrivate = 1
} MunPrivacy;

typedef uint8_t MunPrivacy_t;

/** <div rustbindgen derive="Clone"> */
typedef struct
{
    const char *name;
    const MunTypeInfo *arg_types;
    const MunTypeInfo *return_type;
    const void *fn_ptr;
    uint16_t num_arg_types;
    MunPrivacy_t privacy;
} MunFunctionInfo;

typedef struct
{
    const MunFunctionInfo *functions;
    uint32_t num_functions;
} MunModuleInfo;

#endif
