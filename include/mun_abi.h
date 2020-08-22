#ifndef MUN_ABI_H_
#define MUN_ABI_H_

/* Generated with cbindgen:0.14.2 */

#include <stdint.h>

/**
 * Defines the current ABI version
 */
#define MUN_ABI_VERSION 300

/**
 * Represents the kind of memory management a struct uses.
 */
enum MunStructMemoryKind
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
    /**
     * A garbage collected struct is allocated on the heap and uses reference semantics when passed
     * around.
     */
    GC,
    /**
     * A value struct is allocated on the stack and uses value semantics when passed around.
     *
     * NOTE: When a value struct is used in an external API, a wrapper is created that _pins_ the
     * value on the heap. The heap-allocated value needs to be *manually deallocated*!
     */
    Value,
};
#ifndef __cplusplus
typedef uint8_t MunStructMemoryKind;
#endif // __cplusplus

/**
 * Represents a group of types that illicit the same characteristics.
 */
enum MunTypeGroup
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
    /**
     * Fundamental types (i.e. `()`, `bool`, `float`, `int`, etc.)
     */
    FundamentalTypes = 0,
    /**
     * Struct types (i.e. record, tuple, or unit structs)
     */
    StructTypes = 1,
};
#ifndef __cplusplus
typedef uint8_t MunTypeGroup;
#endif // __cplusplus

/**
 * Represents a globally unique identifier (GUID).
 */
typedef struct {
    uint8_t _0[16];
} MunGuid;

/**
 * Represents the type declaration for a value type.
 *
 * TODO: add support for polymorphism, enumerations, type parameters, generic type definitions, and
 * constructed generic types.
 */
typedef struct {
    /**
     * Type GUID
     */
    MunGuid guid;
    /**
     * Type name
     */
    const char *name;
    /**
     * The exact size of the type in bits without any padding
     */
    uint32_t size_in_bits;
    /**
     * The alignment of the type
     */
    uint8_t alignment;
    /**
     * Type group
     */
    MunTypeGroup group;
} MunTypeInfo;

/**
 * Represents a function signature.
 */
typedef struct {
    /**
     * Argument types
     */
    const MunTypeInfo *const *arg_types;
    /**
     * Optional return type
     */
    const MunTypeInfo *return_type;
    /**
     * Number of argument types
     */
    uint16_t num_arg_types;
} MunFunctionSignature;

/**
 * Represents a function prototype. A function prototype contains the name, type signature, but
 * not an implementation.
 */
typedef struct {
    /**
     * Function name
     */
    const char *name;
    /**
     * The type signature of the function
     */
    MunFunctionSignature signature;
} MunFunctionPrototype;

/**
 * Represents a function definition. A function definition contains the name, type signature, and
 * a pointer to the implementation.
 *
 * `fn_ptr` can be used to call the declared function.
 */
typedef struct {
    /**
     * Function prototype
     */
    MunFunctionPrototype prototype;
    /**
     * Function pointer
     */
    const void *fn_ptr;
} MunFunctionDefinition;

/**
 * Represents a module declaration.
 */
typedef struct {
    /**
     * Module path
     */
    const char *path;
    /**
     * Module functions
     */
    const MunFunctionDefinition *functions;
    /**
     * Module types
     */
    const MunTypeInfo *const *types;
    /**
     * Number of module functions
     */
    uint32_t num_functions;
    /**
     * Number of module types
     */
    uint32_t num_types;
} MunModuleInfo;

/**
 * Represents a function dispatch table. This is used for runtime linking.
 *
 * Function signatures and pointers are stored separately for cache efficiency.
 */
typedef struct {
    /**
     * Function signatures
     */
    const MunFunctionPrototype *prototypes;
    /**
     * Function pointers
     */
    const void **fn_ptrs;
    /**
     * Number of functions
     */
    uint32_t num_entries;
} MunDispatchTable;

/**
 * Represents an assembly declaration.
 */
typedef struct {
    /**
     * Symbols of the top-level module
     */
    MunModuleInfo symbols;
    /**
     * Dispatch table
     */
    MunDispatchTable dispatch_table;
    /**
     * Paths to assembly dependencies
     */
    const char *const *dependencies;
    /**
     * Number of dependencies
     */
    uint32_t num_dependencies;
} MunAssemblyInfo;

/**
 * Represents a struct declaration.
 */
typedef struct {
    /**
     * Struct fields' names
     */
    const char *const *field_names;
    /**
     * Struct fields' information
     */
    const MunTypeInfo *const *field_types;
    /**
     * Struct fields' offsets
     */
    const uint16_t *field_offsets;
    /**
     * Number of fields
     */
    uint16_t num_fields;
    /**
     * Struct memory kind
     */
    MunStructMemoryKind memory_kind;
} MunStructInfo;

#endif /* MUN_ABI_H_ */
