import numpy as np
import os

def GenEncodeMatrices(seed):
    np.random.seed(seed)

    file = open("ATM/encoder-matrices.txt", 'w')
    file.close()
    os.remove("ATM/encoder-matrices.txt")


    file = open("ATM/encoder-matrices.txt", 'a')

    for i in range(11):
        matrix = np.matrix(np.random.uniform(-99.99999999, 100.0, size=(16, 16)))
        np.savetxt(file, matrix)

    file.close()