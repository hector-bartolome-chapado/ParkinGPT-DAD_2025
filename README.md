# ParkinGPT

![Java](https://img.shields.io/badge/Java-Backend-ED8B00?logo=openjdk&logoColor=white)
![Vert.x](https://img.shields.io/badge/Vert.x-REST%20API-782A90)
![MQTT](https://img.shields.io/badge/MQTT-IoT%20Messaging-660066)
![MySQL](https://img.shields.io/badge/MySQL-Persistence-4479A1?logo=mysql&logoColor=white)
![Status](https://img.shields.io/badge/status-team%20academic%20project-blue)

Smart parking management system built as a team project for the Distributed Applications Design course at Universidad de Sevilla.

The project combines Java backend services, REST endpoints, MQTT messaging, relational persistence and an ESP32/Arduino hardware component for sensor and actuator integration.

> [!NOTE]
> This is a fork of the original team repository. It is presented as collaborative academic work and keeps explicit author credits.

## What It Does

ParkinGPT models an IoT parking scenario where sensors publish distance data, backend services persist and evaluate that data, and actuators react through MQTT messages.

The project is useful as a portfolio piece because it connects backend development with distributed communication and hardware integration.

## Core Features

- Sensor and actuator registration linked to parking devices.
- Sensor data ingestion and persistence.
- Automatic range evaluation and actuator control.
- MQTT communication between hardware and backend services.
- REST API for CRUD and business logic.
- Postman collection for endpoint testing.
- ESP32/Arduino sketch for distance sensing and LED control.

## Architecture

```text
ESP32 sensor
   |
   | MQTT
   v
Java backend / Vert.x REST API
   |
   v
MySQL persistence
   |
   v
Business logic -> actuator state -> MQTT command
```

## Repository Structure

```text
dad/
  src/main/java/
    mqtt/       MQTT client and event handling
    parkingpt/  parking controller and domain flow
    router/     API route composition
    types/      sensor, actuator and device models
    vertx/      REST endpoints and database access

ParkinGpt.ino                     ESP32/Arduino sketch
parkingpt_db1.sql                 database schema
ParkinGPT.postman_collection.json API testing collection
```

## Tech Stack

- Java
- Maven
- Vert.x
- MQTT / Mosquitto
- MySQL or MariaDB
- Postman
- ESP32 / Arduino

## Setup

Clone the repository:

```bash
git clone https://github.com/hector-bartolome-chapado/ParkinGPT-DAD_2025.git
cd ParkinGPT-DAD_2025
```

Create the database using:

```text
parkingpt_db1.sql
```

Set the database environment variables:

```bash
export DB_HOST=localhost
export DB_USER=your_user
export DB_PASS=your_password
```

Start an MQTT broker:

```bash
docker run -it -p 1883:1883 eclipse-mosquitto
```

Compile and run the Java backend from the Maven project folder:

```bash
cd dad
mvn clean compile exec:java -Dexec.mainClass=parkingpt.ParkingController
```

## Main REST Endpoints

CRUD endpoints:

- `/api/sensors`
- `/api/actuators`
- `/api/devices`
- `/api/groups`
- `/api/users`

Business logic endpoints:

- `POST /api/business/sensorData`
- `GET /api/business/sensorValues/:id_sensor/latest`
- `GET /api/business/actuatorStates/:id_actuator/latest`
- `GET /api/business/group/:id_grupo/sensorValues/latest`
- `GET /api/business/group/:id_grupo/actuatorStates/latest`

## MQTT Topics

| Purpose | Example topic |
| --- | --- |
| Sensor input | `grupo_1/canal_sensor` |
| Actuator control | `grupo_1/canal_actuador` |

Example sensor payload:

```json
{ "id_sensor": 1, "valor": 23.5 }
```

## ESP32 / Arduino Sketch

Open `ParkinGpt.ino` with the Arduino IDE and replace the placeholder Wi-Fi and broker values:

```cpp
const char* WIFI_SSID   = "YOUR_WIFI_SSID";
const char* WIFI_PASS   = "YOUR_WIFI_PASSWORD";
const char* MQTT_SERVER = "broker.hivemq.com";
```

The sensor publishes distances to `grupo_1/canal_sensor`. The actuator topic accepts commands such as `ON`, `OFF` and `AUTO`.

## Interview Talking Points

This project is useful to discuss:

- designing REST APIs around IoT entities;
- combining MQTT events with backend state;
- persisting sensor and actuator data in a relational database;
- coordinating software and hardware parts of a distributed system;
- testing APIs with Postman;
- documenting a team project honestly and clearly.

## Authors and Credits

- Juan Alvaro Pareja
- Marcos Guisado
- Hector Bartolome

Computer Engineering, Universidad de Sevilla.

## Portfolio

**Hector Bartolome Chapado**

Computer Engineering graduate, Universidad de Sevilla

- GitHub: [hector-bartolome-chapado](https://github.com/hector-bartolome-chapado)
- LinkedIn: [linkedin.com/in/infohbc](https://www.linkedin.com/in/infohbc/)
