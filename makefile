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

$(TESTCASE_DIR)/%.output: $(TESTCASE_DIR)/%.fmj a.out check.out
	@./a.out < $(word 1,$^) > $@
	@./check.out $(word 1,$^) $@
	@rm -rf $@

check.out:
	@ g++ check.cpp -o check.out

a.out: main.o lex.yy.o y.tab.o fdmjast.o util.o printast.o
	@cc -g main.o lex.yy.o y.tab.o fdmjast.o util.o printast.o -o a.out

main.o: main.c fdmjast.h fdmjast.c util.h util.c printast.h printast.c y.tab.h y.tab.c lex.yy.o y.tab.o main.c main.o fdmjast.o util.o printast.o
	@cc -g -c main.c -o main.o

lex.yy.c: lexer.lex y.tab.h y.tab.c
	@lex lexer.lex
	
y.tab.c: parser.yacc fdmjast.h 
	@yacc -d parser.yacc
	
y.tab.h: parser.yacc
	@yacc -d parser.yacc

fdmjast.o: fdmjast.c fdmjast.h util.h
	@cc -g -c fdmjast.c

util.o: util.c util.h
	@cc -g -c util.c

lex.yy.o: lex.yy.c y.tab.h
	@cc -g -c lex.yy.c

y.tab.o: y.tab.c
	@cc -g -c y.tab.c

printast.o: printast.c fdmjast.h util.h 
	@cc -g -c printast.c

y.output:
	yacc -v parser.yacc

clean: 
	@rm -f a.out b.out lex.yy.o lex.yy.c y.tab.o y.tab.c y.tab.h util.o fdmjast.o complier.o interpreter.o main.ll out.ll lib.ll printast.o y.output main.o check.out





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