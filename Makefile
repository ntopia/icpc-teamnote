.PHONY: all clean

all: teamnote.pdf

SOURCE_TEX=teamnote.tex
SOURCE_CPPS=$(shell find 'src' -name '*.cpp')

teamnote.pdf: $(SOURCE_TEX) $(SOURCE_CPPS)
	xelatex --shell-escape $(SOURCE_TEX)
	xelatex --shell-escape $(SOURCE_TEX)

clean:
	rm -rf teamnote.pdf *.log *.aux *.pyg *.toc
