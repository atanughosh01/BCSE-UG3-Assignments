create or replace procedure issue_proc(memid MEMBER_025.MEM_ID%TYPE, bid BOOK_025.BOOK_ID%TYPE, tid ISSUE_025.TR_ID%TYPE)   
as   
   books_issued number;   
   books_returned number;   
   member_flag number;   
   book_availability_flag number;   
   max_no_of_books number;   
   slno number;   
   max_reached exception;   
   already_issued exception;   
   member_not_found exception;   
   cursor c1 is   
   select sno from book_025 where book_id=bid and status='R';   
begin   
    select count(*) into member_flag from member_025 where mem_id=memid;   
    if member_flag=0 then   
        raise member_not_found;   
    end if;   
    select count(*) into books_issued from issue_025 where mem_id=memid;   
    select count(*) into books_returned from return_025 where mem_id=memid;   
    select max_books into max_no_of_books from type_deps_025 where m_type=(select m_type from member_025 where mem_id=memid);   
    if (books_issued-books_returned)=max_no_of_books then   
        raise max_reached;   
    END if;   
    select count(*) into book_availability_flag from book_025 where book_id=bid and status='R';   
    if book_availability_flag=0 then   
        raise already_issued;   
    end if;
    open c1;   
    fetch c1 into slno;   
    close c1;   
    update book_025 set status='I' where book_id=bid and sno=slno;   
      insert into issue_025(tr_id,mem_id,book_id,sno) values(tid,memid,bid,slno);
    dbms_output.put_line('Book with Serial Number '||slno||' issued');   
EXCEPTION
   WHEN max_reached THEN   
         dbms_output.put_line('Member has reached limit of maximum books issued');   
   WHEN member_not_found THEN   
         dbms_output.put_line('Given member does not exist');   
   when already_issued then   
         dbms_output.put_line('No copies of the book are available to be issued');   
end;
