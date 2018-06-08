#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "openssl/sha.h"
#include "ed25519.h"

void printkey(FILE* fp,const uint8_t* key,int len)
{	int i;
	for(i=0;i<len;i++){
		fprintf(fp,"%02X",key[i]);}
	fprintf(fp,"\n");
}

int main(int argc, char** argv)
{	ed25519_public_key pk;
	ed25519_secret_key sk;
	ed25519_signature  sg;
	SHA256_CTX sha256;
        char* key="";

	assert(sizeof(sk)==SHA256_DIGEST_LENGTH);
	if(argc<=1){
		fprintf(stderr,"USAGE: %s \"brain-key-string\"|\"-\"\n",argv[0]);
		return(-1);}
        if(argv[1][0]=='-' && argv[1][1]=='\0'){
		int l=0;
		key=malloc(1025);
		if(fgets(key,1024,stdin)!=NULL){
			l=strlen(key);
			if(l>1 && key[l-1]=='\n'){
				key[l-1]='\0';}}}
	else{
		key=argv[1];}
	SHA256_Init(&sha256);
	SHA256_Update(&sha256,key,strlen(key));
	SHA256_Final(sk,&sha256);
	ed25519_publickey(sk,pk);
	fprintf(stdout,"SK: ");
	printkey(stdout,sk,32);
	fprintf(stdout,"PK: ");
	printkey(stdout,pk,32);
	ed25519_sign((const unsigned char*)NULL,0,sk,pk,sg);
	fprintf(stdout,"SG: ");
	printkey(stdout,sg,64);
	return 0;
}

