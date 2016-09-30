
OUTPUT=../output

$(OUTPUT)/proposal.pdf: proposal.tex grammar/go--/go--.tex
	pdflatex --output-directory ${OUTPUT} proposal.tex 
	rm -f *.aux *.log

clean:
	rm -f *.aux *.log
	
