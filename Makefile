# =========================
# Compiler settings
# =========================
CC = gcc
CFLAGS = -Wall -g -MMD -MP
LDFLAGS = -lm

# =========================
# Directories
# =========================
SRC_DIRS := . Cell-Sheet File Formula

# =========================
# Source files and object files
# =========================
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)
OBJ_WIN := $(subst /,\,$(OBJS))
DEP_WIN := $(subst /,\,$(DEPS))

# =========================
# Target executable
# =========================
TARGET = Exel_Program

# =========================
# Build rules
# =========================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile .c -> .o
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I. -ICell-Sheet -IFile -IFormula -c $< -o $@

# Include dependencies
-include $(DEPS)

# Clean build
clean:
	@echo Cleaning object and dependency files...
	@for %%f in ($(OBJ_WIN) $(DEP_WIN)) do if exist "%%f" del /f /q "%%f"
	@if exist $(TARGET).exe del /f $(TARGET).exe
	@if exist $(TARGET) del /f $(TARGET)
