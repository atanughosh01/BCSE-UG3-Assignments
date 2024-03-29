1.
SELECT MIN(BASIC),
	MAX(BASIC),
	AVG(BASIC)
FROM EMP_BCSE_1005
GROUP BY DEPT_CODE;

2.
SELECT COUNT(*) DEPT_CODE
FROM EMP_BCSE_1005
WHERE SEX = 'F'
GROUP BY DEPT_CODE;
OR
SELECT COUNT(*) AS NO_OF_FEMALES,
	DEPT_CODE
FROM EMP_BCSE_1005
WHERE SEX = 'F'
GROUP BY DEPT_CODE;

3.
SELECT COUNT(*),
	CITY,
	DEPT_CODE
FROM EMP_BCSE_1005
GROUP BY CITY,
	DEPT_CODE;

4.
SELECT COUNT(*)
FROM EMP_BCSE_1005
WHERE JN_DT BETWEEN '01-JAN-00' AND '31-DEC-00'
GROUP BY DESIG_CODE
ORDER BY COUNT(*);

5.
SELECT SUM(BASIC) AS TOTAL_BASIC,
	DEPT_CODE
FROM EMP_BCSE_1005
WHERE SEX = 'M'
	AND BASIC = 1000
GROUP BY DEPT_CODE
ORDER BY TOTAL_BASIC DESC;

6.
SELECT EMP_NAME,
	DESIG_DESC,
	BASIC
FROM EMP_BCSE_1005,
	DESIGNATION_BCSE_1005
WHERE EMP_BCSE_1005.DESIG_CODE = DESIGNATION_BCSE_1005.DESIG_CODE;

7.
SELECT EMP_NAME,
	DESIG_DESC,
	DEPT_NAME,
	BASIC
FROM EMP_BCSE_1005,
	DESIGNATION_BCSE_1005,
	DEPARTMENT_BCSE_1005
WHERE EMP_BCSE_1005.DESIG_CODE = DESIGNATION_BCSE_1005.DESIG_CODE
	AND DEPARTMENT_BCSE_1005.DEPT_CODE = EMP_BCSE_1005.DEPT_CODE;

8.
SELECT DEPT.DEPT_CODE
FROM DEPARTMENT_BCSE_1005 DEPT
	LEFT JOIN EMP_BCSE_1005 EMP ON DEPT.DEPT_CODE = EMP.DEPT_CODE
WHERE EMP.EMP_CODE IS NULL;

9.
SELECT DEPT.DEPT_CODE
FROM DEPARTMENT_BCSE_1005 DEPT
	LEFT JOIN EMP_BCSE_1005 EMP ON DEPT.DEPT_CODE = EMP.DEPT_CODE
WHERE EMP.EMP_CODE IS NOT NULL;

10.
SELECT DEPT_NAME
FROM DEPARTMENT_BCSE_1005
	LEFT JOIN EMP_BCSE_1005 ON DEPARTMENT_BCSE_1005.DEPT_CODE = EMP_BCSE_1005.DEPT_CODE
WHERE EMP_BCSE_1005.DEPT_CODE IS NOT NULL
GROUP BY DEPT_NAME
HAVING COUNT(*) >= 10;

11.
SELECT DEPT_CODE
FROM EMP_BCSE_1005
WHERE BASIC =(
		SELECT MAX(BASIC)
		FROM EMP_BCSE_1005
	);

12.
SELECT DESIG_DESC
FROM EMP_BCSE_1005,
	DESIGNATION_BCSE_1005
WHERE BASIC =(
		SELECT MAX(BASIC)
		FROM EMP_BCSE_1005
	)
	AND EMP_BCSE_1005.DESIG_CODE = DESIGNATION_BCSE_1005.DESIG_CODE;

13.
SELECT COUNT(*),
	DEPT_CODE
FROM EMP_BCSE_1005
WHERE DESIG_CODE = 'MGR'
GROUP BY DEPT_CODE;

14.
SELECT BASIC
FROM EMP_BCSE_1005
ORDER BY BASIC DESC
LIMIT 1;

-- OR

SELECT DISTINCT BASIC
FROM EMP_BCSE_1005
WHERE BASIC >= ALL (
		SELECT BASIC
		FROM EMP_BCSE_1005
	);

15.
SELECT DISTINCT BASIC
FROM EMP_BCSE_1005
WHERE BASIC <= ALL (
		SELECT BASIC
		FROM EMP_BCSE_1005
	);

16.
SELECT DEPT_NAME
FROM EMP_BCSE_1005
	LEFT JOIN DEPARTMENT_BCSE_1005 ON EMP_BCSE_1005.DEPT_CODE = DEPARTMENT_BCSE_1005.DEPT_CODE
GROUP BY DEPT_NAME
HAVING SUM(BASIC) =(
		SELECT MAX(SUM(BASIC))
		FROM EMP_BCSE_1005
		GROUP BY DEPT_CODE
	);

SELECT DEPT_NAME
FROM EMP_BCSE_1005
	LEFT JOIN DEPARTMENT_BCSE_1005 ON EMP_BCSE_1005.DEPT_CODE = DEPARTMENT_BCSE_1005.DEPT_CODE
GROUP BY DEPT_NAME
HAVING AVG(BASIC) =(
		SELECT MAX(AVG(BASIC))
		FROM EMP_BCSE_1005
		GROUP BY DEPT_CODE
	);

SELECT DEPT_NAME
FROM EMP_BCSE_1005
	LEFT JOIN DEPARTMENT_BCSE_1005 ON EMP_BCSE_1014.DEPT_CODE = DEPARTMENT_BCSE_1014.DEPT_CODE
GROUP BY DEPT_NAME
HAVING COUNT(*) =(
		SELECT MAX(COUNT(*))
		FROM EMP_BCSE_1014
		GROUP BY DEPT_CODE
	);

17.
INSERT INTO EMP_BCSE_1005
VALUES(
		'B551',
		'SAPTIK',
		'A014',
		'0001',
		'M',
		'BURDWAN',
		'ANAN',
		'BENGAL',
		713103,
		98765,
		'01-JAN-22'
	);

INSERT INTO EMP_BCSE_1005
VALUES(
		'B552',
		'SAMARESH',
		'A015',
		'0002',
		'M',
		'BURDWAN',
		'COLL',
		'BENGAL',
		713101,
		12345,
		'01-FEB-22'
	);

18.
DELETE FROM EMP_BCSE_1005
WHERE DESIG_CODE NOT IN (
		SELECT DESIG_CODE
		FROM DESIGNATION_BCSE_1005
	);

19.
SELECT EMP_NAME
FROM EMP_BCSE_1005
WHERE BASIC > ANY (
		SELECT AVG(BASIC)
		FROM EMP_BCSE_1005
		WHERE DEPT_CODE = EMP_BCSE_1005.DEPT_CODE
		GROUP BY DEPT_CODE
	)
	AND SEX = 'F';

20.
SELECT COUNT(*)
FROM EMP_BCSE_1005
	JOIN DESIGNATION_BCSE_1005 ON EMP_BCSE_1005.DESIG_CODE = DESIGNATION_BCSE_1005.DESIG_CODE
WHERE SEX = 'F'
GROUP BY DESIG_DESC
HAVING DESIG_DESC = 'MGR';

