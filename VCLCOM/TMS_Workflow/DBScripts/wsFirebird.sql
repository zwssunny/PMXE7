/*
TMS Workflow Studio
Full SQL script for Firebird/Interbase databases
version 1.5

To upgrade your database structure from previous versions, see wsFirebirdUpdate.sql file
*/

CREATE TABLE wsattachment (
  id INTEGER NOT NULL,
  workkey INTEGER,
  createdon TIMESTAMP,
  filecontent BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  objecttype INTEGER,
  PRIMARY KEY (id));

CREATE TABLE wstaskinstance (
  id INTEGER NOT NULL,
  task BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  createdon TIMESTAMP,
  userid VARCHAR(50),
  comments BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  name VARCHAR(50),
  subject VARCHAR(50),
  description BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  workflowinstancekey INTEGER,
  workflowdefinitionkey INTEGER,
  completed VARCHAR(1),
  modifiedon TIMESTAMP,
  modifieduserid VARCHAR(50),
  PRIMARY KEY (id));

CREATE TABLE wsworkflowdefinition (
  id INTEGER NOT NULL,
  workflow BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  name VARCHAR(255), 
  PRIMARY KEY (id));

CREATE TABLE wsworkflowinstance (
  id INTEGER NOT NULL,
  workflow BLOB SUB_TYPE 0 SEGMENT SIZE 0,
  workflowdefinitionkey INTEGER,
  createdon TIMESTAMP,
  modifiedon TIMESTAMP,
  finishedon TIMESTAMP,
  nextruntime TIMESTAMP,
  PRIMARY KEY (id));

CREATE TABLE wstasklog (
  taskinstancekey INTEGER NOT NULL,
  eventdate TIMESTAMP NOT NULL,
  operation VARCHAR(1) NOT NULL,
  userid VARCHAR(50),
  info VARCHAR(100),
  info2 VARCHAR(100),
  PRIMARY KEY (taskinstancekey,eventdate,operation));
