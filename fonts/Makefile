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

fonts.h: NotoSans.h NotoSansMono.h NotoSerif.h
	@printf '#pragma once\n\n' > $@
	@printf '#include "mcufont.h"\n\n' > $@
	@printf '$(foreach font,$^,#include "fonts/$(font)"\n\n)' >> $@

NotoSans.h:
	@printf '#pragma once\n\n' > $@
	@for F in $(foreach style,Regular Bold BoldItalic Italic,NotoSans-$(style) ); do \
		for S in 8 10 12 16; do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> $@; \
		done \
	done
	@for F in $(foreach style,Regular Bold BoldItalic Italic,NotoSansDisplay-$(style) ); do \
		for S in 20 32 48; do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> $@; \
		done \
	done

NotoSerif.h:
	@printf '#pragma once\n\n' > $@
	@for F in $(foreach style,Regular Bold BoldItalic Italic,NotoSerif-$(style) ); do \
		for S in 8 10 12 16; do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> $@; \
		done \
	done
	@for F in $(foreach style,Regular Bold BoldItalic Italic,NotoSerifDisplay-$(style) ); do \
		for S in 20 32 48; do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> $@; \
		done \
	done

NotoSansMono.h:
	@printf '#pragma once\n\n' > $@
	@for F in $(foreach style,Regular Bold,NotoSansMono-$(style) ); do \
		for S in $(SIZES); do \
			$(MCUFONT) import_ttf $$F.ttf $$S; \
			$(MCUFONT) filter $$F$$S.dat $(CHARS); \
			$(MCUFONT) rlefont_optimize $$F$$S.dat $(OPTIMIZE_ITERATIONS); \
			$(MCUFONT) rlefont_export $$F$$S.dat $$F$$S.inc; \
			printf "#include \"fonts/$$F$$S.inc\"\n" >> $@; \
		done \
	done

.PHONY:
clean:
	@find . -type f -name "*.dat" -delete
	@find . -type f -name "*.inc" -delete
	@find . -type f -name "*.h" -delete

.SUFFIXES: