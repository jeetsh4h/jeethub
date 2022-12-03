import numpy as np
import os

__name__ = "gen_decoder_matrix"

def GenDecodeMatrices(seed):
    np.random.seed(seed)

    file = open("server/decoder-matrices.txt", 'w')
    file.close()
    os.remove("server/decoder-matrices.txt")


    file = open('server/decoder-matrices.txt', 'a')

    for i in range(11):
        matrix = np.matrix(np.random.uniform(-99.99999999, 100.0, size=(16, 16)))
        np.savetxt(file, np.linalg.inv(matrix))

    file.close()