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
# 245 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_5
# 270 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_7
# 274 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_8, Tamatown_EventScript_Tangela_Text_9
# 279 "data/maps/Tamatown/scripts.pory"
	closemessage
# 281 "data/maps/Tamatown/scripts.pory"
	delay 24
# 283 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 284 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 285 "data/maps/Tamatown/scripts.pory"
	waitse
# 286 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 288 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_10
# 292 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_11, Tamatown_EventScript_Tangela_Text_12
# 297 "data/maps/Tamatown/scripts.pory"
	closemessage
# 299 "data/maps/Tamatown/scripts.pory"
	delay 24
# 301 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 302 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 303 "data/maps/Tamatown/scripts.pory"
	waitse
# 304 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 306 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_13
# 307 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_14
# 311 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_15, Tamatown_EventScript_Tangela_Text_16
# 316 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 317 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_4
# 318 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 319 "data/maps/Tamatown/scripts.pory"
	waitse
# 321 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 322 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 323 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_17
# 329 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 331 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_4:
# 334 "data/maps/Tamatown/scripts.pory"
	closemessage
# 336 "data/maps/Tamatown/scripts.pory"
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
	setflag POKEGOTCHI_FLAG_FRNTR_RUG
# 232 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 233 "data/maps/Tamatown/scripts.pory"
	destroyfollowernpc
# 234 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_SKITTY_FOLLOWING
# 235 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_SKITTY
# 236 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
# 237 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 238 "data/maps/Tamatown/scripts.pory"
	delay 32
# 239 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 241 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Tangela_5:
# 246 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Tangela_9
# 263 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 264 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 265 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_6
# 268 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_4

Tamatown_EventScript_Tangela_9:
# 247 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 248 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 249 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 252 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 254 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 255 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Tangela_Movement_2
# 256 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 257 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 259 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Sign::
# 340 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_SkittyFollowing::
# 346 "data/maps/Tamatown/scripts.pory"
	lock
# 347 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 348 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 349 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_SkittyFollowing_Text_0
# 352 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 353 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Skitty::
# 358 "data/maps/Tamatown/scripts.pory"
	lock
# 360 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Skitty_2
# 371 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 372 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 373 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 379 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Skitty_Text_2, Tamatown_EventScript_House_Text_2
# 384 "data/maps/Tamatown/scripts.pory"
	closemessage
# 386 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Skitty_5
# 391 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 392 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 393 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_3
# 396 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 397 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Skitty_4:
# 400 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Skitty_2:
# 361 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 362 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 363 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_0
# 366 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 367 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Skitty_5:
# 387 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 388 "data/maps/Tamatown/scripts.pory"
	setfollowernpc LOCALID_SKITTY, FOLLOWER_NPC_FLAG_ALL, Tamatown_EventScript_SkittyFollowing
# 389 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Skitty_4


Tamatown_EventScript_Trashcan::
# 404 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 412 "data/maps/Tamatown/scripts.pory"
	lock
# 414 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 443 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_4
# 448 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_5, Tamatown_EventScript_TrubbishCan_Text_6
# 453 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_9
# 557 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_16
Tamatown_EventScript_TrubbishCan_8:
# 561 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 564 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 415 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 416 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_TrubbishCan_6
# 435 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 436 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 438 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 417 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 418 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 419 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
# 423 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 424 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Tangela_Movement_0
# 425 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_ENCOUNTER
# 426 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 430 "data/maps/Tamatown/scripts.pory"
	closemessage
# 431 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_TrubbishCan_9:
# 454 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 458 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_8, Tamatown_EventScript_TrubbishCan_Text_9
# 463 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_13
# 499 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_17
# 508 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_16:
# 517 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 518 "data/maps/Tamatown/scripts.pory"
	delay 32
# 520 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
# 523 "data/maps/Tamatown/scripts.pory"
	closemessage
# 525 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 526 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 528 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 529 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 530 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 532 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 533 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 534 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 535 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_12:
# 544 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 545 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 547 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 548 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 549 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 552 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 553 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 554 "data/maps/Tamatown/scripts.pory"
	closemessage
# 555 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_8

Tamatown_EventScript_TrubbishCan_13:
# 464 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 465 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 466 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 467 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 468 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 469 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 470 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_10
# 471 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 475 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 476 "data/maps/Tamatown/scripts.pory"
	closemessage
# 478 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 479 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_4
# 480 "data/maps/Tamatown/scripts.pory"
	waitse
# 481 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 483 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 484 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 486 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 487 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 488 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 490 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 491 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
	goto Tamatown_EventScript_TrubbishCan_12

Tamatown_EventScript_TrubbishCan_17:
# 500 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_16


Tamatown_EventScript_VendingMachine::
# 568 "data/maps/Tamatown/scripts.pory"
	lock
# 570 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 571 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 574 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_4
Tamatown_EventScript_VendingMachine_1:
# 590 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
# 595 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_15
Tamatown_EventScript_VendingMachine_14:
# 598 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_18
Tamatown_EventScript_VendingMachine_17:
# 601 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_21
Tamatown_EventScript_VendingMachine_20:
# 604 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_24
Tamatown_EventScript_VendingMachine_23:
# 607 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_27
Tamatown_EventScript_VendingMachine_26:
# 610 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_30
Tamatown_EventScript_VendingMachine_29:
# 613 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 614 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 615 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 10, FALSE, 0, NULL
# 617 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 619 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 619 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_33
# 630 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 631 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_38
# 642 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 643 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 645 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 646 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_42
# 658 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_43
# 670 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_44
# 682 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_45
# 694 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_46
# 706 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_47
Tamatown_EventScript_VendingMachine_40:
# 720 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 721 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 722 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 723 "data/maps/Tamatown/scripts.pory"
	closemessage
# 725 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 581 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 585 "data/maps/Tamatown/scripts.pory"
	closemessage
# 586 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_3:
# 576 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 575 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_3
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_7:
# 578 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_11
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_8:
# 577 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_7
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_11:
# 579 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_3, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_15:
# 596 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 0
	goto Tamatown_EventScript_VendingMachine_14

Tamatown_EventScript_VendingMachine_18:
# 599 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 1
	goto Tamatown_EventScript_VendingMachine_17

Tamatown_EventScript_VendingMachine_21:
# 602 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_20

Tamatown_EventScript_VendingMachine_24:
# 605 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_23

Tamatown_EventScript_VendingMachine_27:
# 608 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_26

Tamatown_EventScript_VendingMachine_30:
# 611 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_29

Tamatown_EventScript_VendingMachine_33:
# 620 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 621 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 622 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 625 "data/maps/Tamatown/scripts.pory"
	closemessage
# 626 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_38:
# 632 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 633 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 634 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 637 "data/maps/Tamatown/scripts.pory"
	closemessage
# 638 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_42:
# 647 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 651 "data/maps/Tamatown/scripts.pory"
	closemessage
# 652 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 653 "data/maps/Tamatown/scripts.pory"
	waitse
# 654 "data/maps/Tamatown/scripts.pory"
	delay 32
# 655 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 656 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_43:
# 659 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 663 "data/maps/Tamatown/scripts.pory"
	closemessage
# 664 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 665 "data/maps/Tamatown/scripts.pory"
	waitse
# 666 "data/maps/Tamatown/scripts.pory"
	delay 32
# 667 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 668 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_44:
# 671 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 675 "data/maps/Tamatown/scripts.pory"
	closemessage
# 676 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 677 "data/maps/Tamatown/scripts.pory"
	waitse
# 678 "data/maps/Tamatown/scripts.pory"
	delay 32
# 679 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 680 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_45:
# 683 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 687 "data/maps/Tamatown/scripts.pory"
	closemessage
# 688 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 689 "data/maps/Tamatown/scripts.pory"
	waitse
# 690 "data/maps/Tamatown/scripts.pory"
	delay 32
# 691 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 692 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_46:
# 695 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 699 "data/maps/Tamatown/scripts.pory"
	closemessage
# 700 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 701 "data/maps/Tamatown/scripts.pory"
	waitse
# 702 "data/maps/Tamatown/scripts.pory"
	delay 32
# 703 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 704 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_40

Tamatown_EventScript_VendingMachine_47:
# 707 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 711 "data/maps/Tamatown/scripts.pory"
	closemessage
# 712 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 713 "data/maps/Tamatown/scripts.pory"
	waitse
# 714 "data/maps/Tamatown/scripts.pory"
	delay 32
# 715 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 716 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_SNACK_4, 1
	goto Tamatown_EventScript_VendingMachine_40


Tamatown_EventScript_Slowpoke::
# 729 "data/maps/Tamatown/scripts.pory"
	lock
# 731 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 741 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 743 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 744 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 745 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 757 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 762 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 840 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 841 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 842 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_13
Tamatown_EventScript_Slowpoke_5:
# 849 "data/maps/Tamatown/scripts.pory"
	closemessage
# 851 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 732 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 733 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 734 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 763 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 764 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 765 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 770 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 771 "data/maps/Tamatown/scripts.pory"
	delay 32
# 772 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 773 "data/maps/Tamatown/scripts.pory"
	waitstate
# 774 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 775 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 777 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 778 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_RESULT
# 779 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_0x8000
# 781 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 796 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 811 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 827 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 828 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
Tamatown_EventScript_Slowpoke_9:
# 836 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 782 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 783 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 788 "data/maps/Tamatown/scripts.pory"
	closemessage
# 790 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 793 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 794 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 795 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 797 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 798 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_8
# 803 "data/maps/Tamatown/scripts.pory"
	closemessage
# 805 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_9
# 808 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 809 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 810 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 812 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 813 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_10
# 818 "data/maps/Tamatown/scripts.pory"
	closemessage
# 820 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 823 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 824 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 825 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 837 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 855 "data/maps/Tamatown/scripts.pory"
	lock
# 857 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 871 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 872 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 873 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 878 "data/maps/Tamatown/scripts.pory"
	closemessage
# 880 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 884 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 885 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 886 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 887 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 890 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 891 "data/maps/Tamatown/scripts.pory"
	delay 44
# 892 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 893 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 894 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 895 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 896 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 898 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 899 "data/maps/Tamatown/scripts.pory"
	delay 48
# 901 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 902 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 905 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 858 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 859 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 860 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 861 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 862 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 865 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 866 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 867 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 868 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 909 "data/maps/Tamatown/scripts.pory"
	lock
# 910 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 918 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 919 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 920 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 926 "data/maps/Tamatown/scripts.pory"
	closemessage
# 928 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 929 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 932 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 933 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 934 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 935 "data/maps/Tamatown/scripts.pory"
	closemessage
# 937 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 940 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 911 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 912 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 913 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 916 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 944 "data/maps/Tamatown/scripts.pory"
	lock
# 946 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 952 "data/maps/Tamatown/scripts.pory"
	closemessage
# 954 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 958 "data/maps/Tamatown/scripts.pory"
	lock
# 960 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 963 "data/maps/Tamatown/scripts.pory"
	closemessage
# 965 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 969 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 972 "data/maps/Tamatown/scripts.pory"
	lock
# 974 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 979 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 983 "data/maps/Tamatown/scripts.pory"
	closemessage
# 985 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 1005 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 970 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 986 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 987 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 988 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 989 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 990 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 991 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 992 "data/maps/Tamatown/scripts.pory"
	waitstate
# 993 "data/maps/Tamatown/scripts.pory"
	waitse
# 995 "data/maps/Tamatown/scripts.pory"
	delay 48
# 997 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 1000 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1002 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 1010 "data/maps/Tamatown/scripts.pory"
	lock
# 1011 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 1012 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Torchic_2
# 1024 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_5
# 1031 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_6
# 1050 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 1051 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1052 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_5
# 1055 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_4:
# 1058 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 1013 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1014 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_ENCOUNTER
# 1015 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 1019 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1020 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Torchic_5:
# 1025 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 1026 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1027 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 1030 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_4

Tamatown_EventScript_Torchic_6:
# 1032 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 1033 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1034 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_3
# 1039 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1041 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_4
# 1044 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1045 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1046 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1047 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_4


Tamatown_EventScript_StepInPoop::
# 1062 "data/maps/Tamatown/scripts.pory"
	lock
# 1063 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 1064 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 1068 "data/maps/Tamatown/scripts.pory"
	lock
# 1069 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 1072 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1073 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 1077 "data/maps/Tamatown/scripts.pory"
	lock
# 1078 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1079 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1080 "data/maps/Tamatown/scripts.pory"
	waitse
# 1081 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 1082 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 1086 "data/maps/Tamatown/scripts.pory"
	lock
# 1088 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 1095 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 1100 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 1104 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1106 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1108 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1176 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 1089 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1090 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1091 "data/maps/Tamatown/scripts.pory"
	waitse
# 1092 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1093 "data/maps/Tamatown/scripts.pory"
	delay 1
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 1109 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 1113 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 1117 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 1122 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 1127 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 1130 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1132 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1133 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 1134 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1135 "data/maps/Tamatown/scripts.pory"
	waitse
# 1136 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 1137 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_DittoLamppost_Movement_4
# 1138 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1139 "data/maps/Tamatown/scripts.pory"
	waitse
# 1141 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1142 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1144 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1145 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 1146 "data/maps/Tamatown/scripts.pory"
	waitse
# 1147 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1149 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1151 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1152 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 1153 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 1157 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1159 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1162 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1163 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1164 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1165 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1167 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1169 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1171 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1172 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 1110 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 1114 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 1118 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


Tamatown_EventScript_TreeckoPrint::
# 1180 "data/maps/Tamatown/scripts.pory"
	lock
# 1182 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_0
# 1186 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TreeckoPrint_Text_1, Tamatown_EventScript_TreeckoPrint_Text_2
# 1190 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1192 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TreeckoPrint_2
# 1209 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_3
# 1212 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TreeckoPrint_1:
# 1215 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TreeckoPrint_2:
# 1193 "data/maps/Tamatown/scripts.pory"
	playse SE_CONTEST_CONDITION_LOSE
# 1194 "data/maps/Tamatown/scripts.pory"
	setmetatile 29, 8, METATILE_Tamatown_BrickWall, TRUE
# 1195 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 1196 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 1197 "data/maps/Tamatown/scripts.pory"
	waitse
# 1198 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1200 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_4
# 1203 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1204 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1205 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1206 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TREECKO
# 1207 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_TreeckoPrint_1


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

# 255 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_2:
# 255 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 255 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 284 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_3:
# 284 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 317 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_4:
# 317 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
# 317 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 487 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 487 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 487 "data/maps/Tamatown/scripts.pory"
	delay_16
# 487 "data/maps/Tamatown/scripts.pory"
	delay_16
# 487 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 500 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 501 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 502 "data/maps/Tamatown/scripts.pory"
	delay_16
# 502 "data/maps/Tamatown/scripts.pory"
	delay_16
# 503 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 504 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 505 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 508 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 509 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 510 "data/maps/Tamatown/scripts.pory"
	delay_16
# 510 "data/maps/Tamatown/scripts.pory"
	delay_16
# 511 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 512 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 513 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 533 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 533 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 880 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 881 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 887 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 888 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 890 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 890 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 1110 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 1111 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1111 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1111 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1111 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1114 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 1115 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 1115 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1115 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 1115 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1118 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 1119 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1119 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1119 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1119 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1122 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 1123 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 1123 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1123 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 1123 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1137 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 1137 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1137 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 1137 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
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
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_5:
# 113 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_6:
# 126 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_7:
# 127 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

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
	.string "You got a cute crochet rug for your\nroom!$"

Tamatown_EventScript_Tangela_Text_5:
# 250 "data/maps/Tamatown/scripts.pory"
	.string "It's hard to hide in plain sight\nwith this one playing with my vines…$"

Tamatown_EventScript_Tangela_Text_6:
# 266 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_7:
# 271 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_8:
# 275 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_9:
# 276 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_10:
# 289 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_11:
# 293 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_12:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_13:
# 306 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_14:
# 308 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_15:
# 312 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_16:
# 313 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_17:
# 324 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 341 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_SkittyFollowing_Text_0:
# 350 "data/maps/Tamatown/scripts.pory"
	.string "I want a ball of yarn!\nMeow!$"

Tamatown_EventScript_Skitty_Text_0:
# 364 "data/maps/Tamatown/scripts.pory"
	.string "Meow meow meow!\nYarn yarn yarn!$"

Tamatown_EventScript_Skitty_Text_1:
# 374 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "You!{PAUSE 8} Bug!{PAUSE 8} Find me more yarn!\n"
	.string "Take me with you!$"

Tamatown_EventScript_Skitty_Text_2:
# 380 "data/maps/Tamatown/scripts.pory"
	.string "Alright$"

Tamatown_EventScript_Skitty_Text_3:
# 394 "data/maps/Tamatown/scripts.pory"
	.string "Alright… Meow…$"

Tamatown_EventScript_Trashcan_Text_0:
# 405 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 417 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 420 "data/maps/Tamatown/scripts.pory"
	.string "Is this cat edible?$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 427 "data/maps/Tamatown/scripts.pory"
	.string "Fshhhh!!! Do not eat cat!!$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 439 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 444 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 449 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 450 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 455 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 459 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 460 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 470 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 472 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 492 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 521 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 536 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_15:
# 550 "data/maps/Tamatown/scripts.pory"
	.string "You got a Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_16:
# 558 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 571 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 582 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have anything for you right\nnow, but I'll be restocked soon!\l(I hope…)$"

Tamatown_EventScript_VendingMachine_Text_2:
# 591 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 596 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 599 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 602 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 605 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 608 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 611 "data/maps/Tamatown/scripts.pory"
	.string "Snack 4{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 613 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 623 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 635 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 648 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Hot Dog, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 655 "data/maps/Tamatown/scripts.pory"
	.string "You got a Hot Dog!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 660 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One PokéBlock, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 667 "data/maps/Tamatown/scripts.pory"
	.string "You got a PokéBlock!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 672 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Sunny Side Up, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 679 "data/maps/Tamatown/scripts.pory"
	.string "You got a Sunny Side Up!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 684 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Doughnut, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 696 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One Ice Cream, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 703 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 708 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One ???, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 715 "data/maps/Tamatown/scripts.pory"
	.string "You got a ???!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 733 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 735 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 746 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 758 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 759 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 766 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 784 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1} happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "That's {STR_VAR_2} cooooins for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 791 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 799 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lYou did your beeeest…\p"
	.string "That's {STR_VAR_2} cooooins for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_9:
# 806 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_10:
# 814 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lOoookaaaaay…\p"
	.string "That's {STR_VAR_2} cooooins for youuuuu…\nAnd a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_11:
# 821 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 829 "data/maps/Tamatown/scripts.pory"
	.string "You served {STR_VAR_1}\ncuuuustomers…\p"
	.string "That's {STR_VAR_2} cooooins for youuuuu…\p"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 843 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 863 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 872 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 874 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 911 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 914 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 921 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 930 "data/maps/Tamatown/scripts.pory"
	.string "You got a Lucky Egg!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 947 "data/maps/Tamatown/scripts.pory"
	.string "Use this letterbox to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 961 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 975 "data/maps/Tamatown/scripts.pory"
	.string "It's a fire hydrant.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 980 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 981 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 998 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 1013 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 1016 "data/maps/Tamatown/scripts.pory"
	.string "I taut I taw a puddy-tat!\nG-get it away from me!$"

Tamatown_EventScript_Torchic_Text_2:
# 1028 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_3:
# 1035 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_4:
# 1042 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat poster for your room!$"

Tamatown_EventScript_Torchic_Text_5:
# 1053 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 1070 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, hot dogs…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 1096 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 1101 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 1102 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 1128 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 1152 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 1154 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool plushie if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 1160 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute plushie for your room!$"

Tamatown_EventScript_TreeckoPrint_Text_0:
# 1183 "data/maps/Tamatown/scripts.pory"
	.string "What a pretty poster!$"

Tamatown_EventScript_TreeckoPrint_Text_1:
# 1187 "data/maps/Tamatown/scripts.pory"
	.string "Grab it$"

Tamatown_EventScript_TreeckoPrint_Text_2:
# 1188 "data/maps/Tamatown/scripts.pory"
	.string "Leave it$"

Tamatown_EventScript_TreeckoPrint_Text_3:
# 1210 "data/maps/Tamatown/scripts.pory"
	.string "Right, what if the cops see you?$"
