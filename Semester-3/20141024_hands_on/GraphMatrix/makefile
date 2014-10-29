COMPILER = gcc
COMPILER_FLAGS = -ansi -g -Og -pedantic -Wall -Wextra
LINKER_FLAGS = -lm
PROG=matrix
C_FILES = $(wildcard *.c)
O_FILES = $(C_FILES:.c=.o)

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) -c $<

$(PROG): $(O_FILES)
	$(COMPILER) -o $@ $(O_FILES) $(LINKER_FLAGS)

clean: 
	rm -f $(O_FILES) $(PROG)

depend:
	@cat < /dev/null > makedep
	@for i in $(C_FILES); do \
		($(COMPILER) -MM $$i >> makedep); done
	@echo "/^# BEGIN DEPENDENCIES\$$/+1,\$$d" > edcmds
	@echo "r makedep" >> edcmds
	@echo "wq" >> edcmds
	@cp makefile makefile.bak
	@ed -v - makefile < edcmds
	@rm edcmds makedep
	@echo "# LINE REQUIRED FOR MAKEDEPEND" >> makefile

# BEGIN DEPENDENCIES
# LINE REQUIRED FOR MAKEDEPEND
