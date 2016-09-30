

OUTPUT := ../../

GO_FILES := $(wildcard *.go)
EXE_FILES := $(addprefix ${OUTPUT}/,$(GO_FILES:.go=${EXT}))


all: ${EXE_FILES} 
	echo $(GO_FILES:.go=)
	echo ${GO_FILES}
	echo ${EXE_FILES}

${OUTPUT}/%${EXT}: %.go
	go build -o "${OUTPUT}/$@" $<

