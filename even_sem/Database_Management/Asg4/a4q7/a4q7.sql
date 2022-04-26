drop table ordermast;
create table ordermast(
orderno int,
orderdt date);

drop table orderdetails;
create table orderdetails(
orderno char(5),
itemno char(5),
qty number);

drop table delmast;
create table delmast(
delno char(5),
orderno char(5),
deldt date);

drop table deldetails;
create table deldetails(
delno char(5),
itemno char(5),
qty number);

insert into ordermast values('1','17-jan-2001');
insert into ordermast values('2','27-jan-2001');
insert into ordermast values('3','07-jan-2001');
insert into ordermast values('4','18-jan-2001');

insert into delmast values('a','1','12-jan-2005');
insert into delmast values('p','2','13-jan-2005');
insert into delmast values('k','3','14-jan-2005');
insert into delmast values('b','4','15-jan-2005');

insert into orderdetails values('1','2', 5);
insert into orderdetails values('2','2', 5);
insert into orderdetails values('3','2', 5);
insert into orderdetails values('4','2', 5);

insert into deldetails values('a','2', 5);
insert into deldetails values('p','2', 5);
insert into deldetails values('k','2', 5);
insert into deldetails values('b','2', 5);

select * from ordermast;
select * from orderdetails;
select * from delmast;
select * from deldetails;
drop table notun;
create table notun as
select delno,itemno,qty,orderno,deldt,orderdt from deldetails left join delmast using(delno) left join ordermast using(orderno);

select * from notun;


declare
    d1 date:='18-jan-2001';
    d2 date:='12-jan-2005';
    cursor curr is 
        select * from notun;
    delno char(5);
    itemno char(5);
    qty number;
    ordno char(5);
    deldate date;
    orderdate date;
begin
    open curr;
    loop
        fetch curr into delno,itemno,qty,ordno,deldate,orderdate;
        if deldate between d1 and d2 then
        dbms_output.put_line(delno||itemno||qty);
        end if;
        --dbms_output.put_line(delno||itemno||qty);
        exit when curr%notfound;
    end loop;
end;
