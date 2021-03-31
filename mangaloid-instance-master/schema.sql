CREATE TABLE "manga" (
    "id" INTEGER NOT NULL,
    "type" INTEGER NOT NULL,
    "country_of_origin" STRING NOT NULL,
    "publication_status" INTEGER NOT NULL,
    "scanlation_status" BOOL NOT NULL,
    "mal_id" INTEGER,
    "anilist_id" INTEGER,
    "mangaupdates_id" INTEGER,
    PRIMARY KEY("id")
);

INSERT INTO "manga" ("id", "type", "country_of_origin", "publication_status", "scanlation_status", "mal_id", "anilist_id", "mangaupdates_id") VALUES
(1, 0, 'ja', 0, 0, 0, 0, 0),
(2, 0, 'ja', 0, 0, 0, 0, 0);

CREATE TABLE "title" (
    "manga_id" INTEGER NOT NULL,
    "text" TEXT NOT NULL
);

INSERT INTO "title" ("manga_id", "text") VALUES
(1, 'YuruYuri'),
(1, 'ゆるゆり'),
(2, 'Yuyushiki'),
(2, 'ゆゆ式');

CREATE TABLE "tag" (
    "id" INTEGER NOT NULL,
    "name" STRING NOT NULL,
    PRIMARY KEY("id")
);

INSERT INTO "tag" ("id", "name") VALUES
(1, 'sol'),
(2, 'yuri'),
(3, 'cgdct'),
(4, 'comedy');

CREATE TABLE "manga_tag" (
    "manga_id" INTEGER NOT NULL,
    "tag_id" INTEGER NOT NULL
);

INSERT INTO "manga_tag" ("manga_id", "tag_id") VALUES
(1, 2),
(1, 4),
(2, 3),
(2, 4);

CREATE TABLE "person" (
    "id" INTEGER NOT NULL,
    "name" STRING NOT NULL,
    PRIMARY KEY("id")
);

INSERT INTO "person" ("id", "name") VALUES
(1, 'Namori'),
(2, 'Komata Mikami');

CREATE TABLE "author" (
    "manga_id" INTEGER NOT NULL,
    "person_id" INTEGER NOT NULL
);

INSERT INTO "author" ("manga_id", "person_id") VALUES
(1, 1),
(2, 2);

CREATE TABLE "artist" (
    "manga_id" INTEGER NOT NULL,
    "person_id" INTEGER NOT NULL
);

INSERT INTO "artist" ("manga_id", "person_id") VALUES
(1, 1),
(2, 2);

CREATE TABLE "chapter" (
    "id" INTEGER NOT NULL,
    "manga_id" INTEGER NOT NULL,
    "chapter_no" INTEGER NOT NULL,
    "chapter_postfix" STRING,
    "ordinal" INTEGER NOT NULL,
    "pages" INTEGER NOT NULL,
    "title" STRING,
    "version" INTEGER,
    "language_id" STRING NOT NULL,
    "group_id" INTEGER,
    "date_added" INTEGER NOT NULL,
    "ipfs_link" STRING NOT NULL,
    PRIMARY KEY("id")
);

INSERT INTO "chapter" ("id", "manga_id", "chapter_no", "chapter_postfix", "ordinal", "pages", "title", "version", "language_id", "group_id", "date_added", "ipfs_link") VALUES
(1, 1, 1, NULL, 100, 13, '', 0, 'en', NULL, 0, ''),
(2, 1, 2, NULL, 200, 13, '', 1, 'en', NULL, 0, ''),
(3, 2, 1, NULL, 100, 13, '', 0, 'en', NULL, 0, '');
