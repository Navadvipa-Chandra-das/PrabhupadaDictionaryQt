S325L
SNixk_ExcynhiL
Sfcfi_ygixihigL
C:\PostgreSQL\psqlODBC\bin\libpq.dll
C:\PostgreSQL\15\bin\libpq.dll

ALTER ROLE "Navadvipa Chandra das" PASSWORD 'PASSWORD';

\i C:/C/NewNavadvipa/SQL/NewNavadvipa.sql 
\i C:/CopperSpice/Prg/PrabhupadaDictionary/SQL/NewNavadvipa.sql 

SELECT "UserRegKey", encode("UserData"::bytea, 'escape') 
FROM "NewNavadvipa"."UserReg";

-- Role: "Navadvipa Chandra das"
-- DROP ROLE IF EXISTS "Navadvipa Chandra das";

CREATE ROLE "Navadvipa Chandra das" WITH
  LOGIN
  SUPERUSER
  INHERIT
  CREATEDB
  CREATEROLE
  REPLICATION
  ENCRYPTED PASSWORD 'md561db9948acc9279bbc0c7afc8bf2a7bc';

COMMENT ON ROLE "Navadvipa Chandra das" IS 'Главный пользователь базы данных NewNavadvipa!';

-- Database: NewNavadvipa

-- DROP DATABASE IF EXISTS "NewNavadvipa";

CREATE DATABASE "NewNavadvipa"
    WITH
    OWNER = "Navadvipa Chandra das"
    ENCODING = 'UTF8'
    LC_COLLATE = 'Russian_Russia.1251'
    LC_CTYPE = 'Russian_Russia.1251'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;

COMMENT ON DATABASE "NewNavadvipa"
    IS 'База данных Новой Навадвипы';

-- DROP SCHEMA IF EXISTS "NavadvipaSchema" ;

CREATE SCHEMA IF NOT EXISTS "NewNavadvipa"
    AUTHORIZATION "Navadvipa Chandra das";

COMMENT ON SCHEMA "NewNavadvipa"
    IS 'Схема Новой Навадвипы!';

