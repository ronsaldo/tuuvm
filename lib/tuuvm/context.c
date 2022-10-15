#include "internal/context.h"
#include "tuuvm/type.h"
#include "tuuvm/environment.h"
#include "tuuvm/string.h"
#include "tuuvm/set.h"
#include "tuuvm/function.h"
#include <stdlib.h>

extern void tuuvm_astInterpreter_setupTypes(tuuvm_context_t *context);

static tuuvm_tuple_t tuuvm_context_createIntrinsicType(tuuvm_context_t *context, const char *name)
{
    tuuvm_tuple_t nameSymbol = tuuvm_symbol_internWithCString(context, name);
    tuuvm_tuple_t type = tuuvm_type_createWithName(context, nameSymbol);
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, nameSymbol, type);
    return type;
}

static void tuuvm_context_createBasicTypes(tuuvm_context_t *context)
{
    // Make a circular base type.
    context->roots.typeType = tuuvm_type_createAnonymous(context);
    tuuvm_tuple_setType((tuuvm_object_tuple_t*)context->roots.typeType, context->roots.typeType);

    // Create the symbol and set type.
    context->roots.primitiveFunctionType = tuuvm_type_createAnonymous(context);

    // Create the basic hash functions.
    context->roots.identityEqualsFunction = tuuvm_function_createPrimitive(context, 0, tuuvm_tuple_primitive_identityEquals);
    context->roots.identityHashFunction = tuuvm_function_createPrimitive(context, 0, tuuvm_tuple_primitive_identityHash);
    context->roots.stringEqualsFunction = tuuvm_function_createPrimitive(context, 0, tuuvm_string_primitive_equals);
    context->roots.stringHashFunction = tuuvm_function_createPrimitive(context, 0, tuuvm_string_primitive_hash);

    context->roots.symbolType = tuuvm_type_createAnonymous(context);
    context->roots.setType = tuuvm_type_createAnonymous(context);
    context->roots.internedSymbolSet = tuuvm_set_create(context, context->roots.stringEqualsFunction, context->roots.stringHashFunction);

    // Create the intrinsic built-in environment
    context->roots.environmentType = tuuvm_type_createWithName(context, tuuvm_symbol_internWithCString(context, "Environment"));
    context->roots.intrinsicsBuiltInEnvironment = tuuvm_environment_create(context, TUUVM_NULL_TUPLE);

    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_symbol_internWithCString(context, "nil"), TUUVM_NULL_TUPLE);
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_symbol_internWithCString(context, "false"), TUUVM_FALSE_TUPLE);
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_symbol_internWithCString(context, "true"), TUUVM_TRUE_TUPLE);
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_symbol_internWithCString(context, "void"), TUUVM_VOID_TUPLE);

    // Set the name of the root basic type.
    tuuvm_type_setName(context->roots.typeType, tuuvm_symbol_internWithCString(context, "Type"));
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_type_getName(context->roots.typeType), context->roots.typeType);

    tuuvm_type_setName(context->roots.primitiveFunctionType, tuuvm_symbol_internWithCString(context, "PrimitiveFunction"));
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_type_getName(context->roots.primitiveFunctionType), context->roots.primitiveFunctionType);

    tuuvm_type_setName(context->roots.symbolType, tuuvm_symbol_internWithCString(context, "Symbol"));
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_type_getName(context->roots.symbolType), context->roots.symbolType);

    tuuvm_type_setName(context->roots.setType, tuuvm_symbol_internWithCString(context, "Set"));
    tuuvm_environment_setSymbolBinding(context, context->roots.intrinsicsBuiltInEnvironment, tuuvm_type_getName(context->roots.setType), context->roots.setType);

    // Create other root basic types.
    context->roots.arrayType = tuuvm_context_createIntrinsicType(context, "Array");
    context->roots.arraySliceType = tuuvm_context_createIntrinsicType(context, "ArraySlice");
    context->roots.arrayListType = tuuvm_context_createIntrinsicType(context, "ArrayList");
    context->roots.dictionaryType = tuuvm_context_createIntrinsicType(context, "Dictionary");
    context->roots.falseType = tuuvm_context_createIntrinsicType(context, "False");
    context->roots.hashtableEmptyType = tuuvm_context_createIntrinsicType(context, "HashtableEmpty");
    context->roots.integerType = tuuvm_context_createIntrinsicType(context, "Integer");
    context->roots.nilType = tuuvm_context_createIntrinsicType(context, "Nil");
    context->roots.stringType = tuuvm_context_createIntrinsicType(context, "String");
    context->roots.trueType = tuuvm_context_createIntrinsicType(context, "True");
    context->roots.voidType = tuuvm_context_createIntrinsicType(context, "Void");

    context->roots.char8Type = tuuvm_context_createIntrinsicType(context, "Char8");
    context->roots.uint8Type = tuuvm_context_createIntrinsicType(context, "UInt8");
    context->roots.int8Type = tuuvm_context_createIntrinsicType(context, "Int8");

    context->roots.char16Type = tuuvm_context_createIntrinsicType(context, "Char16");
    context->roots.uint16Type = tuuvm_context_createIntrinsicType(context, "UInt16");
    context->roots.int16Type = tuuvm_context_createIntrinsicType(context, "Int16");

    context->roots.char32Type = tuuvm_context_createIntrinsicType(context, "Char32");
    context->roots.uint32Type = tuuvm_context_createIntrinsicType(context, "UInt32");
    context->roots.int32Type = tuuvm_context_createIntrinsicType(context, "Int32");

    context->roots.uint64Type = tuuvm_context_createIntrinsicType(context, "UInt64");
    context->roots.int64Type = tuuvm_context_createIntrinsicType(context, "Int64");

    context->roots.floatType = tuuvm_context_createIntrinsicType(context, "Float");
    context->roots.doubleType = tuuvm_context_createIntrinsicType(context, "Double");

    context->roots.sourceCodeType = tuuvm_context_createIntrinsicType(context, "SourceCode");
    context->roots.sourcePositionType = tuuvm_context_createIntrinsicType(context, "SourcePosition");
    context->roots.tokenType = tuuvm_context_createIntrinsicType(context, "Token");

    context->roots.astNodeType = tuuvm_context_createIntrinsicType(context, "ASTNode");
    context->roots.astErrorNodeType = tuuvm_context_createIntrinsicType(context, "ASTErrorNode");
    context->roots.astFunctionApplicationNodeType = tuuvm_context_createIntrinsicType(context, "ASTFunctionApplicationNode");
    context->roots.astLiteralNodeType = tuuvm_context_createIntrinsicType(context, "ASTLiteralNode");
    context->roots.astIdentifierReferenceNodeType = tuuvm_context_createIntrinsicType(context, "ASTIdentifierReferenceNode");
    context->roots.astSequenceNodeType = tuuvm_context_createIntrinsicType(context, "ASTSequenceNode");
    context->roots.astUnexpandedApplicationNodeType = tuuvm_context_createIntrinsicType(context, "ASTUnexpandedApplicationNode");

    context->roots.astQuoteNodeType = tuuvm_context_createIntrinsicType(context, "ASTQuoteNode");
    context->roots.astQuasiQuoteNodeType = tuuvm_context_createIntrinsicType(context, "ASTQuasiQuoteNode");
    context->roots.astQuasiUnquoteNodeType = tuuvm_context_createIntrinsicType(context, "ASTQuasiUnquoteNode");
    context->roots.astSpliceNodeType = tuuvm_context_createIntrinsicType(context, "ASTSpliceNode");

    // Fill the immediate type table.
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_NIL] = context->roots.nilType;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_INTEGER] = context->roots.integerType;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_CHAR8] = context->roots.char8Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_UINT8] = context->roots.uint8Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_INT8] = context->roots.int8Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_CHAR16] = context->roots.char16Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_UINT16] = context->roots.uint16Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_INT16] = context->roots.int16Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_CHAR32] = context->roots.char32Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_UINT32] = context->roots.uint32Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_INT32] = context->roots.int32Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_UINT64] = context->roots.uint64Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_INT64] = context->roots.int64Type;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_FLOAT] = context->roots.floatType;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_DOUBLE] = context->roots.doubleType;
    context->roots.immediateTypeTable[TUUVM_TUPLE_TAG_TRIVIAL] = context->roots.nilType;

    // Fill the immediate trivial type table.
    context->roots.immediateTrivialTypeTable[TUUVM_TUPLE_IMMEDIATE_TRIVIAL_INDEX_FALSE] = context->roots.falseType;
    context->roots.immediateTrivialTypeTable[TUUVM_TUPLE_IMMEDIATE_TRIVIAL_INDEX_TRUE] = context->roots.trueType;
    context->roots.immediateTrivialTypeTable[TUUVM_TUPLE_IMMEDIATE_TRIVIAL_INDEX_VOID] = context->roots.voidType;
    context->roots.immediateTrivialTypeTable[TUUVM_TUPLE_IMMEDIATE_TRIVIAL_INDEX_HASHTABLE_EMPTY_ELEMENT] = context->roots.hashtableEmptyType;
}

TUUVM_API tuuvm_context_t *tuuvm_context_create(void)
{
    tuuvm_context_t *context = (tuuvm_context_t*)calloc(1, sizeof(tuuvm_context_t));
    context->identityHashSeed = 1;
    tuuvm_context_createBasicTypes(context);
    tuuvm_astInterpreter_setupTypes(context);

    return context;
}

TUUVM_API void tuuvm_context_destroy(tuuvm_context_t *context)
{
    if(!context) return;

    // Destroy the context heap.
    tuuvm_heap_destroy(&context->heap);
    free(context);
}

tuuvm_heap_t *tuuvm_context_getHeap(tuuvm_context_t *context)
{
    if(!context) return 0;

    return &context->heap;
}

static size_t tuuvm_context_generateIdentityHash(tuuvm_context_t *context)
{
    return context->identityHashSeed = tuuvm_hashMultiply(context->identityHashSeed) + 12345;
}

tuuvm_object_tuple_t *tuuvm_context_allocateByteTuple(tuuvm_context_t *context, tuuvm_tuple_t type, size_t byteSize)
{
    if(!context) return 0;

    tuuvm_object_tuple_t *result = tuuvm_heap_allocateByteTuple(&context->heap, byteSize);
    result->header.identityHash = tuuvm_context_generateIdentityHash(context);
    if(result)
        tuuvm_tuple_setType(result, type);
    return result;
}

tuuvm_object_tuple_t *tuuvm_context_allocatePointerTuple(tuuvm_context_t *context, tuuvm_tuple_t type, size_t slotCount)
{
    if(!context) return 0;

    tuuvm_object_tuple_t *result = tuuvm_heap_allocatePointerTuple(&context->heap, slotCount);
    result->header.identityHash = tuuvm_context_generateIdentityHash(context);
    if(result)
        tuuvm_tuple_setType(result, type);
    return result;
}
