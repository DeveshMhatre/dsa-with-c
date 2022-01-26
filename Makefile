# Compiler to use
CC = clang

# Compiler flags
CFLAGS = -Wall -DNDEBUG

# The name to use for both the target source files, and the output files
all: custom_array call_by_ref linked_list circular_linked_list doubly_linked_list stack_with_arrays

clear:
	rm custom_array call_by_ref linked_list circular_linked_list doubly_linked_list stack_with_arrays
