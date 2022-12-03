import numpy as np

def LoadDecodeMatrices():
    matrices = []
    file = open("server/decoder-matrices.txt", 'r')
    data = file.readlines()
    
    matrix = []
    i = 1
    for line in data:
        row = list(map(float, line.split()))
        if i != 16:                                         # (16, 16) matrices
            matrix.append(row)
            i += 1
        else:
            matrix.append(row)
            matrices.append(np.matrix(matrix))
            
            i = 1
            matrix = []
    file.close()
    return matrices

INFO_START_POS = 13
WHICH_MATRIX_POS = 14                                       # dont need it for this file
WHICH_PACKET_POS = 15
DECRYPTION_MATRICES = LoadDecodeMatrices()

def ReadPacketFile():
    matrices = []
    file = open("packets.txt", 'r')
    data = file.readlines()
    
    matrix = []
    i = 1
    for line in data:
        row = list(map(float, line.split()))
        if i != 16:
            matrix.append(row)
            i += 1
        else:
            matrix.append(row)
            matrices.append(matrix)
            
            i = 1
            matrix = []
    file.close()
    return matrices

def Decoder(crypt_packets):
    crypt_mat_pos_packet = crypt_packets[5]                 # 5 == len(crypt_packets) - 1 == number of packets
    mat_pos_packet = np.matmul(DECRYPTION_MATRICES[10], crypt_mat_pos_packet)

#converting to int
    mat_pos_packet = np.rint(mat_pos_packet).astype(int)
    mat_pos_list = []
    for i in range(5):                                      # 5 == len(crypt_packets) - 1
        mat_pos_list.append(int(mat_pos_packet[mat_pos_packet[INFO_START_POS] + i, 0]))

#decoding the info packets
    packets = []
    packet = []
    packet_pos_list = []
    for i in range(5):                                      # 5 == len(crypt_packets) - 1
        packet_mat = np.matmul(DECRYPTION_MATRICES[mat_pos_list[i]], crypt_packets[i])
        packet_mat = np.rint(packet_mat).astype(int)

        packet_pos_list.append(packet_mat[WHICH_PACKET_POS, 0])    

        for j in range(4):
            packet.append(int(packet_mat[packet_mat[INFO_START_POS] + j, 0]))
        
        packets.append(packet)
        packet = []

#putting packets in order
    packets_ordered = [[]] * 5
    for i in range(5):
        packets_ordered[packet_pos_list[i] - 1] = packets[i]    # -1 because numbering of packet starts from 1, rather than 0

    return packets_ordered


def CardPinGenerator(packets_ordered):
    card_num = ""
    for i in range(4):
        for j in range(4):
            card_num += str(packets_ordered[i][j])
        card_num += ' '

    pin = ""
    for j in range(4):
        pin += str(packets_ordered[4][j])

    return card_num, pin

def main():
    crypt_packets = ReadPacketFile()
    packets = Decoder(crypt_packets)
    card_num, pin = CardPinGenerator(packets)

    print("The debit card number is " + card_num + "\nThe PIN is " + pin)

    
#--------------------------------------------------#


if __name__ == "__main__":
    main()