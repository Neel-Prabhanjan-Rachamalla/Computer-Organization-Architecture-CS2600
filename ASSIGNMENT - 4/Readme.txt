CacheBlock.c file is used for find Block length of Cache L1 

CacheAssoc.c file is used to find associativity of Cache L1.


No of Sets in Cache L1 is given to be 64.



By isolating cpu core with isolcpus , and cpu pinning with task set, we can run this code 
in linux environment. But, I have found out that cphJudge in Visual Studio Code gave the 
most precise and optimum result.

Hence, I strongly suggest my code to be run in cphJudge extension in Visual Studio Code. 
In that case, compiling instructions are create an empty testcase and click run all,
Nothing else is required.