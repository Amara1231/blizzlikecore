-- Copyright (C) 2011-2012 BlizzLikeCore <http://blizzlike.servegame.com/>
-- ---------------------------------------------------
-- BlizzLike Script to Remove MySQL User and Tables --
-- ---------------------------------------------------

REVOKE ALL PRIVILEGES ON * . * FROM 'blizzlike'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'blizzlike'@'localhost';
REVOKE GRANT OPTION ON `world` . * FROM 'blizzlike'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'blizzlike'@'localhost';
REVOKE GRANT OPTION ON `characters` . * FROM 'blizzlike'@'localhost';

REVOKE ALL PRIVILEGES ON `realmd` . * FROM 'blizzlike'@'localhost';
REVOKE GRANT OPTION ON `realmd` . * FROM 'blizzlike'@'localhost';

DROP USER 'blizzlike'@'localhost';

DROP DATABASE IF EXISTS `world` ;
DROP DATABASE IF EXISTS `characters` ;
DROP DATABASE IF EXISTS `realmd` ;