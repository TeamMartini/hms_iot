# IoT
빌리지의 정보를 수집하기 위한 IoT 기기 소프트웨어

## Env
| 환경  | 버전 |
|  -----  | --- |
| Node  | 15.5.0 |
| Node-RED | 1.3.3 |
| Arduino | 1.8.15 |
| ESP32 board Manager | 1.0.2 |
| Mosquitto | 2.0.10 |

## Install

레포지토리 설치
```shell
npm install -g node-red
```

실행
```
node-red
```

디바이스 설정 변경 시 esp32_mqtt_client_test.ino에서 ssid, password, mqtt_server, mqtt_user, mqtt_password 각자 환경에 맞게 변경
