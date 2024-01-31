/******************************************************************************/
/*                                                                            */
/* Ce code a ete modifie par Matthew Khouzam et Jerome Collin                 */
/* Pour le cours de INF1900                                                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                               memoire_24.cpp                               */
/*                                                                            */
/* Exemple de read sequentielle et aleatoire et d'eriture aleatoire et en  */
/* mode page en utilisant une memoire I2C 24LC256 avec l'interface materiel   */
/* d'un microcontroleur Atmel atmega16. Les broches d'adresses A0, A1 et A2   */
/* de la memoire sont reliees a la masse. SDA est relie a la broche PC1 du    */
/* microcontroleur, SCL a PC0 et WP n'est pas relie.                          */
/*                                                                            */
/* Le code de l'eeprom est : bits 7, 6, 5 et 4 = 1 0 1 0                      */
/* L'adresse physique est  : bits 3, 2, 1 = 0 0 0                             */
/* Le code d'write est   : bit 0 a 1 = read et bit 0 a 0 = write     */
/* Le code de controle est 0xa1 pour une read et 0xa0 pour une write    */
/*                                                                            */
/*  Pour les microcontroleurs Atmel, l'interface I2C est appelee TWI.         */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

#include "Memoire_24.hpp"

#ifndef F_CPU
/* fournir un avertissement mais non une erreur */
#warning "F_CPU pas defini pour 'memoire_24.cpp'"
#define F_CPU 8000000UL
#endif

uint8_t Memoire24CXXX::peripheral_address = 0xA0;

/******************************************************************************/
/* void Memoire24CXXX::Memoire24CXXX()                                        */
/*                                                                            */
/*      Constructeur: ajuste la taille de la page et procede a                */
/*                    l'initialisation                                        */
/*                                                                            */
/* Parametre d'entree  : aucun                                                */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
Memoire24CXXX::Memoire24CXXX()
    : PAGE_SIZE(128)
{
   init();
}

/******************************************************************************/
/* void Memoire24CXXX::~Memoire24CXXX()                                       */
/*                                                                            */
/*      Destructeur: ne fait rien                                             */
/*                                                                            */
/* Parametre d'entree  : aucun                                                */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
Memoire24CXXX::~Memoire24CXXX()
{
   // rien a faire...
}

/******************************************************************************/
/* void Memoire24CXXX::init(void)                                             */
/*                                                                            */
/*      Initialisation du port serie et de l'horloge de l'interface I2C       */
/*                                                                            */
/* Parametre d'entree  : aucun                                                */
/* Parametre de sortie : aucun                                                */
/******************************************************************************/
void Memoire24CXXX::init()
{
   choiceBlanc(0);
   // Initialisation de l'horloge de l'interface I2C
   TWSR = 0;
   // prediviseur
   TWBR = (F_CPU / 100000UL - 16) / 2;
}

/******************************************************************************/
/* uint8_t Memoire24CXXX::choiceBlanc(const uint8_t banc)                    */
/*                                                                            */
/*      Choisir un banc de memoire                                            */
/*                                                                            */
/* Parametre d'entree  : uint8_t banc - le banc de memoire a choisir          */
/* Parametre de sortie : uint8_t      - rv si c'est un succes, 255 si echec   */
/******************************************************************************/
uint8_t Memoire24CXXX::choiceBlanc(const uint8_t banc)
{
   uint8_t temp = banc & 0x03;
   uint8_t rv = 255;
   if (banc == temp)
   {
      Memoire24CXXX::peripheral_address = (0xA0 | (banc << 1));
      rv = Memoire24CXXX::peripheral_address;
   }
   return rv;
}

/******************************************************************************/
/*                read sequentielle de l'eeprom I2C                        */
/*                                                                            */
/* Le microcontroleur est en mode maitre. Il realise un acquittement (ACK) de */
/* la memoire a la fin de chaque read a l'exception de la derniere ou il   */
/* n'acquitte pas la reception (NACK) pour que la memoire place la ligne SDA  */
/* a un niveau haut et libere le bus et il transmet ensuite la condition      */
/* d'arret.                                                                   */
/*                                                                            */
/* a la premiere etape on verifie si le cycle d'write precedent est        */
/* termine. On transmet :                                                     */
/*   - La condition de depart                                                 */
/*   - Une donnee de controle : code de la memoire + adresse physique         */
/*                              + commande d'write                         */
/*   Si le cycle d'write precedent est en cours on recommence la sequence  */
/*                                                                            */
/* A la deuxieme etape on transmet :                                          */
/*   - La condition de depart                                                 */
/*   - Une donnee de controle : code de la memoire + adresses physique        */
/*                              + commande d'write                         */
/*   - L'adresse : poids fort suivi du poids faible                           */
/*                                                                            */
/* A la troisieme etape on transmet :                                         */
/*   - La condition de depart                                                 */
/*   - Une donnee de controle : code de la memoire + adresse physique         */
/*                              + commande de read                         */
/*                                                                            */
/* A la quatrieme etape on realise une read sequentielle :                 */
/*   - read en boucle - Commande de depart de transmission avec ACK,       */
/*                         attente de reception et read de la donnee       */
/*   - Derniere read  - Commande de depart de transmission avec NACK,      */
/*                         attente de reception et read de la donnee       */
/*                         Le NACK indique a la memoire la fin du transfert   */
/*   - Transmission de la condition d'arret                                   */
/*                                                                            */
/* Parametres d'entree  : uint16_t adresse - adresse de debut de read      */
/*                        int longueur     - nombre de donnees a retourner    */
/*                                           (variante de la 2eme procedure)  */
/* Parametres de sortie : uint8_t *donnee  - donnees lues                     */
/*                                                                            */
/******************************************************************************/
uint8_t Memoire24CXXX::read(const uint16_t adresse, uint8_t *donnee)
{
   uint8_t rv = 0;

   //______________ Attente de la fin d'un cycle d'write ______________
   for (;;)
   {
      TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
      while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
         ;

      TWDR = peripheral_address;       // controle - bit 0 a 0, write
      TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
         ;
      if (TWSR == 0x18) // 0x18 = cycle d'write termine
         break;
   }

   //_______________ Transmission de la condition de depart ________________
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
   while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address;       // Controle - bit 0 a 0, write
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________ Transmission du poids fort de l'adresse ________________
   TWDR = (adresse >> 8);           // 8 bits de poids fort de l'addresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_____________ Transmission du poids faible de l'adresse _______________
   TWDR = adresse;                  // 8 bits de poids faible de l'addresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R.�Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_______________ Transmission de la condition de depart ________________
   //  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);    // Condition de fin
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address + 1;   // Controle - bit 0 a 1 read
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //________________________ read de l'eeprom __________________________
   TWCR = _BV(TWINT) | _BV(TWEN);   // R.�Z., interrupt. - Depart de transm.+NACK
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;
   *donnee = TWDR;

   //________________ Transmission de la condition d'arret _________________
   TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
   return rv;
}

uint8_t Memoire24CXXX::read(const uint16_t adresse, uint8_t *donnee,
                            uint8_t longueur)
{
   uint8_t twcr;

   //______________ Attente de la fin d'un cycle d'write ______________
   for (;;)
   {
      TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
      while ((TWCR & _BV(TWINT)) == 0)
         ; // Attente de fin de transmission

      TWDR = peripheral_address;       // Controle - bit 0 a 0, write
      TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
         ;
      if (TWSR == 0x18) // 0x18 = cycle d'write termine
         break;
   }

   //_______________ Transmission de la condition de depart ________________
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
   while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address;       // Controle - bit 0 a 0, write
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________ Transmission du poids fort de l'adresse ________________
   TWDR = adresse >> 8;             // 8 bits de poids fort de l'addresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_____________ Transmission du poids faible de l'adresse _______________
   TWDR = adresse;                  // 8 bits de poids faible de l'addresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_______________ Transmission de la condition de depart ________________
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
   while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address + 1;   // Controle - bit 0 a 1, read
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //________________________ read de l'eeprom __________________________
   // La memoire transmet 8 bits de donnee et le recepteur transmet un
   // acquittement (ACK). Si c'est la derniere donnee le recepteur n'acquitte
   // pas la reception (NACK) et il transmet ensuite la condition de stop.
   // Le ACK est realisee par le recepteur en placant TWEA a 1 au lieu de le
   // laisser a 0.
   for (twcr = _BV(TWINT) | _BV(TWEN) | _BV(TWEA); longueur > 0; longueur--)
   {
      if (longueur == 1)
         twcr = _BV(TWINT) | _BV(TWEN); // Derniere donnee, NACK
      TWCR = twcr;                      // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0)
         ;              // Attente de fin de transmission
      *donnee++ = TWDR; // read
   }

   //________________ Transmission de la condition d'arret _________________
   TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

   return 0;
}

/******************************************************************************/
/*                                                                            */
/*      write d'un bloc de donnees en mode page dans l'eeprom I2C          */
/*                                                                            */
/* On ne peut ecrire qu'une seule page a la fois dans une eeprom et il faut   */
/* s'assurer de ne pas depasser cette limite pour eviter le repliement. Cette */
/* fonction se termine apres l'write d'un bloc de donnees dans une seule   */
/* page. On doit la rappeler plusieurs fois si la longueur d'un bloc de       */
/* donnees depasse les limites d'une page.                                    */
/*                                                                            */
/* Les memoires eeprom i2c ne generent pas de signal d'acquittement pendant   */
/* un cycle d'write. Pour s'assurer que l'eeprom est libre pour l'write */
/* d'une ou de plusieurs nouvelles donnees, on transmet en boucle une         */
/* condition de depart et un octet de controle d'write et on attend un     */
/* signal d'acquittement. On peut ensuite entreprendre la procedure           */
/* d'write. Cette verification est placee au debut de la fonction car le   */
/* temps d'acces permet a la condition de stop precedente de se completer.    */
/*                                                                            */
/* A la premiere, etape on calcule la longueur maximum que l'on peut placer   */
/* dans une page afin d'eviter le repliement dans l'write des donnees      */
/*                                                                            */
/* A la deuxieme etape, on verifie si le cycle d'write precedent est       */
/* termine. On transmet :                                                     */
/*   - La condition de depart                                                 */
/*   - Une donnee de controle : code de la memoire + adresse physique         */
/*                              + commande d'write                         */
/*   Si le cycle d'write precedent est en cours on recommence la sequence  */
/*                                                                            */
/* A la troisieme etape, on transmet :                                        */
/*   - La condition de depart                                                 */
/*   - Une donnee de controle : code de la memoire + adresse physique         */
/*                              + commande d'write                         */
/*                                                                            */
/* A la quatrieme etape, on ecrit la donnee :                                 */
/*   - Transmission de la donnee + commande de depart de transmission avec    */
/*     ACK et attente de fin de transmission.                                 */
/*   - Transmission de la condition d'arret pour demarrer le cycle d'write */
/*                                                                            */
/* Parametres d'entree  : uint16_t adresse - adresse de debut de read      */
/*                        uint8_t *donnee  - donnees a ecrire dans l'eeprom   */
/*                        int longueur     - longueur du bloc de donnees      */
/* Parametre de sortie  : uint8_t rv       - nombre de donnees ecrites        */
/*                                                                            */
/******************************************************************************/
uint8_t Memoire24CXXX::write(const uint16_t adresse, const uint8_t donnee)
{
   //______________ Attente de la fin d'un cycle d'write ______________
   for (;;)
   {
      TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
      while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
         ;

      TWDR = peripheral_address;       // Controle - bit 0 a 0, write
      TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
         ;

      if (TWSR == 0x18)
         break; // 0x18 = cycle d'write termine
   }

   //_______________ Transmission de la condition de depart ________________
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
   while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address;       // Controle - bit 0 a 0, write
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________ Transmission du poids fort de l'adresse ________________
   TWDR = adresse >> 8;             // 8 bits de poids fort de l'adresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_____________ Transmission du poids faible de l'adresse _______________
   TWDR = adresse;                  // 8 bits de poids faible de l'adresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________________ Transmission de la donnee ______________________
   TWDR = donnee;
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //________________ Transmission de la condition d'arret _________________
   TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); // Demarrage du cycle d'write

   return 0;
}

uint8_t Memoire24CXXX::write(const uint16_t adresse, uint8_t *donnee,
                             const uint8_t longueur)
{
   uint8_t rv;
   uint16_t copieAdresse = adresse;
   uint8_t copieLongueur = longueur;
   do
   {
      rv = writePage(copieAdresse, donnee, copieLongueur);
      copieAdresse += rv;  // On pointe une nouvelle page
      copieLongueur -= rv; // On soustrait la partie ecrite precedemment
      donnee += rv;        // On avance le pointeur de donnees
   } while (copieLongueur > 0);

   return 0;
}

uint8_t Memoire24CXXX::writePage(const uint16_t adresse, uint8_t *donnee,
                                 const uint8_t longueur)
{
   uint16_t addr_fin;
   uint8_t rv = 0;
   uint8_t copieLongueur = longueur;

   // Les operations suivantes permettent de tenir compte des limites
   // de grandeur d'une page afin d'eviter le repliement dans l'write
   // des donnees

   if (adresse + longueur < (adresse | (PAGE_SIZE - 1)))
      addr_fin = adresse + longueur;
   else
      addr_fin = (adresse | (PAGE_SIZE - 1)) + 1;
   copieLongueur = addr_fin - adresse;

   //______________ Attente de la fin d'un cycle d'write ______________
   for (;;)
   {
      TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
      while ((TWCR & _BV(TWINT)) == 0)
         ;                             // Attente de fin de transmission
      TWDR = peripheral_address;       // Controle - bit 0 a 0, write
      TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
         ;

      if (TWSR == 0x18)
         break; // 0x18 = cycle d'write termine
   }

   //_______________ Transmission de la condition de depart ________________
   TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Condition de depart
   while ((TWCR & _BV(TWINT)) == 0)            // Attente de fin de transmission
      ;

   //__________________ Transmission du code de controle ___________________
   TWDR = peripheral_address;       // Controle - bit 0 a 0, write
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________ Transmission du poids fort de l'adresse ________________
   TWDR = adresse >> 8;             // 8 bits de poids fort de l'adresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //_____________ Transmission du poids faible de l'adresse _______________
   TWDR = adresse;                  // 8 bits de poids faible de l'adresse
   TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
   while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
      ;

   //______________________ Transmission de la page ______________________
   for (; copieLongueur > 0; copieLongueur--)
   {
      TWDR = *donnee++;
      TWCR = _BV(TWINT) | _BV(TWEN);   // R. a Z., interrupt. - Depart de transm.
      while ((TWCR & _BV(TWINT)) == 0) // Attente de fin de transmission
         ;
      rv++; // Compteur de donnees
   }

   //________________ Transmission de la condition d'arrret _________________
   TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); // Demarrage du cycle d'write

   return rv;
}
