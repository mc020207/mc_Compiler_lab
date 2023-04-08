TESTCASE_DIR := tests
TESTCASES = $(wildcard $(TESTCASE_DIR)/*.fmj)
EXEUTABLES = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.o,$(TESTCASES))
MAINFILES = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.o,$(TESTCASES))
EXPECTS = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.exp,$(TESTCASES))
OUTS = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.out,$(TESTCASES))
OUTPUTS = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.output,$(TESTCASES))
LLFILES = $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.ll,$(TESTCASES))

.SECONDARY: $(LLFILES)
runcomp: $(patsubst $(TESTCASE_DIR)/%.fmj,$(TESTCASE_DIR)/%.output,$(TESTCASES)) clean

$(TESTCASE_DIR)/%.output: $(TESTCASE_DIR)/%.fmj a.out
	@echo test $*
	@./a.out < $(word 1,$^) >$@

a.out: main.o lex.yy.o y.tab.o fdmjast.o util.o printast.o table.o types.o symbol.o typecheck.o pr_tree_readable.o treep.o temp.o ast2treep.o
	@cc -g $^ -o a.out

main.o: main.c fdmjast.h fdmjast.c util.h util.c printast.h printast.c y.tab.h y.tab.c lex.yy.o y.tab.o main.c main.o fdmjast.o util.o printast.o table.o types.o symbol.o typecheck.o pr_tree_readable.o treep.o temp.o 
	@cc -g -c main.c -o main.o

lex.yy.c: lexer.lex y.tab.h y.tab.c
	@lex lexer.lex
	
y.tab.c: parser.yacc fdmjast.h 
	@yacc -d parser.yacc
	
y.tab.h: parser.yacc
	@yacc -d parser.yacc

fdmjast.o: fdmjast.c fdmjast.h util.h
	@cc -g -c fdmjast.c

types.o: types.c

table.o: table.c
	gcc -c -w -o table.o table.c

symbol.o: symbol.c

util.o: util.c util.h
	@cc -g -c util.c

typecheck.o: typecheck.c typecheck.h
	@cc -g -c typecheck.c

ast2treep.o: ast2treep.c ast2treep.h
	@cc -g -c ast2treep.c

lex.yy.o: lex.yy.c y.tab.h
	@cc -g -c lex.yy.c

y.tab.o: y.tab.c
	@cc -g -c y.tab.c

printast.o: printast.c fdmjast.h util.h 
	@cc -g -c printast.c

pr_tree_readable.o: pr_tree_readable.c

temp.o: temp.c temp.h

treep.o: treep.c treep.h

y.output:
	yacc -v parser.yacc

clean: 
	@rm -f a.out b.out ./*.o lex.yy.c y.tab.c y.tab.h

clean2:
	@rm -f ./tests/*.output



# mytest: cleanall
# 	@g++ rd.cpp -o rd
# 	@./rd >mktest.c
# 	@./rd >mktest.c
# 	@gcc mktest.c -o mktest
# 	@./mktest
# 	@make runint2 >b.txt
# 	@make runcomp2 >a.txt
# 	@g++ d.cpp -o d
# 	@./d >d.txt

# runcomp2: clean lib.ll main.ll
# 	@llvm-link main.ll lib.ll -S -o out.ll
# 	@lli out.ll

# runint2: clean lib.ll b.out
# 	@./b.out < fdmjast_source.txt

# main.ll: a.out
# 	@./a.out main.ll <fdmjast_source.txt

# a.out: lex.yy.o y.tab.o main.c main.o fdmjast.o util.o printast.o
# 	@cc -g main.o fdmjast.o util.o y.tab.o lex.yy.o printast.o -ll

# b.out: lex.yy.o y.tab.o interpreter.c interpreter.o fdmjast.o util.o printast.o
# 	@cc -g interpreter.o fdmjast.o util.o y.tab.o lex.yy.o printast.o -ll -o b.out