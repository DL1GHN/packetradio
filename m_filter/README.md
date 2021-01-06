Stand 2020-07-14 DL7NDR

Hallo,

der beiliegende m_filter ist so angepasst, dass beim Eintreffen einer persönlichen Mail ein DAPNET-Funkruf zum DAPNET-Server geschickt wird.
Dieser wertet ihn aus und sendet dann über das DAPNET eine Pager-Nachricht an den jeweiligen Empfänger der Mail.

Vor dem MAKE bitte Folgendes ändern.

m_filter.h
#######
#define Boxcall		Mailboxrufzeichen ohne SSID
#define Mailinfo		ggf. das mailinfo-Verzeichnis anpassen

#define DAPNET_URL		URL des DAPNET-Servers, z. B.
			http://44.149.166.27:8080/calls
			dapnet.db0sda.ampr.org:8080/calls
			http://www.hampager.de:8080/calls

#define DAPNET_NAME		Rufzeichen eines DAPNET-Accounts (z. B. des Sysops)
#define DAPNET_PASSWORD	dem DAPNET-Account zugehöriges Passwort


m_filter.cpp
#########
Im Abschnitt "// Generiere den DAPNET-Funkruf-Befehl"

  strcat(curl_command, "\"], \"transmitterGroupNames\": [\"dl-bw\"], \"emergency\": false }' ");

Die Transmitter-Gruppe "dl-bw" (Deutschland-Baden-Württemberg) legt den Bereich der Aussendung der Nachricht fest.
Hiermit kann man verhindern, dass die Pager-Nachricht über alle DAPNET-Sender rausgeht.
http://dapnet.db0sda.ampr.org/#/transmitters/groups



Originaldateien mit Stand von DH6BB:
https://github.com/DecentralizedAmateurPagingNetwork/packetradio/


Fragen, Probleme?
PR-Mail: dl7ndr@db0lhr.#bw.deu.eu
HAMNET-Mail: dl7ndr@db0for.ampr.org

73
Daniel, dl7ndr


-------

Hallo OMs/YLs!
Hier der neue m_filter.prg, der auch Nachrichten der Rubrik P auswertet.

!!!!! Bitte unbedingt die "m_filter.h" aendern !!!!!!!!!!

Laeuft innerhalb der Baycom-Mailbox und der DP-Box!

Die Dateien "m_filter.h", "Makefile" und "m_filter.cpp" in ein Verzeichnis
kopieren und "make" eingeben. Es sollte jetzt (hoffentlich) ein "m_filter.prg"
rauskommen.
Diesen "m_filter.prg" dann in das richtige Verzeichnis kopieren (Siehe Doku
der jeweiligen Box!) und evtl. die config der Box anpassen!

Wird "DEBUG" in der "m_filter.h" definiert, bleibt nach abarbeiten der
Import-Nachricht eine "Export-Nachricht" im "Import-Verzeichnis" vom
Pager-User-Interface zurueck. Hier kann man sehen, ob evtl. Fehler aufgetreten
sind.

Kepler-Filer:
Im Funkruf-Benutzer-Interface besteht die Moeglichkeit AOS und LOS von
Satelliten berechnen zu lassen und diese dann auf dem Pager auszugeben.
Wichtig sind hierbei aktuelle Kepler-Daten. Der m_filer.prg kann diese
Kepler-Daten automatisch aus eingehenden Mails erkennen und dann kopieren.
Hierzu ist in der m_filter.h das "#define KEPLER" zu setzen und dann Absender-
Call, Titel und Pfadangabe evtl. anzupassen. Gross- und Kleinschreibung
beachten!!!

Bei Fragen oder Problemen bitte eine Mail an mich: dh6bb@db0whv.#nds.deu.eu
oder e-Mail: dh6bb@darc.de

73 de DH6BB
Jens



Support for Packet-Radio Mailbox Gateway for notification on DAPNET
Source of files: http://download.prgm.org/boxfiles/funkruf/

Infos about the files and their function from Marc-André:
````
> #define Mailinfo   "/usr/local/funkruf/lib/mailinfo"
> auf sich hat. Braucht man das? Schreibt da die Box was rein? Wenn ja, muss man das irgendwo anders hinlegen.

So sieht die aus:

root@db0uhi:/usr/local/funkruf/lib# cat mailinfo
DG8OP
DO1OFA
DO1OFM
DO1OFR
DO1OIM
DG9OBU
DJ2BF
...

Da sind alle Rufzeichen drin, die in der Funkruf-DB sind UND deren
MyBBS, also die Heimatbox, sich hier befindet. Er entscheidet mit
Hilfe dieser Liste ob er einen Funkruf erzeugt oder nicht, denn das
macht er nur für lokale User. Grund ist, weil "m_filter.prg" von der
BCM für jede eintreffende Mail, also auch die im Forward (!) aufgerufen
wird, und wir wollen keine Funkrufe für User erzeugen, die nicht hier
ihre MyBBS haben.

Ich lasse die BCM einmal am Tag per BCM-Cron ihre User herausschreiben:

root@db0uhi:/bcm# cat userlst.imp
export -u /bcm/userlist.lst u @=db0uhi

Das lasse ich auch beim Funkrufmaster machen, der kann seine DB in
Textform dumpen. Rufzeichen, die in beiden Listen vorkommen, wandern
in die mailinfo-Datei.

Ich habe das Zeug auf UHI gefunden, muss es nur mal herunterladen, ich
schicke das dann noch nach. Es ist ein bash-Script das den Abgleich
vornimmt und mailinfo generiert, nichts wildes, nur ein paar verschachtelte greps.
````
