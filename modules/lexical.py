
import math
import numpy as np

try:
    from modules.vectorizer import vectorizeWholeFile
except:
    from vectorizer import vectorizeWholeFile

import re

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
    # Arithmetic operators
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
    # Logical operators
    "&&",
    "||",
    "!",
    # Relational operators
    "==",
    "!=",
    ">",
    "<",
    ">=",
    "<=",
    # Bitwise operators
    "&",
    "|",
    "^",
    "~",
    "<<",
    ">>",
    "&=",
    "|=",
    "^=",
    "<<=",
    ">>=",
]

# CPP_ALL_TOKENS = CPP_KEYWORDS + CPP_OPERATORS

def cleanLabelsCountDict(labelsCountDict):

    # This function has the sole purpose of removing the double counts of operators
    # Example: "=" is counted thrice, once for "=" and twice more for "=="
    # "=" is counted twice in another cases, once for "=" and once for "+="

    for oldKey in labelsCountDict.keys():
        for newKey, count in labelsCountDict.items():
            if oldKey in newKey and oldKey != newKey:
                labelsCountDict[oldKey] -= (count * newKey.count(oldKey))

    return labelsCountDict



def lexicalAnalysis(files: list[str]) -> np.ndarray:

    feats = np.zeros((len(files), 3))

    keywordVectorizer = CountVectorizer(vocabulary=CPP_KEYWORDS)
    operatorVectorizer = CountVectorizer(ngram_range=(1, 4), analyzer='char', vocabulary=CPP_OPERATORS)

    keywordCount = keywordVectorizer.fit_transform(files)
    keywordCount = keywordCount.toarray()

    operatorLabels = operatorVectorizer.get_feature_names_out()
    operatorCount = operatorVectorizer.fit_transform(files)
    operatorCount = operatorCount.toarray()


    for i in range(len(files)):

        # print(sum(keywordCount[i]))
        keywordCountSum = sum(keywordCount[i])
        # input()

        # this is needed before counting to clean the operator double counts
        # print(operatorCount[i])
        # print(operatorLabels)
        labelsCountDict = dict(zip(operatorLabels, operatorCount[i]))
        # print(labelsCountDict)
        labelsCountDict = cleanLabelsCountDict(labelsCountDict)
        operatorCountSum = sum(list(labelsCountDict.values()))
        # Not at its most efficient state. Detects strings in commented lines
        stringLiteralCountSum = len(re.findall('(?:"(?:\\\\.|[^"\\\\])*"|\'(?:\\\\.|[^\'\\\\])*\')', files[i]))

        feats[i, 0] = math.log(keywordCountSum/len(files[i]))
        feats[i, 1] = math.log(operatorCountSum/len(files[i]))
        feats[i, 2] = math.log(stringLiteralCountSum/len(files[i]))

    return feats


if __name__ == "__main__":

    vecFile1 = vectorizeWholeFile("/Users/Jbernardis/Documents/stylometryResearch/data/dataset-v3/Snuke/Snuke-a1-2022-worldFinals.cpp")
    vecFile2 = vectorizeWholeFile("/Users/Jbernardis/Documents/stylometryResearch/data/dataset-v3/Benq/Benq-b1-2022-r3.cpp")
    vecFile3 = vectorizeWholeFile("/Users/Jbernardis/Documents/stylometryResearch/data/dataset-v3/Benq/Benq-c1-2022-r3.cpp")

    print(lexicalAnalysis([vecFile1, vecFile2, vecFile3]))
