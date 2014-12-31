build_type ?= Release
build_type_lower = ${shell echo ${build_type} | tr "[:upper:]" "[:lower:]"}

build_dir ?= build/${build_type_lower}
cmake_dir := $(CURDIR)

build_tests ?= OFF


all:
	@echo "Usage:"
	@echo "\tmake docs"
	@echo "\tmake test"
	@echo "\tmake clean"
.PHONY: all


build:
	mkdir -p $(build_dir) && cd $(build_dir) && \
		cmake \
		-D CMAKE_BUILD_TYPE=$(build_type) \
		-D FILTER_ITERATOR_ENABLE_TESTS=$(build_tests) \
		$(cmake_dir) && make
.PHONY: build


test:
	build_tests=ON $(MAKE) build
.PHONY: test


clean:
	rm -rf build
.PHONY: clean


docs:
	mkdir -p $(build_dir)
	doxygen Doxyfile
.PHONY: docs


# Redirect all undefined targets to cmake.
%:
	make -C $(build_dir) $@
.PHONY:
