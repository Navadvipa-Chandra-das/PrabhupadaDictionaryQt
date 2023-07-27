-- База данных Словаря Шрилы Прабхупады SQLite

CREATE TABLE LANGUAGES (
    ID            INTEGER PRIMARY KEY,
    LANGUAGE      TEXT,
    LANGUAGE_WORD TEXT
);

CREATE TABLE SANSKRIT (
    ID           INTEGER PRIMARY KEY,
    ORIGINAL     TEXT,
    TRANSLATE    TEXT,
    LANGUAGE     TEXT,
    [REFERENCES] TEXT
);

CREATE TABLE "UserReg"
(
    "UserRegKey" STRING(720) NOT NULL,
    "UserData" bytea,
    CONSTRAINT "UserReg_pkey" PRIMARY KEY ("UserRegKey")
);

