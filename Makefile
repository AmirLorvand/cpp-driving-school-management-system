CC = g++

CXXFLAGS = -std=c++11

OUTPUT = output

OBJDIR = obj

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(OUTPUT)
	@echo "Clean compilation complete."

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT)
	@rm -rf $(OBJDIR) # Clean up object files

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OUTPUT)
	@rm -rf $(OBJDIR)

.PHONY: all clean
