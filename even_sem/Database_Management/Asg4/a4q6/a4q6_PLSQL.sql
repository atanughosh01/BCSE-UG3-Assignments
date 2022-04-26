create or replace view lv as select emp_id, extract(month from lstart) as "month", lend-lstart as num_of_days from leave;
/*assuming all records are of the current year only*/
--select * from lv;

declare
	cursor cur is select id, basic from emp2 for update of basic;
	temp emp2.basic%type;
	nod int;
	dim int;
	m int;
	cm int := &current_month;
	cy int := extract(year from sysdate);
begin

	for rec in cur
	loop
		begin
			select "month",num_of_days into m,nod from lv where emp_id=rec.id and "month"=cm;
			exception
				when no_data_found then
					dbms_output.put_line(rec.id || ': ' || rec.basic);
					continue;
		end;
		
		--dbms_output.put_line(m || ' ' || nod);

		if m=1 or m=3 or m=5 or m=7 or m=8 or m=10 or m=12 then
			dim := 31;
		elsif m=2 then
			if mod(cy,4)=0 then
				dim := 29;
			else
				dim := 28;
			end if;
		else
			dim := 30;
		end if;

		temp := rec.basic - (rec.basic * nod)/dim;
		dbms_output.put_line(rec.id || ': ' || temp);
	end loop;
end;
/
