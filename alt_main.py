
from modules.misc import getFilesPaths, printTestsPredicts
from modules.vectorizer import vectorizeFileInLines, vectorizeWholeFile
from modules.layout import layoutAnalysis
from modules.lexical import lexicalAnalysis

import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score



DATASET_PATH = "/Users/Jbernardis/Documents/stylometryResearch/data/dataset-v3"
filesPath, filesLabels = getFilesPaths(DATASET_PATH)

vectorizedFilesInLines = [vectorizeFileInLines(path) for path in filesPath]
vectorizedFilesWhole = [vectorizeWholeFile(path) for path in filesPath]

filesLayoutData = layoutAnalysis(vectorizedFilesInLines)
filesLexicalData = lexicalAnalysis(vectorizedFilesWhole)

filesData = np.concatenate((filesLayoutData, filesLexicalData), axis=1)

x_test = filesData[0:15]
y_test = filesLabels[0:15]

x_train = filesData[15:]
y_train = filesLabels[15:]

knn = KNeighborsClassifier(metric="cityblock", n_neighbors=1, algorithm="brute")
knn.fit(x_train, y_train)

# Previsão sobre de quem o arquivo misterioso é
predictedAuthor = knn.predict(x_test)
predictedAuthorProb = knn.predict_proba(x_test)

print(predictedAuthor)
print(predictedAuthorProb.shape)

print(f'Accuracy: {accuracy_score(y_test, predictedAuthor)}')