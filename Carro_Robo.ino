#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
#include "esp_http_server.h"
#include "Arduino.h"


#define CAMERA_MODEL_AI_THINKER 
#include "camera_pins.h"


// Pinos do motor (ajuste conforme necessário)
#define MOTOR1_A 12  // Direção Motor A
#define MOTOR1_B 13
#define MOTOR2_A 14  // Direção Motor B
#define MOTOR2_B 15


const char* ssid = "Wifi-login";
const char* password = "password";
int flashOn = 0;

WebServer server(8080);

// Função para configurar a câmera
void startCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound()) {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Falha ao iniciar a câmera: 0x%x", err);
        return;
    }
}

//Funções de movimentação do carrinho

void moveForward() {
    digitalWrite(MOTOR1_A, HIGH);
    digitalWrite(MOTOR1_B, LOW);
    digitalWrite(MOTOR2_A, HIGH);
    digitalWrite(MOTOR2_B, LOW);
    server.send(200, "text/plain", "Forward");
    Serial.println("Frente");
}

void moveBackward() {
    digitalWrite(MOTOR1_A, LOW);
    digitalWrite(MOTOR1_B, HIGH);
    digitalWrite(MOTOR2_A, LOW);
    digitalWrite(MOTOR2_B, HIGH);
    server.send(200, "text/plain", "Backward");
    Serial.println("Trás");
}

void turnLeft() {
    digitalWrite(MOTOR1_A, LOW);
    digitalWrite(MOTOR1_B, LOW);
    digitalWrite(MOTOR2_A, HIGH);
    digitalWrite(MOTOR2_B, LOW);
    server.send(200, "text/plain", "Left");
    Serial.println("Esquerda");
}

void turnRight() {
    digitalWrite(MOTOR1_A, HIGH);
    digitalWrite(MOTOR1_B, LOW);
    digitalWrite(MOTOR2_A, LOW);
    digitalWrite(MOTOR2_B, LOW);
    server.send(200, "text/plain", "Right");
    Serial.println("Direita");
}

void stopCar() {
    digitalWrite(MOTOR1_A, LOW);
    digitalWrite(MOTOR1_B, LOW);
    digitalWrite(MOTOR2_A, LOW);
    digitalWrite(MOTOR2_B, LOW);
    server.send(200, "text/plain", "Stop");
    Serial.println("Parado");
}

void turnFlash() {
  if(flashOn == 0){
    digitalWrite(LED_GPIO_NUM,HIGH);
    flashOn = 1;
  }
  else if(flashOn == 1){
    digitalWrite(LED_GPIO_NUM,LOW);
    flashOn = 0;
  }

    server.send(200, "text/plain", "Flash");
    Serial.println("Flash ligado");
}

// Página de controle com vídeo ao vivo
// Onde esta server trocar pelo numero do servidor

void handleRoot(){
  server.send(200, "text/html",
"<!DOCTYPE html>"
"<html>"
"<head>"
"  <title>Robot Car Control</title>"
"  <style>"
"    body {"
"      font-family: Arial, sans-serif;"
"      background-color: #f4f4f4;"
"      margin: 0;"
"      padding: 0;"
"      display: flex;"
"      justify-content: center;"
"      align-items: center;"
"      min-height: 100vh;"
"    }"
    
"    .container {"
"      text-align: center;"
"      background-color: #fff;"
"      width: 100%;"
"      height: 100vh;"
"      display: flex;"
"      flex-direction: column;"
"      justify-content: flex-start;" 
"      align-items: center;"
"      padding: 10px;"
"      box-sizing: border-box;"
"    }"
    
"    h1 {"
"      font-size: 24px;"
"      margin: 10px 0;"
"    }"
    
"    .main-content {"
"      display: flex;"
"      flex-direction: row;" 
"      justify-content: center;"
"      align-items: center;"
"      gap: 20px;" 
"      width: 100%;"
"      height: calc(100vh - 80px);" 
"      padding: 10px;"
"      box-sizing: border-box;"
"    }"
    
"    .video-feed {"
"      flex: 1;" 
"      max-width: 60%;" 
"      height: 100%;"
"      display: flex;"
"      justify-content: center;"
"      align-items: center;"
"    }"
    
"    .video-feed img {"
"      width: 100%;"
"      height: 100%;"
"      max-height: 100%;" 
"      border-radius: 10px;"
"      object-fit: cover;" 
"      transform: rotate(180deg);"
"    }"
    
"    .controls {"
"      flex: 1;" 
"      max-width: 40%;" 
"      height: 100%;"
"      display: flex;"
"      flex-direction: column;"
"      justify-content: center;"
"      align-items: center;"
"      gap: 10px;"
"    }"
    
"    .d-pad {"
"      display: grid;"
"      grid-template-areas:"
"        '. forward .'"
"        'left . right'"
"        '. back .';"
"      gap: 10px;"
"    }"
    
"    .d-pad button {"
"      padding: 20px;"
"      font-size: 24px;"
"      border: none;"
"      border-radius: 10px;"
"      background-color: #007bff;"
"      color: #fff;"
"      cursor: pointer;"
"      display: flex;"
"      justify-content: center;"
"      align-items: center;"
"    }"
    
"    .d-pad button:hover {"
"      background-color: #0056b3;"
"    }"
    
"    #forward {"
"      grid-area: forward;"
"    }"
    
"    #left {"
"      grid-area: left;"
"    }"
    
"    #right {"
"      grid-area: right;"
"    }"
    
"    #back {"
"      grid-area: back;"
"    }"
    
"    #flash {"
"      padding: 20px;"
"      font-size: 24px;"
"      border: none;"
"      border-radius: 10px;"
"      background-color: #ffc107;"
"      color: yellow;"
"      cursor: pointer;"
"      display: flex;"
"      justify-content: center;"
"      align-items: center;"
"    }"
    
"    #flash:hover {"
"      background-color: #e0a800;"
"    }"
"  </style>"
"  <link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css'>"
"</head>"
"  <script>"
"    function sendCommand(command) { fetch(command); }"
"    document.addEventListener('DOMContentLoaded', function() {"
"      const buttons = { 'forward': '/forward', 'left': '/left', 'right': '/right', 'back': '/backward' };"
"      Object.keys(buttons).forEach(id => {"
"        let button = document.getElementById(id);"
"        button.addEventListener('mousedown', function(event) { sendCommand(buttons[id]); event.preventDefault(); });"
"        button.addEventListener('mouseup', function(event) { sendCommand('/stop'); event.preventDefault(); });"
"        button.addEventListener('touchstart', function(event) { sendCommand(buttons[id]); event.preventDefault(); });"
"        button.addEventListener('touchend', function(event) { sendCommand('/stop'); event.preventDefault(); });"
"      });"
"    });"
"  </script>"
"<body>"
"  <div class='container'>"
"    <div class='main-content'>"
"      <div class='video-feed'>"
"        <img src='http://server:8081/stream' alt='Live Video Feed'>"
"      </div>"
"      <div class='controls'>"
"        <div class='d-pad'>"
"          <button id='forward'><i class='fas fa-arrow-up'></i></button>"
"          <button id='left'><i class='fas fa-arrow-left'></i></button>"
"          <button id='right'><i class='fas fa-arrow-right'></i></button>"
"          <button id='back'><i class='fas fa-arrow-down'></i></button>"
"        </div>"
"        <button id='flash' onclick=\"fetch('/flash')\">"
"<i class='fas fa-lightbulb'></i></button>"
"      </div>"
"    </div>"
"  </div>"

"</body>"
"</html>"

  );

}


// Servidor de streaming
void startCameraServer();

void setup() {
    Serial.begin(115200);
    pinMode(LED_GPIO_NUM, OUTPUT);
    pinMode(MOTOR1_A, OUTPUT);
    pinMode(MOTOR1_B, OUTPUT);
    pinMode(MOTOR2_A, OUTPUT);
    pinMode(MOTOR2_B, OUTPUT);

    startCamera();

    WiFi.begin(ssid, password);
    Serial.print("Conectando ao Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConectado ao Wi-Fi!");
    Serial.print("Acesse: http://");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/forward", moveForward);
    server.on("/backward", moveBackward);
    server.on("/left", turnLeft);
    server.on("/right", turnRight);
    server.on("/stop", stopCar);
    server.on("/flash", turnFlash);

    
    server.begin();
    startCameraServer();
}

void loop() {
    server.handleClient();
}


httpd_handle_t stream_httpd = NULL;

esp_err_t stream_handler(httpd_req_t *req) {
    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    size_t _jpg_buf_len = 0;
    uint8_t *_jpg_buf = NULL;
    char *part_buf[64];

    res = httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");
    if (res != ESP_OK) {
        return res;
    }

    while (true) {
        fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Falha ao capturar a imagem");
            res = ESP_FAIL;
        } else {
            if (fb->format != PIXFORMAT_JPEG) {
                bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
                if (!jpeg_converted) {
                    Serial.println("Falha ao converter imagem para JPEG");
                    esp_camera_fb_return(fb);
                    res = ESP_FAIL;
                }
            } else {
                _jpg_buf_len = fb->len;
                _jpg_buf = fb->buf;
            }
        }

        if (res == ESP_OK) {
            size_t hlen = snprintf((char *)part_buf, 64, 
                "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %zu\r\n\r\n", 
                _jpg_buf_len);
            res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
        }

        if (res == ESP_OK) {
            res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
        }

        if (res == ESP_OK) {
            res = httpd_resp_send_chunk(req, "\r\n", 2);
        }

        if (fb) {
            esp_camera_fb_return(fb);
            _jpg_buf = NULL;
        }

        if (res != ESP_OK) {
            break;
        }
    }

    return res;
}

void startCameraServer() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 8081;

    httpd_uri_t uri_stream = {
        .uri       = "/stream",
        .method    = HTTP_GET,
        .handler   = stream_handler,
        .user_ctx  = NULL
    };

    if (httpd_start(&stream_httpd, &config) == ESP_OK) {
        httpd_register_uri_handler(stream_httpd, &uri_stream);
    }
}

