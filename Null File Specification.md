# File Format Specification for .null files

This document explains the layout for the binary data to be stored in `.null` files. 

When given ASCII text files to the compressor utility, it will compress that data and write it in a binary format to a `.null` file. The `.null` file will hold the alphabets and their probabilities and after those will be an array of encoded codewords in bytes.



The `.null` file will be a flat array of bytes with 3 sections in this very sequence: 

1. `s` = Size of the alphabet and probability array : `[integer : 1 byte ]` => `unsigned char`

2. `a` = The Alphabet array : `[s characters : s bytes]` => `char[s]`

3. `p` = The Probability array : `[s floats : s*4 bytes]` => `float[s]`

4. `data` = The Codewords array : `[m integers : 2*m bytes]` => `uint16_t[m]` (Read this array till EOF)



An abstract representation of the binary data in the `.null` would look like this :

`100, [a, v, w, a, s,...], [0.06, 0.03, 0.04,...], [32143, 43412, 43542, .....]`








