include barebones.mk

ifndef builddoc
	BB_CMAKE_EXTRA_FLAGS=-DUC_BUILD_DOC
endif

all: bb_all

release: bb_build_release

debug: bb_build_debug

coverage: bb_build_coverage

lint: bb_build_lint

lint_build: bb_lint_build

install: bb_install

clean: bb_clean
