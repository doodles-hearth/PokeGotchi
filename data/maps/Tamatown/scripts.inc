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
# 39 "data/maps/Tamatown/scripts.pory"
	closemessage
# 40 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_House_2:
# 36 "data/maps/Tamatown/scripts.pory"
	playse SE_EXIT
# 37 "data/maps/Tamatown/scripts.pory"
	callnative ReturnToPokegotchiHouse
	return


Tamatown_EventScript_Arcade::
# 45 "data/maps/Tamatown/scripts.pory"
	lock
# 47 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 49 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Arcade_Text_0
# 53 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Arcade_Text_1, Tamatown_EventScript_Arcade_Text_2
# 58 "data/maps/Tamatown/scripts.pory"
	closemessage
# 59 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 61 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 62 "data/maps/Tamatown/scripts.pory"
	delay 32
# 63 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 64 "data/maps/Tamatown/scripts.pory"
	waitstate
# 65 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 66 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 68 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Porygon::
# 72 "data/maps/Tamatown/scripts.pory"
	lockall
# 73 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 74 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Porygon_2
# 87 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_5
# 98 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 100 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 101 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 102 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_4
# 109 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_4:
# 112 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_9
Tamatown_EventScript_Porygon_8:
# 126 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_6, Tamatown_EventScript_Porygon_Text_7
# 131 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 132 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_13
# 160 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 161 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 162 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_9
# 167 "data/maps/Tamatown/scripts.pory"
	closemessage
# 169 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 75 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 76 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_0
# 77 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 78 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
# 82 "data/maps/Tamatown/scripts.pory"
	closemessage
# 83 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Porygon_5:
# 88 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 89 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_1
# 91 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 93 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 94 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_3
	goto Tamatown_EventScript_Porygon_4

Tamatown_EventScript_Porygon_9:
# 113 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_5
# 116 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 117 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 119 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 121 "data/maps/Tamatown/scripts.pory"
	closemessage
# 123 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_8

Tamatown_EventScript_Porygon_13:
# 133 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 134 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_2
# 135 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_8
# 138 "data/maps/Tamatown/scripts.pory"
	closemessage
# 140 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 141 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_17
# 143 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_18
# 145 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_19
Tamatown_EventScript_Porygon_15:
# 149 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 151 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 152 "data/maps/Tamatown/scripts.pory"
	delay 32
# 153 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 154 "data/maps/Tamatown/scripts.pory"
	waitstate
# 155 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 156 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 157 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_17:
# 142 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_18:
# 144 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_15

Tamatown_EventScript_Porygon_19:
# 146 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_4
	goto Tamatown_EventScript_Porygon_15


Tamatown_EventScript_Tree::
# 173 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 180 "data/maps/Tamatown/scripts.pory"
	lock
# 181 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 182 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Tangela_2
# 247 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_5
# 272 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_7
# 276 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_8, Tamatown_EventScript_Tangela_Text_9
# 281 "data/maps/Tamatown/scripts.pory"
	closemessage
# 283 "data/maps/Tamatown/scripts.pory"
	delay 24
# 285 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 286 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 287 "data/maps/Tamatown/scripts.pory"
	waitse
# 288 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 290 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_10
# 294 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_11, Tamatown_EventScript_Tangela_Text_12
# 299 "data/maps/Tamatown/scripts.pory"
	closemessage
# 301 "data/maps/Tamatown/scripts.pory"
	delay 24
# 303 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 304 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_3
# 305 "data/maps/Tamatown/scripts.pory"
	waitse
# 306 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 308 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_13
# 309 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_14
# 313 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_15, Tamatown_EventScript_Tangela_Text_16
# 318 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 319 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_4
# 320 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 321 "data/maps/Tamatown/scripts.pory"
	waitse
# 323 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 324 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 325 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_17
# 331 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 333 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_4:
# 336 "data/maps/Tamatown/scripts.pory"
	closemessage
# 338 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 183 "data/maps/Tamatown/scripts.pory"
	waitse
# 184 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 185 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Tangela_Movement_0
# 186 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 187 "data/maps/Tamatown/scripts.pory"
	waitse
# 188 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 189 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_1
# 190 "data/maps/Tamatown/scripts.pory"
	waitse
# 191 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 192 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 193 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 194 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_0
# 197 "data/maps/Tamatown/scripts.pory"
	closemessage
# 199 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 200 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_0
# 201 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 202 "data/maps/Tamatown/scripts.pory"
	waitse
# 203 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TANGELA, Tamatown_EventScript_Tangela_Movement_1
# 204 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 205 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 206 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 209 "data/maps/Tamatown/scripts.pory"
	closemessage
# 211 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 212 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Porygon_Movement_1
# 213 "data/maps/Tamatown/scripts.pory"
	facefollowernpc
# 214 "data/maps/Tamatown/scripts.pory"
	waitse
# 215 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 217 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 218 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 219 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_3
# 223 "data/maps/Tamatown/scripts.pory"
	closemessage
# 225 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 226 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Tangela_Text_4
# 229 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 230 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 231 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 232 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_RUG
# 234 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 235 "data/maps/Tamatown/scripts.pory"
	destroyfollowernpc
# 236 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_SKITTY_FOLLOWING
# 237 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_SKITTY
# 238 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_SKITTY, 45, 27
# 239 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 240 "data/maps/Tamatown/scripts.pory"
	delay 32
# 241 "data/maps/Tamatown/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 243 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Tangela_5:
# 248 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Tangela_9
# 265 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 266 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 267 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_6
# 270 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_4

Tamatown_EventScript_Tangela_9:
# 249 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_WEAK
# 250 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_1
# 251 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 254 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 256 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 257 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_SKITTY, Tamatown_EventScript_Tangela_Movement_2
# 258 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 259 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 261 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Sign::
# 342 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_SkittyFollowing::
# 348 "data/maps/Tamatown/scripts.pory"
	lock
# 349 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
# 350 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 351 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_SkittyFollowing_Text_0
# 354 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 355 "data/maps/Tamatown/scripts.pory"
	release
	end


Tamatown_EventScript_Skitty::
# 360 "data/maps/Tamatown/scripts.pory"
	lock
# 362 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_RUG, Tamatown_EventScript_Skitty_2
# 373 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 374 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 375 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_1
# 381 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Skitty_Text_2, Tamatown_EventScript_House_Text_2
# 386 "data/maps/Tamatown/scripts.pory"
	closemessage
# 388 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Skitty_5
# 393 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 394 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 395 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_3
# 398 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 399 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Skitty_4:
# 402 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Skitty_2:
# 363 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_HIGH_PITCH
# 364 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 365 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Skitty_Text_0
# 368 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 369 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Skitty_5:
# 389 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_WEAK
# 390 "data/maps/Tamatown/scripts.pory"
	setfollowernpc LOCALID_SKITTY, FOLLOWER_NPC_FLAG_ALL, Tamatown_EventScript_SkittyFollowing
# 391 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Skitty_4


Tamatown_EventScript_Trashcan::
# 406 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 414 "data/maps/Tamatown/scripts.pory"
	lock
# 416 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_TrubbishCan_2
# 445 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_4
# 450 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_5, Tamatown_EventScript_TrubbishCan_Text_6
# 455 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_9
# 560 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_16
Tamatown_EventScript_TrubbishCan_8:
# 564 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 567 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 417 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 418 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_TrubbishCan_6
# 437 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 438 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 440 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_3
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 419 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 420 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 421 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
# 425 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 426 "data/maps/Tamatown/scripts.pory"
	applymovement OBJ_EVENT_ID_NPC_FOLLOWER, Tamatown_EventScript_Tangela_Movement_0
# 427 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SKITTY, CRY_MODE_ENCOUNTER
# 428 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 432 "data/maps/Tamatown/scripts.pory"
	closemessage
# 433 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_TrubbishCan_9:
# 456 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_7
# 460 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_8, Tamatown_EventScript_TrubbishCan_Text_9
# 465 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_13
# 501 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_TrubbishCan_17
# 510 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_2
Tamatown_EventScript_TrubbishCan_16:
# 519 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 520 "data/maps/Tamatown/scripts.pory"
	delay 32
# 522 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_13
# 525 "data/maps/Tamatown/scripts.pory"
	closemessage
# 527 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 528 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 530 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 531 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 532 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 534 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 535 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_3
# 536 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 537 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_12:
# 546 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 547 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT
# 549 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 550 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 551 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 554 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 555 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 556 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 557 "data/maps/Tamatown/scripts.pory"
	closemessage
# 558 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_8

Tamatown_EventScript_TrubbishCan_13:
# 466 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 467 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 468 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 469 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 470 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 471 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 472 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_10
# 473 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 477 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 478 "data/maps/Tamatown/scripts.pory"
	closemessage
# 480 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 481 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_4
# 482 "data/maps/Tamatown/scripts.pory"
	waitse
# 483 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 485 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 486 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 488 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 489 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 490 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 492 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 493 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
	goto Tamatown_EventScript_TrubbishCan_12

Tamatown_EventScript_TrubbishCan_17:
# 502 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_TrubbishCan_Movement_1
	goto Tamatown_EventScript_TrubbishCan_16


Tamatown_EventScript_VendingMachine::
# 571 "data/maps/Tamatown/scripts.pory"
	lock
# 573 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_NORMAL
# 574 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 577 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_5
Tamatown_EventScript_VendingMachine_3:
# 591 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_2
Tamatown_EventScript_VendingMachine_1:
# 597 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_16
Tamatown_EventScript_VendingMachine_15:
# 600 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG, Tamatown_EventScript_VendingMachine_19
Tamatown_EventScript_VendingMachine_18:
# 603 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_22
Tamatown_EventScript_VendingMachine_21:
# 606 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_25
Tamatown_EventScript_VendingMachine_24:
# 609 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_28
Tamatown_EventScript_VendingMachine_27:
# 612 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_VendingMachine_31
Tamatown_EventScript_VendingMachine_30:
# 615 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_9, 6
# 616 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 617 "data/maps/Tamatown/scripts.pory"
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, NULL
# 619 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq Tamatown_EventScript_VendingMachine_34
# 619 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Tamatown_EventScript_VendingMachine_34
# 632 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 633 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 3
	goto_if_lt Tamatown_EventScript_VendingMachine_39
# 646 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_HIGH_PITCH
# 647 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 649 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 650 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_VendingMachine_43
# 664 "data/maps/Tamatown/scripts.pory"
	case 1, Tamatown_EventScript_VendingMachine_44
# 678 "data/maps/Tamatown/scripts.pory"
	case 2, Tamatown_EventScript_VendingMachine_45
# 692 "data/maps/Tamatown/scripts.pory"
	case 3, Tamatown_EventScript_VendingMachine_46
# 706 "data/maps/Tamatown/scripts.pory"
	case 4, Tamatown_EventScript_VendingMachine_47
# 720 "data/maps/Tamatown/scripts.pory"
	case 5, Tamatown_EventScript_VendingMachine_48
Tamatown_EventScript_VendingMachine_41:
# 736 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 737 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 738 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 739 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 740 "data/maps/Tamatown/scripts.pory"
	closemessage
# 741 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 743 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_VendingMachine_2:
# 584 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_1
# 588 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK
	goto Tamatown_EventScript_VendingMachine_1

Tamatown_EventScript_VendingMachine_4:
# 579 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_VendingMachine_9
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_5:
# 578 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_MEAL_POKEBLOCK, Tamatown_EventScript_VendingMachine_4
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_8:
# 581 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM, Tamatown_EventScript_VendingMachine_12
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_9:
# 580 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_DOUGHNUT, Tamatown_EventScript_VendingMachine_8
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_12:
# 582 "data/maps/Tamatown/scripts.pory"
	goto_if_unset POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_VendingMachine_2
	goto Tamatown_EventScript_VendingMachine_3

Tamatown_EventScript_VendingMachine_16:
# 598 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_3, 1
	goto Tamatown_EventScript_VendingMachine_15

Tamatown_EventScript_VendingMachine_19:
# 601 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_4, 0
	goto Tamatown_EventScript_VendingMachine_18

Tamatown_EventScript_VendingMachine_22:
# 604 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_5, 2
	goto Tamatown_EventScript_VendingMachine_21

Tamatown_EventScript_VendingMachine_25:
# 607 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_6, 3
	goto Tamatown_EventScript_VendingMachine_24

Tamatown_EventScript_VendingMachine_28:
# 610 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_7, 4
	goto Tamatown_EventScript_VendingMachine_27

Tamatown_EventScript_VendingMachine_31:
# 613 "data/maps/Tamatown/scripts.pory"
	dynmultipush Tamatown_EventScript_VendingMachine_Text_8, 5
	goto Tamatown_EventScript_VendingMachine_30

Tamatown_EventScript_VendingMachine_34:
# 620 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 622 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 623 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 624 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_10
# 627 "data/maps/Tamatown/scripts.pory"
	closemessage
# 628 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_39:
# 634 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 636 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_ROTOM, CRY_MODE_WEAK
# 637 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_VendingMachine_Text_0
# 638 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_11
# 641 "data/maps/Tamatown/scripts.pory"
	closemessage
# 642 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_VendingMachine_43:
# 651 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_12
# 655 "data/maps/Tamatown/scripts.pory"
	closemessage
# 656 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 657 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 658 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 659 "data/maps/Tamatown/scripts.pory"
	waitse
# 660 "data/maps/Tamatown/scripts.pory"
	delay 32
# 661 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_13
# 662 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_44:
# 665 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_14
# 669 "data/maps/Tamatown/scripts.pory"
	closemessage
# 670 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 671 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 672 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 673 "data/maps/Tamatown/scripts.pory"
	waitse
# 674 "data/maps/Tamatown/scripts.pory"
	delay 32
# 675 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_15
# 676 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_POKEBLOCK, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_45:
# 679 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_16
# 683 "data/maps/Tamatown/scripts.pory"
	closemessage
# 684 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 685 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 686 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 687 "data/maps/Tamatown/scripts.pory"
	waitse
# 688 "data/maps/Tamatown/scripts.pory"
	delay 32
# 689 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_17
# 690 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_46:
# 693 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_18
# 697 "data/maps/Tamatown/scripts.pory"
	closemessage
# 698 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 699 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 700 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 701 "data/maps/Tamatown/scripts.pory"
	waitse
# 702 "data/maps/Tamatown/scripts.pory"
	delay 32
# 703 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_15
# 704 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_DONUT, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_47:
# 707 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_19
# 711 "data/maps/Tamatown/scripts.pory"
	closemessage
# 712 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 713 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 714 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 715 "data/maps/Tamatown/scripts.pory"
	waitse
# 716 "data/maps/Tamatown/scripts.pory"
	delay 32
# 717 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_20
# 718 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
	goto Tamatown_EventScript_VendingMachine_41

Tamatown_EventScript_VendingMachine_48:
# 721 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_VendingMachine_Text_21
# 725 "data/maps/Tamatown/scripts.pory"
	closemessage
# 726 "data/maps/Tamatown/scripts.pory"
	removecoins 3
# 727 "data/maps/Tamatown/scripts.pory"
	updatecoinsbox
# 728 "data/maps/Tamatown/scripts.pory"
	playse SE_VEND
# 729 "data/maps/Tamatown/scripts.pory"
	waitse
# 730 "data/maps/Tamatown/scripts.pory"
	delay 32
# 731 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 732 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_JUICE, 1
	goto Tamatown_EventScript_VendingMachine_41


Tamatown_EventScript_Slowpoke::
# 747 "data/maps/Tamatown/scripts.pory"
	lock
# 749 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 759 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 761 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 762 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 763 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 775 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 780 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 858 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 859 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 860 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_13
Tamatown_EventScript_Slowpoke_5:
# 867 "data/maps/Tamatown/scripts.pory"
	closemessage
# 869 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 750 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 751 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 752 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 781 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 782 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 783 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 788 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_POKE_MART, FALSE
# 789 "data/maps/Tamatown/scripts.pory"
	delay 32
# 790 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 791 "data/maps/Tamatown/scripts.pory"
	waitstate
# 792 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 793 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 795 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 796 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_RESULT
# 797 "data/maps/Tamatown/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_0x8000
# 799 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 814 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 829 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_12
# 845 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 846 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
Tamatown_EventScript_Slowpoke_9:
# 854 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_17
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 800 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 801 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 806 "data/maps/Tamatown/scripts.pory"
	closemessage
# 808 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 811 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 812 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 813 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_11:
# 815 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 816 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_8
# 821 "data/maps/Tamatown/scripts.pory"
	closemessage
# 823 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_9
# 826 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 827 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 828 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_12:
# 830 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 831 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_10
# 836 "data/maps/Tamatown/scripts.pory"
	closemessage
# 838 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 841 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 842 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 843 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
	goto Tamatown_EventScript_Slowpoke_9

Tamatown_EventScript_Slowpoke_17:
# 855 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_HOT_DOG
	goto Tamatown_EventScript_Slowpoke_5


Tamatown_EventScript_Vanillish::
# 873 "data/maps/Tamatown/scripts.pory"
	lock
# 875 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_VANILLISH_DIED, Tamatown_EventScript_Vanillish_2
# 890 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_VANILLISH, CRY_MODE_NORMAL
# 891 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Vanillish_Text_1
# 892 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Vanillish_Text_2
# 897 "data/maps/Tamatown/scripts.pory"
	closemessage
# 899 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Vanillish_Movement_0
# 903 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_CAR
# 904 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_CAR
# 905 "data/maps/Tamatown/scripts.pory"
	playse SE_SHIP
# 906 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_CAR, Tamatown_EventScript_Vanillish_Movement_1
# 909 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Vanillish_Movement_2
# 910 "data/maps/Tamatown/scripts.pory"
	delay 44
# 911 "data/maps/Tamatown/scripts.pory"
	playse SE_BALLOON_YELLOW
# 912 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_VANILLISH_DIED
# 913 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 914 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 915 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_ICE_CREAM
# 917 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 918 "data/maps/Tamatown/scripts.pory"
	delay 48
# 920 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm VAR_LAST_TALKED, 33, 20
# 921 "data/maps/Tamatown/scripts.pory"
	setobjectxyperm LOCALID_CAR, 23, 20
Tamatown_EventScript_Vanillish_1:
# 924 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Vanillish_2:
# 876 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_ICE_CREAM
# 877 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HIDE_ICE_CREAM
# 878 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 879 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_ICE_CREAM, 1
# 880 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Vanillish_Text_0
# 883 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 884 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 885 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 886 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 887 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Vanillish_1


Tamatown_EventScript_Chansey::
# 928 "data/maps/Tamatown/scripts.pory"
	lock
# 929 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG, Tamatown_EventScript_Chansey_2
# 937 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 938 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 939 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_2
# 945 "data/maps/Tamatown/scripts.pory"
	closemessage
# 947 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_EGG, 1
# 948 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Chansey_Text_3
# 951 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 952 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 953 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 954 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 955 "data/maps/Tamatown/scripts.pory"
	closemessage
# 957 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_MEAL_EGG
Tamatown_EventScript_Chansey_1:
# 960 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Chansey_2:
# 930 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Chansey_Text_0
# 931 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
# 932 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Chansey_Text_1
# 935 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Chansey_1


Tamatown_EventScript_Mailbox::
# 964 "data/maps/Tamatown/scripts.pory"
	lock
# 966 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Mailbox_Text_0
# 972 "data/maps/Tamatown/scripts.pory"
	closemessage
# 974 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_Hydrant::
# 978 "data/maps/Tamatown/scripts.pory"
	lock
# 980 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hydrant_Text_0
# 983 "data/maps/Tamatown/scripts.pory"
	closemessage
# 985 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HydrantTorchic::
# 989 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_HydrantTorchic_1
# 992 "data/maps/Tamatown/scripts.pory"
	lock
# 994 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_0
# 999 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_HydrantTorchic_Text_1, Tamatown_EventScript_HydrantTorchic_Text_2
# 1003 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1005 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_HydrantTorchic_5
Tamatown_EventScript_HydrantTorchic_4:
# 1025 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_HydrantTorchic_1:
# 990 "data/maps/Tamatown/scripts.pory"
	call Tamatown_EventScript_Hydrant
	return

Tamatown_EventScript_HydrantTorchic_5:
# 1006 "data/maps/Tamatown/scripts.pory"
	playse SE_M_GIGA_DRAIN
# 1007 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 3
# 1008 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 0
# 1009 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 8
# 1010 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 1011 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 1012 "data/maps/Tamatown/scripts.pory"
	waitstate
# 1013 "data/maps/Tamatown/scripts.pory"
	waitse
# 1015 "data/maps/Tamatown/scripts.pory"
	delay 48
# 1017 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HydrantTorchic_Text_3
# 1020 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1022 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_HYDRATED_TORCHIC
	goto Tamatown_EventScript_HydrantTorchic_4


Tamatown_EventScript_Torchic::
# 1030 "data/maps/Tamatown/scripts.pory"
	lock
# 1031 "data/maps/Tamatown/scripts.pory"
	checkfollowernpc
# 1032 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Tamatown_EventScript_Torchic_2
# 1044 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC, Tamatown_EventScript_Torchic_5
# 1051 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_HYDRATED_TORCHIC, Tamatown_EventScript_Torchic_6
# 1071 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_FAINT
# 1072 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1073 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_5
# 1076 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Torchic_4:
# 1079 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Torchic_2:
# 1033 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1034 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_ENCOUNTER
# 1035 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_1
# 1039 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1040 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Torchic_5:
# 1045 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_NORMAL
# 1046 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1047 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_2
# 1050 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Torchic_4

Tamatown_EventScript_Torchic_6:
# 1052 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TORCHIC, CRY_MODE_HIGH_PITCH
# 1053 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Torchic_Text_0
# 1054 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Torchic_Text_3
# 1059 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1061 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Torchic_Text_4
# 1064 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1065 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1066 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1067 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1068 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TORCHIC
	goto Tamatown_EventScript_Torchic_4


Tamatown_EventScript_StepInPoop::
# 1083 "data/maps/Tamatown/scripts.pory"
	lock
# 1084 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_GRIMER, CRY_MODE_NORMAL
# 1085 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_HotDogs::
# 1089 "data/maps/Tamatown/scripts.pory"
	lock
# 1090 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_HotDogs_Text_0
# 1093 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1094 "data/maps/Tamatown/scripts.pory"
	release
	return


Debugpoop::
# 1098 "data/maps/Tamatown/scripts.pory"
	lock
# 1099 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1100 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1101 "data/maps/Tamatown/scripts.pory"
	waitse
# 1102 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_LAMPPOST
# 1103 "data/maps/Tamatown/scripts.pory"
	release
	return


Tamatown_EventScript_DittoLamppost::
# 1107 "data/maps/Tamatown/scripts.pory"
	lock
# 1109 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_DITTO, Tamatown_EventScript_DittoLamppost_2
# 1116 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_0
# 1121 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_DittoLamppost_Text_1, Tamatown_EventScript_DittoLamppost_Text_2
# 1125 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1127 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1129 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_DittoLamppost_5
Tamatown_EventScript_DittoLamppost_1:
# 1199 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_DittoLamppost_2:
# 1110 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1111 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1112 "data/maps/Tamatown/scripts.pory"
	waitse
# 1113 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1114 "data/maps/Tamatown/scripts.pory"
	delay 1
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_5:
# 1130 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_WEST
	goto_if_eq Tamatown_EventScript_DittoLamppost_8
# 1134 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_EAST
	goto_if_eq Tamatown_EventScript_DittoLamppost_9
# 1138 "data/maps/Tamatown/scripts.pory"
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Tamatown_EventScript_DittoLamppost_10
# 1143 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_3
Tamatown_EventScript_DittoLamppost_7:
# 1148 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_3
# 1151 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1153 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1154 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_DITTO, Tamatown_EventScript_Tangela_Movement_0
# 1155 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1156 "data/maps/Tamatown/scripts.pory"
	waitse
# 1157 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 1158 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_DITTO, Tamatown_EventScript_DittoLamppost_Movement_4
# 1159 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 1160 "data/maps/Tamatown/scripts.pory"
	waitse
# 1162 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1164 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO, OBJ_EVENT_GFX_PG_DITTO
# 1166 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 1167 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 1168 "data/maps/Tamatown/scripts.pory"
	waitse
# 1169 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1171 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1173 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
# 1174 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_DittoLamppost_Text_4
# 1175 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_DittoLamppost_Text_5
# 1179 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1181 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_DittoLamppost_Text_6
# 1184 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1185 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1186 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1187 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1188 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1190 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_DITTO
# 1192 "data/maps/Tamatown/scripts.pory"
	delay 16
# 1194 "data/maps/Tamatown/scripts.pory"
	mosaicmorph LOCALID_DITTO
# 1195 "data/maps/Tamatown/scripts.pory"
	delay 16
	goto Tamatown_EventScript_DittoLamppost_1

Tamatown_EventScript_DittoLamppost_8:
# 1131 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_0
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_9:
# 1135 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_1
	goto Tamatown_EventScript_DittoLamppost_7

Tamatown_EventScript_DittoLamppost_10:
# 1139 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_DittoLamppost_Movement_2
	goto Tamatown_EventScript_DittoLamppost_7


Tamatown_EventScript_TreeckoPrint::
# 1203 "data/maps/Tamatown/scripts.pory"
	lock
# 1205 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_0
# 1209 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TreeckoPrint_Text_1, Tamatown_EventScript_TreeckoPrint_Text_2
# 1213 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1215 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TreeckoPrint_2
# 1233 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TreeckoPrint_Text_4
# 1236 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TreeckoPrint_1:
# 1239 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TreeckoPrint_2:
# 1216 "data/maps/Tamatown/scripts.pory"
	playse SE_CONTEST_CONDITION_LOSE
# 1217 "data/maps/Tamatown/scripts.pory"
	setmetatile 29, 8, METATILE_Tamatown_BrickWall, TRUE
# 1218 "data/maps/Tamatown/scripts.pory"
	special DrawWholeMapView
# 1219 "data/maps/Tamatown/scripts.pory"
	removeobject VAR_LAST_TALKED
# 1220 "data/maps/Tamatown/scripts.pory"
	waitse
# 1221 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1223 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TreeckoPrint_Text_3
# 1226 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1227 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1228 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1229 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1230 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_TREECKO
# 1231 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_TreeckoPrint_1


Tamatown_EventScript_Hypno::
# 1243 "data/maps/Tamatown/scripts.pory"
	lock
# 1244 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_BED, Tamatown_EventScript_Hypno_2
# 1252 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1253 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_3
# 1254 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_NORMAL
# 1255 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_2
# 1262 "data/maps/Tamatown/scripts.pory"
	showcoinsbox 20, 0
# 1264 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Hypno_Text_3, Tamatown_EventScript_Hypno_Text_4
# 1268 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1270 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Hypno_5
# 1294 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1295 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_WEAK
# 1296 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_7
# 1299 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Hypno_1:
# 1303 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Hypno_2:
# 1245 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1246 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_NORMAL
# 1247 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_1
# 1250 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Hypno_1

Tamatown_EventScript_Hypno_5:
# 1271 "data/maps/Tamatown/scripts.pory"
	checkcoins VAR_0x8000
# 1272 "data/maps/Tamatown/scripts.pory"
	compare VAR_0x8000, 50
	goto_if_lt Tamatown_EventScript_Hypno_8
# 1280 "data/maps/Tamatown/scripts.pory"
	removecoins 50
# 1281 "data/maps/Tamatown/scripts.pory"
	hidecoinsbox
# 1282 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1283 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 1284 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_HIGH_PITCH
# 1285 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_6
# 1289 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1291 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_BED
	goto Tamatown_EventScript_Hypno_1

Tamatown_EventScript_Hypno_8:
# 1273 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Hypno_Text_0
# 1274 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_HYPNO, CRY_MODE_WEAK
# 1275 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Hypno_Text_5
# 1278 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Hypno_1


Tamatown_EventScript_Shuckle::
# 1307 "data/maps/Tamatown/scripts.pory"
	lock
# 1309 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE, Tamatown_EventScript_Shuckle_2
# 1320 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1321 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1322 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_2
# 1326 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Shuckle_Text_3, Tamatown_EventScript_Shuckle_Text_4
# 1331 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Shuckle_5
# 1365 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_FAINT
# 1366 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1367 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_7
# 1370 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Shuckle_4:
# 1373 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Shuckle_2:
# 1310 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1311 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1312 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_1
# 1315 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1316 "data/maps/Tamatown/scripts.pory"
	release
	end

Tamatown_EventScript_Shuckle_5:
# 1332 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_ENCOUNTER
# 1333 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Shuckle_Movement_0
# 1334 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_5
# 1337 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 1338 "data/maps/Tamatown/scripts.pory"
	waitmovementall
# 1339 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1341 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1343 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SHUCKLE, CRY_MODE_NORMAL
# 1344 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Shuckle_Text_0
# 1345 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Shuckle_Text_6
# 1349 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 1350 "data/maps/Tamatown/scripts.pory"
	closemessage
# 1351 "data/maps/Tamatown/scripts.pory"
	delay 32
# 1353 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_VendingMachine_Text_22
# 1356 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1357 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1358 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1359 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1360 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_UNLOCKED_SNACK_JUICE
# 1361 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_JUICE, 1
# 1362 "data/maps/Tamatown/scripts.pory"
	closemessage
	goto Tamatown_EventScript_Shuckle_4


Tamatown_EventScript_TrashcanPoster::
# 1377 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FRNTR_POSTER_MUDKIP, Tamatown_EventScript_TrashcanPoster_2
Tamatown_EventScript_TrashcanPoster_1:
# 1381 "data/maps/Tamatown/scripts.pory"
	lock
# 1382 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrashcanPoster_Text_0
# 1385 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 1386 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 1387 "data/maps/Tamatown/scripts.pory"
	waitmessage
# 1388 "data/maps/Tamatown/scripts.pory"
	waitbuttonpress
# 1389 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FRNTR_POSTER_MUDKIP
# 1390 "data/maps/Tamatown/scripts.pory"
	closemessage
	return

Tamatown_EventScript_TrashcanPoster_2:
# 1378 "data/maps/Tamatown/scripts.pory"
	goto Tamatown_EventScript_Trashcan
	goto Tamatown_EventScript_TrashcanPoster_1


# 76 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 76 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 89 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 89 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 142 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 142 "data/maps/Tamatown/scripts.pory"
	walk_right
# 142 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 144 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 144 "data/maps/Tamatown/scripts.pory"
	walk_left
# 144 "data/maps/Tamatown/scripts.pory"
	walk_down
# 144 "data/maps/Tamatown/scripts.pory"
	walk_down
# 144 "data/maps/Tamatown/scripts.pory"
	walk_right
# 144 "data/maps/Tamatown/scripts.pory"
	walk_right
# 144 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 146 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_4:
# 146 "data/maps/Tamatown/scripts.pory"
	walk_down
# 146 "data/maps/Tamatown/scripts.pory"
	walk_right
# 146 "data/maps/Tamatown/scripts.pory"
	walk_right
# 146 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 185 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 185 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
	step_end

# 203 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_1:
# 203 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
# 203 "data/maps/Tamatown/scripts.pory"
	shake_horizontal
	step_end

# 257 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_2:
# 257 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 257 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 286 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_3:
# 286 "data/maps/Tamatown/scripts.pory"
	shake_vertical
	step_end

# 319 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_4:
# 319 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
# 319 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 489 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 489 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 489 "data/maps/Tamatown/scripts.pory"
	delay_16
# 489 "data/maps/Tamatown/scripts.pory"
	delay_16
# 489 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 502 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 503 "data/maps/Tamatown/scripts.pory"
	quarter_step_left
# 504 "data/maps/Tamatown/scripts.pory"
	delay_16
# 504 "data/maps/Tamatown/scripts.pory"
	delay_16
# 505 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 506 "data/maps/Tamatown/scripts.pory"
	quarter_step_right
# 507 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 510 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 511 "data/maps/Tamatown/scripts.pory"
	quarter_step_up
# 512 "data/maps/Tamatown/scripts.pory"
	delay_16
# 512 "data/maps/Tamatown/scripts.pory"
	delay_16
# 513 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 514 "data/maps/Tamatown/scripts.pory"
	quarter_step_down
# 515 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 535 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_3:
# 535 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

# 899 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_0:
# 900 "data/maps/Tamatown/scripts.pory"
	walk_slow_down
	step_end

# 906 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_1:
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
# 907 "data/maps/Tamatown/scripts.pory"
	walk_faster_left
	step_end

# 909 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Vanillish_Movement_2:
# 909 "data/maps/Tamatown/scripts.pory"
	face_down
	step_end

# 1131 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_0:
# 1132 "data/maps/Tamatown/scripts.pory"
	walk_left
# 1132 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1132 "data/maps/Tamatown/scripts.pory"
	walk_right
# 1132 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1135 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_1:
# 1136 "data/maps/Tamatown/scripts.pory"
	walk_right
# 1136 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1136 "data/maps/Tamatown/scripts.pory"
	walk_left
# 1136 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1139 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_2:
# 1140 "data/maps/Tamatown/scripts.pory"
	walk_down
# 1140 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1140 "data/maps/Tamatown/scripts.pory"
	walk_up
# 1140 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1143 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_3:
# 1144 "data/maps/Tamatown/scripts.pory"
	walk_up
# 1144 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1144 "data/maps/Tamatown/scripts.pory"
	walk_down
# 1144 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1158 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_DittoLamppost_Movement_4:
# 1158 "data/maps/Tamatown/scripts.pory"
	lock_facing_direction
# 1158 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 1158 "data/maps/Tamatown/scripts.pory"
	unlock_facing_direction
	step_end

# 1333 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Shuckle_Movement_0:
# 1333 "data/maps/Tamatown/scripts.pory"
	shake_vertical
# 1333 "data/maps/Tamatown/scripts.pory"
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
# 50 "data/maps/Tamatown/scripts.pory"
	.string "Play {COLOR RED}Pachinko{COLOR DARK_GRAY}?\p$"

Tamatown_EventScript_Arcade_Text_1:
# 54 "data/maps/Tamatown/scripts.pory"
	.string "Play$"

Tamatown_EventScript_Arcade_Text_2:
# 55 "data/maps/Tamatown/scripts.pory"
	.string "Don't play$"

Tamatown_EventScript_Porygon_Text_0:
# 75 "data/maps/Tamatown/scripts.pory"
	.string "Skitty$"

Tamatown_EventScript_Porygon_Text_1:
# 79 "data/maps/Tamatown/scripts.pory"
	.string "Porygon is a nerd!\nI don't want a virtual ball of yarn!$"

Tamatown_EventScript_Porygon_Text_2:
# 93 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_3:
# 95 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_4:
# 103 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you {COLOR RED}15 coins{COLOR DARK_GRAY} everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_5:
# 114 "data/maps/Tamatown/scripts.pory"
	.string "You got {COLOR RED}15 coins{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Porygon_Text_6:
# 127 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_7:
# 128 "data/maps/Tamatown/scripts.pory"
	.string "Nah$"

Tamatown_EventScript_Porygon_Text_8:
# 136 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_9:
# 163 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 174 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 195 "data/maps/Tamatown/scripts.pory"
	.string "A ball! A ball of yarn! Meow!!$"

Tamatown_EventScript_Tangela_Text_1:
# 205 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_2:
# 207 "data/maps/Tamatown/scripts.pory"
	.string "I-I'm not a ball of yarn!\nI'm a tree!$"

Tamatown_EventScript_Tangela_Text_3:
# 220 "data/maps/Tamatown/scripts.pory"
	.string "Thank you, odd little bug.\p"
	.string "Here! one of my crafting\nprojects in return!$"

Tamatown_EventScript_Tangela_Text_4:
# 227 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute {COLOR RED}Crochet Rug{COLOR DARK_GRAY} for your\nroom!$"

Tamatown_EventScript_Tangela_Text_5:
# 252 "data/maps/Tamatown/scripts.pory"
	.string "It's hard to hide in plain sight\nwith this one playing with my vines…$"

Tamatown_EventScript_Tangela_Text_6:
# 268 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_7:
# 273 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_8:
# 277 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_9:
# 278 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_10:
# 291 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_11:
# 295 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_12:
# 296 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_13:
# 308 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_14:
# 310 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_15:
# 314 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_16:
# 315 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_17:
# 326 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 343 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_SkittyFollowing_Text_0:
# 352 "data/maps/Tamatown/scripts.pory"
	.string "I want a ball of yarn!\nMeow!$"

Tamatown_EventScript_Skitty_Text_0:
# 366 "data/maps/Tamatown/scripts.pory"
	.string "Meow meow meow!\nYarn yarn yarn!$"

Tamatown_EventScript_Skitty_Text_1:
# 376 "data/maps/Tamatown/scripts.pory"
	.string "Meow…\nI lost my ball of yarn…\p"
	.string "You!{PAUSE 8} Bug!{PAUSE 8} Find me more yarn!\n"
	.string "Take me with you!$"

Tamatown_EventScript_Skitty_Text_2:
# 382 "data/maps/Tamatown/scripts.pory"
	.string "Alright$"

Tamatown_EventScript_Skitty_Text_3:
# 396 "data/maps/Tamatown/scripts.pory"
	.string "Alright… Meow…$"

Tamatown_EventScript_Trashcan_Text_0:
# 407 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 419 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 422 "data/maps/Tamatown/scripts.pory"
	.string "Is this cat edible?$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 429 "data/maps/Tamatown/scripts.pory"
	.string "Fshhhh!!! Do not eat cat!!$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 441 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 446 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 451 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 452 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 457 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 461 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 462 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 472 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 474 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 494 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 523 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 538 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_15:
# 552 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Doughnut{COLOR DARK_GRAY}!$"

Tamatown_EventScript_TrubbishCan_Text_16:
# 561 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_VendingMachine_Text_0:
# 574 "data/maps/Tamatown/scripts.pory"
	.string "Vending machine$"

Tamatown_EventScript_VendingMachine_Text_1:
# 585 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "I don't have much right now, but I'm\noften restocked!$"

Tamatown_EventScript_VendingMachine_Text_2:
# 592 "data/maps/Tamatown/scripts.pory"
	.string "BZZT. This is your friendly\nneighborhood vending machine system.\p"
	.string "Would you like to purchase anything?$"

Tamatown_EventScript_VendingMachine_Text_3:
# 598 "data/maps/Tamatown/scripts.pory"
	.string "PokéBlock{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_4:
# 601 "data/maps/Tamatown/scripts.pory"
	.string "Hot Dog{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_5:
# 604 "data/maps/Tamatown/scripts.pory"
	.string "Sunny Side Up{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_6:
# 607 "data/maps/Tamatown/scripts.pory"
	.string "Doughnut{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_7:
# 610 "data/maps/Tamatown/scripts.pory"
	.string "Ice Cream{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_8:
# 613 "data/maps/Tamatown/scripts.pory"
	.string "Shuckle Juice{CLEAR_TO 0x4c}¥3$"

Tamatown_EventScript_VendingMachine_Text_9:
# 615 "data/maps/Tamatown/scripts.pory"
	.string "No, thanks$"

Tamatown_EventScript_VendingMachine_Text_10:
# 625 "data/maps/Tamatown/scripts.pory"
	.string "Aw…\nUh, I mean, BZZT BZZT…$"

Tamatown_EventScript_VendingMachine_Text_11:
# 639 "data/maps/Tamatown/scripts.pory"
	.string "BZZT BZZT!\nYou don't have enough cash, buddy…$"

Tamatown_EventScript_VendingMachine_Text_12:
# 652 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Hot Dog{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_13:
# 661 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Hot Dog{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_14:
# 666 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}PokéBlock{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_15:
# 675 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}PokéBlock{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_16:
# 680 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Sunny Side Up{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_17:
# 689 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Sunny Side Up{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_18:
# 694 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Doughnut{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_19:
# 708 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Ice Cream{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_20:
# 717 "data/maps/Tamatown/scripts.pory"
	.string "You got an {COLOR RED}Ice Cream{COLOR DARK_GRAY}!$"

Tamatown_EventScript_VendingMachine_Text_21:
# 722 "data/maps/Tamatown/scripts.pory"
	.string "Yay!! I mean, BZZT.\n"
	.string "One {COLOR RED}Shuckle Juice{COLOR DARK_GRAY}, coming up!$"

Tamatown_EventScript_VendingMachine_Text_22:
# 731 "data/maps/Tamatown/scripts.pory"
	.string "You got a box of {COLOR RED}Shuckle Juice{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_0:
# 751 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 753 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us out\ntodaaaaay?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 764 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 776 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 777 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 784 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 802 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1} happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 809 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 {COLOR RED}Hot Dogs{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 817 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lYou did your beeeest…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd you deserve a meaaaaaaal…$"

Tamatown_EventScript_Slowpoke_Text_9:
# 824 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 {COLOR RED}Hot Dogs{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_10:
# 832 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served {STR_VAR_1}\ncuuuustomers…\lOoookaaaaay…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\nAnd a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_11:
# 839 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 {COLOR RED}Hot Dog{COLOR DARK_GRAY}!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 847 "data/maps/Tamatown/scripts.pory"
	.string "You served {STR_VAR_1}\ncuuuustomers…\p"
	.string "That's {COLOR RED}{STR_VAR_2} cooooins{COLOR DARK_GRAY} for youuuuu…\p"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 861 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"

Tamatown_EventScript_Vanillish_Text_0:
# 881 "data/maps/Tamatown/scripts.pory"
	.string "You got an Ice Cream!\nIs this what freedom tastes like?$"

Tamatown_EventScript_Vanillish_Text_1:
# 891 "data/maps/Tamatown/scripts.pory"
	.string "Vanillish$"

Tamatown_EventScript_Vanillish_Text_2:
# 893 "data/maps/Tamatown/scripts.pory"
	.string "Who decides I can only cross the\nstreet on the Zebstrika crossing?\p"
	.string "Shuck the law! Shuck the police!\p"
	.string "This is what freedom tastes like,\nbaby!!$"

Tamatown_EventScript_Chansey_Text_0:
# 930 "data/maps/Tamatown/scripts.pory"
	.string "Chansey$"

Tamatown_EventScript_Chansey_Text_1:
# 933 "data/maps/Tamatown/scripts.pory"
	.string "Do you feel big and strong yet,\nsweetie?$"

Tamatown_EventScript_Chansey_Text_2:
# 940 "data/maps/Tamatown/scripts.pory"
	.string "Hiiii there honey pie! Are you lost?\nOh, you're just out for a stroll?\l"
	.string "Sorry, I thought you were a child!\p"
	.string "I bet other Pokémon would take you\nmore seriously if you evolved.\p"
	.string "Maybe holding this will help you\nbecome big and strong!$"

Tamatown_EventScript_Chansey_Text_3:
# 949 "data/maps/Tamatown/scripts.pory"
	.string "You got a {COLOR RED}Lucky Egg{COLOR DARK_GRAY}!\nYum…$"

Tamatown_EventScript_Mailbox_Text_0:
# 967 "data/maps/Tamatown/scripts.pory"
	.string "Use this {COLOR RED}letterbox{COLOR DARK_GRAY} to send mail to\nother players!\p"
	.string "jk lol, every vanilla feature was\nnuked out of existence and we still\lran out of time to finish this game,\l"
	.string "ha ha ha ha ha…\p"
	.string "(cries)$"

Tamatown_EventScript_Hydrant_Text_0:
# 981 "data/maps/Tamatown/scripts.pory"
	.string "It's a {COLOR RED}fire hydrant{COLOR DARK_GRAY}.\nFor hydrating fire.$"

Tamatown_EventScript_HydrantTorchic_Text_0:
# 995 "data/maps/Tamatown/scripts.pory"
	.string "It's a {COLOR RED}fire hydrant{COLOR DARK_GRAY}.\nFor hydrating fire.\p"
	.string "… … …Hydrate Torchic?$"

Tamatown_EventScript_HydrantTorchic_Text_1:
# 1000 "data/maps/Tamatown/scripts.pory"
	.string "Hydrate away$"

Tamatown_EventScript_HydrantTorchic_Text_2:
# 1001 "data/maps/Tamatown/scripts.pory"
	.string "Maybe not$"

Tamatown_EventScript_HydrantTorchic_Text_3:
# 1018 "data/maps/Tamatown/scripts.pory"
	.string "Torchic looks wetter now.$"

Tamatown_EventScript_Torchic_Text_0:
# 1033 "data/maps/Tamatown/scripts.pory"
	.string "Torchic$"

Tamatown_EventScript_Torchic_Text_1:
# 1036 "data/maps/Tamatown/scripts.pory"
	.string "I taut I taw a puddy-tat!\nG-get it away from me!$"

Tamatown_EventScript_Torchic_Text_2:
# 1048 "data/maps/Tamatown/scripts.pory"
	.string "I wish I were a water type, then I'd be\nhydrated as hell!$"

Tamatown_EventScript_Torchic_Text_3:
# 1055 "data/maps/Tamatown/scripts.pory"
	.string "… … …Oh wow, I feel so refreshed!\p"
	.string "Thank you, little bug!\nDon't worry, I won't eat you!\p"
	.string "Here's a little something to thank\nyou!$"

Tamatown_EventScript_Torchic_Text_4:
# 1062 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Poster{COLOR DARK_GRAY} for your room!$"

Tamatown_EventScript_Torchic_Text_5:
# 1074 "data/maps/Tamatown/scripts.pory"
	.string "I'm so thirsty…$"

Tamatown_EventScript_HotDogs_Text_0:
# 1091 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, {COLOR RED}Hot Dogs{COLOR DARK_GRAY}…\n(Wonder what the sausage is made of…)$"

Tamatown_EventScript_DittoLamppost_Text_0:
# 1117 "data/maps/Tamatown/scripts.pory"
	.string "… … …\p"
	.string "You feel like this lamppost is\nstaring at you…$"

Tamatown_EventScript_DittoLamppost_Text_1:
# 1122 "data/maps/Tamatown/scripts.pory"
	.string "Boop it$"

Tamatown_EventScript_DittoLamppost_Text_2:
# 1123 "data/maps/Tamatown/scripts.pory"
	.string "Leave it be$"

Tamatown_EventScript_DittoLamppost_Text_3:
# 1149 "data/maps/Tamatown/scripts.pory"
	.string "Boop!$"

Tamatown_EventScript_DittoLamppost_Text_4:
# 1174 "data/maps/Tamatown/scripts.pory"
	.string "Ditto$"

Tamatown_EventScript_DittoLamppost_Text_5:
# 1176 "data/maps/Tamatown/scripts.pory"
	.string "Please don't tell anyone.\nI like being a lamppost!\p"
	.string "I'll give you a cool {COLOR RED}Plushie{COLOR DARK_GRAY} if you\nkeep this a secret.$"

Tamatown_EventScript_DittoLamppost_Text_6:
# 1182 "data/maps/Tamatown/scripts.pory"
	.string "You got a cute {COLOR RED}Plushie{COLOR DARK_GRAY} for your room!$"

Tamatown_EventScript_TreeckoPrint_Text_0:
# 1206 "data/maps/Tamatown/scripts.pory"
	.string "What a pretty {COLOR RED}Poster{COLOR DARK_GRAY}!$"

Tamatown_EventScript_TreeckoPrint_Text_1:
# 1210 "data/maps/Tamatown/scripts.pory"
	.string "Grab it$"

Tamatown_EventScript_TreeckoPrint_Text_2:
# 1211 "data/maps/Tamatown/scripts.pory"
	.string "Leave it$"

Tamatown_EventScript_TreeckoPrint_Text_3:
# 1224 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Green Poster{COLOR DARK_GRAY} for your\nroom!$"

Tamatown_EventScript_TreeckoPrint_Text_4:
# 1234 "data/maps/Tamatown/scripts.pory"
	.string "Right, what if the cops see you?$"

Tamatown_EventScript_Hypno_Text_0:
# 1245 "data/maps/Tamatown/scripts.pory"
	.string "Hypno$"

Tamatown_EventScript_Hypno_Text_1:
# 1248 "data/maps/Tamatown/scripts.pory"
	.string "Has your sleep quality improved?{PAUSE 8}\nHmmmm…{PAUSE 8} Yessss…$"

Tamatown_EventScript_Hypno_Text_2:
# 1256 "data/maps/Tamatown/scripts.pory"
	.string "Well,{PAUSE 8} hello there,{PAUSE 8} little child…\nDo you sleep well, mmyes?\p"
	.string "I can sense a…{PAUSE 8} deep…{PAUSE 8} fatigue, yes…\p"
	.string "I can sell you the secret to a better\nsleep…\p"
	.string "Only 50 of those {COLOR RED}Pachinko coins{COLOR DARK_GRAY},{PAUSE 8}\nhmmm,{PAUSE 8} yes…$"

Tamatown_EventScript_Hypno_Text_3:
# 1265 "data/maps/Tamatown/scripts.pory"
	.string "Gimme!$"

Tamatown_EventScript_Hypno_Text_4:
# 1266 "data/maps/Tamatown/scripts.pory"
	.string "Too pricey$"

Tamatown_EventScript_Hypno_Text_5:
# 1276 "data/maps/Tamatown/scripts.pory"
	.string "Come back with more of those sweet,{PAUSE 8}\nscrumptious coins…$"

Tamatown_EventScript_Hypno_Text_6:
# 1286 "data/maps/Tamatown/scripts.pory"
	.string "Hmmm, yes!{PAUSE 8}Love it…{PAUSE 8}\nGive…\p"
	.string "Go back home…{PAUSE 8}\nIt is waiting for you already…$"

Tamatown_EventScript_Hypno_Text_7:
# 1297 "data/maps/Tamatown/scripts.pory"
	.string "Maybe you don't{PAUSE 8} deserve better\nsleep…$"

Tamatown_EventScript_Shuckle_Text_0:
# 1311 "data/maps/Tamatown/scripts.pory"
	.string "Shuckle$"

Tamatown_EventScript_Shuckle_Text_1:
# 1313 "data/maps/Tamatown/scripts.pory"
	.string "Is it weird for me to drink my own\njuice?\lHmmm…$"

Tamatown_EventScript_Shuckle_Text_2:
# 1323 "data/maps/Tamatown/scripts.pory"
	.string "Yo! Quick! Shake me!!$"

Tamatown_EventScript_Shuckle_Text_3:
# 1327 "data/maps/Tamatown/scripts.pory"
	.string "Shake!$"

Tamatown_EventScript_Shuckle_Text_4:
# 1328 "data/maps/Tamatown/scripts.pory"
	.string "Why??$"

Tamatown_EventScript_Shuckle_Text_5:
# 1335 "data/maps/Tamatown/scripts.pory"
	.string "(Shake shake shake shake shake)$"

Tamatown_EventScript_Shuckle_Text_6:
# 1346 "data/maps/Tamatown/scripts.pory"
	.string "… … … … …\p"
	.string "Aaaaand it's ready! Here, have some!$"

Tamatown_EventScript_Shuckle_Text_7:
# 1368 "data/maps/Tamatown/scripts.pory"
	.string "Disappointment!… …$"

Tamatown_EventScript_TrashcanPoster_Text_0:
# 1383 "data/maps/Tamatown/scripts.pory"
	.string "You got a neat {COLOR RED}Blue Poster{COLOR DARK_GRAY} for your\nroom!$"
