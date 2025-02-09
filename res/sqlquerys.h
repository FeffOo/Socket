const char TABLE_INIT[] = "CREATE TABLE users( id_user INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username CHAR(16) NOT NULL, passwd CHAR(16) NOT NULL, islogin BOOLEAN NOT NULL DEFAULT 0);";
string UPDATE_USER_STATUS = "UPDATE users SET islogin = 0 WHERE id_users = ?;";
string UsernameCheck = "SELECT COUNT(*) FROM users WHERE username = ?;";
string PasswdCheck = "SELECT COUNT(*) FROM passwd WHERE passwd = ?;";
