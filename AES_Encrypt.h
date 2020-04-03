void AES_Encrypt(unsigned char* message, unsigned char* expandedKey){
    
    //To copy the message into a separate array to work on it.
    unsigned char state[16];
    for(int i=0;i<16;i++)
        state[i] = message[i];
    int number_of_rounds = 9;
    //Adding round key to the expanded key
    AddRoundKey(state,expandedKey);

    for(int i=0;i<number_of_rounds;i++){
        
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state,expandedKey + (16*(i+1)));
    }
    //For Final Round
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state,expandedKey + 160);
    //Copy the encrypted version of state to the original message
    for(int i=0;i<16;i++)
        message[i] = state[i];
}

