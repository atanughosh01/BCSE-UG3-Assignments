create or replace procedure return_proc(memid MEMBER_025.MEM_ID%TYPE, bid BOOK_025.BOOK_ID%TYPE, slno BOOK_025.SNO%TYPE, tid RETURN_025.TR_ID%TYPE)
as
   rd date;
   books_issued number;
   books_returned number;
   not_issued_to_this exception;
begin
    select count(*) into books_issued from issue_025 where mem_id=memid and book_id=bid and sno=slno;
    select count(*) into books_returned from return_025 where mem_id=memid and book_id=bid and sno=slno;
    if books_issued=books_returned then
        raise not_issued_to_this;
    end if;
    update book_025 set status='A' where book_id=bid and sno=slno;
    insert into return_025(tr_id,mem_id,book_id,sno,dt_return) values(tid,memid,bid,slno,sysdate);
    select max(to_ret_by) into rd from issue_025 where mem_id=memid and book_id=bid and slno=sno;
    if  rd < sysdate then
         dbms_output.put_line('Book Returned late');
    end if;
    dbms_output.put_line('Returned');
EXCEPTION
   WHEN not_issued_to_this THEN
         dbms_output.put_line('Given Book copy not issued to this member');
end;
