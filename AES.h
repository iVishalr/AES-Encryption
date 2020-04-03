#include"lookup.h"
void KeyExpansionCore(unsigned char* in, unsigned char i) {
  
    unsigned int * q = (unsigned int *) in;
    // Left rotate bytes
    *q = (*q >> 8 | ((*q & 0xff) << 24));

    in[0] = s_box[in[0]]; 
    in[1] = s_box[in[1]];
    in[2] = s_box[in[2]]; 
    in[3] = s_box[in[3]];

    // RCon XOR
    in[0] ^= rcon[i];
}

void KeyExpansion(unsigned char* inputKey, unsigned char* expandedKey){

    //The first 16 bytes are the original key bytes
    for(int i=0;i<16;i++)
        expandedKey[i] = inputKey[i];
    
    int bytesGenerated = 16;
    int rconIteration = 1;
    unsigned char temp[4];
    while(bytesGenerated<176){

        //The bytes for the core are the previously generated 4 bytes
        for(int i=0;i<4;i++)
            temp[i] = expandedKey[i+bytesGenerated-4];

        //Once every new key is created we call the KeyExpansionCore
        if(bytesGenerated%16==0)
            KeyExpansionCore(temp,rconIteration++);
        //Once we have the four bytes generated from the KeyExpansionCore, we XOR the first four bytes with
        //temp[i] and store it as a new set of generated 4 bytes.
        for(unsigned int a = 0;a<4;a++){
            expandedKey[bytesGenerated] = expandedKey[bytesGenerated - 16] ^ temp[a];
            bytesGenerated++;
        }
    }
}

void AddRoundKey(unsigned char* state,unsigned char* roundkey){

    for(int i=0;i<16;i++)
        state[i] = state[i]^roundkey[i];
}

void SubBytes(unsigned char* state){

    for (int i = 0; i < 16; i++){
        state[i] = s_box[state[i]];
    }
}

void ShiftRows(unsigned char* state){

    unsigned char tmp[16];
    //tmp[16] = '\0';
    //1st column
    tmp[0] = state[0];
    tmp[1] = state[5];
    tmp[2] = state[10];
    tmp[3] = state[15];
    //2nd column
    tmp[4] = state[4];
    tmp[5] = state[9];
    tmp[6] = state[14];
    tmp[7] = state[3];
    //3rd column
    tmp[8] = state[8];
    tmp[9] = state[13];
    tmp[10] = state[2];
    tmp[11] = state[7];
    //4th column
    tmp[12] = state[12];
    tmp[13] = state[1];
    tmp[14] = state[6];
    tmp[15] = state[11];

    //Copying the shifted grid to our state array.
    for(int i=0;i<16;i++)
        state[i] = tmp[i];
}

void MixColumns(unsigned char* state){
    
    unsigned char tmp[16];

    // Column 1 entries
    tmp[0] = (unsigned char) ((((mul2[state[0]] ^ mul3[state[1]]) ^ state[2]) ^ state[3]));
    tmp[1] = (unsigned char) (state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3]);
    tmp[2] = (unsigned char) (state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]]);
    tmp[3] = (unsigned char) (mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]]);
 
    // Column 2 entries
    tmp[4] = (unsigned char) (mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7]);
    tmp[5] = (unsigned char) (state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7]);
    tmp[6] = (unsigned char) (state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]]);
    tmp[7] = (unsigned char) (mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]]);
 
    // Column 3 entries
    tmp[8] = (unsigned char) (mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11]);
    tmp[9] = (unsigned char) (state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11]);
    tmp[10] = (unsigned char) (state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]]);
    tmp[11] = (unsigned char) (mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]]);
 
    // Column 4 entries
    tmp[12] = (unsigned char) (mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15]);
    tmp[13] = (unsigned char) (state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15]);
    tmp[14] = (unsigned char) (state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]]);
    tmp[15] = (unsigned char) (mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]]);

    //memcpy(state,tmp,sizeof(state));
    for(int i=0;i<16;i++)
        state[i] = tmp[i];
}
void InvShiftRows(unsigned char* state){

    unsigned char tmp[16];
    // First row don't shift (idx = idx)
    tmp[0] = state[0];
    tmp[4] = state[4];
    tmp[8] = state[8];
    tmp[12] = state[12];

    // Second row shift right once
    tmp[1] = state[13];
    tmp[5] = state[1];
    tmp[9] = state[5];
    tmp[13] = state[9];

    // Third row shift right twice
    tmp[2] = state[10];
    tmp[6] = state[14];
    tmp[10] = state[2];
    tmp[14] = state[6];

    // Fourth row shift right three times
    tmp[3] = state[7];
    tmp[7] = state[11];
    tmp[11] = state[15];
    tmp[15] = state[3];

    for (int i = 0; i < 16; i++)
        state[i] = tmp[i];
}

void InvSubBytes(unsigned char* state){

    // Substitute each state value with another byte in the Rijndael S-Box
    for (int i = 0; i < 16; i++)
        state[i] = inverseS_Box[state[i]];
}

void InvMixColumns(unsigned char* state){

    unsigned char tmp[16];

    // Column 1
    tmp[0] = (unsigned char) (mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]] ^ mul9[state[3]]);
    tmp[1] = (unsigned char) (mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]]);
    tmp[2] = (unsigned char) (mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]]);
    tmp[3] = (unsigned char) (mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]]);
 
    // Column 2
    tmp[4] = (unsigned char) (mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]] ^ mul9[state[7]]);
    tmp[5] = (unsigned char) (mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]]);
    tmp[6] = (unsigned char) (mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]]);
    tmp[7] = (unsigned char) (mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]]);
 
    // Column 3
    tmp[8] = (unsigned char) (mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]] ^ mul9[state[11]]);
    tmp[9] = (unsigned char) (mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]]);
    tmp[10] = (unsigned char) (mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]]);
    tmp[11] = (unsigned char) (mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]]);
 
    // Column 4
    tmp[12] = (unsigned char) (mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]]);
    tmp[13] = (unsigned char) (mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]]);
    tmp[14] = (unsigned char) (mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]]);
    tmp[15] = (unsigned char) (mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]]);

    for (int i = 0; i < 16; i++)
        state[i] = tmp[i];
}