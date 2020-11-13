#
# Part of the Conic project - robot arm controller
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

my-dir = $(dir $(lastword $(MAKEFILE_LIST)))

# Makefiles suck: This macro sets a default value of $(2) for the
# variable named by $(1), unless the variable has been set by
# environment or command line. This is necessary for CC and AR
# because make sets default values, so the simpler ?= approach
# won't work as expected.
define allow-override
  $(if $(or $(findstring environment,$(origin $(1))),\
            $(findstring command line,$(origin $(1)))),,\
    $(eval $(1) = $(2)))
endef

# Check that given variables are set and all have non-empty values,
# die with an error otherwise.
#
# Params:
#   1. Variable name(s) to test.
#   2. (optional) Error message to print.
check-defined = \
    $(strip $(foreach 1,$1, \
        $(call _check-defined,$1,$(strip $(value 2)))))
_check-defined = \
    $(if $(value $1),, \
      $(error Undefined $1$(if $2, ($2))))

# Check if we are building on mingw and produce dll in that case
# very bad and unreliable way to tell it
#
# Params:
#   1. Host GCC compiler
obtain-shared-extension = \
    $(if $(filter $(call gcc-target, $1), mingw32),.dll,.so)

gcc-target = \
    $(lastword $(subst -, ,$(shell $1 -dumpmachine)))

# Assume that make all is default, which is pretty incorrect
get-make-targets = \
    $(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)

