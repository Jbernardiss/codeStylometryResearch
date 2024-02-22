
import glob
import os

def getFilesPaths(path: str):
    if os.name == "posix":
        filesPath = glob.glob(path.replace("'", "") + "/*/*.cpp")
        filesLabels = [path.split("/")[-2] for path in filesPath]
        return filesPath, filesLabels

    elif os.name == "nt":
        filesPath = glob.glob(path.replace("'", "") + "\*\*.cpp")
        filesLabels = [path.split("\\")[-2] for path in filesPath]
        return filesPath, filesLabels


def printTestsPredicts(y_test, predictedAuthor):
    print('\n\n' + "\u0332".join("Tests:") + '\n')
    print("Author        || Predicted    : Check status")
    print("--------------------------------------------")
    erros = 0
    for a, b in zip(y_test, predictedAuthor):

        if a == b:
            print(f'{a}{" " * (13 - len(a))} == {b}{" " * (13 - len(b))}: V')
        if a != b:
            print(f'{a}{" " * (13 - len(a))} != {b}{" " * (13 - len(b))}: F')
            erros += 1

    print(f'\nTotal: {len(y_test)}')
    print(f'Erros: {erros}')