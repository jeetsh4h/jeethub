import numpy as np
import os

def LoadEncodeMatrices():
    matrices = []
    file = open("ATM/encoder-matrices.txt", 'r')
    data = file.readlines()
    
    matrix = []
    i = 1
    for line in data:
        row = list(map(float, line.split()))
        if i != 16:                                             # (16, 16) matrices
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
WHICH_MATRIX_POS = 14                                           # just to inline random choosing of matrices
                                                                # ^ have to create and send list of which matrix as packet later (encoded with own matrix)
WHICH_PACKET_POS = 15
ENCRYPTION_MATRICES = LoadEncodeMatrices()

def Packet(card_num, pin):                                      # packet has 4 digits of information
    packets = []

#packeting card number
    k = 0
    for i in range(4):                                          # card_num divided into 4 packets
        packet = [np.random.randint(0, 9) for j in range(16)]
        
        j = packet[INFO_START_POS]
        for l in range(j, j + 4):                               # 4 == informationally significant digits per packet
            packet[l] = int(card_num[k])
            k += 1
        packet[WHICH_PACKET_POS] = i + 1
        packets.append(np.matrix(np.array(packet).reshape(16, 1), dtype=float))

#packeting pin 
    packet = [np.random.randint(0, 9) for j in range(16)]

    i = 0
    j = packet[INFO_START_POS]
    for l in range(j, j + 4):                                   # 4 == informationally significant digits per packet
        packet[l] = int(pin[i])
        i += 1
    packet[WHICH_PACKET_POS] = 5
    packets.append(np.matrix(np.array(packet).reshape(16, 1), dtype=float))

    return packets

def Encoder(packets):
    crypt_packets = []
    mat_pos_list = []

    for i in range(5):                                          # 5 == number of packets
#forming them for future use
        enc_mat_pos = int((packets[i])[WHICH_MATRIX_POS, 0])
        mat_pos_list.append(enc_mat_pos)
        
#encrypting the packet
        crypt_packet = np.matmul(ENCRYPTION_MATRICES[enc_mat_pos], packets[i])
        crypt_packets.append(crypt_packet)

    return crypt_packets, mat_pos_list
        

def WritePacketFile(crypt_packets):
#to ensure a fresh file is opened
    file = open("packets.txt", 'w')
    file.close()
    os.remove("packets.txt")


    indices_used = []
    file = open("packets.txt", 'a')

#randomly writing on text file
    while len(indices_used) < 5:                                # 5 == number of packets
        i = np.random.randint(0, 5)
        if indices_used.count(i) == 0:
            np.savetxt(file, crypt_packets[i])

#for future use,,, decrypting
            indices_used.append(i)

    file.close()
    return indices_used


def WriteMatPosFile(mat_pos_list, indices_used):                # need for decrypting
    file = open("packets.txt", 'a')

#corresponding mat_pos_list indices with packet order
    new_mat_pos_list = [0] * 5
    for i in range(5):
        new_mat_pos_list[i] = mat_pos_list[indices_used[i]]

#filling up the mat_pos with random integers
    mat_pos_packet = [np.random.randint(0, 9) for j in range(16)]
    if mat_pos_packet[INFO_START_POS] == 9:                     # mat_pos_packet has 5 informationally significant digits
        mat_pos_packet[INFO_START_POS] = 8

    j = mat_pos_packet[INFO_START_POS]
    i = 0
    for l in range(j, j + 5):
        mat_pos_packet[l] = new_mat_pos_list[i]
        i += 1

#encoding the mat_pos
    mat_pos_packet = np.matrix(np.array(mat_pos_packet).reshape(16, 1), dtype=float)
    crypt_mat_pos_list = np.matmul(ENCRYPTION_MATRICES[10], mat_pos_packet)     # chose new matrix because, if this gets cracked,, packets still have a layer of protection


    np.savetxt(file, crypt_mat_pos_list)
    file.close()
    return

def main():
    card_num = input("Enter your debit card number (16 digits): ").replace(" ", "")
    pin      = input("Enter your PIN: ")

    packets = Packet(card_num, pin)

    crypt_packets, mat_pos_list = Encoder(packets)
    
    indices_used = WritePacketFile(crypt_packets)
    WriteMatPosFile(mat_pos_list, indices_used)


#--------------------------------------------------#


if __name__ == "__main__":
    main()