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


Tamatown_EventScript_Arcade::
# 15 "data/maps/Tamatown/scripts.pory"
	lock
# 17 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 19 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Arcade_Text_0
# 23 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Arcade_Text_1, Tamatown_EventScript_Arcade_Text_2
# 28 "data/maps/Tamatown/scripts.pory"
	closemessage
# 29 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 31 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 32 "data/maps/Tamatown/scripts.pory"
	delay 32
# 33 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 34 "data/maps/Tamatown/scripts.pory"
	waitstate
# 35 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 36 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 38 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Porygon::
# 42 "data/maps/Tamatown/scripts.pory"
	lockall
# 44 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_2
# 55 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 57 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 58 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 59 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_2
# 66 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_1:
# 69 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_6
Tamatown_EventScript_Porygon_5:
# 83 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_4, Tamatown_EventScript_Porygon_Text_5
# 88 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 89 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_10
# 117 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 118 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 119 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_7
# 124 "data/maps/Tamatown/scripts.pory"
	closemessage
# 126 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 45 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 46 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 48 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 50 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 51 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 70 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_3
# 73 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 74 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 76 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 78 "data/maps/Tamatown/scripts.pory"
	closemessage
# 80 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_5

Tamatown_EventScript_Porygon_10:
# 90 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 91 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 92 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_6
# 95 "data/maps/Tamatown/scripts.pory"
	closemessage
# 97 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 98 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_14
# 100 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_15
# 102 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_16
Tamatown_EventScript_Porygon_12:
# 106 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 108 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 109 "data/maps/Tamatown/scripts.pory"
	delay 32
# 110 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 111 "data/maps/Tamatown/scripts.pory"
	waitstate
# 112 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 113 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 114 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_14:
# 99 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_15:
# 101 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_16:
# 103 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_12


Tamatown_EventScript_Tree::
# 130 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 137 "data/maps/Tamatown/scripts.pory"
	lock
# 139 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 147 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 151 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 156 "data/maps/Tamatown/scripts.pory"
	closemessage
# 158 "data/maps/Tamatown/scripts.pory"
	delay 24
# 160 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 161 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 162 "data/maps/Tamatown/scripts.pory"
	waitse
# 163 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 165 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 169 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 174 "data/maps/Tamatown/scripts.pory"
	closemessage
# 176 "data/maps/Tamatown/scripts.pory"
	delay 24
# 178 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 179 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 180 "data/maps/Tamatown/scripts.pory"
	waitse
# 181 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 183 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 184 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 188 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 193 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 194 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_1
# 195 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 196 "data/maps/Tamatown/scripts.pory"
	waitse
# 198 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 199 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 200 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 206 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 208 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 211 "data/maps/Tamatown/scripts.pory"
	closemessage
# 213 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 140 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 141 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 142 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 145 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 217 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
# 223 "data/maps/Tamatown/scripts.pory"
	lock
# 226 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 227 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Skitty_Text_0
# 228 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 232 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Trashcan::
# 236 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 244 "data/maps/Tamatown/scripts.pory"
	lock
# 246 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 255 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 260 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_3, Tamatown_EventScript_TrubbishCan_Text_4
# 265 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 369 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_5:
# 373 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 376 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 247 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 248 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 250 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 266 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_5
# 270 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_6, Tamatown_EventScript_TrubbishCan_Text_7
# 275 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_10
# 311 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_14
# 320 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_13:
# 329 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 330 "data/maps/Tamatown/scripts.pory"
	delay 32
# 332 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 335 "data/maps/Tamatown/scripts.pory"
	closemessage
# 337 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 338 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 340 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 341 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 342 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 344 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 345 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 346 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 347 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
Tamatown_EventScript_TrubbishCan_9:
# 356 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 357 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 359 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 360 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 361 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 364 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 365 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 366 "data/maps/Tamatown/scripts.pory"
	closemessage
# 367 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_5

Tamatown_EventScript_TrubbishCan_10:
# 276 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 277 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 278 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 279 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 280 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 281 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 282 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 283 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
# 287 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 288 "data/maps/Tamatown/scripts.pory"
	closemessage
# 290 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 291 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_1
# 292 "data/maps/Tamatown/scripts.pory"
	waitse
# 293 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 295 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 296 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 298 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 299 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 300 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 302 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 303 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
	goto Tamatown_EventScript_TrubbishCan_9

Tamatown_EventScript_TrubbishCan_14:
# 312 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_13


Tamatown_EventScript_VendingMachine::
# 380 "data/maps/Tamatown/scripts.pory"
	lock
# 382 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 383 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 386 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 402 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 407 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 410 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 413 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 416 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 419 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 422 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 425 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 426 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 427 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 429 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 431 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 431 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 442 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 443 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 454 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 455 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 457 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 458 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 470 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 482 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 494 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 506 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 518 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 532 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 533 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 534 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 535 "data/maps/Tamatown/scripts.pory"
	closemessage
# 537 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 393 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 397 "data/maps/Tamatown/scripts.pory"
	closemessage
# 398 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 388 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 387 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 390 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 389 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 391 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 408 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 411 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 414 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 417 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 420 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 423 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 432 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 433 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 434 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 437 "data/maps/Tamatown/scripts.pory"
	closemessage
# 438 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 444 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 445 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 446 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 449 "data/maps/Tamatown/scripts.pory"
	closemessage
# 450 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 459 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 463 "data/maps/Tamatown/scripts.pory"
	closemessage
# 464 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 465 "data/maps/Tamatown/scripts.pory"
	waitse
# 466 "data/maps/Tamatown/scripts.pory"
	delay 32
# 467 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 468 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 471 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 475 "data/maps/Tamatown/scripts.pory"
	closemessage
# 476 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 477 "data/maps/Tamatown/scripts.pory"
	waitse
# 478 "data/maps/Tamatown/scripts.pory"
	delay 32
# 479 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 480 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 483 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 487 "data/maps/Tamatown/scripts.pory"
	closemessage
# 488 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 489 "data/maps/Tamatown/scripts.pory"
	waitse
# 490 "data/maps/Tamatown/scripts.pory"
	delay 32
# 491 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 492 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 495 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 499 "data/maps/Tamatown/scripts.pory"
	closemessage
# 500 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 501 "data/maps/Tamatown/scripts.pory"
	waitse
# 502 "data/maps/Tamatown/scripts.pory"
	delay 32
# 503 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 504 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 507 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 511 "data/maps/Tamatown/scripts.pory"
	closemessage
# 512 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 513 "data/maps/Tamatown/scripts.pory"
	waitse
# 514 "data/maps/Tamatown/scripts.pory"
	delay 32
# 515 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 516 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 519 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 523 "data/maps/Tamatown/scripts.pory"
	closemessage
# 524 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 525 "data/maps/Tamatown/scripts.pory"
	waitse
# 526 "data/maps/Tamatown/scripts.pory"
	delay 32
# 527 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 528 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 541 "data/maps/Tamatown/scripts.pory"
	lock
# 543 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 553 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 555 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 556 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 557 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 569 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 574 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 672 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 673 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 674 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 681 "data/maps/Tamatown/scripts.pory"
	closemessage
# 683 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 544 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 545 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 546 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 575 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 576 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 577 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 582 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 583 "data/maps/Tamatown/scripts.pory"
	delay 32
# 584 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 585 "data/maps/Tamatown/scripts.pory"
	waitstate
# 586 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 587 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 589 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 591 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 614 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 637 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 661 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 662 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
Tamatown_EventScript_Slowpoke_9:
# 668 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 592 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 594 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 599 "data/maps/Tamatown/scripts.pory"
	closemessage
# 601 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 604 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 605 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 606 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 608 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 611 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 612 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 613 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 615 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 617 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 622 "data/maps/Tamatown/scripts.pory"
	closemessage
# 624 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 627 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 628 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 629 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 631 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 634 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 635 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 636 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 638 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 640 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 645 "data/maps/Tamatown/scripts.pory"
	closemessage
# 647 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 650 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 651 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 652 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 654 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 657 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 658 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 659 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 669 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 687 "data/maps/Tamatown/scripts.pory"
	lock
# 689 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 703 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 704 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 705 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 710 "data/maps/Tamatown/scripts.pory"
	closemessage
# 712 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 716 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 717 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 718 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 719 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 722 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 723 "data/maps/Tamatown/scripts.pory"
	delay 44
# 724 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 725 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 726 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 727 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 728 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 730 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 731 "data/maps/Tamatown/scripts.pory"
	delay 48
# 733 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 734 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 737 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 690 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 691 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 692 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 693 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 694 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 697 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 698 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 699 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 700 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 741 "data/maps/Tamatown/scripts.pory"
	lock
# 742 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 750 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 751 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 752 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 758 "data/maps/Tamatown/scripts.pory"
	closemessage
# 760 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 761 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 764 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 765 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 766 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 767 "data/maps/Tamatown/scripts.pory"
	closemessage
# 769 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 772 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 743 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 744 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 745 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 748 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 776 "data/maps/Tamatown/scripts.pory"
	lock
# 778 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 784 "data/maps/Tamatown/scripts.pory"
	closemessage
# 786 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 790 "data/maps/Tamatown/scripts.pory"
	lock
# 792 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 795 "data/maps/Tamatown/scripts.pory"
	closemessage
# 797 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 801 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 804 "data/maps/Tamatown/scripts.pory"
	lock
# 806 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 811 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 815 "data/maps/Tamatown/scripts.pory"
	closemessage
# 817 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 837 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 802 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 818 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 819 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 820 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 821 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 822 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 823 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 824 "data/maps/Tamatown/scripts.pory"
	waitstate
# 825 "data/maps/Tamatown/scripts.pory"
	waitse
# 827 "data/maps/Tamatown/scripts.pory"
	delay 48
# 829 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 832 "data/maps/Tamatown/scripts.pory"
	closemessage
# 834 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 842 "data/maps/Tamatown/scripts.pory"
	lock
# 844 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_2
# 851 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_3
# 870 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 871 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 872 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_4
# 875 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_1:
# 878 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 845 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 846 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 847 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 850 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_1

Tamatown_EventScript_Torchic_3:
# 852 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 853 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 854 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 859 "data/maps/Tamatown/scripts.pory"
	closemessage
# 861 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_3
# 864 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 865 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 866 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 867 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_1


Tamatown_EventScript_StepInPoop::
# 882 "data/maps/Tamatown/scripts.pory"
	lock
# 883 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 884 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 888 "data/maps/Tamatown/scripts.pory"
	lock
# 889 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 892 "data/maps/Tamatown/scripts.pory"
	closemessage
# 893 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 897 "data/maps/Tamatown/scripts.pory"
	lock
# 898 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 899 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 900 "data/maps/Tamatown/scripts.pory"
	waitse
# 901 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 902 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 906 "data/maps/Tamatown/scripts.pory"
	lock
# 908 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 914 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 919 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 923 "data/maps/Tamatown/scripts.pory"
	closemessage
# 925 "data/maps/Tamatown/scripts.pory"
	delay 32
# 927 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 995 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 909 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 910 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 911 "data/maps/Tamatown/scripts.pory"
	waitse
# 912 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 928 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 932 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 936 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 941 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 946 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 949 "data/maps/Tamatown/scripts.pory"
	closemessage
# 951 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 952 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_4
# 953 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 954 "data/maps/Tamatown/scripts.pory"
	waitse
# 955 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 956 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_5
# 957 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 958 "data/maps/Tamatown/scripts.pory"
	waitse
# 960 "data/maps/Tamatown/scripts.pory"
	delay 32
# 961 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 963 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 964 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_4
# 965 "data/maps/Tamatown/scripts.pory"
	waitse
# 966 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 968 "data/maps/Tamatown/scripts.pory"
	delay 32
# 970 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 971 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 972 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 976 "data/maps/Tamatown/scripts.pory"
	closemessage
# 978 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 981 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 982 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 983 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 984 "data/maps/Tamatown/scripts.pory"
	closemessage
# 986 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 988 "data/maps/Tamatown/scripts.pory"
	delay 16
# 990 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 991 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 929 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 933 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 937 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


# 46 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 46 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 99 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 99 "data/maps/Tamatown/scripts.pory"
	walk_right
# 99 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 101 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 101 "data/maps/Tamatown/scripts.pory"
	walk_left
# 101 "data/maps/Tamatown/scripts.pory"
	walk_down
# 101 "data/maps/Tamatown/scripts.pory"
	walk_down
# 101 "data/maps/Tamatown/scripts.pory"
	walk_right
# 101 "data/maps/Tamatown/scripts.pory"
	walk_right
# 101 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 103 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 103 "data/maps/Tamatown/scripts.pory"
	walk_down
# 103 "data/maps/Tamatown/scripts.pory"
	walk_right
# 103 "data/maps/Tamatown/scripts.pory"
	walk_right
# 103 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 161 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 161 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 194 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 194 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
# 194 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 299 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 299 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 299 "data/maps/Tamatown/scripts.pory"
	delay_16
# 299 "data/maps/Tamatown/scripts.pory"
	delay_16
# 299 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 312 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 313 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 314 "data/maps/Tamatown/scripts.pory"
	delay_16
# 314 "data/maps/Tamatown/scripts.pory"
	delay_16
# 315 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 316 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 317 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 320 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 321 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 322 "data/maps/Tamatown/scripts.pory"
	delay_16
# 322 "data/maps/Tamatown/scripts.pory"
	delay_16
# 323 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 324 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 325 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 345 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 345 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 712 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 713 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 719 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 720 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 722 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 722 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 929 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 930 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 930 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 930 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 930 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 933 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 934 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 934 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 934 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 934 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 937 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 938 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 938 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 938 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 938 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 941 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 942 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 942 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 942 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 942 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 952 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 952 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 956 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_5:
# 956 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 956 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 956 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

Tamatown_EventScript_Arcade_Text_0:
# 20 "data/maps/Tamatown/scripts.pory"
	.string "Play {COLOR RED}Pachinko{COLOR DARK_GRAY}?\p$"

Tamatown_EventScript_Arcade_Text_1:
# 24 "data/maps/Tamatown/scripts.pory"
	.string "Play$"

Tamatown_EventScript_Arcade_Text_2:
# 25 "data/maps/Tamatown/scripts.pory"
	.string "Don't play$"

Tamatown_EventScript_Porygon_Text_0:
# 50 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_1:
# 52 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_2:
# 60 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_3:
# 71 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_4:
# 84 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_5:
# 85 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_6:
# 93 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_7:
# 120 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 131 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 141 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 143 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 148 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 152 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 153 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 166 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 170 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 171 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 183 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 185 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 189 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 190 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 201 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 218 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Skitty_Text_0:
# 227 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Skitty_Text_1:
# 229 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "Would you be so kind as to find me some\nmore yarn?$"

Tamatown_EventScript_Trashcan_Text_0:
# 237 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 247 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 251 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 256 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 261 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 262 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 267 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 271 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 272 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 282 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 284 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 304 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 333 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 348 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 362 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 370 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 383 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 394 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 403 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 408 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 411 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 414 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 417 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 420 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 423 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 425 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 435 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 447 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 460 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 467 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 472 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 479 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 484 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 491 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 496 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 508 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 515 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 520 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 527 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 545 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 547 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 558 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 570 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 571 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 578 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 595 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 602 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 609 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 618 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 625 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 632 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 641 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 648 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 655 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 663 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 675 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 695 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 704 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 706 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 743 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 746 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 753 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 762 "data/maps/Tamatown/scripts.pory"
	.string "You got a Lucky Egg!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 779 "data/maps/Tamatown/scripts.pory"
	.string "Use this letterbox to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 793 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 807 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 812 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 813 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 830 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 846 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 848 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_2:
# 855 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_3:
# 862 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat poster for your room!$"

Tamatown_EventScript_Torchic_Text_4:
# 873 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 890 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, hot dogs…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 915 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 920 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 921 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 947 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 971 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 973 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool plushie if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 979 "data/maps/Tamatown/scripts.pory"
	.string "You got a Ditto plushie for your room!$"
