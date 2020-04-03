AES-Encryption

---------------------------------------------------------------------------------------------------------------------------------------------------

MIT License

Copyright (c) 2020 Vishal R

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---------------------------------------------------------------------------------------------------------------------------------------------------

This is a simple implementation of the Advanced Encryption Standard using C Programming Language

This is a quick and simple AES Encryption implementation using C Programming Language The below code takes in a Base64 encoded string(message) and and Base64 encoded Key from the user and encrypts it according to AES algorithms and standards. As of now only 128 - bit level encryption is supported.

THIS IMPLEMENTATION MUST NOT BE USED TO ENCRYPT AND DECRYPT TEXT,FILES OR ANYTHING AS IT IS VULNERABLE TO CACHE ATTACKS AND MANY OTHER ATTACKS AND HE OR SHE WHO IS ATTACKING CAN READ THE BYTES SUBSTITUTED FROM S_BOX BY TIMING THEIR ATTACK WHILE THE ENCRYPTION IS TAKING PLACE.

---------------------------------------------------------------------------------------------------------------------------------------------------
TO BUILD THE PROJECT

In your terminal run the following:

make

To remove the image file after program execution run the following:

make clean
