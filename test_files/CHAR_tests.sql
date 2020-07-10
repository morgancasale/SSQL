#CREATE test
    create TaBle CHAR_test (VAR1 char, Var2 CHAR not null, primary key(Var2));
    CREATE TABLE Err_CHAR_test (VAR1 Char, Var2 ChAr not null, primary key(Var2));


#INSERT INTO test
    insErt iNto CHAR_test (VAR1, Var2) valUes( 'c', 'r');
    inSert into CHAR_test (Var2) valUEs('e');

#This lines should give errors if uncommented
    #insert InTo Err_CHAR_test(VAR1) values ('d'); #No value was given to Var2
    #insErt iNto CHAR_test (VAR1, Var2) valUes( '"', 'r'); # The use of the character '"' is not permitted

#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    select * from CHAR_test;

    select VAR1 from CHAR_test where Var2 = 'e';
    select * from CHAR_test where Var2 > 'c';
    select VAR1 from CHAR_test where Var2 < 'p';
    select * from CHAR_test where Var2 >= 'c';
    select * from CHAR_test where Var2 <= 'r';
    select * from CHAR_test where Var2 <> 'e';
    select * from CHAR_test where VAR1 between 'a' and 'd';

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select vaR4 from CHAR_test where Var2 = -2.3;
    #select vaR4 from CHAR_test where Var2 = 2;
    #select vaR4 from CHAR_test where Var2 = "ciao";
    #select vaR4 from CHAR_test where Var2 = 15-01-2012;
    #select vaR4 from CHAR_test where Var2 = 15:01:22;
    #select vaR4 from CHAR_test where Var2 between 'a' and "ciao";
    #select vaR4 from CHAR_test where Var2 between "bau" and "ciao";

~