.phony:q1
q1: FCFS RRBN PRIOR

q1-main.o:q1.c q1.h
	@echo "making $@"
	gcc -c $^
	mv	q1.o $@


q1-common.o:q1-common.c q1.h
	@echo "making $@"
	gcc -c $^

q1-skeleton.o: q1-main.o q1-common.o
	@echo "making $@"
	ld -r $^ -o $@

FCFS:FCFS.c q1-skeleton.o
	@echo "making $@"
	gcc	$^ -o $@

RRBN: RRBN.c q1-skeleton.o
	@echo "making $@"
	gcc	$^ -o $@

PRIOR:	PRIOR.c	q1-skeleton.o
	@echo "making $@"
	gcc	$^ -o $@

THR=-l pthread

q2:	q2.c
	@echo "making $@"
	gcc	$^ -o $@ $(THR)

q3a:q3a.c
	@echo "making $@"
	gcc	$^ -o $@ $(THR)

q3b:q3b.c
	@echo "making $@"
	gcc	$^ -o $@ $(THR)

