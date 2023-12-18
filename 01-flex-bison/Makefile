
CC := gcc
FLEX := flex
BISON := bison

objs := spc scanner lex.yy.c parser.tab.c parser.tab.h

spc: lex.yy.c parser.tab.c sp.c
	$(CC) -o $@ $^

scanner: lex.yy.c
	$(CC) -o $@ -DDEBUG_SCANNER $<

lex.yy.c: scanner.l parser.tab.h
	$(FLEX) $<

parser.tab.c parser.tab.h: parser.y
	$(BISON) -H $<

.PHONY: clean
clean:
	rm -rf $(objs)