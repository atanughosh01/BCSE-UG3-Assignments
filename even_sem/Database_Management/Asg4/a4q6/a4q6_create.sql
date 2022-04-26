create table DEPT2(id int primary key, dept_name varchar(10));

create table EMP2(
    id int primary key,
    emp_name varchar(10),
    constraint emp_name_ch check(emp_name = upper(emp_name)),
    dept int,
    addr varchar(10),
    city varchar(10),
    basic number(10, 2) CHECK(
        basic >= 5000
        and basic <= 9000
    ),
    joined DATE default sysdate,
    grade varchar(2),
    constraint grade_ch check(
        grade = 'A'
        or grade = 'B'
        or grade = 'C'
    ),
    constraint emp_fk foreign key(dept) references DEPT2(id)
);

create table LEAVE(
    emp_id int not null,
    ltype varchar(3),
    constraint ltype_ch check(
        ltype = 'EL'
        or ltype = 'CL'
        or ltype = 'PL'
    ),
    lstart DATE,
    lend DATE,
    constraint leave_pk primary key(emp_id, lstart),
    constraint leave_fk foreign key(emp_id) references EMP2(id) on delete cascade
);
