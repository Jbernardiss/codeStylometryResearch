
from modules.layout import layoutAnalysis
from modules.lexical import lexicalAnalisys
from modules.vectorizer import vectorizeFileInLines, vectorizeFile

import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

import glob
import os
import sys


def printTestsPredicts(y_test, predictedAuthor):
    print("\n\nTests: ")
    erros = 0
    for a, b in zip(y_test, predictedAuthor):

        if a == b:
            print(f'{a} = {b}: V')
        if a != b:
            print(f'{a} != {b}: F')
            erros += 1

    print(f'Total: {len(y_test)}')
    print(f'Erros: {erros}')

if os.name == "posix":
    filesPath = glob.glob(input("Type the path to the training files: ").replace("'", "") + "/*/*.cpp")
    filesLabels = [path.split("/")[-2] for path in filesPath]

elif os.name == "nt":
    filesPath = glob.glob(input("Type the path to the training files: ").replace("'", "") + "\*\*.cpp")
    filesLabels = [path.split("\\")[-2] for path in filesPath]


vectorizedFilesInLines = [vectorizeFileInLines(path) for path in filesPath]
vectorizedFilesWhole = [vectorizeFile(path) for path in filesPath]

filesLayoutData = layoutAnalysis(vectorizedFilesInLines)
filesLexicalData = lexicalAnalisys(vectorizedFilesWhole)

print(filesLayoutData[0])
print(filesLexicalData[0])

filesData = np.concatenate((filesLayoutData, filesLexicalData), axis=1)
print(filesData[0])

x_train, x_test, y_train, y_test = train_test_split(filesData, filesLabels, test_size=0.3)

# Geração do modelo por processo de machine learning com os dados dos arquivos conhecidos
knn = KNeighborsClassifier(metric="cityblock", n_neighbors=1, algorithm="brute")
knn.fit(x_train, y_train)



# Previsão sobre de quem o arquivo misterioso é
predictedAuthor = knn.predict(x_test)

# Calculo da precisão do modelo
print(f'Accuracy: {accuracy_score(y_test, predictedAuthor) * 100}')

if "-v" in sys.argv:
    printTestsPredicts(y_test, predictedAuthor)
