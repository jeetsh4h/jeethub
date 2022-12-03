from server.gen_decoder_matrix import GenDecodeMatrices
from ATM.gen_encoder_matrix import GenEncodeMatrices

from numpy import random
from time import time

random.seed(int(time()))


seed = random.randint(0, 999999999)

GenEncodeMatrices(seed)
GenDecodeMatrices(seed)