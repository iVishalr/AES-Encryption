void AES_Decrypt(unsigned char* message, unsigned char* expandedKey){

    unsigned char state[16];
    // Take only the first 16 characters of the message
    for (int i = 0; i < 16; i++)
        state[i] = message[i];

    int numberofrounds = 9;
    AddRoundKey(state,expandedKey + 160);

    for (int i = numberofrounds;i>0;i--){
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state,expandedKey + (16 * i));
        InvMixColumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state,expandedKey);

    for(int i=0;i<16;i++){
        message[i] = state[i];
    }
}