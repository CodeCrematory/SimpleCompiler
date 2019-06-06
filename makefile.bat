win_flex compiler.l
win_bison -d compiler.y
g++ -std=c++11 -o MYCOMPILE tree.cpp draw.cpp table.cpp lex.yy.c Compiler.tab.c interRepre.cpp

MYCOMPILE.exe testCode.txt