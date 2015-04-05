PATH_INC = ../
PATH_SRC = .
PATH_BIN = .
PATH_OBJ = .

# Setting for business lib
PATH_BASE         = /usr/local/cftlib

#boost library
LIB_BASE     = $(PATH_INC)/libblpbase.a


# Setting for compile
CC       := g++
CFLAGS   +=  -I$(PATH_INC)             
CFLAGS   += -g -O -DNDEBUG -Wall -fpic 
LIBS     += $(LIB_BASE)

# Target to create
EXE  := $(PATH_BIN)/main
OBJS := $(patsubst $(PATH_SRC)/%.cpp,$(PATH_OBJ)/%.o,$(wildcard $(PATH_SRC)/*.cpp))

# Compile
$(EXE) : $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

$(PATH_OBJ)/%.o :  $(PATH_SRC)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

# Tools
.PHONY : clean
clean:
	rm -f $(OBJS) $(SO) $(PATH_SRC)/*.d $(PATH_BIN)/logservice
