/*
 * sscanf_str.c
 *
 *  Created on: 2014. 1. 9.
 *      Author: yiso
 */
#include "sscanf_str.h"

#define STRING_NUM_MAX (255)

s2_t sscanf_str (s1_t *s1p_InputStr, s1_t *s1p_OutputStr, s1_t *s1p_EOS)
{
  s2_t s2_StrLen;

  *s1p_EOS = 0;

  for(s2_StrLen = 0; s2_StrLen < STRING_NUM_MAX; s2_StrLen++)
  {
    if((char) (*(s1p_InputStr + s2_StrLen)) == ' ')
      break;
    else if((char) (*(s1p_InputStr + s2_StrLen)) == 0)
    {
      *s1p_EOS = 1;
      break;
    }
    else
      *(s1p_OutputStr + s2_StrLen) = *(s1p_InputStr + s2_StrLen);
  }
  *(s1p_OutputStr + s2_StrLen) = 0;

  return s2_StrLen;
}

s2_t sscanf_char (s1_t **s1pp_InputStr, s1_t *s1p_Data1)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
//u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
//for(u1_Index = 0; u1_Index < 1; u1_Index++)
//{
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *s1p_Data1 = s1a_DataStr[0];
      s2_ParamRead++;
    }
//  if(s1_EOS == 1)
//    break;
//}

  return s2_ParamRead;
}

s2_t sscanf_1s4 (s1_t **s1pp_InputStr, s4_t *s4p_Data1, s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
//u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
//for(u1_Index = 0; u1_Index < 1; u1_Index++)
//{
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *s4p_Data1 = strtol (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
//  if(s1_EOS == 1)
//    break;
//}

  return s2_ParamRead;
}

s2_t sscanf_1u4 (s1_t **s1pp_InputStr, u4_t *u4p_Data1, s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
//u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
//for(u1_Index = 0; u1_Index < 1; u1_Index++)
//{
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *u4p_Data1 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
//  if(s1_EOS == 1)
//    break;
//}

  return s2_ParamRead;
}

s2_t sscanf_2u4 (s1_t **s1pp_InputStr, u4_t *u4p_Data1, u4_t *u4p_Data2,
                 s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
  u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
  for(u1_Index = 0; u1_Index < 2; u1_Index++)
  {
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *u4p_Data1 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 1)
        *u4p_Data2 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
    if(s1_EOS == 1)
      break;
  }

  return s2_ParamRead;
}

s2_t sscanf_3u4 (s1_t **s1pp_InputStr, u4_t *u4p_Data1, u4_t *u4p_Data2,
                 u4_t *u4p_Data3, s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
  u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
  for(u1_Index = 0; u1_Index < 3; u1_Index++)
  {
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *u4p_Data1 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 1)
        *u4p_Data2 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 2)
        *u4p_Data3 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
    if(s1_EOS == 1)
      break;
  }

  return s2_ParamRead;
}

s2_t sscanf_4u4 (s1_t **s1pp_InputStr, u4_t *u4p_Data1, u4_t *u4p_Data2,
                 u4_t *u4p_Data3, u4_t *u4p_Data4, s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
  u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
  for(u1_Index = 0; u1_Index < 4; u1_Index++)
  {
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *u4p_Data1 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 1)
        *u4p_Data2 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 2)
        *u4p_Data3 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 3)
        *u4p_Data4 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
    if(s1_EOS == 1)
      break;
  }

  return s2_ParamRead;
}

s2_t sscanf_5u4 (s1_t **s1pp_InputStr, u4_t *u4p_Data1, u4_t *u4p_Data2,
                 u4_t *u4p_Data3, u4_t *u4p_Data4, u4_t *u4p_Data5,
                 s4_t s4_Base)
{
  s2_t s2_ParamRead;
  s2_t s2_StrLen;
  s1_t s1_EOS;
  u1_t u1_Index;
  s1_t s1a_DataStr[STRING_NUM_MAX + 1];
  s1_t *s1p_XStr;

  s2_ParamRead = 0;
  for(u1_Index = 0; u1_Index < 5; u1_Index++)
  {
    s2_StrLen = sscanf_str (*s1pp_InputStr, s1a_DataStr, &s1_EOS);
    *s1pp_InputStr = *s1pp_InputStr + s2_StrLen + 1;
    if(s2_StrLen != 0)
    {
      if(s2_ParamRead == 0)
        *u4p_Data1 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 1)
        *u4p_Data2 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 2)
        *u4p_Data3 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 3)
        *u4p_Data4 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      else if(s2_ParamRead == 4)
        *u4p_Data5 = strtoul (s1a_DataStr, &s1p_XStr, s4_Base);
      s2_ParamRead++;
    }
    if(s1_EOS == 1)
      break;
  }

  return s2_ParamRead;
}

