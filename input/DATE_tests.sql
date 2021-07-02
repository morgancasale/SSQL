#CREATE test
    create TaBle DATE_test (VAR1 DATE, Var2 Date not null, var3 date not null, vAr4 date, primary key(var3));
    CREATE TABLE DATE_TEst (VAR1 DATE, Var2 Date not null, var3 date not null, vAr4 date, primary key(var3)); #this should be a different Table
    CREATE TablE DATE_test2 (Var1 date, var2 date not null, primary key(var2));

#INSERT INTO test
    insert into DATE_test (VAR1, Var2, var3, vAr4) vaLues( 29-03-2001, 30-10-1335, 19-03-2039, 31-12-3005);
    insert into DATE_test (Var2, var3, vAr4) vaLues( 01.12.0678, 25.12.1675, 23.06.0889);
    insert into DATE_test (VAR1, Var2, var3, vAr4) vaLues( 12.04.1986, 25.08.1770, 19-05-2005, 31/01/2021);

    insert InTo DATE_test (Var2, var3) valueS (08/07/0001, 29/02/2020);
    insert into DATE_test2(Var1, var2) values (05/07/1999, 23/08/2002);
    insert into DATE_test2 (var2) values (09/06/2901);


#This lines should give errors if uncommented
    #insert into DATE_test2 (var3) values (10/11/0667); #var3 was not initialized int the first insert into
    #insert InTo DATE_test2 (var1) values (07-12-1339); #No value was given to Var2 primary key
    #insert into DATE_test2 (Var1, var2) values ('e', "miao"); #unmatched types
    #insert into DATE_test2 (var2) values (05/2403); #void day field
    #insert into DATE_test2 (var2) values (06/01); #void year field

#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    #select * from DATE_test;
    select * from DATE_test2;

    select vAr4 from DATE_test where Var2 = 25.08.1770;
    select * from DATE_test where Var2 > 29-12-1999;
    select * from DATE_test where Var2 < 12/07/2006;
    select * from DATE_test where Var2 >= 29-12-1999;
    select * from DATE_test where Var2 <= 12/07/2006;
    select * from DATE_test where Var2 <> 25.08.1770;
    select * from DATE_test where VAR1 between 01.01.1999 and 31.12.1999;

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select vaR4 from DATE_test where Var2 = 15;
    #select vaR4 from DATE_test where Var2 = -2.3;
    #select vaR4 from DATE_test where Var2 = c;
    #select vaR4 from DATE_test where Var2 = "ciao";
    #select vaR4 from DATE_test where Var2 = 15:01:22;
    #select vaR4 from DATE_test where Var2 between 1 and "ciao";
    #select vaR4 from DATE_test where Var2 between "bau" and "ciao";

~