CXX 		:= g++47
CXXFLAGS	:= -std=c++11 -Wall
LDFLAGS		:= -Wall "-Wl,-rpath,/usr/local/lib/gcc47/"
LDLIBS		:= -L/usr/local/include

SRC_DIR = .
OUT_DIR = bin
vpath %.cpp $(SRC_DIR)

PROGRAMS = atomic_check

atomic_check_OBJS = atomic_type.o

################ DO NOT MODIFY BELOW THIS LINE! ################

.PHONY: all
all: $(PROGRAMS)

# generic rule to compile and link executable
define PROGRAM_template =
$(1): $$(addprefix $$(OUT_DIR)/,$$($(1)_OBJS))
endef

$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

# generic rule to compile objects
define compile_template =
$(1)/%.o: %.cpp
	mkdir -p $(1)
	$$(CXX) $$(CXXFLAGS) -c $$< -o $$@
endef

$(eval $(call compile_template,$(OUT_DIR)))

$(PROGRAMS):
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: clean
clean:
	rm -rf $(OUT_DIR) $(PROGRAMS)
