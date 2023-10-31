create function capture() returns text language c
as 'MODULE_PATHNAME';

create function log_warning(text) returns void language c
AS 'MODULE_PATHNAME';
