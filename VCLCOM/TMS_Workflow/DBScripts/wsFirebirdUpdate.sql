/*
TMS Workflow Studio
SQL update script for Firebird/Interbase databases
version 1.5
*/


/* From previous versions to version 1.5 */

ALTER TABLE WSWORKFLOWINSTANCE ADD nextruntime
  TIMESTAMP;
