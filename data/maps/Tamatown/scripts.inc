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
	playfanfare MUS_OBTAIN_ITEM
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
	return


Tamatown_EventScript_Trashcan::
# 248 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 256 "data/maps/Tamatown/scripts.pory"
	lock
# 258 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 267 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 272 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_3, Tamatown_EventScript_TrubbishCan_Text_4
# 277 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 381 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_5:
# 385 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 388 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 259 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 260 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 262 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 278 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_5
# 282 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_6, Tamatown_EventScript_TrubbishCan_Text_7
# 287 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_10
# 323 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_14
# 332 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_13:
# 341 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 342 "data/maps/Tamatown/scripts.pory"
	delay 32
# 344 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 347 "data/maps/Tamatown/scripts.pory"
	closemessage
# 349 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 350 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 352 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 353 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 354 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 356 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 357 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 358 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 359 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
Tamatown_EventScript_TrubbishCan_9:
# 368 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 369 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 371 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 372 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 373 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 376 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 377 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 378 "data/maps/Tamatown/scripts.pory"
	closemessage
# 379 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_5

Tamatown_EventScript_TrubbishCan_10:
# 288 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 289 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 290 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 291 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 292 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 293 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 294 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 295 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
# 299 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 300 "data/maps/Tamatown/scripts.pory"
	closemessage
# 302 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 303 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_1
# 304 "data/maps/Tamatown/scripts.pory"
	waitse
# 305 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 307 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 308 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 310 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 311 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 312 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 314 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 315 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
	goto Tamatown_EventScript_TrubbishCan_9

Tamatown_EventScript_TrubbishCan_14:
# 324 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_13


Tamatown_EventScript_VendingMachine::
# 392 "data/maps/Tamatown/scripts.pory"
	lock
# 394 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 395 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 398 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 414 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 419 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 422 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 425 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 428 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 431 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 434 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 437 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 438 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 439 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 441 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 443 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 443 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 454 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 455 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 466 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 467 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 469 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 470 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 482 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 494 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 506 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 518 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 530 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 544 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 545 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 546 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 547 "data/maps/Tamatown/scripts.pory"
	closemessage
# 549 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 405 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 409 "data/maps/Tamatown/scripts.pory"
	closemessage
# 410 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 400 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 399 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 402 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 401 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 403 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 420 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 423 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 426 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 429 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 432 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 435 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 444 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 445 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 446 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 449 "data/maps/Tamatown/scripts.pory"
	closemessage
# 450 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 456 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 457 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 458 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 461 "data/maps/Tamatown/scripts.pory"
	closemessage
# 462 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 471 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 475 "data/maps/Tamatown/scripts.pory"
	closemessage
# 476 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 477 "data/maps/Tamatown/scripts.pory"
	waitse
# 478 "data/maps/Tamatown/scripts.pory"
	delay 32
# 479 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 480 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 483 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 487 "data/maps/Tamatown/scripts.pory"
	closemessage
# 488 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 489 "data/maps/Tamatown/scripts.pory"
	waitse
# 490 "data/maps/Tamatown/scripts.pory"
	delay 32
# 491 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 492 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 495 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 499 "data/maps/Tamatown/scripts.pory"
	closemessage
# 500 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 501 "data/maps/Tamatown/scripts.pory"
	waitse
# 502 "data/maps/Tamatown/scripts.pory"
	delay 32
# 503 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 504 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 507 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 511 "data/maps/Tamatown/scripts.pory"
	closemessage
# 512 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 513 "data/maps/Tamatown/scripts.pory"
	waitse
# 514 "data/maps/Tamatown/scripts.pory"
	delay 32
# 515 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 516 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 519 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 523 "data/maps/Tamatown/scripts.pory"
	closemessage
# 524 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 525 "data/maps/Tamatown/scripts.pory"
	waitse
# 526 "data/maps/Tamatown/scripts.pory"
	delay 32
# 527 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 528 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 531 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 535 "data/maps/Tamatown/scripts.pory"
	closemessage
# 536 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 537 "data/maps/Tamatown/scripts.pory"
	waitse
# 538 "data/maps/Tamatown/scripts.pory"
	delay 32
# 539 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 540 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 553 "data/maps/Tamatown/scripts.pory"
	lock
# 555 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 565 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 567 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 568 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 569 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 581 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 586 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 684 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 685 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 686 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 693 "data/maps/Tamatown/scripts.pory"
	closemessage
# 695 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 556 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 557 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 558 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 587 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 588 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 589 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 594 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 595 "data/maps/Tamatown/scripts.pory"
	delay 32
# 596 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 597 "data/maps/Tamatown/scripts.pory"
	waitstate
# 598 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 599 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 601 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 603 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 626 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 649 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 673 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 674 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
Tamatown_EventScript_Slowpoke_9:
# 680 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 604 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 606 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 611 "data/maps/Tamatown/scripts.pory"
	closemessage
# 613 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 616 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 617 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 618 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 620 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 623 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 624 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 625 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 627 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 629 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 634 "data/maps/Tamatown/scripts.pory"
	closemessage
# 636 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 639 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 640 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 641 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 643 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 646 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 647 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 648 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 650 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 652 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 657 "data/maps/Tamatown/scripts.pory"
	closemessage
# 659 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 662 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 663 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 664 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 666 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 669 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 670 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 671 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 681 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 699 "data/maps/Tamatown/scripts.pory"
	lock
# 701 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 715 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 716 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 717 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 722 "data/maps/Tamatown/scripts.pory"
	closemessage
# 724 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 728 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 729 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 730 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 731 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 734 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 735 "data/maps/Tamatown/scripts.pory"
	delay 44
# 736 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 737 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 738 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 739 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 740 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 742 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 743 "data/maps/Tamatown/scripts.pory"
	delay 48
# 745 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 746 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 749 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 702 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 703 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 704 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 705 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 706 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 709 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 710 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 711 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 712 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


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

# 311 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 311 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 311 "data/maps/Tamatown/scripts.pory"
	delay_16
# 311 "data/maps/Tamatown/scripts.pory"
	delay_16
# 311 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 324 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 325 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 326 "data/maps/Tamatown/scripts.pory"
	delay_16
# 326 "data/maps/Tamatown/scripts.pory"
	delay_16
# 327 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 328 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 329 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 332 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 333 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 334 "data/maps/Tamatown/scripts.pory"
	delay_16
# 334 "data/maps/Tamatown/scripts.pory"
	delay_16
# 335 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 336 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 337 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 357 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 357 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 724 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 725 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 731 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 732 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 734 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 734 "data/maps/Tamatown/scripts.pory"
	face_down
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
# 239 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 249 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 259 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 263 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 268 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 273 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 274 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 279 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 283 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 284 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 296 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 316 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 345 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 360 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 374 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 382 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 395 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 406 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 415 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 420 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 423 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 426 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 429 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 432 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 435 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 437 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 447 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 459 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 472 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 479 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 484 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 491 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 496 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 503 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 508 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 520 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 527 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 532 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 539 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 557 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 559 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 570 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 582 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 583 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 590 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 607 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 614 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 621 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 630 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 637 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 644 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 653 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 660 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 667 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 675 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 687 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 707 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 716 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 718 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"
