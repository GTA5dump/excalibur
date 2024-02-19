#include "pch.h"
#include "rage/classes/joaat.h"
#include "rage/classes/enums.h"
#include "rage/invoker/types.h"
#include "rage/classes/SyncTree.h"
#include "rage/classes/dataNodes.h"
#include "rage/classes/HashTable.h"
#include "rage/classes/CBaseModelInfo.h"
#include "rage/classes/CVehicleModelInfo.h"
#include "rage/classes/NetObject.h"
#include "rage/classes/CObject.h"
#include "rage/classes/CPed.h"
#include "rage/classes/fwArchetype.h"
#include "rage/classes/fwArchetypeDef.h"
#include "rage/engine.h"
#include "rage/classes/pools.h"
#include <array>

enum class eTaskTypeIndex
{
	CTaskHandsUp = 0,
	CTaskClimbLadder = 1,
	CTaskExitVehicle = 2,
	CTaskCombatRoll = 3,
	CTaskAimGunOnFoot = 4,
	CTaskMovePlayer = 5,
	CTaskPlayerOnFoot = 6,
	CTaskWeapon = 8,
	CTaskPlayerWeapon = 9,
	CTaskPlayerIdles = 10,
	CTaskAimGun = 12,
	CTaskComplex = 12,
	CTaskFSMClone = 12,
	CTaskMotionBase = 12,
	CTaskMove = 12,
	CTaskMoveBase = 12,
	CTaskNMBehaviour = 12,
	CTaskNavBase = 12,
	CTaskScenario = 12,
	CTaskSearchBase = 12,
	CTaskSearchInVehicleBase = 12,
	CTaskShockingEvent = 12,
	CTaskTrainBase = 12,
	CTaskVehicleFSM = 12,
	CTaskVehicleGoTo = 12,
	CTaskVehicleMissionBase = 12,
	CTaskVehicleTempAction = 12,
	CTaskPause = 14,
	CTaskDoNothing = 15,
	CTaskGetUp = 16,
	CTaskGetUpAndStandStill = 17,
	CTaskFallOver = 18,
	CTaskFallAndGetUp = 19,
	CTaskCrawl = 20,
	CTaskComplexOnFire = 25,
	CTaskDamageElectric = 26,
	CTaskTriggerLookAt = 28,
	CTaskClearLookAt = 29,
	CTaskSetCharDecisionMaker = 30,
	CTaskSetPedDefensiveArea = 31,
	CTaskUseSequence = 32,
	CTaskMoveStandStill = 34,
	CTaskComplexControlMovement = 35,
	CTaskMoveSequence = 36,
	CTaskAmbientClips = 38,
	CTaskMoveInAir = 39,
	CTaskNetworkClone = 40,
	CTaskUseClimbOnRoute = 41,
	CTaskUseDropDownOnRoute = 42,
	CTaskUseLadderOnRoute = 43,
	CTaskSetBlockingOfNonTemporaryEvents = 44,
	CTaskForceMotionState = 45,
	CTaskSlopeScramble = 46,
	CTaskGoToAndClimbLadder = 47,
	CTaskClimbLadderFully = 48,
	CTaskRappel = 49,
	CTaskVault = 50,
	CTaskDropDown = 51,
	CTaskAffectSecondaryBehaviour = 52,
	CTaskAmbientLookAtEvent = 53,
	CTaskOpenDoor = 54,
	CTaskShovePed = 55,
	CTaskSwapWeapon = 56,
	CTaskGeneralSweep = 57,
	CTaskPolice = 58,
	CTaskPoliceOrderResponse = 59,
	CTaskPursueCriminal = 60,
	CTaskArrestPed = 62,
	CTaskArrestPed2 = 63,
	CTaskBusted = 64,
	CTaskFirePatrol = 65,
	CTaskHeliOrderResponse = 66,
	CTaskHeliPassengerRappel = 67,
	CTaskAmbulancePatrol = 68,
	CTaskPoliceWantedResponse = 69,
	CTaskSwat = 70,
	CTaskSwatWantedResponse = 72,
	CTaskSwatOrderResponse = 73,
	CTaskSwatGoToStagingArea = 74,
	CTaskSwatFollowInLine = 75,
	CTaskWitness = 76,
	CTaskGangPatrol = 77,
	CTaskArmy = 78,
	CTaskShockingEventWatch = 80,
	CTaskShockingEventGoto = 82,
	CTaskShockingEventHurryAway = 83,
	CTaskShockingEventReactToAircraft = 84,
	CTaskShockingEventReact = 85,
	CTaskShockingEventBackAway = 86,
	CTaskShockingPoliceInvestigate = 87,
	CTaskShockingEventStopAndStare = 88,
	CTaskShockingNiceCarPicture = 89,
	CTaskShockingEventThreatResponse = 90,
	CTaskTakeOffHelmet = 92,
	CTaskCarReactToVehicleCollision = 93,
	CTaskCarReactToVehicleCollisionGetOut = 95,
	CTaskDyingDead = 97,
	CTaskWanderingScenario = 100,
	CTaskWanderingInRadiusScenario = 101,
	CTaskMoveBetweenPointsScenario = 103,
	CTaskChatScenario = 104,
	CTaskCowerScenario = 106,
	CTaskDeadBodyScenario = 107,
	CTaskSayAudio = 114,
	CTaskWaitForSteppingOut = 116,
	CTaskCoupleScenario = 117,
	CTaskUseScenario = 118,
	CTaskUseVehicleScenario = 119,
	CTaskUnalerted = 120,
	CTaskStealVehicle = 121,
	CTaskReactToPursuit = 122,
	CTaskHitWall = 125,
	CTaskCower = 126,
	CTaskCrouch = 127,
	CTaskMelee = 128,
	CTaskMoveMeleeMovement = 129,
	CTaskMeleeActionResult = 130,
	CTaskMeleeUpperbodyAnims = 131,
	CTaskMoVEScripted = 133,
	CTaskScriptedAnimation = 134,
	CTaskSynchronizedScene = 135,
	CTaskComplexEvasiveStep = 137,
	CTaskWalkRoundCarWhileWandering = 138,
	CTaskComplexStuckInAir = 140,
	CTaskWalkRoundEntity = 141,
	CTaskMoveWalkRoundVehicle = 142,
	CTaskReactToGunAimedAt = 144,
	CTaskDuckAndCover = 146,
	CTaskAggressiveRubberneck = 147,
	CTaskInVehicleBasic = 150,
	CTaskCarDriveWander = 151,
	CTaskLeaveAnyCar = 152,
	CTaskComplexGetOffBoat = 153,
	CTaskCarSetTempAction = 155,
	CTaskBringVehicleToHalt = 156,
	CTaskCarDrive = 157,
	CTaskPlayerDrive = 159,
	CTaskEnterVehicle = 160,
	CTaskEnterVehicleAlign = 161,
	CTaskOpenVehicleDoorFromOutside = 162,
	CTaskEnterVehicleSeat = 163,
	CTaskCloseVehicleDoorFromInside = 164,
	CTaskInVehicleSeatShuffle = 165,
	CTaskExitVehicleSeat = 167,
	CTaskCloseVehicleDoorFromOutside = 168,
	CTaskControlVehicle = 169,
	CTaskMotionInAutomobile = 170,
	CTaskMotionOnBicycle = 171,
	CTaskMotionOnBicycleController = 172,
	CTaskMotionInVehicle = 173,
	CTaskMotionInTurret = 174,
	CTaskReactToBeingJacked = 175,
	CTaskReactToBeingAskedToLeaveVehicle = 176,
	CTaskTryToGrabVehicleDoor = 177,
	CTaskGetOnTrain = 178,
	CTaskGetOffTrain = 179,
	CTaskRideTrain = 180,
	CTaskMountThrowProjectile = 190,
	CTaskGoToCarDoorAndStandStill = 195,
	CTaskMoveGoToVehicleDoor = 196,
	CTaskSetPedInVehicle = 197,
	CTaskSetPedOutOfVehicle = 198,
	CTaskVehicleMountedWeapon = 199,
	CTaskVehicleGun = 200,
	CTaskVehicleProjectile = 201,
	CTaskSmashCarWindow = 204,
	CTaskMoveGoToPoint = 205,
	CTaskMoveAchieveHeading = 206,
	CTaskMoveFaceTarget = 207,
	CTaskComplexGoToPointAndStandStillTimed = 208,
	CTaskMoveGoToPointAndStandStill = 208,
	CTaskMoveFollowPointRoute = 209,
	CTaskMoveSeekEntity_CEntitySeekPosCalculatorStandard = 210,
	CTaskMoveSeekEntity_CEntitySeekPosCalculatorLastNavMeshIntersection = 211,
	CTaskMoveSeekEntity_CEntitySeekPosCalculatorLastNavMeshIntersection2 = 212,
	CTaskMoveSeekEntity_CEntitySeekPosCalculatorXYOffsetFixed = 213,
	CTaskMoveSeekEntity_CEntitySeekPosCalculatorXYOffsetFixed2 = 214,
	CTaskExhaustedFlee = 215,
	CTaskGrowlAndFlee = 216,
	CTaskScenarioFlee = 217,
	CTaskSmartFlee = 218,
	CTaskFlyAway = 219,
	CTaskWalkAway = 220,
	CTaskWander = 221,
	CTaskWanderInArea = 222,
	CTaskFollowLeaderInFormation = 223,
	CTaskGoToPointAnyMeans = 224,
	CTaskTurnToFaceEntityOrCoord = 225,
	CTaskFollowLeaderAnyMeans = 226,
	CTaskFlyToPoint = 228,
	CTaskFlyingWander = 229,
	CTaskGoToPointAiming = 230,
	CTaskGoToScenario = 231,
	CTaskSeekEntityAiming = 233,
	CTaskSlideToCoord = 234,
	CTaskSwimmingWander = 235,
	CTaskMoveTrackingEntity = 237,
	CTaskMoveFollowNavMesh = 238,
	CTaskMoveGoToPointOnRoute = 239,
	CTaskEscapeBlast = 240,
	CTaskMoveWander = 241,
	CTaskMoveBeInFormation = 242,
	CTaskMoveCrowdAroundLocation = 243,
	CTaskMoveCrossRoadAtTrafficLights = 244,
	CTaskMoveWaitForTraffic = 245,
	CTaskMoveGoToPointStandStillAchieveHeading = 246,
	CTaskMoveGetOntoMainNavMesh = 251,
	CTaskMoveSlideToCoord = 252,
	CTaskMoveGoToPointRelativeToEntityAndStandStill = 253,
	CTaskHelicopterStrafe = 254,
	CTaskGetOutOfWater = 256,
	CTaskMoveFollowEntityOffset = 259,
	CTaskFollowWaypointRecording = 261,
	CTaskMotionPed = 264,
	CTaskMotionPedLowLod = 265,
	CTaskHumanLocomotion = 268,
	CTaskMotionBasicLocomotionLowLod = 269,
	CTaskMotionStrafing = 270,
	CTaskMotionTennis = 271,
	CTaskMotionAiming = 272,
	CTaskBirdLocomotion = 273,
	CTaskFlightlessBirdLocomotion = 274,
	CTaskFishLocomotion = 278,
	CTaskQuadLocomotion = 279,
	CTaskMotionDiving = 280,
	CTaskMotionSwimming = 281,
	CTaskMotionParachuting = 282,
	CTaskMotionDrunk = 283,
	CTaskRepositionMove = 284,
	CTaskMotionAimingTransition = 285,
	CTaskThrowProjectile = 286,
	CTaskCover = 287,
	CTaskMotionInCover = 288,
	CTaskAimAndThrowProjectile = 289,
	CTaskGun = 290,
	CTaskAimFromGround = 291,
	CTaskAimGunVehicleDriveBy = 295,
	CTaskAimGunScripted = 296,
	CTaskReloadGun = 298,
	CTaskWeaponBlocked = 299,
	CTaskEnterCover = 300,
	CTaskExitCover = 301,
	CTaskAimGunFromCoverIntro = 302,
	CTaskAimGunFromCoverOutro = 303,
	CTaskAimGunBlindFire = 304,
	CTaskCombatClosestTargetInArea = 307,
	CTaskCombatAdditionalTask = 308,
	CTaskInCover = 309,
	CTaskAimSweep = 313,
	CTaskSharkCircle = 319,
	CTaskSharkAttack = 320,
	CTaskAgitated = 321,
	CTaskAgitatedAction = 322,
	CTaskConfront = 323,
	CTaskIntimidate = 324,
	CTaskShove = 325,
	CTaskShoved = 326,
	CTaskCrouchToggle = 328,
	CTaskRevive = 329,
	CTaskParachute = 335,
	CTaskParachuteObject = 336,
	CTaskTakeOffPedVariation = 337,
	CTaskCombatSeekCover = 340,
	CTaskCombatFlank = 342,
	CTaskCombat = 343,
	CTaskCombatMounted = 344,
	CTaskMoveCircle = 345,
	CTaskMoveCombatMounted = 346,
	CTaskSearch = 347,
	CTaskSearchOnFoot = 348,
	CTaskSearchInAutomobile = 349,
	CTaskSearchInBoat = 350,
	CTaskSearchInHeli = 351,
	CTaskThreatResponse = 352,
	CTaskInvestigate = 353,
	CTaskStandGuardFSM = 354,
	CTaskPatrol = 355,
	CTaskShootAtTarget = 356,
	CTaskSetAndGuardArea = 357,
	CTaskStandGuard = 358,
	CTaskSeparate = 359,
	CTaskStayInCover = 360,
	CTaskVehicleCombat = 361,
	CTaskVehiclePersuit = 362,
	CTaskVehicleChase = 363,
	CTaskDraggingToSafety = 364,
	CTaskDraggedToSafety = 365,
	CTaskVariedAimPose = 366,
	CTaskMoveWithinAttackWindow = 367,
	CTaskMoveWithinDefensiveArea = 368,
	CTaskShootOutTire = 369,
	CTaskShellShocked = 370,
	CTaskBoatChase = 371,
	CTaskBoatCombat = 372,
	CTaskBoatStrafe = 373,
	CTaskHeliChase = 374,
	CTaskHeliCombat = 375,
	CTaskSubmarineCombat = 376,
	CTaskSubmarineChase = 377,
	CTaskPlaneChase = 378,
	CTaskTargetUnreachable = 379,
	CTaskTargetUnreachableInInterior = 380,
	CTaskTargetUnreachableInExterior = 381,
	CTaskStealthKill = 382,
	CTaskWrithe = 383,
	CTaskAdvance = 384,
	CTaskCharge = 385,
	CTaskMoveToTacticalPoint = 386,
	CTaskToHurtTransit = 387,
	CTaskAnimatedHitByExplosion = 388,
	CTaskNMRelax = 389,
	CTaskNMPose = 391,
	CTaskNMBrace = 392,
	CTaskNMBuoyancy = 393,
	CTaskNMInjuredOnGround = 394,
	CTaskNMShot = 395,
	CTaskNMHighFall = 396,
	CTaskNMBalance = 397,
	CTaskNMElectrocute = 398,
	CTaskNMPrototype = 399,
	CTaskNMExplosion = 400,
	CTaskNMOnFire = 401,
	CTaskNMScriptControl = 402,
	CTaskNMJumpRollFromRoadVehicle = 403,
	CTaskNMFlinch = 404,
	CTaskNMSit = 405,
	CTaskNMFallDown = 406,
	CTaskBlendFromNM = 407,
	CTaskNMControl = 408,
	CTaskNMDangle = 409,
	CTaskNMGenericAttach = 412,
	CTaskNMDraggingToSafety = 414,
	CTaskNMThroughWindscreen = 415,
	CTaskNMRiverRapids = 416,
	CTaskNMSimple = 417,
	CTaskRageRagdoll = 418,
	CTaskJumpVault = 421,
	CTaskJump = 422,
	CTaskFall = 423,
	CTaskReactAimWeapon = 425,
	CTaskChat = 426,
	CTaskMobilePhone = 427,
	CTaskReactToDeadPed = 428,
	CTaskSearchForUnknownThreat = 430,
	CTaskBomb = 432,
	CTaskDetonator = 433,
	CTaskAnimatedAttach = 435,
	CTaskCutScene = 441,
	CTaskReactToExplosion = 442,
	CTaskReactToImminentExplosion = 443,
	CTaskDiveToGround = 444,
	CTaskReactAndFlee = 445,
	CTaskSidestep = 446,
	CTaskCallPolice = 447,
	CTaskReactInDirection = 448,
	CTaskReactToBuddyShot = 449,
	CTaskVehicleGoToAutomobileNew = 454,
	CTaskVehicleGoToPlane = 455,
	CTaskVehicleGoToHelicopter = 456,
	CTaskVehicleGoToSubmarine = 457,
	CTaskVehicleGoToBoat = 458,
	CTaskVehicleGoToPointAutomobile = 459,
	CTaskVehicleGoToPointWithAvoidanceAutomobile = 460,
	CTaskVehiclePursue = 461,
	CTaskVehicleRam = 462,
	CTaskVehicleSpinOut = 463,
	CTaskVehicleApproach = 464,
	CTaskVehicleThreePointTurn = 465,
	CTaskVehicleDeadDriver = 466,
	CTaskVehicleCruiseNew = 467,
	CTaskVehicleCruiseBoat = 468,
	CTaskVehicleStop = 469,
	CTaskVehiclePullOver = 470,
	CTaskVehiclePassengerExit = 471,
	CTaskVehicleFlee = 472,
	CTaskVehicleFleeAirborne = 473,
	CTaskVehicleFleeBoat = 474,
	CTaskVehicleFollowRecording = 475,
	CTaskVehicleFollow = 476,
	CTaskVehicleBlock = 477,
	CTaskVehicleBlockCruiseInFront = 478,
	CTaskVehicleBlockBrakeInFront = 479,
	CTaskVehicleBlockBackAndForth = 478,
	CTaskVehicleCrash = 481,
	CTaskVehicleLand = 482,
	CTaskVehicleLandPlane = 483,
	CTaskVehicleHover = 484,
	CTaskVehicleAttack = 485,
	CTaskVehicleAttackTank = 486,
	CTaskVehicleCircle = 487,
	CTaskVehiclePoliceBehaviour = 488,
	CTaskVehiclePoliceBehaviourHelicopter = 489,
	CTaskVehiclePoliceBehaviourBoat = 490,
	CTaskVehicleEscort = 491,
	CTaskVehicleHeliProtect = 492,
	CTaskVehiclePlayerDriveAutomobile = 494,
	CTaskVehiclePlayerDriveBike = 495,
	CTaskVehiclePlayerDriveBoat = 496,
	CTaskVehiclePlayerDriveSubmarine = 497,
	CTaskVehiclePlayerDriveSubmarineCar = 498,
	CTaskVehiclePlayerDriveAmphibiousAutomobile = 499,
	CTaskVehiclePlayerDrivePlane = 500,
	CTaskVehiclePlayerDriveHeli = 501,
	CTaskVehiclePlayerDriveAutogyro = 502,
	CTaskVehiclePlayerDriveDiggerArm = 503,
	CTaskVehiclePlayerDriveTrain = 504,
	CTaskVehiclePlaneChase = 505,
	CTaskVehicleNoDriver = 506,
	CTaskVehicleAnimation = 507,
	CTaskVehicleConvertibleRoof = 508,
	CTaskVehicleParkNew = 509,
	CTaskVehicleFollowWaypointRecording = 510,
	CTaskVehicleGoToNavmesh = 511,
	CTaskVehicleReactToCopSiren = 512,
	CTaskVehicleGotoLongRange = 513,
	CTaskVehicleWait = 514,
	CTaskVehicleReverse = 515,
	CTaskVehicleBrake = 516,
	CTaskVehicleHandBrake = 517,
	CTaskVehicleTurn = 518,
	CTaskVehicleGoForward = 519,
	CTaskVehicleSwerve = 520,
	CTaskVehicleFlyDirection = 521,
	CTaskVehicleHeadonCollision = 522,
	CTaskVehicleBoostUseSteeringAngle = 523,
	CTaskVehicleShotTire = 524,
	CTaskVehicleBurnout = 525,
	CTaskVehicleRevEngine = 526,
	CTaskVehicleSurfaceInSubmarine = 527,
	CTaskVehiclePullAlongside = 528,
	CTaskVehicleTransformToSubmarine = 529,
	CTaskAnimatedFallback = 530
};
class model_info
{
public:
	static bool does_model_exist(const rage::joaat_t hash)
	{
		if (const auto model = model_info::get_model(hash); model)
			return true;
		return false;
	}

	template<typename T = CBaseModelInfo*>
	static T get_model(const rage::joaat_t hash)
	{
		const auto model_table = patterns::model_table;
		for (auto i = model_table->m_lookup_table[hash % model_table->m_lookup_key]; i; i = i->m_next)
		{
			if (i->m_hash == hash)
			{
				if (const auto model = model_table->m_data[i->m_idx]; model)
				{
					return reinterpret_cast<T>(model);
				}
			}
		}
		return nullptr;
	}

	static CVehicleModelInfo* get_vehicle_model(const rage::joaat_t hash)
	{
		if (const auto model = model_info::get_model<CVehicleModelInfo*>(hash); model && model->m_model_type == eModelType::Vehicle)
			return model;
		return nullptr;
	}

	template<typename T, typename... Args>
	static bool is_model_of_type(const rage::joaat_t hash, const T arg, const Args... args)
	{
		bool of_type = false;
		if (const auto model = model_info::get_model(hash))
		{
			of_type = model->m_model_type == arg;
			(
				[&of_type, &model](eModelType type) {
					of_type |= model->m_model_type == type;
				}(args),
					...);
		}
		return of_type;
	}
};

namespace menu::helpers {

	struct sync_node_id
	{
		Hash id;
		const char* name;

		constexpr sync_node_id()
		{
			id = 0;
		}

		template<size_t N>
		constexpr sync_node_id(char const (&pp)[N])
		{
			id = rage::consteval_joaat(pp);
			name = pp;
		}

		// implicit conversion
		constexpr operator Hash() const
		{
			return id;
		}
	};

	using sync_node_vft = uintptr_t;

	// Sync Node Virtual Function Table address to all sync node identifiers that also have that vft address.
	using sync_node_vft_to_ids = std::unordered_map<sync_node_vft, std::vector<sync_node_id>>;

	// Sync Tree node array index to node identifier.
	using sync_tree_node_array_index_to_node_id_t = std::vector<sync_node_id>;

	struct sync_node_finder_t
	{
		static constexpr size_t sync_tree_count = size_t(eNetObjType::NET_OBJ_TYPE_TRAIN) + 1;

		std::array<sync_node_vft_to_ids, sync_tree_count> sync_trees_sync_node_vft_to_ids;

		std::array<sync_tree_node_array_index_to_node_id_t, sync_tree_count> sync_trees_node_array_index_to_node_id = {
			{
				// AUTOMOBILE
				{
					{"CVehicleCreationDataNode"},
					{"CAutomobileCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// BIKE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CBikeGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// BOAT
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CBoatGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// DOOR
				{
					{"CDoorCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDoorScriptInfoDataNode"},
					{"CDoorScriptGameStateDataNode"},

					{"CDoorMovementDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// HELI
				{
					{"CVehicleCreationDataNode"},
					{"CAutomobileCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},
					{"CHeliHealthDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CHeliControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// OBJECT
				{
					{"CObjectCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CObjectGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CObjectScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CPhysicalHealthDataNode"},

					{"CSectorDataNode"},
					{"CObjectSectorPosNode"},
					{"CObjectOrientationNode"},
					{"CPhysicalVelocityDataNode"},
					{"CPhysicalAngVelocityDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// PED
				{
					{"CPedCreationDataNode"},
					{"CPedScriptCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CPedGameStateDataNode"},
					{"CPedComponentReservationDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CPedScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPedAttachDataNode"},
					{"CPedHealthDataNode"},
					{"CPedMovementGroupDataNode"},
					{"CPedAIDataNode"},
					{"CPedAppearanceDataNode"},

					{"CPedOrientationDataNode"},
					{"CPedMovementDataNode"},

					{"CPedTaskTreeDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},

					{"CSectorDataNode"},
					{"CPedSectorPosMapNode"},
					{"CPedSectorPosNavMeshNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CPedInventoryDataNode"},
					{"CPedTaskSequenceDataNode"},
				},
				// PICKUP
				{
					{"CPickupCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},

					{"CPickupScriptGameStateNode"},
					{"CPhysicalGameStateDataNode"},
					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},
					{"CPhysicalHealthDataNode"},

					{"CPhysicalAttachDataNode"},

					{"CSectorDataNode"},
					{"CPickupSectorPosNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CPhysicalAngVelocityDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// PICKUP_PLACEMENT
				{
					{"CPickupPlacementCreationDataNode"},
					{"CMigrationDataNode"},
					{"CGlobalFlagsDataNode"},
					{"CPickupPlacementStateDataNode"},
				},
				// PLANE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},
					{"CPlaneGameStateDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CPlaneControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// SUBMARINE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CSubmarineGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CSubmarineControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// PLAYER
				{
					{"CPlayerCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CPedGameStateDataNode"},
					{"CPedComponentReservationDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPlayerGameStateDataNode"},

					{"CPedAttachDataNode"},
					{"CPedHealthDataNode"},
					{"CPedMovementGroupDataNode"},
					{"CPedAIDataNode"},
					{"CPlayerAppearanceDataNode"},
					{"CPlayerPedGroupDataNode"},
					{"CPlayerAmbientModelStreamingNode"},
					{"CPlayerGamerDataNode"},
					{"CPlayerExtendedGameStateNode"},

					{"CPedOrientationDataNode"},
					{"CPedMovementDataNode"},

					{"CPedTaskTreeDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},

					{"CSectorDataNode"},
					{"CPlayerSectorPosNode"},
					{"CPlayerCameraDataNode"},
					{"CPlayerWantedAndLOSDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// TRAILER
				{

				},
				// TRAIN
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CTrainGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
			},
		};
	};
	inline bool is_valid_interior_game(uint32_t interior_index)
	{
		if ((int)(__int64)*(int16_t*)&interior_index >= (int)(*patterns::interior_proxy_pool)->m_size) // this is the bug, should have been an unsigned compare instead
			return false;

		// some more checks that aren't broken

		auto a1 = (uint16_t*)&interior_index;

		__int16 v2;          // ax
		unsigned __int16 v3; // ax
		bool v4;             // cf
		bool v5;             // zf
		unsigned __int16 v6; // ax

		if (*a1 == 0xFFFF)
			return false;

		v2 = a1[1];
		if ((v2 & 1) != 0)
		{
			v6 = v2 >> 2;
			v4 = v6 < 0xFFu;
			v5 = v6 == 255;
		}
		else
		{
			v3 = v2 >> 2;
			v4 = v3 < 0x1Fu;
			v5 = v3 == 31;
		}
		return v4 || v5;
	}

	inline bool is_valid_interior_fixed(uint32_t interior_index)
	{
		if ((uint32_t)(__int64)*(int16_t*)&interior_index >= (uint32_t)(*patterns::interior_proxy_pool)->m_size)
			return false;

		return true;
	}
	class sync_node_finder
	{
	private:
		static inline sync_node_finder_t finder;

	public:
		static const std::vector<sync_node_id>& find(eNetObjType obj_type, uintptr_t vft)
		{
			return finder.sync_trees_sync_node_vft_to_ids[(int)obj_type][vft];
		}

		static void init()
		{
			for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
			{
				if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
					continue;

				rage::netSyncTree* tree = patterns::get_sync_tree_for_type(*patterns::network_object_mgr, i);

				if (tree->m_child_node_count != finder.sync_trees_node_array_index_to_node_id[i].size())
				{
					LOG_ERROR("Failed to find sync handler");

					throw std::runtime_error("Failed to find sync handler");
				}

				for (int j = 0; j < tree->m_child_node_count; j++)
				{
					const uintptr_t vft = *(uintptr_t*)tree->m_child_nodes[j];

					const sync_node_id node_id = finder.sync_trees_node_array_index_to_node_id[i][j];

					finder.sync_trees_sync_node_vft_to_ids[i][vft].push_back(node_id);
				}
			}
		}
	};

	constexpr uint32_t crash_peds[] = { 
		0x431D501C,
		RAGE_JOAAT("A_C_Boar"),
		RAGE_JOAAT("A_C_Cat_01"),
		RAGE_JOAAT("A_C_Cow"),
		RAGE_JOAAT("A_C_Coyote"),
		RAGE_JOAAT("A_C_Deer"),
		RAGE_JOAAT("A_C_Husky"),
		RAGE_JOAAT("A_C_MtLion"),
		RAGE_JOAAT("A_C_Pig"),
		RAGE_JOAAT("A_C_Poodle"),
		RAGE_JOAAT("A_C_Pug"),
		RAGE_JOAAT("A_C_Rabbit_01"),
		RAGE_JOAAT("A_C_Retriever"),
		RAGE_JOAAT("A_C_Rottweiler"),
		RAGE_JOAAT("A_C_shepherd"),
		RAGE_JOAAT("A_C_Westy"),
		RAGE_JOAAT("A_C_Chickenhawk"),
		RAGE_JOAAT("A_C_Cormorant"),
		RAGE_JOAAT("A_C_Crow"),
		RAGE_JOAAT("A_C_Hen"),
		RAGE_JOAAT("A_C_Pigeon"),
		RAGE_JOAAT("A_C_Seagull"),
		RAGE_JOAAT("A_C_Dolphin"),
		RAGE_JOAAT("A_C_Fish"),
		RAGE_JOAAT("A_C_KillerWhale"),
		RAGE_JOAAT("A_C_SharkHammer"),
		RAGE_JOAAT("A_C_SharkTiger"),
		RAGE_JOAAT("A_C_Stingray"),
		RAGE_JOAAT("IG_Orleans"),
		RAGE_JOAAT("A_C_Chop"),
		RAGE_JOAAT("A_C_HumpBack"), RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped") };

	constexpr uint32_t crash_vehicles[] = { RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95") };

	constexpr uint32_t crash_objects[] = { 2063962179, 959275690, 1396140175, 2968924808, 2931248133, 1098812088, 379820688, 1692612370,
				2946368461, 1082648418, 3561133533, 3825864590, 3357950520, 4121926986, 109264625, 3955926036, 1181661112,
				RAGE_JOAAT("prop_container_01a"), RAGE_JOAAT("prop_container_01b"), RAGE_JOAAT("prop_container_01c"),
				RAGE_JOAAT("prop_container_01d"), RAGE_JOAAT("prop_container_01e"), RAGE_JOAAT("prop_container_01f"),
				RAGE_JOAAT("prop_container_01g"), RAGE_JOAAT("prop_container_01h"), RAGE_JOAAT("prop_container_01mb"),
				RAGE_JOAAT("prop_container_02a"), RAGE_JOAAT("prop_container_03a"), RAGE_JOAAT("prop_container_03b"),
				RAGE_JOAAT("prop_container_03mb"), RAGE_JOAAT("prop_container_03_ld"), RAGE_JOAAT("prop_container_04a"),
				RAGE_JOAAT("prop_container_04mb"), RAGE_JOAAT("prop_container_05mb"), RAGE_JOAAT("prop_container_door_mb_l"),
				RAGE_JOAAT("prop_container_door_mb_r"), RAGE_JOAAT("prop_container_hole"), RAGE_JOAAT("prop_container_ld"),
				RAGE_JOAAT("prop_container_ld2"), RAGE_JOAAT("prop_container_old1"), RAGE_JOAAT("prop_container_ld"),
				RAGE_JOAAT("prop_container_ld2"), RAGE_JOAAT("prop_container_old1"), RAGE_JOAAT("prop_dog_cage_02"),
				RAGE_JOAAT("prop_dog_cage_01"), RAGE_JOAAT("prop_dog_cage_02"), RAGE_JOAAT("prop_conslift_cage"),
				RAGE_JOAAT("prop_rub_cage01a"), RAGE_JOAAT("prop_gold_cont_01b"), RAGE_JOAAT("prop_gold_trolly"),
				RAGE_JOAAT("prop_gold_trolly_full"), RAGE_JOAAT("prop_gold_trolly_strap_01"), RAGE_JOAAT("prop_cctv_cont_01"),
				RAGE_JOAAT("prop_cctv_cont_03"), RAGE_JOAAT("prop_cctv_cont_04"), RAGE_JOAAT("prop_cctv_cont_05"),
				RAGE_JOAAT("prop_cctv_cont_06"), RAGE_JOAAT("prop_container_01a"), RAGE_JOAAT("prop_container_01b"),
				RAGE_JOAAT("prop_container_01c"), RAGE_JOAAT("prop_container_01d"), RAGE_JOAAT("prop_container_01e"),
				RAGE_JOAAT("prop_container_01f"), RAGE_JOAAT("prop_container_01g"), RAGE_JOAAT("prop_container_01h"),
				RAGE_JOAAT("prop_container_01mb"), RAGE_JOAAT("prop_container_02a"), RAGE_JOAAT("prop_container_03a"),
				RAGE_JOAAT("prop_container_03b"), RAGE_JOAAT("prop_container_03mb"), RAGE_JOAAT("prop_container_03_ld"),
				RAGE_JOAAT("prop_container_04a"), RAGE_JOAAT("prop_container_04mb"), RAGE_JOAAT("prop_container_05mb"),
				RAGE_JOAAT("prop_container_door_mb_l"), RAGE_JOAAT("prop_container_door_mb_r"), RAGE_JOAAT("prop_container_hole"),
				RAGE_JOAAT("prop_container_ld"), RAGE_JOAAT("prop_container_ld2"), RAGE_JOAAT("prop_container_old1"),
				RAGE_JOAAT("prop_contnr_pile_01a"), RAGE_JOAAT("prop_controller_01"), RAGE_JOAAT("prop_control_rm_door_01"),
				RAGE_JOAAT("prop_cont_chiller_01"), RAGE_JOAAT("prop_container_hole"), RAGE_JOAAT("prop_cont_chiller_01"),
				0xC6C3242D, RAGE_JOAAT("prop_beach_fire"), 0xA2023E64, 2799454049, 3482883616, 564151899, 710268902,
				3284981583, 3500568834, 1060884015, 4248442390, 4256736313, 2693815128, 1925435073, 682074297,
				3763106032, 621481054, 2908189926, 3763623269, 1369811908, 1098122770, RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"), RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"), RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"), RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"), RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"), RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"), RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"), RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"), RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"), 92962485 };

	
	constexpr auto valid_player_models = {
		RAGE_JOAAT("mp_m_freemode_01"),
		RAGE_JOAAT("mp_f_freemode_01"),
		RAGE_JOAAT("u_m_m_filmdirector"),
		RAGE_JOAAT("player_zero"),
		RAGE_JOAAT("player_one"),
		RAGE_JOAAT("player_two"),
		// peyote
		RAGE_JOAAT("A_C_Boar"),
		RAGE_JOAAT("A_C_Cat_01"),
		RAGE_JOAAT("A_C_Cow"),
		RAGE_JOAAT("A_C_Coyote"),
		RAGE_JOAAT("A_C_Deer"),
		RAGE_JOAAT("A_C_Husky"),
		RAGE_JOAAT("A_C_MtLion"),
		RAGE_JOAAT("A_C_Pig"),
		RAGE_JOAAT("A_C_Poodle"),
		RAGE_JOAAT("A_C_Pug"),
		RAGE_JOAAT("A_C_Rabbit_01"),
		RAGE_JOAAT("A_C_Retriever"),
		RAGE_JOAAT("A_C_Rottweiler"),
		RAGE_JOAAT("A_C_shepherd"),
		RAGE_JOAAT("A_C_Westy"),
		RAGE_JOAAT("A_C_Chickenhawk"),
		RAGE_JOAAT("A_C_Cormorant"),
		RAGE_JOAAT("A_C_Crow"),
		RAGE_JOAAT("A_C_Hen"),
		RAGE_JOAAT("A_C_Pigeon"),
		RAGE_JOAAT("A_C_Seagull"),
		RAGE_JOAAT("A_C_Dolphin"),
		RAGE_JOAAT("A_C_Fish"),
		RAGE_JOAAT("A_C_KillerWhale"),
		RAGE_JOAAT("A_C_SharkHammer"),
		RAGE_JOAAT("A_C_SharkTiger"),
		RAGE_JOAAT("A_C_Stingray"),
		RAGE_JOAAT("IG_Orleans"),
		RAGE_JOAAT("A_C_Chop"),
		RAGE_JOAAT("A_C_HumpBack"),
	};
	inline bool is_valid_player_model(rage::joaat_t model)
	{
		for (auto iterator : valid_player_models)
			if (iterator == model)
				return true;
		return false;
	}
	inline bool is_crash_ped(uint32_t model)
	{
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		if (!model_info::is_model_of_type(model, eModelType::Ped, eModelType::OnlineOnlyPed))
			return true;
		return false;
	}

	inline bool is_crash_vehicle(uint32_t model)
	{
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		if (!model_info::is_model_of_type(model, eModelType::Vehicle, eModelType::Unk133))
			return true;
		return false;
	}

	inline bool is_crash_object(uint32_t model)
	{
		if (!model_info::get_model(model))
			return false;
		if (!model_info::is_model_of_type(model, eModelType::Object, eModelType::Time, eModelType::Weapon, eModelType::Destructable, eModelType::WorldObject, eModelType::Sprinkler, eModelType::Unk65, eModelType::Plant, eModelType::LOD, eModelType::Unk132, eModelType::Building))
			return true;
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}


	// the game function does weird stuff that we don't want
	inline CObject* get_entity_attached_to(CObject* entity)
	{
		if (!entity)
			return nullptr;

		if (!entity->gap50)
			return nullptr;

		__int64 component = *(__int64*)((__int64)(entity->gap50) + 0x48);

		if (!component)
			return nullptr;

		int unk_count = *(int*)(component + 0x5C) & 0xF;

		if (unk_count < 2)
			return nullptr;

		return *(CObject**)(component);
	}

	inline bool is_attachment_infinite(rage::netObject* object, uint16_t attached_to_net_id, int from_bone, int to_bone)
	{
		if (object == nullptr)
			return false;

		auto target = patterns::get_net_object(*patterns::network_object_mgr, attached_to_net_id, false);

		while (target)
		{
			if (target == object)
				return true;

			auto next = get_entity_attached_to(target->GetGameObject());

			if (!next)
				return false;

			if (!next->m_net_object)
				return false;

			target = next->m_net_object;
		}

		return false;
	}

	inline bool is_in_vehicle(CPed* ped, CVehicle* vehicle)
	{
		if (!ped || !vehicle)
			return false;

		if (ped == vehicle->m_driver)
			return true;

		for (int i = 0; i < 15; i++)
			if (vehicle->m_passengers[i] == ped)
				return true;

		return false;
	}

	inline bool is_local_player_an_occupant(CVehicleProximityMigrationDataNode* node)
	{
		for (int i = 0; i < 16; i++)
		{
			if (node->m_has_occupants[i] && node->m_occupants[i] == (*patterns::ped_factory)->m_local_ped->m_net_object->m_object_id)
				return true;
		}

		return false;
	}

	inline bool is_sane_override_pos(float x, float y, float z)
	{
		bool crash = (char)(fmaxf(0.0, (x + 149.0) - -8192.0) / 75.0) == 255 || (char)(fmaxf(0.0, (y + 149.0) - -8192.0) / 75.0) == 255;

		return !crash;
	}

	inline eNetObjType vehicle_type_to_object_type(eVehicleType type)
	{
		switch (type)
		{
		case eVehicleType::VEHICLE_TYPE_CAR:
		case eVehicleType::VEHICLE_TYPE_SUBMARINECAR:
		case eVehicleType::VEHICLE_TYPE_AUTOGYRO:
		case eVehicleType::VEHICLE_TYPE_QUADBIKE:
		case eVehicleType::VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE:
		case eVehicleType::VEHICLE_TYPE_AMPHIBIOUS_AUTOMOBILE: return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE;
		case eVehicleType::VEHICLE_TYPE_HELI:
		case eVehicleType::VEHICLE_TYPE_BLIMP: return eNetObjType::NET_OBJ_TYPE_HELI;
		case eVehicleType::VEHICLE_TYPE_PLANE: return eNetObjType::NET_OBJ_TYPE_PLANE;
		case eVehicleType::VEHICLE_TYPE_BIKE:
		case eVehicleType::VEHICLE_TYPE_BICYCLE: return eNetObjType::NET_OBJ_TYPE_BIKE;
		case eVehicleType::VEHICLE_TYPE_TRAILER: return eNetObjType::NET_OBJ_TYPE_TRAILER;
		case eVehicleType::VEHICLE_TYPE_TRAIN: return eNetObjType::NET_OBJ_TYPE_TRAIN;
		case eVehicleType::VEHICLE_TYPE_SUBMARINE: return eNetObjType::NET_OBJ_TYPE_SUBMARINE;
		case eVehicleType::VEHICLE_TYPE_BOAT: return eNetObjType::NET_OBJ_TYPE_BOAT;
		case eVehicleType::VEHICLE_TYPE_DRAFT: return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; // this appears to be unused
		}

		return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE;
	}

	inline bool is_crash_ped_task(eTaskTypeIndex type)
	{
		if (type == eTaskTypeIndex::CTaskUnalerted && patterns::g_syncing_object_type == eNetObjType::NET_OBJ_TYPE_PLAYER)
			return true;

		return false;
	}

	inline bool is_crash_vehicle_task(eTaskTypeIndex type)
	{
		switch (type)
		{
		case eTaskTypeIndex::CTaskVehicleGoToPlane:
		case eTaskTypeIndex::CTaskVehicleLandPlane:
		case eTaskTypeIndex::CTaskVehiclePlayerDrivePlane:
		case eTaskTypeIndex::CTaskVehiclePlaneChase: return patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_PLANE;
		case eTaskTypeIndex::CTaskVehicleGoToHelicopter:
		case eTaskTypeIndex::CTaskVehiclePoliceBehaviourHelicopter:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveHeli:
		case eTaskTypeIndex::CTaskVehicleLand:
		case eTaskTypeIndex::CTaskVehicleHeliProtect: return patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_HELI;
		case eTaskTypeIndex::CTaskVehicleGoToBoat:
		case eTaskTypeIndex::CTaskVehicleCruiseBoat:
		case eTaskTypeIndex::CTaskVehicleFleeBoat:
		case eTaskTypeIndex::CTaskVehiclePoliceBehaviourBoat:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveBoat:
			return patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_BOAT;
		case eTaskTypeIndex::CTaskVehicleGoToSubmarine:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveSubmarine:
			return patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_SUBMARINE;
		case eTaskTypeIndex::CTaskVehicleFleeAirborne:
			return patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_HELI && patterns::g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_PLANE;
		}

		return false;
	}



	inline bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (check_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			const auto vft = *(uintptr_t*)node;

			for (const sync_node_id node_id : sync_node_finder::find((eNetObjType)object->m_object_type, vft))
			{
				if ((((CProjectBaseSyncDataNode*)node)->flags & 1) == 0)
					continue;

				switch (node_id)
				{
				case sync_node_id("CVehicleCreationDataNode"):
				{
					const auto creation_node = (CVehicleCreationDataNode*)(node);
					if (is_crash_vehicle(creation_node->m_model))
					{
						notify::stacked(std::format("Blocked Vehicle Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CDoorCreationDataNode"):
				{
					const auto creation_node = (CDoorCreationDataNode*)(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::stacked(std::format("Blocked Object Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CPickupCreationDataNode"):
				{
					const auto creation_node = (CPickupCreationDataNode*)(node);
					if (creation_node->m_custom_model && is_crash_object(creation_node->m_custom_model))
					{
						notify::stacked(std::format("Blocked Pickup Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CPhysicalAttachDataNode"):
				{
					const auto attach_node = (CPhysicalAttachDataNode*)(node);

					if (attach_node->m_attached
						&& is_attachment_infinite(object,
							attach_node->m_attached_to,
							attach_node->m_attach_bone,
							attach_node->m_other_attach_bone))
					{
						notify::stacked(std::format("Blocked Bro Hug Crash From {}", sender->GetName()).c_str());
						return true;
					}

					if (attach_node->m_attached && object && object->m_object_type == (int16_t)eNetObjType::NET_OBJ_TYPE_TRAILER)
					{
						if (auto net_obj =
							patterns::get_net_object(*patterns::network_object_mgr, attach_node->m_attached_to, false))
						{
							if (auto entity = net_obj->GetGameObject())
							{
								if (entity->m_entity_type != 3)
								{
									notify::stacked(std::format("Blocked Invalid Attachment Crash From {}", sender->GetName()).c_str());
									return true;
								}
							}
						}
					}

					break;
				}
				case sync_node_id("CPedCreationDataNode"):
				{
					const auto creation_node = (CPedCreationDataNode*)(node);
					if (is_crash_ped(creation_node->m_model))
					{
						notify::stacked(std::format("Blocked Ped Crash From {}", sender->GetName()).c_str());
						return true;
					}
					else if (creation_node->m_has_prop && is_crash_object(creation_node->m_prop_model))
					{
						notify::stacked(std::format("Blocked Ped Prop Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CPedAttachDataNode"):
				{
					const auto attach_node = (CPedAttachDataNode*)(node);
					if (attach_node->m_attached
						&& is_attachment_infinite(object,
							attach_node->m_attached_to,
							attach_node->m_attachment_bone,
							attach_node->m_attachment_bone))
					{
						notify::stacked(std::format("Blocked Bro Hug Crash From {}", sender->GetName()).c_str());
						return true;
					}

					break;
				}
				case sync_node_id("CObjectCreationDataNode"):
				{
					const auto creation_node = (CObjectCreationDataNode*)(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::stacked(std::format("Blocked Object Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CPlayerAppearanceDataNode"):
				{
					const auto player_appearance_node = (CPlayerAppearanceDataNode*)(node);
					if (is_crash_ped(player_appearance_node->m_model_hash))
					{
						notify::stacked(std::format("Blocked Player Crash From {}", sender->GetName()).c_str());
						return true;
					}
					//check_player_model(sender_plyr, player_appearance_node->m_model_hash);
					break;
				}
				case sync_node_id("CPlayerCreationDataNode"):
				{
					const auto player_creation_node = (CPlayerCreationDataNode*)(node);
					if (is_crash_ped(player_creation_node->m_model))
					{
						notify::stacked(std::format("Blocked Player Crash From {}", sender->GetName()).c_str());
						return true;
					}
					//check_player_model(sender_plyr, player_creation_node->m_model);
					break;
				}
				case sync_node_id("CSectorDataNode"):
				{
					const auto sector_node = (CSectorDataNode*)(node);
					int posX = (sector_node->m_pos_x - 512.0f) * 54.0f;
					int posY = (sector_node->m_pos_y - 512.0f) * 54.0f;
					bool is_x_invalid = (((posX + 149) + 8192) / 75) >= 255;
					bool is_y_invalid = (((posY + 149) + 8192) / 75) >= 255;
					if (is_x_invalid || is_y_invalid)
					{
						notify::stacked(std::format("Blocked Host Crash From {}", sender->GetName()).c_str());
						return true;
					}
					break;
				}
				case sync_node_id("CPlayerGameStateDataNode"):
				{
					const auto game_state_node = (CPlayerGameStateDataNode*)(node);
					if (game_state_node->m_is_overriding_population_control_sphere
						&& !is_sane_override_pos(game_state_node->m_population_control_sphere_x,
							game_state_node->m_population_control_sphere_y,
							game_state_node->m_population_control_sphere_z)
						&& (*patterns::network)->m_game_session_ptr->is_host())
					{
						notify::stacked(std::format("Blocked Host Crash From {}", sender->GetName()).c_str());
						return true;
					}

					if (sender->m_player_id)
					{
						if (game_state_node->m_is_spectating)
						{
							if (!sender->m_player_info->m_ped)
								break;

							if (!sender->m_player_info->m_ped->m_health <= 0.0f) // you spectate the player that killed you
								break;

							auto net_obj = patterns::get_net_object(*patterns::network_object_mgr,
								game_state_node->m_spectating_net_id,
								false);

							if (!net_obj)
								break;

							auto entity = net_obj->GetGameObject();

							if (!entity || entity->m_entity_type != 4)
								break;

							auto player_info = ((CPed*)entity)->m_player_info;

							if (!player_info)
								break;

							auto target = nullptr;

							if ((*patterns::ped_factory)->m_local_ped && (CPed*)entity == (*patterns::ped_factory)->m_local_ped)
							{
								notify::stacked(std::format("{} is spectating you", sender->GetName()).c_str());
							}
							else
							{
								for (auto p = 0; p < 32; p++) {
									if (patterns::get_net_player(p)->m_player_info == player_info) {
										notify::stacked(std::format("{} is spectating {}", sender->GetName(), patterns::get_net_player(p)->GetName()).c_str());
									}
								}
							}
						}
					}

					break;
				}
				case sync_node_id("CTrainGameStateDataNode"):
				{
					const auto train_node = (CTrainGameStateDataNode*)(node);
					int track_id = train_node->m_track_id;
					if (track_id != -1 && (track_id < 0 || track_id >= 12))
					{
						menu::notify::stacked(std::format("{} train track id", sender->GetName()).c_str());
						return true;
					}

					int train_config_index = train_node->m_train_config_index;
					int carriage_config_index = train_node->m_carriage_config_index;

					if (train_config_index != -1)
					{
						if ((uint32_t)train_config_index >= patterns::train_config_array->size())
						{
							menu::notify::stacked(std::format("{} train config", sender->GetName()).c_str());
							return true;
						}

						if (carriage_config_index != -1)
						{
							if ((uint32_t)carriage_config_index
								>= (*patterns::train_config_array)[train_config_index].m_carraige_configs.size())
							{
								menu::notify::stacked(std::format("{} train config", sender->GetName()).c_str());
								return true;
							}
						}
					}

					break;
				}
				case sync_node_id("CVehicleProximityMigrationDataNode"):
				{
					if (object && patterns::ped_factory && (*patterns::ped_factory)->m_local_ped && (*patterns::ped_factory)->m_local_ped->m_net_object)
					{
						const auto migration_node = (CVehicleProximityMigrationDataNode*)(node);

						if (!(*patterns::ped_factory)->m_local_ped->m_vehicle || !(*patterns::ped_factory)->m_local_ped->m_vehicle->m_net_object
							|| (*patterns::ped_factory)->m_local_ped->m_vehicle->m_net_object->m_object_id != object->m_object_id
							|| !is_in_vehicle((*patterns::ped_factory)->m_local_ped, (*patterns::ped_factory)->m_local_ped->m_vehicle))
						{
							if (is_local_player_an_occupant(migration_node))
							{
								return true; // remote teleport
							}
						}
					}

					break;
				}
			
				case sync_node_id("CVehicleControlDataNode"):
				{
					const auto control_node = (CVehicleControlDataNode*)(node);
					if (control_node->m_is_submarine_car)
					{
						if (auto vehicle = (CVehicle*)object->GetGameObject())
						{
							if (auto model_info = static_cast<CVehicleModelInfo*>(vehicle->m_model_info))
							{
								if (model_info->m_vehicle_type != eVehicleType::VEHICLE_TYPE_SUBMARINECAR)
								{
									menu::notify::stacked(std::format("{} send a vhicle control event", sender->GetName()).c_str());
									return true;
								}
							}
						}
					}

					break;
				}
				case sync_node_id("CPlayerCameraDataNode"):
				{
					const auto camera_node = (CPlayerCameraDataNode*)(node);
					if (!is_sane_override_pos(camera_node->m_free_cam_pos_x, camera_node->m_free_cam_pos_y, camera_node->m_free_cam_pos_z))
					{
						if ((*patterns::network)->m_game_session_ptr->is_host())
							menu::notify::stacked(std::format("{} send a camera event", sender->GetName()).c_str());
						return true;
					}

					break;
				}
				case sync_node_id("CVehicleGadgetDataNode"):
				{
					const auto gadget_node = (CVehicleGadgetDataNode*)(node);
					for (int i = 0; i < gadget_node->m_gadget_count; i++)
					{
						if (gadget_node->m_gadget_data[i].m_gadget_type > 6)
						{
							menu::notify::stacked(std::format("{} send a gadget vehicle event", sender->GetName()).c_str());
							return true;
						}
					}
					break;
				}
				case sync_node_id("CPedTaskTreeDataNode"):
				{
					const auto task_node = (CPedTaskTreeDataNode*)(node);

					for (int i = 0; i < 8; i++)
					{
						if (task_node->m_task_bitset & (1 << i))
						{
							if (is_crash_ped_task((eTaskTypeIndex)task_node->m_tasks[i].m_task_type))
							{
								menu::notify::stacked(std::format("{} send a task ped event", sender->GetName()).c_str());
								return true;
							}
						}
					}

					break;
				}
				case sync_node_id("CVehicleTaskDataNode"):
				{
					const auto task_node = (CVehicleTaskDataNode*)(node);
					if (is_crash_vehicle_task((eTaskTypeIndex)task_node->m_task_type))
					{
						menu::notify::stacked(std::format("{} send a task vehicle event", sender->GetName()).c_str());
						return true;
					}

					break;
				}
				case sync_node_id("CEntityScriptInfoDataNode"):
				{
					const auto script_node = (CEntityScriptInfoDataNode*)(node);
					if (script_node->m_has_script_info)
					{
						if (script_node->m_script_info.m_local_handle == 0)
						{
							menu::notify::stacked(std::format("{} send a entity script info event", sender->GetName()).c_str());
							return true;
						}
					}
					break;
				}
				case sync_node_id("CDynamicEntityGameStateDataNode"):
				{
					const auto game_state_node = (CDynamicEntityGameStateDataNode*)(node);

					if (is_valid_interior_game(game_state_node->m_interior_index)
						&& !is_valid_interior_fixed(game_state_node->m_interior_index)) // will crash
					{
						menu::notify::stacked(std::format("{} send a dynamic entity game state event", sender->GetName()).c_str());
						return true;
					}
				}
				}
			}
		}
		return false;
	}
	
}