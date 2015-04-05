# Setting for compile
CC       := g++
CFLAGS   += -g -O -DNDEBUG -Wall -fpic -std=c++0x
#-std=c++11


# Target to create
LIBS := libblpbase.a

# Objects compile rule 
OBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

# Create lib
$(LIBS) : $(OBJS)
	@ar rv $@ $^

%.o : %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

# Tools
.PHONY : clean
clean:
	rm -f $(OBJS) $(LIBS)
