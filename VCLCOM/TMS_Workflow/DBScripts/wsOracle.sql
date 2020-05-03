/*
TMS Workflow Studio
Full SQL script for Oracle databases
version 1.5

To upgrade your database structure from previous versions, see wsOracleUpdate.sql file
*/

CREATE TABLE wsattachment (
  id NUMBER(38,0) not null,
  workkey NUMBER(38,0),
  createdon DATE,
  filecontent BLOB,
  objecttype NUMBER(38,0))
/
CREATE TABLE wstaskinstance (
  id NUMBER(38,0) NOT NULL,
  task CLOB,
  createdon DATE,
  userid VARCHAR2(50),
  comments CLOB,
  name VARCHAR2(50),
  subject VARCHAR2(50),
  description CLOB,
  workflowinstancekey NUMBER(38,0),
  workflowdefinitionkey NUMBER(38,0),
  completed VARCHAR2(1),
  modifiedon DATE,
  modifieduserid VARCHAR2(50))
/
CREATE TABLE wsworkflowdefinition (
  id NUMBER(38,0) NOT NULL,
  workflow CLOB,
  name VARCHAR2(255))
/
CREATE TABLE wsworkflowinstance (
  id NUMBER(38,0) NOT NULL,
  workflow CLOB,
  workflowdefinitionkey NUMBER(38,0),
  createdon DATE,
  modifiedon DATE,
  finishedon DATE,
  nextruntime DATE)
/
CREATE TABLE wstasklog (
  taskinstancekey NUMBER(38,0) NOT NULL,
  eventdate DATE NOT NULL,
  operation VARCHAR2(1) NOT NULL,
  userid VARCHAR2(50),
  info VARCHAR2(100),
  info2 VARCHAR2(100))
/
ALTER TABLE wsattachment ADD PRIMARY KEY (id)
/
ALTER TABLE wstaskinstance ADD PRIMARY KEY (id)
/
ALTER TABLE wsworkflowdefinition ADD PRIMARY KEY (id)
/
ALTER TABLE wsworkflowinstance ADD PRIMARY KEY (id)
/
ALTER TABLE wstasklog ADD PRIMARY KEY (taskinstancekey,eventdate,operation)
/
