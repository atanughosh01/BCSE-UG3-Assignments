drop table request;
create table request(
    reqno int,
    reqdt date
);
insert into request values(1,'25-feb-1888');
insert into request values(2,'25-jan-1888');
insert into request values(3,'25-mar-1888');
insert into request values(4,'25-jun-1888');

drop table logentry;
create table logentry(
    entryno int,
    reqno   int,
    entrydt date
);
insert into logentry values(1,100,'17-jan-2001');

create or replace trigger logreq
before delete on request
for each row
declare
    reqnum int;
    enum int:=0;
    edt date;
begin
    reqnum:= :old.reqno;
    edt:= sysdate;
    for rec in (select * from logentry)
    loop
        enum:=rec.entryno;
    end loop;
    insert into logentry values(enum,reqnum,edt);
end;
/
select * from logentry;
delete from request where reqno=4;
select * from logentry;
