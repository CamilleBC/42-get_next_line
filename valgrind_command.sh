#!/bin/zsh
valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 --verbose \
		 --log-file=valgrind-out.log \
		 ./get_next_line test_no_nl
