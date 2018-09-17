# DTHACK18_MMF
DTHACK18_Team2

### TEAM

Tanja Hohenstatt ()

Ethan Arnold ()

Sandro Bühler ()

Emir Onuk ()

Markus Jakobs ()

Halil Coban ()

Weiling Xi ()

Friedl Lesch ()

### UI Design
![Page1](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page1.png?token=AaT2sxAD0FiASSnRGXm2sGrrawWVYFWKks5bqR4rwA%3D%3D)

![Page2](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page2.png)

![Page3](https://raw.githubusercontent.com/notagenius/DTHACK18_MMF/master/doc/Page3.png)

### Hardware
ESP8266

ESP32（Undertest） 

### Hardware Note
Board Manger: Esp8266 2.4.2

Board Choice: NodeMCU(ESP-12E Module)

Sample Code of Sniffer Mode: https://github.com/notagenius/dthack18

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

###
