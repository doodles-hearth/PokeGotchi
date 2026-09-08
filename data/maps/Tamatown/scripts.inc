Tamatown_MapScripts::
# 6 "data/maps/Tamatown/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, Tamatown_MapScripts_MAP_SCRIPT_ON_LOAD
# 11 "data/maps/Tamatown/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Tamatown_MapScripts_MAP_SCRIPT_ON_LOAD:
# 7 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TREECKO, Tamatown_MapScripts_MAP_SCRIPT_ON_LOAD_1
	return

Tamatown_MapScripts_MAP_SCRIPT_ON_LOAD_1:
# 8 "data/maps/Tamatown/scripts.pory"
	setmetatile 29, 8, METATILE_Tamatown_BrickWall, TRUE
	return

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 12 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_2
Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 17 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_4
	return

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_2:
# 13 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_ICE_CREAM, 33, 20
# 14 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
	goto Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_1

Tamatown_MapScripts_MAP_SCRIPT_ON_TRANSITION_4:
# 18 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
	return


Tamatown_EventScript_House::
# 24 "data/maps/Tamatown/scripts.pory"
	lock
# 25 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_House_Text_0
# 29 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_House_Text_1, Tamatown_EventScript_House_Text_2
# 34 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 35 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_House_2
# 38 "data/maps/Tamatown/scripts.pory"
	closemessage
# 39 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_House_2:
# 36 "data/maps/Tamatown/scripts.pory"
	callnative ReturnToPokegotchiHouse
	return


Tamatown_EventScript_Arcade::
# 44 "data/maps/Tamatown/scripts.pory"
	lock
# 46 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 48 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Arcade_Text_0
# 52 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Arcade_Text_1, Tamatown_EventScript_Arcade_Text_2
# 57 "data/maps/Tamatown/scripts.pory"
	closemessage
# 58 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 60 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 61 "data/maps/Tamatown/scripts.pory"
	delay 32
# 62 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 63 "data/maps/Tamatown/scripts.pory"
	waitstate
# 64 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 65 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 67 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Porygon::
# 71 "data/maps/Tamatown/scripts.pory"
	lockall
# 72 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 73 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Porygon_2
# 86 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_5
# 97 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 99 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 100 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 101 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_4
# 108 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_4:
# 111 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_9
Tamatown_EventScript_Porygon_8:
# 125 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_6, Tamatown_EventScript_Porygon_Text_7
# 130 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 131 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_13
# 159 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 160 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 161 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_9
# 166 "data/maps/Tamatown/scripts.pory"
	closemessage
# 168 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 74 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 75 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_0
# 76 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 77 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
# 81 "data/maps/Tamatown/scripts.pory"
	closemessage
# 82 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Porygon_5:
# 87 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 88 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_1
# 90 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 92 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 93 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_3
	goto Tamatown_EventScript_Porygon_4

Tamatown_EventScript_Porygon_9:
# 112 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_5
# 115 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 116 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 118 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 120 "data/maps/Tamatown/scripts.pory"
	closemessage
# 122 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_13:
# 132 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 133 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 134 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_8
# 137 "data/maps/Tamatown/scripts.pory"
	closemessage
# 139 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 140 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_17
# 142 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_18
# 144 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_19
Tamatown_EventScript_Porygon_15:
# 148 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 150 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 151 "data/maps/Tamatown/scripts.pory"
	delay 32
# 152 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 153 "data/maps/Tamatown/scripts.pory"
	waitstate
# 154 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 155 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 156 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_17:
# 141 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_18:
# 143 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_19:
# 145 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_4
	goto Tamatown_EventScript_Porygon_15


Tamatown_EventScript_Tree::
# 172 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 179 "data/maps/Tamatown/scripts.pory"
	lock
# 180 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 181 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Tangela_2
# 246 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_5
# 271 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_7
# 275 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_8, Tamatown_EventScript_Tangela_Text_9
# 280 "data/maps/Tamatown/scripts.pory"
	closemessage
# 282 "data/maps/Tamatown/scripts.pory"
	delay 24
# 284 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 285 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 286 "data/maps/Tamatown/scripts.pory"
	waitse
# 287 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 289 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_10
# 293 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_11, Tamatown_EventScript_Tangela_Text_12
# 298 "data/maps/Tamatown/scripts.pory"
	closemessage
# 300 "data/maps/Tamatown/scripts.pory"
	delay 24
# 302 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 303 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 304 "data/maps/Tamatown/scripts.pory"
	waitse
# 305 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 307 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_13
# 308 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_14
# 312 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_15, Tamatown_EventScript_Tangela_Text_16
# 317 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 318 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_4
# 319 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 320 "data/maps/Tamatown/scripts.pory"
	waitse
# 322 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 323 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 324 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_17
# 330 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 332 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_4:
# 335 "data/maps/Tamatown/scripts.pory"
	closemessage
# 337 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 182 "data/maps/Tamatown/scripts.pory"
	waitse
# 183 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 184 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Tangela_Movement_0
# 185 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 186 "data/maps/Tamatown/scripts.pory"
	waitse
# 187 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 188 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_1
# 189 "data/maps/Tamatown/scripts.pory"
	waitse
# 190 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 191 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 192 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 193 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_0
# 196 "data/maps/Tamatown/scripts.pory"
	closemessage
# 198 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 199 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_0
# 200 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 201 "data/maps/Tamatown/scripts.pory"
	waitse
# 202 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_1
# 203 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 204 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 205 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 208 "data/maps/Tamatown/scripts.pory"
	closemessage
# 210 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 211 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_1
# 212 "data/maps/Tamatown/scripts.pory"
	facefollowernpc
# 213 "data/maps/Tamatown/scripts.pory"
	waitse
# 214 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 216 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 217 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 218 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_3
# 222 "data/maps/Tamatown/scripts.pory"
	closemessage
# 224 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 225 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Tangela_Text_4
# 228 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 229 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 230 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 231 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_RUG
# 233 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 234 "data/maps/Tamatown/scripts.pory"
	destroyfollowernpc
# 235 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_SKITTY_FOLLOWING
# 236 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_SKITTY
# 237 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
# 238 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 239 "data/maps/Tamatown/scripts.pory"
	delay 32
# 240 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 242 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Tangela_5:
# 247 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Tangela_9
# 264 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 265 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 266 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_6
# 269 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_4

Tamatown_EventScript_Tangela_9:
# 248 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 249 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 250 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 253 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 255 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 256 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Tangela_Movement_2
# 257 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 258 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 260 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Sign::
# 341 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_SkittyFollowing::
# 347 "data/maps/Tamatown/scripts.pory"
	lock
# 348 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 349 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 350 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_SkittyFollowing_Text_0
# 353 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 354 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Skitty::
# 359 "data/maps/Tamatown/scripts.pory"
	lock
# 361 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Skitty_2
# 372 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 373 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 374 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 380 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Skitty_Text_2, Tamatown_EventScript_House_Text_2
# 385 "data/maps/Tamatown/scripts.pory"
	closemessage
# 387 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Skitty_5
# 392 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 393 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 394 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_3
# 397 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 398 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Skitty_4:
# 401 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Skitty_2:
# 362 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 363 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 364 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_0
# 367 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 368 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Skitty_5:
# 388 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 389 "data/maps/Tamatown/scripts.pory"
	setfollowernpc LOCALID_SKITTY, FOLLOWER_NPC_FLAG_ALL, Tamatown_EventScript_SkittyFollowing
# 390 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Skitty_4


Tamatown_EventScript_Trashcan::
# 405 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 413 "data/maps/Tamatown/scripts.pory"
	lock
# 415 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 444 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_4
# 449 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_5, Tamatown_EventScript_TrubbishCan_Text_6
# 454 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_9
# 559 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_16
Tamatown_EventScript_TrubbishCan_8:
# 563 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 566 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 416 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 417 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_TrubbishCan_6
# 436 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 437 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 439 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 418 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 419 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 420 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
# 424 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 425 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Tangela_Movement_0
# 426 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_ENCOUNTER
# 427 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 431 "data/maps/Tamatown/scripts.pory"
	closemessage
# 432 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_TrubbishCan_9:
# 455 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 459 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_8, Tamatown_EventScript_TrubbishCan_Text_9
# 464 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_13
# 500 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_17
# 509 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_16:
# 518 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 519 "data/maps/Tamatown/scripts.pory"
	delay 32
# 521 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
# 524 "data/maps/Tamatown/scripts.pory"
	closemessage
# 526 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 527 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 529 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 530 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 531 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 533 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 534 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 535 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 536 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_12:
# 545 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 546 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 548 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 549 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 550 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 553 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 554 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 555 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 556 "data/maps/Tamatown/scripts.pory"
	closemessage
# 557 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_8

Tamatown_EventScript_TrubbishCan_13:
# 465 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 466 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 467 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 468 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 469 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 470 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 471 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_10
# 472 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 476 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 477 "data/maps/Tamatown/scripts.pory"
	closemessage
# 479 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 480 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_4
# 481 "data/maps/Tamatown/scripts.pory"
	waitse
# 482 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 484 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 485 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 487 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 488 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 489 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 491 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 492 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
	goto Tamatown_EventScript_TrubbishCan_12

Tamatown_EventScript_TrubbishCan_17:
# 501 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_16


Tamatown_EventScript_VendingMachine::
# 570 "data/maps/Tamatown/scripts.pory"
	lock
# 572 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 573 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 576 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_5
Tamatown_EventScript_VendingMachine_3:
# 590 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
Tamatown_EventScript_VendingMachine_1:
# 596 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_16
Tamatown_EventScript_VendingMachine_15:
# 599 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_19
Tamatown_EventScript_VendingMachine_18:
# 602 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_22
Tamatown_EventScript_VendingMachine_21:
# 605 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_25
Tamatown_EventScript_VendingMachine_24:
# 608 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_28
Tamatown_EventScript_VendingMachine_27:
# 611 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_VendingMachine_31
Tamatown_EventScript_VendingMachine_30:
# 614 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 615 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 616 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 618 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_34
# 618 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_34
# 631 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 632 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_39
# 645 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 646 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 648 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 649 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_43
# 663 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_44
# 677 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_45
# 691 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_46
# 705 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_47
# 719 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_48
Tamatown_EventScript_VendingMachine_41:
# 735 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 736 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 737 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 738 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 739 "data/maps/Tamatown/scripts.pory"
	closemessage
# 740 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 742 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 583 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 587 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 578 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_9
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_5:
# 577 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_4
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_8:
# 580 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_12
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_9:
# 579 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_12:
# 581 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_16:
# 597 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 1
	goto Tamatown_EventScript_VendingMachine_15

Tamatown_EventScript_VendingMachine_19:
# 600 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 0
	goto Tamatown_EventScript_VendingMachine_18

Tamatown_EventScript_VendingMachine_22:
# 603 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_21

Tamatown_EventScript_VendingMachine_25:
# 606 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_24

Tamatown_EventScript_VendingMachine_28:
# 609 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_27

Tamatown_EventScript_VendingMachine_31:
# 612 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_30

Tamatown_EventScript_VendingMachine_34:
# 619 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 621 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 622 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 623 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 626 "data/maps/Tamatown/scripts.pory"
	closemessage
# 627 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_39:
# 633 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 635 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 636 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 637 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 640 "data/maps/Tamatown/scripts.pory"
	closemessage
# 641 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_43:
# 650 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 654 "data/maps/Tamatown/scripts.pory"
	closemessage
# 655 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 656 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 657 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 658 "data/maps/Tamatown/scripts.pory"
	waitse
# 659 "data/maps/Tamatown/scripts.pory"
	delay 32
# 660 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 661 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_44:
# 664 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 668 "data/maps/Tamatown/scripts.pory"
	closemessage
# 669 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 670 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 671 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 672 "data/maps/Tamatown/scripts.pory"
	waitse
# 673 "data/maps/Tamatown/scripts.pory"
	delay 32
# 674 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 675 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_45:
# 678 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 682 "data/maps/Tamatown/scripts.pory"
	closemessage
# 683 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 684 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 685 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 686 "data/maps/Tamatown/scripts.pory"
	waitse
# 687 "data/maps/Tamatown/scripts.pory"
	delay 32
# 688 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 689 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_46:
# 692 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 696 "data/maps/Tamatown/scripts.pory"
	closemessage
# 697 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 698 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 699 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 700 "data/maps/Tamatown/scripts.pory"
	waitse
# 701 "data/maps/Tamatown/scripts.pory"
	delay 32
# 702 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 703 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_47:
# 706 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 710 "data/maps/Tamatown/scripts.pory"
	closemessage
# 711 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 712 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 713 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 714 "data/maps/Tamatown/scripts.pory"
	waitse
# 715 "data/maps/Tamatown/scripts.pory"
	delay 32
# 716 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 717 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_48:
# 720 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 724 "data/maps/Tamatown/scripts.pory"
	closemessage
# 725 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 726 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 727 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 728 "data/maps/Tamatown/scripts.pory"
	waitse
# 729 "data/maps/Tamatown/scripts.pory"
	delay 32
# 730 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 731 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_JUICE, 1
	goto Tamatown_EventScript_VendingMachine_41


Tamatown_EventScript_Slowpoke::
# 746 "data/maps/Tamatown/scripts.pory"
	lock
# 748 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 758 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 760 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 761 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 762 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 774 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 779 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 857 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 858 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 859 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_13
Tamatown_EventScript_Slowpoke_5:
# 866 "data/maps/Tamatown/scripts.pory"
	closemessage
# 868 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 749 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 750 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 751 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 780 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 781 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 782 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 787 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 788 "data/maps/Tamatown/scripts.pory"
	delay 32
# 789 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 790 "data/maps/Tamatown/scripts.pory"
	waitstate
# 791 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 792 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 794 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 795 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_RESULT
# 796 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_0x8000
# 798 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 813 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 828 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 844 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 845 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
Tamatown_EventScript_Slowpoke_9:
# 853 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 799 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 800 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 805 "data/maps/Tamatown/scripts.pory"
	closemessage
# 807 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 810 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 811 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 812 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 814 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 815 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_8
# 820 "data/maps/Tamatown/scripts.pory"
	closemessage
# 822 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_9
# 825 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 826 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 827 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 829 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 830 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_10
# 835 "data/maps/Tamatown/scripts.pory"
	closemessage
# 837 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 840 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 841 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 842 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 854 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 872 "data/maps/Tamatown/scripts.pory"
	lock
# 874 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 889 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 890 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 891 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 896 "data/maps/Tamatown/scripts.pory"
	closemessage
# 898 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 902 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 903 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 904 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 905 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 908 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 909 "data/maps/Tamatown/scripts.pory"
	delay 44
# 910 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 911 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 912 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 913 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 914 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 916 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 917 "data/maps/Tamatown/scripts.pory"
	delay 48
# 919 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 920 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 923 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 875 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 876 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 877 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 878 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 879 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 882 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 883 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 884 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 885 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 886 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 927 "data/maps/Tamatown/scripts.pory"
	lock
# 928 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 936 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 937 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 938 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 944 "data/maps/Tamatown/scripts.pory"
	closemessage
# 946 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 947 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 950 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 951 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 952 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 953 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 954 "data/maps/Tamatown/scripts.pory"
	closemessage
# 956 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 959 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 929 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 930 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 931 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 934 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 963 "data/maps/Tamatown/scripts.pory"
	lock
# 965 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 971 "data/maps/Tamatown/scripts.pory"
	closemessage
# 973 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 977 "data/maps/Tamatown/scripts.pory"
	lock
# 979 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 982 "data/maps/Tamatown/scripts.pory"
	closemessage
# 984 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 988 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 991 "data/maps/Tamatown/scripts.pory"
	lock
# 993 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 998 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 1002 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1004 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 1024 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 989 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 1005 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 1006 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 1007 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 1008 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 1009 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 1010 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 1011 "data/maps/Tamatown/scripts.pory"
	waitstate
# 1012 "data/maps/Tamatown/scripts.pory"
	waitse
# 1014 "data/maps/Tamatown/scripts.pory"
	delay 48
# 1016 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 1019 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1021 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 1029 "data/maps/Tamatown/scripts.pory"
	lock
# 1030 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 1031 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Torchic_2
# 1043 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_5
# 1050 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_6
# 1070 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 1071 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1072 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_5
# 1075 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_4:
# 1078 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 1032 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1033 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_ENCOUNTER
# 1034 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 1038 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1039 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Torchic_5:
# 1044 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 1045 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1046 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 1049 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_4

Tamatown_EventScript_Torchic_6:
# 1051 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 1052 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1053 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_3
# 1058 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1060 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_4
# 1063 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1064 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1065 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1066 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1067 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_4


Tamatown_EventScript_StepInPoop::
# 1082 "data/maps/Tamatown/scripts.pory"
	lock
# 1083 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 1084 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 1088 "data/maps/Tamatown/scripts.pory"
	lock
# 1089 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 1092 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1093 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 1097 "data/maps/Tamatown/scripts.pory"
	lock
# 1098 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1099 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1100 "data/maps/Tamatown/scripts.pory"
	waitse
# 1101 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 1102 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 1106 "data/maps/Tamatown/scripts.pory"
	lock
# 1108 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 1115 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 1120 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 1124 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1126 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1128 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1202 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 1109 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1110 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1111 "data/maps/Tamatown/scripts.pory"
	waitse
# 1112 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1113 "data/maps/Tamatown/scripts.pory"
	delay 1
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 1129 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 1133 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 1137 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 1142 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 1147 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 1150 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1152 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1153 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_DITTO, Tamatown_EventScript_Tangela_Movement_0
# 1154 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1155 "data/maps/Tamatown/scripts.pory"
	waitse
# 1156 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 1157 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_DITTO, Tamatown_EventScript_DittoLamppost_Movement_4
# 1158 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1159 "data/maps/Tamatown/scripts.pory"
	waitse
# 1161 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1167 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1169 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1170 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 1171 "data/maps/Tamatown/scripts.pory"
	waitse
# 1172 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1174 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1176 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1177 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 1178 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 1182 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1184 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1187 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1188 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1189 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1190 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1191 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1193 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1195 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1197 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1198 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 1130 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 1134 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 1138 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


Tamatown_EventScript_TreeckoPrint::
# 1206 "data/maps/Tamatown/scripts.pory"
	lock
# 1208 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_0
# 1212 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TreeckoPrint_Text_1, Tamatown_EventScript_TreeckoPrint_Text_2
# 1216 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1218 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TreeckoPrint_2
# 1236 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_4
# 1239 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TreeckoPrint_1:
# 1242 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TreeckoPrint_2:
# 1219 "data/maps/Tamatown/scripts.pory"
	playse SE_CONTEST_CONDITION_LOSE
# 1220 "data/maps/Tamatown/scripts.pory"
	setmetatile 29, 8, METATILE_Tamatown_BrickWall, TRUE
# 1221 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 1222 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 1223 "data/maps/Tamatown/scripts.pory"
	waitse
# 1224 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1226 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TreeckoPrint_Text_3
# 1229 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1230 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1231 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1232 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1233 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TREECKO
# 1234 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_TreeckoPrint_1


Tamatown_EventScript_Hypno::
# 1246 "data/maps/Tamatown/scripts.pory"
	lock
# 1247 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_BED, Tamatown_EventScript_Hypno_2
# 1255 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1256 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_3
# 1257 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_NORMAL
# 1258 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_2
# 1265 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 1267 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Hypno_Text_3, Tamatown_EventScript_Hypno_Text_4
# 1271 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1273 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Hypno_5
# 1297 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1298 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_WEAK
# 1299 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_7
# 1302 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Hypno_1:
# 1306 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Hypno_2:
# 1248 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1249 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_NORMAL
# 1250 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_1
# 1253 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Hypno_1

Tamatown_EventScript_Hypno_5:
# 1274 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 1275 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 50
	goto_if_lt Tamatown_EventScript_Hypno_8
# 1283 "data/maps/Tamatown/scripts.pory"
	removecoins 50
# 1284 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 1285 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1286 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 1287 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_HIGH_PITCH
# 1288 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_6
# 1292 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1294 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_BED
	goto Tamatown_EventScript_Hypno_1

Tamatown_EventScript_Hypno_8:
# 1276 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1277 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_WEAK
# 1278 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_5
# 1281 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Hypno_1


Tamatown_EventScript_Shuckle::
# 1310 "data/maps/Tamatown/scripts.pory"
	lock
# 1312 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_Shuckle_2
# 1323 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1324 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1325 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_2
# 1329 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Shuckle_Text_3, Tamatown_EventScript_Shuckle_Text_4
# 1334 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Shuckle_5
# 1368 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_FAINT
# 1369 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1370 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_7
# 1373 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Shuckle_4:
# 1376 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Shuckle_2:
# 1313 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1314 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1315 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_1
# 1318 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1319 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Shuckle_5:
# 1335 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_ENCOUNTER
# 1336 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Shuckle_Movement_0
# 1337 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_5
# 1340 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 1341 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1342 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1344 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1346 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1347 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1348 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_6
# 1352 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 1353 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1354 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1356 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 1359 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1360 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1361 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1362 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1363 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE
# 1364 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_JUICE, 1
# 1365 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Shuckle_4


Tamatown_EventScript_TrashcanPoster::
# 1380 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_MUDKIP, Tamatown_EventScript_TrashcanPoster_2
Tamatown_EventScript_TrashcanPoster_1:
# 1384 "data/maps/Tamatown/scripts.pory"
	lock
# 1385 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrashcanPoster_Text_0
# 1388 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1389 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1390 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1391 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1392 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_MUDKIP
# 1393 "data/maps/Tamatown/scripts.pory"
	closemessage
	return

Tamatown_EventScript_TrashcanPoster_2:
# 1381 "data/maps/Tamatown/scripts.pory"
	goto Tamatown_EventScript_Trashcan
	goto Tamatown_EventScript_TrashcanPoster_1


# 75 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 75 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 88 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 88 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 141 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 141 "data/maps/Tamatown/scripts.pory"
	walk_right
# 141 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 143 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 143 "data/maps/Tamatown/scripts.pory"
	walk_left
# 143 "data/maps/Tamatown/scripts.pory"
	walk_down
# 143 "data/maps/Tamatown/scripts.pory"
	walk_down
# 143 "data/maps/Tamatown/scripts.pory"
	walk_right
# 143 "data/maps/Tamatown/scripts.pory"
	walk_right
# 143 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 145 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_4:
# 145 "data/maps/Tamatown/scripts.pory"
	walk_down
# 145 "data/maps/Tamatown/scripts.pory"
	walk_right
# 145 "data/maps/Tamatown/scripts.pory"
	walk_right
# 145 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 184 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 184 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 202 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 202 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
# 202 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 256 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_2:
# 256 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 256 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 285 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_3:
# 285 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 318 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_4:
# 318 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
# 318 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 488 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 488 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 488 "data/maps/Tamatown/scripts.pory"
	delay_16
# 488 "data/maps/Tamatown/scripts.pory"
	delay_16
# 488 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 501 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 502 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 503 "data/maps/Tamatown/scripts.pory"
	delay_16
# 503 "data/maps/Tamatown/scripts.pory"
	delay_16
# 504 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 505 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 506 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 509 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 510 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 511 "data/maps/Tamatown/scripts.pory"
	delay_16
# 511 "data/maps/Tamatown/scripts.pory"
	delay_16
# 512 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 513 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 514 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 534 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 534 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 898 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 899 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 905 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 906 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 908 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 908 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 1130 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 1131 "data/maps/Tamatown/scripts.pory"
	walk_left
# 1131 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1131 "data/maps/Tamatown/scripts.pory"
	walk_right
# 1131 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1134 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 1135 "data/maps/Tamatown/scripts.pory"
	walk_right
# 1135 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1135 "data/maps/Tamatown/scripts.pory"
	walk_left
# 1135 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1138 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 1139 "data/maps/Tamatown/scripts.pory"
	walk_down
# 1139 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1139 "data/maps/Tamatown/scripts.pory"
	walk_up
# 1139 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1142 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 1143 "data/maps/Tamatown/scripts.pory"
	walk_up
# 1143 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1143 "data/maps/Tamatown/scripts.pory"
	walk_down
# 1143 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1157 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 1157 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1157 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 1157 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1336 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Shuckle_Movement_0:
# 1336 "data/maps/Tamatown/scripts.pory"
	shake_vertical
# 1336 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

Tamatown_EventScript_House_Text_0:
# 26 "data/maps/Tamatown/scripts.pory"
	.string "Go home?$"

Tamatown_EventScript_House_Text_1:
# 30 "data/maps/Tamatown/scripts.pory"
	.string "Yes$"

Tamatown_EventScript_House_Text_2:
# 31 "data/maps/Tamatown/scripts.pory"
	.string "No$"

Tamatown_EventScript_Arcade_Text_0:
# 49 "data/maps/Tamatown/scripts.pory"
	.string "Play {COLOR RED}Pachinko{COLOR DARK_GRAY}?\p$"

Tamatown_EventScript_Arcade_Text_1:
# 53 "data/maps/Tamatown/scripts.pory"
	.string "Play$"

Tamatown_EventScript_Arcade_Text_2:
# 54 "data/maps/Tamatown/scripts.pory"
	.string "Don't play$"

Tamatown_EventScript_Porygon_Text_0:
# 74 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Porygon_Text_1:
# 78 "data/maps/Tamatown/scripts.pory"
	.string "Porygon is a nerd!\nI don't want a virtual ball of yarn!$"

Tamatown_EventScript_Porygon_Text_2:
# 92 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_3:
# 94 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_4:
# 102 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you {COLOR RED}15 coins{COLOR DARK_GRAY} everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_5:
# 113 "data/maps/Tamatown/scripts.pory"
	.string "You got {COLOR RED}15 coins{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Porygon_Text_6:
# 126 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_7:
# 127 "data/maps/Tamatown/scripts.pory"
	.string "Nah$"

Tamatown_EventScript_Porygon_Text_8:
# 135 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_9:
# 162 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 173 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 194 "data/maps/Tamatown/scripts.pory"
	.string "A ball! A ball of yarn! Meow!!$"

Tamatown_EventScript_Tangela_Text_1:
# 204 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_2:
# 206 "data/maps/Tamatown/scripts.pory"
	.string "I-I'm not a ball of yarn!\nI'm a tree!$"

Tamatown_EventScript_Tangela_Text_3:
# 219 "data/maps/Tamatown/scripts.pory"
	.string "Thank you, odd little bug.\p"
	.string "Here! one of my crafting\nprojects in return!$"

Tamatown_EventScript_Tangela_Text_4:
# 226 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute {COLOR RED}Crochet Rug{COLOR DARK_GRAY} for your\nroom!$"

Tamatown_EventScript_Tangela_Text_5:
# 251 "data/maps/Tamatown/scripts.pory"
	.string "It's hard to hide in plain sight\nwith this one playing with my vines…$"

Tamatown_EventScript_Tangela_Text_6:
# 267 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_7:
# 272 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_8:
# 276 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_9:
# 277 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_10:
# 290 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_11:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_12:
# 295 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_13:
# 307 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_14:
# 309 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_15:
# 313 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_16:
# 314 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_17:
# 325 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 342 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_SkittyFollowing_Text_0:
# 351 "data/maps/Tamatown/scripts.pory"
	.string "I want a ball of yarn!\nMeow!$"

Tamatown_EventScript_Skitty_Text_0:
# 365 "data/maps/Tamatown/scripts.pory"
	.string "Meow meow meow!\nYarn yarn yarn!$"

Tamatown_EventScript_Skitty_Text_1:
# 375 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "You!{PAUSE 8} Bug!{PAUSE 8} Find me more yarn!\n"
	.string "Take me with you!$"

Tamatown_EventScript_Skitty_Text_2:
# 381 "data/maps/Tamatown/scripts.pory"
	.string "Alright$"

Tamatown_EventScript_Skitty_Text_3:
# 395 "data/maps/Tamatown/scripts.pory"
	.string "Alright… Meow…$"

Tamatown_EventScript_Trashcan_Text_0:
# 406 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 418 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 421 "data/maps/Tamatown/scripts.pory"
	.string "Is this cat edible?$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 428 "data/maps/Tamatown/scripts.pory"
	.string "Fshhhh!!! Do not eat cat!!$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 440 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 445 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 450 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 451 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 456 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 460 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 461 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 471 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 473 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 493 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 522 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 537 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_15:
# 551 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Doughnut{COLOR DARK_GRAY}!$"

Tamatown_EventScript_TrubbishCan_Text_16:
# 560 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 573 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 584 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have much right now, but I'm\noften restocked!$"

Tamatown_EventScript_VendingMachine_Text_2:
# 591 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 597 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 600 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 603 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 606 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 609 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 612 "data/maps/Tamatown/scripts.pory"
	.string "Shuckle Juice{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 614 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 624 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 638 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 651 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Hot Dog{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 660 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Hot Dog{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 665 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}PokéBlock{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 674 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}PokéBlock{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 679 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Sunny Side Up{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 688 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Sunny Side Up{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 693 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Doughnut{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 707 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Ice Cream{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 716 "data/maps/Tamatown/scripts.pory"
	.string "You got an {COLOR RED}Ice Cream{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 721 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Shuckle Juice{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 730 "data/maps/Tamatown/scripts.pory"
	.string "You got a box of {COLOR RED}Shuckle Juice{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 750 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 752 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us out\ntodaaaaay?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 763 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 775 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 776 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 783 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 801 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1} happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 808 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 {COLOR RED}Hot Dogs{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 816 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lYou did your beeeest…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_9:
# 823 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 {COLOR RED}Hot Dogs{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_10:
# 831 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lOoookaaaaay…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_11:
# 838 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 {COLOR RED}Hot Dog{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 846 "data/maps/Tamatown/scripts.pory"
	.string "You served {STR_VAR_1}\ncuuuustomers…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\p"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 860 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 880 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 890 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 892 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 929 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 932 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 939 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 948 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Lucky Egg{COLOR DARK_GRAY}!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 966 "data/maps/Tamatown/scripts.pory"
	.string "Use this {COLOR RED}letterbox{COLOR DARK_GRAY} to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 980 "data/maps/Tamatown/scripts.pory"
	.string "It's a {COLOR RED}fire hydrant{COLOR DARK_GRAY}.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 994 "data/maps/Tamatown/scripts.pory"
	.string "It's a {COLOR RED}fire hydrant{COLOR DARK_GRAY}.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 999 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 1000 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 1017 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 1032 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 1035 "data/maps/Tamatown/scripts.pory"
	.string "I taut I taw a puddy-tat!\nG-get it away from me!$"

Tamatown_EventScript_Torchic_Text_2:
# 1047 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_3:
# 1054 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_4:
# 1061 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Poster{COLOR DARK_GRAY} for your room!$"

Tamatown_EventScript_Torchic_Text_5:
# 1073 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 1090 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, {COLOR RED}Hot Dogs{COLOR DARK_GRAY}…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 1116 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 1121 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 1122 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 1148 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 1177 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 1179 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool {COLOR RED}Plushie{COLOR DARK_GRAY} if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 1185 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute {COLOR RED}Plushie{COLOR DARK_GRAY} for your room!$"

Tamatown_EventScript_TreeckoPrint_Text_0:
# 1209 "data/maps/Tamatown/scripts.pory"
	.string "What a pretty {COLOR RED}Poster{COLOR DARK_GRAY}!$"

Tamatown_EventScript_TreeckoPrint_Text_1:
# 1213 "data/maps/Tamatown/scripts.pory"
	.string "Grab it$"

Tamatown_EventScript_TreeckoPrint_Text_2:
# 1214 "data/maps/Tamatown/scripts.pory"
	.string "Leave it$"

Tamatown_EventScript_TreeckoPrint_Text_3:
# 1227 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Green Poster{COLOR DARK_GRAY} for your\nroom!$"

Tamatown_EventScript_TreeckoPrint_Text_4:
# 1237 "data/maps/Tamatown/scripts.pory"
	.string "Right, what if the cops see you?$"

Tamatown_EventScript_Hypno_Text_0:
# 1248 "data/maps/Tamatown/scripts.pory"
	.string "Hypno$"

Tamatown_EventScript_Hypno_Text_1:
# 1251 "data/maps/Tamatown/scripts.pory"
	.string "Has your sleep quality improved?{PAUSE 8}\nHmmmm…{PAUSE 8} Yessss…$"

Tamatown_EventScript_Hypno_Text_2:
# 1259 "data/maps/Tamatown/scripts.pory"
	.string "Well,{PAUSE 8} hello there,{PAUSE 8} little child…\nDo you sleep well, mmyes?\p"
	.string "I can sense a…{PAUSE 8} deep…{PAUSE 8} fatigue, yes…\p"
	.string "I can sell you the secret to a better\nsleep…\p"
	.string "Only 50 of those {COLOR RED}Pachinko coins{COLOR DARK_GRAY},{PAUSE 8}\nhmmm,{PAUSE 8} yes…$"

Tamatown_EventScript_Hypno_Text_3:
# 1268 "data/maps/Tamatown/scripts.pory"
	.string "Gimme!$"

Tamatown_EventScript_Hypno_Text_4:
# 1269 "data/maps/Tamatown/scripts.pory"
	.string "Too pricey$"

Tamatown_EventScript_Hypno_Text_5:
# 1279 "data/maps/Tamatown/scripts.pory"
	.string "Come back with more of those sweet,{PAUSE 8}\nscrumptious coins…$"

Tamatown_EventScript_Hypno_Text_6:
# 1289 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, yes!{PAUSE 8}Love it…{PAUSE 8}\nGive…\p"
	.string "Go back home…{PAUSE 8}\nIt is waiting for you already…$"

Tamatown_EventScript_Hypno_Text_7:
# 1300 "data/maps/Tamatown/scripts.pory"
	.string "Maybe you don't{PAUSE 8} deserve better\nsleep…$"

Tamatown_EventScript_Shuckle_Text_0:
# 1314 "data/maps/Tamatown/scripts.pory"
	.string "Shuckle$"

Tamatown_EventScript_Shuckle_Text_1:
# 1316 "data/maps/Tamatown/scripts.pory"
	.string "Is it weird for me to drink my own\njuice?\lHmmm…$"

Tamatown_EventScript_Shuckle_Text_2:
# 1326 "data/maps/Tamatown/scripts.pory"
	.string "Yo! Quick! Shake me!!$"

Tamatown_EventScript_Shuckle_Text_3:
# 1330 "data/maps/Tamatown/scripts.pory"
	.string "Shake!$"

Tamatown_EventScript_Shuckle_Text_4:
# 1331 "data/maps/Tamatown/scripts.pory"
	.string "Why??$"

Tamatown_EventScript_Shuckle_Text_5:
# 1338 "data/maps/Tamatown/scripts.pory"
	.string "(Shake shake shake shake shake)$"

Tamatown_EventScript_Shuckle_Text_6:
# 1349 "data/maps/Tamatown/scripts.pory"
	.string "… … … … …\p"
	.string "Aaaaand it's ready! Here, have some!$"

Tamatown_EventScript_Shuckle_Text_7:
# 1371 "data/maps/Tamatown/scripts.pory"
	.string "Disappointment!… …$"

Tamatown_EventScript_TrashcanPoster_Text_0:
# 1386 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Blue Poster{COLOR DARK_GRAY} for your\nroom!$"
