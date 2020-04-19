OUT=example.out
CC=g++
CCFLAGS= --std=c++17
INCLUDES= -I ../include
CONFPARSEROBJS= ../confparser.a
SRC= main.cpp

$(OUT) : $(SRC) $(CONFPARSEROBJS) 
	$(CC) $(SRC) $(CCFLAGS) -o $(OUT) $(INCLUDES) $(CONFPARSEROBJS) 

$(CONFPARSEROBJS)  :
	cd .. && $(MAKE)

.PHONY:clean,cleanall

clean :
	rm -f $(OUT)

cleanall : clean
	cd .. && $(MAKE) clean