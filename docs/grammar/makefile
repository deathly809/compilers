
all:
	pdflatex go.tex
	pdflatex mine.tex

clean:
	-@rm -fv *.aux *.log *.pdf

nuke: clean
	make -C go-- nuke
