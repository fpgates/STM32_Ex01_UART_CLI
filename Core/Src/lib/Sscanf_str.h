/*
 * sscanf_str.h
 *
 *  Created on: 2014. 1. 9.
 *      Author: yiso
 */

#ifndef SSCANF_STR_H_
#define SSCANF_STR_H_

#include "../Defines.h"

s2_t sscanf_str(s1_t* s1p_InputStr, s1_t* s1p_OutputStr, s1_t* s1p_EOS);
s2_t sscanf_1s4(s1_t** s1pp_InputStr, s4_t* s4p_Data1, s4_t s4_Base);
s2_t sscanf_1u4(s1_t** s1pp_InputStr, u4_t* u4p_Data1, s4_t s4_Base);
s2_t sscanf_2u4(s1_t** s1pp_InputStr, u4_t* u4p_Data1, u4_t* u4p_Data2, s4_t s4_Base);
s2_t sscanf_3u4(s1_t** s1pp_InputStr, u4_t* u4p_Data1, u4_t* u4p_Data2, u4_t* u4p_Data3, s4_t s4_Base);
s2_t sscanf_4u4(s1_t** s1pp_InputStr, u4_t* u4p_Data1, u4_t* u4p_Data2, u4_t* u4p_Data3, u4_t* u4p_Data4, s4_t s4_Base);
s2_t sscanf_5u4(s1_t** s1pp_InputStr, u4_t* u4p_Data1, u4_t* u4p_Data2, u4_t* u4p_Data3, u4_t* u4p_Data4, u4_t* u4p_Data5, s4_t s4_Base);

#endif /* SSCANF_STR_H_ */

