CREATE TABLE IF NOT EXISTS `school` (
        `name`	TEXT DEFAULT "",
        `address`	TEXT DEFAULT "",
        `phone`	TEXT DEFAULT "",
        `email`	TEXT DEFAULT "",
        `logo`	BLOB
);

INSERT INTO `school` (
        `name`, `address`, `phone`, `email`, `logo`)
        VALUES (NULL, NULL, NULL, NULL, NULL);

CREATE TABLE IF NOT EXISTS `gender` (
	`genderId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `type`          TEXT NOT NULL UNIQUE
);

INSERT INTO `gender` (
	`type`)
	VALUES
	("Male"),
	("Female");

CREATE TABLE IF NOT EXISTS `user_type` (
	`userTypeId` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `type`       TEXT NOT NULL UNIQUE
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
        `name`          TEXT NOT NULL UNIQUE,
        `description`   TEXT
);

CREATE TABLE IF NOT EXISTS `grade` (
	`gradeId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `name`          TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `bus_stop` (
	`busstopId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `busstopName`	TEXT NOT NULL UNIQUE,
        `description`   TEXT
);

CREATE TABLE IF NOT EXISTS `subject` (
	`subjectId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`subjectName`	TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS `classroom` (
	`classroomId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        `classroomName`	TEXT NOT NULL UNIQUE,
        `description`   TEXT
);

CREATE TABLE IF NOT EXISTS `nationality` (
	`nationalityId`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`country`	TEXT NOT NULL UNIQUE
);

INSERT INTO `nationality` (
        `country`)
        VALUES
        (""),
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
        `name`	        TEXT,
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
        `gradeId`	INTEGER,
        `className`	TEXT,
	`subjectId`	INTEGER,
	`classroomId`	INTEGER,
	FOREIGN KEY(`subjectId`) REFERENCES subject(subjectId),
        FOREIGN KEY(`gradeId`) REFERENCES `grade`(`gradeId`),
	FOREIGN KEY(`classroomId`) REFERENCES classroom(classroomId)
);

CREATE TABLE IF NOT EXISTS `teacher_class` (
	`classId`	INTEGER,
	`teacherId`	INTEGER,
        PRIMARY KEY(`classId`,`teacherId`),
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
        `date`          TEXT,
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
        PRIMARY KEY(`classId`,`studentId`),
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

CREATE TABLE IF NOT EXISTS `attendance_type` (
        `typeId`        INTEGER PRIMARY KEY AUTOINCREMENT,
        `type` TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS `class_record` (
        `recordId` INTEGER PRIMARY KEY AUTOINCREMENT,
        `date` TEXT,
        `classId` INTEGER,
        `teacherId` INTEGER,
        FOREIGN KEY(`teacherId`) REFERENCES `teacher`(`teacherId`),
        FOREIGN KEY(`classId`) REFERENCES `class`(`classId`)
);

CREATE TABLE IF NOT EXISTS `attendance_record` (
        `class_record_id` INTEGER,
        `studentId` INTEGER,
        `attendance_type_id` INTEGER,
        FOREIGN KEY(`attendance_type_id`) REFERENCES `attendance_type`(`typeId`),
        FOREIGN KEY(`studentId`) REFERENCES `student`(`studentId`),
        PRIMARY KEY(`class_record_id`,`studentId`),
        FOREIGN KEY(`class_record_id`) REFERENCES `class_record`(`recordId`)
);

CREATE VIEW teacher_class_summary AS
SELECT C.classId, group_concat(T.name, ', ') AS 'teachers'
FROM teacher_class TC
LEFT OUTER JOIN class C ON C.classId = TC.classId
LEFT OUTER JOIN teacher T ON T.teacherId = TC.teacherId
GROUP BY TC.classId;

CREATE VIEW class_summary AS
SELECT C.classId, G.name AS 'grade', className, S.subjectName, CR.classroomName, TCS.teachers 'Teachers', count(DISTINCT CS.studentId) AS "Num Students"
FROM class C
LEFT OUTER JOIN class_student CS ON C.classId = CS.classId
LEFT OUTER JOIN subject S ON S.subjectId = C.subjectId
LEFT OUTER JOIN classroom CR ON CR.classroomId = C.classroomId
LEFT OUTER JOIN teacher_class TC ON TC.classId = C.classId
LEFT OUTER JOIN teacher_class_summary TCS ON TCS.classId = C.classId
LEFT OUTER JOIN grade G ON G.gradeId = C.gradeId
GROUP BY C.classId
ORDER BY G.name, className;

CREATE VIEW student_summary AS
SELECT studentId, S.name, GR.name AS 'Grade', type, country, IDNumber, studentPhoneNumber, D.name AS 'Dorm'
FROM student S
LEFT OUTER JOIN gender G on G.genderId = S.genderId
LEFT OUTER JOIN nationality N on N.nationalityId = S.nationalityId
LEFT OUTER JOIN dormitory D on D.dormitoryId = S.dormitoryId
LEFT OUTER JOIN grade GR ON GR.gradeId = S.gradeId
ORDER BY S.name;

CREATE VIEW teacher_summary AS
SELECT teacherId, name, type, country, address, phoneNumber
FROM teacher
LEFT OUTER JOIN gender ON gender.genderId = teacher.genderId
LEFT OUTER JOIN nationality ON nationality.nationalityId = teacher.nationalityId;

CREATE VIEW teacher_summary2 AS
SELECT TS.teacherId, TS.name, TS.type, TS.country, TS.address, TS.phoneNumber, group_concat(S.subjectName, ', ') AS classes
FROM teacher_summary TS
LEFT OUTER JOIN teacher_class TC ON TC.teacherId = TS.teacherId
LEFT OUTER JOIN class C ON C.classId = TC.classId
LEFT OUTER JOIN subject S ON C.subjectId = S.subjectId
GROUP BY TS.teacherId
ORDER BY TS.name;

CREATE VIEW class_record_summary AS
SELECT DISTINCT recordId, date, C.className, T.name, CS.'Num Students' AS 'students'
FROM class_record CR
LEFT OUTER JOIN class C on C.classId = CR.classId
LEFT OUTER JOIN teacher T on T.teacherId = CR.teacherId
LEFT OUTER JOIN class_summary CS ON CS.classId = CR.classId
ORDER BY date DESC, C.className;

CREATE VIEW attendance_summary AS
SELECT C.className 'Class', S.name 'Student', AT.type 'Status'
FROM attendance_record AR
LEFT OUTER JOIN student S ON S.studentId = AR.studentId
LEFT OUTER JOIN attendance_type AT ON AT.typeId = AR.attendance_type_id
LEFT OUTER JOIN class_record CR ON CR.recordId = AR.class_record_id
LEFT OUTER JOIN class C ON C.classId = CR.classId;
