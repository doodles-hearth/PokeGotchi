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
	goto_if_set POKEGOTCHI_FLAG_SKITTY_FOLLOWING, Tamatown_EventScript_Porygon_2
# 77 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_5
# 88 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 90 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 91 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 92 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_4
# 99 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_4:
# 102 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_9
Tamatown_EventScript_Porygon_8:
# 116 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_6, Tamatown_EventScript_Porygon_Text_7
# 121 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 122 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_13
# 150 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 151 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 152 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_9
# 157 "data/maps/Tamatown/scripts.pory"
	closemessage
# 159 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 65 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 66 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Porygon_Movement_0
# 67 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 68 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
# 72 "data/maps/Tamatown/scripts.pory"
	closemessage
# 73 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Porygon_5:
# 78 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 79 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_1
# 81 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 83 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 84 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_3
	goto Tamatown_EventScript_Porygon_4

Tamatown_EventScript_Porygon_9:
# 103 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_5
# 106 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 107 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 109 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 111 "data/maps/Tamatown/scripts.pory"
	closemessage
# 113 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_13:
# 123 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 124 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 125 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_8
# 128 "data/maps/Tamatown/scripts.pory"
	closemessage
# 130 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 131 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_17
# 133 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_18
# 135 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_19
Tamatown_EventScript_Porygon_15:
# 139 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 141 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 142 "data/maps/Tamatown/scripts.pory"
	delay 32
# 143 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 144 "data/maps/Tamatown/scripts.pory"
	waitstate
# 145 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 146 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 147 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_17:
# 132 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_18:
# 134 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_19:
# 136 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_4
	goto Tamatown_EventScript_Porygon_15


Tamatown_EventScript_Tree::
# 163 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 170 "data/maps/Tamatown/scripts.pory"
	lock
# 172 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 180 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 184 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 189 "data/maps/Tamatown/scripts.pory"
	closemessage
# 191 "data/maps/Tamatown/scripts.pory"
	delay 24
# 193 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 194 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 195 "data/maps/Tamatown/scripts.pory"
	waitse
# 196 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 198 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 202 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 207 "data/maps/Tamatown/scripts.pory"
	closemessage
# 209 "data/maps/Tamatown/scripts.pory"
	delay 24
# 211 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 212 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 213 "data/maps/Tamatown/scripts.pory"
	waitse
# 214 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 216 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 217 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 221 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 226 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 227 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_1
# 228 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 229 "data/maps/Tamatown/scripts.pory"
	waitse
# 231 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 232 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 233 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 239 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 241 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 244 "data/maps/Tamatown/scripts.pory"
	closemessage
# 246 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 173 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 174 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 175 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 178 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 250 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
# 256 "data/maps/Tamatown/scripts.pory"
	lock
# 258 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_SKITTY_FOLLOWING, Tamatown_EventScript_Skitty_2
# 269 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 270 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 271 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 277 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Skitty_Text_2, Tamatown_EventScript_House_Text_2
# 282 "data/maps/Tamatown/scripts.pory"
	closemessage
# 284 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Skitty_5
# 291 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 292 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 293 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_3
# 296 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 297 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Skitty_4:
# 300 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Skitty_2:
# 259 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 260 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 261 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_0
# 264 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 265 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Skitty_5:
# 285 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 286 "data/maps/Tamatown/scripts.pory"
	setfollowernpc LOCALID_SKITTY, FOLLOWER_NPC_FLAG_CLEAR_ON_WHITE_OUT
# 287 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 289 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_SKITTY_FOLLOWING
	goto Tamatown_EventScript_Skitty_4


Tamatown_EventScript_Trashcan::
# 304 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 312 "data/maps/Tamatown/scripts.pory"
	lock
# 314 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 342 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_4
# 347 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_5, Tamatown_EventScript_TrubbishCan_Text_6
# 352 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_9
# 456 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_16
Tamatown_EventScript_TrubbishCan_8:
# 460 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 463 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 315 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_SKITTY_FOLLOWING, Tamatown_EventScript_TrubbishCan_6
# 334 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 335 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 337 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 316 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 317 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 318 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
# 322 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 323 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_TrubbishCan_Movement_0
# 324 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_ENCOUNTER
# 325 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 329 "data/maps/Tamatown/scripts.pory"
	closemessage
# 330 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_TrubbishCan_9:
# 353 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 357 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_8, Tamatown_EventScript_TrubbishCan_Text_9
# 362 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_13
# 398 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_17
# 407 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_3
Tamatown_EventScript_TrubbishCan_16:
# 416 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 417 "data/maps/Tamatown/scripts.pory"
	delay 32
# 419 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
# 422 "data/maps/Tamatown/scripts.pory"
	closemessage
# 424 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 425 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 427 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 428 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_1
# 429 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 431 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 432 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_4
# 433 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 434 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_12:
# 443 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 444 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 446 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 447 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 448 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 451 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 452 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 453 "data/maps/Tamatown/scripts.pory"
	closemessage
# 454 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_8

Tamatown_EventScript_TrubbishCan_13:
# 363 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 364 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 365 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 366 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 367 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 368 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 369 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_10
# 370 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 374 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 375 "data/maps/Tamatown/scripts.pory"
	closemessage
# 377 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 378 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_1
# 379 "data/maps/Tamatown/scripts.pory"
	waitse
# 380 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 382 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 383 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 385 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 386 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_1
# 387 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 389 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 390 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
	goto Tamatown_EventScript_TrubbishCan_12

Tamatown_EventScript_TrubbishCan_17:
# 399 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
	goto Tamatown_EventScript_TrubbishCan_16


Tamatown_EventScript_VendingMachine::
# 467 "data/maps/Tamatown/scripts.pory"
	lock
# 469 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 470 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 473 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 489 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 494 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 497 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 500 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 503 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 506 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 509 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 512 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 513 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 514 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 516 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 518 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 518 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 529 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 530 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 541 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 542 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 544 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 545 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 557 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 569 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 581 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 593 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 605 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 619 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 620 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 621 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 622 "data/maps/Tamatown/scripts.pory"
	closemessage
# 624 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 480 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 484 "data/maps/Tamatown/scripts.pory"
	closemessage
# 485 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 475 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 474 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 477 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 476 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 478 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 495 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 498 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 501 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 504 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 507 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 510 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 519 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 520 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 521 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 524 "data/maps/Tamatown/scripts.pory"
	closemessage
# 525 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 531 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 532 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 533 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 536 "data/maps/Tamatown/scripts.pory"
	closemessage
# 537 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 546 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 550 "data/maps/Tamatown/scripts.pory"
	closemessage
# 551 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 552 "data/maps/Tamatown/scripts.pory"
	waitse
# 553 "data/maps/Tamatown/scripts.pory"
	delay 32
# 554 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 555 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 558 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 562 "data/maps/Tamatown/scripts.pory"
	closemessage
# 563 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 564 "data/maps/Tamatown/scripts.pory"
	waitse
# 565 "data/maps/Tamatown/scripts.pory"
	delay 32
# 566 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 567 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 570 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 574 "data/maps/Tamatown/scripts.pory"
	closemessage
# 575 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 576 "data/maps/Tamatown/scripts.pory"
	waitse
# 577 "data/maps/Tamatown/scripts.pory"
	delay 32
# 578 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 579 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 582 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 586 "data/maps/Tamatown/scripts.pory"
	closemessage
# 587 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 588 "data/maps/Tamatown/scripts.pory"
	waitse
# 589 "data/maps/Tamatown/scripts.pory"
	delay 32
# 590 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 591 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 594 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 598 "data/maps/Tamatown/scripts.pory"
	closemessage
# 599 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 600 "data/maps/Tamatown/scripts.pory"
	waitse
# 601 "data/maps/Tamatown/scripts.pory"
	delay 32
# 602 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 603 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 606 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 610 "data/maps/Tamatown/scripts.pory"
	closemessage
# 611 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 612 "data/maps/Tamatown/scripts.pory"
	waitse
# 613 "data/maps/Tamatown/scripts.pory"
	delay 32
# 614 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 615 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 628 "data/maps/Tamatown/scripts.pory"
	lock
# 630 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 640 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 642 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 643 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 644 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 656 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 661 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 759 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 760 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 761 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 768 "data/maps/Tamatown/scripts.pory"
	closemessage
# 770 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 631 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 632 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 633 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 662 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 663 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 664 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 669 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 670 "data/maps/Tamatown/scripts.pory"
	delay 32
# 671 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 672 "data/maps/Tamatown/scripts.pory"
	waitstate
# 673 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 674 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 676 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 678 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 701 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 724 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 748 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 749 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
Tamatown_EventScript_Slowpoke_9:
# 755 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 679 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 681 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 686 "data/maps/Tamatown/scripts.pory"
	closemessage
# 688 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 691 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 692 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 693 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 695 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 698 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 699 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 700 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 702 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 704 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 709 "data/maps/Tamatown/scripts.pory"
	closemessage
# 711 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 714 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 715 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 716 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 718 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 721 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 722 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 723 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 725 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 727 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 732 "data/maps/Tamatown/scripts.pory"
	closemessage
# 734 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 737 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 738 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 739 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 741 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 744 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 745 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 746 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 756 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 774 "data/maps/Tamatown/scripts.pory"
	lock
# 776 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 790 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 791 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 792 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 797 "data/maps/Tamatown/scripts.pory"
	closemessage
# 799 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 803 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 804 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 805 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 806 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 809 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 810 "data/maps/Tamatown/scripts.pory"
	delay 44
# 811 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 812 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 813 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 814 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 815 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 817 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 818 "data/maps/Tamatown/scripts.pory"
	delay 48
# 820 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 821 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 824 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 777 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 778 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 779 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 780 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 781 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 784 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 785 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 786 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 787 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 828 "data/maps/Tamatown/scripts.pory"
	lock
# 829 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 837 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 838 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 839 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 845 "data/maps/Tamatown/scripts.pory"
	closemessage
# 847 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 848 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 851 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 852 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 853 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 854 "data/maps/Tamatown/scripts.pory"
	closemessage
# 856 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 859 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 830 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 831 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 832 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 835 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 863 "data/maps/Tamatown/scripts.pory"
	lock
# 865 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 871 "data/maps/Tamatown/scripts.pory"
	closemessage
# 873 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 877 "data/maps/Tamatown/scripts.pory"
	lock
# 879 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 882 "data/maps/Tamatown/scripts.pory"
	closemessage
# 884 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 888 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 891 "data/maps/Tamatown/scripts.pory"
	lock
# 893 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 898 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 902 "data/maps/Tamatown/scripts.pory"
	closemessage
# 904 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 924 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 889 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 905 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 906 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 907 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 908 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 909 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 910 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 911 "data/maps/Tamatown/scripts.pory"
	waitstate
# 912 "data/maps/Tamatown/scripts.pory"
	waitse
# 914 "data/maps/Tamatown/scripts.pory"
	delay 48
# 916 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 919 "data/maps/Tamatown/scripts.pory"
	closemessage
# 921 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 929 "data/maps/Tamatown/scripts.pory"
	lock
# 931 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_2
# 938 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_3
# 957 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 958 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 959 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_4
# 962 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_1:
# 965 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 932 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 933 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 934 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 937 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_1

Tamatown_EventScript_Torchic_3:
# 939 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 940 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 941 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 946 "data/maps/Tamatown/scripts.pory"
	closemessage
# 948 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_3
# 951 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 952 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 953 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 954 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_1


Tamatown_EventScript_StepInPoop::
# 969 "data/maps/Tamatown/scripts.pory"
	lock
# 970 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 971 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 975 "data/maps/Tamatown/scripts.pory"
	lock
# 976 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 979 "data/maps/Tamatown/scripts.pory"
	closemessage
# 980 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 984 "data/maps/Tamatown/scripts.pory"
	lock
# 985 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 986 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 987 "data/maps/Tamatown/scripts.pory"
	waitse
# 988 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 989 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 993 "data/maps/Tamatown/scripts.pory"
	lock
# 995 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 1002 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 1007 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 1011 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1013 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1015 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1083 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 996 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 997 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 998 "data/maps/Tamatown/scripts.pory"
	waitse
# 999 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1000 "data/maps/Tamatown/scripts.pory"
	delay 1
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 1016 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 1020 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 1024 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 1029 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 1034 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 1037 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1039 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1040 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_0
# 1041 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1042 "data/maps/Tamatown/scripts.pory"
	waitse
# 1043 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 1044 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_4
# 1045 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1046 "data/maps/Tamatown/scripts.pory"
	waitse
# 1048 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1049 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1051 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1052 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_0
# 1053 "data/maps/Tamatown/scripts.pory"
	waitse
# 1054 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1056 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1058 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1059 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 1060 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 1064 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1066 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1069 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1070 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1071 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1072 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1074 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1076 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1078 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1079 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 1017 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 1021 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 1025 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


# 66 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 66 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 79 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 79 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 132 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 132 "data/maps/Tamatown/scripts.pory"
	walk_right
# 132 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 134 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 134 "data/maps/Tamatown/scripts.pory"
	walk_left
# 134 "data/maps/Tamatown/scripts.pory"
	walk_down
# 134 "data/maps/Tamatown/scripts.pory"
	walk_down
# 134 "data/maps/Tamatown/scripts.pory"
	walk_right
# 134 "data/maps/Tamatown/scripts.pory"
	walk_right
# 134 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 136 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_4:
# 136 "data/maps/Tamatown/scripts.pory"
	walk_down
# 136 "data/maps/Tamatown/scripts.pory"
	walk_right
# 136 "data/maps/Tamatown/scripts.pory"
	walk_right
# 136 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 194 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 194 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 227 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 227 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
# 227 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 323 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 323 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 386 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 386 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 386 "data/maps/Tamatown/scripts.pory"
	delay_16
# 386 "data/maps/Tamatown/scripts.pory"
	delay_16
# 386 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 399 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 400 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 401 "data/maps/Tamatown/scripts.pory"
	delay_16
# 401 "data/maps/Tamatown/scripts.pory"
	delay_16
# 402 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 403 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 404 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 407 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 408 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 409 "data/maps/Tamatown/scripts.pory"
	delay_16
# 409 "data/maps/Tamatown/scripts.pory"
	delay_16
# 410 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 411 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 412 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 432 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_4:
# 432 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 799 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 800 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 806 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 807 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 809 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 809 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 1017 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 1018 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1018 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1018 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1018 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1021 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 1022 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1022 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1022 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1022 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1025 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 1026 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1026 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1026 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1026 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1029 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 1030 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1030 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1030 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1030 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1044 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 1044 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1044 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 1044 "data/maps/Tamatown/scripts.pory"
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
# 65 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Porygon_Text_1:
# 69 "data/maps/Tamatown/scripts.pory"
	.string "Porygon is such a nerd!\nI don't want a virtual ball of yarn!$"

Tamatown_EventScript_Porygon_Text_2:
# 83 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_3:
# 85 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_4:
# 93 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_5:
# 104 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_6:
# 117 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_7:
# 118 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_8:
# 126 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_9:
# 153 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 164 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 174 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 176 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 181 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 185 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 186 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 199 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 203 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 204 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 216 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 218 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 222 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 223 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 234 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 251 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Skitty_Text_0:
# 262 "data/maps/Tamatown/scripts.pory"
	.string "I want a ball of yarn!\nMeow!$"

Tamatown_EventScript_Skitty_Text_1:
# 272 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "Would you be so kind as to find me some\nmore yarn?\p"
	.string "Take me with you!$"

Tamatown_EventScript_Skitty_Text_2:
# 278 "data/maps/Tamatown/scripts.pory"
	.string "Alright$"

Tamatown_EventScript_Skitty_Text_3:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "Alright… Meow…$"

Tamatown_EventScript_Trashcan_Text_0:
# 305 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 316 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 319 "data/maps/Tamatown/scripts.pory"
	.string "Is this cat edible?$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 326 "data/maps/Tamatown/scripts.pory"
	.string "Fshhhh!!!$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 338 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 343 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 348 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 349 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 354 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 358 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 359 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 369 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 371 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 391 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 420 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 435 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_15:
# 449 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_16:
# 457 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 470 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 481 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 490 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 495 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 498 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 501 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 504 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 507 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 510 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 512 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 522 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 534 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 547 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 554 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 559 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 566 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 571 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 578 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 583 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 595 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 602 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 607 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 614 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 632 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 634 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 645 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 657 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 658 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 665 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 682 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 689 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 696 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 705 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 712 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 719 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 728 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 735 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 742 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 750 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 762 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 782 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 791 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 793 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 830 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 833 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 840 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 849 "data/maps/Tamatown/scripts.pory"
	.string "You got a Lucky Egg!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 866 "data/maps/Tamatown/scripts.pory"
	.string "Use this letterbox to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 880 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 894 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 899 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 900 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 917 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 933 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 935 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_2:
# 942 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_3:
# 949 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat poster for your room!$"

Tamatown_EventScript_Torchic_Text_4:
# 960 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 977 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, hot dogs…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 1003 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 1008 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 1009 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 1035 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 1059 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 1061 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool plushie if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 1067 "data/maps/Tamatown/scripts.pory"
	.string "You got a Ditto plushie for your room!$"
