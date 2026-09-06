Tamatown_MapScripts::
# 5 "data/maps/Tamatown/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 6 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	return

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 7 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_VANILLISH, 33, 20
# 8 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
# 9 "data/maps/Tamatown/scripts.pory"
	setobjectmovementtype LOCALID_VANILLISH, MOVEMENT_TYPE_FACE_UP
	return


Tamatown_EventScript_House::
# 15 "data/maps/Tamatown/scripts.pory"
	lock
# 16 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_House_Text_0
# 20 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_House_Text_1, Tamatown_EventScript_House_Text_2
# 25 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 26 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_House_2
# 29 "data/maps/Tamatown/scripts.pory"
	closemessage
# 30 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_House_2:
# 27 "data/maps/Tamatown/scripts.pory"
	callnative ReturnToPokegotchiHouse
	return


Tamatown_EventScript_Arcade::
# 35 "data/maps/Tamatown/scripts.pory"
	lock
# 37 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 39 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Arcade_Text_0
# 43 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Arcade_Text_1, Tamatown_EventScript_Arcade_Text_2
# 48 "data/maps/Tamatown/scripts.pory"
	closemessage
# 49 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 51 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 52 "data/maps/Tamatown/scripts.pory"
	delay 32
# 53 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 54 "data/maps/Tamatown/scripts.pory"
	waitstate
# 55 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 56 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 58 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Porygon::
# 62 "data/maps/Tamatown/scripts.pory"
	lockall
# 64 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_2
# 75 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 77 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 78 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 79 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_2
# 86 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_1:
# 89 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_6
Tamatown_EventScript_Porygon_5:
# 103 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_4, Tamatown_EventScript_Porygon_Text_5
# 108 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 109 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_10
# 137 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 138 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 139 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_7
# 144 "data/maps/Tamatown/scripts.pory"
	closemessage
# 146 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 65 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 66 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 68 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 70 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 71 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 90 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_3
# 93 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 94 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 96 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 98 "data/maps/Tamatown/scripts.pory"
	closemessage
# 100 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_5

Tamatown_EventScript_Porygon_10:
# 110 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 111 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 112 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_6
# 115 "data/maps/Tamatown/scripts.pory"
	closemessage
# 117 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 118 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_14
# 120 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_15
# 122 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_16
Tamatown_EventScript_Porygon_12:
# 126 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 128 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 129 "data/maps/Tamatown/scripts.pory"
	delay 32
# 130 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 131 "data/maps/Tamatown/scripts.pory"
	waitstate
# 132 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 133 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 134 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_14:
# 119 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_15:
# 121 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_16:
# 123 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_12


Tamatown_EventScript_Tree::
# 150 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 157 "data/maps/Tamatown/scripts.pory"
	lock
# 159 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 167 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 171 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 176 "data/maps/Tamatown/scripts.pory"
	closemessage
# 178 "data/maps/Tamatown/scripts.pory"
	delay 24
# 180 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 181 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 182 "data/maps/Tamatown/scripts.pory"
	waitse
# 183 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 185 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 189 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 194 "data/maps/Tamatown/scripts.pory"
	closemessage
# 196 "data/maps/Tamatown/scripts.pory"
	delay 24
# 198 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 199 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 200 "data/maps/Tamatown/scripts.pory"
	waitse
# 201 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 203 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 204 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 208 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 213 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 214 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_1
# 215 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 216 "data/maps/Tamatown/scripts.pory"
	waitse
# 218 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 219 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 220 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 226 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 228 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 231 "data/maps/Tamatown/scripts.pory"
	closemessage
# 233 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 160 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 161 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 162 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 165 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 237 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
# 243 "data/maps/Tamatown/scripts.pory"
	lock
# 246 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 247 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Skitty_Text_0
# 248 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 252 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Trashcan::
# 256 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 264 "data/maps/Tamatown/scripts.pory"
	lock
# 266 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 275 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 280 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_3, Tamatown_EventScript_TrubbishCan_Text_4
# 285 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 389 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_5:
# 393 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 396 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 267 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 268 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 270 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 286 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_5
# 290 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_6, Tamatown_EventScript_TrubbishCan_Text_7
# 295 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_10
# 331 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_14
# 340 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_13:
# 349 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 350 "data/maps/Tamatown/scripts.pory"
	delay 32
# 352 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 355 "data/maps/Tamatown/scripts.pory"
	closemessage
# 357 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 358 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 360 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 361 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 362 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 364 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 365 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 366 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 367 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
Tamatown_EventScript_TrubbishCan_9:
# 376 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 377 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 379 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 380 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 381 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 384 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 385 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 386 "data/maps/Tamatown/scripts.pory"
	closemessage
# 387 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_5

Tamatown_EventScript_TrubbishCan_10:
# 296 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 297 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 298 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 299 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 300 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 301 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 302 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 303 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
# 307 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 308 "data/maps/Tamatown/scripts.pory"
	closemessage
# 310 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 311 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_1
# 312 "data/maps/Tamatown/scripts.pory"
	waitse
# 313 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 315 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 316 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 318 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 319 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 320 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 322 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 323 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
	goto Tamatown_EventScript_TrubbishCan_9

Tamatown_EventScript_TrubbishCan_14:
# 332 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_13


Tamatown_EventScript_VendingMachine::
# 400 "data/maps/Tamatown/scripts.pory"
	lock
# 402 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 403 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 406 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 422 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 427 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 430 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 433 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 436 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 439 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 442 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 445 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 446 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 447 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 449 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 451 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 451 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 462 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 463 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 474 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 475 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 477 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 478 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 490 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 502 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 514 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 526 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 538 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 552 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 553 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 554 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 555 "data/maps/Tamatown/scripts.pory"
	closemessage
# 557 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 413 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 417 "data/maps/Tamatown/scripts.pory"
	closemessage
# 418 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 408 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 407 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 410 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 409 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 411 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 428 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 431 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 434 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 437 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 440 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 443 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 452 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 453 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 454 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 457 "data/maps/Tamatown/scripts.pory"
	closemessage
# 458 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 464 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 465 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 466 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 469 "data/maps/Tamatown/scripts.pory"
	closemessage
# 470 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 479 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 483 "data/maps/Tamatown/scripts.pory"
	closemessage
# 484 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 485 "data/maps/Tamatown/scripts.pory"
	waitse
# 486 "data/maps/Tamatown/scripts.pory"
	delay 32
# 487 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 488 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 491 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 495 "data/maps/Tamatown/scripts.pory"
	closemessage
# 496 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 497 "data/maps/Tamatown/scripts.pory"
	waitse
# 498 "data/maps/Tamatown/scripts.pory"
	delay 32
# 499 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 500 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 503 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 507 "data/maps/Tamatown/scripts.pory"
	closemessage
# 508 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 509 "data/maps/Tamatown/scripts.pory"
	waitse
# 510 "data/maps/Tamatown/scripts.pory"
	delay 32
# 511 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 512 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 515 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 519 "data/maps/Tamatown/scripts.pory"
	closemessage
# 520 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 521 "data/maps/Tamatown/scripts.pory"
	waitse
# 522 "data/maps/Tamatown/scripts.pory"
	delay 32
# 523 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 524 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 527 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 531 "data/maps/Tamatown/scripts.pory"
	closemessage
# 532 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 533 "data/maps/Tamatown/scripts.pory"
	waitse
# 534 "data/maps/Tamatown/scripts.pory"
	delay 32
# 535 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 536 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 539 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 543 "data/maps/Tamatown/scripts.pory"
	closemessage
# 544 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 545 "data/maps/Tamatown/scripts.pory"
	waitse
# 546 "data/maps/Tamatown/scripts.pory"
	delay 32
# 547 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 548 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 561 "data/maps/Tamatown/scripts.pory"
	lock
# 563 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 573 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 575 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 576 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 577 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 589 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 594 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 692 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 693 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 694 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 701 "data/maps/Tamatown/scripts.pory"
	closemessage
# 703 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 564 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 565 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 566 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 595 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 596 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 597 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 602 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 603 "data/maps/Tamatown/scripts.pory"
	delay 32
# 604 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 605 "data/maps/Tamatown/scripts.pory"
	waitstate
# 606 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 607 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 609 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 611 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 634 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 657 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 681 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 682 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
Tamatown_EventScript_Slowpoke_9:
# 688 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 612 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 614 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 619 "data/maps/Tamatown/scripts.pory"
	closemessage
# 621 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 624 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 625 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 626 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 628 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 631 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 632 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 633 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 635 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 637 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 642 "data/maps/Tamatown/scripts.pory"
	closemessage
# 644 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 647 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 648 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 649 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 651 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 654 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 655 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 656 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 658 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 660 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 665 "data/maps/Tamatown/scripts.pory"
	closemessage
# 667 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 670 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 671 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 672 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 674 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 677 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 678 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 679 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 689 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 707 "data/maps/Tamatown/scripts.pory"
	lock
# 709 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 723 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 724 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 725 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 730 "data/maps/Tamatown/scripts.pory"
	closemessage
# 732 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 736 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 737 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 738 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 739 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 742 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 743 "data/maps/Tamatown/scripts.pory"
	delay 44
# 744 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 745 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 746 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 747 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 748 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 750 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 751 "data/maps/Tamatown/scripts.pory"
	delay 48
# 753 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 754 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 757 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 710 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 711 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 712 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 713 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 714 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 717 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 718 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 719 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 720 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 761 "data/maps/Tamatown/scripts.pory"
	lock
# 762 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 770 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 771 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 772 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 778 "data/maps/Tamatown/scripts.pory"
	closemessage
# 780 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 781 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 784 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 785 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 786 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 787 "data/maps/Tamatown/scripts.pory"
	closemessage
# 789 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 792 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 763 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 764 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 765 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 768 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 796 "data/maps/Tamatown/scripts.pory"
	lock
# 798 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 804 "data/maps/Tamatown/scripts.pory"
	closemessage
# 806 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 810 "data/maps/Tamatown/scripts.pory"
	lock
# 812 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 815 "data/maps/Tamatown/scripts.pory"
	closemessage
# 817 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 821 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 824 "data/maps/Tamatown/scripts.pory"
	lock
# 826 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 831 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 835 "data/maps/Tamatown/scripts.pory"
	closemessage
# 837 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 857 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 822 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 838 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 839 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 840 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 841 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 842 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 843 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 844 "data/maps/Tamatown/scripts.pory"
	waitstate
# 845 "data/maps/Tamatown/scripts.pory"
	waitse
# 847 "data/maps/Tamatown/scripts.pory"
	delay 48
# 849 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 852 "data/maps/Tamatown/scripts.pory"
	closemessage
# 854 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 862 "data/maps/Tamatown/scripts.pory"
	lock
# 864 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_2
# 871 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_3
# 890 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 891 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 892 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_4
# 895 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_1:
# 898 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 865 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 866 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 867 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 870 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_1

Tamatown_EventScript_Torchic_3:
# 872 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 873 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 874 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 879 "data/maps/Tamatown/scripts.pory"
	closemessage
# 881 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_3
# 884 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 885 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 886 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 887 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_1


Tamatown_EventScript_StepInPoop::
# 902 "data/maps/Tamatown/scripts.pory"
	lock
# 903 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 904 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 908 "data/maps/Tamatown/scripts.pory"
	lock
# 909 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 912 "data/maps/Tamatown/scripts.pory"
	closemessage
# 913 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 917 "data/maps/Tamatown/scripts.pory"
	lock
# 918 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 919 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 920 "data/maps/Tamatown/scripts.pory"
	waitse
# 921 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 922 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 926 "data/maps/Tamatown/scripts.pory"
	lock
# 928 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 934 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 939 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 943 "data/maps/Tamatown/scripts.pory"
	closemessage
# 945 "data/maps/Tamatown/scripts.pory"
	delay 32
# 947 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1015 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 929 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 930 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 931 "data/maps/Tamatown/scripts.pory"
	waitse
# 932 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 948 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 952 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 956 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 961 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 966 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 969 "data/maps/Tamatown/scripts.pory"
	closemessage
# 971 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 972 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_4
# 973 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 974 "data/maps/Tamatown/scripts.pory"
	waitse
# 975 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 976 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_5
# 977 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 978 "data/maps/Tamatown/scripts.pory"
	waitse
# 980 "data/maps/Tamatown/scripts.pory"
	delay 32
# 981 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 983 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 984 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_4
# 985 "data/maps/Tamatown/scripts.pory"
	waitse
# 986 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 988 "data/maps/Tamatown/scripts.pory"
	delay 32
# 990 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 991 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 992 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 996 "data/maps/Tamatown/scripts.pory"
	closemessage
# 998 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1001 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1002 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1003 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1004 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1006 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1008 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1010 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 1011 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 949 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 953 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 957 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


# 66 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 66 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 119 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 119 "data/maps/Tamatown/scripts.pory"
	walk_right
# 119 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 121 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 121 "data/maps/Tamatown/scripts.pory"
	walk_left
# 121 "data/maps/Tamatown/scripts.pory"
	walk_down
# 121 "data/maps/Tamatown/scripts.pory"
	walk_down
# 121 "data/maps/Tamatown/scripts.pory"
	walk_right
# 121 "data/maps/Tamatown/scripts.pory"
	walk_right
# 121 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 123 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 123 "data/maps/Tamatown/scripts.pory"
	walk_down
# 123 "data/maps/Tamatown/scripts.pory"
	walk_right
# 123 "data/maps/Tamatown/scripts.pory"
	walk_right
# 123 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 181 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 181 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 214 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 214 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
# 214 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 319 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 319 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 332 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 333 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 334 "data/maps/Tamatown/scripts.pory"
	delay_16
# 334 "data/maps/Tamatown/scripts.pory"
	delay_16
# 335 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 336 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 337 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 340 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 341 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 342 "data/maps/Tamatown/scripts.pory"
	delay_16
# 342 "data/maps/Tamatown/scripts.pory"
	delay_16
# 343 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 344 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 345 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 365 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 365 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 732 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 733 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 739 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 740 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 742 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 742 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 949 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 950 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 950 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 950 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 950 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 953 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 954 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 954 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 954 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 954 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 957 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 958 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 958 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 958 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 958 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 961 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 962 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 962 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 962 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 962 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 972 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 972 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 976 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_5:
# 976 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 976 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 976 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

Tamatown_EventScript_House_Text_0:
# 17 "data/maps/Tamatown/scripts.pory"
	.string "Go home?$"

Tamatown_EventScript_House_Text_1:
# 21 "data/maps/Tamatown/scripts.pory"
	.string "Yes$"

Tamatown_EventScript_House_Text_2:
# 22 "data/maps/Tamatown/scripts.pory"
	.string "No$"

Tamatown_EventScript_Arcade_Text_0:
# 40 "data/maps/Tamatown/scripts.pory"
	.string "Play {COLOR RED}Pachinko{COLOR DARK_GRAY}?\p$"

Tamatown_EventScript_Arcade_Text_1:
# 44 "data/maps/Tamatown/scripts.pory"
	.string "Play$"

Tamatown_EventScript_Arcade_Text_2:
# 45 "data/maps/Tamatown/scripts.pory"
	.string "Don't play$"

Tamatown_EventScript_Porygon_Text_0:
# 70 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_1:
# 72 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_2:
# 80 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_3:
# 91 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_4:
# 104 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_5:
# 105 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_6:
# 113 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_7:
# 140 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 151 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 161 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 163 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 168 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 172 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 173 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 186 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 190 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 191 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 203 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 205 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 209 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 210 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 221 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 238 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Skitty_Text_0:
# 247 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Skitty_Text_1:
# 249 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "Would you be so kind as to find me some\nmore yarn?$"

Tamatown_EventScript_Trashcan_Text_0:
# 257 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 267 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 271 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 276 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 281 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 282 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 287 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 291 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 292 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 302 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 304 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 324 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 353 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 368 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 382 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 390 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 403 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 414 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 423 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 428 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 431 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 434 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 437 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 440 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 443 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 445 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 455 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 467 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 480 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 487 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 492 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 499 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 504 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 511 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 516 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 528 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 535 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 540 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 547 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 565 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 567 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 578 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 590 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 591 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 598 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 615 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 622 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 629 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 638 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 645 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 652 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 661 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 668 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 675 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 683 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 695 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 715 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 724 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 726 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 763 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 766 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 773 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 782 "data/maps/Tamatown/scripts.pory"
	.string "You got a Lucky Egg!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 799 "data/maps/Tamatown/scripts.pory"
	.string "Use this letterbox to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 813 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 827 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 832 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 833 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 850 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 866 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 868 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_2:
# 875 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_3:
# 882 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat poster for your room!$"

Tamatown_EventScript_Torchic_Text_4:
# 893 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 910 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, hot dogs…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 935 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 940 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 941 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 967 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 991 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 993 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool plushie if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 999 "data/maps/Tamatown/scripts.pory"
	.string "You got a Ditto plushie for your room!$"
