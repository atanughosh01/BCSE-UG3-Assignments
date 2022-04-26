drop table result;
create table result(
    roll int,
    scode int,
    marks int
);

drop table backpaper;
create table backpaper(
    roll int,
    scode int
);

create trigger findback
before insert on result
for each row
declare
    roll int:= :new.roll;
    scode int:= :new.scode;
    marks int:= :new.marks;
begin
    if marks>=50 then
        delete from backpaper where backpaper.roll=roll and backpaper.scode=scode;
    else
        insert into backpaper values(roll,scode);
    end if;
end;
