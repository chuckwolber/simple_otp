/**
 * Copyright 2017 Chuck Wolber
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This is a very simple proof of concept tool to demonstrate OTP (One Time
 * Pad) encryption at a binary level. There are three lines of output for each
 * plain text character input - PLT (PLain Text), KEY (the OTP key value), and
 * XOR (the encrypted version).
 *
 * The first two lines are XOR'd to form the third line. Decryption occurs simply
 * by XOR'ing the second and third line, which should give you the first line. 
 * And for the sake of completeness, you can XOR the first and third line to get
 * the second line.
 *
 * In this implementation, if the key argument is shorter than the plain text
 * argument, the key is reused. In a real OTP implementation, one would *NEVER*
 * reuse any portion of the key. 
 *
 * As is the case with all encryption code, unless you are an expert in the
 * specific algorithm you are implementing, you should not be writing your own
 * code. As I am not an expert, I would strongly advise against using this code
 * for anything other than demonstration / POC purposes.
 * 
 * XOR Truth Table
 *    A B | O
 *   ---------
 *    0 0 | 0
 *    0 1 | 1
 *    1 0 | 1
 *    1 1 | 0
 *
 * Build Instructions:
 *  gcc -Wall -Wextra simple_otp.c -o simple_otp
 * 
 * Usage Instructions: 
 *  ./simple_otp "Hello World" "secret"
 *
 * Example Output:
 *  PLT: H  01001000
 *  KEY: s  01110011
 *  XOR:    00111011
 *  
 *  [ ... ]
 *  
 *  PLT: d  01100100
 *  KEY: e  01100101
 *  XOR:    00000001
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOCAL            static inline
#define BITSPERBYTE        8

LOCAL char* char_to_binary_string(char);
LOCAL char next_key_char(void);
LOCAL inline void display_code(char);

static const char *key;

int main(int argc, char **argv)
{
    char *plain_text;
    unsigned int i, pt_length;

    if (argc != 3) {
        printf("%s plain_text key\n", argv[0]);
        return 1;
    }
    
    plain_text = argv[1];
    key = argv[2];

    pt_length = strlen(plain_text);
    for (i=0; i<pt_length; i++)
        display_code(plain_text[i]);
    return 0;
}

LOCAL void display_code(char pt)
{
    char next_key = next_key_char();

    printf("PLT: %c\t%s\n", pt, char_to_binary_string(pt));
    printf("KEY: %c\t%s\n", next_key, char_to_binary_string(next_key));
    printf("XOR:   \t%s\n", char_to_binary_string(pt^next_key));
    printf("\n");
}

LOCAL char next_key_char(void) 
{
    static unsigned int next_key = 0;
    static size_t key_length;
    key_length = strlen(key);
    if (next_key >= key_length)
        next_key = 0;
    return key[next_key++];
}

LOCAL char* char_to_binary_string(char schar) 
{
    unsigned int bits = BITSPERBYTE*sizeof(char);
    char *result = malloc(bits);
    for (; bits>0; bits--) {
        result[bits-1] = '0';
        if (schar & 1)
            result[bits-1] = '1';
        schar = schar >> 1;
    }
    return result;
}
