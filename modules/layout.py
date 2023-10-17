
import math
import numpy as np


def layoutAnalysis(files: list[list[str]]) -> np.ndarray:

    """A function that does a layout analysis of a set of files

        Info inside the returned matrix:

            0 - A int boolean(0(false), 1(true)) representing the use of tabs or spaces for identation. 1 is for the use of tabs, 0 is
        for the use of spaces.

        1 - Log of the number of spaces divided by the file length in characters. Ln(num/len)

        2 - Log of the number of empty lines divided by the file length in characters. Ln(num/len)

        3 - Log of the number of comments divided by the file length in characters. Ln(num/len)

        4 - Average line length

        Returns:
            NDArray[float64]: A matrix containing the info about the analyzed files
    """

    feats = np.zeros((len(files),5))


    index = 0
    for file in files:
        tabIdent = 0
        spaceCount = 0
        emptyLinesCount = 0
        commentCount = 0
        linesLengthSum = 0

        for line in file:

            linesLengthSum += len(line)

            if "\t" in line:
                tabIdent = 1

            if line == "\n":
                emptyLinesCount += 1

            if "//" in line:
                if '"' in line[0:line.rindex("//")] and '"' in line[line.rindex("//"):]:
                    pass
                else:
                    commentCount += 1

            if "/*" in line:
                commentCount +=1

            for c in line:
                if c == " ":
                    spaceCount += 1



        feats[index, 0] = tabIdent

        if spaceCount != 0:
            feats[index, 1] = math.log(spaceCount/len(file))

        if emptyLinesCount != 0:
            feats[index, 2] = math.log(emptyLinesCount/len(file))

        if commentCount != 0:
            feats[index, 3] = math.log(commentCount/len(file))

        if linesLengthSum != 0:
            feats[index, 4] = linesLengthSum/len(file)

        index += 1

    return feats
