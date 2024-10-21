# Define output and source files
EXEC = parser       # The final executable
FLEX_SRC = lexer.l  # The lexer file
BISON_SRC = parser.y # The Bison file
AST_SRC = ast.c     # The AST source file
AST_HEADER = ast.h  # The AST header file
BISON_OUTPUT = parser.tab.c # The output of Bison
LEX_OUTPUT = lexer.c # The output of Flex
BISON_HEADER = parser.tab.h # Bison-generated header file
SYMBOLTABLE_SRC = symboltable.c
SYMBOLTABLE_HEADER = symboltable.h
SEMANTIC_HEADER = semantic.h
SEMANTIC_SRC = semantic.c

# Compilation rule
all: clean $(EXEC)

# Build the final executable by linking the AST, Bison, and Flex files
$(EXEC): $(BISON_OUTPUT) $(LEX_OUTPUT) $(AST_SRC) $(SYMBOLTABLE_SRC) $(SEMANTIC_SRC) 
	@echo "Linking..."
	cc -o $(EXEC) $(BISON_OUTPUT) $(LEX_OUTPUT) $(AST_SRC) $(SYMBOLTABLE_SRC) $(SEMANTIC_SRC)  -lfl
	./parser source.txt

# Bison rule: generate the parser code from parser.y
$(BISON_OUTPUT): $(BISON_SRC) $(AST_HEADER) $(SYMBOLTABLE_HEADER) $(SEMANTIC_HEADER) 
	@echo "Generating Bison parser..."
	bison -d $(BISON_SRC)

# Flex rule: generate lexer code from lexer.l
$(LEX_OUTPUT): $(FLEX_SRC) $(BISON_HEADER) $(AST_HEADER) $(SYMBOLTABLE_HEADER) $(SEMANTIC_HEADER)
	@echo "Generating Flex lexer..."
	flex $(FLEX_SRC)

# Rule to clean up generated files
clean:
	@echo Refreshing environment...
	rm -f $(EXEC) $(BISON_OUTPUT) $(BISON_HEADER) $(LEX_OUTPUT)
