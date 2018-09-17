# DTHACK18_Monitoring Mobility Flow 
Challenge 2: How can the city use WiFi monitoring to measure traffic flow and optimize planning (KPI: pedestrian, bicycle, car)?

### TEAM

![TEAM](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/3cover.png?token=AaT2s7tdwmyXaXVsgIav5kiJM2_7yUfhks5bqSSewA%3D%3D)

Tanja Hohenstatt ()

[Ethan Arnold](https://github.com/arnolde)

[Sandro Bühler](https://github.com/Sandro199)

[Emir Onuk](https://github.com/e-onux)

[Markus Jakobs](https://github.com/e-onux)

[Halil Coban](https://github.com/Halil234)

[Weiling Xi](https://github.com/notagenius)

[Friedl Lesch](https://github.com/Flesch-04-18)

### UI Design
![Page1](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page1.png?token=AaT2sxAD0FiASSnRGXm2sGrrawWVYFWKks5bqR4rwA%3D%3D)

![Page2](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page3.png?token=AaT2swaVur4cmjaOWsoKkrzr4Jh9sYp8ks5bqR8KwA%3D%3D)

![Page3](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page2.png?token=AaT2s2Re4cr6S7s6anKEo2IqtC7voelYks5bqR8JwA%3D%3D)

### Hardware
ESP8266

ESP32（Under testing） 

### Hardware Note
- Board Manger: Esp8266 2.4.2

- Board Choice: NodeMCU(ESP-12E Module)

- Sample Code of Sniffer Mode: https://github.com/notagenius/dthack18

- NTP: https://github.com/gmag11/NtpClient & http://yfrobot.com/thread-11881-1-1.html

- SNTP: with LUA https://nodemcu.readthedocs.io/en/master/en/modules/sntp/

### Server
PHP / MYSQL 

### Login in Server Notes 
Cloud Server for Storage of collected data: mmf.etadar.de

ssh login with root, after havin given Ethan your SSH key

### Emir Onuk's PHP MYSQL Rest API Tutorial
Emir Onuk sum up whole installation:

(you need php mysql web server)

- Install composer: https://getcomposer.org/download/

- Install Symfony into web server document root : https://symfony.com/doc/current/setup.html

- Install FOS Rest Api Bundle: https://symfony.com/doc/master/bundles/FOSRestBundle/1-setting_up_the_bundle.html

- Install JMS Serialize: http://jmsyst.com/bundles/JMSSerializerBundle

- Create a database table model codes: ./app/console generate:doctrine:entity

- Apply codes to generate database table: ./app/console doctrine:schema:update --force

- Generate controller: https://symfony.com/doc/master/bundles/SensioGeneratorBundle/commands/generate_controller.html

- Create methods as you can see here(Under "Getting records from database" title): https://www.cloudways.com/blog/rest-api-in-symfony-3-1/#crayon-5b9f0c72e1936746604741

- Composer: https://getcomposer.org/download/

### RISS Analysis

At the frequency of 1s per channel. ESP8266 got about 4 records of MAC sniffer when the object is in the range.
when the phone is active. 

![Page3](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/RISS_Chart.png?token=AaT2s1EQLUkzQ6sXIs1JrtkbdquFy4Qtks5bqSdjwA%3D%3D)

