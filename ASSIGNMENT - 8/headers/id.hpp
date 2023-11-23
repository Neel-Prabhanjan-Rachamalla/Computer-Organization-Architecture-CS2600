#ifndef __ID_H__
#define  __ID_H__


int ID_propagate()
{
    ID_IR = IF_IR;
   
    ID_C = ID_IR&(15);
    ID_IR >>= 4;
    ID_B = ID_IR&(15);
    ID_IR>>=4;
    ID_A = ID_IR&(15);
    ID_IR >>=4;
    ID_OP = ID_IR;
    

    int cat = Instruction_Category(ID_OP);
    

    if (ID_OP == ADD|| ID_OP == SUB || ID_OP == MUL || ID_OP == AND || ID_OP == OR || ID_OP == XOR)
    {
        if (write_reg_cycle[ID_B] >= Cycles||write_reg_cycle[ID_C] >= Cycles)
        { 
            //optype[2] = 0;
            Stalls[0]++;
            return 1;
        }else {
            write_reg_cycle[ID_A] = Cycles + 1 ; 
            ID_B = Fwd_reg[ID_B];
            ID_C = Fwd_reg[ID_C];
            optype[2] = ID_OP; 
            optype[1] = -1;
            Instru[cat]++;
            prev_OP = ID_OP;
            return 0;
        }
    }else if (ID_OP == INC)
    {
       if (write_reg_cycle[ID_A] >= Cycles)
       {
          // optype[2] = 0;
           Stalls[0]++;
           return 1;
       }else {
            write_reg_cycle[ID_A] = Cycles + 1 ; 
           ID_B = Fwd_reg[ID_B];
           ID_C = 1;
           optype[2] = ID_OP;
           optype[1] = -1;
           Instru[cat]++;
            prev_OP = ID_OP;
           return 0;
       } 
    }else if (ID_OP == NOT)
    {
          if (write_reg_cycle[ID_B] >= Cycles)
        {
            Stalls[0]++;
            return 1;
        }else {
            write_reg_cycle[ID_B] = Cycles + 1 ;
           
            ID_B = Fwd_reg[ID_B];
            optype[2] = ID_OP;
            optype[1] = -1;
            Instru[cat]++;
            prev_OP = ID_OP;
            return 0;
        }
    }else if (ID_OP == LOAD)
    {
         if (write_reg_cycle[ID_B] >= Cycles)
        {
            Stalls[0]++;
            return 1;
        }else {
            write_reg_cycle[ID_A] = Cycles + 2 ;
            ID_B = Fwd_reg[ID_B];
            optype[2] = ID_OP;
            optype[1] = -1;
            Instru[cat]++;
            prev_OP = ID_OP;
            return 0;
        }  
    }else if (ID_OP == STORE)
    {
        if (write_reg_cycle[ID_B] >= Cycles ||write_reg_cycle[ID_A] >= Cycles)
        {
            Stalls[0]++;
            return 1;
        }else {
           
           ID_A = Fwd_reg[ID_A];
           ID_B = Fwd_reg[ID_B];
           optype[2] = ID_OP;
           optype[1] = -1;
           Instru[cat]++;
           prev_OP = ID_OP;
           
            return 0;
        }   
    }else if (ID_OP == JMP)
    {
        branch_instr = Cycles + 1;
       
        ID_B = (ID_A << 4) + ID_B ;
        ID_B = IF_PC + ID_B;
         ID_A = 0;
        optype[2] = ID_OP;
           optype[1] = -1;
           Instru[cat]++;
           prev_OP = ID_OP;
         
        return 0;
        
    }else if (ID_OP == BEQZ)
    {
        if (write_reg_cycle[ID_A] >= Cycles)
        {
            Stalls[0]++;
            return 1;
        }else {
            branch_instr = Cycles + 1;
            ID_A = Fwd_reg[ID_A];
            ID_B = (ID_B << 4) ;
            ID_B += ID_C;
            ID_B = IF_PC + ID_B;
           optype[2] = ID_OP;
           optype[1] = -1;
           Instru[cat]++;
           prev_OP = ID_OP;
            return 0;
        }
    }else if (ID_OP == HLT)
    {
        optype[0] = -1;
        optype[1] = -1;
        optype[2] = ID_OP;
        Instru[cat]++;
        prev_OP = ID_OP;
        
        return 0;
    }


    return 1;

}


#endif