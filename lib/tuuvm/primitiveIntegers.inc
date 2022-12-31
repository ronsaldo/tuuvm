static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_printString)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

#if IS_SIGNED
    return tuuvm_primitiveInteger_signed_printString(context, primitiveInteger_decode(arguments[0]));
#else
    return tuuvm_primitiveInteger_unsigned_printString(context, primitiveInteger_decode(arguments[0]));
#endif
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_add)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left + right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_subtract)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left - right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_negate)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    integer_t operand = primitiveInteger_decode(arguments[0]);
    return primitiveInteger_encode(-operand);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_bitInvert)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 1) tuuvm_error_argumentCountMismatch(1, argumentCount);

    integer_t operand = primitiveInteger_decode(arguments[0]);
    return primitiveInteger_encode(~operand);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_multiply)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left * right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_divide)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left / right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_remainder)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left % right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_bitAnd)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left & right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_bitOr)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left | right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_bitXor)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left ^ right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_shiftLeft)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left << right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_shiftRight)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return primitiveInteger_encode(left >> right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_equals)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left == right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_notEquals)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left != right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_lessThan)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left < right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_lessEquals)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left <= right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_greaterThan)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left > right);
}

static tuuvm_tuple_t PRIMITIVE_INTEGER_FUNCTION(primitive_greaterEquals)(tuuvm_context_t *context, tuuvm_tuple_t closure, size_t argumentCount, tuuvm_tuple_t *arguments)
{
    (void)context;
    (void)closure;
    if(argumentCount != 2) tuuvm_error_argumentCountMismatch(2, argumentCount);

    integer_t left = primitiveInteger_decode(arguments[0]);
    integer_t right = primitiveInteger_decode(arguments[1]);
    return tuuvm_tuple_boolean_encode(left >= right);
}

void PRIMITIVE_INTEGER_FUNCTION(setupPrimitives)(tuuvm_context_t *context)
{
    tuuvm_type_setPrintStringFunction(context->roots.INTEGER_TYPE_ROOT_NAME, tuuvm_function_createPrimitive(context, 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_printString)));

    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::negate"), tuuvm_function_createPrimitive(context, 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_negate)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::bitInvert"), tuuvm_function_createPrimitive(context, 1, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_bitInvert)));

    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::add:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_add)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::subtract:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_subtract)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::multiply:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_multiply)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::divide:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_divide)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::remainder:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_remainder)));

    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::bitAnd:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_bitAnd)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::bitOr:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_bitOr)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::bitXor:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_bitXor)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::shiftLeft:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_shiftLeft)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::shiftRight:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_shiftRight)));

    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::equals:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_equals)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::notEquals:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_notEquals)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::lessThan:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_lessThan)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::lessEquals:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_lessEquals)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::greaterThan:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_greaterThan)));
    tuuvm_context_setIntrinsicSymbolBinding(context, tuuvm_symbol_internWithCString(context, INTEGER_TYPE_NAME "::greaterEquals:"), tuuvm_function_createPrimitive(context, 2, TUUVM_FUNCTION_FLAGS_NONE, NULL, PRIMITIVE_INTEGER_FUNCTION(primitive_greaterEquals)));
}

#undef integer_t
#undef primitiveInteger_decode
#undef primitiveInteger_encode
#undef IS_SIGNED
#undef FUNCTION_PREFIX
#undef INTEGER_TYPE_NAME
#undef INTEGER_TYPE_ROOT_NAME