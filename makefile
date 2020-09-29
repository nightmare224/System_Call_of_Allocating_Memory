target=hw4
objects=hw4.o mm.o
all:$(target)
$(target):$(objects)
	gcc -o $(target) $(objects)
$(objects):%.o:%.c
	gcc -c $<
clean:
	rm -f $(target) $(objects)
