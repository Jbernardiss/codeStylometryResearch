
import io

def vectorizeFile(filePath: str) -> list[str]:

  with open(filePath, "rb") as f:
      file = f.readlines()
      file = [line.decode("utf-8") for line in file]

      return file