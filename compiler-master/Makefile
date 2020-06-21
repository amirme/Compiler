all: build_lexyacc calc3.exe

calc3.exe: bin/calc3a.exe bin/calc3b.exe bin/calc3g.exe bin/calc3i.exe

bin/%.exe: lexyacc-code_lab3/%.c build_lexyacc
	gcc -I builds builds/y.tab.o builds/lex.yy.o $< -o $@

build_lexyacc:
	bison -y -d lexyacc-code_lab3/calc3.y -o builds/y.tab.c
	flex -o builds/lex.yy.c lexyacc-code_lab3/calc3.l
	gcc -I lexyacc-code_lab3 -c builds/y.tab.c -o builds/y.tab.o
	gcc -I lexyacc-code_lab3 -c builds/lex.yy.c -o builds/lex.yy.o

clean:
	rm -f -v builds/*
	rm -f -v bin/*
	rm -f -v fact.s
	rm -f -v fact
