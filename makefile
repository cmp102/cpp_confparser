CC=g++
AR = ar
ARFLAGS = -crs
RANLIB = ranlib
CCFLAGS = -Wall --pedantic --std=c++17
OUT=confparser.a
SRCDIR=src
OBJDIR=obj
BUILDDIR=build
SRCDIRS= $(shell find src/ -type d)
SRCFILES= $(shell find src/ -name '*.cpp' -type f)
OBJDIRS=	$(patsubst $(SRCDIR)/%,$(BUILDDIR)/$(OBJDIR)/%,$(SRCDIRS))
OBJFILES = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/$(OBJDIR)/%.o,$(SRCFILES))
INCDIRS=-I include


ifdef DEBUG
	CCFLAGS += -g
else
	CCFLAGS += -O3
endif

.PHONY:clean,info,run

$(OUT) : $(OBJDIRS) $(OBJFILES)
	$(AR) $(ARFLAGS) $(OUT) $(OBJFILES) $(OBJFILES)
	$(RANLIB) $(OUT)

$(BUILDDIR)/$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) $(INCDIRS) -c -o $@ $^

$(OBJDIRS) :
	mkdir -p $(OBJDIRS)

$(BUILDDIR) :
	mkdir -p $(BUILDDIR)

run: $(BUILDDIR)/$(APP)
	cd $(BUILDDIR) && ./$(APP)

valgrind: $(BUILDDIR)/$(APP)
	cd $(BUILDDIR) && valgrind ./$(APP) 2> valgrind.log

clean:
	rm -rf $(OUT) $(BUILDDIR)

info:
	$(info $(OBJDIRS))
	$(info $(OBJFILES))
