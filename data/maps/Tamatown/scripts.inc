Tamatown_MapScripts::
	.byte 0


Tamatown_EventScript_Porygon::
# 9 "data/maps/Tamatown/scripts.pory"
	lockall
# 11 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_PACHINKO, Tamatown_EventScript_Porygon_2
# 22 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_PACHINKO
# 24 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 25 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 26 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_2
# 33 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_Porygon_1:
# 36 "data/maps/Tamatown/scripts.pory"
	goto_if_unset FLAG_RECEIVED_PACHINKO_COINS, Tamatown_EventScript_Porygon_6
Tamatown_EventScript_Porygon_5:
# 50 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Porygon_Text_4, Tamatown_EventScript_Porygon_Text_5
# 55 "data/maps/Tamatown/scripts.pory"
	switch VAR_RESULT
# 56 "data/maps/Tamatown/scripts.pory"
	case 0, Tamatown_EventScript_Porygon_10
# 84 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_WEAK
# 85 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 86 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_7
# 91 "data/maps/Tamatown/scripts.pory"
	closemessage
# 93 "data/maps/Tamatown/scripts.pory"
	releaseall
	return

Tamatown_EventScript_Porygon_2:
# 12 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 13 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Porygon_Movement_0
# 15 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_NORMAL
# 17 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 18 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_1
	goto Tamatown_EventScript_Porygon_1

Tamatown_EventScript_Porygon_6:
# 37 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Porygon_Text_3
# 40 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 41 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 43 "data/maps/Tamatown/scripts.pory"
	addcoins 15
# 45 "data/maps/Tamatown/scripts.pory"
	closemessage
# 47 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_PACHINKO_COINS
	goto Tamatown_EventScript_Porygon_5

Tamatown_EventScript_Porygon_10:
# 57 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_PORYGON, CRY_MODE_HIGH_PITCH
# 58 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Porygon_Text_0
# 59 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Porygon_Text_6
# 62 "data/maps/Tamatown/scripts.pory"
	closemessage
# 64 "data/maps/Tamatown/scripts.pory"
	switch VAR_FACING
# 65 "data/maps/Tamatown/scripts.pory"
	case DIR_NORTH, Tamatown_EventScript_Porygon_14
# 67 "data/maps/Tamatown/scripts.pory"
	case DIR_SOUTH, Tamatown_EventScript_Porygon_15
# 69 "data/maps/Tamatown/scripts.pory"
	case DIR_EAST, Tamatown_EventScript_Porygon_16
Tamatown_EventScript_Porygon_12:
# 73 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 75 "data/maps/Tamatown/scripts.pory"
	playbgm MUS_TRICK_HOUSE, FALSE
# 76 "data/maps/Tamatown/scripts.pory"
	delay 32
# 77 "data/maps/Tamatown/scripts.pory"
	callnative PlayPachinko
# 78 "data/maps/Tamatown/scripts.pory"
	waitstate
# 79 "data/maps/Tamatown/scripts.pory"
	savebgm MUS_DUMMY
# 80 "data/maps/Tamatown/scripts.pory"
	fadedefaultbgm
# 81 "data/maps/Tamatown/scripts.pory"
	releaseall
	end

Tamatown_EventScript_Porygon_14:
# 66 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_1
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_15:
# 68 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_2
	goto Tamatown_EventScript_Porygon_12

Tamatown_EventScript_Porygon_16:
# 70 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Porygon_Movement_3
	goto Tamatown_EventScript_Porygon_12


Tamatown_EventScript_Tree::
# 97 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tree_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_Tangela::
# 104 "data/maps/Tamatown/scripts.pory"
	lock
# 106 "data/maps/Tamatown/scripts.pory"
	goto_if_set POKEGOTCHI_FLAG_FOUND_TANGELA, Tamatown_EventScript_Tangela_2
# 114 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_2
# 118 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_3, Tamatown_EventScript_Tangela_Text_4
# 123 "data/maps/Tamatown/scripts.pory"
	closemessage
# 125 "data/maps/Tamatown/scripts.pory"
	delay 24
# 128 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 130 "data/maps/Tamatown/scripts.pory"
	waitse
# 133 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_5
# 137 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_6, Tamatown_EventScript_Tangela_Text_7
# 142 "data/maps/Tamatown/scripts.pory"
	closemessage
# 144 "data/maps/Tamatown/scripts.pory"
	delay 24
# 147 "data/maps/Tamatown/scripts.pory"
	playse SE_FU_ZAKU
# 149 "data/maps/Tamatown/scripts.pory"
	waitse
# 152 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_8
# 153 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_9
# 157 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_Tangela_Text_10, Tamatown_EventScript_Tangela_Text_11
# 162 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 163 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_Tangela_Movement_0
# 164 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 165 "data/maps/Tamatown/scripts.pory"
	waitse
# 167 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 168 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 169 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_12
# 175 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 177 "data/maps/Tamatown/scripts.pory"
	setflag POKEGOTCHI_FLAG_FOUND_TANGELA
Tamatown_EventScript_Tangela_1:
# 180 "data/maps/Tamatown/scripts.pory"
	closemessage
# 182 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Tangela_2:
# 107 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TANGELA, CRY_MODE_NORMAL
# 108 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Tangela_Text_0
# 109 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Tangela_Text_1
# 112 "data/maps/Tamatown/scripts.pory"
	waitmoncry
	goto Tamatown_EventScript_Tangela_1


Tamatown_EventScript_Sign::
# 186 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Sign_Text_0, MSGBOX_SIGN
	return


Tamatown_EventScript_Skitty::
	return


Tamatown_EventScript_Trashcan::
# 197 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Trashcan_Text_0, MSGBOX_AUTOCLOSE
	return


Tamatown_EventScript_TrubbishCan::
# 205 "data/maps/Tamatown/scripts.pory"
	lock
# 207 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_RECEIVED_DAILY_DONUT, Tamatown_EventScript_TrubbishCan_2
# 216 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_2
# 221 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_TrubbishCan_Text_3, Tamatown_EventScript_TrubbishCan_Text_4
# 226 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_6
# 313 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_14
Tamatown_EventScript_TrubbishCan_5:
# 317 "data/maps/Tamatown/scripts.pory"
	closemessage
Tamatown_EventScript_TrubbishCan_1:
# 320 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_TrubbishCan_2:
# 208 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 209 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 211 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_1
	goto Tamatown_EventScript_TrubbishCan_1

Tamatown_EventScript_TrubbishCan_6:
# 227 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_5
# 231 "data/maps/Tamatown/scripts.pory"
	mcdialogue Tamatown_EventScript_TrubbishCan_Text_6, Tamatown_EventScript_TrubbishCan_Text_7
# 236 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_TrubbishCan_10
# 273 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 274 "data/maps/Tamatown/scripts.pory"
	applymovement VAR_LAST_TALKED, Tamatown_EventScript_TrubbishCan_Movement_1
# 275 "data/maps/Tamatown/scripts.pory"
	waitse
# 276 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 278 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_11
# 281 "data/maps/Tamatown/scripts.pory"
	closemessage
# 283 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 284 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 286 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 287 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 288 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 290 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 291 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_2
# 292 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 293 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_12
Tamatown_EventScript_TrubbishCan_9:
# 302 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_RECEIVED_DAILY_DONUT
# 304 "data/maps/Tamatown/scripts.pory"
	setspeaker NULL
# 305 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 306 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_TrubbishCan_Text_13
# 309 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 310 "data/maps/Tamatown/scripts.pory"
	closemessage
# 311 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_TEMP_1
	goto Tamatown_EventScript_TrubbishCan_5

Tamatown_EventScript_TrubbishCan_10:
# 237 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8004, 0
# 238 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8005, 3
# 239 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8006, 4
# 240 "data/maps/Tamatown/scripts.pory"
	setvar VAR_0x8007, 2
# 241 "data/maps/Tamatown/scripts.pory"
	special ShakeScreen
# 242 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_TRUBBISH, CRY_MODE_NORMAL
# 243 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_8
# 244 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_9
# 248 "data/maps/Tamatown/scripts.pory"
	waitmoncry
# 249 "data/maps/Tamatown/scripts.pory"
	closemessage
# 251 "data/maps/Tamatown/scripts.pory"
	playse SE_PIN
# 252 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_PLAYER, Tamatown_EventScript_Tangela_Movement_0
# 253 "data/maps/Tamatown/scripts.pory"
	waitse
# 254 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 256 "data/maps/Tamatown/scripts.pory"
	clearflag POKEGOTCHI_FLAG_HIDE_TRUBBISH
# 257 "data/maps/Tamatown/scripts.pory"
	addobject LOCALID_TRUBBISH
# 259 "data/maps/Tamatown/scripts.pory"
	playse SE_LEDGE
# 260 "data/maps/Tamatown/scripts.pory"
	applymovement LOCALID_TRUBBISH, Tamatown_EventScript_TrubbishCan_Movement_0
# 261 "data/maps/Tamatown/scripts.pory"
	waitmovement 0
# 263 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_TrubbishCan_Text_0
# 264 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_TrubbishCan_Text_10
	goto Tamatown_EventScript_TrubbishCan_9


Tamatown_EventScript_Slowpoke::
# 324 "data/maps/Tamatown/scripts.pory"
	lock
# 326 "data/maps/Tamatown/scripts.pory"
	goto_if_set FLAG_EXPLAINED_RESTAURANT, Tamatown_EventScript_Slowpoke_2
# 336 "data/maps/Tamatown/scripts.pory"
	setflag FLAG_EXPLAINED_RESTAURANT
# 338 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 339 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 340 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_2
Tamatown_EventScript_Slowpoke_1:
# 352 "data/maps/Tamatown/scripts.pory"
	mcdialogueB Tamatown_EventScript_Slowpoke_Text_3, Tamatown_EventScript_Slowpoke_Text_4
# 357 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Tamatown_EventScript_Slowpoke_6
# 447 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_FAINT
# 448 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 449 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_16
Tamatown_EventScript_Slowpoke_5:
# 456 "data/maps/Tamatown/scripts.pory"
	closemessage
# 458 "data/maps/Tamatown/scripts.pory"
	release
	return

Tamatown_EventScript_Slowpoke_2:
# 327 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 328 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 329 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_1
	goto Tamatown_EventScript_Slowpoke_1

Tamatown_EventScript_Slowpoke_6:
# 358 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_HIGH_PITCH
# 359 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 360 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_5
# 365 "data/maps/Tamatown/scripts.pory"
	callnative PlayPokegotchiWaiterMinigameHard
# 366 "data/maps/Tamatown/scripts.pory"
	waitstate
# 368 "data/maps/Tamatown/scripts.pory"
	setspeaker Tamatown_EventScript_Slowpoke_Text_0
# 370 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 20
	goto_if_gt Tamatown_EventScript_Slowpoke_9
# 393 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_gt Tamatown_EventScript_Slowpoke_10
# 416 "data/maps/Tamatown/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_gt Tamatown_EventScript_Slowpoke_11
# 440 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 441 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_15
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_9:
# 371 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 373 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_6
# 378 "data/maps/Tamatown/scripts.pory"
	closemessage
# 380 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_7
# 383 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 384 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 385 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 3
# 387 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_8
# 390 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 391 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 392 "data/maps/Tamatown/scripts.pory"
	addcoins 10
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_10:
# 394 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 396 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_9
# 401 "data/maps/Tamatown/scripts.pory"
	closemessage
# 403 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_10
# 406 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 407 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 408 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 2
# 410 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_11
# 413 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 414 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 415 "data/maps/Tamatown/scripts.pory"
	addcoins 5
	goto Tamatown_EventScript_Slowpoke_5

Tamatown_EventScript_Slowpoke_11:
# 417 "data/maps/Tamatown/scripts.pory"
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
# 419 "data/maps/Tamatown/scripts.pory"
	msgbox Tamatown_EventScript_Slowpoke_Text_12
# 424 "data/maps/Tamatown/scripts.pory"
	closemessage
# 426 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_13
# 429 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 430 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 431 "data/maps/Tamatown/scripts.pory"
	addpokegotchifood FEED_FOOD_KEY_HOT_DOG, 1
# 433 "data/maps/Tamatown/scripts.pory"
	message Tamatown_EventScript_Slowpoke_Text_14
# 436 "data/maps/Tamatown/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 437 "data/maps/Tamatown/scripts.pory"
	waitfanfare
# 438 "data/maps/Tamatown/scripts.pory"
	addcoins 3
	goto Tamatown_EventScript_Slowpoke_5


# 13 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_0:
# 13 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
	step_end

# 66 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_1:
# 66 "data/maps/Tamatown/scripts.pory"
	walk_right
# 66 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 68 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_2:
# 68 "data/maps/Tamatown/scripts.pory"
	walk_left
# 68 "data/maps/Tamatown/scripts.pory"
	walk_down
# 68 "data/maps/Tamatown/scripts.pory"
	walk_down
# 68 "data/maps/Tamatown/scripts.pory"
	walk_right
# 68 "data/maps/Tamatown/scripts.pory"
	walk_right
# 68 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 70 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Porygon_Movement_3:
# 70 "data/maps/Tamatown/scripts.pory"
	walk_down
# 70 "data/maps/Tamatown/scripts.pory"
	walk_right
# 70 "data/maps/Tamatown/scripts.pory"
	walk_right
# 70 "data/maps/Tamatown/scripts.pory"
	face_up
	step_end

# 163 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_Tangela_Movement_0:
# 163 "data/maps/Tamatown/scripts.pory"
	emote_exclamation_mark
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
# 163 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 260 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_0:
# 260 "data/maps/Tamatown/scripts.pory"
	jump_in_place_down
# 260 "data/maps/Tamatown/scripts.pory"
	delay_16
# 260 "data/maps/Tamatown/scripts.pory"
	delay_16
# 260 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 274 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_1:
# 274 "data/maps/Tamatown/scripts.pory"
	emote_heart
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
# 274 "data/maps/Tamatown/scripts.pory"
	delay_16
	step_end

# 291 "data/maps/Tamatown/scripts.pory"
Tamatown_EventScript_TrubbishCan_Movement_2:
# 291 "data/maps/Tamatown/scripts.pory"
	emote_heart
	step_end

Tamatown_EventScript_Porygon_Text_0:
# 17 "data/maps/Tamatown/scripts.pory"
	.string "Porygon$"

Tamatown_EventScript_Porygon_Text_1:
# 19 "data/maps/Tamatown/scripts.pory"
	.string "Yooo, my man's back!\nWanna play {COLOR RED}PACHINKO{COLOR DARK_GRAY}??\p$"

Tamatown_EventScript_Porygon_Text_2:
# 27 "data/maps/Tamatown/scripts.pory"
	.string "Yo, my man, come over here…\p"
	.string "Wanna try your luck at the most fun\nway to lose money ever invented?\l"
	.string "That's right, {COLOR RED}PACHINKO{COLOR DARK_GRAY}!!\p"
	.string "A game costs 3 coins.\nI'll give you 15 coins everyday!\p"
	.string "What are the coins for? Uhh…\nThey look super neat!$"

Tamatown_EventScript_Porygon_Text_3:
# 38 "data/maps/Tamatown/scripts.pory"
	.string "You got 15 coins!$"

Tamatown_EventScript_Porygon_Text_4:
# 51 "data/maps/Tamatown/scripts.pory"
	.string "I wanna play!$"

Tamatown_EventScript_Porygon_Text_5:
# 52 "data/maps/Tamatown/scripts.pory"
	.string "Nah.$"

Tamatown_EventScript_Porygon_Text_6:
# 60 "data/maps/Tamatown/scripts.pory"
	.string "Heck yeah! Have fun!$"

Tamatown_EventScript_Porygon_Text_7:
# 87 "data/maps/Tamatown/scripts.pory"
	.string "Aight, aight, can't help ya if you\nhate fun…$"

Tamatown_EventScript_Tree_Text_0:
# 98 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.\nIt kinda looks like your cousin Mark.$"

Tamatown_EventScript_Tangela_Text_0:
# 108 "data/maps/Tamatown/scripts.pory"
	.string "Tangela$"

Tamatown_EventScript_Tangela_Text_1:
# 110 "data/maps/Tamatown/scripts.pory"
	.string "Don't look at me!\nI am invisible!$"

Tamatown_EventScript_Tangela_Text_2:
# 115 "data/maps/Tamatown/scripts.pory"
	.string "It's a tree.$"

Tamatown_EventScript_Tangela_Text_3:
# 119 "data/maps/Tamatown/scripts.pory"
	.string "Yep$"

Tamatown_EventScript_Tangela_Text_4:
# 120 "data/maps/Tamatown/scripts.pory"
	.string "Totes$"

Tamatown_EventScript_Tangela_Text_5:
# 134 "data/maps/Tamatown/scripts.pory"
	.string "The tree moved impatiently.$"

Tamatown_EventScript_Tangela_Text_6:
# 138 "data/maps/Tamatown/scripts.pory"
	.string "Hmm.$"

Tamatown_EventScript_Tangela_Text_7:
# 139 "data/maps/Tamatown/scripts.pory"
	.string "Ahem.$"

Tamatown_EventScript_Tangela_Text_8:
# 152 "data/maps/Tamatown/scripts.pory"
	.string "Tree$"

Tamatown_EventScript_Tangela_Text_9:
# 154 "data/maps/Tamatown/scripts.pory"
	.string "{FONT_SMALL}Hee hee hee hee…{FONT_NORMAL}$"

Tamatown_EventScript_Tangela_Text_10:
# 158 "data/maps/Tamatown/scripts.pory"
	.string "Were you hiding?$"

Tamatown_EventScript_Tangela_Text_11:
# 159 "data/maps/Tamatown/scripts.pory"
	.string "I can see you$"

Tamatown_EventScript_Tangela_Text_12:
# 170 "data/maps/Tamatown/scripts.pory"
	.string "What? Oh, man!\p"
	.string "I was trying out my new “hiding in\nplain sight” secret technique…\l"
	.string "But you saw right through me!\p"
	.string "You must be some kind of genius!$"

Tamatown_EventScript_Sign_Text_0:
# 188 "data/maps/Tamatown/scripts.pory"
	.string "“6 Week Course: How To Manipulate\nYour Human Through Pooping”$"

Tamatown_EventScript_Trashcan_Text_0:
# 198 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "As hungry as it makes you, you need\nto go.$"

Tamatown_EventScript_TrubbishCan_Text_0:
# 208 "data/maps/Tamatown/scripts.pory"
	.string "Trubbish$"

Tamatown_EventScript_TrubbishCan_Text_1:
# 212 "data/maps/Tamatown/scripts.pory"
	.string "Om nom nom nom nom…$"

Tamatown_EventScript_TrubbishCan_Text_2:
# 217 "data/maps/Tamatown/scripts.pory"
	.string "It's a trashcan.\p"
	.string "…Wait a second…\nDid the trashcan just move?$"

Tamatown_EventScript_TrubbishCan_Text_3:
# 222 "data/maps/Tamatown/scripts.pory"
	.string "It did!$"

Tamatown_EventScript_TrubbishCan_Text_4:
# 223 "data/maps/Tamatown/scripts.pory"
	.string "I'm imagining things.$"

Tamatown_EventScript_TrubbishCan_Text_5:
# 228 "data/maps/Tamatown/scripts.pory"
	.string "What to do?$"

Tamatown_EventScript_TrubbishCan_Text_6:
# 232 "data/maps/Tamatown/scripts.pory"
	.string "Kick it.$"

Tamatown_EventScript_TrubbishCan_Text_7:
# 233 "data/maps/Tamatown/scripts.pory"
	.string "Hug it.$"

Tamatown_EventScript_TrubbishCan_Text_8:
# 243 "data/maps/Tamatown/scripts.pory"
	.string "Trashcan?$"

Tamatown_EventScript_TrubbishCan_Text_9:
# 245 "data/maps/Tamatown/scripts.pory"
	.string "WAIT! WAIT! STOP!$"

Tamatown_EventScript_TrubbishCan_Text_10:
# 265 "data/maps/Tamatown/scripts.pory"
	.string "Whew! You almost got me there!\nNo, I wasn't hiding…\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_11:
# 279 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks… happy?$"

Tamatown_EventScript_TrubbishCan_Text_12:
# 294 "data/maps/Tamatown/scripts.pory"
	.string "I-I've never been held with such\nkindness before…\p"
	.string "Thanks, buddy.\nI'm happy you don't think I'm trash!\p"
	.string "I just found this box of barely licked\ndoughnuts!\p"
	.string "Look at these glazed beauties\nwhispering “Eat me”…\lI can't resist!\p"
	.string "Here, have one, you'll see what I mean!$"

Tamatown_EventScript_TrubbishCan_Text_13:
# 307 "data/maps/Tamatown/scripts.pory"
	.string "You got the Doughnut!$"

Tamatown_EventScript_TrubbishCan_Text_14:
# 314 "data/maps/Tamatown/scripts.pory"
	.string "The trashcan looks saddened.$"

Tamatown_EventScript_Slowpoke_Text_0:
# 328 "data/maps/Tamatown/scripts.pory"
	.string "Slowpoke$"

Tamatown_EventScript_Slowpoke_Text_1:
# 330 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Heeeeeeeeyyyyy…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_2:
# 341 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "… … … … … … …\p"
	.string "We opened up our restaurant\nreeeeecently… Buuuut…\p"
	.string "Customers don't tiiiiiiiip…\p"
	.string "They say the service is too sloooow…\p"
	.string "Can you belieeeeve it?\p"
	.string "You look faaaaast enouuuuuugh…\p"
	.string "Think you could help us ouuuuut?$"

Tamatown_EventScript_Slowpoke_Text_3:
# 353 "data/maps/Tamatown/scripts.pory"
	.string "For sure!$"

Tamatown_EventScript_Slowpoke_Text_4:
# 354 "data/maps/Tamatown/scripts.pory"
	.string "Sounds tiring…$"

Tamatown_EventScript_Slowpoke_Text_5:
# 361 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "Yaaaaaaaaaaaaaaaaaaay…$"

Tamatown_EventScript_Slowpoke_Text_6:
# 374 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 20 happy\ncuuuustomers…\lGreaaaaat joooob…\p"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_7:
# 381 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_8:
# 388 "data/maps/Tamatown/scripts.pory"
	.string "You got 10 coins!$"

Tamatown_EventScript_Slowpoke_Text_9:
# 397 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served over 10\ncuuuustomers…\lYou did your beeeest…"
	.string "You deserve a meaaaaaaal…\nAnd a saaaaaalaryyyyy…$"

Tamatown_EventScript_Slowpoke_Text_10:
# 404 "data/maps/Tamatown/scripts.pory"
	.string "You got 2 hot dogs!$"

Tamatown_EventScript_Slowpoke_Text_11:
# 411 "data/maps/Tamatown/scripts.pory"
	.string "You got 5 coins!$"

Tamatown_EventScript_Slowpoke_Text_12:
# 420 "data/maps/Tamatown/scripts.pory"
	.string "Thaaaanks for heeeelping ooout…\p"
	.string "You served a couple\ncuuuustomers…\lOoookaaaaay…\p"
	.string "Here's a little sooooomething…$"

Tamatown_EventScript_Slowpoke_Text_13:
# 427 "data/maps/Tamatown/scripts.pory"
	.string "You got 1 hot dog!$"

Tamatown_EventScript_Slowpoke_Text_14:
# 434 "data/maps/Tamatown/scripts.pory"
	.string "You got 3 coins!$"

Tamatown_EventScript_Slowpoke_Text_15:
# 442 "data/maps/Tamatown/scripts.pory"
	.string "Daaaaaaamn, you're even slower than\nmeeeee…\p"
	.string "Oooooh wellllllll…$"

Tamatown_EventScript_Slowpoke_Text_16:
# 450 "data/maps/Tamatown/scripts.pory"
	.string "… … … … … … …\p"
	.string "I understaaaand…\p"
	.string "It's suuuuuper tiiiiiiring…$"
