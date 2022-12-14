# Gebruiksaanwijzing

### opladen / vervangen batterijen
We kunnen de baterijen opladen door ze in een geschikte oplader te steken en wachten totdat ze opgeladen zijn. Als er geen geschikte oplader voor dat type baterijen gebruikt wordt moet er rekening worden gehouden met de maximum spanning van de 18650 baterijen (4,20V).
Tijdens gebruik van de linefollower moet er op gelet worden dat de spanning niet onder de minimale spanning van de baterijen gaat (2,5V).

Als de baterijen buiten de limieten (2,5V-4,7) ontladen of opladen kunnen deze kapot gaan. Dit kan zelfs lijden tot het in brand vliegen of zelfs ontploffen van de baterijen.

### draadloze communicatie
#### verbinding maken
Verbinding maken met de linefollower kan vanaf dat de baterijspanning aanstaat (blauwe schakelaar vanachter op de auto). Als deze aanstaat kan je de linefollwer terugvinden onder bluetooth aperaten las "lijnvolger" op de gekozen GSM/laptop. Eenmaal de linefollower en het apparaat verbonden zijn open we een serial monitor zodat er gecomuniceerd kan worden met de linefollower. Hieronder zien we alle mogelijke commandos die we kunnen doorsturen naar de linefollower. 

#### commando's
debug  
start  
stop  
set cycle [µs]  
set power [0..255]  
set diff [0..1]  
set kp [0..]  
set ki [0..]  
set kd [0..]  
calibrate black  
calibrate white  

### kalibratie
De linefollwer kan gecalibreerd worden in vier stappen:
  1. Plaats de line folower zodat de sensor enkel de zwarte lijn ziet of als mogelijk op een zwart gedrukt vlak op het papier.
  2. Dan wordt het commando "calibrate black" gestuurd naar de linefollower. Wacht totdat er "done" verschijnt in de seriele monitor.
  3. na zwart calibreren we wit door te zorgen dat de follwer sensor enkel boven het witte papier is.
  4. Als laatste sturen we het commando "calibrate white" gestuurd naar de linefollower. Wacht terug todat er "done" verschijnt in de seriele monitor.

Proficiat de linefollower is gecalibreerd.

### settings
De robot rijdt stabiel met volgende parameters:  

### start/stop button
De start/stop button is de zwarte knop die zich rechts vanachter op de linefollwer bevindt.
Deze zet de baterij spanning niet aan of uit maar deze stopt of start de werking van de motoren op de linefollower.


