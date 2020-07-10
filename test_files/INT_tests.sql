#CREATE test
    create TaBle INT_test (VAR1 INT, Var2 int not null,
                           VaR3 int auto_increment,
                           vaR4 int not null auto_increment, primary key(Var2));
    CREATE TABLE INt_test (VAR1 int, Var2 int not null,
                           VaR3 int auto_increment,
                           vaR4 int not null auto_increment, primary key(vaR4)); #this should be a different Table
    CREATE TablE INT_Test2 (Var1 int auto_increment, var2 int not null, primary key(var2));
    CREATE TABLE Err_INT_test (VAR1 int, Var2 int not null,
                              VaR3 int auto_increment,
                              vaR4 int not null auto_increment, vAr5 int, primary key(vaR4));


#INSERT INTO test
    insErt iNto INT_test (VAR1, Var2, VaR3, vaR4) valUes( 42, 75, 67, 2);
    inSert into INT_test (VAR1, Var2, VaR3, vaR4) valUEs( -1, -2, -3, -4);
    insert InTo INT_test (Var2) valueS (80);

    insert Into INt_test (VAR1, Var2, VaR3, vaR4) Values (1, 4, -4, -6);
    inserT intO INt_test (VAR1, Var2, VaR3, vaR4) VAlues (1, 5, 6, 9);

    insert into INT_Test2(var2) values (8);
    insert into INT_Test2(var2) values (8);

#This lines should give errors if uncommented
    #insert Into Err_INT_test (Var2) values (30); #vaR4 was not initialized int the first insert into
    #insert InTo Err_INT_test(VAR1, VaR3, vaR4) values (1,2,3); #No value was given to Var2
    #insert into Err_INT_test (VAR1, Var2, VaR3, vaR4, vAr5) valUEs ( 'c', -2.3, "test", -4, 19:01, 15-01-2024);


#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    select * from INT_test;
    SeleCt * from INt_test;
    select * from INT_Test2;

    select vaR4 from INT_test where Var2 = -2;
    select * from INT_test where Var2 > -2;
    select * from INT_test where Var2 < 80;
    select * from INT_test where Var2 >= -2;
    select * from INT_test where Var2 <= 80;
    select * from INT_test where Var2 <> 80;
    select * from INT_test where VAR1 between -100 and 43;

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select vaR4 from INT_test where Var2 = -2.3;
    #select vaR4 from INT_test where Var2 = 'c';
    #select vaR4 from INT_test where Var2 = "ciao";
    #select vaR4 from INT_test where Var2 = 15-01-2012;
    #select vaR4 from INT_test where Var2 = 15:01:22;
    #select vaR4 from INT_test where Var2 between 1 and "ciao";
    #select vaR4 from INT_test where Var2 between "bau" and "ciao";

~