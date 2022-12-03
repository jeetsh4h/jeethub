This is the first file that will be run
The update.py script can be executed at a regular frequency

The main directory,, the folder that the README is saved in is the main folder

This folder current houses the update.py script file,, which would ideally be run at the same time
for both the server (stored as a directory) and the ATM (also stored as a directory)

Moreover, the main directory also acts as a place where network traffic goes through
the encrypted packets will be stored in this directory




When running the ATM-server files for the first time,,, run the update.py script once
before the ATM-server files are run
the udpdate.py file can be run before every ATM-server file execution
or after every n executions (transactions)




The ATM file takes in two user inputs -> a 16 digit card number
                                      -> a 4 digit PIN
The output for the file is 1 meta-packet, that contains 6 packets (of 16 floats)
The meta-packet consists of 5 16x1 matrices that have been encrypted using one of 10 16x16 matrices (random floats)
                        and 1 16x1 matrix that has been encypted using 1 16x16 matrix (random floats)
The first 5 packets in the meta-packet consists of the information in encrypted form (the card number and pin)
The last packet consists of ancillary information that consists integers to help decrypt the above 5 packets

The last packet stores which 16x16 matrix has been used to encrypt the 5 packets
Moreover, the 5 packets are randomly stored, they are not stored in order,,, the position of the packet is also stored
                                                                              as a pre-defined element in their respective matrix
The ATM also reads the 11 matrices


The server takes in no user inputs
It only outputs the decrypted card number and PIN
The file reads the packets (in their encrypted forms),,, decrypts it using inverse 16x6 matrices (corresponding)
The file then sets up the packets in the correct order and extracts the information



Make sure to run the python interpreter in the main folder "linear-transform-crypto"