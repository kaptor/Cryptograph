#include "base64.h"

void toBase64(const char* in, int len, char* out)
{
	const char alphabet[] = "ABCDEFGH" "IJKLMNOP" "QRSTUVWX" "YZabcdef"
		"ghijklmn" "opqrstuv" "wxyz0123" "456789+/";
	const char padchar = '=';

	int padlen = 0;

	int i = 0;
	while (i < len) 
	{
		// encode 3 bytes at a time
		int chunk = 0;
		chunk |= int(static_cast<unsigned char>(in[i++])) << 16;
		if (i == len) {
			padlen = 2;
		} else {
			chunk |= int(static_cast<unsigned char>(in[i++])) << 8;
			if (i == len)
				padlen = 1;
			else
				chunk |= int(static_cast<unsigned char>(in[i++]));
		}

		int j = (chunk & 0x00fc0000) >> 18;
		int k = (chunk & 0x0003f000) >> 12;
		int l = (chunk & 0x00000fc0) >> 6;
		int m = (chunk & 0x0000003f);
		*out++ = alphabet[j];
		*out++ = alphabet[k];
		
		if (padlen > 1) {
			*out++ = padchar;
		} else {
			*out++ = alphabet[l];
		}

		if (padlen > 0) {
			*out++ = padchar;
		} else {
			*out++ = alphabet[m];
		}
	}
}


int fromBase64(const char* in, int len, char* out)
{
	unsigned int buf = 0;
	int nbits = 0;
	// out * 3 / 4

	int offset = 0;
	for (int i = 0; i < len; ++i)
	{
		int ch = in[i];
		int d;

		if (ch >= 'A' && ch <= 'Z')
			d = ch - 'A';
		else if (ch >= 'a' && ch <= 'z')
			d = ch - 'a' + 26;
		else if (ch >= '0' && ch <= '9')
			d = ch - '0' + 52;
		else if ('+' == ch)
			d = 62;
		else if ('/' == ch)
			d = 63;
		else
			d = -1;

		if (d != -1) {
			buf = (buf << 6) | d;
			nbits += 6;
			if (nbits >= 8) {
				nbits -= 8;
				out[offset++] = buf >> nbits;
				buf &= (1 << nbits) - 1;
			}
		}
	}
	return offset;
}
