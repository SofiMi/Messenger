CREATE SCHEMA server;

CREATE TABLE server.user (
  userid integer NOT NULL PRIMARY KEY,
  name character varying(100) NOT NULL,
  login character varying(100) NOT NULL,
  password character varying(100) NOT NULL,
  nickname character varying(100) NOT NULL
);

/* Нужно для коректной работы сервера.*/
insert into server.user
values (0, '0', '0', '0', '0'); 

CREATE TABLE server.friend (
  first_uid integer NOT NULL,
  second_uid integer NOT NULL,
  FOREIGN KEY (first_uid) REFERENCES server.user(userid),
  FOREIGN KEY (second_uid) REFERENCES server.user(userid)
);

CREATE TABLE server.chat (
  chatid integer NOT NULL,
  userid integer NOT NULL,
  FOREIGN KEY (userid) REFERENCES server.user(userid)
);

CREATE TABLE server.chatname (
  chatid integer NOT NULL,
  chatname character varying(100) NOT NULL
);

CREATE TABLE server.message (
  messageid integer NOT NULL PRIMARY KEY,
  chatid integer NOT NULL,
  userid integer NOT NULL,
  index_in_char integer NOT NULL,
  text character varying(1000) NOT NULL
);

insert into server.message (messageid, chatid, index_in_char, text, userid)
values (0, 0, 0, '', 0)
