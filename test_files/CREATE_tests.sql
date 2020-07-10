#CREATE TABLE err1 (var int not_null); #No primary key specified
#CREATE TABLE err2 (var int, primary key(var)); #Primary key cannot be null
#CREATE TABLE INT_test (var int not_null, primary key(var)); #Table name already in use