/*
 * Web server esp8266 e-12
 * Controllo di 8 uscite digitali tramite smartphone o pc
 * By Vinz
 */

// Includo la libreria per il wifi
#include <ESP8266WiFi.h>

// Sostituire con l'SSID e la password della rete wifi
const char* ssid     = "ssid";
const char* password = "password";

// Imposto il webserver in ascolto sulla porta 80
WiFiServer server(80);

// Variabile in cui salvo le richieste HTTP
String header;

// Variabili in cui salvo lo stato delle uscite digitali
String output0State = "off";
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";

//Nome dei punti luce da accendere (es. luce cucina, luce salotto, lavatrice, ecc...)
String output0Name = "Led 1";
String output1Name = "Led 2";
String output2Name = "Led 3";
String output3Name = "Led 4";
String output4Name = "Led 5";
String output5Name = "Led 6";
String output6Name = "Led 7";
String output7Name = "Led 8";

// Associo le variabili alle uscite
const int output7 = D8;
const int output6 = D7;
const int output5 = D6;
const int output4 = D5;
const int output3 = D4;
const int output2 = D3;
const int output1 = D2;
const int output0 = D1;

void setup() {
  //Inizio la comunicazione seriale
  Serial.begin(115200);
  // Inizializzo gli output
  pinMode(output7, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output0, OUTPUT);
  // Imposto le uscite su 0
  digitalWrite(output7, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output1, LOW);
  digitalWrite(output0, LOW);

  // Connessione alla rete wifi
  Serial.print("Mi Connetto alla rete ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Mostro l'indirizzo IP nel monitor seriale
  Serial.println("");
  Serial.println("Connessione Wifi stabilita.");
  Serial.println("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Server in ascolto per i clients

  if (client) {                             // Se si collega un nuovo dispositivo
    Serial.println("Nuovo Client.");          // Mostro il messaggio nel monitor seriale
    String currentLine = "";                // creo una stringa in cui verranno salvati i dati in arrivo dal client
    while (client.connected()) {            // Eseguo un loop mentre il client è collegato
      if (client.available()) {             // se ci sono dei byte in arrivo dal client
        char c = client.read();             // leggo il valore
        Serial.write(c);                    // e lo stampo sul monitor seriale
        header += c;
        if (c == '\n') {                    // Se il byte è il carattere \n (new line)
          // se la riga corrente è vuota, ci sono due caratteri di nuova riga in una sola riga
          // questa è la fine della richiesta HTTP del client, quindi invio una risposta:
          if (currentLine.length() == 0) {
            // Codice di risposta HTTP (ad esempio HTTP / 1.1 200 OK) e content-type, infine chiuso la connesseione e stampo una riga vuota
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Uscita D0
            // Imposto l'uscita su 1 se ricevo la variabile GET=0/on
            if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            // se invece ricevo 0/off imposto l'uscita su low
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";
              digitalWrite(output0, LOW);

            // D1, come prima
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);

            // D2
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);

            // D3
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);

            // D4
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);

            // D5
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);

            // D6
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              digitalWrite(output6, HIGH);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
              digitalWrite(output6, LOW);

            // D7
            } else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 7 on");
              output7State = "on";
              digitalWrite(output7, HIGH);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 7 off");
              output7State = "off";
              digitalWrite(output7, LOW);
            }

            // Visualizzo la pagina HTML (Codice HTML e CSS per gli stili)
            // HEAD della pagina
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; /*display: inline-block;*/ margin: 0px auto; text-align: center;}");
            client.println(".block { width:30%; float:left; margin:1%}");
            client.println("@media only screen and (max-width: 600px) { .block { width:47%;} }");
            client.println("@media only screen and (max-width: 320px) { .block { width:98%;} }");
            client.println(".button { background-color: #ff0000; border: none; color: white; padding: 16px 40px; width:100%; box-sizing: border-box; text-decoration: none; font-size: 18px; margin: 0 auto; cursor: pointer;}");
            client.println(".button2 {background-color: #00ff00; color: #000}");
            client.println(".stato {display:block;font-size:12px;color:#efefef;}");
            client.println(".button2 .stato {color:#333;}");
            client.println(".clear {clear: both;}</style>");
            client.println("</head>");
            
            // Inizia contenuto vero e proprio della pagina
            client.println("<body>");
            
            // Visualizzo lo stato dell'uscita GPIO
            client.println("<div class=\"block\">");
            // se l'uscita è su HIGH visualizzo il bottone OFF, se l'uscita e LOW  visualizzo il bottone ON. Lo stato dell'uscita 0 è salvato nella variabile output0State, lo stesso vale per le altre uscite.
            if (output0State=="off") {;
              client.println("<p><a href=\"/0/on\"><button class=\"button\">"+output0Name+"<span class=\"stato\">Stato: " + output0State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">"+output0Name+"<span class=\"stato\">Stato: " + output0State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");    
            if (output1State=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">"+output1Name+"<span class=\"stato\">Stato: " + output1State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">"+output1Name+"<span class=\"stato\">Stato: " + output1State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");     
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">"+output2Name+"<span class=\"stato\">Stato: " + output2State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">"+output2Name+"<span class=\"stato\">Stato: " + output2State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");        
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">"+output3Name+"<span class=\"stato\">Stato: " + output3State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">"+output3Name+"<span class=\"stato\">Stato: " + output3State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");        
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">"+output4Name+"<span class=\"stato\">Stato: " + output4State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">"+output4Name+"<span class=\"stato\">Stato: " + output4State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");        
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">"+output5Name+"<span class=\"stato\">Stato: " + output5State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">"+output5Name+"<span class=\"stato\">Stato: " + output5State + "</span></button></a></p>");
            } 
            client.println("</div>");

            client.println("<div class=\"block\">");        
            if (output6State=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">"+output6Name+"<span class=\"stato\">Stato: " + output6State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">"+output6Name+"<span class=\"stato\">Stato: " + output6State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("<div class=\"block\">");   
            if (output7State=="off") {
              client.println("<p><a href=\"/7/on\"><button class=\"button\">"+output7Name+"<span class=\"stato\">Stato: " + output7State + "</span></button></a></p>");
            } else {
              client.println("<p><a href=\"/7/off\"><button class=\"button button2\">"+output7Name+"<span class=\"stato\">Stato: " + output7State + "</span></button></a></p>");
            }
            client.println("</div>");

            client.println("</body></html>");
               
            
            // La risposta HTTP termina con una ulteriore riga vuota
            client.println();
            // Interrompo il ciclo while
            break;
          } else { // se ricevo una nuova riga resetto la variabile currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // Se c'è un carattere diverso da \r (ritorno a capo)
          currentLine += c;      // lo aggiungo alla variabile currentLine
        }
      }
    }
    // Resetto la variabile
    header = "";
    // Chiudo la connessione e mostro un messaggio nel monitor seriale
    client.stop();
    Serial.println("Client disconnesso.");
    Serial.println("");
  }
}
