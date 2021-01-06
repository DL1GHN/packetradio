// ***************************************************************
// m_filter.prg zum Funkruf-Server
// Stand 15.10.2006  DH6BB
// Stand 2020-07-14 DL7NDR
// ***************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

// #define DEBUG
#define BCM                   					// <== Fuer die BayBox die "//" vor "#define" entfernen!!
#define Boxcall    "DB0XXX"				// <== A E N D E R N !!!  (ohne SSID)
#define Mailinfo   "/home/bcm/mailinfo"				// urspruenglich "/usr/local/funkruf/lib/mailinfo"

#define DAPNET_URL		"http://44.149.166.27:8080/calls"	// oder dapnet.db0sda.ampr.org:8080/calls oder via Internet: http://www.hampager.de:8080/calls
#define DAPNET_NAME		"dl7ndr"			// DAPNET-Accounts fÃ¼r Mailboxen werden nicht angelegt. Es mÃ¼ssen Personenaccounts verwendet werden.
#define DAPNET_PASSWORD	"passwortmeinesdapnetaccounts"

// #define KEPLER
#ifdef KEPLER
 #define KeplerCall   "CX2SA"
 #define KeplerRubrik "KEPS"
 #define KeplerTitel  "2Line"
 #define Keplerfile   "/usr/local/funkruf/lib/kepler.txt"
#endif

// ********* Ab hier nichts mehr aendern !!! *************
#define Version    0.26

#ifndef BCM
 #define DPBOX
#endif

void Mailerkennung(void);
void Funkruf(int);
void Sende(char [100]);
