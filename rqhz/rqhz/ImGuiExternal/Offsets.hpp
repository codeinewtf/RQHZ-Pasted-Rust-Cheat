#pragma once
#include "Imports.hpp"
#define offset(name, value) const static std::uintptr_t m_##name = value
offset ( mod, 0xE8 );
offset ( camlerp, 0x20 );
offset ( camspeed, 0x2C );
offset ( camlookspeed, 0x34 );
offset ( item_definition, 0x20 );
offset ( projectile_spread, 0x30 );
offset ( projectile_velocity_spread, 0x38 );

offset( OcclusionCulling_c, 56966008); // OcclusionCulling_c*
offset( tod_sky_c, 56976808); // tod_sky_c*
offset( ConVar_Culling_c, 56965952); // ConVar_Culling_c*
offset( flashbangoverlay_c, 56902048); // flashbangoverlay_c*
offset( convar_admin_c, 56954176); // convar_admin_c*
offset( localplayer_c, 56971600); // localplayer_c*
offset( convar_graphics_c, 56967448); // convar_graphics_c*
offset( BaseEntity_c, 56957136); // System_Collections_Generic_List_BaseGameMode__c*
offset( ConVar_Client_c, 56959376); // ConVar_Client_c*
offset( Skinnable_c, 57026592); // Skinnable_c*
offset( Maincamera_c, 56968928); // Maincamera_c*

namespace Offsets
{
	namespace Classes
	{
		namespace BasePlayer
		{
			constexpr auto __menuOption_Climb = 0x240; // Option
			constexpr auto __menuOption_Drink = 0x298; // Option
			constexpr auto __menuOption_InviteToTeam = 0x2f0; // Option
			constexpr auto __menuOption_Menu_AssistPlayer = 0x348; // Option
			constexpr auto __menuOption_Menu_LootPlayer = 0x3a0; // Option
			constexpr auto __menuOption_Promote = 0x3f8; // Option
			constexpr auto __menuOption_SaltWater = 0x450; // Option
			constexpr auto lastOpenSoundPlay = 0x4a8; // TimeSince
			constexpr auto currentViewMode = 0x4ac; // BasePlayer.CameraMode
			constexpr auto selectedViewMode = 0x4b0; // BasePlayer.CameraMode
			constexpr auto lastRevivePoint = 0x4b4; // Vector3
			constexpr auto lastReviveDirection = 0x4c0; // Vector3
			constexpr auto playerModel = 0x4d0; // PlayerModel
			constexpr auto Frozen = 0x4d8; // bool
			constexpr auto voiceRecorder = 0x4e0; // PlayerVoiceRecorder
			constexpr auto voiceSpeaker = 0x4e8; // PlayerVoiceSpeaker
			constexpr auto input = 0x4f0; // PlayerInput
			constexpr auto movement = 0x4f8; // BaseMovement
			constexpr auto collision = 0x500; // BaseCollision
			constexpr auto _lookingAt = 0x508; // GameObject
			constexpr auto _lookingAtEntity = 0x510; // BaseEntity
			constexpr auto _lookingAtCollider = 0x518; // Collider
			constexpr auto lookingAtPointk__BackingField = 0x520; // Vector3
			constexpr auto wakeTime = 0x52c; // float
			constexpr auto needsClothesRebuild = 0x530; // bool
			constexpr auto wasSleeping = 0x531; // bool
			constexpr auto wokeUpBefore = 0x532; // bool
			constexpr auto wasDead = 0x533; // bool
			constexpr auto lastClothesHash = 0x534; // uint
			constexpr auto IsWearingDiveGogglesk__BackingField = 0x538; // bool
			constexpr auto GestureViewModel = 0x540; // ViewModel
			constexpr auto timeSinceUpdatedLookingAt = 0x548; // RealTimeSince
			constexpr auto nextTopologyTestTime = 0x54c; // float
			constexpr auto usePressTime = 0x550; // float
			constexpr auto useHeldTime = 0x554; // float
			constexpr auto lookingAtTest = 0x558; // HitTest
			constexpr auto cachedWaterDrinkingPoint = 0x560; // Vector3
			constexpr auto gestureList = 0x570; // GestureCollection
			constexpr auto gestureFinishedTime = 0x578; // TimeUntil
			constexpr auto blockHeldInputTimer = 0x57c; // TimeSince
			constexpr auto currentGesture = 0x580; // GestureConfig
			constexpr auto disabledHeldEntity = 0x588; // HeldEntity
			constexpr auto nextGestureMenuOpenTime = 0x590; // float
			constexpr auto lastGestureCancel = 0x594; // TimeSince
			constexpr auto client_lastHelloTime = 0x598; // float
			constexpr auto currentTeam = 0x5a0; // ulong
			constexpr auto clientTeam = 0x5a8; // PlayerTeam
			constexpr auto lastReceivedTeamTime = 0x5b0; // float
			constexpr auto lastPresenceTeamId = 0x5b8; // ulong
			constexpr auto lastPresenceTeamSize = 0x5c0; // int
			constexpr auto playerGroupKey = 0x5c8; // string
			constexpr auto playerGroupSizeKey = 0x5d0; // string
			constexpr auto clActiveItem = 0x5d8; // uint
			constexpr auto ClientCurrentMapNote = 0x5e0; // MapNote
			constexpr auto ClientCurrentDeathNote = 0x5e8; // MapNote
			constexpr auto missions = 0x5f0; // List(BaseMission.MissionInstance)
			constexpr auto _activeMission = 0x5f8; // int
			constexpr auto modelState = 0x600; // ModelState
			constexpr auto mounted = 0x608; // EntityRef
			constexpr auto nextSeatSwapTime = 0x618; // float
			constexpr auto PetEntity = 0x620; // BaseEntity
			constexpr auto lastPetCommandIssuedTime = 0x628; // float
			constexpr auto PetPrefabID = 0x62c; // uint
			constexpr auto PetID = 0x630; // uint
			constexpr auto cachedBuildingPrivilegeTime = 0x634; // float
			constexpr auto cachedBuildingPrivilege = 0x638; // BuildingPrivlidge
			constexpr auto maxProjectileID = 0x640; // int
			constexpr auto lastUpdateTime = 0x644; // float
			constexpr auto cachedThreatLevel = 0x648; // float
			constexpr auto serverTickRate = 0x64c; // int
			constexpr auto clientTickRate = 0x650; // int
			constexpr auto serverTickInterval = 0x654; // float
			constexpr auto clientTickInterval = 0x658; // float
			constexpr auto lastSentTickTime = 0x65c; // float
			constexpr auto lastTickStopwatch = 0x660; // Stopwatch
			constexpr auto lastSentTick = 0x668; // PlayerTick
			constexpr auto nextVisThink = 0x670; // float
			constexpr auto lastTimeSeen = 0x674; // float
			constexpr auto debugPrevVisible = 0x678; // bool
			constexpr auto fallDamageEffect = 0x680; // GameObjectRef
			constexpr auto drownEffect = 0x688; // GameObjectRef
			constexpr auto playerFlags = 0x690; // BasePlayer.PlayerFlags
			constexpr auto eyes = 0x698; // PlayerEyes
			constexpr auto inventory = 0x6a0; // PlayerInventory
			constexpr auto blueprints = 0x6a8; // PlayerBlueprints
			constexpr auto metabolism = 0x6b0; // PlayerMetabolism
			constexpr auto modifiers = 0x6b8; // PlayerModifiers
			constexpr auto playerCollider = 0x6c0; // CapsuleCollider
			constexpr auto Belt = 0x6c8; // PlayerBelt
			constexpr auto playerRigidbody = 0x6d0; // Rigidbody
			constexpr auto userID = 0x6d8; // ulong
			constexpr auto UserIDString = 0x6e0; // string
			constexpr auto gamemodeteam = 0x6e8; // int
			constexpr auto reputation = 0x6ec; // int
			constexpr auto _displayName = 0x6f0; // string
			constexpr auto _lastSetName = 0x6f8; // string
			constexpr auto playerColliderStanding = 0x700; // BasePlayer.CapsuleColliderInfo
			constexpr auto playerColliderDucked = 0x714; // BasePlayer.CapsuleColliderInfo
			constexpr auto playerColliderCrawling = 0x728; // BasePlayer.CapsuleColliderInfo
			constexpr auto playerColliderLyingDown = 0x73c; // BasePlayer.CapsuleColliderInfo
			constexpr auto cachedProtection = 0x750; // ProtectionProperties
			constexpr auto lastHeadshotSoundTime = 0x758; // float
			constexpr auto nextColliderRefreshTime = 0x75c; // float
			constexpr auto clothingBlocksAiming = 0x760; // bool
			constexpr auto clothingMoveSpeedReduction = 0x764; // float
			constexpr auto clothingWaterSpeedBonus = 0x768; // float
			constexpr auto clothingAccuracyBonus = 0x76c; // float
			constexpr auto equippingBlocked = 0x770; // bool
			constexpr auto eggVision = 0x774; // float
			constexpr auto activeTelephone = 0x778; // PhoneController
			constexpr auto designingAIEntity = 0x780; // BaseEntity
		}
		namespace BaseMovement
		{
			constexpr auto adminCheat = 0x18; // bool
			constexpr auto adminSpeed = 0x1c; // float
			constexpr auto Ownerk__BackingField = 0x20; // BasePlayer
			constexpr auto InheritedVelocityk__BackingField = 0x28; // Vector3
			constexpr auto TargetMovementk__BackingField = 0x34; // Vector3
			constexpr auto Runningk__BackingField = 0x40; // float
			constexpr auto Duckingk__BackingField = 0x44; // float
			constexpr auto Crawlingk__BackingField = 0x48; // float
			constexpr auto Groundedk__BackingField = 0x4c; // float
			constexpr auto lastTeleportedTime = 0x50; // float
		}
		namespace BaseMountable
		{
			constexpr auto __menuOption_Menu_Mount = 0x240; // Option
			constexpr auto eyePositionOverride = 0x298; // Transform
			constexpr auto eyeCenterOverride = 0x2a0; // Transform
			constexpr auto pitchClamp = 0x2a8; // Vector2
			constexpr auto yawClamp = 0x2b0; // Vector2
			constexpr auto canWieldItems = 0x2b8; // bool
			constexpr auto relativeViewAngles = 0x2b9; // bool
			constexpr auto mountAnchor = 0x2c0; // Transform
			constexpr auto mountPose = 0x2c8; // PlayerModel.MountPoses
			constexpr auto maxMountDistance = 0x2cc; // float
			constexpr auto dismountPositions = 0x2d0; // Transform[]
			constexpr auto checkPlayerLosOnMount = 0x2d8; // bool
			constexpr auto disableMeshCullingForPlayers = 0x2d9; // bool
			constexpr auto allowHeadLook = 0x2da; // bool
			constexpr auto ignoreVehicleParent = 0x2db; // bool
			constexpr auto modifiesPlayerCollider = 0x2dc; // bool
			constexpr auto customPlayerCollider = 0x2e0; // BasePlayer.CapsuleColliderInfo
			constexpr auto mountSoundDef = 0x2f8; // SoundDefinition
			constexpr auto swapSoundDef = 0x300; // SoundDefinition
			constexpr auto dismountSoundDef = 0x308; // SoundDefinition
			constexpr auto mountTimeStatType = 0x310; // BaseMountable.MountStatType
			constexpr auto allowedGestures = 0x314; // BaseMountable.MountGestureType
			constexpr auto canDrinkWhileMounted = 0x318; // bool
			constexpr auto allowSleeperMounting = 0x319; // bool
			constexpr auto animateClothInLocalSpace = 0x31a; // bool
			constexpr auto MountedCameraMode = 0x31c; // BasePlayer.CameraMode
			constexpr auto isMobile = 0x320; // bool
			constexpr auto SideLeanAmount = 0x324; // float // NEW WTF
		}
		namespace PlayerModel
		{
			constexpr auto _smoothAimWeight = 0x18; // float
			constexpr auto _smoothVelocity = 0x1c; // float
			constexpr auto _smoothlookAngle = 0x20; // Vector3
			constexpr auto allowMountedHeadLook = 0x2c; // bool
			constexpr auto smoothLookDir = 0x30; // Vector3
			constexpr auto lastSafeLookDir = 0x3c; // Vector3
			constexpr auto Shoulders = 0x48; // Transform[]
			constexpr auto AdditionalSpineBones = 0x50; // Transform[]
			constexpr auto LegParts = 0x58; // List(SkinnedMeshRenderer)
			constexpr auto fakeSpineBones = 0x60; // Transform[]
			constexpr auto extraLeanBack = 0x68; // float
			constexpr auto drawState = 0x6c; // Nullable(bool)
			constexpr auto timeInArmsMode = 0x70; // float
			constexpr auto collision = 0x78; // BoxCollider
			constexpr auto censorshipCube = 0x80; // GameObject
			constexpr auto censorshipCubeBreasts = 0x88; // GameObject
			constexpr auto jawBone = 0x90; // GameObject
			constexpr auto neckBone = 0x98; // GameObject
			constexpr auto headBone = 0xa0; // GameObject
			constexpr auto eyeController = 0xa8; // EyeController
			constexpr auto blinkController = 0xb0; // EyeBlink
			constexpr auto SpineBones = 0xb8; // Transform[]
			constexpr auto leftFootBone = 0xc0; // Transform
			constexpr auto rightFootBone = 0xc8; // Transform
			constexpr auto leftHandPropBone = 0xd0; // Transform
			constexpr auto rightHandPropBone = 0xd8; // Transform
			constexpr auto rightHandTarget = 0xe0; // Vector3
			constexpr auto leftHandTargetPosition = 0xec; // Vector3
			constexpr auto leftHandTargetRotation = 0xf8; // Quaternion
			constexpr auto rightHandTargetPosition = 0x108; // Vector3
			constexpr auto rightHandTargetRotation = 0x114; // Quaternion
			constexpr auto steeringTargetDegrees = 0x124; // float
			constexpr auto rightFootTargetPosition = 0x128; // Vector3
			constexpr auto rightFootTargetRotation = 0x134; // Quaternion
			constexpr auto leftFootTargetPosition = 0x144; // Vector3
			constexpr auto leftFootTargetRotation = 0x150; // Quaternion
			constexpr auto CinematicAnimationController = 0x160; // RuntimeAnimatorController
			constexpr auto DefaultAvatar = 0x168; // Avatar
			constexpr auto CinematicAvatar = 0x170; // Avatar
			constexpr auto DefaultHoldType = 0x178; // RuntimeAnimatorController
			constexpr auto SleepGesture = 0x180; // RuntimeAnimatorController
			constexpr auto CrawlToIncapacitatedGesture = 0x188; // RuntimeAnimatorController
			constexpr auto StandToIncapacitatedGesture = 0x190; // RuntimeAnimatorController
			constexpr auto CurrentGesture = 0x198; // RuntimeAnimatorController
			constexpr auto MaleSkin = 0x1a0; // SkinSetCollection
			constexpr auto FemaleSkin = 0x1a8; // SkinSetCollection
			constexpr auto subsurfaceProfile = 0x1b0; // SubsurfaceProfile
			constexpr auto voiceVolume = 0x1b8; // float
			constexpr auto skinColor = 0x1bc; // float
			constexpr auto skinNumber = 0x1c0; // float
			constexpr auto meshNumber = 0x1c4; // float
			constexpr auto hairNumber = 0x1c8; // float
			constexpr auto skinType = 0x1cc; // int
			constexpr auto movementSounds = 0x1d0; // MovementSounds
			constexpr auto showSash = 0x1d8; // bool
			constexpr auto tempPoseType = 0x1dc; // int
			constexpr auto underwearSkin = 0x1e0; // uint
			constexpr auto overrideSkinSeedk__BackingField = 0x1e8; // ulong
			constexpr auto AimAnglesk__BackingField = 0x1f0; // Quaternion
			constexpr auto LookAnglesk__BackingField = 0x200; // Quaternion
			constexpr auto modelState = 0x210; // ModelState
			constexpr auto position = 0x218; // Vector3
			constexpr auto velocity = 0x224; // Vector3
			constexpr auto speedOverride = 0x230; // Vector3
			constexpr auto newVelocity = 0x23c; // Vector3
			constexpr auto rotation = 0x248; // Quaternion
			constexpr auto mountedRotation = 0x258; // Quaternion
			constexpr auto smoothLeftFootIK = 0x268; // Vector3
			constexpr auto smoothRightFootIK = 0x274; // Vector3
			constexpr auto drawShadowOnly = 0x280; // bool
			constexpr auto isIncapacitated = 0x281; // bool
			constexpr auto flinchLocation = 0x284; // uint
			constexpr auto visible = 0x288; // bool
			constexpr auto nameTag = 0x290; // PlayerNameTag
			constexpr auto animatorNeedsWarmup = 0x298; // bool
			constexpr auto isLocalPlayer = 0x299; // bool
			constexpr auto aimSoundDef = 0x2a0; // SoundDefinition
			constexpr auto aimEndSoundDef = 0x2a8; // SoundDefinition
			constexpr auto InGesture = 0x2b0; // bool
			constexpr auto CurrentGestureConfig = 0x2b8; // GestureConfig
			constexpr auto InCinematic = 0x2c0; // bool
			constexpr auto defaultAnimatorController = 0x2c8; // RuntimeAnimatorController
			constexpr auto _multiMesh = 0x2d0; // SkinnedMultiMesh
			constexpr auto _animator = 0x2d8; // Animator
			constexpr auto _lodGroup = 0x2e0; // LODGroup
			constexpr auto _currentGesture = 0x2e8; // RuntimeAnimatorController
			constexpr auto holdTypeLock = 0x2f0; // float
			constexpr auto hasHeldEntity = 0x2f4; // bool
			constexpr auto wasMountedRightAim = 0x2f5; // bool
			constexpr auto cachedMask = 0x2f8; // int
			constexpr auto cachedConstructionMask = 0x2fc; // int
			constexpr auto WorkshopHeldEntity = 0x300; // HeldEntity
			constexpr auto wasCrawling = 0x308; // bool
			constexpr auto mountedSpineLookWeight = 0x30c; // float
			constexpr auto mountedAnimSpeed = 0x310; // float
			constexpr auto preserveBones = 0x314; // bool
			constexpr auto downLimitOverride = 0x318; // Nullable(float)
			constexpr auto IsNpck__BackingField = 0x320; // bool
			constexpr auto timeSinceReactionStart = 0x324; // TimeSince
			constexpr auto timeSinceLeftFootTest = 0x328; // TimeSince
			constexpr auto cachedLeftFootPos = 0x32c; // Vector3
			constexpr auto cachedLeftFootNormal = 0x338; // Vector3
			constexpr auto timeSinceRightFootTest = 0x344; // TimeSince
			constexpr auto cachedRightFootPos = 0x348; // Vector3
			constexpr auto cachedRightFootNormal = 0x354; // Vector3
		}
		namespace BaseCombatEntity
		{
			constexpr auto __menuOption_Menu_Pickup = 0x168; // Option
			constexpr auto skeletonProperties = 0x1c0; // SkeletonProperties
			constexpr auto baseProtection = 0x1c8; // ProtectionProperties
			constexpr auto startHealth = 0x1d0; // float
			constexpr auto pickup = 0x1d8; // BaseCombatEntity.Pickup
			constexpr auto repair = 0x1f8; // BaseCombatEntity.Repair
			constexpr auto ShowHealthInfo = 0x220; // bool
			constexpr auto lifestate = 0x224; // BaseCombatEntity.LifeState
			constexpr auto sendsHitNotification = 0x228; // bool
			constexpr auto sendsMeleeHitNotification = 0x229; // bool
			constexpr auto markAttackerHostile = 0x22a; // bool
			constexpr auto _health = 0x22c; // float
			constexpr auto _maxHealth = 0x230; // float
			constexpr auto faction = 0x234; // BaseCombatEntity.Faction
			constexpr auto deathTime = 0x238; // float
			constexpr auto lastNotifyFrame = 0x23c; // int
		}
		namespace PlayerEyes
		{
			constexpr auto thirdPersonSleepingOffset = 0x20; // Vector3
			constexpr auto defaultLazyAim = 0x30; // LazyAimProperties
			constexpr auto viewOffset = 0x38; // Vector3
			constexpr auto bodyRotationk__BackingField = 0x44; // Quaternion
			constexpr auto headAnglesk__BackingField = 0x54; // Vector3
			constexpr auto rotationLookk__BackingField = 0x60; // Quaternion
			constexpr auto IsAltLookingLegsThresholdk__BackingField = 0x70; // bool
		}
		namespace BaseEntity
		{
			constexpr auto ragdoll = 0x78; // Ragdoll
			constexpr auto positionLerp = 0x80; // PositionLerp
			constexpr auto menuOptions = 0x88; // List(Option)
			constexpr auto broadcastProtocol = 0x90; // uint
			constexpr auto links = 0x98; // List(EntityLink)
			constexpr auto linkedToNeighbours = 0xa0; // bool
			constexpr auto _pendingFileRequests = 0xa8; // List(BaseEntity.PendingFileRequest)
			constexpr auto updateParentingAction = 0xb0; // Action
			constexpr auto addedToParentEntity = 0xb8; // BaseEntity
			constexpr auto itemSkin = 0xc0; // ItemSkin
			constexpr auto entitySlots = 0xc8; // EntityRef[]
			constexpr auto triggers = 0xd0; // List(TriggerBase)
			constexpr auto isVisible = 0xd8; // bool
			constexpr auto isAnimatorVisible = 0xd9; // bool
			constexpr auto isShadowVisible = 0xda; // bool
			constexpr auto localOccludee = 0xe0; // OccludeeSphere
			constexpr auto Weightk__BackingField = 0x100; // float
			constexpr auto bounds = 0x104; // Bounds
			constexpr auto impactEffect = 0x120; // GameObjectRef
			constexpr auto enableSaving = 0x128; // bool
			constexpr auto syncPosition = 0x129; // bool
			constexpr auto model = 0x130; // Model
			constexpr auto flags = 0x138; // BaseEntity.Flags
			constexpr auto parentBone = 0x13c; // uint
			constexpr auto skinID = 0x140; // ulong
			constexpr auto _components = 0x148; // EntityComponentBase[]
			constexpr auto HasBrain = 0x150; // bool
			constexpr auto _name = 0x158; // string
			constexpr auto OwnerIDk__BackingField = 0x160; // ulong
		}
		namespace BaseProjectile
		{
			constexpr auto NoiseRadius = 0x280; // float
			constexpr auto damageScale = 0x284; // float
			constexpr auto distanceScale = 0x288; // float
			constexpr auto projectileVelocityScale = 0x28c; // float
			constexpr auto automatic = 0x290; // bool
			constexpr auto usableByTurret = 0x291; // bool
			constexpr auto turretDamageScale = 0x294; // float
			constexpr auto attackFX = 0x298; // GameObjectRef
			constexpr auto silencedAttack = 0x2a0; // GameObjectRef
			constexpr auto muzzleBrakeAttack = 0x2a8; // GameObjectRef
			constexpr auto MuzzlePoint = 0x2b0; // Transform
			constexpr auto reloadTime = 0x2b8; // float
			constexpr auto canUnloadAmmo = 0x2bc; // bool
			constexpr auto primaryMagazine = 0x2c0; // BaseProjectile.Magazine
			constexpr auto fractionalReload = 0x2c8; // bool
			constexpr auto reloadStartDuration = 0x2cc; // float
			constexpr auto reloadFractionDuration = 0x2d0; // float
			constexpr auto reloadEndDuration = 0x2d4; // float
			constexpr auto aimSway = 0x2d8; // float
			constexpr auto aimSwaySpeed = 0x2dc; // float
			constexpr auto recoil = 0x2e0; // RecoilProperties
			constexpr auto aimconeCurve = 0x2e8; // AnimationCurve
			constexpr auto aimCone = 0x2f0; // float
			constexpr auto hipAimCone = 0x2f4; // float
			constexpr auto aimconePenaltyPerShot = 0x2f8; // float
			constexpr auto aimConePenaltyMax = 0x2fc; // float
			constexpr auto aimconePenaltyRecoverTime = 0x300; // float
			constexpr auto aimconePenaltyRecoverDelay = 0x304; // float
			constexpr auto stancePenaltyScale = 0x308; // float
			constexpr auto hasADS = 0x30c; // bool
			constexpr auto noAimingWhileCycling = 0x30d; // bool
			constexpr auto manualCycle = 0x30e; // bool
			constexpr auto needsCycle = 0x30f; // bool
			constexpr auto isCycling = 0x310; // bool
			constexpr auto aiming = 0x311; // bool
			constexpr auto resetDuration = 0x314; // float
			constexpr auto numShotsFired = 0x318; // int
			constexpr auto nextReloadTime = 0x31c; // float
			constexpr auto startReloadTime = 0x320; // float
			constexpr auto stancePenalty = 0x324; // float
			constexpr auto aimconePenalty = 0x328; // float
			constexpr auto cachedModHash = 0x32c; // uint
			constexpr auto sightAimConeScale = 0x330; // float
			constexpr auto sightAimConeOffset = 0x334; // float
			constexpr auto hipAimConeScale = 0x338; // float
			constexpr auto hipAimConeOffset = 0x33c; // float
			constexpr auto isReloading = 0x340; // bool
			constexpr auto swaySampleTime = 0x344; // float
			constexpr auto lastShotTime = 0x348; // float
			constexpr auto reloadPressTime = 0x34c; // float
			constexpr auto ammoTypePreReload = 0x350; // ItemDefinition
			constexpr auto fractionalReloadDesiredCount = 0x358; // int
			constexpr auto fractionalReloadNumAdded = 0x35c; // int
			constexpr auto triggerReady = 0x360; // bool
			constexpr auto nextHeightCheckTime = 0x364; // float
			constexpr auto cachedUnderground = 0x368; // bool
			constexpr auto createdProjectiles = 0x370; // List(Projectile)

		}
		namespace ItemContainer
		{
			constexpr auto flags = 0x10; // ItemContainer.Flag
			constexpr auto allowedContents = 0x14; // ItemContainer.ContentsType
			constexpr auto onlyAllowedItems = 0x18; // ItemDefinition[]
			constexpr auto availableSlots = 0x20; // List(ItemSlot)
			constexpr auto capacity = 0x28; // int
			constexpr auto uid = 0x2c; // uint
			constexpr auto dirty = 0x30; // bool
			constexpr auto itemList = 0x38; // List(Item)
			constexpr auto temperature = 0x40; // float
			constexpr auto parent = 0x48; // Item
			constexpr auto playerOwner = 0x50; // BasePlayer
			constexpr auto entityOwner = 0x58; // BaseEntity
			constexpr auto isServer = 0x60; // bool
			constexpr auto maxStackSize = 0x64; // int
		}
		namespace ItemDefinition
		{
			constexpr auto itemid = 0x18; // int
			constexpr auto shortname = 0x20; // string
			constexpr auto displayName = 0x28; // Translate.Phrase
			constexpr auto displayDescription = 0x30; // Translate.Phrase
			constexpr auto iconSprite = 0x38; // Sprite
			constexpr auto category = 0x40; // ItemCategory
			constexpr auto selectionPanel = 0x44; // ItemSelectionPanel
			constexpr auto maxDraggable = 0x48; // int
			constexpr auto itemType = 0x4c; // ItemContainer.ContentsType
			constexpr auto amountType = 0x50; // ItemDefinition.AmountType
			constexpr auto occupySlots = 0x54; // ItemSlot
			constexpr auto stackable = 0x58; // int
			constexpr auto quickDespawn = 0x5c; // bool
			constexpr auto rarity = 0x60; // Rarity
			constexpr auto spawnAsBlueprint = 0x64; // bool
			constexpr auto inventoryGrabSound = 0x68; // SoundDefinition
			constexpr auto inventoryDropSound = 0x70; // SoundDefinition
			constexpr auto physImpactSoundDef = 0x78; // SoundDefinition
			constexpr auto condition = 0x80; // ItemDefinition.Condition
			constexpr auto hidden = 0x98; // bool
			constexpr auto flags = 0x9c; // ItemDefinition.Flag
			constexpr auto steamItem = 0xa0; // SteamInventoryItem
			constexpr auto steamDlc = 0xa8; // SteamDLCItem
			constexpr auto Parent = 0xb0; // ItemDefinition
			constexpr auto worldModelPrefab = 0xb8; // GameObjectRef
			constexpr auto isRedirectOf = 0xc0; // ItemDefinition
			constexpr auto redirectVendingBehaviour = 0xc8; // ItemDefinition.RedirectVendingBehaviour
			constexpr auto itemMods = 0xd0; // ItemMod[]
			constexpr auto Traits = 0xd8; // BaseEntity.TraitFlag
			constexpr auto skins = 0xe0; // ItemSkinDirectory.Skin[]
			constexpr auto _skins2 = 0xe8; // IPlayerItemDefinition[]
			constexpr auto panel = 0xf0; // GameObject
			constexpr auto ItemModWearablek__BackingField = 0xf8; // ItemModWearable
			constexpr auto isHoldablek__BackingField = 0x100; // bool
			constexpr auto isUsablek__BackingField = 0x101; // bool
			constexpr auto CraftableWithSkink__BackingField = 0x102; // bool
			constexpr auto Children = 0x108; // ItemDefinition[]
		}
		namespace AttackEntity
		{
			constexpr auto deployDelay = 0x1f8; // float
			constexpr auto repeatDelay = 0x1fc; // float
			constexpr auto animationDelay = 0x200; // float
			constexpr auto effectiveRange = 0x204; // float
			constexpr auto npcDamageScale = 0x208; // float
			constexpr auto CurrentBurst = 0x360; 
			constexpr auto attackLengthMin = 0x20c; // float
			constexpr auto attackLengthMax = 0x210; // float
			constexpr auto attackSpacing = 0x214; // float
			constexpr auto aiAimSwayOffset = 0x218; // float
			constexpr auto aiAimCone = 0x21c; // float
			constexpr auto aiOnlyInRange = 0x220; // bool
			constexpr auto CloseRangeAddition = 0x224; // float
			constexpr auto MediumRangeAddition = 0x228; // float
			constexpr auto LongRangeAddition = 0x22c; // float
			constexpr auto CanUseAtMediumRange = 0x230; // bool
			constexpr auto CanUseAtLongRange = 0x231; // bool
			constexpr auto reloadSounds = 0x238; // SoundDefinition[]
			constexpr auto thirdPersonMeleeSound = 0x240; // SoundDefinition
			constexpr auto recoilCompDelayOverride = 0x248; // float
			constexpr auto wantsRecoilComp = 0x24c; // bool
			constexpr auto nextAttackTime = 0x250; // float
			constexpr auto lastTickTime = 0x254; // float
			constexpr auto nextTickTime = 0x258; // float
			constexpr auto timeSinceDeploy = 0x25c; // float
			constexpr auto lastRecoilCompTime = 0x260; // float
			constexpr auto startAimingDirection = 0x264; // Vector3
			constexpr auto wasDoingRecoilComp = 0x270; // bool
			constexpr auto reductionSpeed = 0x274; // Vector3
		}
		namespace PlayerWalkMovement
		{
			constexpr auto zeroFrictionMaterial = 0x58; // PhysicMaterial
			constexpr auto highFrictionMaterial = 0x60; // PhysicMaterial
			constexpr auto capsuleHeight = 0x68; // float
			constexpr auto capsuleCenter = 0x6c; // float
			constexpr auto capsuleHeightDucked = 0x70; // float
			constexpr auto capsuleCenterDucked = 0x74; // float
			constexpr auto capsuleHeightCrawling = 0x78; // float
			constexpr auto capsuleCenterCrawling = 0x7c; // float
			constexpr auto gravityTestRadius = 0x80; // float
			constexpr auto gravityMultiplier = 0x84; // float
			constexpr auto gravityMultiplierSwimming = 0x88; // float
			constexpr auto maxAngleWalking = 0x8c; // float
			constexpr auto maxAngleClimbing = 0x90; // float
			constexpr auto maxAngleSliding = 0x94; // float
			constexpr auto maxStepHeight = 0x98; // float
			constexpr auto body = 0xa0; // Rigidbody
			constexpr auto initialColDetectionMode = 0xa8; // CollisionDetectionMode
			constexpr auto capsule = 0xb0; // CapsuleCollider
			constexpr auto ladder = 0xb8; // TriggerLadder
			constexpr auto maxVelocity = 0xc0; // float
			constexpr auto groundAngle = 0xc4; // float
			constexpr auto groundAngleNew = 0xc8; // float
			constexpr auto groundTime = 0xcc; // float
			constexpr auto jumpTime = 0xd0; // float
			constexpr auto landTime = 0xd4; // float
			constexpr auto previousPosition = 0xd8; // Vector3
			constexpr auto previousVelocity = 0xe4; // Vector3
			constexpr auto previousInheritedVelocity = 0xf0; // Vector3
			constexpr auto groundNormal = 0xfc; // Vector3
			constexpr auto groundNormalNew = 0x108; // Vector3
			constexpr auto groundVelocity = 0x114; // Vector3
			constexpr auto groundVelocityNew = 0x120; // Vector3
			constexpr auto nextSprintTime = 0x12c; // float
			constexpr auto lastSprintTime = 0x130; // float
			constexpr auto sprintForced = 0x134; // bool
			constexpr auto attemptedMountTime = 0x138; // TimeSince
			constexpr auto modify = 0x13c; // BaseEntity.MovementModify
			constexpr auto grounded = 0x140; // bool
			constexpr auto climbing = 0x141; // bool
			constexpr auto sliding = 0x142; // bool
			constexpr auto swimming = 0x143; // bool
			constexpr auto wasSwimming = 0x144; // bool
			constexpr auto jumping = 0x145; // bool
			constexpr auto wasJumping = 0x146; // bool
			constexpr auto falling = 0x147; // bool
			constexpr auto wasFalling = 0x148; // bool
			constexpr auto flying = 0x149; // bool
			constexpr auto wasFlying = 0x14a; // bool
			constexpr auto forcedDuckDelta = 0x14c; // float
		}
		namespace ModelState
		{
			constexpr auto ShouldPool = 0x10; // bool
			constexpr auto _disposed = 0x11; // bool
			constexpr auto waterLevel = 0x14; // float
			constexpr auto lookDir = 0x18; // Vector3
			constexpr auto flags = 0x24; // int
			constexpr auto poseType = 0x28; // int
			constexpr auto inheritedVelocity = 0x2c; // Vector3
		}
		namespace Projectile
		{
			constexpr auto initialVelocity = 0x18; // Vector3
			constexpr auto drag = 0x24; // float
			constexpr auto gravityModifier = 0x28; // float
			constexpr auto thickness = 0x2c; // float
			constexpr auto initialDistance = 0x30; // float
			constexpr auto remainInWorld = 0x34; // bool
			constexpr auto stickProbability = 0x38; // float
			constexpr auto breakProbability = 0x3c; // float
			constexpr auto conditionLoss = 0x40; // float
			constexpr auto ricochetChance = 0x44; // float
			constexpr auto penetrationPower = 0x48; // float
			constexpr auto damageProperties = 0x50; // DamageProperties
			constexpr auto damageDistances = 0x58; // MinMax
			constexpr auto damageMultipliers = 0x60; // MinMax
			constexpr auto damageTypes = 0x68; // List(DamageTypeEntry)
			constexpr auto rendererToScale = 0x70; // ScaleRenderer
			constexpr auto firstPersonRenderer = 0x78; // ScaleRenderer
			constexpr auto createDecals = 0x80; // bool
			constexpr auto doDefaultHitEffects = 0x81; // bool
			constexpr auto flybySound = 0x88; // SoundDefinition
			constexpr auto flybySoundDistance = 0x90; // float
			constexpr auto closeFlybySound = 0x98; // SoundDefinition
			constexpr auto closeFlybyDistance = 0xa0; // float
			constexpr auto tumbleSpeed = 0xa4; // float
			constexpr auto tumbleAxis = 0xa8; // Vector3
			constexpr auto swimScale = 0xb4; // Vector3
			constexpr auto swimSpeed = 0xc0; // Vector3
			constexpr auto owner = 0xd0; // BasePlayer
			constexpr auto sourceWeaponPrefab = 0xd8; // AttackEntity
			constexpr auto sourceProjectilePrefab = 0xe0; // Projectile
			constexpr auto mod = 0xe8; // ItemModProjectile
			constexpr auto projectileID = 0xf0; // int
			constexpr auto seed = 0xf4; // int
			constexpr auto clientsideEffect = 0xf8; // bool
			constexpr auto clientsideAttack = 0xf9; // bool
			constexpr auto integrity = 0xfc; // float
			constexpr auto maxDistance = 0x100; // float
			constexpr auto modifier = 0x104; // Projectile.Modifier
			constexpr auto invisible = 0x114; // bool
			constexpr auto currentVelocity = 0x118; // Vector3
			constexpr auto currentPosition = 0x124; // Vector3
			constexpr auto traveledDistance = 0x130; // float
			constexpr auto traveledTime = 0x134; // float
			constexpr auto launchTime = 0x138; // float
			constexpr auto sentPosition = 0x13c; // Vector3
			constexpr auto previousPosition = 0x148; // Vector3
			constexpr auto previousVelocity = 0x154; // Vector3
			constexpr auto previousTraveledTime = 0x160; // float
			constexpr auto isRicochet = 0x164; // bool
			constexpr auto isRetiring = 0x165; // bool
			constexpr auto flybyPlayed = 0x166; // bool
			constexpr auto wasFacingPlayer = 0x167; // bool
			constexpr auto flybyPlane = 0x168; // Plane
			constexpr auto flybyRay = 0x178; // Ray
			constexpr auto cleanupAction = 0x190; // Action
			constexpr auto hitTest = 0x198; // HitTest
			constexpr auto swimRandom = 0x1a0; // float
		}
		namespace HitTest
		{
			constexpr auto type = 0x10; // HitTest.Type
			constexpr auto AttackRay = 0x14; // Ray
			constexpr auto Radius = 0x2c; // float
			constexpr auto Forgiveness = 0x30; // float
			constexpr auto MaxDistance = 0x34; // float
			constexpr auto RayHit = 0x38; // RaycastHit
			constexpr auto MultiHit = 0x64; // bool
			constexpr auto BestHit = 0x65; // bool
			constexpr auto DidHit = 0x66; // bool
			constexpr auto damageProperties = 0x68; // DamageProperties
			constexpr auto gameObject = 0x70; // GameObject
			constexpr auto collider = 0x78; // Collider
			constexpr auto ignoreEntity = 0x80; // BaseEntity
			constexpr auto HitEntity = 0x88; // BaseEntity
			constexpr auto HitPoint = 0x90; // Vector3
			constexpr auto HitNormal = 0x9c; // Vector3
			constexpr auto HitDistance = 0xa8; // float
			constexpr auto HitTransform = 0xb0; // Transform
			constexpr auto HitPart = 0xb8; // uint
			constexpr auto HitMaterial = 0xc0; // string
		}
		namespace ProjectileWeaponMod
		{
			constexpr auto defaultSilencerEffect = 0x168; // GameObjectRef
			constexpr auto isSilencer = 0x170; // bool
			constexpr auto repeatDelay = 0x174; // ProjectileWeaponMod.Modifier
			constexpr auto projectileVelocity = 0x180; // ProjectileWeaponMod.Modifier
			constexpr auto projectileDamage = 0x18c; // ProjectileWeaponMod.Modifier
			constexpr auto projectileDistance = 0x198; // ProjectileWeaponMod.Modifier
			constexpr auto aimsway = 0x1a4; // ProjectileWeaponMod.Modifier
			constexpr auto aimswaySpeed = 0x1b0; // ProjectileWeaponMod.Modifier
			constexpr auto recoil = 0x1bc; // ProjectileWeaponMod.Modifier
			constexpr auto sightAimCone = 0x1c8; // ProjectileWeaponMod.Modifier
			constexpr auto hipAimCone = 0x1d4; // ProjectileWeaponMod.Modifier
			constexpr auto isLight = 0x1e0; // bool
			constexpr auto isMuzzleBrake = 0x1e1; // bool
			constexpr auto isMuzzleBoost = 0x1e2; // bool
			constexpr auto isScope = 0x1e3; // bool
			constexpr auto zoomAmountDisplayOnly = 0x1e4; // float
			constexpr auto magazineCapacity = 0x1e8; // ProjectileWeaponMod.Modifier
			constexpr auto needsOnForEffects = 0x1f4; // bool
		}
		namespace RecoilProperties
		{
			constexpr auto recoilYawMin = 0x18; // float
			constexpr auto recoilYawMax = 0x1c; // float
			constexpr auto recoilPitchMin = 0x20; // float
			constexpr auto recoilPitchMax = 0x24; // float
			constexpr auto timeToTakeMin = 0x28; // float
			constexpr auto timeToTakeMax = 0x2c; // float
			constexpr auto ADSScale = 0x30; // float
			constexpr auto movementPenalty = 0x34; // float
			constexpr auto clampPitch = 0x38; // float
			constexpr auto pitchCurve = 0x40; // AnimationCurve
			constexpr auto yawCurve = 0x48; // AnimationCurve
			constexpr auto useCurves = 0x50; // bool
			constexpr auto curvesAsScalar = 0x51; // bool
			constexpr auto shotsUntilMax = 0x54; // int
			constexpr auto maxRecoilRadius = 0x58; // float
			constexpr auto overrideAimconeWithCurve = 0x5c; // bool
			constexpr auto aimconeCurveScale = 0x60; // float
			constexpr auto aimconeCurve = 0x68; // AnimationCurve
			constexpr auto aimconeProbabilityCurve = 0x70; // AnimationCurve
			constexpr auto newRecoilOverride = 0x78; // RecoilProperties
		}
		namespace Item
		{
			constexpr auto amountOverride = 0x10; // Nullable(int)
			constexpr auto _condition = 0x18; // float
			constexpr auto _maxCondition = 0x1c; // float
			constexpr auto info = 0x20; // ItemDefinition
			constexpr auto uid = 0x28; // uint
			constexpr auto dirty = 0x2c; // bool
			constexpr auto amount = 0x30; // int
			constexpr auto position = 0x34; // int
			constexpr auto busyTime = 0x38; // float
			constexpr auto removeTime = 0x3c; // float
			constexpr auto fuel = 0x40; // float
			constexpr auto isServer = 0x44; // bool
			constexpr auto instanceData = 0x48; // Item.InstanceData
			constexpr auto skin = 0x50; // ulong
			constexpr auto name = 0x58; // string
			constexpr auto text = 0x60; // string
			constexpr auto cookTimeLeft = 0x68; // float
			constexpr auto progressBar = 0x6c; // float
			constexpr auto OnDirty = 0x70; // Action(Item)
			constexpr auto flags = 0x78; // Item.Flag
			constexpr auto contents = 0x80; // ItemContainer
			constexpr auto parent = 0x88; // ItemContainer
			constexpr auto worldEnt = 0x90; // EntityRef
			constexpr auto heldEntity = 0xa0; // EntityRef

		}
		namespace FlintStrikeWeapon
		{
			constexpr auto successFraction = 0x378; // float
			constexpr auto strikeRecoil = 0x380; // RecoilProperties
			constexpr auto _didSparkThisFrame = 0x388; // bool
			constexpr auto _isStriking = 0x389; // bool
			constexpr auto strikes = 0x38c; // int
			constexpr auto lastSpectatorAttack = 0x390; // TimeSince
		}
		namespace BowWeapon
		{
			constexpr auto attackReady = 0x378; // bool
			constexpr auto arrowBack = 0x37c; // float
			constexpr auto swapArrows = 0x380; // SwapArrows
			constexpr auto wasAiming = 0x388; // bool
		}
		namespace CompoundBowWeapon
		{
			constexpr auto stringHoldDurationMax = 0x390; // float
			constexpr auto stringBonusDamage = 0x394; // float
			constexpr auto stringBonusDistance = 0x398; // float
			constexpr auto stringBonusVelocity = 0x39c; // float
			constexpr auto movementPenaltyRampUpTime = 0x3a0; // float
			constexpr auto conditionLossPerSecondHeld = 0x3a4; // float
			constexpr auto conditionLossHeldDelay = 0x3a8; // float
			constexpr auto chargeUpSoundDef = 0x3b0; // SoundDefinition
			constexpr auto stringHeldSoundDef = 0x3b8; // SoundDefinition
			constexpr auto drawFinishSoundDef = 0x3c0; // SoundDefinition
			constexpr auto chargeUpSound = 0x3c8; // Sound
			constexpr auto stringHeldSound = 0x3d0; // Sound
			constexpr auto movementPenalty = 0x3d8; // float
			constexpr auto lastMoveTime = 0x3dc; // float
			constexpr auto currentHoldProgress = 0x3e0; // float
			constexpr auto stringHoldTimeStart = 0x3e4; // float
			constexpr auto drawFinishPlayed = 0x3e8; // bool
		}
		namespace HeldEntity
		{
			constexpr auto _punches = 0x168; // List(HeldEntity.PunchEntry)
			constexpr auto punchAdded = 0x170; // Vector3
			constexpr auto lastPunchTime = 0x17c; // float
			constexpr auto worldModelAnimator = 0x180; // Animator
			constexpr auto thirdPersonDeploySound = 0x188; // SoundDefinition
			constexpr auto thirdPersonAimSound = 0x190; // SoundDefinition
			constexpr auto thirdPersonAimEndSound = 0x198; // SoundDefinition
			constexpr auto viewModel = 0x1a0; // ViewModel
			constexpr auto isDeployed = 0x1a8; // bool
			constexpr auto nextExamineTime = 0x1ac; // float
			constexpr auto handBone = 0x1b0; // string
			constexpr auto HoldAnimationOverride = 0x1b8; // AnimatorOverrideController
			constexpr auto isBuildingTool = 0x1c0; // bool
			constexpr auto hostileScore = 0x1c4; // float
			constexpr auto holsterInfo = 0x1c8; // HeldEntity.HolsterInfo
			constexpr auto HeldCameraMode = 0x1d0; // BasePlayer.CameraMode
			constexpr auto FirstPersonArmOffset = 0x1d4; // Vector3
			constexpr auto FirstPersonArmRotation = 0x1e0; // Vector3
			constexpr auto FirstPersonRotationStrength = 0x1ec; // float
			constexpr auto ownerItemUID = 0x1f0; // uint
		}
		namespace BaseViewModel
		{
			constexpr auto lazyaimRegular = 0x18; // LazyAimProperties
			constexpr auto lazyaimIronsights = 0x20; // LazyAimProperties
			constexpr auto pivot = 0x28; // Transform
			constexpr auto useViewModelCamera = 0x30; // bool
			constexpr auto wantsHeldItemFlags = 0x31; // bool
			constexpr auto hideSightMeshes = 0x38; // GameObject[]
			constexpr auto isGestureViewModel = 0x40; // bool
			constexpr auto MuzzlePoint = 0x48; // Transform
			constexpr auto subsurfaceProfile = 0x50; // SubsurfaceProfile
			constexpr auto animator = 0x58; // Animator
			constexpr auto animationEvent = 0x60; // AnimationEvents
			constexpr auto ironSights = 0x68; // IronSights
			constexpr auto sway = 0x70; // ViewmodelSway
			constexpr auto lower = 0x78; // ViewmodelLower
			constexpr auto bob = 0x80; // ViewmodelBob
			constexpr auto punch = 0x88; // ViewmodelPunch
			constexpr auto aspectOffset = 0x90; // ViewmodelAspectOffset
			constexpr auto mountedAnchor = 0x98; // ViewmodelMountedAnchor
			constexpr auto model = 0xa0; // Model
			constexpr auto Skeleton = 0xa8; // Skeleton
			constexpr auto Clothing = 0xb0; // GameObject
			constexpr auto workshopMode = 0xb8; // bool
		}
		namespace SkinSet
		{
			constexpr auto Label = 0x18; // string
			constexpr auto SkinColour = 0x20; // Gradient
			constexpr auto HairCollection = 0x28; // HairSetCollection
			constexpr auto Head = 0x30; // GameObjectRef
			constexpr auto Torso = 0x38; // GameObjectRef
			constexpr auto Legs = 0x40; // GameObjectRef
			constexpr auto Feet = 0x48; // GameObjectRef
			constexpr auto Hands = 0x50; // GameObjectRef
			constexpr auto CensoredTorso = 0x58; // GameObjectRef
			constexpr auto CensoredLegs = 0x60; // GameObjectRef
			constexpr auto HeadMaterial = 0x68; // Material
			constexpr auto BodyMaterial = 0x70; // Material
			constexpr auto EyeMaterial = 0x78; // Material
		}
		namespace ViewmodelSway
		{
			constexpr auto positionalSwaySpeed = 0x18; // float
			constexpr auto positionalSwayAmount = 0x1c; // float
			constexpr auto rotationSwaySpeed = 0x20; // float
			constexpr auto rotationSwayAmount = 0x24; // float
			constexpr auto lastPosition = 0x28; // Vector3
			constexpr auto smoothedVelocity = 0x34; // Vector3
			constexpr auto lastRotation = 0x40; // Vector3
			constexpr auto smoothedRotation = 0x4c; // Vector3
			constexpr auto rotateAmountTest = 0x58; // float
		}
		namespace ViewmodelBob
		{
			constexpr auto bobSpeedWalk = 0x18; // float
			constexpr auto bobSpeedRun = 0x1c; // float
			constexpr auto bobAmountWalk = 0x20; // float
			constexpr auto bobAmountRun = 0x24; // float
			constexpr auto leftOffsetRun = 0x28; // float
			constexpr auto bobAmountRotateYaw = 0x2c; // float
			constexpr auto bobAmountRotateRoll = 0x30; // float
			constexpr auto velocity = 0x34; // Vector3
			constexpr auto bobOffset = 0x40; // Vector3
			constexpr auto bobRotateYaw = 0x4c; // float
			constexpr auto bobRotateRoll = 0x50; // float
			constexpr auto bobCycle = 0x54; // float
			constexpr auto smoothedBob = 0x58; // ViewmodelBob.BobSettings
		}
		namespace ViewmodelPunch
		{
			constexpr auto punchScale = 0x18; // AnimationCurve
			constexpr auto punchDirection = 0x20; // Vector3
			constexpr auto punchDuration = 0x2c; // float
			constexpr auto punchMagnitude = 0x30; // float
			constexpr auto punchStartTime = 0x34; // float
		}
		namespace Skinnable
		{
			constexpr auto Name = 0x18; // string
			constexpr auto ItemName = 0x20; // string
			constexpr auto EntityPrefab = 0x28; // GameObject
			constexpr auto EntityPrefabName = 0x30; // string
			constexpr auto ViewmodelPrefab = 0x38; // GameObject
			constexpr auto ViewmodelPrefabName = 0x40; // string
			constexpr auto MeshDownloads = 0x48; // Mesh[]
			constexpr auto MeshDownloadPaths = 0x50; // string[]
			constexpr auto Category = 0x58; // Category
			constexpr auto HideInWorkshopUpload = 0x5c; // bool
			constexpr auto Groups = 0x60; // Skinnable.Group[]
			constexpr auto _sourceMaterials = 0x68; // Material[]
		}
		namespace SkinnableGroup
		{
			constexpr auto Name = 0x10; // string
			constexpr auto Material = 0x18; // Material
			constexpr auto MaxTextureSize = 0x20; // int
		}
		namespace TOD_Sky
		{
			constexpr auto ColorSpace = 0x18; // TOD_ColorSpaceType
			constexpr auto ColorRange = 0x1c; // TOD_ColorRangeType
			constexpr auto ColorOutput = 0x20; // TOD_ColorOutputType
			constexpr auto SkyQuality = 0x24; // TOD_SkyQualityType
			constexpr auto CloudQuality = 0x28; // TOD_CloudQualityType
			constexpr auto MeshQuality = 0x2c; // TOD_MeshQualityType
			constexpr auto StarQuality = 0x30; // TOD_StarQualityType
			constexpr auto Cycle = 0x38; // TOD_CycleParameters
			constexpr auto World = 0x40; // TOD_WorldParameters
			constexpr auto Atmosphere = 0x48; // TOD_AtmosphereParameters
			constexpr auto Day = 0x50; // TOD_DayParameters
			constexpr auto Night = 0x58; // TOD_NightParameters
			constexpr auto Sun = 0x60; // TOD_SunParameters
			constexpr auto Moon = 0x68; // TOD_MoonParameters
			constexpr auto Stars = 0x70; // TOD_StarParameters
			constexpr auto Clouds = 0x78; // TOD_CloudParameters
			constexpr auto Light = 0x80; // TOD_LightParameters
			constexpr auto Fog = 0x88; // TOD_FogParameters
			constexpr auto Ambient = 0x90; // TOD_AmbientParameters
			constexpr auto Reflection = 0x98; // TOD_ReflectionParameters
			constexpr auto Initializedk__BackingField = 0xa0; // bool
			constexpr auto Componentsk__BackingField = 0xa8; // TOD_Components
			constexpr auto Resourcesk__BackingField = 0xb0; // TOD_Resources
			constexpr auto IsDayk__BackingField = 0xb8; // bool
			constexpr auto IsNightk__BackingField = 0xb9; // bool
			constexpr auto LerpValuek__BackingField = 0xbc; // float
			constexpr auto SunZenithk__BackingField = 0xc0; // float
			constexpr auto SunAltitudek__BackingField = 0xc4; // float
			constexpr auto SunAzimuthk__BackingField = 0xc8; // float
			constexpr auto MoonZenithk__BackingField = 0xcc; // float
			constexpr auto MoonAltitudek__BackingField = 0xd0; // float
			constexpr auto MoonAzimuthk__BackingField = 0xd4; // float
			constexpr auto SunsetTimek__BackingField = 0xd8; // float
			constexpr auto SunriseTimek__BackingField = 0xdc; // float
			constexpr auto LocalSiderealTimek__BackingField = 0xe0; // float
			constexpr auto SunVisibilityk__BackingField = 0xe4; // float
			constexpr auto MoonVisibilityk__BackingField = 0xe8; // float
			constexpr auto SunDirectionk__BackingField = 0xec; // Vector3
			constexpr auto MoonDirectionk__BackingField = 0xf8; // Vector3
			constexpr auto LightDirectionk__BackingField = 0x104; // Vector3
			constexpr auto LocalSunDirectionk__BackingField = 0x110; // Vector3
			constexpr auto LocalMoonDirectionk__BackingField = 0x11c; // Vector3
			constexpr auto LocalLightDirectionk__BackingField = 0x128; // Vector3
			constexpr auto SunLightColork__BackingField = 0x134; // Color
			constexpr auto MoonLightColork__BackingField = 0x144; // Color
			constexpr auto SunRayColork__BackingField = 0x154; // Color
			constexpr auto MoonRayColork__BackingField = 0x164; // Color
			constexpr auto SunSkyColork__BackingField = 0x174; // Color
			constexpr auto MoonSkyColork__BackingField = 0x184; // Color
			constexpr auto SunMeshColork__BackingField = 0x194; // Color
			constexpr auto MoonMeshColork__BackingField = 0x1a4; // Color
			constexpr auto SunCloudColork__BackingField = 0x1b4; // Color
			constexpr auto MoonCloudColork__BackingField = 0x1c4; // Color
			constexpr auto FogColork__BackingField = 0x1d4; // Color
			constexpr auto GroundColork__BackingField = 0x1e4; // Color
			constexpr auto AmbientColork__BackingField = 0x1f4; // Color
			constexpr auto MoonHaloColork__BackingField = 0x204; // Color
			constexpr auto ReflectionCur = 0x218; // TOD_Sky.ReflectionProbeState
			constexpr auto ReflectionSrc = 0x220; // TOD_Sky.ReflectionProbeState
			constexpr auto ReflectionDst = 0x228; // TOD_Sky.ReflectionProbeState
			constexpr auto timeSinceLightUpdate = 0x230; // float
			constexpr auto timeSinceAmbientUpdate = 0x234; // float
			constexpr auto timeSinceReflectionUpdate = 0x238; // float
			constexpr auto kBetaMie = 0x23c; // Vector3
			constexpr auto kSun = 0x248; // Vector4
			constexpr auto k4PI = 0x258; // Vector4
			constexpr auto kRadius = 0x268; // Vector4
			constexpr auto kScale = 0x278; // Vector4
		}
		namespace TOD_Components
		{
			constexpr auto Space = 0x18; // GameObject
			constexpr auto Stars = 0x20; // GameObject
			constexpr auto Sun = 0x28; // GameObject
			constexpr auto Moon = 0x30; // GameObject
			constexpr auto Atmosphere = 0x38; // GameObject
			constexpr auto Clear = 0x40; // GameObject
			constexpr auto Clouds = 0x48; // GameObject
			constexpr auto Billboards = 0x50; // GameObject
			constexpr auto Light = 0x58; // GameObject
			constexpr auto DomeTransformk__BackingField = 0x60; // Transform
			constexpr auto SpaceTransformk__BackingField = 0x68; // Transform
			constexpr auto StarTransformk__BackingField = 0x70; // Transform
			constexpr auto SunTransformk__BackingField = 0x78; // Transform
			constexpr auto MoonTransformk__BackingField = 0x80; // Transform
			constexpr auto AtmosphereTransformk__BackingField = 0x88; // Transform
			constexpr auto ClearTransformk__BackingField = 0x90; // Transform
			constexpr auto CloudTransformk__BackingField = 0x98; // Transform
			constexpr auto BillboardTransformk__BackingField = 0xa0; // Transform
			constexpr auto LightTransformk__BackingField = 0xa8; // Transform
			constexpr auto SpaceRendererk__BackingField = 0xb0; // Renderer
			constexpr auto StarRendererk__BackingField = 0xb8; // Renderer
			constexpr auto SunRendererk__BackingField = 0xc0; // Renderer
			constexpr auto MoonRendererk__BackingField = 0xc8; // Renderer
			constexpr auto AtmosphereRendererk__BackingField = 0xd0; // Renderer
			constexpr auto ClearRendererk__BackingField = 0xd8; // Renderer
			constexpr auto CloudRendererk__BackingField = 0xe0; // Renderer
			constexpr auto BillboardRenderersk__BackingField = 0xe8; // Renderer[]
			constexpr auto SpaceMeshFilterk__BackingField = 0xf0; // MeshFilter
			constexpr auto StarMeshFilterk__BackingField = 0xf8; // MeshFilter
			constexpr auto SunMeshFilterk__BackingField = 0x100; // MeshFilter
			constexpr auto MoonMeshFilterk__BackingField = 0x108; // MeshFilter
			constexpr auto AtmosphereMeshFilterk__BackingField = 0x110; // MeshFilter
			constexpr auto ClearMeshFilterk__BackingField = 0x118; // MeshFilter
			constexpr auto CloudMeshFilterk__BackingField = 0x120; // MeshFilter
			constexpr auto BillboardMeshFiltersk__BackingField = 0x128; // MeshFilter[]
			constexpr auto SpaceMaterialk__BackingField = 0x130; // Material
			constexpr auto StarMaterialk__BackingField = 0x138; // Material
			constexpr auto SunMaterialk__BackingField = 0x140; // Material
			constexpr auto MoonMaterialk__BackingField = 0x148; // Material
			constexpr auto AtmosphereMaterialk__BackingField = 0x150; // Material
			constexpr auto ClearMaterialk__BackingField = 0x158; // Material
			constexpr auto CloudMaterialk__BackingField = 0x160; // Material
			constexpr auto BillboardMaterialsk__BackingField = 0x168; // Material[]
			constexpr auto LightSourcek__BackingField = 0x170; // Light
			constexpr auto Skyk__BackingField = 0x178; // TOD_Sky
			constexpr auto Animationk__BackingField = 0x180; // TOD_Animation
			constexpr auto Timek__BackingField = 0x188; // TOD_Time
			constexpr auto Camerak__BackingField = 0x190; // TOD_Camera
			constexpr auto Raysk__BackingField = 0x198; // TOD_Rays
			constexpr auto Scatteringk__BackingField = 0x1a0; // TOD_Scattering
			constexpr auto Shadowsk__BackingField = 0x1a8; // TOD_Shadows
		}
		namespace TOD_AtmosphereParameters
		{
			constexpr auto RayleighMultiplier = 0x10; // float
			constexpr auto MieMultiplier = 0x14; // float
			constexpr auto Brightness = 0x18; // float
			constexpr auto Contrast = 0x1c; // float
			constexpr auto Directionality = 0x20; // float
			constexpr auto Fogginess = 0x24; // float
		}
		namespace TOD_DayParameters
		{
			constexpr auto SunColor = 0x10; // Gradient
			constexpr auto LightColor = 0x18; // Gradient
			constexpr auto RayColor = 0x20; // Gradient
			constexpr auto SkyColor = 0x28; // Gradient
			constexpr auto CloudColor = 0x30; // Gradient
			constexpr auto FogColor = 0x38; // Gradient
			constexpr auto AmbientColor = 0x40; // Gradient
			constexpr auto LightIntensity = 0x48; // float
			constexpr auto ShadowStrength = 0x4c; // float
			constexpr auto AmbientMultiplier = 0x50; // float
			constexpr auto ReflectionMultiplier = 0x54; // float
		}
		namespace TOD_CycleParameters
		{
			constexpr auto Hour = 0x10; // float
			constexpr auto Day = 0x14; // int
			constexpr auto Month = 0x18; // int
			constexpr auto Year = 0x1c; // int
		}
		namespace TOD_AmbientParameters
		{
			constexpr auto Mode = 0x10; // TOD_AmbientType
			constexpr auto Saturation = 0x14; // float
			constexpr auto UpdateInterval = 0x18; // float
		}
		namespace TOD_Scattering
		{
			constexpr auto ScatteringShader = 0x30; // Shader
			constexpr auto ScreenClearShader = 0x38; // Shader
			constexpr auto SkyMaskShader = 0x40; // Shader
			constexpr auto DitheringTexture = 0x48; // Texture2D
			constexpr auto SinglePass = 0x50; // bool
			constexpr auto GlobalDensity = 0x54; // float
			constexpr auto HeightFalloff = 0x58; // float
			constexpr auto StartDistance = 0x5c; // float
			constexpr auto ZeroLevel = 0x60; // float
			constexpr auto Resolution = 0x64; // TOD_ImageEffect.ResolutionType
			constexpr auto BlurIterations = 0x68; // int
			constexpr auto BlurRadius = 0x6c; // float
			constexpr auto MaxRadius = 0x70; // float
			constexpr auto scatteringMaterial = 0x78; // Material
			constexpr auto screenClearMaterial = 0x80; // Material
			constexpr auto skyMaskMaterial = 0x88; // Material
		}
		namespace TOD_CloudParameters
		{
			constexpr auto Size = 0x10; // float
			constexpr auto Opacity = 0x14; // float
			constexpr auto Coverage = 0x18; // float
			constexpr auto Sharpness = 0x1c; // float
			constexpr auto Coloring = 0x20; // float
			constexpr auto Attenuation = 0x24; // float
			constexpr auto Saturation = 0x28; // float
			constexpr auto Scattering = 0x2c; // float
			constexpr auto Brightness = 0x30; // float
		}
		namespace TOD_NightParameters
		{
			constexpr auto MoonColor = 0x10; // Gradient
			constexpr auto LightColor = 0x18; // Gradient
			constexpr auto RayColor = 0x20; // Gradient
			constexpr auto SkyColor = 0x28; // Gradient
			constexpr auto CloudColor = 0x30; // Gradient
			constexpr auto FogColor = 0x38; // Gradient
			constexpr auto AmbientColor = 0x40; // Gradient
			constexpr auto LightIntensity = 0x48; // float
			constexpr auto ShadowStrength = 0x4c; // float
			constexpr auto AmbientMultiplier = 0x50; // float
			constexpr auto ReflectionMultiplier = 0x54; // float
		}
		namespace TOD_MoonParameters
		{
			constexpr auto MeshSize = 0x10; // float
			constexpr auto MeshBrightness = 0x14; // float
			constexpr auto MeshContrast = 0x18; // float
			constexpr auto HaloSize = 0x1c; // float
			constexpr auto HaloBrightness = 0x20; // float
			constexpr auto Position = 0x24; // TOD_MoonPositionType
		}
		namespace TOD_StarParameters
		{
			constexpr auto Size = 0x10; // float
			constexpr auto Brightness = 0x14; // float
			constexpr auto Position = 0x18; // TOD_StarsPositionType
		}
		namespace TOD_SunParameters
		{
			constexpr auto MeshSize = 0x10; // float
			constexpr auto MeshBrightness = 0x14; // float
			constexpr auto MeshContrast = 0x18; // float
		}
	}
}