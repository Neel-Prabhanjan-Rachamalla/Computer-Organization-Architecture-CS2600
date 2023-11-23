#include <bits/stdc++.h>
using namespace std;

//All propagate functions return 0 if successful else 0
//If a Buffer register is used by previous pipeline stage, then it need to be called;

int write_reg_cycle[16]; //Contains the cycle from which the corresponding reg is free.
int branch_instr;//   zero if no pending branch instruction else 1

int optype[5];   //-1 if no instruction pending to be instruction else the instruction type

enum Opcode{ADD,SUB,MUL,INC,AND,OR,NOT,XOR,LOAD,STORE,JMP,BEQZ,HLT = 15};
enum Instr_type{ARITH,LOGIC,DAT,CONTR,HALT};
enum Stall_type{DATA,CONTROL};


unsigned short int reg[18],Fwd_reg[18];  //8 bit 16 registers
unsigned short int Inst_cache[130]; // 2Byte 128 locations
unsigned short int Data_cache[259];      //1Byte 256 locations of data cache


long long Instru[5];
long long Stalls[3];
long long Cycles;


int IF_IR,IF_PC;

int ID_IR;
int ID_OP,ID_A,ID_B,ID_C;
int prev_OP = -1;


int EX_ALU;
signed char EX_OP,EX_A, EX_B,EX_C;
 
int MEM_ALU,MEM_A,MEM_LMD;


int WB_LMD,WB_A;


int Instruction_Category(int a)
{
    if (0<= a && a < 4)
     return 0;
    else if (4 <= a && a < 8)
     return 1;
    else if (8 <= a && a < 10)
     return 2;
    else if (10 <= a && a < 12)
     return 3;
    else if (a == 15)
    {
        return 4;
    }
    return -1;
}

#include "headers/wb.hpp"
#include "headers/mem.hpp"
#include "headers/ex.hpp"
#include "headers/if.hpp"
#include "headers/id.hpp"

bool check()   //True if program execution is done else false 
{
   

    int i = 0;

    

    while (i < 5 && optype[i] == -1)
       i++;


   return (i != 5);
}

int hextodec(char a)   //converts hex to decimal
{
    if ('0' <= a && '9' >= a)
    {
        return a -'0';
    }else {
        return a - 'a' + 10;
    }
}

void init_processor()
{
    fstream fp;
    fp.open("input/RF.txt");

    string line,line2;
    int i = 0;
   
    while (fp)
    {
           getline(fp,line);
          //  cout << line[0] << " " << line[1] <<"\n";
           reg[i] = hextodec(line[1])+ hextodec(line[0]) * 16;
           Fwd_reg[i] = reg[i];
        //cout << i << " " <<reg[i] <<"\n";
            i++;
    }

    fp.close();

    fp.open("input/ICache.txt");
    i = 0;
   
    while (fp)
    {
        getline(fp,line);
        getline(fp,line2);

        Inst_cache[i] = (hextodec(line[0]) << 4) + hextodec(line[1]);
        int y = (hextodec(line2[0]) << 4) + hextodec(line2[1]);

         //cout <<i << " " << Inst_cache[i] << " "<<y << "\n";
        Inst_cache[i] = (Inst_cache[i] <<8) + y;
       

       
        i++;
    }

    fp.close();


    fp.open("input/DCache.txt");
    i = 0;
     
   
    while (fp)
    {
        getline(fp,line);
        
        Data_cache[i] = hextodec(line[1]) + hextodec(line[0])*16;
        
       //cout <<i << " " << Data_cache[i] << "\n";
        i++;

    } 
    fp.close();


   

    memset(Instru,0,sizeof Instru);
    memset(Stalls,0,sizeof Stalls);

    for (int i = 1;i < 5;i++)
     optype[i] = -1;

    optype[0] = 0;
    
    IF_PC = 0;
    Cycles = 0;

    memset(write_reg_cycle,0, sizeof (write_reg_cycle));
    branch_instr = 0;

   

}
char dectohex(int a)
{
    if (0 <= a && a  < 10){
        char f = '0' + a;
     return f;
    }else if (a >= 10){
        char f =  'a'+ a - 10;
        return f;
    }

    return '0';
}
void print_stat()
{
    ofstream fp;

    fp.open("output/ODCache.txt",ios::out);

    int i;
    for (i = 0;i < 256;i++)
    {
        int h = Data_cache[i] &(15);
        int k = (Data_cache[i] >> 4);
        k = k&15;

        char t = dectohex(k);
        string line = "";
        line = line + t;

        t = dectohex(h);
        line = line + t;

        fp << line << "\n";


    }

    fp.close();

    fp.open("output/Output.txt",ios::out);
    
    long long sum = 0;

    for (int i = 0;i < 5;i++)
    {
        sum += Instru[i];
    }
    fp << "Total numbers of instructions executed: "<<sum << "\n";
    fp << "Number of instructions in each class    "<< "\n";
    fp << "Arithmetic instructions               : "<<Instru[0] << "\n";
    fp << "Logical instructions                  : "<<Instru[1] << "\n";
    fp << "Data instructions                     : "<<Instru[2] << "\n";
    fp << "Control instructions                  : "<<Instru[3] << "\n";
    fp << "Halt instructions                     : "<<Instru[4] << "\n";
    fp << "Cycles Per Instruction                : "<< (float)(Cycles )/sum << "\n";
    fp << "Total number of stalls                : "<< Stalls[0] + Stalls[1] << "\n";
    fp << "Data stalls (RAW)                     : "<< Stalls[0] << "\n";
    fp << "Control stalls                        : "<< Stalls[1] << "\n";


    fp.close();
}

int main()
{
    init_processor();


    while (check())
    {
        Cycles++;
        

        if (optype[4] != -1)
        {
            int h  = WB_propagate();

            if (h )
             continue;
        }

        if (optype[3] != -1)
        {
            int h  = MEM_propagate();

            if (h )
             continue;
        }

        if (optype[2] != -1)
        {
             int h  = EX_propagate();

            if (h )
             continue;
        }

        if (optype[1] != -1)
        {
            int h = ID_propagate();

            if (h)
             continue;
        }


        if (optype[0] != -1)
        {
            int h = IF_propagate();

            if (h)
             continue;
        }

       

    }


    print_stat();
}
