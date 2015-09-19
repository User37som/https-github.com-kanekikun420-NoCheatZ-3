#include <list>

#include "igameevents.h"

#ifdef GNUC
#undef min
#undef max
#endif

#include "Systems/BaseSystem.h"
#include "Systems/Logger.h"
#include "Systems/Testers/Detections/temp_BaseDetection.h"
#include "Hooks/PlayerRunCommandHookListener.h"
#include "Players/temp_PlayerDataStruct.h"
#include "Misc/temp_Singleton.h"
#include "Misc/IFaceManager.h"

#ifndef ShotTester_H
#define ShotTester_H

#define SHORT_TIME 0.04 // sec

typedef struct ShotStatHandler
{
	size_t n;
	double avg_time;
	double ratio;
} ShotStatHandlerT;

void TriggerStat(ShotStatHandlerT* handler);
void OutputStat(ShotStatHandlerT* handler);

typedef struct ShotStats
{
	double up_time; // Heure o� le bouton est appuy�
	double down_time; // Heure o� le bouton est rel�ch�
	ShotStatHandlerT clicks; // Nombre de click total
	ShotStatHandlerT short_clicks; // Nombre de click trop courts :
	ShotStatHandlerT with_hand;    // - D�sarm�
	ShotStatHandlerT with_pistol;  // - Avec un pistolet ou un fusil � pompe
	ShotStatHandlerT with_auto;    // - Avec une arme automatique
	ShotStatHandlerT on_target;    // - En visant un adversaire
	size_t row; // D�tections cons�cutives
	double last_detection; // Heure de la derni�re d�tection
} ShotStatsT;

class ShotTester :
	public BaseSystem,
	public Logger,
	public PlayerRunCommandHookListener,
	public PlayerDataStructHandler<ShotStatsT>,
	public Singleton<ShotTester>
{
public:
	ShotTester();
	virtual ~ShotTester();

	virtual void Load();
	virtual void Unload();
	virtual SlotStatus GetFilter();
	virtual bool PlayerRunCommandCallback(NczPlayer* player, CUserCmd* pCmd);
};

class ShotDetection : public LogDetection<ShotStats>
{
	typedef LogDetection<ShotStats> hClass;
public:
	ShotDetection() : hClass() {};
	~ShotDetection(){};

	virtual const char * GetDataDump();
	virtual const char * GetDetectionLogMessage()
	{
		return "ShotDetection";
	};
};

class Detection_TriggerBot : public ShotDetection
{
public:
	Detection_TriggerBot() : ShotDetection() {};
	~Detection_TriggerBot(){};

	virtual const char * GetDetectionLogMessage()
	{
		return "TriggerBot";
	};
};

class Detection_AutoPistol : public ShotDetection
{
public:
	Detection_AutoPistol() : ShotDetection() {};
	~Detection_AutoPistol(){};

	virtual const char * GetDetectionLogMessage()
	{
		return "AutoPistol";
	};
};

#endif
