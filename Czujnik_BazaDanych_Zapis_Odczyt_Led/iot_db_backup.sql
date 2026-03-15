-- MariaDB dump 10.19  Distrib 10.4.24-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: iot_db
-- ------------------------------------------------------
-- Server version	10.4.24-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tboard`
--

DROP TABLE IF EXISTS `tboard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tboard` (
  `idtBoard` int(11) NOT NULL AUTO_INCREMENT,
  `boardName` varchar(50) DEFAULT NULL,
  `deviceId` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idtBoard`),
  UNIQUE KEY `deviceId` (`deviceId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tboard`
--

LOCK TABLES `tboard` WRITE;
/*!40000 ALTER TABLE `tboard` DISABLE KEYS */;
INSERT INTO `tboard` VALUES (1,'Moja Plytka','arduDevId');
/*!40000 ALTER TABLE `tboard` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `treadings`
--

DROP TABLE IF EXISTS `treadings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `treadings` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `readDate` timestamp NOT NULL DEFAULT current_timestamp(),
  `value` float DEFAULT NULL,
  `unitType` varchar(10) DEFAULT NULL,
  `fkBoard` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fkBoard` (`fkBoard`),
  CONSTRAINT `treadings_ibfk_1` FOREIGN KEY (`fkBoard`) REFERENCES `tboard` (`idtBoard`)
) ENGINE=InnoDB AUTO_INCREMENT=65 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `treadings`
--

LOCK TABLES `treadings` WRITE;
/*!40000 ALTER TABLE `treadings` DISABLE KEYS */;
INSERT INTO `treadings` VALUES (1,'2026-03-15 09:33:39',23.8,'st. C',1),(2,'2026-03-15 09:33:39',49,'%',1),(3,'2026-03-15 09:33:50',23.8,'st. C',1),(4,'2026-03-15 09:33:50',48,'%',1),(5,'2026-03-15 09:34:00',23.7,'st. C',1),(6,'2026-03-15 09:34:00',47,'%',1),(7,'2026-03-15 09:34:10',23.8,'st. C',1),(8,'2026-03-15 09:34:10',48,'%',1),(9,'2026-03-15 09:34:20',23.7,'st. C',1),(10,'2026-03-15 09:34:20',46,'%',1),(11,'2026-03-15 09:34:30',23.8,'st. C',1),(12,'2026-03-15 09:34:30',47,'%',1),(13,'2026-03-15 09:34:40',23.7,'st. C',1),(14,'2026-03-15 09:34:40',47,'%',1),(15,'2026-03-15 09:34:50',23.7,'st. C',1),(16,'2026-03-15 09:34:50',47,'%',1),(17,'2026-03-15 09:35:00',23.7,'st. C',1),(18,'2026-03-15 09:35:00',47,'%',1),(19,'2026-03-15 09:35:10',23.8,'st. C',1),(20,'2026-03-15 09:35:10',48,'%',1),(21,'2026-03-15 09:35:20',23.8,'st. C',1),(22,'2026-03-15 09:35:20',48,'%',1),(23,'2026-03-15 09:35:30',23.8,'st. C',1),(24,'2026-03-15 09:35:30',48,'%',1),(25,'2026-03-15 09:35:40',23.8,'st. C',1),(26,'2026-03-15 09:35:40',48,'%',1),(27,'2026-03-15 09:35:51',23.8,'st. C',1),(28,'2026-03-15 09:35:51',47,'%',1),(29,'2026-03-15 09:36:01',23.9,'st. C',1),(30,'2026-03-15 09:36:01',48,'%',1),(31,'2026-03-15 09:36:11',23.9,'st. C',1),(32,'2026-03-15 09:36:11',47,'%',1),(33,'2026-03-15 09:36:21',23.9,'st. C',1),(34,'2026-03-15 09:36:21',47,'%',1),(35,'2026-03-15 09:36:31',23.9,'st. C',1),(36,'2026-03-15 09:36:31',49,'%',1),(37,'2026-03-15 09:36:41',23.9,'st. C',1),(38,'2026-03-15 09:36:41',49,'%',1),(39,'2026-03-15 09:36:51',23.9,'st. C',1),(40,'2026-03-15 09:36:51',50,'%',1),(41,'2026-03-15 09:37:01',23.9,'st. C',1),(42,'2026-03-15 09:37:01',49,'%',1),(43,'2026-03-15 09:37:11',23.9,'st. C',1),(44,'2026-03-15 09:37:11',49,'%',1),(45,'2026-03-15 09:37:21',23.9,'st. C',1),(46,'2026-03-15 09:37:21',48,'%',1),(47,'2026-03-15 09:37:31',23.8,'st. C',1),(48,'2026-03-15 09:37:31',47,'%',1),(49,'2026-03-15 09:37:41',23.8,'st. C',1),(50,'2026-03-15 09:37:41',48,'%',1),(51,'2026-03-15 09:37:51',23.9,'st. C',1),(52,'2026-03-15 09:37:51',48,'%',1),(53,'2026-03-15 09:38:01',23.9,'st. C',1),(54,'2026-03-15 09:38:01',48,'%',1),(55,'2026-03-15 09:38:12',23.9,'st. C',1),(56,'2026-03-15 09:38:12',48,'%',1),(57,'2026-03-15 09:38:22',23.9,'st. C',1),(58,'2026-03-15 09:38:22',48,'%',1),(59,'2026-03-15 09:38:32',23.9,'st. C',1),(60,'2026-03-15 09:38:32',48,'%',1),(61,'2026-03-15 09:38:42',23.8,'st. C',1),(62,'2026-03-15 09:38:42',49,'%',1),(63,'2026-03-15 09:38:52',23.8,'st. C',1),(64,'2026-03-15 09:38:52',48,'%',1);
/*!40000 ALTER TABLE `treadings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tresponses`
--

DROP TABLE IF EXISTS `tresponses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tresponses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `respFieldName` varchar(50) DEFAULT NULL,
  `value` int(11) DEFAULT NULL,
  `fkBoard` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fkBoard` (`fkBoard`),
  CONSTRAINT `tresponses_ibfk_1` FOREIGN KEY (`fkBoard`) REFERENCES `tboard` (`idtBoard`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tresponses`
--

LOCK TABLES `tresponses` WRITE;
/*!40000 ALTER TABLE `tresponses` DISABLE KEYS */;
INSERT INTO `tresponses` VALUES (1,'led_state',0,1);
/*!40000 ALTER TABLE `tresponses` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-03-15 10:51:47
