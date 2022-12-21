# Instructable

Een instructable is een stappenplan - zonder verdere uitleg - hoe je vertrekkend van de bill of materials en gebruik makend van de technische tekeningen de robot kan nabouwen. Ook de nodige stappen om de microcontroller te compileren en te uploaden staan beschreven.  

## bouwen van de auto

### stap 1
bestel alle componenten uit de bill of materials

### Stap 2
teken vooraan de linefollwer (een van de korte zeides) een rechthoek van 50 x 30 mm.

### Stap 3
Snij de rechthoek van 50x30 mm in een keer uit (als gewenst kunnen we voor hulp klijne gaaatjes boren op de interne hoeken van de rechthoek). 
LET OP:Gooi deze niet weg we gebruiken het later nog!

### Stap 4
Meet nu 120 mm af van de voorkant van de linefollower. duid deze plaats aan beide zijden aan.

### stap 5
Houd aan beide zeiden een bracke zo goed mogelijk in het midden van de heit lijntje uit stap 4 en duid de gaten van de bracket aan.

### stap 6
Boor nu gaten op de 4 aangeduide plaatsen uit stap 5

### stap7
Nu dat de printplaat klaar is bereiden we de componenten voor om te solderen. dit doen we door indien nodig de beentjes op de sensor, H-brug en spanningsomvormer te solderen.
HINT: Soldeer de pinnen zodanig dat de benaming altijd naar boven wijst.
LET OP: zorg dat de beentjes aan de andere kant zitten dan de sensoren op de array.

### stap 8
Plaats de esp32 redelijk dicht bij de voorkant maar zorg dat er nog zeker 2 draadjes tussen de esp en de uitgesneden rechthoek kunnen.
Soldeer deze vast op de printplaat

### stap 9
knip de male zijde van de female-male dupont draadjes we solderen de ooit male kant vast aan de 5V zijde op volgende pinnen: 2x 3V, 1x ground, 1x G34, 1x G35, 1x G32, 1x G33, 1x G25, 1x G26, 1x G27, 1x G14, 1x G12

### stap 10
verbind nu de pinnen led en vcc op de sensor met de dupont draadjes op 3V, de grounds met elkaar en verbind de sensoren in de volgorde die hierboven staat.

### stap 11
soldeer nu aan de kant van de USB poort de 5V omvormer.
LET OP: de USB ingang van de ESP 32 genoeg vrijblijft.

### stap 12
verbind de Vout van de omvormer met de 5V en de ground van de omvormer met een ground van de esp32.

### stap 13
Soldeer nu de h-brug helemaal achteraan de printplaat maar laat 2 gaten vrij op de printplaat. Zorg dat de ingangen van H-brug aan de kant van de ESP32 zijn.

### stap 14
Verbind nu de ingangen van de H-brug met de esp32 op volgende wijze: ground naar ground, Bin1 naar G19, Bin2 naar G18, Ain2 naar G5 en Ain1 naar G17.

### stap 15
Soldeer de 220 ohm weerstand aan de G23 pin en soldeer aan de andere pin van de weerstand de LED. we solderen dan de -pool van de LED aan een ground van de esp32.

### stap 16
soldeer rechts van de H brug (ground kant) alvast een 10K ohm weerstand

### stap 17
soldeer een kant van de weerstand aan de ground van de esp32 en de andere kant aan de G22 pin.

### stap 18
Bevestig nu de motoren aan de onderkant van de printplaat met de bijgeleverde bouten en moeren. Zorg ervoor dat de plus zijde van de motoren naar voor wijzen.
We verbinden de rechtste motor met Buit 1 en Buit 2 verbind de plus kant van de motor met de Buit 1. Doe hetzelfde voor de linker motor verander de B door de A kant van de H-brug.

### stap 19
Verbindt de negatieve pool (zwarte kabel) met de ground aan de uit kant van de h)brug en de ground van de spannings omvormer.
HINT: dit is het gemakelijkste met een tussenstap in de linsk achter hoek van de auto

### stap 20
Pak de rechthoek erbij die in stap 3 is uitgesneden en sij hem parrallel met de korte zijde in 2.

### stap 21
Boor in elk plaatje een gat in het eerste is het 4mm en in het tweede plaatje 7,5mm

### stap 22 
monteer op het 1 plaatje de schakelaar en op het tweede de drukknop

### stap 23
Verbind de positieve pool van de baterijhouder (rode draad) met een van de twee buitenste beentjes van de schakelaar.

### stap 24
verbind het middenste beentje van de schakelaar met de Vin  van de H-brug en de spanningsomvormer.
HINT: dit is het gemakelijkste met een tussenstap in de linsk achter hoek van de auto in de buurt van de ground

### stap 25
Plaats nu de baterij houder met de achterste baterij boven de motor as. We houden deze in de lucht met 2 kartonnenlatjes die we kunnen bevestigen op de printplaat met dubbelzijdeige plakband. plaats de baterijhouder met de plakand ook op de kartonetje

### stap 26
Verbind nu een van de beentjes van de zwarte knop met de 3V pin van de esp32 (doe dit naast de pinnen van de sensor.

### stap 27
verbind het andere beentje van de knop aan de 10K ohm weerstand maar doe dit aan de kant waar pin G22 met verbonden is.

### stap 28 
plak nu met dubbel zijdige tape de knoppen vast aan de achterkant van de printplaat.

## Uploaden van de code

### stap 29
download de het .ino bestand en de 2 libraries op github onder "finale code".

### stap 30
open het bestand in arduino ide.

### stap 31
maak de arduino omgeving compatible met esp32 door in arduino ide Bij File-prefrences deze link toe te voegen:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

### stap 32
kies vanboven in de arduino omgeving als microcontroler: "ESP32 dev module".
stel de bautrate in op 115600.

### stap 33
Download de arduino libraries die bovenaan de code staan

### stap 34
compileer de code door linsk vanboven op het vinkje te drukken.

### stap 35
als de code compileert kan deze geupload worden door naast het vinkje op het pijltje te duwen.
Lukt dit niet controleer dan nog eens ofdat de instellingen in arduino ide kloppen.

als alles juist gedaan is zou het autootje nu rechtdoor moeten rijden
