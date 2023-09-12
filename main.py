
from modules.layout import layoutAnalysis
from modules.vectorizer import vectorizeFile
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import glob

filesPath = glob.glob(input("Type the path to the training files: ") + "/*/*.cpp")
filesLabels = [path.split("/")[-2] for path in filesPath]
files = [vectorizeFile(path) for path in filesPath]
filesData = layoutAnalysis(files)

x_train, x_test, y_train, y_test = train_test_split(filesData, filesLabels, test_size=0.3)

# Geração do modelo por processo de machine learning com os dados dos arquivos conhecidos
knn = KNeighborsClassifier(metric="cityblock", n_neighbors=1, algorithm="brute")
knn.fit(x_train, y_train)



# Previsão sobre de quem o arquivo misterioso é
predictedAuthor = knn.predict(x_test)
print(predictedAuthor)

# Calculo da precisão do modelo
print(accuracy_score(y_test, predictedAuthor))
