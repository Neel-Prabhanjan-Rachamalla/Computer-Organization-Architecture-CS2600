#ifndef __EX_H__
#define  __EX_H__



int EX_propagate()
{

    EX_OP = ID_OP;
    EX_A = ID_A;
    EX_B = ID_B;
    EX_C = ID_C;

   

  if (EX_OP == ADD)
    {

        //Leaving the Structural stall
            EX_ALU = EX_B + EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
            Fwd_reg[EX_A] = EX_ALU;
           
            return 0;
        
    }else if (EX_OP == SUB)
    {
        
       
           EX_ALU = EX_B - EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
            
            return 0;
       
    }else if (EX_OP == MUL)
    {

       
        EX_ALU = EX_B*EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
           
            return 0;
      

    }else if (EX_OP == INC)
    {
       
        EX_ALU = EX_B + 1;
          optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
            
           return 4;
       
    }else if (EX_OP == AND)
    {
       
          EX_ALU = EX_B & EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
           
            return 0;
        
       
    }else if (EX_OP == OR)
    {
       
         EX_ALU = EX_B |EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
           
            return 0;
        
         
    }else if (EX_OP == NOT)
    {
       
         EX_ALU = (~EX_B)&(255) ;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
            
            return 0;
        
       
    }else if (EX_OP== XOR)
    {
         EX_ALU = EX_B ^ EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
              Fwd_reg[EX_A] = EX_ALU;
           
            return 0;
        
        
        
    }else if (EX_OP == LOAD||EX_OP == STORE)
    {
           
           EX_ALU = EX_B + EX_C;
            optype[2] = -1;
            optype[3] = EX_OP;
           
            return 0;
        
        
    }else if (EX_OP == BEQZ|| EX_OP == JMP)
    {
          
            if (EX_A == 0)
              IF_PC = EX_B;
              optype[3] = EX_OP;
              optype[2] = -1;
              
            return 0;
       
    }else if (EX_OP == HLT)
    {
         optype[2] = -1;
         optype[3] = EX_OP;

         

        return 0;
    }

    return 1; 
    
}


#endif