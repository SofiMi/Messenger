CREATE SCHEMA server;

CREATE TABLE server.user (
  userid integer NOT NULL PRIMARY KEY,
  name character varying(100) NOT NULL,
  login character varying(100) NOT NULL,
  password character varying(100) NOT NULL
);

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

CREATE TABLE server.message (
  messageid integer NOT NULL PRIMARY KEY,
  chatid integer NOT NULL,
  index_in_char integer NOT NULL,
  text character varying(1000) NOT NULL
);