MCUFONT ?= ../bin/mcufont

SRCS := $(shell find . -type f -name "*.bdf")

OUTPUT := $(SRCS:.bdf=.c)

CHARS ?= 0-255

OPTIMIZE_ITERATIONS ?= 10

SIZES ?= 8 10 12 14 18 24

.PHONY:
all: fonts.h
	@find . -type f -name "*.dat" -delete

fonts.h: Helvetica.h 
	@printf '#pragma once\n\n' > $@
	@printf '#include "mcufont.h"\n\n' > $@
	@printf '$(foreach font,$^,#include "fonts/$(font)"\n\n)' >> $@

Courier.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Courier/Courier-$$S.bdf; \
		$(MCUFONT) filter Courier/Courier-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Courier/Courier-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Courier/Courier-$$S.dat Courier-$$S.inc; \
		printf "#include \"fonts/Courier/Courier-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Courier/CourierBold-$$S.bdf; \
		$(MCUFONT) filter Courier/CourierBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Courier/CourierBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Courier/CourierBold-$$S.dat CourierBold-$$S.inc; \
		printf "#include \"fonts/Courier/CourierBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Courier/CourierBoldItalic-$$S.bdf; \
		$(MCUFONT) filter Courier/CourierBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Courier/CourierBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Courier/CourierBoldItalic-$$S.dat CourierBoldItalic-$$S.inc; \
		printf "#include \"fonts/Courier/CourierBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Courier/CourierItalic-$$S.bdf; \
		$(MCUFONT) filter Courier/CourierItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Courier/CourierItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Courier/CourierItalic-$$S.dat CourierItalic-$$S.inc; \
		printf "#include \"fonts/Courier/CourierItalic-$$S.inc\"\n" >> $@; \
	done

Helvetica.h:
	@printf '#pragma once\n\n' > $@
	for S in 8 ; do \
		$(MCUFONT) import_bdf Helvetica/HelveticaBoldItalic-$$S.bdf; \
		$(MCUFONT) filter Helvetica/HelveticaBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Helvetica/HelveticaBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Helvetica/HelveticaBoldItalic-$$S.dat HelveticaBoldItalic-$$S.inc; \
		printf "#include \"fonts/Helvetica/HelveticaBoldItalic-$$S.inc\"\n" >> $@; \
	done

Helvetica_S:
	for S in $(SIZES) ; do \
		$(MCUFONT) import_bdf Helvetica/Helvetica-$$S.bdf; \
		$(MCUFONT) filter Helvetica/Helvetica-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Helvetica/Helvetica-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Helvetica/Helvetica-$$S.dat Helvetica-$$S.inc; \
		printf "#include \"fonts/Helvetica/Helvetica-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES) ; do \
		$(MCUFONT) import_bdf Helvetica/HelveticaBold-$$S.bdf; \
		$(MCUFONT) filter Helvetica/HelveticaBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Helvetica/HelveticaBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Helvetica/HelveticaBold-$$S.dat HelveticaBold-$$S.inc; \
		printf "#include \"fonts/Helvetica/HelveticaBold-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES) ; do \
		$(MCUFONT) import_bdf Helvetica/HelveticaItalic-$$S.bdf; \
		$(MCUFONT) filter Helvetica/HelveticaItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Helvetica/HelveticaItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Helvetica/HelveticaItalic-$$S.dat HelveticaItalic-$$S.inc; \
		printf "#include \"fonts/Helvetica/HelveticaItalic-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES) ; do \
		$(MCUFONT) import_bdf Helvetica/HelveticaBoldItalic-$$S.bdf; \
		$(MCUFONT) filter Helvetica/HelveticaBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Helvetica/HelveticaBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Helvetica/HelveticaBoldItalic-$$S.dat HelveticaBoldItalic-$$S.inc; \
		printf "#include \"fonts/Helvetica/HelveticaBoldItalic-$$S.inc\"\n" >> $@; \
	done

Lucida.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Lucida/Lucida-$$S.bdf; \
		$(MCUFONT) filter Lucida/Lucida-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Lucida/Lucida-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Lucida/Lucida-$$S.dat Lucida-$$S.inc; \
		printf "#include \"fonts/Lucida/Lucida-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Lucida/LucidaBold-$$S.bdf; \
		$(MCUFONT) filter Lucida/LucidaBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Lucida/LucidaBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Lucida/LucidaBold-$$S.dat LucidaBold-$$S.inc; \
		printf "#include \"fonts/Lucida/LucidaBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Lucida/LucidaBoldItalic-$$S.bdf; \
		$(MCUFONT) filter Lucida/LucidaBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Lucida/LucidaBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Lucida/LucidaBoldItalic-$$S.dat LucidaBoldItalic-$$S.inc; \
		printf "#include \"fonts/Lucida/LucidaBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Lucida/LucidaItalic-$$S.bdf; \
		$(MCUFONT) filter Lucida/LucidaItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Lucida/LucidaItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Lucida/LucidaItalic-$$S.dat LucidaItalic-$$S.inc; \
		printf "#include \"fonts/Lucida/LucidaItalic-$$S.inc\"\n" >> $@; \
	done

LucidaBright.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaBright/LucidaBright-$$S.bdf; \
		$(MCUFONT) filter LucidaBright/LucidaBright-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaBright/LucidaBright-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaBright/LucidaBright-$$S.dat LucidaBright-$$S.inc; \
		printf "#include \"fonts/LucidaBright/LucidaBright-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaBright/LucidaBrightBold-$$S.bdf; \
		$(MCUFONT) filter LucidaBright/LucidaBrightBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaBright/LucidaBrightBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaBright/LucidaBrightBold-$$S.dat LucidaBrightBold-$$S.inc; \
		printf "#include \"fonts/LucidaBright/LucidaBrightBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaBright/LucidaBrightBoldItalic-$$S.bdf; \
		$(MCUFONT) filter LucidaBright/LucidaBrightBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaBright/LucidaBrightBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaBright/LucidaBrightBoldItalic-$$S.dat LucidaBrightBoldItalic-$$S.inc; \
		printf "#include \"fonts/LucidaBright/LucidaBrightBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaBright/LucidaBrightItalic-$$S.bdf; \
		$(MCUFONT) filter LucidaBright/LucidaBrightItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaBright/LucidaBrightItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaBright/LucidaBrightItalic-$$S.dat LucidaBrightItalic-$$S.inc; \
		printf "#include \"fonts/LucidaBright/LucidaBrightItalic-$$S.inc\"\n" >> $@; \
	done

LucidaTypewriter.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaTypewriter/LucidaTypewriter-$$S.bdf; \
		$(MCUFONT) filter LucidaTypewriter/LucidaTypewriter-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaTypewriter/LucidaTypewriter-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaTypewriter/LucidaTypewriter-$$S.dat LucidaTypewriter-$$S.inc; \
		printf "#include \"fonts/LucidaTypewriter/LucidaTypewriter-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf LucidaTypewriter/LucidaTypewriterBold-$$S.bdf; \
		$(MCUFONT) filter LucidaTypewriter/LucidaTypewriterBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize LucidaTypewriter/LucidaTypewriterBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export LucidaTypewriter/LucidaTypewriterBold-$$S.dat LucidaTypewriterBold-$$S.inc; \
		printf "#include \"fonts/LucidaTypewriter/LucidaTypewriterBold-$$S.inc\"\n" >> $@; \
	done

NewCenturySchoolbook.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf NewCenturySchoolbook/NewCenturySchoolbook-$$S.bdf; \
		$(MCUFONT) filter NewCenturySchoolbook/NewCenturySchoolbook-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize NewCenturySchoolbook/NewCenturySchoolbook-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export NewCenturySchoolbook/NewCenturySchoolbook-$$S.dat NewCenturySchoolbook-$$S.inc; \
		printf "#include \"fonts/NewCenturySchoolbook/NewCenturySchoolbook-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf NewCenturySchoolbook/NewCenturySchoolbookBold-$$S.bdf; \
		$(MCUFONT) filter NewCenturySchoolbook/NewCenturySchoolbookBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize NewCenturySchoolbook/NewCenturySchoolbookBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export NewCenturySchoolbook/NewCenturySchoolbookBold-$$S.dat NewCenturySchoolbookBold-$$S.inc; \
		printf "#include \"fonts/NewCenturySchoolbook/NewCenturySchoolbookBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf NewCenturySchoolbook/NewCenturySchoolbookBoldItalic-$$S.bdf; \
		$(MCUFONT) filter NewCenturySchoolbook/NewCenturySchoolbookBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize NewCenturySchoolbook/NewCenturySchoolbookBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export NewCenturySchoolbook/NewCenturySchoolbookBoldItalic-$$S.dat NewCenturySchoolbookBoldItalic-$$S.inc; \
		printf "#include \"fonts/NewCenturySchoolbook/NewCenturySchoolbookBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf NewCenturySchoolbook/NewCenturySchoolbookItalic-$$S.bdf; \
		$(MCUFONT) filter NewCenturySchoolbook/NewCenturySchoolbookItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize NewCenturySchoolbook/NewCenturySchoolbookItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export NewCenturySchoolbook/NewCenturySchoolbookItalic-$$S.dat NewCenturySchoolbookItalic-$$S.inc; \
		printf "#include \"fonts/NewCenturySchoolbook/NewCenturySchoolbookItalic-$$S.inc\"\n" >> $@; \
	done

Terminus.h:
	@printf '#pragma once\n\n' > $@
	for S in 12 14 18 24; do \
		$(MCUFONT) import_bdf Terminus/Terminus-$$S.bdf; \
		$(MCUFONT) filter Terminus/Terminus-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Terminus/Terminus-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Terminus/Terminus-$$S.dat Terminus-$$S.inc; \
		printf "#include \"fonts/Terminus/Terminus-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in 12 14 18 24; do \
		$(MCUFONT) import_bdf Terminus/TerminusBold-$$S.bdf; \
		$(MCUFONT) filter Terminus/TerminusBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Terminus/TerminusBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Terminus/TerminusBold-$$S.dat TerminusBold-$$S.inc; \
		printf "#include \"fonts/Terminus/TerminusBold-$$S.inc\"\n" >> $@; \
	done

Times.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Times/Times-$$S.bdf; \
		$(MCUFONT) filter Times/Times-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Times/Times-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Times/Times-$$S.dat Times-$$S.inc; \
		printf "#include \"fonts/Times/Times-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Times/TimesBold-$$S.bdf; \
		$(MCUFONT) filter Times/TimesBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Times/TimesBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Times/TimesBold-$$S.dat TimesBold-$$S.inc; \
		printf "#include \"fonts/Times/TimesBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Times/TimesBoldItalic-$$S.bdf; \
		$(MCUFONT) filter Times/TimesBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Times/TimesBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Times/TimesBoldItalic-$$S.dat TimesBoldItalic-$$S.inc; \
		printf "#include \"fonts/Times/TimesBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf Times/TimesItalic-$$S.bdf; \
		$(MCUFONT) filter Times/TimesItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Times/TimesItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Times/TimesItalic-$$S.dat TimesItalic-$$S.inc; \
		printf "#include \"fonts/Times/TimesItalic-$$S.inc\"\n" >> $@; \
	done

Utopia.h:
	@printf '#pragma once\n\n' > $@
	for S in 10 12 15 19 25; do \
		$(MCUFONT) import_bdf Utopia/Utopia-$$S.bdf; \
		$(MCUFONT) filter Utopia/Utopia-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Utopia/Utopia-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Utopia/Utopia-$$S.dat Utopia-$$S.inc; \
		printf "#include \"fonts/Utopia/Utopia-$$S.inc\"\n" >> $@; \
	done
	for S in 10 12 15 19 25; do \
		$(MCUFONT) import_bdf Utopia/UtopiaItalic-$$S.bdf; \
		$(MCUFONT) filter Utopia/UtopiaItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize Utopia/UtopiaItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export Utopia/UtopiaItalic-$$S.dat UtopiaItalic-$$S.inc; \
		printf "#include \"fonts/Utopia/UtopiaItalic-$$S.inc\"\n" >> $@; \
	done

OpenDyslexic.h:
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf OpenDyslexic/OpenDyslexic-$$S.bdf; \
		$(MCUFONT) filter OpenDyslexic/OpenDyslexic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize OpenDyslexic/OpenDyslexic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export OpenDyslexic/OpenDyslexic-$$S.dat OpenDyslexic-$$S.inc; \
		printf "#include \"fonts/OpenDyslexic/OpenDyslexic-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf OpenDyslexic/OpenDyslexicBold-$$S.bdf; \
		$(MCUFONT) filter OpenDyslexic/OpenDyslexicBold-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize OpenDyslexic/OpenDyslexicBold-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export OpenDyslexic/OpenDyslexicBold-$$S.dat OpenDyslexicBold-$$S.inc; \
		printf "#include \"fonts/OpenDyslexic/OpenDyslexicBold-$$S.inc\"\n" >> $@; \
	done
	@printf '#pragma once\n\n' > $@
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf OpenDyslexic/OpenDyslexicBoldItalic-$$S.bdf; \
		$(MCUFONT) filter OpenDyslexic/OpenDyslexicBoldItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize OpenDyslexic/OpenDyslexicBoldItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export OpenDyslexic/OpenDyslexicBoldItalic-$$S.dat OpenDyslexicBoldItalic-$$S.inc; \
		printf "#include \"fonts/OpenDyslexic/OpenDyslexicBoldItalic-$$S.inc\"\n" >> $@; \
	done
	for S in $(SIZES); do \
		$(MCUFONT) import_bdf OpenDyslexic/OpenDyslexicItalic-$$S.bdf; \
		$(MCUFONT) filter OpenDyslexic/OpenDyslexicItalic-$$S.dat $(CHARS); \
		$(MCUFONT) rlefont_optimize OpenDyslexic/OpenDyslexicItalic-$$S.dat $(OPTIMIZE_ITERATIONS); \
		$(MCUFONT) rlefont_export OpenDyslexic/OpenDyslexicItalic-$$S.dat OpenDyslexicItalic-$$S.inc; \
		printf "#include \"fonts/OpenDyslexic/OpenDyslexicItalic-$$S.inc\"\n" >> $@; \
	done

	
.PHONY:
clean:
	@find . -type f -name "*.dat" -delete
	@find . -type f -name "*.inc" -delete
	@find . -type f -name "*.h" -delete

.SUFFIXES: