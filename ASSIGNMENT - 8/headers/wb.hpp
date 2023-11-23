#ifndef __WB_H__
#define  __WB_H__



int WB_propagate()
{
     WB_LMD = MEM_LMD;
     WB_A = MEM_A;

   
       
     if (optype[4] != STORE && optype[4] != JMP && optype[4] != BEQZ)
               reg[WB_A] = WB_LMD;

     optype[4] = -1;

     return 0;
}
#endif