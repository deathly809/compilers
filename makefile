
.PHONY: docs
.PHONY: flexingBison 
.PHONY: top-down

all: flexingBison docs top-down

flexingBison:
	make -C flexingBison

top-down:
	make -C top-down

docs:
	cd docs && ${MAKE}

nuke:
	make -C flexingBison nuke
	make -C top-down nuke
	make -C docs nuke
