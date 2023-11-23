#ifndef __IF_H__
#define  __IF_H__



int IF_propagate()
{
    if (branch_instr >= Cycles)
    {
        Stalls[1]++;
        optype[1] = -1;
        return 1;
    }else {
       
        IF_IR = Inst_cache[IF_PC];
        IF_PC++;
        optype[1] = 0;

        return 0;
    }
}

#endif