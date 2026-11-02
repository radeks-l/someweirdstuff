CPPFLAGS:= -std=c++14 \
           -O3 \
           -MMD \
           -MP

LD_FALGS:= -lpthread

SOURCES:= main.cpp \
          StopWatch.cpp \
          unionfind.cpp \
          permutations.cpp

OBJECTS:= $(subst .cpp,.o,$(SOURCES))

EXEC:= main

.PHONY: all $(EXEC) clean

all: $(EXEC)

main: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $^ $(LD_FALGS) -o $@

-include $(subst .cpp,.d,$(SOURCES))

clean:
	rm $(EXEC) *.o *.d
