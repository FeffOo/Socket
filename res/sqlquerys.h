const char* dbLocalPath = "users.db";

const char* TABLE_INIT = "CREATE TABLE users(id_user INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username VARCHAR(16) NOT NULL, passwd VARCHAR(16) NOT NULL, islogin BOOLEAN NOT NULL DEFAULT 0);";
const char* UPDATE_USER_STATUS = "UPDATE users SET islogin = 0 WHERE id_users = ?;";
const char* UserLogCrd = "SELECT COUNT(*) FROM users WHERE username = ? AND passwd = ?;";
const char* UserRegistr = "INSERT INTO users(username passwd, isLogin) VALUES ( ? , ? , true);";

