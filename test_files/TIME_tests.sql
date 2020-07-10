#CREATE test
    create TaBle TIME_test (VAR1 TIME, Var2 Time not null, primary key(Var2));
    CREATE TABLE Err_TIME_test (VAR1 STring, Var2 TIME not null, VAr3 time, primary key(Var2));


#INSERT INTO test
    insErt iNto TIME_test (VAR1, Var2) valUes( 19:01:45, 21.57.02);
    inSert into TIME_test (Var2) valUEs( 06.07.23);

#This lines should give errors if uncommented
    #insert InTo Err_TIME_test(VAR1) values (18:45); #No value was given to Var2
    #insErt iNto Err_TIME_test (VAR1, Var2, VAr3) valUes( -17:40, 07.-50.4, 04:47:-30); #Negative time
    #inseRt inTo Err_TIME_test (VAR1, Var2, VAr3) valUes( 25:40, 07.67.4, 04:47:80)

#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    #select * from TIME_test;


    select VAR1 from TIME_test where Var2 = 21:57:02;
    select * from TIME_test where Var2 > 21:56:55;
    select Var2 from TIME_test where Var2 < 22.30;
    select * from TIME_test where Var2 >= 21:57;
    select * from TIME_test where Var2 <= 21:57;
    select * from TIME_test where VAR1 <> 19:01:45;
    select * from TIME_test where VAR1 between 00:01 and 23:35;

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select vaR4 from TIME_test where Var2 = -2.3;
    #select vaR4 from TIME_test where Var2 = 2;
    #select vaR4 from TIME_test where Var2 = 'y';
    #select vaR4 from TIME_test where Var2 = 15-01-2012;
    #select vaR4 from TIME_test where Var2 = "string";
    #select vaR4 from TIME_test where Var2 between 19:01:34 and 2;
    #select vaR4 from TIME_test where Var2 between -2.5 and 9.86;

~