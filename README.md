# BSVS_Prak_G15


## Einleitung

In diesem Praktikum soll aus verschiedenen Komponenten in mehreren Schritten ein Serverprogramm in C Programmierung entstehen, in dem über eine Netzverbindung (Sockets) Daten von mehreren Clients abgelegt und abgefragt werden können. Die Clients sollen sich gleichzeitig per TCP verbinden können und mit einem gegebenen Befehlsset Daten auf den Server schreiben, bzw. abfragen oder löschen. Dabei sollen die Daten auf dem Server konsistent gehalten werden. Im Prinzip können Sie die Aufgabenstellung vergleichen mit Key-Value-Stores wie bspw. Redis oder Memcached. Wenn Sie entsprechende Wahlergänzungen implementieren können Sie Ihren Key-Value-Server später vielleicht in eigenen Projekten nutzen. Nutzen Sie zur Verwaltung des Source Codes in Ihrem Team Git!

Im Verlauf des Praktikums werden Sie diverse Aufgabenstellungen bearbeiten. Damit Ihnen der Blick auf die einzelnen Themenbereiche und die damit einhergehende Implementierung einfacher fällt, versuchen Sie die Aufgabenstellung wo möglich als eine eigenständige Systemkomponente zu betrachten, die auch außerhalb des Hauptprogramms lauffähig sein sollte. Sie können hierfür bspw. einfach ein neues Projekt erstellen, darin die nötige Teilaufgabe separat implementieren und bereits ihre grundlegende Funktionalität testen, und anschließend in Ihr Hauptprogramm übertragen. Bei den meisten der hier beschriebenen Aufgaben ist das möglich und es erleichtert Ihnen das Praktikum ungemein.
Handlungsfähig werden

Vor dem Bearbeiten der Aufgaben, müssen erst einmal einige Vorbereitungen getroffen werden. Die ersten Fingerübungen dienen der Installation der Entwicklungsumgebung, der Installation der Kompilierungsumgebung und der Konfiguration der Remote-Entwicklung.
Installation der CLion IDE (1. Voraussetzung)

Die erste Voraussetzung für das Absolvieren des Praktikums ist die richtige IDE. Das Tool, das wir einheitlich für das BS-Praktikum nutzen, lautet CLion (verfügbar über https://www.jetbrains.com/clion/). Mithilfe des Education-Programms von JetBrains (https://www.jetbrains.com/de-de/community/education/#students) können Sie deren Tools kostenlos nutzen. Melden Sie sich hierfür beim Bildungsprogramm von JetBrains an und installieren Sie anschließend CLion auf Ihrem Rechner. Sie können CLion entweder als StandAlone Programm installieren oder mithilfe der ToolBox von JetBrains. Wie Sie es machen, ist ganz Ihnen überlassen.
Docker als Plattform für eine auf Unix basierende Container VM installieren und aufsetzen (2. Voraussetzung)

Hier der Link zur Schritt-für-Schritt-Anleitung der Docker Installation  !!!Wichtig!!!
Remote Development Einstellungen in der CLion IDE (3. Voraussetzung)

Hier der Link zur Anleitung Remote Deployen und Debuggen mit CLion !!! Wichtig!!!
Git-Repo einrichten

Jedes Team sollte das eigene Git-Repo nutzen und den Code dort teilen. Insbesondere sollten von den Teammitgliedern regelmäßig die Arbeitsstände und Beiträge gepusht werden. Das Repository sollte ein CLion-Projekt (insb. C99, Files für cmake) enthalten.
C-Programm für die Basis des Servers

Der Basisteil des Praktikums besteht aus einigen grundlegenden Aufgaben, welche die wesentlichen Mechanismen des Systems abdecken sollen. 
Erstellen Sie vorab die Grundstruktur Ihres Programmes:
Die Main-File (main.c inkl. associated header main.h), das sämtliche Komponenten nutzt, selbst aber nur (soweit möglich) die main() als Funktion enthält.
Eine Datei für den Key-Value-Store inkl. associated Header-File (z. B. keyValStore.c/.h)
und eine Datei für die restlichen (allgemeinen) Subroutinen inkl. seiner Header-File (z. B. sub.c/.h).
Lagern sie, wo immer möglich, Teilaufgaben in in kleinere, übersichtliche Funktionen aus und legen sie diese, je nach Zuständigkeit, in eine der beiden C-Dateien
(keyValStore.c oder sub.c) zur Kompilierung ab. 
Datenhaltung als Grundlage

Implementieren Sie die Datenhaltung als Grundlage. Ihr Datenhaltungssystem sollte mindesten die Funktionen PUT, GET, DELETE bereitstellen. Die Funktionsaufrufe sollten sinnvoller Weise mit Call-by-Reference erfolgen. Die Funktionen könnten beispielsweise wie folgt lauten:
int put(char* key, char* value);
int get(char* key, char* res);
int del(char* key);
Funktionsbeschreibung

Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden, wird durch einen Rückgabewert <0 darauf aufmerksam gemacht.
Die put() Funktion soll eine Wert (value) mit dem Schlüsselwert (key) hinterlegen. Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden. Der Rückgabewert der Funktion könnte Auskunft dazu geben.
Die del() Funktion soll einen Schlüsselwert suchen und zusammen mit dem Wert aus der Datenhaltung entfernen.
Die Datenhaltung kann im Speicher z. B. in Arrays und Structs erfolgen.
Kommunikation mit Sockets

Implementieren Sie einen einfachen Socket-Server, den Sie mit Telnet als Client auf TCP-Port 5678 ansprechen können. Integrieren Sie die Funktionalität der Datenerhaltung, sodass die Funktionen in einem Telnet Client eingegeben und auf dem Server ausgeführt werden. Das Ergebnis soll wieder an den Telnet-Client zurückgegeben werden. Lassen Sie die Ein- und Ausgabe in einer Schleife laufen, so dass der Telnet-Client so viele Befehle wie gewünscht hintereinander eingeben kann. Verwenden Sie das Kommando "QUIT", damit die Eingabe und die Verbindung zum Client beendet wird.
Das Telnet Kommando muss folgende Struktur aufweisen:
[Befehl] [key] [value]
Mögliche Befehle: GET, PUT, DEL, QUIT
GET akzeptiert einen key und liefert den zugehörigen value in dem Format 'GET:key:value'. Ist der key unbekannt wird statt dem value der Fehler "key_nonexistent" ausgegeben.
PUT akzeptiert einen key und einen value. Der Befehl liefert das gespeicherte Paar im Folgenden Format zurück: 'PUT:key:value'
DEL akzeptiert einen key und löscht das Paar aus der Datenhaltung. War der key vorhanden, wird 'DEL:key:key_deleted' ausgegeben. War der key nicht vorhanden, wird 'DEL:key:key_nonexistent' ausgegeben.
QUIT beendet die Socket Verbindung und terminiert.
key und value akzeptieren alphanumerische Zeichen, keine Sonderzeichen.
Der key darf keine Leerzeichen enthalten.
Nachdem sich ein Telnet-Client verbunden hat, sollte die Nutzung des Servers am Client wie folgt aussehen:
GET key1
> GET:key1:key_nonexistent
PUT key1 value1
> PUT:key1:value1
PUT key2 value2
> PUT:key2:value2
PUT key1 value3
> PUT:key1:value3
DEL key2
> DEL:key2:key_deleted
DEL key2
> DEL:key2:key_nonexistent
GET key1
> GET:key1:value3
QUIT
Ein kurzes Video zur Demonstration

Das Port des Socket-Servers und IP-Adresse des remote host etc. können von der aktuellen Aufgabenstellung abweichen und sind nur
als Beispiel zu verstehen. Wenn es sich im aktuellen Fall um einen Docker Container handelt, der auf ihrem lokalen System läuft und
auf dem sie remote deployen, dann ist die IP-Adr. 127.0.0.1 bzw. localhost! 


 

Multiclientfähigkeit

Erweitern Sie das Programm ihres Socket-Servers, sodass statt einer Warteschlange bei der Socketverbindung für mehrere Clients, alle Clients gleichzeitig mit dem Server interagieren können. Überlegen Sie, wie Sie mit Prozessen und Shared Memory den Austausch der Daten im Key-Value-Store gestalten können
Transaktionen

Erweitern Sie die Teilaufgabe der konsistenten Datenerhaltung um exklusive Transaktionen. Einem Client soll alleiniger Zugriff auf den Key-Value-Store gegeben werden können. Es soll immer nur eine Transaktion auf dem Key-Value-Store stattfinden dürfen. Nutzen Sie hierfür den Befehl BEG, um eine Transaktion zu beginnen, und den Befehl END, um eine Transaktion zu beenden. Während ein Client exklusiven Zugriff auf den Key-Value-Store besitzt, dürfen andere Clients keinen Zugriff erhalten und müssen stattdessen warten. Weiterhin sollen aber auch nicht-exklusive Interaktionen möglich sein, wenn BEG und END nicht verwendet werden.
Pub/Sub

Realisieren Sie die Möglichkeit, dass ein Client sich auf Veränderung der Werte eines Schlüssels registrieren kann. Bieten Sie die Möglichkeit, dass sich Clients für einen Schlüsselwert "interessieren" können (Subscription). Sobald eine Änderung des Inhaltes für diesen Schlüssel durch einen anderen Client stattfindet (Publish), sollen alle verbundenen Clients mit dem Abonnement, durch den Server informiert werden. Subscriber erhalten die gleichen Ausgaben wie die Telnet Clients aus der Basisaufgabe "Kommunikation mit Sockets" (siehe Codeblock unten). Ein Client soll durch eine Subscription nicht blockiert werden, d. h. er soll sich beispielsweise auf mehrere Keys registrieren können. Man kann sich diese Aufgabe auch vorstellen wie einen Chat mit verschiedenen Chaträumen. Implementieren Sie hierfür eine Subscribe-Funktion, die Sie anschließend mit dem Befehl "SUB" in der Konsole aufrufen können (vergessen Sie nicht, dass Sie Ihrer Funktion einen Schlüssel übergeben müssen).
Client A
// Client A Anfang
 
 
 
SUB key1
> SUB:key1:value1
 
 
 
// Client B changed key1 to value2 (Das ist nur ein Kommentar für Sie und wird später nicht ausgegeben)
> PUT:key1:value2
 
 
// Client B deleted key1 (Das ist nur ein Kommentar für Sie und wird später nicht ausgegeben)
> DEL:key1:key_deleted
 
 
// Client A Ende

Client B
// Client B Anfang
 
PUT key1 value1
> PUT:key1:value1
 
 
PUT key1 value2
> PUT:key1:value2
 
 
 
DEL key1
> DEL:key1:key_deleted
 
 
 
 
// Client B Ende
Erweiterungen

Die Erweiterungen stellen optionale Aufgabenteile dar, die vertiefend betrachtet werden können, um das System durch weitere Funktionen zu verbessern und das eigene Wissen in dieser Materie zu erweitern. Sämtliche Inhalte der Erweiterungen sind klausurrelevant.
Asynchrone Operationen

Bieten Sie dem Client die Möglichkeit, weitere allgemeine Systembefehle auf die Daten anwenden zu können (also solche Programme und Befehle, die auch an der Shell funktionieren). Dabei soll der Client einen Befehle für einen Schlüssel übermitteln, die der Server mit dem Wert des Schlüssels asynchron ausführt. Achten Sie darauf, dass Ihre Daten konsistent bleiben (siehe Pflichtteil 2).

Ein Beispiel im Client könnte wie folgt aussehen:
Beispiel

PUT calculation 4 + 1
> PUT:calculation:4 + 1
OP calculation expr
> sending 4 + 1 to system call expr
GET calculation
> GET:calculation:5

Hinweis: für diesen Aufgabenteil benötigen Sie Warteschlangen, Pipes und Aufrufe aus der exec-Familie.
REST-Interface

Erstellen Sie eine HTTP-Interface, dass die Abfrage nicht nur per Kommunikation über Telnet, sondern auch per REST-Anfrage für GET, PUT und DELETE ermöglicht. Stellen Sie für HTTP-Kommunikation ggfs. einen gesonderten Port zur Verfügung. Testen Sie Ihren HTTP-Key-Value-Store beispielsweise mit curl oder einem REST-Client.  Achten Sie darauf, dass Ihre Daten konsistent bleiben (siehe Teilaufgabe: Konsistente Daten).
Wildcards

Ermöglichen Sie die Suche von mit Platzhaltern für die Befehle GET und DEL, damit mit einem einzigen Befehl auch mehrere, ähnliche Ergebnisse gefunden bzw. gelöscht werden können. Implementieren Sie dazu ein Schema wie bei regulären Ausdrücken oder in der Shell Sie können beispielsweise Sternchen ("*") und Fragezeichen nutzen ("?"), um mehrere bzw. genau ein Zeichen zu ersetzen. Ein Beispiel am Client könnte wie folgt aussehen:

PUT semop "atomic array of operations on a semaphore set"
> PUT:semop:"atomic array of operations on a semaphore set"
PUT semget "obtain a semaphore id"
> PUT:semget:"obtain a semaphore id"
PUT semctl "control operations on a semaphore set"
> PUT:semctl:"control operations on a semaphore set"
PUT fork "create a new process"
> PUT:fork:"create a new process"
 
GET sem*
> GET:sem*:"atomic array of operations on a semaphore set"
> GET:sem*:"obtain a semaphore id"
> GET:sem*:"control operations on a semaphore set"

Persistenz und Wiederherstellung der Datenstruktur in/aus Dateien

Ihr Server soll neu gestartet werden können, ohne dass Daten verloren gehen. Was passiert, wenn der Server mehrmals parallel läuft? Lassen Sie den Server die vorhandenen Daten dazu in Intervallen speichern, z.B. serialisiert in einer Datei. Prüfen Sie beim Start des Serverprogramms ob Persistierungsdaten vorhanden sind und wenn ja, nutzen Sie diese für die Initialisierung. Achten Sie darauf, dass Ihre Daten konsistent bleiben (siehe Basisteil).

Ersatz des Telnet-Clients durch eigene Anwendung

Schreiben Sie einen Socket-Client, der die Ein- und Ausgabefunktion des Telnet-Programms ersetzt und mindestens eine gleichwertige Funktionalität anbietet.
