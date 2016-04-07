#!/usr/bin/env python3

uppermask = (2**8-1)<<8
lowermask = (2**8-1)

def sbox0(input):
    return (((input & uppermask) + (input & lowermask)) % 256 ) << 2

if __name__ == "__main__":
    output = ""
    for i in range(2**16):
        output+=","+str(sbox0(i))
    f = open("output.txt", "w")
    f.write(output)
    f.close()
