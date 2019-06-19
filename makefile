CC = g++
SRC_FILES = proxy.cpp httputils.cpp
EXEC = main
LIB = -lm

$(EXEC) : $(SRC_FILES)
	$(CC) $(SRC_FILES) -o $(EXEC) $(LIB)

.PHONY: clean
clean:
	rm main
