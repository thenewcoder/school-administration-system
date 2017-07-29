﻿CREATE TABLE IF NOT EXISTS `gender` (
	`genderId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`type`	TEXT NOT NULL UNIQUE
);

INSERT INTO `gender` (
	`type`)
	VALUES
	("Male"),
	("Female");

CREATE TABLE IF NOT EXISTS `user_type` (
	`userTypeId` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`type` TEXT NOT NULL UNIQUE
);

INSERT INTO `user_type` (
	`type`)
	VALUES
	("Administrator"),
        ("Teacher");
	
CREATE TABLE IF NOT EXISTS `user` (
	`userId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `username`	TEXT NOT NULL UNIQUE,
        `password`	TEXT NOT NULL,
        `fullname`      TEXT,
	`userTypeId`	INTEGER NOT NULL DEFAULT 1,
	FOREIGN KEY(`userTypeId`) REFERENCES `user_type`(`userTypeId`)
);

CREATE TABLE IF NOT EXISTS `dormitory` (
	`dormitoryId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `grade` (
	`gradeId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `bus_stop` (
	`busstopId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`busstopName`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `subject` (
	`subjectId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`subjectName`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `classroom` (
	`classroomId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`classroomName`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `nationality` (
	`nationalityId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`country`	TEXT NOT NULL UNIQUE
);

INSERT INTO `nationality` (
        `country`)
        VALUES
        ("Afghanistan"),
        ("Albania"),
        ("Algeria"),
        ("Andorra"),
        ("Angola"),
        ("Antigua and Barbuda"),
        ("Argentina"),
        ("Armenia"),
        ("Aruba"),
        ("Australia"),
        ("Austria"),
        ("Azerbaijan"),
        ("Bahamas"),
        ("Bahrain"),
        ("Bangladesh"),
        ("Barbados"),
        ("Belarus"),
        ("Belgium"),
        ("Belize"),
        ("Benin"),
        ("Bhutan"),
        ("Bolivia"),
        ("Bosnia and Herzegovina"),
        ("Brazil"),
        ("Brunei"),
        ("Bulgaria"),
        ("Burkina Faso"),
        ("Burma"),
        ("Burundi"),
        ("Cambodia"),
        ("Cameroon"),
        ("Canada"),
        ("Cape Verde"),
        ("Central Africa"),
        ("Chad"),
        ("Chile"),
        ("China"),
        ("Colombia"),
        ("Comoros"),
        ("Congo"),
        ("Costa Rica"),
        ("Croatia"),
        ("Cuba"),
        ("Curacao"),
        ("Cyprus"),
        ("Czechia"),
        ("Denmark"),
        ("Djibouti"),
        ("Domonica"),
        ("Dominican Republic"),
        ("East Timor"),
        ("Ecuador"),
        ("Egypt"),
        ("El Salvador"),
        ("Equatorial Guinea"),
        ("Eritrea"),
        ("Estonia"),
        ("Ethiopia"),
        ("Fiji"),
        ("Finland"),
        ("France"),
        ("Gabon"),
        ("Gambia"),
        ("Georgia"),
        ("Germany"),
        ("Ghana"),
        ("Greece"),
        ("Grenada"),
        ("Guatemala"),
        ("Guinea"),
        ("Guinea-Bissau"),
        ("Guyana"),
        ("Haiti"),
        ("Honduras"),
        ("Hungary"),
        ("Iceland"),
        ("India"),
        ("Indonesia"),
        ("Iran"),
        ("Iraq"),
        ("Ireland"),
        ("Israel"),
        ("Italy"),
        ("Jamaica"),
        ("Japan"),
        ("Jordan"),
        ("Kazakhstan"),
        ("Kenya"),
        ("Kuwait"),
        ("Kyrgystan"),
        ("Laos"),
        ("Latvia"),
        ("Lebanon"),
        ("Liberia"),
        ("Libya"),
        ("Liechtenstein"),
        ("Lithuania"),
        ("Luxembourg"),
        ("Macau"),
        ("Macedonia"),
        ("Madagascar"),
        ("Malawi"),
        ("Malaysia"),
        ("Maldives"),
        ("Mali"),
        ("Malta"),
        ("Marshall Islands"),
        ("Mauritania"),
        ("Mauritius"),
        ("Mexico"),
        ("Micronesia"),
        ("Moldova"),
        ("Monaco"),
        ("Mongolia"),
        ("Montenegro"),
        ("Morocco"),
        ("Mozambique"),
        ("Namibia"),
        ("Nauru"),
        ("Nepal"),
        ("New Zealand"),
        ("Nicaragua"),
        ("Nigeria"),
        ("North Korea"),
        ("Northern Ireland"),
        ("Norway"),
        ("Oman"),
        ("Pakistan"),
        ("Palau"),
        ("Panama"),
        ("Papua New Guinea"),
        ("Paragua"),
        ("Peru"),
        ("Philipines"),
        ("Poland"),
        ("Portugal"),
        ("Qatar"),
        ("Romania"),
        ("Russia"),
        ("Rwanda"),
        ("Saint Lucia"),
        ("Salvador"),
        ("Samoa"),
        ("San Marino"),
        ("Sao Tome"),
        ("Saudi Arabia"),
        ("Scottland"),
        ("Senegal"),
        ("Serbia"),
        ("Seychelles"),
        ("Sierra Leone"),
        ("Singapore"),
        ("Slovakia"),
        ("Slovenia"),
        ("Solomon Islands"),
        ("Somalia"),
        ("South Africa"),
        ("South Korea"),
        ("Spain"),
        ("Sri Lanka"),
        ("Sudan"),
        ("Suriname"),
        ("Swaziland"),
        ("Sweden"),
        ("Switzerland"),
        ("Syria"),
        ("Taiwan"),
        ("Tajikistan"),
        ("Tanzania"),
        ("Thailand"),
        ("Togo"),
        ("Tonga"),
        ("Trinidad and Tobago"),
        ("Tunisia"),
        ("Turkey"),
        ("Tuvalu"),
        ("Uganda"),
        ("Ukraine"),
        ("United Arab Emirates"),
        ("United Kingdom"),
        ("United States"),
        ("Uruguay"),
        ("Uzbekistan"),
        ("Venezuela"),
        ("Vietnam"),
        ("Wales"),
        ("Yemen"),
        ("Zambia"),
        ("Zimbabwe");

CREATE TABLE IF NOT EXISTS `teacher` (
	`teacherId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT,
	`genderId`	INTEGER,
	`nationalityId`	INTEGER,
	`address`	TEXT,
	`phoneNumber`	TEXT,
        `photo`         BLOB,
	FOREIGN KEY(`genderId`) REFERENCES gender(genderId),
        FOREIGN KEY(`nationalityId`) REFERENCES nationality(nationalityId)
);

CREATE TABLE IF NOT EXISTS `class` (
	`classId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`subjectId`	INTEGER,
	`classroomId`	INTEGER,
	FOREIGN KEY(`subjectId`) REFERENCES subject(subjectId),
	FOREIGN KEY(`classroomId`) REFERENCES classroom(classroomId)
);

CREATE TABLE IF NOT EXISTS `teacher_class` (
	`classId`	INTEGER,
	`teacherId`	INTEGER,
	FOREIGN KEY(`classId`) REFERENCES class(classId),
	FOREIGN KEY(`teacherId`) REFERENCES teacher(teacherId)
);

CREATE TABLE IF NOT EXISTS `enrollment` (
	`enrollmentId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`startDate`	TEXT,
	`graduateDate`	TEXT,
	`result`	TEXT
);

CREATE TABLE IF NOT EXISTS `test` (
	`testId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`subjectId`	INTEGER,
	`date`	TEXT,
	FOREIGN KEY(`subjectId`) REFERENCES subject(subjectId)
);

CREATE TABLE IF NOT EXISTS `student` (
	`studentId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL,
	`dateOfBirth`	TEXT,
	`genderId`	INTEGER,
	`nationalityId`	INTEGER,
	`passportNumber`	TEXT,
	`IDNumber`	TEXT,
	`address`	TEXT,
	`studentPhoneNumber`	TEXT,
	`studentEmail`	TEXT,
	`fathersPhoneNumber`	TEXT,
	`mothersPhoneNumber`	TEXT,
	`parentEmail`	TEXT,
	`gradeId`	INTEGER,
        `photo`         BLOB,
	`dormitoryId`	INTEGER,
	`enrollmentId`	INTEGER,
	`busstopId`	INTEGER,
	FOREIGN KEY(`genderId`) REFERENCES gender(genderId),
	FOREIGN KEY(`nationalityId`) REFERENCES nationality(nationalityId),
	FOREIGN KEY(`gradeId`) REFERENCES grade(gradeId),
	FOREIGN KEY(`dormitoryId`) REFERENCES dormitory(dormitoryId),
	FOREIGN KEY(`enrollmentId`) REFERENCES enrollment(enrollmentId),
	FOREIGN KEY(`busstopId`) REFERENCES bus_stop(busstopId)
);

CREATE TABLE IF NOT EXISTS `class_student` (
	`classId`	INTEGER,
	`studentId`	INTEGER,
	FOREIGN KEY(`classId`) REFERENCES class(classId),
	FOREIGN KEY(`studentId`) REFERENCES student(studentId)
);

CREATE TABLE IF NOT EXISTS `grade_score` (
	`studentId`	INTEGER NOT NULL,
	`subjectId`	INTEGER NOT NULL,
	`score`	TEXT,
	PRIMARY KEY(`studentId`,`subjectId`),
	FOREIGN KEY(`studentId`) REFERENCES `student`(`studentId`),
	FOREIGN KEY(`subjectId`) REFERENCES `subject`(`subjectId`)
);

CREATE TABLE IF NOT EXISTS `test_result` (
	`testId`	INTEGER,
	`studentId`	INTEGER,
	`result`	TEXT,
	FOREIGN KEY(`testId`) REFERENCES `test`(`testId`),
	FOREIGN KEY(`studentId`) REFERENCES `student`(`studentId`)
);
