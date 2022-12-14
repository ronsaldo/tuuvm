#include "tuuvm/tuple.h"
#include "tuuvm/context.h"
#include "tuuvm/errors.h"
#include "tuuvm/function.h"
#include "tuuvm/string.h"
#include "internal/context.h"
#include <stdlib.h>
#include <string.h>

TUUVM_API tuuvm_tuple_t tuuvm_tuple_getImmediateTypeWithTag(tuuvm_context_t *context, size_t immediateTypeTag)
{
    return immediateTypeTag < TUUVM_TUPLE_TAG_COUNT ? context->roots.immediateTypeTable[immediateTypeTag] : 0;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_getImmediateTrivialTypeWithIndex(tuuvm_context_t *context, size_t immediateTrivialIndex)
{
    return immediateTrivialIndex < TUUVM_TUPLE_IMMEDIATE_TRIVIAL_COUNT ? context->roots.immediateTrivialTypeTable[immediateTrivialIndex] : 0;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_char32_encodeBig(tuuvm_context_t *context, tuuvm_char32_t value)
{
    tuuvm_object_tuple_t *result = tuuvm_context_allocateByteTuple(context, context->roots.char32Type, sizeof(tuuvm_char32_t));
    *((tuuvm_char32_t*)result->bytes) = value;
    return (tuuvm_tuple_t)result;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_uint32_encodeBig(tuuvm_context_t *context, uint32_t value)
{
    tuuvm_object_tuple_t *result = tuuvm_context_allocateByteTuple(context, context->roots.uint32Type, sizeof(uint32_t));
    *((uint32_t*)result->bytes) = value;
    return (tuuvm_tuple_t)result;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_int32_encodeBig(tuuvm_context_t *context, int32_t value)
{
    tuuvm_object_tuple_t *result = tuuvm_context_allocateByteTuple(context, context->roots.int32Type, sizeof(int32_t));
    *((int32_t*)result->bytes) = value;
    return (tuuvm_tuple_t)result;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_uint64_encodeBig(tuuvm_context_t *context, uint64_t value)
{
    tuuvm_object_tuple_t *result = tuuvm_context_allocateByteTuple(context, context->roots.uint64Type, sizeof(uint64_t));
    *((uint64_t*)result->bytes) = value;
    return (tuuvm_tuple_t)result;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_int64_encodeBig(tuuvm_context_t *context, int64_t value)
{
    tuuvm_object_tuple_t *result = tuuvm_context_allocateByteTuple(context, context->roots.int64Type, sizeof(int64_t));
    *((int64_t*)result->bytes) = value;
    return (tuuvm_tuple_t)result;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_primitive_identityHash(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)closure;
    (void)argumentCount;
    return tuuvm_tuple_size_encode(context, tuuvm_tuple_identityHash(arguments[0]));
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_primitive_identityEquals(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    (void)argumentCount;
    return tuuvm_tuple_boolean_encode(tuuvm_tuple_identityEquals(arguments[0], arguments[1]));
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_primitive_identityNotEquals(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    (void)argumentCount;
    return tuuvm_tuple_boolean_encode(tuuvm_tuple_identityNotEquals(arguments[0], arguments[1]));
}

TUUVM_API char *tuuvm_tuple_bytesToCString(tuuvm_tuple_t tuple)
{
    size_t stringSize = tuuvm_tuple_getSizeInBytes(tuple);
    size_t sizeToAllocate = stringSize + 1;
    char *cstring = (char*)malloc(sizeToAllocate);
    memcpy(cstring, TUUVM_CAST_OOP_TO_OBJECT_TUPLE(tuple)->bytes, sizeToAllocate);
    cstring[stringSize] = 0;
    return cstring;
}

TUUVM_API void tuuvm_tuple_bytesToCStringFree(char *cstring)
{
    free(cstring);
}

static tuuvm_tuple_t tuuvm_tuple_primitive_getType(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    return tuuvm_tuple_getType(context, arguments[0]);
}

static tuuvm_tuple_t tuuvm_tuple_primitive_setType(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    if(tuuvm_tuple_isNonNullPointer(arguments[0]))
        tuuvm_tuple_setType((tuuvm_object_tuple_t*)arguments[0], arguments[1]);
    return TUUVM_VOID_TUPLE;
}

TUUVM_API tuuvm_tuple_t tuuvm_tuple_slotAt(tuuvm_context_t *context, tuuvm_tuple_t tuple, size_t slotIndex)
{
    (void)context;
    if(!tuuvm_tuple_isNonNullPointer(tuple))
    {
        if(slotIndex < sizeof(tuuvm_tuple_t))
        {
            tuuvm_tuple_t tag = tuple & TUUVM_TUPLE_TAG_BIT_MASK;
            if(TUUVM_TUPLE_TAG_SIGNED_START <= tag && tag <= TUUVM_TUPLE_TAG_SIGNED_END)
            {
                tuuvm_tuple_t byteValue = ( ((tuuvm_stuple_t)tuple) >> (TUUVM_TUPLE_TAG_BIT_COUNT + slotIndex*8)) & 0xFF;
                return tuuvm_tuple_uint8_encode(byteValue);
            }
            else
            {
                tuuvm_tuple_t byteValue = (tuple >> (TUUVM_TUPLE_TAG_BIT_COUNT + slotIndex*8)) & 0xFF;
                return tuuvm_tuple_uint8_encode(byteValue);
            }
        }

        return TUUVM_NULL_TUPLE;
    }

    if(tuuvm_tuple_isBytes(tuple))
    {
        if(slotIndex < tuuvm_tuple_getSizeInBytes(tuple))
            return tuuvm_tuple_uint8_encode(TUUVM_CAST_OOP_TO_OBJECT_TUPLE(tuple)->bytes[slotIndex]);
    }
    else
    {
        if(slotIndex < tuuvm_tuple_getSizeInSlots(tuple))
            return TUUVM_CAST_OOP_TO_OBJECT_TUPLE(tuple)->pointers[slotIndex];
    }

    return TUUVM_NULL_TUPLE;
}

static tuuvm_tuple_t tuuvm_tuple_primitive_slotAt(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    return tuuvm_tuple_slotAt(context, arguments[0], tuuvm_tuple_anySize_decode(arguments[1]));
}

TUUVM_API void tuuvm_tuple_slotAtPut(tuuvm_context_t *context, tuuvm_tuple_t tuple, size_t slotIndex, tuuvm_tuple_t value)
{
    (void)context;
    if(!tuuvm_tuple_isNonNullPointer(tuple))
        return;

    if(tuuvm_tuple_isBytes(tuple))
    {
        if(slotIndex < tuuvm_tuple_getSizeInBytes(tuple))
            TUUVM_CAST_OOP_TO_OBJECT_TUPLE(tuple)->bytes[slotIndex] = tuuvm_tuple_anySize_decode(value) & 0xFF;
    }
    else
    {
        if(slotIndex < tuuvm_tuple_getSizeInSlots(tuple))
            TUUVM_CAST_OOP_TO_OBJECT_TUPLE(tuple)->pointers[slotIndex] = value;
    }
}

static tuuvm_tuple_t tuuvm_tuple_primitive_slotAtPut(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 3) tuuvm_error_argumentCountMismatch(3, argumentCount);

    tuuvm_tuple_slotAtPut(context, arguments[0], tuuvm_tuple_anySize_decode(arguments[1]), arguments[2]);
    return TUUVM_VOID_TUPLE;
}

static tuuvm_tuple_t tuuvm_tuple_primitive_new(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    return (tuuvm_tuple_t)tuuvm_context_allocatePointerTuple(context, TUUVM_NULL_TUPLE, tuuvm_tuple_anySize_decode(arguments[0]));
}

static tuuvm_tuple_t tuuvm_tuple_primitive_byteNew(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    return (tuuvm_tuple_t)tuuvm_context_allocateByteTuple(context, TUUVM_NULL_TUPLE, tuuvm_tuple_anySize_decode(arguments[0]));
}

static tuuvm_tuple_t tuuvm_tuple_primitive_size(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    return tuuvm_tuple_integer_encodeInt64(context, tuuvm_tuple_getSizeInSlots(arguments[0]));
}

static tuuvm_tuple_t tuuvm_tuple_primitive_byteSize(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    return tuuvm_tuple_integer_encodeInt64(context, tuuvm_tuple_getSizeInBytes(arguments[0]));
}

void tuuvm_tuple_setupPrimitives(tuuvm_context_t *context)
{
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::type", 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_getType);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::type:", 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_setType);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::slotAt:", 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_slotAt);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::slotAt:put:", 3, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_slotAtPut);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::new", 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_new);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::byteNew", 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_byteNew);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::size", 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_size);
    tuuvm_context_setIntrinsicSymbolBindingWithPrimitiveFunction(context, "RawTuple::byteSize", 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, tuuvm_tuple_primitive_byteSize);
}
