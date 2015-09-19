#ifndef HELPERS
#define HELPERS

#include <iostream>
#include <string>
#include <locale>
#include <cstdarg>
#include <fstream>
#include <vector>
#include <sstream>
#undef min
#undef max
#include <algorithm>
#include <iterator>
#include <cmath>

#include "Preprocessors.h"
#include "Types.h"
#include "IFaceManager.h"
#include "temp_Singleton.h"
#include "edict.h"
#include "MRecipientFilter.h"

#ifdef WIN32
#	include "include_windows_headers.h"
#	include "TlHelp32.h"
#else
#	include <sys/types.h>
#	include <wchar.h>
#	include <dlfcn.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#endif

struct SigInst
{
	IFaceIndex base_mod;
	unsigned char* sig;
	const char* mask;
	size_t sig_len;
	size_t final_address_offset;
};

namespace Helpers
{
	/* Convertis une chaine de caract�res en caract�res minuscules */
	void toLowerCase(std::string &p_str);

	/* Envoie un message */
	void xMsg(const char *p_fmt, ...);

	/* V�rifie que 2 chaines de caract�res sont strictement identiques
	   Possibilit� de se servir de sz1 comme un buffer � l'aide de start_offset et length */
	bool bStrEq(const char *sz1, const char *sz2, size_t start_offset = 0, size_t length = 0xFFFFFFFF);

	/* M�me utilit� que bStrEq, sz1 est un buffer obligatoirement */
	bool bBytesEq(const char *sz1, const char *sz2, size_t start_offset, size_t length);

	/* M�me utilit� que bStrEq, n'est pas sensible � la casse */
	bool bStriEq(const char *sz1, const char *sz2, size_t start_offset = 0, size_t length = 0xFFFFFFFF);

	/* Ecrit dans le fichier de log. Doit �tre remplac� par une classe du m�me style que BanRequest */
	void writeToLogfile(const std::string &p_text);

	/* Retourne la date selon le format */
	std::string getStrDateTime(const char *p_format);

	/* Retourne le chemin absolu du dossier contenant le gameinfo.txt en cours */
	std::string getStrGameDir();


	edict_t * getEdictFromSteamID(const char *p_SteamID);
	int getIndexFromSteamID(const char *SteamID);
	//edict_t * PEntityOfEntIndex(const int p_iEntIndex);
	int getIndexFromUserID(const int p_userid);
	//int IndexOfEdict(const edict_t *p_pEdict);
	bool isValidEdict(const edict_t * p_entity);
	int GetPlayerCount();

	/* Permet d'avoir un format style C dans un conteneur C++ */
	std::string format(const char *fmt, ...);
	
	/* Retourne vrai si la valeur est impaire ... */
	bool isOdd(const int value);

	/* D�coupe une chaine de caract�re */
	void split(const std::string &p_s, char p_delim, std::vector<std::string> &elems);

	/* Conversion des chars vers std::string */
	template<typename T>
	std::string tostring(const T & p_toConvert);

	/* Retourne vrai si value est un entier ... (140.000, 1587.000 etc) */
	bool IsInt(double value);

	/* Envoie un message chat � tous les clients sauf pEntity */
	void noTell(const edict_t *pEntity, const std::string& msg);

	void chatmsg(const std::string& msg);

	/* Envoie un message chat � pEntity */
	void tell(edict_t *pEntity, const std::string& message);

	/* Aide au sigscan, retourne l'endroit qui est int�ressant dans la m�moire du module sinon 0 */
	const unsigned char * FastScan_Internal(SigInst instructions);

	/* Essaie de r�cup�rer m_EdictList si null */
	void FastScan_EntList();

	/* C'est la base ... */
	extern edict_t* m_EdictList;

	/* N'est pas utilis� */
	extern int m_edictCount;

	/* Ne doit pas �tre utilis� */
	extern int m_clientMax;
};

#endif
