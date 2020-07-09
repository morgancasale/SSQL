#CREATE test
    create TaBle TEXT_test (VAR1 TExt, Var2 string not null, primary key(Var2));
    CREATE TABLE Err_TEXT_test (VAR1 STring, Var2 TExT not null, primary key(Var2));


#INSERT INTO test
    insErt iNto TEXT_test (VAR1, Var2) valUes( "abba", "zyyz");
    inSert into TEXT_test (Var2) valUEs("miao");

#This lines should give errors if uncommented
    #insert InTo Err_TEXT_test(VAR1) values ("tef"); #No value was given to Var2
    #insErt iNto TEXT_test (VAR1, Var2) valUes( "/err", "swrt"); # The use of the string "/err" (and others) is not permitted

#WHERE test (WHERE is shared between SELECT, UPDATE and DELETE)
    select * from TEXT_test;

    select vaR1 from TEXT_test where Var2 = "zyyz";
    select * from TEXT_test where Var2 > "abba";
    select vaR1 from TEXT_test where Var2 < "ZZZzz";
    select * from TEXT_test where Var2 >= "abba";
    select * from TEXT_test where Var2 <= "ZZZz";
    select * from TEXT_test where Var2 <> "xiaorb";
    select * from TEXT_test where VAR1 between "aa" and "ringogol";

#This lines should give errors if uncommented
#Comparing data of different types should give an error
    #select vaR4 from TEXT_test where Var2 = -2.3;
    #select vaR4 from TEXT_test where Var2 = 2;
    #select vaR4 from TEXT_test where Var2 = 'y';
    #select vaR4 from TEXT_test where Var2 = 15-01-2012;
    #select vaR4 from TEXT_test where Var2 = 15:01:22;
    #select vaR4 from TEXT_test where Var2 between "shid" and 2;
    #select vaR4 from TEXT_test where Var2 between -2.5 and 9.86;

~