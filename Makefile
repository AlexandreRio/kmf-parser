CONTIKI_PROJECT = kmf-parser
CONTIKI_SOURCEFILES += kmf-parser.c \
		       kmf-lexer.c

all: $(CONTIKI_PROJECT)

CONTIKI = $(HOME)/IRISA/contiki/
include $(CONTIKI)/Makefile.include
