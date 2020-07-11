create table Transazioni ( data date not null, ammontare float not null, ora time, ID int auto_increment, commento string, primary key(ID));

insert into Transazioni (data, ora, ammontare) values (12/07/2003, 10:24, 123.45);
insert into Transazioni (data, ora, ammontare) values (12/07/2003, 11:45, -189.10);
insert into Transazioni (data, ora, ammontare) values (12/07/2003, 13:08, 530.23);
insert into Transazioni (data, ora, ammontare) values (12/07/2003, 17:30, 23.88);
insert into Transazioni (data, ora, ammontare) values (12/07/2003, 21:55, -62.95);
insert into Transazioni (data, ora, ammontare, commento) values (12/07/2003, 23:41, 425.5, "totale giornata");

insert into Transazioni (data, ora, ammontare) values (13/07/2003, 9:06, 133.45);
insert into Transazioni (data, ora, ammontare) values (13/07/2003, 11:02, -199.10);
insert into Transazioni (data, ora, ammontare) values (13/07/2003, 13:58, 630.23);
insert into Transazioni (data, ora, ammontare) values (13/07/2003, 16:24, 123.88);
insert into Transazioni (data, ora, ammontare) values (13/07/2003, 21:40, -262.95);
insert into Transazioni (data, ora, ammontare, commento) values (13/07/2003, 23:53, 425.5, "totale giornata");

insert into Transazioni (data, ora, ammontare) values (14/07/2003, 8:26, 138.45);
insert into Transazioni (data, ora, ammontare) values (14/07/2003, 10:02, -194.10);
insert into Transazioni (data, ora, ammontare) values (14/07/2003, 12:48, 130.23);
insert into Transazioni (data, ora, ammontare) values (14/07/2003, 18:34, 133.88);
insert into Transazioni (data, ora, ammontare) values (14/07/2003, 22:00, -172.95);
insert into Transazioni (data, ora, ammontare) values (14/07/2003, 22:05, -2.85);
insert into Transazioni (data, ora, ammontare, commento) values (14/07/2003, 23:35, 425.5, "totale giornata");

update Transazioni set ammontare = -20.85 where ora = 22.05;

select * from Transazioni;
select * from Transazioni where data = 13/07/2003;

~