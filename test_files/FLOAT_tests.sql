#CREATE test
    create Table FLOAT_test (var1 float, Var2 float, VAR3 float not null, vAr4 float, primary key(VAR3));
    create Table FLOAT_TEst (var1 float, Var2 float, VAR3 float not null, vAr4 float, primary key(VAR3)); #this should be a different Table
    CREATE TablE FLOAT_test2 (Var1 float, var2 float not null, primary key(var2));

#INSERT INTO test
    insert into FLOAT_test (var1, Var2, VAR3) values ( 2.355, -0.000008, 0.0);
    insert into FLOAT_test (var1, Var2, vAr4, VAR3) values ( 267.45, 0.00668, 7684.23, -56.00);
    insert into FLOAT_test (vAr4, VAR3) values (9000.98, 32242.7);
    insert into FLOAT_test2 (var2) values (8.3);
    insert into FLOAT_test2 (Var1, var2) values (78.466, 90.1356);

#This lines should give errors if uncommented
    #insert Into FLOAT_test2 (Var3) values (57.789); #Var3 was not initialized int the first insert into
    #insert InTo FLOAT_test (var1, VAR3, vAr4) values (1.24, 2.2536, 0.0003); #No value was given to Var2 primary key
    #insert into FLOAT_test2 (Var1, var2) values ('e', "miao");

#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    SeleCt * from FLOAT_test;
    select * from FLOAT_test2;

    select * from FLOAT_test where vAr4 = 0.0;
    select var1, Var2 from FLOAT_test where VAR3 = 0.0;
    select * from FLOAT_test where VAR3 > -4.7;
    select * from FLOAT_test where VAR3 < 8009.2345;
    select * from FLOAT_test where VAR3 >= -90.1356;
    select * from FLOAT_test where VAR3 <= 35.346;
    select * from FLOAT_test where VAR3 <> 0.0;
    select * from FLOAT_test where VAR3 between -343.45 and 0.0;

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select * from FLOAT_test where VAR3 = c;
    #select * from FLOAT_test where VAR3 = "ciao";
    #select * from FLOAT_test where VAR3 = 15-01-2012;
    #select * from FLOAT_test where VAR3 = 15:01:22;
    #select * from FLOAT_test where VAR3 between 1.34 and "ciao";
    #select * from FLOAT_test where VAR3 between "bau" and "ciao";

~