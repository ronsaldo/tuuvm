#include "TestMacros.h"
#include "tuuvm/ast.h"
#include "tuuvm/arraySlice.h"
#include "tuuvm/parser.h"
#include "tuuvm/string.h"

TEST_SUITE(Parser)
{
    TEST_CASE_WITH_FIXTURE(EmptyString, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(0, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));
    }

    TEST_CASE_WITH_FIXTURE(SingleLineComment, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "## Comment", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(0, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));
    }

    TEST_CASE_WITH_FIXTURE(MultiLineComment, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "#* \nMulti line comment \n *#", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(0, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));
    }

    TEST_CASE_WITH_FIXTURE(IdentifierReference, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "identifier", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(1, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));

        tuuvm_tuple_t node = tuuvm_astSequenceNode_getExpressionAt(sequenceNode, 0);
        TEST_ASSERT(tuuvm_astNode_isIdentifierReferenceNode(tuuvm_test_context, node));
        TEST_ASSERT_EQUALS(tuuvm_symbol_internWithCString(tuuvm_test_context, "identifier"), tuuvm_astIdentifierReferenceNode_getValue(node));
    }

    TEST_CASE_WITH_FIXTURE(LiteralInteger, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "1234", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(1, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));

        tuuvm_tuple_t node = tuuvm_astSequenceNode_getExpressionAt(sequenceNode, 0);
        TEST_ASSERT(tuuvm_astNode_isLiteralNode(tuuvm_test_context, node));
    }

    TEST_CASE_WITH_FIXTURE(LiteralSymbol, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "#test", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(1, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));

        tuuvm_tuple_t node = tuuvm_astSequenceNode_getExpressionAt(sequenceNode, 0);
        TEST_ASSERT(tuuvm_astNode_isLiteralNode(tuuvm_test_context, node));
        TEST_ASSERT_EQUALS(tuuvm_symbol_internWithCString(tuuvm_test_context, "test"), tuuvm_astLiteralNode_getValue(node));
    }

    TEST_CASE_WITH_FIXTURE(UnexpandedEmptySExpression, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "()", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(1, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));

        tuuvm_tuple_t node = tuuvm_astSequenceNode_getExpressionAt(sequenceNode, 0);
        TEST_ASSERT(tuuvm_astNode_isUnexpandedSExpressionNode(tuuvm_test_context, node));

        tuuvm_tuple_t elements = tuuvm_astUnexpandedSExpressionNode_getElements(node);
        TEST_ASSERT_EQUALS(0, tuuvm_arraySlice_getSize(elements));
    }

    TEST_CASE_WITH_FIXTURE(UnexpandedSExpression, TuuvmCore)
    {
        tuuvm_tuple_t sequenceNode = tuuvm_parser_parseCString(tuuvm_test_context, "(function)", "test");
        TEST_ASSERT(tuuvm_astNode_isSequenceNode(tuuvm_test_context, sequenceNode));
        TEST_ASSERT_EQUALS(1, tuuvm_astSequenceNode_getExpressionCount(sequenceNode));

        tuuvm_tuple_t node = tuuvm_astSequenceNode_getExpressionAt(sequenceNode, 0);
        TEST_ASSERT(tuuvm_astNode_isUnexpandedSExpressionNode(tuuvm_test_context, node));

        tuuvm_tuple_t elements = tuuvm_astUnexpandedSExpressionNode_getElements(node);
        TEST_ASSERT_EQUALS(1, tuuvm_arraySlice_getSize(elements));
    }
}
