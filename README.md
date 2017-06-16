# Overview #

This is a very simple proof of concept tool to demonstrate OTP (One Time
Pad) encryption at a binary level. There are three lines of output for each
plain text character input - PLT (PLain Text), KEY (the OTP key value), and
XOR (the encrypted version).

The first two lines are XOR'd to form the third line. Decryption occurs simply
by XOR'ing the second and third line, which should give you the first line. 
And for the sake of completeness, you can XOR the first and third line to get
the second line.

In this implementation, if the key argument is shorter than the plain text
argument, the key is reused. In a real OTP implementation, one would *NEVER*
reuse any portion of the key. 

As is the case with all encryption code, unless you are an expert in the
specific algorithm you are implementing, you should not be writing your own
code. As I am not an expert, I would strongly advise against using this code
for anything other than demonstration / POC purposes.
 
## XOR Truth Table ##

    A B  | O
    --------
    0 0  | 0
    0 1  | 1
    1 0  | 1
    1 1  | 0

## Build Instructions: ##
 `gcc -Wall -Wextra simple_otp.c -o simple_otp`

## Usage Instructions: ##
 `./simple_otp "Hello World" "secret"`

## Example Output: ##

    PLT: H  01001000
    KEY: s  01110011
    XOR:    00111011
    
    [ ... ]
    
    PLT: d  01100100
    KEY: e  01100101
    XOR:    00000001
