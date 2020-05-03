/*
TMS Workflow Studio
SQL update script for MS SQL Server databases
version 1.5
*/


/* From previous versions to version 1.5 */

ALTER TABLE wsworkflowinstance ADD nextruntime
  DATETIME NULL
GO
