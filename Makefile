object = ./obj/CalcState.o ./obj/CalcComplexMain.o ./obj/CalcInput.o ./obj/CalcExe.o ./obj/CalcOutput.o \
		 ./obj/DataCenter.o
target = ./bin/CalcComplexMain 


$(target): $(object)
	gcc $^ -o $@ -g -std=c99
$(object): ./obj/%.o: ./source/%.c
	gcc  $^ -o $@ -c -g -std=c99

.PHONY: clean
clean:
	rm -rf $(object) 
