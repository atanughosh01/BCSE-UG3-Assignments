declare
	st date := to_date('&from_date','dd/mm/yyyy');
	en date := to_date('&to_date','dd/mm/yyyy');
begin
	dbms_output.put_line('Pending deliveries for orders placed between ' || st || ' and ' || en);
	
	for ord in (select * from ordermast natural join deliverymast natural join delivery_details where order_dt between st and en and delv_dt>=sysdate)
	loop
		dbms_output.put_line(ord.order_no);
		dbms_output.put_line(ord.delv_no);
		dbms_output.put_line(ord.delv_dt);
	       	dbms_output.put_line(ord.item_no);
		dbms_output.put_line(ord.qty);
	end loop;
end;
/
