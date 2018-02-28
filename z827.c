#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Compresses a file by removing the first bit of every byte (ASCII z827), with a single line of C code.
void compress(FILE* in, FILE* out){ // Main loop. Initialize bit count to 7 then run one round of loop. Encode each character until end of file. Repeatedly or buff with next bit shifted left by current bit count, while increasing bit count by 7 after that, then if bit count is greater than 8, flush the last byte. Then, wrap up by flushing buf one last time.
	for(uint16_t bitc=7, buff=fgetc(in); feof(in) ? (fputc(buff,out)&0) : 1; buff|=fgetc(in)<<((bitc+=7)-7)) bitc = (bitc>8) ? ((bitc - 8)+(fputc(buff^(buff>>8)^(buff>>=8), out)&0)) : bitc;
}

int main() {
	compress(stdin, stdout);
}