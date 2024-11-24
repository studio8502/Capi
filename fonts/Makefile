MCUFONT ?= ../bin/mcufont

SRCS := $(shell find . -type f -name "*.ttf")

OUTPUT := $(SRCS:.ttf=.c)

CHARS ?= 0-255

OPTIMIZE_ITERATIONS ?= 50

SIZES ?= 8 10 12 14

.PHONY:
all: fonts.h DejaVu

.PHONY:
install: all
	cp -f *.h ../include/fonts
	cp -f *.inc ../include/fonts

%.c: %.dat
	$(MCUFONT) rlefont_export $<

%.inc: %.c
	mv $< $@

.PHONY:
DejaVu: DejaVuSans.h $(foreach size,$(SIZES),DejaVuSans$(size).inc)

fonts.h: DejaVuSans.h
	printf '#pragma once\n\n' > $@
	printf '$(foreach font,$^,#include "fonts/$(font)"\n)' >> $@

DejaVuSans.h: $(foreach size,$(SIZES),DejaVuSans$(size).inc)
	printf '#pragma once\n\n' > $@
	printf '$(foreach font,$^,#include "fonts/$(font)"\n)' >> $@

DejaVuSans8: DejaVuSans8.inc

DejaVuSans8.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 8
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ $(OPTIMIZE_ITERATIONS)

DejaVuSans10: DejaVuSans10.inc

DejaVuSans10.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 10
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ $(OPTIMIZE_ITERATIONS)

DejaVuSans12: DejaVuSans12.inc

DejaVuSans12.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 12
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ $(OPTIMIZE_ITERATIONS)

DejaVuSans14: DejaVuSans14.inc

DejaVuSans14.dat: DejaVuSans.ttf
	$(MCUFONT) import_ttf $< 14
	$(MCUFONT) filter $@ $(CHARS)
	$(MCUFONT) rlefont_optimize $@ $(OPTIMIZE_ITERATIONS)

.PHONY:
clean:
	find . -type f -name "*.dat" -delete
	find . -type f -name "*.inc" -delete
	find . -type f -name "*.h" -delete

.SUFFIXES: