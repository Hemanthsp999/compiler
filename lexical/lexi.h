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
        INCREEMENT,
        DECREEMENT,
        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_NOT,
        MODULUS,
        BITWISE_AND,
        BITWISE_OR,
        BITWISE_XOR,
        LEFT_SHIFT,
        RIGHT_SHIFT,
        TERNARY_OPERATOR,
        HASH
} operators;

typedef enum {
        INT_LITERALS,
        FLOAT_LITERALS,
        STRING_LITERAL,
        CHAR_LITERAL,
        DOUBLER_LITERAL,
        LONG_DOUBLE_LITERAL,
        BOOLEAN_LITERAL
} literals;

typedef enum {
        COMMENT,
        KEYWORDS,
        IDENTIFEIERS,
        SEPARATORS_PUNCTUATORS,
        OPERATORS,
        LITERALS
} tokenizerType;

/* single-line comment/multi-line comment */
typedef struct {
        comment s_comment;
        comment m_comment;
} Comment;

/* variable naming */
typedef struct {
        char *identifier;
} Identifiers;

typedef struct {
        ReservedKeywords reserver_keywords;
        PreprocessorDirectives preprocess_directives;
} Keywords;

typedef struct {
        char *token_value;
        tokenizerType type;
} tokenizer;

tokenizer parse_operators( char);
void lexical_analyzer(const char *);
#endif
