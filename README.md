OMPSS-Controller
==============

Internetinio matematinio programavimo ir projektavimo serverius kontroliuojanti paslauga skirta *Ubuntu* operacinei
sistemai. Si paslauga buvo sukruta *OpenStack* debesies naudojimui taciau gali buti naudojama ir ne kaip debesies 
pslauga.

Diegimas:
--------------
Parsisiuskite projekta pasinaudoja zemiau pateikta komanda:

    git clone https://github.com/nereliz/OMPSS-Controller.git $dir

Tada sukurkite nuoroda i vydkomaji aplanka:

    sudo ln $dir/ompssc /etc/ompssc

Sekantis zingsnis sukurti nuoroda i *init.d* aplanka

    sudo ln /etc/ompss/init.d/opssc /etc/init.d/ompssc

**$dir** jusu pasiriktas aplankas

Sukurkite aplanka IP addresams saugoti

    sudo mkdir /etc/ompssc/ips
    
Sukurkite rinkmenas su OMPSS-Service serveriu adresais

    sudo touch /etc/ompssc/ips/$IP1
    sudo touch /etc/ompssc/ips/$IP2
    sudo touch /etc/ompssc/ips/$IPN
    
Paleiskite pasluga 

    sudo service ompssc start


Konfiguravimas:
--------------

Konfiguracijoms naudojama */etc/ompssc/config.ini* rinkmena.

Pastaba:
-------

Jeigu */etc/ompssc/ips* aplnkas neturi nei vienos IP rinkmenos paslauga nevykdoma.

Copyright (c) 2010 - 2013 Nerijus Barauskas

Projektas realizuotas kaip dalis baigimojo magistraturos darbo Siauliu Universitete.

