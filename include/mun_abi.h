#ifndef MUN_ABI_H_
#define MUN_ABI_H_

#include <stdint.h>

/** <div rustbindgen derive="PartialEq"> */
typedef struct
{
    const uint8_t b[16];
} MunGuid;

typedef struct
{
    const MunGuid guid;
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
    const uint16_t num_arg_types;
    const MunPrivacy_t privacy;
} MunFunctionSignature;

/** <div rustbindgen derive="Clone"> */
typedef struct
{
    const MunFunctionSignature signature;
    const void *fn_ptr;
} MunFunctionInfo;

typedef struct
{
    const char *path;
    const MunFunctionInfo *functions;
    const uint32_t num_functions;
} MunModuleInfo;

typedef struct
{
    const MunFunctionSignature *signatures;
    const void **fn_ptrs;
    const uint32_t num_entries;
} MunDispatchTable;

typedef struct
{
    const MunModuleInfo symbols;
    MunDispatchTable dispatch_table;
    const char *const *dependencies;
    const uint32_t num_dependencies;
} MunAssemblyInfo;

#endif
