#ifndef __MEM_H__
#define  __MEM_H__


int MEM_propagate()
{
    MEM_ALU = EX_ALU;
    MEM_A = EX_A;


    if (optype[3] == LOAD)
    {
         MEM_LMD = Data_cache[MEM_ALU];
           Fwd_reg[EX_A] = MEM_LMD;
         optype[4] = optype[3];
         optype[3] = -1;
         return 0;
    }else if (optype[3] == STORE)
    {
       
        Data_cache[MEM_ALU] = MEM_A;
        optype[3] = -1;
        return 0;
        
    }else if (optype[3] == HLT)
    {
        optype[4] = optype[3];
        optype[3] = -1;
        return 0;
    }else {
        MEM_LMD = MEM_ALU;
        optype[4] = optype[3];
        optype[3] = -1;
        return 0;
    }
    return 1;
}

#endif