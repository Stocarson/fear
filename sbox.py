#!/usr/bin/env python3

uppermask = (2**8-1)<<8
lowermask = (2**8-1)

sbox_input_bits = 16
sbox_output_bits = 8
sbox_input_size = 1 << sbox_input_bits
sbox_output_size = 1 << sbox_output_bits


def sbox0(input):
    return (((input & uppermask) + (input & lowermask)) % 256 ) << 2

def isRelationTrue(inbits, outbits, sboxinput, sboxoutput):
    mask = 0
    inputrelation = 0
    outputrelation = 0
    for i in range(sbox_input_bits):
           mask = 1 << i
           if inbits & mask != 0:
               inputrelation ^= (sboxinput & mask) >> i
    for i in range(sbox_output_bits):
        mask = 1 << i
        if outbits & mask != 0:
            outputrelation ^= (sboxoutput & mask) >> i

    if inputrelation == outputrelation:
        return 1
    else:
        return 0

def buildlineartable():
    table = [[0 for j in range(sbox_output_size)] for i in range(sbox_input_size)]
    for i in range(sbox_input_size):
        for j in range(sbox_output_size):
            for z in range(sbox_input_size):
                table[i][j] += isRelationTrue(i, j, z, sbox0(z))
    for i in range(sbox_input_bits):
        for j in range(sbox_output_bits):
            table[i][j] -= (sbox_output_bits/2)
    return table

if __name__ == "__main__":
    output = ""
    for i in range(2**16):
        output+=str(sbox0(i))+","
    f = open("sbox0.txt", "w")
    f.write(output)
    f.close()
