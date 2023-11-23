Execution of a program:

First open the terminal ans then change the directory to this folder.

Then the following commands are to be executed on terminal in serial order after giving required inputs.


		cd input
		bash compile.sh arithmetic.asm ICache.txt
		cd ..
		g++ processor.cpp
		./a.out

The above 5 cmds can also be directly executed using Auto.py file.



Inputs 

The Arithmetic.asm should contain the required asm code which is to be executed on the processor.
The DCache.txt and RF.txt should be initialized with the Data_Cache and Register values.


Outputs
The Output file contains the required output files.



