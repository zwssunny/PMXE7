/*
TMS Workflow Studio
Full SQL script for MS SQL Server databases
version 1.5

To upgrade your database structure from previous versions, see wsSQLServerUpdate.sql file
*/

CREATE TABLE wsworkflowinstance (
  id INTEGER NOT NULL,
  workflow TEXT,
  workflowdefinitionkey INTEGER,
  createdon DATETIME,
  modifiedon DATETIME,
  finishedon DATETIME,
  nextruntime DATETIME,
  PRIMARY KEY (id)
)
GO
CREATE TABLE wstasklog (
  taskinstancekey INTEGER NOT NULL,
  eventdate DATETIME NOT NULL,
  operation VARCHAR(1) NOT NULL,
  userid VARCHAR(50),
  info VARCHAR(100),
  info2 VARCHAR(100),
  PRIMARY KEY (taskinstancekey,
  eventdate,
  operation)
)
GO
CREATE TABLE wsattachment (
  id INTEGER NOT NULL,
  workkey INTEGER,
  createdon DATETIME,
  filecontent IMAGE,
  objecttype INTEGER,
  PRIMARY KEY (id)
)
GO
CREATE TABLE wstaskinstance (
  id INTEGER NOT NULL,
  task TEXT,
  createdon DATETIME,
  userid VARCHAR(50),
  comments TEXT,
  name VARCHAR(50),
  subject VARCHAR(50),
  description TEXT,
  workflowinstancekey INTEGER,
  workflowdefinitionkey INTEGER,
  completed VARCHAR(1),
  modifiedon DATETIME,
  modifieduserid VARCHAR(50),
  PRIMARY KEY (id)
)
GO
CREATE TABLE wsworkflowdefinition (
  id INTEGER NOT NULL,
  workflow TEXT,
  name VARCHAR(255),
  PRIMARY KEY (id)
)
GO