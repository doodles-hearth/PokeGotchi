Tamatown_MapScripts::
# 5 "data/maps/Tamatown/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 6 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_2
Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 11 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_4
	return

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
# 7 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_ICE_CREAM, 33, 20
# 8 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
	goto Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_4:
# 12 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
	return


Tamatown_EventScript_House::
# 18 "data/maps/Tamatown/scripts.pory"
	lock
# 19 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_House_Text_0
# 23 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_House_Text_1, Tamatown_EventScript_House_Text_2
# 28 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 29 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_House_2
# 32 "data/maps/Tamatown/scripts.pory"
	closemessage
# 33 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_House_2:
# 30 "data/maps/Tamatown/scripts.pory"
	callnative ReturnToPokegotchiHouse
	return


Tamatown_EventScript_Arcade::
# 38 "data/maps/Tamatown/scripts.pory"
	lock
# 40 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 42 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Arcade_Text_0
# 46 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Arcade_Text_1, Tamatown_EventScript_Arcade_Text_2
# 51 "data/maps/Tamatown/scripts.pory"
	closemessage
# 52 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 54 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 55 "data/maps/Tamatown/scripts.pory"
	delay 32
# 56 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 57 "data/maps/Tamatown/scripts.pory"
	waitstate
# 58 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 59 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 61 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Porygon::
# 65 "data/maps/Tamatown/scripts.pory"
	lockall
# 66 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 67 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Porygon_2
# 80 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_5
# 91 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 93 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 94 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 95 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_4
# 102 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_4:
# 105 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_9
Tamatown_EventScript_Porygon_8:
# 119 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_6, Tamatown_EventScript_Porygon_Text_7
# 124 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 125 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_13
# 153 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 154 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 155 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_9
# 160 "data/maps/Tamatown/scripts.pory"
	closemessage
# 162 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 68 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 69 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Porygon_Movement_0
# 70 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 71 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
# 75 "data/maps/Tamatown/scripts.pory"
	closemessage
# 76 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Porygon_5:
# 81 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 82 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_1
# 84 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 86 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 87 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_3
	goto Tamatown_EventScript_Porygon_4

Tamatown_EventScript_Porygon_9:
# 106 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_5
# 109 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 110 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 112 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 114 "data/maps/Tamatown/scripts.pory"
	closemessage
# 116 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_13:
# 126 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 127 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 128 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_8
# 131 "data/maps/Tamatown/scripts.pory"
	closemessage
# 133 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 134 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_17
# 136 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_18
# 138 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_19
Tamatown_EventScript_Porygon_15:
# 142 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 144 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 145 "data/maps/Tamatown/scripts.pory"
	delay 32
# 146 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 147 "data/maps/Tamatown/scripts.pory"
	waitstate
# 148 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 149 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 150 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_17:
# 135 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_18:
# 137 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_19:
# 139 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_4
	goto Tamatown_EventScript_Porygon_15


Tamatown_EventScript_Tree::
# 166 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 173 "data/maps/Tamatown/scripts.pory"
	lock
# 174 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 175 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Tangela_2
# 229 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_5
# 248 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_7
# 252 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_8, Tamatown_EventScript_Tangela_Text_9
# 257 "data/maps/Tamatown/scripts.pory"
	closemessage
# 259 "data/maps/Tamatown/scripts.pory"
	delay 24
# 261 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 262 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_2
# 263 "data/maps/Tamatown/scripts.pory"
	waitse
# 264 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 266 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_10
# 270 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_11, Tamatown_EventScript_Tangela_Text_12
# 275 "data/maps/Tamatown/scripts.pory"
	closemessage
# 277 "data/maps/Tamatown/scripts.pory"
	delay 24
# 279 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 280 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_2
# 281 "data/maps/Tamatown/scripts.pory"
	waitse
# 282 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 284 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_13
# 285 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_14
# 289 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_15, Tamatown_EventScript_Tangela_Text_16
# 294 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 295 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 296 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 297 "data/maps/Tamatown/scripts.pory"
	waitse
# 299 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 300 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 301 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_17
# 307 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 309 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_4:
# 312 "data/maps/Tamatown/scripts.pory"
	closemessage
# 314 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 176 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 177 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Tangela_Movement_0
# 178 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 179 "data/maps/Tamatown/scripts.pory"
	waitse
# 180 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 181 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Porygon_Movement_1
# 182 "data/maps/Tamatown/scripts.pory"
	waitse
# 183 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 184 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 185 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 186 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_0
# 189 "data/maps/Tamatown/scripts.pory"
	closemessage
# 191 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 192 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_0
# 193 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 194 "data/maps/Tamatown/scripts.pory"
	waitse
# 195 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_1
# 196 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 197 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 198 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 201 "data/maps/Tamatown/scripts.pory"
	closemessage
# 203 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 204 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 205 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_3
# 209 "data/maps/Tamatown/scripts.pory"
	closemessage
# 211 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 212 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Tangela_Text_4
# 215 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 216 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 217 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_RUG
# 219 "data/maps/Tamatown/scripts.pory"
	destroyfollowernpc
# 220 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 221 "data/maps/Tamatown/scripts.pory"
	delay 32
# 222 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
# 223 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 225 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Tangela_5:
# 230 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Tangela_9
# 241 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 242 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 243 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_6
# 246 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_4

Tamatown_EventScript_Tangela_9:
# 231 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 232 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 233 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 236 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 237 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Sign::
# 318 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_SkittyFollowing::
# 324 "data/maps/Tamatown/scripts.pory"
	lock
# 325 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 326 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 327 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_SkittyFollowing_Text_0
# 330 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 331 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Skitty::
# 336 "data/maps/Tamatown/scripts.pory"
	lock
# 338 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Skitty_2
# 349 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 350 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 351 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 357 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Skitty_Text_2, Tamatown_EventScript_House_Text_2
# 362 "data/maps/Tamatown/scripts.pory"
	closemessage
# 364 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Skitty_5
# 370 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 371 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 372 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_3
# 375 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 376 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Skitty_4:
# 379 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Skitty_2:
# 339 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 340 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 341 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_0
# 344 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 345 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Skitty_5:
# 365 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 367 "data/maps/Tamatown/scripts.pory"
	setfollowernpc LOCALID_SKITTY, FOLLOWER_NPC_FLAG_ALL, Tamatown_EventScript_SkittyFollowing
# 368 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Skitty_4


Tamatown_EventScript_Trashcan::
# 383 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 391 "data/maps/Tamatown/scripts.pory"
	lock
# 393 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 422 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_4
# 427 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_5, Tamatown_EventScript_TrubbishCan_Text_6
# 432 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_9
# 536 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_16
Tamatown_EventScript_TrubbishCan_8:
# 540 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 543 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 394 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 395 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_TrubbishCan_6
# 414 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 415 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 417 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 396 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 397 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 398 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
# 402 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 403 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Tangela_Movement_0
# 404 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_ENCOUNTER
# 405 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 409 "data/maps/Tamatown/scripts.pory"
	closemessage
# 410 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_TrubbishCan_9:
# 433 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 437 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_8, Tamatown_EventScript_TrubbishCan_Text_9
# 442 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_13
# 478 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_17
# 487 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_16:
# 496 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 497 "data/maps/Tamatown/scripts.pory"
	delay 32
# 499 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
# 502 "data/maps/Tamatown/scripts.pory"
	closemessage
# 504 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 505 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 507 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 508 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 509 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 511 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 512 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 513 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 514 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_12:
# 523 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 524 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 526 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 527 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 528 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 531 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 532 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 533 "data/maps/Tamatown/scripts.pory"
	closemessage
# 534 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_8

Tamatown_EventScript_TrubbishCan_13:
# 443 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 444 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 445 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 446 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 447 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 448 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 449 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_10
# 450 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 454 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 455 "data/maps/Tamatown/scripts.pory"
	closemessage
# 457 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 458 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_3
# 459 "data/maps/Tamatown/scripts.pory"
	waitse
# 460 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 462 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 463 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 465 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 466 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 467 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 469 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 470 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
	goto Tamatown_EventScript_TrubbishCan_12

Tamatown_EventScript_TrubbishCan_17:
# 479 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_16


Tamatown_EventScript_VendingMachine::
# 547 "data/maps/Tamatown/scripts.pory"
	lock
# 549 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 550 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 553 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 569 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 574 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 577 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 580 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 583 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 586 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 589 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 592 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 593 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 594 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 596 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 598 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 598 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 609 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 610 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 621 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 622 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 624 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 625 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 637 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 649 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 661 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 673 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 685 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 699 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 700 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 701 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 702 "data/maps/Tamatown/scripts.pory"
	closemessage
# 704 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 560 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 564 "data/maps/Tamatown/scripts.pory"
	closemessage
# 565 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 555 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 554 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 557 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 556 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 558 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 575 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 578 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 581 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 584 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 587 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 590 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 599 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 600 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 601 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 604 "data/maps/Tamatown/scripts.pory"
	closemessage
# 605 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 611 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 612 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 613 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 616 "data/maps/Tamatown/scripts.pory"
	closemessage
# 617 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 626 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 630 "data/maps/Tamatown/scripts.pory"
	closemessage
# 631 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 632 "data/maps/Tamatown/scripts.pory"
	waitse
# 633 "data/maps/Tamatown/scripts.pory"
	delay 32
# 634 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 635 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 638 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 642 "data/maps/Tamatown/scripts.pory"
	closemessage
# 643 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 644 "data/maps/Tamatown/scripts.pory"
	waitse
# 645 "data/maps/Tamatown/scripts.pory"
	delay 32
# 646 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 647 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 650 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 654 "data/maps/Tamatown/scripts.pory"
	closemessage
# 655 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 656 "data/maps/Tamatown/scripts.pory"
	waitse
# 657 "data/maps/Tamatown/scripts.pory"
	delay 32
# 658 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 659 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 662 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 666 "data/maps/Tamatown/scripts.pory"
	closemessage
# 667 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 668 "data/maps/Tamatown/scripts.pory"
	waitse
# 669 "data/maps/Tamatown/scripts.pory"
	delay 32
# 670 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 671 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 674 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 678 "data/maps/Tamatown/scripts.pory"
	closemessage
# 679 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 680 "data/maps/Tamatown/scripts.pory"
	waitse
# 681 "data/maps/Tamatown/scripts.pory"
	delay 32
# 682 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 683 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 686 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 690 "data/maps/Tamatown/scripts.pory"
	closemessage
# 691 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 692 "data/maps/Tamatown/scripts.pory"
	waitse
# 693 "data/maps/Tamatown/scripts.pory"
	delay 32
# 694 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 695 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 708 "data/maps/Tamatown/scripts.pory"
	lock
# 710 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 720 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 722 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 723 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 724 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 736 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 741 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 839 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 840 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 841 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 848 "data/maps/Tamatown/scripts.pory"
	closemessage
# 850 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 711 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 712 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 713 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 742 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 743 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 744 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 749 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 750 "data/maps/Tamatown/scripts.pory"
	delay 32
# 751 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 752 "data/maps/Tamatown/scripts.pory"
	waitstate
# 753 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 754 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 756 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 758 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 781 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 804 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 828 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 829 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
Tamatown_EventScript_Slowpoke_9:
# 835 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 759 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 761 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 766 "data/maps/Tamatown/scripts.pory"
	closemessage
# 768 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 771 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 772 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 773 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 775 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 778 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 779 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 780 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 782 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 784 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 789 "data/maps/Tamatown/scripts.pory"
	closemessage
# 791 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 794 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 795 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 796 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 798 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 801 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 802 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 803 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 805 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 807 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 812 "data/maps/Tamatown/scripts.pory"
	closemessage
# 814 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 817 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 818 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 819 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 821 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 824 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 825 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 826 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 836 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 854 "data/maps/Tamatown/scripts.pory"
	lock
# 856 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 870 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 871 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 872 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 877 "data/maps/Tamatown/scripts.pory"
	closemessage
# 879 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 883 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 884 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 885 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 886 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 889 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 890 "data/maps/Tamatown/scripts.pory"
	delay 44
# 891 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 892 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 893 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 894 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 895 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 897 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 898 "data/maps/Tamatown/scripts.pory"
	delay 48
# 900 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 901 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 904 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 857 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 858 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 859 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 860 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 861 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 864 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 865 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 866 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 867 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 908 "data/maps/Tamatown/scripts.pory"
	lock
# 909 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 917 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 918 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 919 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 925 "data/maps/Tamatown/scripts.pory"
	closemessage
# 927 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 928 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 931 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 932 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 933 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 934 "data/maps/Tamatown/scripts.pory"
	closemessage
# 936 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 939 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 910 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 911 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 912 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 915 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 943 "data/maps/Tamatown/scripts.pory"
	lock
# 945 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 951 "data/maps/Tamatown/scripts.pory"
	closemessage
# 953 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 957 "data/maps/Tamatown/scripts.pory"
	lock
# 959 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 962 "data/maps/Tamatown/scripts.pory"
	closemessage
# 964 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 968 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 971 "data/maps/Tamatown/scripts.pory"
	lock
# 973 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 978 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 982 "data/maps/Tamatown/scripts.pory"
	closemessage
# 984 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 1004 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 969 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 985 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 986 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 987 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 988 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 989 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 990 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 991 "data/maps/Tamatown/scripts.pory"
	waitstate
# 992 "data/maps/Tamatown/scripts.pory"
	waitse
# 994 "data/maps/Tamatown/scripts.pory"
	delay 48
# 996 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 999 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1001 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 1009 "data/maps/Tamatown/scripts.pory"
	lock
# 1010 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 1011 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Torchic_2
# 1023 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_5
# 1030 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_6
# 1049 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 1050 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1051 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_5
# 1054 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_4:
# 1057 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 1012 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1013 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_ENCOUNTER
# 1014 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 1018 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1019 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Torchic_5:
# 1024 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 1025 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1026 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 1029 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_4

Tamatown_EventScript_Torchic_6:
# 1031 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 1032 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1033 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_3
# 1038 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1040 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_4
# 1043 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1044 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1045 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1046 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_4


Tamatown_EventScript_StepInPoop::
# 1061 "data/maps/Tamatown/scripts.pory"
	lock
# 1062 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 1063 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 1067 "data/maps/Tamatown/scripts.pory"
	lock
# 1068 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 1071 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1072 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 1076 "data/maps/Tamatown/scripts.pory"
	lock
# 1077 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1078 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1079 "data/maps/Tamatown/scripts.pory"
	waitse
# 1080 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 1081 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 1085 "data/maps/Tamatown/scripts.pory"
	lock
# 1087 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 1094 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 1099 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 1103 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1105 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1107 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1175 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 1088 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1089 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1090 "data/maps/Tamatown/scripts.pory"
	waitse
# 1091 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1092 "data/maps/Tamatown/scripts.pory"
	delay 1
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 1108 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 1112 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 1116 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 1121 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 1126 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 1129 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1131 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1132 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 1133 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1134 "data/maps/Tamatown/scripts.pory"
	waitse
# 1135 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 1136 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_4
# 1137 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1138 "data/maps/Tamatown/scripts.pory"
	waitse
# 1140 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1141 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1143 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1144 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 1145 "data/maps/Tamatown/scripts.pory"
	waitse
# 1146 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1148 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1150 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1151 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 1152 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 1156 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1158 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1161 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1162 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1163 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1164 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1166 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1168 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1170 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1171 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 1109 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 1113 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 1117 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


# 69 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 69 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 82 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 82 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 135 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 135 "data/maps/Tamatown/scripts.pory"
	walk_right
# 135 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 137 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 137 "data/maps/Tamatown/scripts.pory"
	walk_left
# 137 "data/maps/Tamatown/scripts.pory"
	walk_down
# 137 "data/maps/Tamatown/scripts.pory"
	walk_down
# 137 "data/maps/Tamatown/scripts.pory"
	walk_right
# 137 "data/maps/Tamatown/scripts.pory"
	walk_right
# 137 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 139 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_4:
# 139 "data/maps/Tamatown/scripts.pory"
	walk_down
# 139 "data/maps/Tamatown/scripts.pory"
	walk_right
# 139 "data/maps/Tamatown/scripts.pory"
	walk_right
# 139 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 177 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 177 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 195 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 195 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
# 195 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
# 195 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 262 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_2:
# 262 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 295 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_3:
# 295 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
# 295 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 466 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 466 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 466 "data/maps/Tamatown/scripts.pory"
	delay_16
# 466 "data/maps/Tamatown/scripts.pory"
	delay_16
# 466 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 479 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 480 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 481 "data/maps/Tamatown/scripts.pory"
	delay_16
# 481 "data/maps/Tamatown/scripts.pory"
	delay_16
# 482 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 483 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 484 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 487 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 488 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 489 "data/maps/Tamatown/scripts.pory"
	delay_16
# 489 "data/maps/Tamatown/scripts.pory"
	delay_16
# 490 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 491 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 492 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 512 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 512 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 879 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 880 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 886 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 887 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 889 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 889 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 1109 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 1110 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1110 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1110 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1110 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1113 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 1114 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1114 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1114 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1114 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1117 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 1118 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1118 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1118 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1118 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1121 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 1122 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1122 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1122 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1122 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1136 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 1136 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1136 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 1136 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

Tamatown_EventScript_House_Text_0:
# 20 "data/maps/Tamatown/scripts.pory"
	.string "Go home?$"

Tamatown_EventScript_House_Text_1:
# 24 "data/maps/Tamatown/scripts.pory"
	.string "Yes$"

Tamatown_EventScript_House_Text_2:
# 25 "data/maps/Tamatown/scripts.pory"
	.string "No$"

Tamatown_EventScript_Arcade_Text_0:
# 43 "data/maps/Tamatown/scripts.pory"
	.string "Play {COLOR RED}Pachinko{COLOR DARK_GRAY}?\p$"

Tamatown_EventScript_Arcade_Text_1:
# 47 "data/maps/Tamatown/scripts.pory"
	.string "Play$"

Tamatown_EventScript_Arcade_Text_2:
# 48 "data/maps/Tamatown/scripts.pory"
	.string "Don't play$"

Tamatown_EventScript_Porygon_Text_0:
# 68 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Porygon_Text_1:
# 72 "data/maps/Tamatown/scripts.pory"
	.string "Porygon is such a nerd!\nI don't want a virtual ball of yarn!$"

Tamatown_EventScript_Porygon_Text_2:
# 86 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_3:
# 88 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_4:
# 96 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_5:
# 107 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_6:
# 120 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_7:
# 121 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_8:
# 129 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_9:
# 156 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 167 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 187 "data/maps/Tamatown/scripts.pory"
	.string "A ball! A ball of yarn! Meow!!$"

Tamatown_EventScript_Tangela_Text_1:
# 197 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_2:
# 199 "data/maps/Tamatown/scripts.pory"
	.string "I-I'm not a ball of yarn!\nI'm a tree!$"

Tamatown_EventScript_Tangela_Text_3:
# 206 "data/maps/Tamatown/scripts.pory"
	.string "Thank you, you odd little bug.\p"
	.string "I'll give you one of my crafting\nprojects in return!$"

Tamatown_EventScript_Tangela_Text_4:
# 213 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute crochet rug for your\nroom!$"

Tamatown_EventScript_Tangela_Text_5:
# 234 "data/maps/Tamatown/scripts.pory"
	.string "It's hard to hide in plain sight\nwith this one playing with my vines…$"

Tamatown_EventScript_Tangela_Text_6:
# 244 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_7:
# 249 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_8:
# 253 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_9:
# 254 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_10:
# 267 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_11:
# 271 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_12:
# 272 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_13:
# 284 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_14:
# 286 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_15:
# 290 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_16:
# 291 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_17:
# 302 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 319 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_SkittyFollowing_Text_0:
# 328 "data/maps/Tamatown/scripts.pory"
	.string "I want a ball of yarn!\nMeow!$"

Tamatown_EventScript_Skitty_Text_0:
# 342 "data/maps/Tamatown/scripts.pory"
	.string "Meow meow meow!\nYarn yarn yarn!$"

Tamatown_EventScript_Skitty_Text_1:
# 352 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "Would you be so kind as to find me some\nmore yarn?\p"
	.string "Take me with you!$"

Tamatown_EventScript_Skitty_Text_2:
# 358 "data/maps/Tamatown/scripts.pory"
	.string "Alright$"

Tamatown_EventScript_Skitty_Text_3:
# 373 "data/maps/Tamatown/scripts.pory"
	.string "Alright… Meow…$"

Tamatown_EventScript_Trashcan_Text_0:
# 384 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 396 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 399 "data/maps/Tamatown/scripts.pory"
	.string "Is this cat edible?$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 406 "data/maps/Tamatown/scripts.pory"
	.string "Fshhhh!!!$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 418 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 423 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 428 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 429 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 434 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 438 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 439 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 449 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 451 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 471 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 500 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 515 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_15:
# 529 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_16:
# 537 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 550 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 561 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 570 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 575 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 578 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 581 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 584 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 587 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 590 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 592 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 602 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 614 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 627 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 634 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 639 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 646 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 651 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 658 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 663 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 675 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 682 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 687 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 694 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 712 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 714 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 725 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 737 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 738 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 745 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 762 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 769 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 776 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 785 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 792 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 799 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 808 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 815 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 822 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 830 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 842 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 862 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 871 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 873 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 910 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 913 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 920 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 929 "data/maps/Tamatown/scripts.pory"
	.string "You got a Lucky Egg!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 946 "data/maps/Tamatown/scripts.pory"
	.string "Use this letterbox to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 960 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 974 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 979 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 980 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 997 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 1012 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 1015 "data/maps/Tamatown/scripts.pory"
	.string "I taut I taw a puddy-tat!\nG-get it away from me!$"

Tamatown_EventScript_Torchic_Text_2:
# 1027 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_3:
# 1034 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_4:
# 1041 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat poster for your room!$"

Tamatown_EventScript_Torchic_Text_5:
# 1052 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 1069 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, hot dogs…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 1095 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 1100 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 1101 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 1127 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 1151 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 1153 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool plushie if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 1159 "data/maps/Tamatown/scripts.pory"
	.string "You got a Ditto plushie for your room!$"
