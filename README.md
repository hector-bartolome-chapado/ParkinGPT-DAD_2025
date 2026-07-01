# ParkinGPT

Smart parking management system built as a team project for the Distributed Applications Design course at Universidad de Sevilla.

The project combines backend services, REST endpoints, MQTT messaging, database persistence and an ESP32/Arduino hardware component for sensor and actuator integration.

> [!NOTE]
> This is a fork of the original team repository. It is presented as collaborative academic work and keeps explicit author credits.

## Features

- Sensor and actuator registration linked to parking devices.
- Sensor data ingestion and persistence.
- Automatic range evaluation and actuator control.
- MQTT communication between hardware and backend services.
- REST API for CRUD and business logic.
- Postman collection for endpoint testing.
- ESP32/Arduino sketch for distance sensing and LED control.

## Architecture

```text
dad/
  src/main/java/
    mqtt/       MQTT client and event handling
    parkingpt/  main parking controller
    vertx/      REST endpoints and database access
ParkinGpt.ino   ESP32/Arduino sketch
parkingpt_db1.sql
ParkinGPT.postman_collection.json
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

Create the database using `parkingpt_db1.sql`.

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

## My Portfolio Focus

For interviews, this project is useful to discuss:

- Designing REST APIs around IoT entities.
- Combining MQTT events with backend state.
- Persisting sensor and actuator data in a relational database.
- Coordinating software and hardware parts of a distributed system.
- Testing APIs with Postman.

## Authors and Credits

- Juan Alvaro Pareja
- Marcos Guisado
- Hector Bartolome

Computer Engineering, Universidad de Sevilla.

