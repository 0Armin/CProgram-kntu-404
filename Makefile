# =========================
# Compiler settings
# =========================
CC = gcc
CFLAGS = -Wall -g -MMD -MP
LDFLAGS = -lm

# =========================
# Directories (بدون تست)
# =========================
SRC_DIRS := . Cell-Sheet Formula File

# همه فایل‌ها به جز test_file.c
SRCS := $(filter-out File/test_file.c, $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)))
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

# =========================
# Target executable
# =========================
TARGET = Exel_Program

# =========================
# Build main program
# =========================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile .c -> .o
%.o: %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) -I. -ICell-Sheet -IFile -IFormula -c $< -o $@

# Include dependencies
-include $(DEPS)

# =========================
# File module tests
# =========================
test: CFLAGS += -DRUN_FILE_TESTS
test: File/test_file.o File/utils.o File/format_check.o File/loader.o File/saver.o
	$(CC) $(CFLAGS) -o file_tests $^ $(LDFLAGS)

# =========================
# Clean build (Linux + Windows)
# =========================
clean:
	@echo Cleaning object and dependency files...
	rm -f $(OBJS) $(DEPS) $(TARGET) file_tests 2>/dev/null || true
	del /f $(OBJS) $(DEPS) $(TARGET).exe file_tests.exe 2>nul || true
