#ifndef LEXI_
#define LEXI_
#include <stdio.h>

typedef enum {
        EQUAL,
        ASTERISK,
        OPEN_BRACES,
        CLOSE_BRACES,
        OPEN_PARANTHESIS,
        CLOSE_PARANTHESIS,
        COMMA,
        SEMICOLON,
        DIFF
} separators_punctuators;

typedef enum { FORWARD_SLASH, BACKWARD_SLASH, ASHTRIC } comment;

typedef enum {
        ALIGN,
        CHAR,
        AUTO,
        INT,
        BOOL,
        FLOAT,
        DOUBLE,
        LONG,
        CONST,
        CONTINUE,
        DO,
        WHILE,
        FOR,
        IF,
        ELSE,
        SWITCH,
        TRUE,
        FALSE,
        GOTO,
        REGISTER,
        RESTRICT,
        STATIC,
        DEFAULT,
        RETURN,
        SHORT,
        SIGNED,
        UNSIGNED,
        NULLPTR,
        INLINE,
        THREAD_LOCAL,
        TYPEDEF,
        TYPEOF,
        VOID,
        STRUCT
} ReservedKeywords;

typedef enum {
        HASH_IF,
        HASH_ELIF,
        HASH_ELSE,
        HASH_ENDIF,
        HASH_IFDEF,
        HASH_IFNDEF,
        HASH_ELIFDEF,
        HASH_UNDEF,
        HASH_INCLUDE,
        HASH_EMBED,
        HASH_LINE,
        HASH_ERROR,
        HASH_WARNING,
        HASH_PRAGMA
} PreprocessorDirectives;

typedef enum {
        BITWISE_AND,
        BITWISE_OR,
        BITWISE_XOR,
        LEFT_SHIFT,
        RIGHT_SHIFT,
} bitwise_operators;

typedef enum {
        INCREEMENT,
        DECREEMENT,
        TERNARY_OPERATOR,
        HASH
} misscilenious_operator;

typedef enum {
        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_NOT,
} logical_operators;

typedef enum {
        ADDITION,
        SUBTRACTION,
        DIVIDE,
        MULTIPLY,
        MODULUS
} airthmetic_operators;

typedef enum {
        INT_LITERALS,
        FLOAT_LITERALS,
        STRING_LITERAL,
        CHAR_LITERAL,
        DOUBLER_LITERAL,
        LONG_DOUBLE_LITERAL,
        BOOLEAN_LITERAL
} literals;

typedef struct {
        airthmetic_operators AirthmeticOperator;
        logical_operators LogicalOperator;
        bitwise_operators BitwiseOperator;
        misscilenious_operator xOperator;
} operators;

typedef struct {
        comment comment_operator;
        ReservedKeywords keyword_operator;
        operators operator_handler;
        literals literal_operators;
        separators_punctuators separator_operator;
        char *identifiers;
        char *error_msg;
} tokenizerType;

/* single-line comment/multi-line comment */
typedef struct {
        comment s_comment;
        comment m_comment;
} Comment;

typedef struct {
        ReservedKeywords reserver_keywords;
        PreprocessorDirectives preprocess_directives;
} Keywords;

typedef struct {
        char *token_value;
        tokenizerType type;
} tokenizer;

tokenizer parse_identifiers(char);
tokenizer parse_operators(char);
void lexical_analyzer(const char *);
#endif
