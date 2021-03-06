//
// Created by junaid on 25/02/21.
//

#include "../include/Decoder.h"
 
 /*
 
 decode_for_5character_words(num)
 {  
    for(int i=0; i<5; i++)
    {
        loop through cumm_probability map of characters
        {
            if(scale*cumm_probability[ch+1]>num) { 
                store ch
                break;    
            }
        }
        num = ( num - cumm_probability[ch] ) / probability[ch] ;
    }
 }
 */