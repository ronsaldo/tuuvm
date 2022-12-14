#include "tuuvm/stackFrame.h"
#include "tuuvm/arrayList.h"
#include "tuuvm/arraySlice.h"
#include "tuuvm/tuple.h"
#include "tuuvm/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

thread_local tuuvm_context_t *tuuvm_stackFrame_activeContext;
thread_local tuuvm_stackFrameRecord_t *tuuvm_stackFrame_activeRecord;

TUUVM_API void tuuvm_stackFrame_enterContext(tuuvm_context_t *context, tuuvm_stackFrameRecord_t *topLevelStackRecord)
{
    tuuvm_stackFrame_activeContext = context;
    tuuvm_stackFrame_activeRecord = topLevelStackRecord;
}

TUUVM_API void tuuvm_stackFrame_leaveContext()
{
    tuuvm_stackFrame_activeContext = NULL;
    tuuvm_stackFrame_activeRecord = NULL;
}

TUUVM_API tuuvm_context_t *tuuvm_stackFrame_getActiveContext()
{
    return tuuvm_stackFrame_activeContext;
}

TUUVM_API tuuvm_stackFrameRecord_t *tuuvm_stackFrame_getActiveRecord()
{
    return tuuvm_stackFrame_activeRecord;
}

TUUVM_API void tuuvm_stackFrame_pushRecord(tuuvm_stackFrameRecord_t *record)
{
    record->previous = tuuvm_stackFrame_activeRecord;
    tuuvm_stackFrame_activeRecord = record;
}

TUUVM_API void tuuvm_stackFrame_popRecord(tuuvm_stackFrameRecord_t *record)
{
    tuuvm_stackFrame_activeRecord = record->previous;
}

TUUVM_API void tuuvm_stackFrame_raiseException(tuuvm_tuple_t exception)
{
    tuuvm_context_t *context = tuuvm_stackFrame_activeContext;
    tuuvm_stackFrameRecord_t *exceptionRecord = tuuvm_stackFrame_activeRecord;

    if(!exceptionRecord)
    {
        fprintf(stderr, "Cannot raise an exception without an active context.\n");
        abort();
    }


    // Find the landing pad record.
    tuuvm_stackFrameRecord_t *stackFrameRecord = exceptionRecord;
    while(stackFrameRecord && stackFrameRecord->type != TUUVM_STACK_FRAME_RECORD_TYPE_LANDING_PAD)
        stackFrameRecord = stackFrameRecord->previous;

    // Did we find it?
    if(!stackFrameRecord)
    {
        tuuvm_tuple_t errorString = tuuvm_tuple_toString(context, exception);
        fprintf(stderr, "Unhandled exception: " TUUVM_STRING_PRINTF_FORMAT "\n", TUUVM_STRING_PRINTF_ARG(errorString));
        tuuvm_stackFrame_printStackTrace(context, tuuvm_stackFrame_buildStackTraceUpTo(NULL));
        abort();
    }

    // We found it, transfer the control flow onto it.
    tuuvm_stackFrameLandingPadRecord_t *landingPadRecord = (tuuvm_stackFrameLandingPadRecord_t*)stackFrameRecord;
    landingPadRecord->exception = exception;
    if(landingPadRecord->keepStackTrace)
        landingPadRecord->stackTrace = tuuvm_stackFrame_buildStackTraceUpTo((tuuvm_stackFrameRecord_t*)landingPadRecord);

    tuuvm_stackFrame_activeRecord = (tuuvm_stackFrameRecord_t*)landingPadRecord;
    longjmp(landingPadRecord->jmpbuffer, 1);
}

TUUVM_API tuuvm_tuple_t tuuvm_stackFrame_buildStackTraceUpTo(tuuvm_stackFrameRecord_t *targetRecord)
{
    tuuvm_context_t *context = tuuvm_stackFrame_activeContext;
    tuuvm_tuple_t arrayList = tuuvm_arrayList_create(context);
    
    tuuvm_stackFrameRecord_t *stackFrameRecord = tuuvm_stackFrame_activeRecord;
    //tuuvm_tuple_t currentFunction = TUUVM_NULL_TUPLE;
    tuuvm_tuple_t currentSourcePosition = TUUVM_NULL_TUPLE;
    while(stackFrameRecord && stackFrameRecord != targetRecord)
    {
        if(stackFrameRecord->type == TUUVM_STACK_FRAME_RECORD_TYPE_SOURCE_POSITION)
        {
            if(!currentSourcePosition)
                currentSourcePosition = ((tuuvm_stackFrameSourcePositionRecord_t*)stackFrameRecord)->sourcePosition;
        }
        else if(stackFrameRecord->type == TUUVM_STACK_FRAME_RECORD_TYPE_FUNCTION_ACTIVATION)
        {
            if(currentSourcePosition)
            {
                tuuvm_arrayList_add(context, arrayList, currentSourcePosition);
                currentSourcePosition = TUUVM_NULL_TUPLE;
            }
            //currentFunction = ((tuuvm_stackFrameFunctionActivationRecord_t*)stackFrameRecord)->function;
        }

        stackFrameRecord = stackFrameRecord->previous;
    }

    if(currentSourcePosition)
        tuuvm_arrayList_add(context, arrayList, currentSourcePosition);

    return tuuvm_arrayList_asArraySlice(context, arrayList);
}

TUUVM_API void tuuvm_stackFrame_printStackTrace(tuuvm_context_t *context, tuuvm_tuple_t stackTrace)
{
    size_t stackTraceSize = tuuvm_arraySlice_getSize(stackTrace);
    for(size_t i = 0; i < stackTraceSize; ++i)
    {
        tuuvm_tuple_t stackTraceRecord = tuuvm_arraySlice_at(stackTrace, i);
        tuuvm_tuple_t stackTraceRecordString = tuuvm_tuple_toString(context, stackTraceRecord);
        fprintf(stderr, TUUVM_STRING_PRINTF_FORMAT "\n", TUUVM_STRING_PRINTF_ARG(stackTraceRecordString));
    }
}