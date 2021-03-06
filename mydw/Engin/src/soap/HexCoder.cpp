#ifdef ENABLE_AXISTRACE
/* TRACE ADDED BY THE TRACE INSTRUMENTOR TOOL */
#include "../common/AxisTrace.h"
#endif
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "HexCoder.h"

const static char s_HexToNumTable[256]=
{
/* following is for ascii characters */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 00  - 15  */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 16  - 31  */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32  - 47  */
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,  /* 48  - 63  */
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64  - 79  */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 80  - 95  */
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96  - 111 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 112 - 127 */
/* Following is for ebcdic characters */
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 143 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 144 - 159 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 175 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 176 - 191 */
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 207 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 208 - 223 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 239 */
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,  /* 240 - 255 */
};
    
const static char s_NumToHexTable[16] =
{
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

int Hex_Encode(char * coded_dst, const unsigned char *plain_src,
               int len_plain_src)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry(NULL, "Hex_Encode", NULL, 3,
					TRACETYPE_STRING, 0, ((void*)&coded_dst),
					TRACETYPE_POINTER, sizeof(unsigned char), ((void*)&plain_src),
					TRACETYPE_INT, 0, ((void*)&len_plain_src));	  /* AUTOINSERTED TRACE */
	#endif

    const unsigned char *cur = plain_src;
    const unsigned char *end = cur + len_plain_src;
    while(cur < end)
    {
        *coded_dst = s_NumToHexTable[(*cur) >> 4];
        coded_dst++;
        *coded_dst = s_NumToHexTable[(*cur)& 0x0f];
        coded_dst++;
        cur++;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = (0);
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit(NULL, "Hex_Encode", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return 0;
		#endif
	}

}

int Hex_Decode(unsigned char * plain_dst, const char *coded_src)
{
	#ifdef ENABLE_AXISTRACE
		if (axiscpp::AxisTrace::isTraceOn())
			axiscpp::AxisTrace::traceEntry(NULL, "Hex_Decode", NULL, 2,
					TRACETYPE_POINTER, sizeof(unsigned char), ((void*)&plain_dst),
					TRACETYPE_STRING, 0, ((void*)&coded_src));	  /* AUTOINSERTED TRACE */
	#endif

    unsigned char* curr = plain_dst;
    while (*coded_src != '\0')
    {
        *curr = (s_HexToNumTable[(int)(*coded_src)] << 4) | 
            s_HexToNumTable[(int)(*(coded_src+1))];
        curr++;
        coded_src+=2;
    }
    	{
		#ifdef ENABLE_AXISTRACE
			int traceRet = ((int)(curr-plain_dst));
			if (axiscpp::AxisTrace::isTraceOn())
				axiscpp::AxisTrace::traceExit(NULL, "Hex_Decode", NULL, 0,
					TRACETYPE_INT, 0, ((void*)&traceRet));	  /* AUTOINSERTED TRACE */
			return traceRet;
		#else
			return (int)(curr-plain_dst);
		#endif
	}

}

