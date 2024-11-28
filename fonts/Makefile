MCUFONT ?= ../bin/mcufont

SRCS := $(shell find . -type f -name "*.ttf")

OUTPUT := $(SRCS:.ttf=.c)

CHARS ?= 0-255

OPTIMIZE_ITERATIONS ?= 25

SIZES ?= 8 10 12 16 20 32 48

.PHONY:
all: fonts.h
	@find . -type f -name "*.dat" -delete

.PHONY:
install: all
	@cp -f *.h ../include/fonts
	@cp -f *.inc ../include/fonts

fonts.h: Lexend.h
	@printf '#pragma once\n\n' > $@
	@printf '$(foreach font,$^,#include "fonts/$(font)"\n)' >> $@

Lexend.h:
	@printf '#pragma once\n\n' > Lato.h
	@for F in $(foreach style,Regular Bold,Lexend-$(style) ); do \
		for S in $(SIZES); do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat; \
			mv $$F$$S.c $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> Lato.h; \
		done \
	done


.PHONY:
clean:
	@find . -type f -name "*.dat" -delete
	@find . -type f -name "*.inc" -delete
	@find . -type f -name "*.h" -delete

.SUFFIXES: