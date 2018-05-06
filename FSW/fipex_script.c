#include "includes.h"

int nCurrentScriptLoop = 0;
SCRIPT_STRUCTURE_t *pScriptArray;
int nFIPAbortScript = 0;
int nScriptStep;
int nSMStep;

void FIP_InitScripts(void)
{
  pScriptArray = (SCRIPT_STRUCTURE_t *)FIP_SCRIPT_ADDRESS;
  
  if (OP_GetActiveFIPScript() > 0)
  {
    FIP_RunScript(1);
  }
}

int FIP_VerifyScript(uint8 yScript)
{
  SCRIPT_STRUCTURE_t *pScript = &pScriptArray[yScript-1];
  uint16 wCRC;
  uint8 *pBytes = (uint8 *)(&(pScript->suScript));
  
  if (pScript->unSync == FIP_SCRIPT_SYNC)
  {
    wCRC = CRC16_CCITT(pBytes,pScript->uwLen);
    if (wCRC == pScript->uwCRC)
    {
      print_uart_msg("FIP:  Script %d Verified Successfully. (%lu)\n",yScript,get_time());
      return(1);
    }
    else
    {
      print_uart_msg("FIP:  Script %d Failed CRC Check %04X/%04X (%lu)\n",
                                     yScript, wCRC, pScript->uwCRC,get_time());
      return(0);
    }
  }
  else
  {
    print_uart_msg("FIP:  Script %d Failed Sync Check\n", yScript);
    return(0);
  } 
}

int FIP_StoreScriptBytes(uint8 yScript, 
                         uint8 yOffset, 
                         uint8 yLen, 
                         uint8 *pScriptBytes)
{
  int i;
  uint8 *pScript = (uint8 *)(&pScriptArray[yScript-1]) + yOffset;
  
  //print_uart_msg("FIPEX:  Storing script %d, offset %d, Len %d.\n",yScript,yOffset,yLen);
  
  if ((yLen+yOffset) > sizeof(SCRIPT_STRUCTURE_t))
  {
    print_uart_msg("FIPEX:  Script load too large.\n");
    return 0; //Too big
  }
  else
  {
    if (yOffset == 0)
    {
      print_uart_msg("Deleting old script: %d bytes @%p  (%lu)\n",
                   sizeof(SCRIPT_STRUCTURE_t),&pScriptArray[yScript-1],get_time());
      memset(&pScriptArray[yScript-1],0,sizeof(SCRIPT_STRUCTURE_t)); //Zero out old one
    }
    
    print_uart_msg("FIPEX:  Loading %d bytes to script %d (%lu)\n",yLen,yScript,get_time());
    for (i=0;i<yLen;i++)
    {
      *pScript = pScriptBytes[i];
      pScript++;
    }
    return 1;
  }  
}

void FIP_StoreScript(uint8 yScript, SCRIPT_STRUCTURE_t *pScript)
{
  memset(&pScriptArray[yScript-1],0,sizeof(SCRIPT_STRUCTURE_t)); //Zero out old one
  
  //Copy in new one
  memcpy(&pScriptArray[yScript-1],pScript,sizeof(SCRIPT_STRUCTURE_t));
}

void FIP_ReadScript(uint8 yScript, SCRIPT_STRUCTURE_t *pScript)
{
  memcpy(&pScript,&pScriptArray[yScript-1],sizeof(SCRIPT_STRUCTURE_t));
}

uint8 FIP_GetScriptLen(uint8 yScript)
{
  return(pScriptArray[yScript-1].suScript.yLen);
}

uint32 FIP_GetScriptStartTime(uint8 yScript)
{
  return(Swap32(pScriptArray[yScript-1].suScript.unStartTime));
}

uint16 FIP_GetScriptRepeatTime(uint8 yScript)
{
  return(Swap16(pScriptArray[yScript-1].suScript.uwRepeatTime));
}

uint8 FIP_GetScriptCmdCount(uint8 yScript)
{
  return(pScriptArray[yScript-1].suScript.yCmdCnt);
}

void FIP_PrintScript(uint8 yScript)
{
  PrintBytes((uint8 *)&pScriptArray[yScript-1], sizeof(SCRIPT_STRUCTURE_t));
}

void FIP_EraseScript(uint8 yScript)
{
int i;

  if (yScript > 0)
  {
    memset(&pScriptArray[yScript-1],0,sizeof(SCRIPT_STRUCTURE_t));
    if (OP_GetActiveFIPScript() == yScript)
    {
      OP_SetActiveFIPScript(0);
    }
  }
  else  //Erase all scripts if yScript is 0
  {
    for (i=1;i<=7;i++)
    {
      memset(&pScriptArray[i-1],0,sizeof(SCRIPT_STRUCTURE_t));
    }
    OP_SetActiveFIPScript(0);
  }
}

int FIP_GetCmdOffset(uint8 yScript, uint8 yCmdNum)
{
int i;
int nOffset = 0;
uint8 yCmdLen;

  if (yCmdNum == 0)
  {
    return 0;
  }
  else
  {
    for (i=1;i<=yCmdNum;i++)
    {
      yCmdLen = pScriptArray[yScript-1].suScript.ayCmdBytes[nOffset+2];
      nOffset = nOffset + yCmdLen + 4 + 2; //Add 2 more for delay
      
      if (i==yCmdNum)
      {
        break;
      }
    }
    
    return(nOffset);
  } 
}

uint8 FIP_GetCmdID(uint8 yScript, uint8 yCmdNum)
{
int nOffset;

  nOffset = FIP_GetCmdOffset(yScript, yCmdNum);
  
  return(pScriptArray[yScript-1].suScript.ayCmdBytes[nOffset+1]);
}

uint8 FIP_GetCmdLen(uint8 yScript, uint8 yCmdNum)
{
int nOffset;

  nOffset = FIP_GetCmdOffset(yScript, yCmdNum);
  
  return(pScriptArray[yScript-1].suScript.ayCmdBytes[nOffset+2]);
}

void FIP_SendScriptCmd(uint8 yScript, uint8 yCmdNum)
{
uint8 yCmdLen = FIP_GetCmdLen(yScript, yCmdNum);
int nOffset   = FIP_GetCmdOffset(yScript, yCmdNum);

/*
  print_uart_msg("FIP:  Cmd=%02X  Len=%d\n",
                pScriptArray[yScript-1].suScript.ayCmdBytes[nOffset+1],
                yCmdLen);
*/
               
  FIP_SendCmd(&pScriptArray[yScript-1].suScript.ayCmdBytes[nOffset], yCmdLen+4);
}

uint16 FIP_GetCmdDelay(uint8 yScript, uint8 yCmdNum)
{
int nOffset;
uint8 yLen;
uint16 uwDelay;
int nDelayOffset;

  nOffset = FIP_GetCmdOffset(yScript, yCmdNum);
  yLen    = FIP_GetCmdLen(yScript, yCmdNum);
  
  nDelayOffset = nOffset+yLen+4;
  
  //Get LE value
  uwDelay = pScriptArray[yScript-1].suScript.ayCmdBytes[nDelayOffset] +
            (pScriptArray[yScript-1].suScript.ayCmdBytes[nDelayOffset+1] << 8);
            
  if (uwDelay == 0xFFFF)
  {
    return(1); //1 second delay for immediate
  }            
  else
  {
    return(uwDelay);
  }
}

void FIP_RunScript(int nStart)
{
static uint32 unRunTime;
uint8 yScript   = 0;
uint8 yCmdID    = 0;
static int nNakCount = 0;

  yScript = OP_GetActiveFIPScript();
  
  if (nStart)
  {
    nScriptStep = 0;
    nSMStep     = FIP_SCRIPT_START;
    unRunTime   = FIP_GetScriptStartTime(yScript);
  }
   
  switch (nSMStep)
  {
    case FIP_SCRIPT_START:
      if (yScript > 0)
      {
        unRunTime = FIP_GetScriptStartTime(yScript);
        nScriptStep = 0;
        nSMStep = FIP_SCRIPT_WAIT1;
      }
      else
      {
        nSMStep = FIP_SCRIPT_START;
        nFIPAbortScript = 0;
      }
      break;
      
    case FIP_SCRIPT_WAIT1:
      if (nFIPAbortScript == 1)
      {
        nSMStep = FIP_SCRIPT_EXEC_END;
      }
      else
      {
        if (get_time() >= unRunTime)
        {
          nSMStep = FIP_SCRIPT_GETCMD;
          unRunTime = get_time();
        }
        else
        {
          nSMStep = FIP_SCRIPT_WAIT1;
        }
      }
      break;
      
    case FIP_SCRIPT_GETCMD:
      if (nScriptStep < FIP_GetScriptCmdCount(yScript))
      {
        yCmdID = FIP_GetCmdID(yScript,nScriptStep);
        if ((yCmdID == 0x0F) || (yCmdID == 0xF0) || (yCmdID == 0xFF))
        {
          nSMStep = FIP_SCRIPT_EXEC_OBC;
        }
        else
        {
          nSMStep = FIP_SCRIPT_EXEC_SU;
        }
      }
      else
      {
        nSMStep = FIP_SCRIPT_EXEC_END;
      }
      break;
      
    case FIP_SCRIPT_EXEC_OBC:
      yCmdID = FIP_GetCmdID(yScript,nScriptStep);
      switch (yCmdID)
      {
        case 0x0F:
          FIP_SetFIPPacketProcEnable(0);
          pwr_ctl(FIPEX,PWR_ON);
          nSMStep = FIP_SCRIPT_POWER_ON1;
          print_uart_msg("FIP:  FIPEX On (%lu)\n",get_time());
          break;
          
        case 0xF0:
          pwr_ctl(FIPEX,PWR_OFF);
          nSMStep = FIP_SCRIPT_EXEC_ONOFF;
          print_uart_msg("FIP:  FIPEX Off (%lu)\n",get_time());
          break;
          
        case 0xFF:
          nSMStep = FIP_SCRIPT_EXEC_END;
          break;
          
        default:
          pwr_ctl(FIPEX,PWR_OFF);
          nSMStep = FIP_SCRIPT_EXEC_END1;
          print_uart_msg("FIP:  Bad OBC Command.  Ending Script.\n");
          break;
      }
      break;
      
    case FIP_SCRIPT_POWER_ON1:
      nSMStep = FIP_SCRIPT_POWER_ON2;
      break;
      
    case FIP_SCRIPT_POWER_ON2:
      nSMStep = FIP_SCRIPT_EXEC_ONOFF;
      FIP_ClearHWFIFO();
      FIP_SetFIPPacketProcEnable(1);  //Turn on packet processing from FIPEX
      break;
      
    case FIP_SCRIPT_EXEC_ONOFF:
      nNakCount = FIP_GetNakCount();  //Just to satisfy check in EXEC_DELAY
      unRunTime += FIP_GetCmdDelay(yScript,nScriptStep);
      nScriptStep++;
      nSMStep = FIP_SCRIPT_EXEC_DELAY;
      break;
      
    case FIP_SCRIPT_EXEC_END1:
      pwr_ctl(FIPEX,PWR_OFF);
      nSMStep = FIP_SCRIPT_EXEC_END;
      break;
  
    case FIP_SCRIPT_EXEC_END:
      if ((FIP_GetScriptRepeatTime(yScript) == 0) || (nFIPAbortScript == 1))
      {
        OP_SetActiveFIPScript(0); //Deactivate
        print_uart_msg("FIP:  Deactivating script %d (%lu)\n",yScript,get_time());
        nSMStep     = FIP_SCRIPT_START;
        nScriptStep = 0;
      }
      else
      {
        unRunTime += FIP_GetScriptRepeatTime(yScript);
        nSMStep = FIP_SCRIPT_WAIT1;
        print_uart_msg("FIP:  Repeat time:%d  Next Run: %lu (%lu)\n",
                         FIP_GetScriptRepeatTime(yScript),
                         unRunTime,
                         get_time());
        nScriptStep = 0;
      }
      break;
      
    case FIP_SCRIPT_EXEC_SU:
      nNakCount = FIP_GetNakCount(); //Get current NAK Count
      FIP_SendScriptCmd(yScript,nScriptStep);
      unRunTime += FIP_GetCmdDelay(yScript,nScriptStep);
      nScriptStep++;
      nSMStep = FIP_SCRIPT_EXEC_DELAY;
      break;
      
    case FIP_SCRIPT_EXEC_DELAY:
      if (FIP_GetNakCount() > nNakCount)
      {
        nSMStep = FIP_SCRIPT_ERROR1;
      }
      else
      {
        nSMStep = FIP_SCRIPT_WAIT1;
      }
      break;
      
    case FIP_SCRIPT_ERROR1:
      FIP_SendNoParmCmd(FIP_HK);
      nSMStep = FIP_SCRIPT_ERROR2;
      break;
      
    case FIP_SCRIPT_ERROR2:
      FIP_SendNoParmCmd(FIP_DP);
      nSMStep = FIP_SCRIPT_ERROR3;
      break;
      
    case FIP_SCRIPT_ERROR3:
      pwr_ctl(FIPEX,PWR_OFF);
      nSMStep = FIP_SCRIPT_ERROR4;
      print_uart_msg("FIP:  FIPEX Off (%lu)\n",get_time());
      break;
      
    case FIP_SCRIPT_ERROR4:
      nSMStep = FIP_SCRIPT_START;
      nScriptStep = 0;
      break;

    default:
      nSMStep = FIP_SCRIPT_EXEC_END;
      break;
  }
}

int FIP_SetNextActive(void)
{
int i;
uint32 unTime = get_time();
int nRC = 0;
  
  if (OP_GetFIPScriptProcEnable())
  {
    for (i=0;i<FIP_MAX_SCRIPTS;i++)
    {
      if (pScriptArray[i].unSync == FIP_SCRIPT_SYNC)
      {           
        if (FIP_GetScriptStartTime(i+1) == unTime)
        {
          if (OP_GetActiveFIPScript() != (i+1))
          {
            print_uart_msg("FIP:  Setting script active: %d (%lu)\n",i+1,get_time());
          }
          
          OP_SetActiveFIPScript(i+1);
          
          nRC = 1;
          break;
        }
      }
    }
  }
  return(nRC);   
}

void FIP_ListScripts(void)
{
int i;
uint8 yActiveScript = OP_GetActiveFIPScript();
char szTag[2];

  for (i=0;i<FIP_MAX_SCRIPTS;i++)
  {
    if ((i+1)==yActiveScript)
    {
      strcpy(szTag,"*");
    }
    else
    {
      strcpy(szTag," ");
    }
    
    if (pScriptArray[i].unSync == FIP_SCRIPT_SYNC)
    {
      print_uart_msg("FIP:  Script %d%s  Start=%08X\n",i+1,szTag,FIP_GetScriptStartTime(i+1));
    }
    else
    {
      print_uart_msg("FIP:  Script %d%s  ---EMPTY---\n",i+1,szTag);
    }
  }
}

void FIP_SetScriptProcEnable(uint8 yEnable)
{
  OP_SetFIPScriptProcEnable(yEnable);
  
  if (yEnable == 0)
  { 
    print_uart_msg("FIP:  Script processing disabled. (%lu)\n",get_time());
    nFIPAbortScript = 1;  //Abort any running script
  }
  else
  {
    print_uart_msg("FIP:  Script processing enabled. (%lu)\n",get_time());
  }
}

uint16 FIP_GetScriptState(void)
{
  return(nSMStep);
}

uint16 FIP_GetScriptStep(void)
{
  return(nScriptStep);
}