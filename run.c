#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "helper.c"
#include "encode.c"
#include "decode.c"

/*
 * This is the main Program to Implement Encode and Decode
 */

int main(int argc, char *argv[]){

	union decStore data;	/* decStore union is declared and defined in helper.c */
	
	if(argc != 3){		/* Program Validates the Number of Arguments Passed via command line Interface */
		printf("Error: Invalid Number of Arguments\n");
		return 0;
	}
	
	FILE *file = fopen(argv[2],"r");	/* Opening a File and Handling the Error if not open
						 * Pointer file of Given Input contains the number lengths or the encoded 
						 * Sequences of the lengths that is supposed to be encoded 
						 */
	if(!file){
		perror("Error: ");
		return 0;
	}
	
	/* This Part mainly deals with the Encoding of the given data */
	if(strcmp(argv[1],"-e")==0){		

	
		unsigned char *in, *out, lengthInBits, countOfSeqBits;
		
		FILE *encodedSeq = fopen("encodedSeq","w");	
		/* encodedSeq File is the file in which the number of encoded sequences of lengths will be Stored */
		
		fclose(encodedSeq);
		encodedSeq = fopen("encodedSeq","a");
		
		/* while loop scans the whole file and store the Encoded sequence for every length */
		while(fscanf(file,"%llu",&data.num)==1){	
		
			
			/* calCountOfBits(unsigned long long int) returns the number of bits required to store the length stored in unsigned long long int */
			lengthInBits = calCountOfBits(data.num);	
			

			unsigned char size = lengthInBits/8;

			if(lengthInBits%8!=0)
				size++;
			/* size is nothing but the Number of Bytes required to store the value returned by calCountOfBits() */
			
			/* Memory Allocation to in */
			in = (unsigned char *)malloc(size);
		
			//printf("For %llu\n",data.num);

			/* Storing data in in pointer so that can be passed to encode function */
			for(int i = 0; i < size; i++)
				*(in + i) = data.numInChar[size - i - 1];
			
			/* Memory Allocation to out */
			out = (unsigned char *)calloc(11,sizeof(unsigned char));

			/* 
			 * encode(unsigned char *, unsigned char, unsigned char *) is defined in encode.c and it encodes the value present in *in
			 * and Stores in *out and also returns the count of Bits required by the Encoded Sequence
			 */
			countOfSeqBits = encode(in,lengthInBits,out);
			
			
			/* writeSeqInFile is defined and declared in helper.c and stores the encoded Sequence in the opened file by FILE ptr 
			 * encodedSeq
			 */
			writeSeqInFile(encodedSeq,out,countOfSeqBits);
			
			/* freeing the *in and *out */
			free(in);
			free(out);
		}
		printf("Encoded Sequences successfully Generated for Input Files\nEncoded Sequences stored successfully in 'encodedSeq'\n");
		/* Closing the File */
		fclose(encodedSeq);

	}else if(strcmp(argv[1],"-d")==0){
	
		unsigned long long int data;
		/*
		 * Memory Allocation to encSeq so that line by line of String can be stored and passed to decode
		 */ 
		unsigned char *encSeq = (unsigned char *)calloc(13,sizeof(unsigned char));
		
		/* 
		 * File decodedData stores the Data retrieved from the encoded Sequences
		 */
		FILE *decodedData = fopen("decodedData","w");
		fclose(decodedData);
		decodedData = fopen("decodedData","a");
		
		/*
		 * While loop scanning line by line and decoding each encoded sequence
		 */
		while(fgets(encSeq,13,file)!=NULL){
			/* 
			 * decode(unsigned char*) is defined in helper.c and 
			 * returns the actual data which was encoded in that respective sequence
			 */
			data = decode(encSeq);
			
			/* Writing the data in the decodedData */
			writeDataInFile(decodedData,data);
                }
                printf("Encoded Sequences Decoded successfully\nRetreived Datas stored successfully in 'decodedData'\n");
                /* closing the decodedData file */
		fclose(decodedData);
	}else{
		/* Error Message */
		printf("Error: Invalid Operation Passed\n");
	}
	
	/*closing the Input File */
	fclose(file);
}
