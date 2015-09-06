#include <list>
#include "Players/NczPlayerManager.h"

#ifndef BASEFRAMEDTESTER
#define BASEFRAMEDTESTER

/////////////////////////////////////////////////////////////////////////
// BaseFramedTester
/////////////////////////////////////////////////////////////////////////

class BaseFramedTester
{
public:
	BaseFramedTester();
	virtual ~BaseFramedTester(){};

	/* Appel� par le plugin � chaque frame
	   Permet d'appeler les classes filles qui sont � l'�coute */
	static void OnFrame();

	/* Filtre du testeur, peut/doit �tre red�finit dans la classe fille */
	virtual SlotStatus GetFilter(){return PLAYER_CONNECTED;};

protected:
	/* Appel� par OnFrame, sert � i�trer entre les diff�rents joueurs en fonction du filtre */
	virtual void ProcessTests();

	/* Appel� par ProcessTests() lorsque le joueur correspond au filtre */
	virtual void ProcessPlayerTest(NczPlayer* player) = 0;

	/* Permet de se mettre � l'�coute de l'�v�nement, appel� par Load/Unload des testeurs */
	static void RegisterFramedTester(BaseFramedTester* tester);
	static void RemoveFramedTester(BaseFramedTester* tester);

private:
	static std::list<BaseFramedTester*> m_framedTestersList;
};

#endif
