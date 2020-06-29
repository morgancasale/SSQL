create table car ( model text not null, company text, yor int, price float, speed float, primary key(model) );
insert iNTo car ( model, company, yor, price, speed) values ( "Pa,nda", "Fiat", 2012, 3000.0, 120.5);
insert iNTo car ( model, yor, price) values ( "C3 Picasso", 2006, 5000.5);
insert iNTo car ( model, company, yor, price, speed) values ( "Grand Cherokee", "Jeep", 2012, 68000.0, 140.0);

select * from car where model between "C3 Picasso" and "Grand Cherokee" ;
delete from car where model between  "C3 Picasso" and "Grand Cherokee";
insert iNTo car ( model, company, yor, price, speed) values ( "Grand Cherokee", "Jeep", 2012, 68000.0, 140.0);

CREATE table phone ( Name tExt not null, yOr int not null, price float, sef int auto_increment not null, primary key(Name) );
insert into phone (yOr, Name, sef, price) values (2020, "oneplus 8 pro", 6, 1019.01);
insert into phone (yOr, Name, sef, price) values (2013, "iphone 5", 5, 729.99);
insert into phone (yOr, Name, sef, price) values (2016, "samsung s7 edge", 10, 729.99);

CREATE table EUROPE ( EUROPIAN_COUNTRIES text, PRIMARY KEY (EUROPIAN_COUNTRIES));
insert into EUROPE (EUROPIAN_COUNTRIES) values ("Italy");
insert into EUROPE (EUROPIAN_COUNTRIES) values ("France");
insert into EUROPE (EUROPIAN_COUNTRIES) values ("Greece");

Create table AMERICA ( AMERICAN_COUNTRIES text, PRIMARY KEY (AMERICAN_COUNTRIES));
insert into AMERICA (AMERICAN_COUNTRIES) values ("USA");
insert into AMERICA (AMERICAN_COUNTRIES) values ("Canada");
insert into AMERICA (AMERICAN_COUNTRIES) values ("Mexico");

create TABLE COUNTRIES (
            ID INT               NOT NULL,
            NAME_EUROPE TEXT,
            NAME_AMERICAN TEXT,
            PRIMARY KEY (ID),
            FOREIGN KEY (NAME_EUROPE) REFERENCES EUROPE (EUROPIAN_COUNTRIES),
            FOREIGN KEY (NAME_AMERICAN) REFERENCES AMERICA (AMERICAN_COUNTRIES)
           );
insert Into COUNTRIES (ID, NAME_EUROPE, NAME_AMERICAN) VALUES ( 23, "Italy", "Mexico");
Update COUNTRIES
           seT NAME_EUROPE = "Greece",
           NAME_AMERICAN = "USA"
           WheRe ID = 23;

create TABLE moto ( Name text not null, company1 text, color text, wheels int, primary key(Name));
insert into moto (Name, company1, color, wheels) values ("gina", "piaggio", "rosso", 2);
insert into moto (Name, company1, color, wheels) values ("figa ", "yamaha", "nera", 4);

truncate table AMERICA;

select * from car;

select * from EUROPE;
select * from phone;
select * from AMERICA;
select * from COUNTRIES;

select * from moto;

~