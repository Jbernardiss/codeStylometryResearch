
import math
import numpy as np
import nltk

from sklearn.feature_extraction.text import CountVectorizer

CPP_KEYWORDS = [
    "alignas",
    "alignof",
    "and",
    "and_eq",
    "asm",
    "atomic_cancel",
    "atomic_commit",
    "atomic_noexcept",
    "auto",
    "bitand",
    "bitor",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "char8_t",
    "char16_t",
    "char32_t",
    "class",
    "compl",
    "concept",
    "const",
    "consteval",
    "constexpr",
    "constinit",
    "const_cast",
    "continue",
    "co_await",
    "co_return",
    "co_yield",
    "decltype",
    "default",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "operator",
    "or",
    "or_eq",
    "private",
    "protected",
    "public",
    "reflexpr",
    "register",
    "reinterpret_cast",
    "requires",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "struct",
    "switch",
    "synchronized",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "xor",
    "xor_eq",
]

CPP_OPERATORS = [
    #arithmetic operators
    "=",
    "+", 
    "++",  
    "+=", 
    "-",
    "--",
    "-=",
    "*",
    "*=",
    "/",
    "/=",
    "%",
    "%=",
    #logical operators
    "^",
    "^=",
    "&",
    "&=",
    "|",
    "|=",
    "~",
    #relational operators
    "<",
    "<=",
    ">",
    ">=",
    "==",
    "!=",
    "!",
    "&&",
    "||",
    "<<",
    "<<=",
    ">>",
    ">>=",
]





def lexicalAnalisys(files: list[str]) -> np.ndarray:

    feats = np.zeros((len(files), 3))


    vectorizer = CountVectorizer(vocabulary=CPP_KEYWORDS)

    X = vectorizer.fit_transform(files)

    for i, file in enumerate(files):
        feats[i, 0] = math.log(X[i].sum()/len(file))

    index = 0
    for file in files:

        numOperations = 0

        tokens = nltk.word_tokenize(file)
        for token in tokens:
            if token in CPP_OPERATORS:
                numOperations += 1

        feats[index, 1] = math.log(numOperations/len(file))
        feats[index, 2] = math.log(len(tokens)/len(file))
        index += 1

    return feats

if __name__ == "__main__":
    print(lexicalAnalisys(["int main() { return 0; }"]))