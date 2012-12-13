#pragma once

#define	SERVER_PORT				4242	// TODO: PAS ENCORE PRIS EN COMPTE
#define STRING_SEPARATOR		':'
#define MIN_NB_SEPARATOR_USER	2


enum ECommandId
{
/*
	ID commande			|   valeur du data dans la structure package    ||  valeurs de retour
*/
	CONNECT,			//	loginSTRING_SEPARATORmodDePasse				||	retourne un packet contenant un int avec les valeur decrites en dessous.
	SET_STATUS,			//	string du status							||	ne revoie rien. / TODO: broadcast le nouveau status a tout ceux qui l'ont ds les contacts ?
	GET_STATUS,			//  string login du User						||	retourne un packet avec la string du status
	NEW_SUBSCRIBER,		//	newLoginSTRING_SEPARATORmotDePasse			||	returne les meme valeurs que l'ajout d'un contact.
	START_CALL,			//	loginPeerSTRING_SEPARATORnbPort				||	retourne un packet avec la confirmation ou non de lancer un server sur le demandeur
	ADD_CONTACT,		//  loginNewContact								||	retourne un packet avec les valeurs de retour decrites en dessous.
	GET_CONTACTS,		//												||	retourne un packet avec tous les logins des contacts
	END_CALL			// pour dire au server que les 2 client son plus en converse
};

/*
-------- valeurs de retour: -------- 
ajout d'un contact:
	0:	login du demandeur invalide
	1:	success
	2:	login du contact non existant
	3:	login du contact deja dans la liste de contact de l'utilisateur

connexion:
	0:	login non existant
	1:	success
	2:	mauvais mot de passe.

nouveau compte:
	0:	login deja pris
	1:	success

start_call:
	0:	pas possible
	1:	ok pour lancer le serveur sur le port donne

*/

typedef struct
{
	int		cmdId;
	int		size;
	void	* data;
	
}		s_protocol;

