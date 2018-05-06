#include "includes.h"

#define DEPLOY0  0
#define DEPLOY1A 1
#define DEPLOY1  2
#define DEPLOY2A 3
#define DEPLOY2  4
#define DEPLOY3A 5
#define DEPLOY3  6
#define DEPLOY4A 7
#define DEPLOY4  8
#define DEPLOY5  9
#define DEPLOY6  10

#define TIME_PER_DEPLOY_STEP 10
#define BURN_TIME            30

uint32 nDeployState = DEPLOY0;
uint32 nDeploySequenceStart;
uint32 nStepStart;

extern CDH_IO_t *cdhio;

void enable_burn_power(uint8 yState)
{
  cdhio->EPS_BURN_PWR = yState;
}

void burn_sp1(uint8 yState)
{
  cdhio->SP1_BURN = yState;
}

void burn_sp2(uint8 yState)
{
  cdhio->SP2_BURN = yState;
}

void burn_sp3(uint8 yState)
{
  cdhio->SP3_BURN = yState;
}

void burn_bd4(uint8 yState)
{
  cdhio->BD4_BURN = yState;
}

void init_deploy(uint32 nStartTime)
{
  nDeploySequenceStart = nStartTime;
  nDeployState = DEPLOY0;
  enable_burn_power(PWR_ON);
  print_uart_msg("Deploy:  Burn Power enabled\n");
}

int run_deploy_sequence(int nAbort)
{
  uint32 nTimeCode;
  int nRC = 0;

  nTimeCode = get_time();

  if (nAbort == 1)
  {
    nDeployState = DEPLOY5;
  }

  switch (nDeployState)
  {
    case DEPLOY0:
      if ((nTimeCode - nDeploySequenceStart) >= TIME_PER_DEPLOY_STEP)
      {
        nDeployState = DEPLOY1A;
      }
      break;

    case DEPLOY1A:
      nDeployState = DEPLOY1;
      burn_bd4(PWR_ON);
      nStepStart = nTimeCode;
      print_uart_msg("Deploy:  Burn BD4\n");
      break;

    case DEPLOY1:
      if ((nTimeCode - nStepStart) >= BURN_TIME)
      {
        nDeployState = DEPLOY2A;
        burn_bd4(PWR_OFF);
        print_uart_msg("\nDeploy:  Burn BD4 complete.\n");
        nStepStart = nTimeCode;
        OP_IncrementDeployCount();
      }
      else
      {
        print_uart_msg(".");
      }
      break;
/*
    case DEPLOY2A:
      if ((nTimeCode - nStepStart) >= TIME_PER_DEPLOY_STEP)
      {
        nDeployState = DEPLOY2;
        burn_sp2(PWR_ON);
        nStepStart = nTimeCode;
        print_uart_msg("Deploy:  Burn SP2\n");
      }
      break;

    case DEPLOY2:
      if ((nTimeCode - nStepStart) >= BURN_TIME)
      {
        nDeployState = DEPLOY3A;
        burn_sp2(PWR_OFF);
        print_uart_msg("\nDeploy:  Burn SP2 complete.\n");
        nStepStart = nTimeCode;
        OP_IncrementDeployCount();
      }
      else
      {
        print_uart_msg(".");
      }
      break;

    case DEPLOY3A:
      if ((nTimeCode - nStepStart) >= TIME_PER_DEPLOY_STEP)
      {
        nDeployState = DEPLOY3;
        burn_sp1(PWR_ON);
        nStepStart = nTimeCode;
        print_uart_msg("Deploy:  Burn SP1\n");
      }
      break;

    case DEPLOY3:
      if ((nTimeCode - nStepStart) >= BURN_TIME)
      {
        nDeployState = DEPLOY4A;
        burn_sp1(PWR_OFF);
        print_uart_msg("\nDeploy:  Burn SP1 complete.\n");
        nStepStart = nTimeCode;
        OP_IncrementDeployCount();
      }
      else
      {
        print_uart_msg(".");
      }
      break;

    case DEPLOY4A:
      if ((nTimeCode - nStepStart) >= TIME_PER_DEPLOY_STEP)
      {
        nDeployState = DEPLOY4;
        burn_sp3(PWR_ON);
        nStepStart = nTimeCode;
        print_uart_msg("Deploy:  Burn SP3\n");
      }
      break;

    case DEPLOY4:
      if ((nTimeCode - nStepStart) >= BURN_TIME)
      {
        nDeployState = DEPLOY5;
        burn_sp3(PWR_OFF);
        print_uart_msg("\nDeploy:  Burn SP3 complete.\n");
        nStepStart = nTimeCode;
        OP_IncrementDeployCount();
      }
      else
      {
        print_uart_msg(".");
      }
      break;
*/
    case DEPLOY5:
      //burn_sp1(PWR_OFF);  //Just to make sure
      //burn_sp2(PWR_OFF);
      //burn_sp3(PWR_OFF);
      //burn_bd4(PWR_OFF);
      enable_burn_power(PWR_OFF);
      nDeployState = DEPLOY6;
      nRC = 1;
      print_uart_msg("Deploy:  Burn Power disabled.\n");
      print_uart_msg("Deploy:  Sequence complete.\n");
      break;

    case DEPLOY6:
      nDeployState = DEPLOY6;
      nRC=1;
      break;

    default:
      nDeployState = DEPLOY6;  //Safe state
      break;
  }

  return(nRC);
}
