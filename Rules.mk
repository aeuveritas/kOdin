sub_build:
	@for dir in $(SUB_DIRS); do \
	make -C $$dir || exit $?; \
	done

sub_clean:
	@for dir in $(SUB_DIRS); do \
	make -C $$dir clean; \
	done