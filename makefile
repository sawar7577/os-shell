TARGETS = Shell

all: $(TARGETS)

%o: %.c
	gcc -g -c -o  $@ $<
Shell: childsighandler.o clock.o echo.o execommand.o ls.o othercommand.o pinfo.o printprompt.o pwd.o remindme.o main.o tokenise.o cd.o setenv.o kjob.o 
		gcc -o Shell childsighandler.o clock.o echo.o execommand.o ls.o othercommand.o pinfo.o printprompt.o pwd.o remindme.o main.o tokenise.o cd.o setenv.o kjob.o	

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o