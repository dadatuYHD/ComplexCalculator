object = ./obj/CalcState.o ./obj/calc_complex_YHD.o ./obj/CalcInput.o ./obj/CalcExe.o ./obj/CalcOutput.o \
		 ./obj/DataCenter.o
target = ./bin/calc_complex_YHD 


$(target): $(object)
	gcc $^ -o $@ -g -std=c99
$(object): ./obj/%.o: ./source/%.c
	gcc  $^ -o $@ -c -g -std=c99

.PHONY: clean
clean:
	rm -rf $(object) 
