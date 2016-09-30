
ifeq ($(OS), Windows_NT)
    EXT :=.exe
else
    EXT :=
endif

OUTPUT_DIR_NAME := output
SOURCE_DIR_NAME := src
BASE     := "${CURDIR}"

export SRC      := ${BASE}/${SOURCE_DIR_NAME}
export OUTPUT   := ${BASE}/${OUTPUT_DIR_NAME}

.PHONY: bin
.PHONY: all
.PHONY: docs

all: bin docs output

bin:
	cd ${SRC}/bin && make

docs:
	cd docs && ${MAKE}

output:
	mkdir output
