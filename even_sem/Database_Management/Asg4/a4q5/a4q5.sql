create table book_deets(bookid int primary key, title varchar(20), author varchar(20), publisher varchar(20), price number(7,2));

create table book_nums(bookid int, avail int default 1 not null check(avail=0 or avail=1), serial int default 1, constraint book_nums_pk primary key(bookid, serial), constraint book_nums_fk foreign key(bookid) references book_deets(bookid)); 

create table members(memid int primary key, name varchar(20), email varchar(20), addr varchar(20), memtype char(1) not null, issued int default 0 not null);

create table privi(memtype char(1) primary key, blimit int not null);

create table trans(tid int primary key, memid int not null, bookid int not null, serial int not null, issue_date date not null, return_date date);

CREATE OR REPLACE TRIGGER books_insert_trigger
    BEFORE INSERT
    ON book_nums
    FOR EACH ROW
DECLARE
	ser int;
BEGIN
   select max(serial) into ser from book_nums where bookid=:new.bookid;
   if ser is null then
	ser := 0;
   end if;
   :new.serial := ser+1;
END;
/
CREATE OR REPLACE TRIGGER TRANSACTION
	BEFORE INSERT OR UPDATE ON TRANS
	FOR EACH ROW
DECLARE 
	ISS INT;
	MT PRIVI.MEMTYPE%TYPE;
	MXISS INT;
	BK BOOK_NUMS%ROWTYPE;
	TR TRANS%ROWTYPE;
BEGIN
	SELECT * INTO BK FROM BOOK_NUMS WHERE BOOKID=:NEW.BOOKID AND SERIAL=:NEW.SERIAL;

	IF :NEW.RETURN_DATE IS NULL THEN
		SELECT ISSUED, MEMTYPE INTO ISS, MT FROM MEMBERS M WHERE :NEW.MEMID=M.MEMID;
		IF BK.AVAIL=0 THEN
			RAISE_APPLICATION_ERROR(-20000, 'BOOK UNAVAILABLE');
		END IF;
		SELECT BLIMIT INTO MXISS FROM PRIVI WHERE MEMTYPE=MT;
		IF ISS+1>MXISS THEN
			RAISE_APPLICATION_ERROR(-20001, 'EXCEEDED MAXIMUM ISSUE LIMIT');
		ELSE
			UPDATE MEMBERS SET ISSUED=ISS+1 WHERE MEMID=:NEW.MEMID;
			UPDATE BOOK_NUMS SET AVAIL=0 WHERE BOOKID=:NEW.BOOKID AND SERIAL=:NEW.SERIAL;
			SELECT COUNT(TID) INTO :NEW.TID FROM TRANS;
			:NEW.TID := :NEW.TID+1;
		END IF;
	ELSE
		IF :OLD.RETURN_DATE IS NOT NULL THEN
			RAISE_APPLICATION_ERROR('-20003', 'MEMBER HAS NOT ISSUED THE BOOK YET');
		ELSE
			UPDATE MEMBERS SET ISSUED=ISSUED-1 WHERE MEMID=:OLD.MEMID;
			UPDATE BOOK_NUMS SET AVAIL=1 WHERE BOOKID=:OLD.BOOKID AND SERIAL=:OLD.SERIAL;
		END IF;
	END IF;

	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			RAISE_APPLICATION_ERROR(-20002, 'NO SUCH MEMBER AND/OR BOOK EXISTS');
END;
/
