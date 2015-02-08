# Utilities
RM              = rm -rf
MKDIR           = mkdir -p
EXEC            = exec

# Directories
DISTPATH        = dist
SRCPATH         = src
INCPATH         = inc

# Source Artifacts
SRCFILES        = $(shell find $(SRCPATH) -iname "*.c")
SRCOBJS         = $(SRCFILES:$(SRCPATH)/%.c=$(DISTPATH)/%.o)
SRCDEPS         = $(SRCFILES:$(SRCPATH)/%.c=$(DISTPATH)/%.d)

# Compiler
CC              = clang
CFLAGS          = -std=c11 -fmessage-length=0 -Wall -Wextra -pedantic -O2 -I$(INCPATH)
LDFLAGS         = -flto

# Executable
EXENAME         = hpknxd
OUTPUT          = $(DISTPATH)/$(EXENAME)

# Default Targets
all: $(OUTPUT)

clean:
	$(RM) $(SRCDEPS) $(SRCOBJS)

test: $(OUTPUT)
	$(EXEC) $(OUTPUT)

mkdirs:
	$(MKDIR) $(dir $(OUTPUT) $(SRCOBJS) $(SRCDEPS))

.PHONY: all clean test mkdirs

# File Targets
-include $(SRCDEPS)

$(OUTPUT): $(SRCOBJS) mkdirs
	$(CC) $(LDFLAGS) -o$@ $(SRCOBJS)

$(DISTPATH)/%.o: $(SRCPATH)/%.c mkdirs
	$(CC) -c $(CFLAGS) -MMD -MF$(@:%.o=%.d) -MT$@ -o$@ $<